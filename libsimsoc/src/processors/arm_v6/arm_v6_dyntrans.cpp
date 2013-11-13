//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "arm_v6_dyntrans.hpp"
#include <libsimsoc/processors/llvm_gen_parameters.hpp>

#ifdef SIMSOC_HAVE_LLVM
#include "arm_v6_llvm_server.hpp"
#include "arm_v6_llvm_generator.hpp"
#include <llvm/Function.h>
#endif

#include "arm_v6_printers.hpp"
#include <cstring>

#ifndef SLV6_LDR_M2_ImmOff_NC_ID
#define SLV6_LDR_M2_ImmOff_NC_ID ((uint16_t)~0)
#endif

using namespace std;

namespace simsoc {

  // replace PC-relative LDR by "set reg"
  void optimize_pc_relative_ldr(SLv6_Instruction *instr, SLv6_Processor *proc) {
    // 1. test
    if (instr->args.g0.id!=SLV6_LDR_M2_ImmOff_ID &&
        instr->args.g0.id!=SLV6_LDR_M2_ImmOff_NC_ID) return;
    if (instr->args.SLV6_LDR_M2_ImmOff_GID.n!=15 ||
        instr->args.SLV6_LDR_M2_ImmOff_GID.d==15) return;
    if (!ConditionPassed(&proc->cpsr,instr->args.SLV6_LDR_M2_ImmOff_GID.cond)) return;
    // 2. read
    const uint8_t d = instr->args.SLV6_LDR_M2_ImmOff_GID.d;
    const uint32_t data = reg(proc,d); // the instruction has just been executed.
    const SLv6_Condition cond = instr->args.SLV6_LDR_M2_ImmOff_GID.cond;
    // 3. write
    if (cond==SLV6_AL) instr->args.g0.id = ARMv6_Processor::SET_REG_NC_ID;
    else instr->args.g0.id = ARMv6_Processor::SET_REG_ID;
    instr->sem_fct = slv6_instruction_functions[instr->args.g0.id];
    instr->args.set_reg.cond = cond;
    instr->args.set_reg.d = d;
    instr->args.set_reg.data = data;
  }

  // replace Thumb LDR3 by "set reg"
  void optimize_thumb_ldr3(SLv6_Instruction *instr, SLv6_Processor *proc) {
    // 1. test
    if (instr->args.g0.id!=SLV6_Tb_LDR3_ID) return;
    // 2. read
    const uint8_t d = instr->args.SLV6_Tb_LDR3_GID.d;
    const uint32_t data = reg(proc,d); // the instruction has just been executed.
    // 3. write
    instr->args.g0.id = ARMv6_Processor::SET_REG_NC_ID;
    instr->sem_fct = slv6_instruction_functions[instr->args.g0.id];
    instr->args.set_reg.d = d;
    instr->args.set_reg.data = data;
  }

  // Semantics functions of special instruction

#ifdef SIMSOC_HAVE_LLVM
  void exec_opt_basic_block(SLv6_Processor *proc,
                            SLv6_Instruction *instr) {
    (*instr->args.opt_basic_block.obb->native_function)(proc);
  }
#endif // SIMSOC_HAVE_LLVM

  // Execution of a basic block
  static void exec_basic_block_32(SLv6_Processor *proc,
                                  SLv6_Instruction *instr) {
    ARMv6_Processor &arm = *proc->proc_ptr;
    assert(!proc->jump);
    ARMv6_BasicBlock &bb = *instr->args.basic_block.bb;
    std::vector<SLv6_Instruction>::iterator i = bb.instructions.begin();
    const std::vector<SLv6_Instruction>::iterator ei = bb.instructions.end();
    const std::vector<SLv6_Instruction>::iterator li = ei-1;
    while (i!=li) {
      assert(i->args.g0.id<=ARMv6_Processor::SET_REG_NC_ID);
      arm.debug() <<"execute: \t" <<slv6_instruction_names[i->args.g0.id] <<endl;
      i->sem_fct(proc,&*i);
      assert(!proc->jump);
      increment_pc_arm32(proc);
      slv6_hook(proc);
      ++i;
    }
    assert(i->args.g0.id<=ARMv6_Processor::SET_REG_NC_ID);
    arm.debug() <<"execute: \t" <<slv6_instruction_names[i->args.g0.id] <<endl;
    i->sem_fct(proc,&*i);
  }

  static void exec_basic_block_16(SLv6_Processor *proc,
                                  SLv6_Instruction *instr) {
    ARMv6_Processor &arm = *proc->proc_ptr;
    assert(!proc->jump);
    ARMv6_BasicBlock &bb = *instr->args.basic_block.bb;
    std::vector<SLv6_Instruction>::iterator i = bb.instructions.begin();
    const std::vector<SLv6_Instruction>::iterator ei = bb.instructions.end();
    const std::vector<SLv6_Instruction>::iterator li = ei-1;
    while (i!=li) {
      assert(i->args.g0.id<=ARMv6_Processor::SET_REG_NC_ID);
      arm.debug() <<"execute: \t" <<slv6_instruction_names[i->args.g0.id] <<endl;
      i->sem_fct(proc,&*i);
      assert(!proc->jump);
      increment_pc_arm16(proc);
      slv6_hook(proc);
      ++i;
    }
    assert(i->args.g0.id<=ARMv6_Processor::SET_REG_NC_ID);
    arm.debug() <<"execute: \t" <<slv6_instruction_names[i->args.g0.id] <<endl;
    i->sem_fct(proc,&*i);
  }

  static void exec_basic_block_32_prof(SLv6_Processor *proc,
                                       SLv6_Instruction *instr) {
#ifdef SIMSOC_HAVE_LLVM
    ARMv6_BasicBlock &bb = *instr->args.basic_block.bb;
    ++bb.count;
    if (bb.count > proc->proc_ptr->dt3_threshold) {
      instr->args.opt_basic_block.obb = ARMv6_LLVM_Generator::get().compile(&bb);
      instr->args.g0.id = ARMv6_Processor::OPT_BASIC_BLOCK_ID;
      instr->sem_fct = exec_opt_basic_block;
      proc->proc_ptr->info() <<"basic block at address " <<hex <<simsoc::get_pc(proc)
                             <<" compiled to native code\n";
      exec_opt_basic_block(proc,instr);
      return;
    }
#else
    abort(); // should be unreachable
#endif
    exec_basic_block_32(proc,instr);
  }

  static void exec_basic_block_16_prof(SLv6_Processor *proc,
                                       SLv6_Instruction *instr) {
#ifdef SIMSOC_HAVE_LLVM
    ARMv6_BasicBlock &bb = *instr->args.basic_block.bb;
    ++bb.count;
    if (bb.count > proc->proc_ptr->dt3_threshold) {
      instr->args.opt_basic_block.obb = ARMv6_LLVM_Generator::get().compile(&bb);
      instr->args.g0.id = ARMv6_Processor::OPT_BASIC_BLOCK_ID;
      instr->sem_fct = exec_opt_basic_block;
      proc->proc_ptr->info() <<"basic block at address " <<hex <<simsoc::get_pc(proc)
                             <<" compiled to native code\n";
      exec_opt_basic_block(proc,instr);
      return;
    }
#else
    abort(); // should be unreachable
#endif
    exec_basic_block_16(proc,instr);
  }

#ifdef SIMSOC_HAVE_LLVM
  static inline void basic_block_server_profiling(SLv6_Processor *proc,
                                                  SLv6_Instruction *instr) {
    ARMv6_BasicBlock &bb = *instr->args.basic_block.bb;
    --bb.partial_count;
    if (bb.partial_count<=0 && !bb.inside_comp_queue) {
      const size_t cqt = DT3_comp_queue_threshold.get();
      bb.count += cqt;
      bb.partial_count = cqt;
      bb.inside_comp_queue = true;
      ARMv6_LLVM_Server::get().add_candidate(&bb);
    }
  }
#endif

  static void exec_basic_block_32_serv_prof(SLv6_Processor *proc,
                                            SLv6_Instruction *instr) {
#ifdef SIMSOC_HAVE_LLVM
    basic_block_server_profiling(proc,instr);
#else
    abort(); // should be unreachable
#endif
    exec_basic_block_32(proc,instr);
  }

  static void exec_basic_block_16_serv_prof(SLv6_Processor *proc,
                                            SLv6_Instruction *instr) {
#ifdef SIMSOC_HAVE_LLVM
    basic_block_server_profiling(proc,instr);
#else
    abort(); // should be unreachable
#endif
    exec_basic_block_16(proc,instr);
  }

  // Construction of a basic block
  void armv6_exec_empty_cell(SLv6_Processor *proc,
                             SLv6_Instruction *instr) {
    ARMv6_Processor &arm = *proc->proc_ptr;
    SLv6_Instruction zero; memset(&zero,'\0',sizeof(SLv6_Instruction));
    const bool is_thumb = proc->cpsr.T_flag;
    ARMv6_BasicBlock *bb =
      new ARMv6_BasicBlock(is_thumb, instr); // FIXME: delete if exception
    const uint32_t start = get_pc(proc)-2*inst_size(proc);
    SLv6_Instruction *i;
    bool not_may_branch;
    uint32_t bincode;
    arm.info() <<"construct " <<(is_thumb ? "thumb" : "arm" ) <<" block starting at address "
               <<hex <<start <<".\n";
    do {
      assert(!proc->jump);
      bb->instructions.push_back(zero);
      i = &bb->instructions.back();
      if (is_thumb) {
        assert(inst_size(proc)==2);
        bincode = proc->mmu_ptr->load_instr_16(address_of_current_instruction(proc));
        thumb_decode_and_store(i,bincode);
      } else {
        assert(inst_size(proc)==4);
        bincode = proc->mmu_ptr->load_instr_32(address_of_current_instruction(proc));
        arm_decode_and_store(i,bincode);
      }
      assert(i->args.g0.id<=ARMv6_Processor::UNDEF_OR_UNPRED_ID);
      i->sem_fct = slv6_instruction_functions[i->args.g0.id];
      arm.debug() <<"execute: \t" <<ARMv6_InstPrinter(*i,bincode) <<endl;
      i->sem_fct(proc,i);
      if (is_thumb)
        optimize_thumb_ldr3(i,proc);
      else
        optimize_pc_relative_ldr(i,proc);
      not_may_branch = !may_branch(i);
      if (not_may_branch) {
        increment_pc(proc);
        slv6_hook(proc);
      }
    } while (not_may_branch);
    if (is_thumb) {
      if (arm.mode==DYN_COMP) {
        if (DT3_server.get()) {
          instr->args.g0.id = ARMv6_Processor::BASIC_BLOCK_16_SERV_PROF_ID;
          instr->sem_fct = exec_basic_block_16_serv_prof;
        } else {
          instr->args.g0.id = ARMv6_Processor::BASIC_BLOCK_16_PROF_ID;
          instr->sem_fct = exec_basic_block_16_prof;
        }
      } else {
        instr->args.g0.id = ARMv6_Processor::BASIC_BLOCK_16_ID;
        instr->sem_fct = exec_basic_block_16;
      }
    } else {
      if (arm.mode==DYN_COMP) {
        if (DT3_server.get()) {
          instr->args.g0.id = ARMv6_Processor::BASIC_BLOCK_32_SERV_PROF_ID;
          instr->sem_fct = exec_basic_block_32_serv_prof;
        } else {
          instr->args.g0.id = ARMv6_Processor::BASIC_BLOCK_32_PROF_ID;
          instr->sem_fct = exec_basic_block_32_prof;
        }
      } else {
        instr->args.g0.id = ARMv6_Processor::BASIC_BLOCK_32_ID;
        instr->sem_fct = exec_basic_block_32;
      }
    }
    instr->args.basic_block.bb = bb;
    arm.info() <<"translated block ends at address "
               <<hex <<start+(is_thumb ? 2 : 4)*(bb->instructions.size()-1) <<".\n";
  }

  static void exec_set_reg(SLv6_Processor *proc,
                           SLv6_Instruction *instr) {
    if (!ConditionPassed(&proc->cpsr,instr->args.set_reg.cond)) return;
    set_reg(proc,instr->args.set_reg.d,instr->args.set_reg.data);
  }

  static void exec_set_reg_nc(SLv6_Processor *proc,
                              SLv6_Instruction *instr) {
    set_reg(proc,instr->args.set_reg.d,instr->args.set_reg.data);
  }

  void init_dyntrans() {
    slv6_instruction_names[ARMv6_Processor::EMPTY_CELL_ID] = "empty cell";
    slv6_instruction_references[ARMv6_Processor::EMPTY_CELL_ID] = "no ref.";
    slv6_instruction_functions[ARMv6_Processor::EMPTY_CELL_ID] = armv6_exec_empty_cell;

    slv6_instruction_names[ARMv6_Processor::BASIC_BLOCK_32_ID] = "basic block (arm32)";
    slv6_instruction_references[ARMv6_Processor::BASIC_BLOCK_32_ID] = "no ref.";
    slv6_instruction_functions[ARMv6_Processor::BASIC_BLOCK_32_ID] =
      exec_basic_block_32;

    slv6_instruction_names[ARMv6_Processor::BASIC_BLOCK_16_ID] = "basic block (thumb)";
    slv6_instruction_references[ARMv6_Processor::BASIC_BLOCK_16_ID] = "no ref.";
    slv6_instruction_functions[ARMv6_Processor::BASIC_BLOCK_16_ID] =
      exec_basic_block_16;

    slv6_instruction_names[ARMv6_Processor::BASIC_BLOCK_32_PROF_ID] =
      "basic block (arm32) with profiling";
    slv6_instruction_references[ARMv6_Processor::BASIC_BLOCK_32_PROF_ID] = "no ref.";
    slv6_instruction_functions[ARMv6_Processor::BASIC_BLOCK_32_PROF_ID] =
      exec_basic_block_32_prof;

    slv6_instruction_names[ARMv6_Processor::BASIC_BLOCK_16_PROF_ID] =
      "basic block (thumb) with profiling";
    slv6_instruction_references[ARMv6_Processor::BASIC_BLOCK_16_PROF_ID] = "no ref.";
    slv6_instruction_functions[ARMv6_Processor::BASIC_BLOCK_16_PROF_ID] =
      exec_basic_block_16_prof;

    slv6_instruction_names[ARMv6_Processor::OPT_BASIC_BLOCK_ID] =
      "optimized basic block";
    slv6_instruction_references[ARMv6_Processor::OPT_BASIC_BLOCK_ID] = "no ref.";
#ifdef SIMSOC_HAVE_LLVM
    slv6_instruction_functions[ARMv6_Processor::OPT_BASIC_BLOCK_ID] =
      exec_opt_basic_block;
#endif

    slv6_instruction_names[ARMv6_Processor::SET_REG_ID] = "Set register";
    slv6_instruction_references[ARMv6_Processor::SET_REG_ID] = "no ref.";
    slv6_instruction_functions[ARMv6_Processor::SET_REG_ID] = exec_set_reg;

    slv6_instruction_names[ARMv6_Processor::SET_REG_NC_ID] = "Set register (no cond)";
    slv6_instruction_references[ARMv6_Processor::SET_REG_NC_ID] = "no ref.";
    slv6_instruction_functions[ARMv6_Processor::SET_REG_NC_ID] = exec_set_reg_nc;
  }

  // Constructor
  ARMv6_BasicBlock::ARMv6_BasicBlock(bool thumb, SLv6_Instruction *bl):
    instructions(), count(0),
    partial_count(DT3_comp_queue_threshold.get()),
    is_thumb_code(thumb),
    inside_comp_queue(false), being_compiled(false), back_link(bl)
  {
    assert(back_link);
  }

  // Destructor
  ARMv6_BasicBlock::~ARMv6_BasicBlock() {
    assert(!inside_comp_queue);
    assert(!being_compiled);
  }

  void ARMv6_BasicBlock::try_delete(ARMv6_BasicBlock *bb) {
    if (!bb) return;
#ifdef SIMSOC_HAVE_LLVM
    if (bb->being_compiled) {
      bb->back_link = NULL;
      return;
    }
    if (bb->inside_comp_queue)
      ARMv6_LLVM_Server::get().remove_candidate(bb);
#endif // SIMSOC_HAVE_LLVM
    delete bb;
  }

#ifdef SIMSOC_HAVE_LLVM
  // Constructor
  ARMv6_OptimizedBasicBlock::ARMv6_OptimizedBasicBlock(ARMv6_BasicBlock *bb,
                                                       llvm::Function *lf,
                                                       ExecFunction nf):
    basic_block(bb), llvm_function(lf), native_function(nf)
  {}

  // Destructor
  ARMv6_OptimizedBasicBlock::~ARMv6_OptimizedBasicBlock() {
    llvm_function->eraseFromParent();
    delete basic_block;
  }
#endif // SIMSOC_HAVE_LLVM

} // namespace simsoc
