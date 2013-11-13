//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARM_DECODE_HPP
#define ARM_DECODE_HPP

#include "libsimsoc/processors/arm/armis.hpp"

namespace simsoc {

  extern bool arm_user_level_mode;

  ARM_Instruction * armDecode(uint32_t instr);

} // namespace simsoc

#endif //ARM_DECODE_HPP
