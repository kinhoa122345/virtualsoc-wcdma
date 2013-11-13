//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARMV6_LLVM_GENERATOR_HPP
#define ARMV6_LLVM_GENERATOR_HPP

#include <llvm/LLVMContext.h>
#include <llvm/Support/IRBuilder.h>
#include <libsimsoc/profiling.hpp>
#include <fstream>

namespace llvm {
  class PassManager;
  class FunctionPassManager;
  class ExecutionEngine;
}

namespace simsoc {

  class ARMv6_BasicBlock;
  class ARMv6_OptimizedBasicBlock;
  struct SLv6_Instruction;

  class ARMv6_LLVM_Generator {
    ARMv6_LLVM_Generator();
    static ARMv6_LLVM_Generator *singleton;
  public:
    ~ARMv6_LLVM_Generator();
    static ARMv6_LLVM_Generator &get();

    ARMv6_OptimizedBasicBlock *compile(ARMv6_BasicBlock*);

  private:
    friend struct ARMv6_LLVM_Tools;

    void generate_one_instruction__pre(SLv6_Instruction&);
    void generate_one_instruction(SLv6_Instruction&);

    llvm::LLVMContext &context;
    llvm::IRBuilder<> IRB;

    llvm::Module *module;
    llvm::Value *proc;

    llvm::Function *increment_pc_arm32;
    llvm::Function *increment_pc_arm16;
    llvm::Function *arm_hook;
    llvm::Function *decrement_pc_if_not_OK;

    const llvm::IntegerType *const i8;
    const llvm::IntegerType *const i16;
    const llvm::IntegerType *const i32;
    const llvm::FunctionType *dyncode_type;

    llvm::PassManager *pm;
    llvm::FunctionPassManager *fpm;
    llvm::ExecutionEngine *ee;

    // profiling data
    std::ofstream profstream;
    bool profiling;
    bool prof_total;
    size_t prof_icount;
    size_t prof_bbcount;
    TimeVal prof_time;
  };

} // namespace simsoc

#endif // ARMV6_LLVM_GENERATOR_HPP
