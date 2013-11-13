//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "armis_arithmetic.hpp"
#include "libsimsoc/bitwise_operator.hpp"

namespace simsoc {

ARM_DPI_ShiftImm::ARM_DPI_ShiftImm(ARM_Condition c,
                                   uint8_t sa, uint8_t z, uint8_t m):
  ARM32_Instruction(), cond(c),
  shift_amount((!sa && (z==LSR||z==ASR))? 32: sa),
  shift(((ARM_Shift) z==ROR && sa==0)? RRX: (ARM_Shift) z),
  Rm(m) {}

ARM_DPI_ShiftReg::ARM_DPI_ShiftReg(ARM_Condition c,
                                   uint8_t sa, uint8_t z, uint8_t m):
  ARM32_Instruction(), cond(c),
  Rs(sa), shift((ARM_Shift) z), Rm(m) {}

ARM_DPI_Imm::ARM_DPI_Imm(ARM_Condition c,
                         uint8_t ra, uint8_t i):
  ARM32_Instruction(), cond(c),
  rotate_amount(ra*2), immed(i) {}

/******************************************************************************/

void ARM_clz::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    const uint32_t m = proc.cpu.regs[Rm];
    proc.cpu.regs[Rd] = 32-fls(m);
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

std::ostream& ARM_clz::display(std::ostream& os) const {
  return os <<"CLZ" <<cond <<'\t' <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rm;
}

/******************************************************************************/
ARM_mla::ARM_mla(ARM_Condition c, bool s_, uint8_t d, uint8_t m, uint8_t rs, uint8_t n):
  ARM32_Instruction(), cond(c), s(s_), Rd(d), Rm(m), Rs(rs), Rn(n) {}

void ARM_mla::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    proc.cpu.regs[Rd] = proc.cpu.regs[Rs]*proc.cpu.regs[Rm]+proc.cpu.regs[Rn];
    if (s) {
      proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
      proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
    }
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

std::ostream& ARM_mla::display(std::ostream& os) const {
  return os <<"MLA" <<cond <<(s? "S":"") <<'\t' <<(ARM_AsmId) Rd <<", "
            <<(ARM_AsmId) Rm <<", " <<(ARM_AsmId) Rs <<", " <<(ARM_AsmId) Rn;
}

/******************************************************************************/

ARM_mul::ARM_mul(ARM_Condition c, bool s_, uint8_t d, uint8_t m, uint8_t rs):
  ARM32_Instruction(), cond(c), s(s_), Rd(d), Rm(m), Rs(rs) {}

void ARM_mul::exec(ARM_Processor &proc) {
  if (conditionPassed(proc.cpu.cpsr,cond)) {
    proc.cpu.regs[Rd] = proc.cpu.regs[Rs]*proc.cpu.regs[Rm];
    if (s) {
      proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
      proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
    }
  }
  proc.cpu.regs[ARM_CPU::PC] += 4;
}

std::ostream& ARM_mul::display(std::ostream& os) const {
  return os <<"MUL" <<cond <<(s? "S":"") <<'\t' <<(ARM_AsmId) Rd <<", "
            <<(ARM_AsmId) Rm <<", " <<(ARM_AsmId) Rs;
}

/******************************************************************************/

void ARM_smlal::compute(uint32_t & RdHi, uint32_t & RdLo, uint32_t Rm, uint32_t Rs) {
//  TODO("SMLAL instruction");
	int64_t r =(int64_t)(int32_t)RdHi;
	r = r<<32;
	r = (int64_t)(int32_t)Rm * (int64_t)(int32_t)Rs + r + (int64_t)(int32_t)RdLo;
	RdLo = r;
	RdHi = r>>32;
}

void ARM_smull::compute(uint32_t & RdHi, uint32_t & RdLo, uint32_t Rm, uint32_t Rs) {
  int64_t r = (int64_t)(int32_t)Rm * (int64_t)(int32_t)Rs;
  RdHi = r>>32;
  RdLo = r;
}

void ARM_umlal::compute(uint32_t & RdHi, uint32_t & RdLo, uint32_t Rm, uint32_t Rs) {
//  TODO("UMLAL instruction");
	uint64_t r = RdHi;
	r = r<<32;
	r = (uint64_t) Rm * (uint64_t) Rs + r + RdLo;
	RdHi = (uint32_t)(r >> 32);
	RdLo = (uint32_t) r;
}

void ARM_umull::compute(uint32_t & RdHi, uint32_t & RdLo, uint32_t Rm, uint32_t Rs) {
  uint64_t r = (uint64_t) Rm * (uint64_t) Rs;
  RdHi = (uint32_t) (r>>32);
  RdLo = (uint32_t) r;
}

} // namespace simsoc
