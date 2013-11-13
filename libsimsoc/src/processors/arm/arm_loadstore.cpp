//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "arm_loadstore.hpp"

namespace simsoc {

LoadStoreOpcode& operator++(LoadStoreOpcode &op) {
  return (LoadStoreOpcode &) ++((unsigned int &) op);
}

std::ostream& operator<<(std::ostream &os, LoadStoreOpcode op) {
  return os <<LOADSTORE_OPCODE_NAMES[(unsigned int) op];
}

const char * LOADSTORE_OPCODE_NAMES[14] =
  { "LDR","LDRB","STR","STRB",
    "LDRT","LDRBT","STRT","STRBT",
    "LDRH","LDRSB", "LDRSH", "STRH", "LDRD", "STRD" };

} // namespace simsoc
