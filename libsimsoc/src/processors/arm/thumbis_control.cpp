//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "thumbis_control.hpp"
#include "libsimsoc/processors/arm/arm_cpu.hpp"
#include "libsimsoc/processors/arm/arm_processor.hpp"
#include "libsimsoc/display.hpp"
#include "libsimsoc/processors/arm/arm_thumb_pi.hpp"

using namespace std;

namespace simsoc {

/*****************************************************************/

THUMB_b::THUMB_b( ARM_Condition c, int32_t o):
  THUMB_Instruction(), cond(c), offset(o) {}

void THUMB_b::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond))
    proc.cpu.regs[ARM_CPU::PC] += offset;
  else
    proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_b::display(std::ostream& os) const {
  const int32_t o = offset-4;
  return os <<"b" <<cond <<"\tpc"
            <<(o>=0?'+':'-')
            <<(o>=0? o: -o);
}

/*****************************************************************/

THUMB_bl_blx1::THUMB_bl_blx1( bool x, int32_t o):
  THUMB_Instruction(), exchange(x), offset(o) {}

void THUMB_bl_blx1::exec(ARM_Processor &proc){
  proc.cpu.regs[ARM_CPU::LR] = proc.cpu.regs[ARM_CPU::PC]|1;
  proc.cpu.regs[ARM_CPU::PC] += offset;
  if (exchange)
    proc.cpu.unset_thumb_mode();
}

std::ostream& THUMB_bl_blx1::display(std::ostream& os) const {
  const int32_t o = offset-4;
  return os <<hex <<(exchange? "blx": "bl")  <<"\tpc"
            <<(o>=0?'+':'-')
            <<(o>=0? o: -o);
}

/*****************************************************************/

THUMB_bx_blx2::THUMB_bx_blx2( bool l, uint8_t m):
  THUMB_Instruction(), set_lr(l), Rm(m) {}

void THUMB_bx_blx2::exec(ARM_Processor &proc){
  uint32_t target = proc.cpu.regs[Rm];
  if (set_lr)
    proc.cpu.regs[ARM_CPU::LR] = (proc.cpu.regs[ARM_CPU::PC]-2)|1;
  switch (target&3) {
  case 0: // 00
    proc.cpu.unset_thumb_mode();
    proc.cpu.regs[ARM_CPU::PC] = target+8;
    break;
  case 2: // 10
    proc.error() <<"unpredictable word access to a non-aligned address" <<endl;
    exit(5);
  case 1: // 01
  case 3: // 11
    proc.cpu.regs[ARM_CPU::PC] = (target&~1)+4;
  }
}

std::ostream& THUMB_bx_blx2::display(std::ostream& os) const {
  return os <<(set_lr? "blx": "bx") <<'\t' <<(ARM_AsmId) Rm;
}

/*****************************************************************/

THUMB_swi::THUMB_swi( uint8_t i):
  THUMB_Instruction(), immed(i) {}

void THUMB_swi::exec(ARM_Processor &proc) {
  proc.software_interrupt();
}

std::ostream& THUMB_swi::display(std::ostream& os) const {
  return os <<"swi\t" <<immed;
}

/*****************************************************************/

THUMB_bkpt::THUMB_bkpt( uint8_t i):
  THUMB_Instruction(), immed(i) {}

void THUMB_bkpt::exec(ARM_Processor &proc) {
  TODO("THUMB BKPT instruction");
}

std::ostream& THUMB_bkpt::display(std::ostream& os) const {
  return os <<"bkpt\t" <<immed;
}

} // namespace simsoc
