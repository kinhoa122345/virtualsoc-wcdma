// Stub for the simlight code
// NB: compiled as C++ code.

#ifndef ARM_SYSTEM_COPROC_H
#define ARM_SYSTEM_COPROC_H

#include "../arm_v5_systemcontrol_coproc.hpp"

namespace simsoc {

  typedef ARMv6_SystemCoproc SLv6_SystemCoproc;
  
  static inline void init_CP15(SLv6_SystemCoproc *cp15) {}
  
  static inline bool CP15_reg1_VEbit(const SLv6_SystemCoproc *cp15) {
    return cp15->get_VE();
  }
  
  static inline bool CP15_reg1_EEbit(const SLv6_SystemCoproc *cp15) {
    return cp15->get_EE();
  }
  
  static inline bool CP15_reg1_Ubit(const SLv6_SystemCoproc *cp15) {
    return cp15->get_U();
  }
  
  static inline bool CP15_reg1_Vbit(const SLv6_SystemCoproc *cp15) {
    return cp15->get_exception_vector();
  }

} // namespace simsoc

#endif // ARM_SYSTEM_COPROC_H
