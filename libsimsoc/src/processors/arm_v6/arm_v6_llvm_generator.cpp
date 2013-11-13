//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "arm_v6_llvm_generator.hpp"
#include "arm_v6_dyntrans.hpp"
#include <libsimsoc/processors/llvm_gen_parameters.hpp>
#include <libsimsoc/display.hpp>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/PassManager.h>
#include <llvm/Module.h>
#include <llvm/Target/TargetData.h>
#include <llvm/Transforms/IPO.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Target/TargetSelect.h>
#include <llvm/Target/TargetOptions.h>
#include "simsoc-config.h"

using namespace std;
using namespace llvm;

namespace simsoc {

  struct ARMv6_LLVM_Deleter {
    ARMv6_LLVM_Generator *gen;
    ARMv6_LLVM_Deleter(): gen(NULL) {}
    ~ARMv6_LLVM_Deleter() {delete gen;}
  };
  ARMv6_LLVM_Deleter arm_v6_deleter;

  static const char *bitcode_file() {
    return ABS_TOP_BUILDDIR "/libsimsoc/arm_v6_llvm_lib.bc";
  }

  ARMv6_LLVM_Generator *ARMv6_LLVM_Generator::singleton = NULL;

  ARMv6_LLVM_Generator &ARMv6_LLVM_Generator::get() {
    if (!singleton) {
      singleton = new ARMv6_LLVM_Generator();
      arm_v6_deleter.gen = singleton;
    }
    return *singleton;
  }

  ARMv6_LLVM_Generator::ARMv6_LLVM_Generator():
    context(getGlobalContext()),
    IRB(context),
    module(NULL), proc(NULL),
    i8(IntegerType::get(context,8)),
    i16(IntegerType::get(context,16)),
    i32(IntegerType::get(context,32)),
    dyncode_type(NULL),
    pm(NULL), fpm(NULL), ee(NULL),
    profiling(false),
    prof_total(DT3_prof_total.get()), prof_icount(0), prof_bbcount(0), prof_time()
  {
    // Load bitcode file
    string err_str;
    MemoryBuffer *mb = MemoryBuffer::getFile(bitcode_file(),&err_str);
    if (!mb) {
      error() <<"Cannot open \"" <<bitcode_file() <<"\": " <<err_str <<endl;
      exit(1);
    }
    module = llvm::ParseBitcodeFile(mb,context,&err_str);
    if (!module) {
      error() <<"Failed to load module from bitcode file: " <<err_str <<endl;
      exit(1);
    }
    delete mb;
    debug() <<"bitcode file loaded.\n";
    // mark all slv6_* functions as "AlwaysInline"
    const string prefix("slv6_");
    const size_t len = prefix.size();
    for (llvm::Module::iterator f = module->begin(), ef = module->end(); f!=ef; ++f) {
      if (f->hasName() && !f->getNameStr().compare(0,len,prefix)) {
        debug() <<"Add \"AlwaysInline\" attribute to function "
                <<f->getNameStr() <<".\n";
        f->addFnAttr(Attribute::AlwaysInline);
      }
    }
    // Extract some common functions
    increment_pc_arm32 = module->getFunction("slv6_increment_pc_arm32");
    assert(increment_pc_arm32);
    increment_pc_arm16 = module->getFunction("slv6_increment_pc_arm16");
    assert(increment_pc_arm16);
    arm_hook = module->getFunction("slv6_lib_hook"); assert(arm_hook);
    // compute function type for dynamic code: void XXX(SLv6_Processor*)
    // NB: it is the same type than increment_pc_arm32
    dyncode_type = increment_pc_arm32->getFunctionType();
    // Initialize pass managers
    pm = new PassManager();
    pm->add(createAlwaysInlinerPass());
    fpm = new FunctionPassManager(module);
    fpm->add(new TargetData(module));
    fpm->add(createGVNPass());
    fpm->add(createInstructionCombiningPass());
    fpm->add(createCFGSimplificationPass());
    fpm->add(createDeadStoreEliminationPass());
    // Initialize the JIT compiler
#ifdef SIMSOC_HAVE_LLVM_DWARFEXCEPTIONHANDLING
    llvm::DwarfExceptionHandling = true;
#else
    llvm::JITExceptionHandling = true;
#endif
    InitializeNativeTarget();
    atexit(llvm_shutdown);  // Call llvm_shutdown() on exit.
    EngineBuilder builder(module);
    builder.setErrorStr(&err_str);
    builder.setEngineKind(EngineKind::JIT);
    builder.setOptLevel(CodeGenOpt::Default); // None/Less/Default/Aggressive
    ee = builder.create();
    if (!ee) {
      error() <<"failed to create execution engine: " <<err_str <<"\n";
      exit(1);
    }
    ee->DisableLazyCompilation(true);
    debug() <<"execution engine created; LLVM generator is ready.\n";
  }

  ARMv6_LLVM_Generator::~ARMv6_LLVM_Generator() {
    if (profiling)
      profstream.close();
    if (prof_total) {
      cout <<"[ARMv6 LLVM generator] " <<prof_icount <<" instructions in "
           <<prof_bbcount <<" blocks compiled in " <<prof_time <<endl; 
    }
  }

  ARMv6_OptimizedBasicBlock *ARMv6_LLVM_Generator::compile(ARMv6_BasicBlock *bb) {
    TimeVal start;
    if (profiling||prof_total)
      start.set();

    // create function
    Function *fct = Function::Create(dyncode_type, Function::ExternalLinkage,
                                     "dynamic_code", module);
    Function::arg_iterator arg0 = fct->arg_begin();
    arg0->setName("proc");
    proc = arg0;
    assert(++arg0==fct->arg_end());
    debug() <<"create llvm function " <<fct->getNameStr() <<".\n";
    Function *increment_pc =
      (bb->is_thumb_code) ? increment_pc_arm16 : increment_pc_arm32;
    // create and fill the main block
    BasicBlock *lbb = BasicBlock::Create(context, "entry", fct);
    IRB.SetInsertPoint(lbb);
    std::vector<SLv6_Instruction>::iterator i = bb->instructions.begin();
    const std::vector<SLv6_Instruction>::iterator ei = bb->instructions.end();
    const std::vector<SLv6_Instruction>::iterator li = ei-1;
    while (i!=li) {
      generate_one_instruction__pre(*i);
      IRB.CreateCall(increment_pc,proc);
      IRB.CreateCall(arm_hook,proc);
      ++i;
    }
    generate_one_instruction__pre(*i);
    IRB.CreateRetVoid();
    // optimize
    // fct->dump(); // display the initial llvm code
    pm->run(*module);
    // fct->dump(); // display the function after inlining
    fpm->run(*fct);
    // fct->dump(); // display the function after optimization
    // Check if everything OK
    debug() <<"LLVM code generated\n";
    ARMv6_OptimizedBasicBlock::ExecFunction nf =
      reinterpret_cast<ARMv6_OptimizedBasicBlock::ExecFunction>
      (ee->getPointerToFunction(fct));
    debug() <<"LLVM code compiled\n";
    // profiling
    if (profiling) {
      TimeVal end; end.set();
      profstream <<bb->instructions.size() <<";" <<end-start <<'\n';
    }
    if (prof_total) {
      TimeVal end; end.set();
      prof_icount += bb->instructions.size(); ++prof_bbcount;
      prof_time = prof_time + (end-start);
    }
    return new ARMv6_OptimizedBasicBlock(bb,fct,nf);
  }

  void ARMv6_LLVM_Generator::generate_one_instruction__pre(SLv6_Instruction &instr) {
    if (instr.args.g0.id==ARMv6_Processor::SET_REG_ID) {
      Function *fct = module->getFunction("slv6_X_set_reg"); assert(fct);
      Value *cond = ConstantInt::get(i32,instr.args.set_reg.cond);
      Value *d = ConstantInt::get(i8,instr.args.set_reg.d);
      Value *data = ConstantInt::get(i32,instr.args.set_reg.data);
      IRB.CreateCall4(fct,proc,cond,d,data);
    } else if (instr.args.g0.id==ARMv6_Processor::SET_REG_NC_ID) {
      Function *fct = module->getFunction("slv6_X_set_reg_nc"); assert(fct);
      Value *d = ConstantInt::get(i8,instr.args.set_reg.d);
      Value *data = ConstantInt::get(i32,instr.args.set_reg.data);
      IRB.CreateCall3(fct,proc,d,data);
    } else {
      generate_one_instruction(instr);
    }
  }

  // Include the implementation of the generate_one_instruction function,
  // automatically generated by SimSoC-CERT
#include "simlight/slv6_iss-llvm_generator.hpp"

} // namespace simsoc
