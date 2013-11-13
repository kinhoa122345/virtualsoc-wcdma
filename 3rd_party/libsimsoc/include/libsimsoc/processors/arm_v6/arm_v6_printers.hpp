//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARM_V6_PRINTERS_HPP
#define ARM_V6_PRINTERS_HPP

#include "simlight/slv6_condition.h"
#include "simlight/slv6_mode.h"
#include <ostream>

namespace simsoc {

  extern void slv6_print_cond(std::ostream &, SLv6_Condition);
  extern void slv6_print_mode(std::ostream &, SLv6_Mode);
  extern void slv6_print_reg(std::ostream &, uint8_t);
  extern void slv6_print_reglist(std::ostream &, uint16_t);

} // namespace simsoc

#include "simlight/slv6_iss_printers.hpp"

namespace simsoc {

  struct ARMv6_InstPrinter: Printable {
    const SLv6_Instruction &instr;
    const uint32_t bincode;
    inline ARMv6_InstPrinter(const SLv6_Instruction &i, uint32_t b):
      instr(i), bincode(b) {}
    std::ostream &display(std::ostream &os) const;
    static uint32_t thumb_bl_offset;
  };

} // namespace simsoc


#endif // ARM_V6_PRINTERS_HPP
