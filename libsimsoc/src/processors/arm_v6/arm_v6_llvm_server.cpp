//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "arm_v6_llvm_server.hpp"
#include <libsimsoc/processors/compil_server.tpp>

namespace simsoc {

  template class CompilationQueue<ARMv6_DT3>;
  template class CompilationServer<ARMv6_DT3>;

  ARMv6_LLVM_Server *ARMv6_LLVM_Server::singleton = NULL;

  ARMv6_LLVM_Server &ARMv6_LLVM_Server::get() {
    if (!singleton) {
      singleton = new ARMv6_LLVM_Server(); // FIXME: delete before exit
    }
    return *singleton;
  }

  ARMv6_LLVM_Server::ARMv6_LLVM_Server():
    comp_queue(), comp_server(), server_busy(false)
  {}

  void ARMv6_LLVM_Server::add_candidate(ARMv6_BasicBlock *bb) {
    assert(bb);
    bb->inside_comp_queue = true;
    comp_queue.add_candidate(bb);
  }

  void ARMv6_LLVM_Server::remove_candidate(ARMv6_BasicBlock *bb) {
    assert(bb);
    bb->inside_comp_queue = false;
    comp_queue.remove_candidate(bb);
  }

  void ARMv6_LLVM_Server::synchronize() {
    if (server_busy) {
      ARMv6_OptimizedBasicBlock *obb = comp_server.get_result();
      if (obb) {
        info() <<"insert an optimized bock to the instruction cache\n";
        server_busy = false;
        obb->basic_block->being_compiled = false;
        SLv6_Instruction *instr = obb->basic_block->back_link;
        if (instr) {
          info() <<"insert obb in the instruction cache\n";
          instr->args.g0.id = ARMv6_Processor::OPT_BASIC_BLOCK_ID;
          instr->sem_fct = exec_opt_basic_block;
          instr->args.opt_basic_block.obb = obb;
        } else {
          info() <<"Optimized block outdated, and so discarded\n";
          delete obb;
        }
      }
    }
    if (!server_busy) {
      ARMv6_BasicBlock *bb = comp_queue.select_candidate();
      if (bb) {
        bb->inside_comp_queue = false;
        bb->being_compiled = true;
        server_busy = true;
        info() <<"send a request to the compilation server\n";
        comp_server.do_that(bb);
      }
    }
  }

} // namespace simsoc
