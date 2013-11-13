//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef THUMB_DECODE_HPP
#define THUMB_DECODE_HPP

#include "libsimsoc/processors/arm/armis.hpp"

namespace simsoc {

  extern bool arm_user_level_mode;

  ARM_Instruction * thumbDecode(uint16_t bincode, uint16_t next_half);

} // namespace simsoc

#endif //THUMB_DECODE_HPP
