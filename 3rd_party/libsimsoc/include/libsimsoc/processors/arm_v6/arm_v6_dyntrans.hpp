//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARM_V6_DYNTRANS_HPP
#define ARM_V6_DYNTRANS_HPP

#include <libsimsoc/simsoc-config.h>
#include "arm_v6_processor.hpp"
#include <vector>

#ifdef SIMSOC_HAVE_LLVM
namespace llvm {class Function;}
#endif

namespace simsoc {

  // fill the tables "slv6_instruction_*s"
  void init_dyntrans();

  // execute and construct a basic block
  extern void armv6_exec_empty_cell(SLv6_Processor *proc,
                                    SLv6_Instruction *instr);

  // execute an optimized basic block
  extern void exec_opt_basic_block(SLv6_Processor *proc,
                                   SLv6_Instruction *instr);

  class ARMv6_BasicBlock {
  public:
    ARMv6_BasicBlock(bool thumb, SLv6_Instruction *back_link);
    ~ARMv6_BasicBlock();
    static void try_delete(ARMv6_BasicBlock*);

    std::vector<SLv6_Instruction> instructions;
    size_t count; // number of time that this block has been executed
    int partial_count; // about insertion in the compilation queue
    bool is_thumb_code;
    bool inside_comp_queue;
    bool being_compiled;
    SLv6_Instruction *back_link;
  };

#ifdef SIMSOC_HAVE_LLVM
  class ARMv6_OptimizedBasicBlock {
  public:
    typedef void (*ExecFunction)(SLv6_Processor*);
    ARMv6_OptimizedBasicBlock(ARMv6_BasicBlock*, llvm::Function*, ExecFunction);
    ~ARMv6_OptimizedBasicBlock();
    ARMv6_BasicBlock *basic_block;
    llvm::Function *llvm_function;
    ExecFunction native_function;
  };
#endif // SIMSOC_HAVE_LLVM

} // namespace simsoc

#endif // ARM_V6_DYNTRANS_HPP
