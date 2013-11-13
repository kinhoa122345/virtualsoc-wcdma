//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARM_DPI_HPP
#define ARM_DPI_HPP

#include <ostream>

namespace simsoc {

typedef enum {AND=0, EOR, ORR, BIC, TST, TEQ,
              ADD, ADC, SUB, SBC, RSB, RSC, CMP, CMN,
              MOV, MVN} DPI_Opcode;

DPI_Opcode& operator++(DPI_Opcode &op);
const DPI_Opcode FIRST_DPI = AND;
const DPI_Opcode LAST_DPI = MVN;
const DPI_Opcode FIRST_BOOL = AND;
const DPI_Opcode FIRST_INT = ADD;
const DPI_Opcode FIRST_MOVE = MOV;

std::ostream& operator<<(std::ostream &os, DPI_Opcode op);
extern const char * DPI_OPCODE_NAMES[16];

} // namespace simsoc

#endif //ARM_DPI_HPP
