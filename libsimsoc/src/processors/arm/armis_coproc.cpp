//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "armis_coproc.hpp"
#include "libsimsoc/processors/arm/arm_processor.hpp"
#include "libsimsoc/processors/arm/arm_coproc.hpp"
#include "libsimsoc/display.hpp"

using namespace std;

namespace simsoc {

const char * OP4[16] =
  {"0b0000", "0b0001", "0b0010", "0b0011", "0b0100", "0b0101", "0b0110", "0b0111",
   "0b1000", "0b1001", "0b1010", "0b1011", "0b1100", "0b1101", "0b1110", "0b1111"};
const char * OP3[8] =
  {"0b000", "0b001", "0b010", "0b011", "0b100", "0b101", "0b110", "0b111"};
const char * OP3F[8] =
  {"", ", 0b001", ", 0b010", ", 0b011", ", 0b100", ", 0b101", ", 0b110", ", 0b111"};

/******************************************************************************/

void ARM_cdp::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond))
    proc.coprocessors[coproc]->cdp(opcode1,opcode2,CRd,CRn,CRm);
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

ostream& ARM_cdp::display(ostream& os) const {
  return os <<"CDP" <<cond <<"\tp" <<dec <<(int) coproc <<", " <<OP4[opcode1]
            <<", c" <<(int) CRd <<", c"  <<(int) CRn <<", c" <<(int) CRm
            <<OP3F[opcode2];
}

void ARM_cdp2::exec(ARM_Processor &proc) {
  proc.coprocessors[coproc]->cdp2(opcode1,opcode2,CRd,CRn,CRm);
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

ostream& ARM_cdp2::display(ostream& os) const {
  return os <<"CDP2\tp" <<dec <<(int) coproc <<", " <<OP4[opcode1]
            <<", c" <<(int) CRd <<", c"  <<(int) CRn <<", c" <<(int) CRm
            <<OP3F[opcode2];
}

/******************************************************************************/

void ARM_ldc::exec(ARM_Processor &proc) {
  TODO("LDC instruction");
}

ostream& ARM_ldc::display(ostream& os) const {
  return os <<"LDC" <<cond <<(l? "L":"") <<"\tp" <<dec <<(int) coproc <<", CR" <<(int) CRd
            <<", ...";
}

void ARM_ldc2::exec(ARM_Processor &proc) {
  TODO("LDC2 instruction");
}

ostream& ARM_ldc2::display(ostream& os) const {
  return os <<"LDC2" <<(l? "L":"") <<"\tp" <<dec <<(int) coproc <<", CR" <<(int) CRd
            <<", ...";
}

/******************************************************************************/

void ARM_stc::exec(ARM_Processor &proc) {
  TODO("STC instruction");
}

ostream& ARM_stc::display(ostream& os) const {
  return os <<"STC" <<cond <<(l? "L":"") <<"\tp" <<dec <<(int) coproc <<", CR" <<(int) CRd
            <<", ...";
}

void ARM_stc2::exec(ARM_Processor &proc) {
  TODO("STC2 instruction");
}

ostream& ARM_stc2::display(ostream& os) const {
  return os <<"STC2" <<(l? "L":"") <<"\tp" <<dec <<(int) coproc <<", CR" <<(int) CRd
            <<", ...";
}

/******************************************************************************/

void ARM_mcr::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond))
    proc.coprocessors[coproc]->mcr(opcode1,opcode2,proc.cpu.regs[Rd],CRn,CRm);
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

ostream& ARM_mcr::display(ostream& os) const {
  return os <<"MCR" <<cond  <<"\tp" <<dec <<(int) coproc <<", " <<OP3[opcode1]
            <<", " <<(ARM_AsmId) Rd <<", c"  <<(int) CRn <<", c" <<(int) CRm
            <<OP3F[opcode2];
}

void ARM_mcr2::exec(ARM_Processor &proc) {
  proc.coprocessors[coproc]->mcr2(opcode1,opcode2,proc.cpu.regs[Rd],CRn,CRm);
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

ostream& ARM_mcr2::display(ostream& os) const {
  return os <<"MCR2\tp" <<dec <<(int) coproc <<", " <<OP3[opcode1]
            <<", " <<(ARM_AsmId) Rd <<", c"  <<(int) CRn <<", c" <<(int) CRm
            <<OP3F[opcode2];
}

/******************************************************************************/

void ARM_mrc::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    uint32_t data = proc.coprocessors[coproc]->mrc(opcode1,opcode2,CRn,CRm);
    if (Rd==ARM_CPU::PC) {
      proc.cpu.cpsr.n = data&(1<<31);
      proc.cpu.cpsr.z = data&(1<<30);
      proc.cpu.cpsr.c = data&(1<<29);
      proc.cpu.cpsr.v = data&(1<<28);
    } else
      proc.cpu.regs[Rd] = data;
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

ostream& ARM_mrc::display(ostream& os) const {
  return os <<"MRC" <<cond  <<"\tp" <<dec <<(int) coproc <<", " <<OP3[opcode1]
            <<", " <<(ARM_AsmId) Rd <<", c"  <<(int) CRn <<", c" <<(int) CRm
            <<OP3F[opcode2];
}

void ARM_mrc2::exec(ARM_Processor &proc) {
  uint32_t data = proc.coprocessors[coproc]->mrc2(opcode1,opcode2,CRn,CRm);
  if (Rd==ARM_CPU::PC) {
    proc.cpu.cpsr.n = data&(1<<31);
    proc.cpu.cpsr.z = data&(1<<30);
    proc.cpu.cpsr.c = data&(1<<29);
    proc.cpu.cpsr.v = data&(1<<28);
  } else
    proc.cpu.regs[Rd] = data;
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

ostream& ARM_mrc2::display(ostream& os) const {
  return os <<"MRC2\tp" <<dec <<(int) coproc <<", " <<OP3[opcode1]
            <<", " <<(ARM_AsmId) Rd <<", c"  <<(int) CRn <<", c" <<(int) CRm
            <<OP3F[opcode2];
}

} // namespace simsoc
