//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "arm_shift.hpp"
#include "libsimsoc/display.hpp"
#include "libsimsoc/processors/arm/arm_cpu.hpp"

using namespace std;

namespace simsoc {

const char * ARM_SHIFT_NAMES[5] = {"LSL", "LSR", "ASR", "ROR", "RRX"};

ostream& operator<<(ostream& os, const ARM_Shift& s) {
  return os <<ARM_SHIFT_NAMES[s];
}

} // namespace simsoc
