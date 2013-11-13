//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARM_SHIFT_HPP
#define ARM_SHIFT_HPP

#include <inttypes.h>
#include <iostream>

#include "libsimsoc/processors/arm/arm_status_register.hpp"
#include "libsimsoc/bitwise_operator.hpp"

namespace simsoc {

typedef enum {LSL, LSR, ASR, ROR, RRX} ARM_Shift;
extern const char * ARM_SHIFT_NAMES[5];
std::ostream& operator<<(std::ostream& os, const ARM_Shift& s);

inline uint32_t valueLSL(uint32_t r, uint8_t s) {
  return (s<32)? r<<s: 0;
}
inline void carryLSL(ARM_StatusRegister& sr, uint32_t r, uint8_t s) {
  if (s>32)
    sr.c = false;
  else if (s)
    sr.c = r&(1<<(32-s));
}

inline uint32_t valueLSR(uint32_t r, uint8_t s) {
  return (s<32)? r>>s: 0;
}
inline void carryLSR(ARM_StatusRegister& sr, uint32_t r, uint8_t s) {
  if (s>32)
    sr.c = false;
  else if (s)
    sr.c = r&(1<<(s-1));
}

inline uint32_t valueASR(uint32_t r, uint8_t s) {
  return (s<32)? (uint32_t) ((int32_t) r >>s): ((r&(1<<31))? ~0: 0);
}
inline void carryASR(ARM_StatusRegister& sr, uint32_t r, uint8_t s) {
  if (s)
    if (s>=32)
      sr.c = r&(1<<31);
    else
      sr.c = r&(1<<(s-1));
}

inline uint32_t valueROR(uint32_t r, uint8_t s) {
  return rotateRight(r,s&0x1f);
}
inline void carryROR(ARM_StatusRegister& sr, uint32_t r, uint8_t s) {
  if (s)
    if (s&0x1f)
      sr.c = r&(1<<((s&0x1f)-1));
    else
      sr.c = r&(1<<31);
}

inline uint32_t valueRRX(uint32_t r, bool C) {
  return C? (1<<31)|(r>>1): r>>1;
}
inline void carryRRX(ARM_StatusRegister& sr, uint32_t r) {
  sr.c = r&1;
}

} // namespace simsoc

#endif //ARM_SHIFT_HPP
