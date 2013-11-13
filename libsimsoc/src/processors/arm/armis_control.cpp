//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "armis_control.hpp"
#include "libsimsoc/processors/arm/arm_translation_page.hpp"
#include "libsimsoc/processors/arm/arm_processor.hpp"
#include "libsimsoc/display.hpp"

using namespace std;

namespace simsoc {

/******************************************************************************/
void ARM_b::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond))
    proc.cpu.regs[ARM_CPU::PC] += offset;
  else
    proc.cpu.regs[ARM_CPU::PC] += 4;
}

ostream& ARM_b::display(ostream& os) const {
  int32_t o = offset-8;
  return os <<"B" <<cond <<hex <<"\tpc"
            <<(o>=0?'+':'-')
            <<(o>=0? o: -o);
}

/******************************************************************************/

void ARM_Idle::exec(ARM_Processor &proc) {
  proc.idle();
}

ostream& ARM_Idle::display(ostream& os) const {
  return os <<"B\tpc-8 ; idle loop";
}

/******************************************************************************/

void ARM_bl::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    proc.cpu.regs[ARM_CPU::LR] = proc.cpu.regs[ARM_CPU::PC] - 4;
    proc.cpu.regs[ARM_CPU::PC] += offset;
  } else
    proc.cpu.regs[ARM_CPU::PC] += 4;
}

ostream& ARM_bl::display(ostream& os) const {
  int32_t o = offset-8;
  return os <<"BL" <<cond <<hex <<"\tpc"
            <<(o>=0?'+':'-')
            <<(o>=0? o: -o);
}

/******************************************************************************/

void ARM_bx::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t addr = proc.cpu.regs[Rm];
    switch (addr&3) {
    case 0: // 00
      proc.cpu.regs[ARM_CPU::PC] = addr+8; break;
    case 2: // 10
      proc.error() <<"unpredictable branching to a non-aligned address" <<endl;
      exit(5);
    case 1: // 01
    case 3: // 11
      proc.cpu.regs[ARM_CPU::PC] = (addr&~1)+4;
      proc.cpu.set_thumb_mode();
    }
  } else
    proc.cpu.regs[ARM_CPU::PC] += 4;
}

ostream& ARM_bx::display(ostream& os) const {
  return os <<"BX" <<cond <<'\t' <<(ARM_AsmId) Rm;
}

/******************************************************************************/

void ARM_blx::exec(ARM_Processor &proc) {
  proc.cpu.regs[ARM_CPU::LR] = proc.cpu.regs[ARM_CPU::PC]-4;
  proc.cpu.regs[ARM_CPU::PC] += offset;
  proc.cpu.set_thumb_mode();
}

ostream& ARM_blx::display(ostream& os) const {
  int32_t o = offset-8;
  return os <<"BLX" <<hex <<"\tpc"
            <<(o>=0?'+':'-')
            <<(o>=0? o: -o);
}

/******************************************************************************/

void ARM_blx2::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    proc.cpu.regs[ARM_CPU::LR] = proc.cpu.regs[ARM_CPU::PC] - 4;
    uint32_t addr = proc.cpu.regs[Rm];
    switch (addr&3) {
    case 0: // 00
      proc.cpu.regs[ARM_CPU::PC] = addr+8; break;
    case 2: // 10
      proc.error() <<"unpredictable branching to a non-aligned address" <<endl;
      exit(5);
    case 1: // 01
    case 3: // 11
      proc.cpu.regs[ARM_CPU::PC] = addr&~1;
      proc.cpu.set_thumb_mode();
    }
  } else
    proc.cpu.regs[ARM_CPU::PC] += 4;
}

ostream& ARM_blx2::display(ostream& os) const {
  return os <<"BLX" <<cond <<'\t' <<(ARM_AsmId) Rm;
}

/******************************************************************************/

void ARM_bkpt::exec(ARM_Processor &proc) {
  if (proc.debugger())
    proc.debugger()->notify(Debugger::EV_TRAP);
  else
    TODO("raise the right exception (prefetch)");
}

ostream& ARM_bkpt::display(ostream& os) const {
  return os << "BKPT\t" << hex << immed << dec;
}

/******************************************************************************/

void ARM_mrs::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    const ARM_StatusRegister &psr = R? proc.cpu.spsr(): proc.cpu.cpsr;
    proc.cpu.regs[Rd] = psr.binary_encoding();
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

ostream& ARM_mrs::display(ostream& os) const {
  return os <<"MRS" <<cond <<'\t' <<(ARM_AsmId) Rd <<(R? ", SPSR": ", CPSR");
}

/******************************************************************************/

void ARM_msr_imm::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    if (R) {
      if (fields&1) {
        proc.cpu.spsr().mode = arm_mode(immed&0x1f);
        proc.cpu.spsr().t = immed&(1<<5);
        proc.cpu.spsr().f = immed&(1<<6);
        proc.cpu.spsr().i = immed&(1<<7);
      }
      if (fields&(1<<3)) {
        proc.cpu.spsr().q = immed&(1<<27);
        proc.cpu.spsr().v = immed&(1<<28);
        proc.cpu.spsr().c = immed&(1<<29);
        proc.cpu.spsr().z = immed&(1<<30);
        proc.cpu.spsr().n = immed&(1<<31);
      }
    } else {
      if (proc.cpu.cpsr.mode==ARM_USER)
        fields &= ~1;
      if (fields&1 && (proc.cpu.cpsr.t!=immed&(1<<5))) {
        proc.error() <<"attempt to alter the T bit using MSR" <<std::endl;
        exit(1);
      }
      proc.set_cpsr(immed,fields);
    }
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

ostream& ARM_msr_imm::display(ostream& os) const {
  return os <<"MSR" <<cond <<'\t' <<(R? "SPSR_": "CPSR_")
            <<((fields&1)? "c":"")
            <<((fields&2)? "x":"")
            <<((fields&4)? "s":"")
            <<((fields&8)? "f":"")
            <<", #" <<hex <<immed;
}

/******************************************************************************/

void ARM_msr_reg::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t value = proc.cpu.regs[Rm];
    if (R) {
      if (fields&1) {
        proc.cpu.spsr().mode = arm_mode(value&0x1f);
        proc.cpu.spsr().t = value&(1<<5);
        proc.cpu.spsr().f = value&(1<<6);
        proc.cpu.spsr().i = value&(1<<7);
      }
      if (fields&(1<<3)) {
        proc.cpu.spsr().q = value&(1<<27);
        proc.cpu.spsr().v = value&(1<<28);
        proc.cpu.spsr().c = value&(1<<29);
        proc.cpu.spsr().z = value&(1<<30);
        proc.cpu.spsr().n = value&(1<<31);
      }
    } else {
      if (proc.cpu.cpsr.mode==ARM_USER)
        fields &= ~1;
      if (fields&1 && (proc.cpu.cpsr.t!=value&(1<<5))) {
        proc.error() <<"attempt to alter the T bit using MSR" <<std::endl;
        exit(1);
      }
      proc.set_cpsr(value,fields);
    }
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

ostream& ARM_msr_reg::display(ostream& os) const {
  return os <<"MSR" <<cond <<'\t' <<(R? "SPSR_": "CPSR_")
            <<((fields&1)? "c":"")
            <<((fields&2)? "x":"")
            <<((fields&4)? "s":"")
            <<((fields&8)? "f":"")
            <<", " <<(ARM_AsmId) Rm;
}

/******************************************************************************/

void ARM_swi::exec(ARM_Processor &proc) {
 if (conditionPassed(proc.cpu.cpsr,cond)) {
   proc.software_interrupt();
 } else
   proc.cpu.regs[ARM_CPU::PC] += 4;
}

ostream& ARM_swi::display(ostream& os) const {
  return os <<"SWI" <<cond <<"\t" <<hex <<immed;
}

/******************************************************************************/

} // namespace simsoc
