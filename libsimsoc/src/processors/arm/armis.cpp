//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "armis.hpp"
#include <cassert>
#include "libsimsoc/processors/arm/armpi.hpp"
#include "libsimsoc/processors/arm/arm_processor.hpp"
#include "libsimsoc/display.hpp"

using namespace std;

namespace simsoc {

  /******************************************************************************/

  bool ARM_Instruction::may_raise_something() const {return true;}
  bool ARM_Instruction::may_branch() const {return true;}

  /******************************************************************************/

  void ARM_Undefined::exec(ARM_Processor &proc) {
    proc.undefined_interrupt();
  }
  ostream& ARM_Undefined::display(ostream& os) const {
    return os <<"Undefined instruction: " <<msg;
  }

  /******************************************************************************/

  void ARM_Unpredictable::exec(ARM_Processor &proc) {
    proc.error() <<"unpredictable instruction: " <<msg <<endl;
    exit(4);
  }
  ostream& ARM_Unpredictable::display(ostream& os) const {
    return os <<"Unpredictable instruction: " <<msg;
  }

  /******************************************************************************/

  void ARM_Nop::exec(ARM_Processor &proc) {
    proc.cpu.regs[ARM_CPU::PC] += proc.cpu.cpsr.t? 2: 4;
  }
  ostream& ARM_Nop::display(ostream &os) const {
    return os <<"NOP";
  }

  bool ARM_Nop::may_raise_something() const {return false;}
  bool ARM_Nop::may_branch() const {return false;}

} // namespace simsoc
