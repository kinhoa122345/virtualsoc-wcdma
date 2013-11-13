//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "arm_dpi.hpp"

using namespace std;

namespace simsoc {

DPI_Opcode& operator++(DPI_Opcode &op) {
  return (DPI_Opcode &) ++((unsigned int &) op);
}

ostream& operator<<(ostream &os, DPI_Opcode op) {
  return os <<DPI_OPCODE_NAMES[(unsigned int) op];
}

const char * DPI_OPCODE_NAMES[16] =
  {"AND", "EOR", "ORR", "BIC", "TST", "TEQ",
   "ADD", "ADC", "SUB", "SBC", "RSB", "RSC", "CMP", "CMN",
   "MOV", "MVN"};

} // namespace simsoc
