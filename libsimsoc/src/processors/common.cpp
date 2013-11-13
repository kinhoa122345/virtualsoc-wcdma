//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "common.hpp"
#include <cassert>

namespace simsoc {

const char * ARCH_NAMES[LAST_ARCH] = { "ARM", "POWERPC", "MIPS" };


const char * PSEUDOSTATUS_NAMES[LAST_PSEUDO] =  { "OK", "BRANCH", "FORWARD_BRANCH",
                                       "BACK_BRANCH", "BRANCH_SAME_PAGE",
                                       "LONG_BRANCH", "CALL", "RETURN",
                                       "SPECIAL", "NEXT_PAGE" };

std::ostream& operator<<(std::ostream &os, const PseudoStatus& s) {
  assert(static_cast<int>(s)<LAST_PSEUDO);
  return os << PSEUDOSTATUS_NAMES[static_cast<int>(s)];
}

std::ostream& operator<<(std::ostream &os, const Architecture &a) {
  assert(static_cast<int>(a)<LAST_ARCH);
  return os << ARCH_NAMES[static_cast<int>(a)];
}

} // namespace simsoc
