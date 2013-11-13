#ifndef slv6_iss_PRINTERS_HPP
#define slv6_iss_PRINTERS_HPP

#include <ostream>
#include "slv6_iss.h"

namespace simsoc {

  typedef void (*PrintFunction)(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode);
  extern PrintFunction slv6_printers[SLV6_TABLE_SIZE];

  extern void slv6_print_instr(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode);

} // namespace simsoc

#endif // slv6_iss_PRINTERS_HPP
