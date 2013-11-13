//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "arm_status_register.hpp"

using namespace std;

namespace simsoc {

  const char * ARM_MODE_NAMES[7] = {"FIQ", "IRQ", "ABT", "UND", "SVC", "System", "User"};

  ARM_Mode arm_mode(uint8_t binary) {
    switch (binary) {
    case 0x11: return ARM_FIQ;
    case 0x12: return ARM_IRQ;
    case 0x17: return ARM_ABT;
    case 0x1b: return ARM_UND;
    case 0x13: return ARM_SVC;
    case 0x1f: return ARM_SYSTEM;
    case 0x10: return ARM_USER;
    default: return ARM_WRONG;
    }
  }

  const uint8_t ARM_StatusRegister::MODE_BITS[7] =
    {0x11, 0x12, 0x17, 0x1b, 0x13,  0x1f,  0x10};
  //  FIQ,  IRQ,  ABT,  UND,  SVC, SYSTEM, USER

  ARM_StatusRegister::ARM_StatusRegister():
    n(false), z(false), c(false), v(false), q(false),
    i(true), f(true), t(false), mode(ARM_SYSTEM)
  {}

  uint32_t ARM_StatusRegister::binary_encoding() const {
    uint32_t x = 0;
    if (n) x |= 1<<31;
    if (z) x |= 1<<30;
    if (c) x |= 1<<29;
    if (v) x |= 1<<28;
    if (q) x |= 1<<27;
    if (i) x |= 1<<7;
    if (f) x |= 1<<6;
    if (t) x |= 1<<5;
    x |= ARM_StatusRegister::MODE_BITS[mode];
    return x;
  }

  ostream& operator<<(ostream& os, const simsoc::ARM_Mode& m) {
    return os <<simsoc::ARM_MODE_NAMES[m];
  }
  
  ostream& ARM_StatusRegister::display(ostream& os) const {
    return os <<(n?'N':'n') <<(z?'Z':'z') <<(c?'C':'c')
              <<(v?'V':'v') <<", " <<(q?'Q':'q') <<", "
              <<(i?'I':'i') <<(f?'F':'f') <<(t?'T':'t') <<", "
              <<mode;
  }

} // namespace simsoc
