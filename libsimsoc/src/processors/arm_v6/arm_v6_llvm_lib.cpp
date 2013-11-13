//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// compiled with llvm-g++, and included after simlight/slv6_iss_expanded.hot.c

namespace simsoc {

  extern "C" void slv6_increment_pc_arm32(struct SLv6_Processor *proc) {
    increment_pc_arm32(proc);
  }

  extern "C" void slv6_increment_pc_arm16(struct SLv6_Processor *proc) {
    increment_pc_arm16(proc);
  }

  extern "C" void slv6_lib_hook(struct SLv6_Processor *proc) {
    slv6_hook(proc);
  }

  extern "C" void slv6_X_set_reg(SLv6_Processor *proc,
                                 const SLv6_Condition cond,
                                 const uint8_t d,
                                 const uint32_t data) {
    if (!ConditionPassed(&proc->cpsr,cond)) return;
    set_reg(proc,d,data);
  }
  
  extern "C" void slv6_X_set_reg_nc(SLv6_Processor *proc,
                                    const uint8_t d,
                                    const uint32_t data) {
    set_reg(proc,d,data);
  }

}
