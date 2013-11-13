//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "thumbis_arithmetic.hpp"
#include "libsimsoc/processors/arm/arm_cpu.hpp"
#include "libsimsoc/processors/arm/arm_shift.hpp"
#include "libsimsoc/processors/arm/arm_processor.hpp"
#include "libsimsoc/processors/arm/arm_thumb_pi.hpp"

namespace simsoc {

/***********************************************************************************/

THUMB_adc::THUMB_adc( uint8_t d, uint8_t m):
  THUMB_Instruction(), Rd(d), Rm(m) {}

void THUMB_adc::exec(ARM_Processor &proc){
  const uint32_t a = proc.cpu.regs[Rd];
  const uint32_t b = proc.cpu.regs[Rm];
  const uint32_t c = static_cast<uint32_t>(proc.cpu.cpsr.c);
  const uint32_t r = a+b+c;
  proc.cpu.regs[Rd] = r;
  proc.cpu.cpsr.n = r&(1<<31);
  proc.cpu.cpsr.z = r==0;
  proc.cpu.cpsr.c = r<b+c || b+c<c;
  proc.cpu.cpsr.v = ((b^~a)&(b^r))>>31;
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_adc::display(std::ostream& os) const {
  return os <<"adc\t" <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rm;
}

/**********************************************************************************/

THUMB_mov2::THUMB_mov2(uint8_t d,uint8_t n):
  THUMB_Instruction(), Rd(d), Rn(n) {}

void THUMB_mov2::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rn];
  proc.cpu.regs[Rd] = a;
  proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
  proc.cpu.cpsr.c = 0;
  proc.cpu.cpsr.v = 0;
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_mov2::display(std::ostream& os) const {
  return os <<"mov\t" <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rn;
}

/**********************************************************************************/

THUMB_add1::THUMB_add1(uint8_t i,uint8_t d,uint8_t n):
  THUMB_Instruction(),immed(i), Rd(d), Rn(n) {}

void THUMB_add1::exec(ARM_Processor &proc){
  uint8_t a = immed;
  uint32_t b = proc.cpu.regs[Rn];
  proc.cpu.regs[Rd] = a+b;
  proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
  proc.cpu.cpsr.c = proc.cpu.regs[Rd]<b;
  proc.cpu.cpsr.v = ((b^~a)&(b^proc.cpu.regs[Rd]))>>31;
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_add1::display(std::ostream& os) const {
  return os <<"add\t" <<(ARM_AsmId) Rd  <<", " <<(ARM_AsmId) Rn <<", " <<"#" <<(int) immed;
}

/**********************************************************************************/

THUMB_add2::THUMB_add2(uint8_t i,uint8_t d):
  THUMB_Instruction(),immed(i), Rd(d) {}

void THUMB_add2::exec(ARM_Processor &proc){
  uint32_t a = immed;
  uint32_t b = proc.cpu.regs[Rd];
  proc.cpu.regs[Rd] = a+b;
  proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
  proc.cpu.cpsr.c = proc.cpu.regs[Rd]<b;
  proc.cpu.cpsr.v = ((b^~a)&(b^proc.cpu.regs[Rd]))>>31;
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_add2::display(std::ostream& os) const {
  return os <<"add\t" <<(ARM_AsmId) Rd  <<", " <<"#" <<(int) immed;
}

/**********************************************************************************/

THUMB_add3::THUMB_add3(uint8_t m,uint8_t d,uint8_t n):
  THUMB_Instruction(), Rm(m), Rd(d), Rn(n) {}

void THUMB_add3::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rm];
  uint32_t b = proc.cpu.regs[Rn];
  proc.cpu.regs[Rd] = a+b;
  proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
  proc.cpu.cpsr.c = proc.cpu.regs[Rd]<b;
  proc.cpu.cpsr.v = ((b^~a)&(b^proc.cpu.regs[Rd]))>>31;
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_add3::display(std::ostream& os) const {
  return os <<"add\t" <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rn <<", " <<(ARM_AsmId) Rm;
}

/**********************************************************************************/

THUMB_add4::THUMB_add4( uint8_t d, uint8_t m):
  THUMB_Instruction(), Rd(d), Rm(m) {}

void THUMB_add4::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rd];
  uint32_t b = proc.cpu.regs[Rm];
  if (Rd==ARM_CPU::PC) {
    proc.cpu.regs[ARM_CPU::PC] = a+b+4;
  } else {
    proc.cpu.regs[Rd] = a+b;
    proc.cpu.regs[ARM_CPU::PC] += 2;
  }
}
std::ostream& THUMB_add4::display(std::ostream& os) const {
  return os <<"add\t" <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rm;
}


/***********************************************************************************/

THUMB_add5::THUMB_add5(uint8_t i,uint8_t d):
  THUMB_Instruction(),immed(i), Rd(d) {}

void THUMB_add5::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[ARM_CPU::PC];
    proc.cpu.regs[Rd] = (a&0xFFFFFFFC) + (immed<<2);
    proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_add5::display(std::ostream& os) const {
  return os <<"add\t" <<(ARM_AsmId) Rd  <<", pc, #" <<(int) immed*4;
}

/**********************************************************************************/

THUMB_add6::THUMB_add6( uint8_t i, uint8_t d):
  THUMB_Instruction(), immed(i), Rd(d) {}

void THUMB_add6::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[ARM_CPU::SP];
  proc.cpu.regs[Rd] = a + (immed<<2);
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_add6::display(std::ostream& os) const {
  return os <<"add\t" <<(ARM_AsmId) Rd  <<", sp, #" <<(int) immed*4;
}

/**********************************************************************************/

THUMB_add7::THUMB_add7( uint8_t i):
  THUMB_Instruction(),immed(i) {}

void THUMB_add7::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[ARM_CPU::SP];
  proc.cpu.regs[ARM_CPU::SP] = a + (immed<<2);
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_add7::display(std::ostream& os) const {
  return os <<"add\t"  <<" sp, #" <<(int) immed*4;
}

/***********************************************************************************/

THUMB_and::THUMB_and(uint8_t m, uint8_t d):
  THUMB_Instruction(), Rd(d), Rm(m) {}

void THUMB_and::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rd];
  uint32_t b = proc.cpu.regs[Rm];
  proc.cpu.regs[Rd] = a&b;
  proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_and::display(std::ostream& os) const {
  return os <<"and\t" <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rm;
}

/**********************************************************************************/

THUMB_asr1::THUMB_asr1( uint8_t i, uint8_t d, uint8_t m):
  THUMB_Instruction(), immed(i?i:32), Rd(d), Rm(m) {}

void THUMB_asr1::exec(ARM_Processor &proc) {
  uint32_t value = proc.cpu.regs[Rm];
  proc.cpu.cpsr.c = value&(1<<(immed-1));
  if (immed==32)
    proc.cpu.regs[Rd] = proc.cpu.cpsr.c? ~0: 0;
  else
    proc.cpu.regs[Rd] = (int32_t) value >>immed;
  proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_asr1::display(std::ostream& os) const {
  return os <<"asr\t" <<(ARM_AsmId) Rd  <<", " <<(ARM_AsmId) Rm <<", #" <<(int) immed;
}

/**********************************************************************************/

THUMB_asr2::THUMB_asr2( uint8_t s, uint8_t d):
  THUMB_Instruction(), Rs(s), Rd(d) {}

void THUMB_asr2::exec(ARM_Processor &proc){
  uint8_t shift = proc.cpu.regs[Rs];
  uint32_t value = proc.cpu.regs[Rd];
  if (shift>=32) {
    proc.cpu.cpsr.c = value&(1<<31);
    proc.cpu.regs[Rd] = proc.cpu.cpsr.c? ~0: 0;
  } else if (shift>0) {
    proc.cpu.cpsr.c = value&(1<<(shift-1));
    proc.cpu.regs[Rd] = (int32_t) value >>shift;
  }
  proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_asr2::display(std::ostream& os) const {
  return os <<"asr\t" <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rs;
}

/**********************************************************************************/

THUMB_bic::THUMB_bic( uint8_t m, uint8_t d):
  THUMB_Instruction(), Rm(m), Rd(d) {}

void THUMB_bic::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rd];
  uint32_t b = proc.cpu.regs[Rm];
  proc.cpu.regs[Rd] = a&~b;
  proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_bic::display(std::ostream& os) const {
  return os <<"bic\t" <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rm;
}

/**********************************************************************************/

THUMB_cmn::THUMB_cmn(uint8_t m,uint8_t n):
  THUMB_Instruction(), Rm(m), Rn(n) {}

void THUMB_cmn::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rn];
  uint32_t b = proc.cpu.regs[Rm];
  uint32_t alu_out = a+b;
  proc.cpu.cpsr.n = alu_out&(1<<31);
  proc.cpu.cpsr.z = !alu_out;
  proc.cpu.cpsr.c = alu_out<b;
  proc.cpu.cpsr.v = ((b^~a)&(b^alu_out))>>31;
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_cmn::display(std::ostream& os) const {
  return os <<"cmn\t" <<(ARM_AsmId) Rn <<", " <<(ARM_AsmId) Rm;
}

/***********************************************************************************/

THUMB_cmp1::THUMB_cmp1( uint8_t i, uint8_t n):
  THUMB_Instruction(), immed(i), Rn(n) {}

void THUMB_cmp1::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rn];
  uint32_t b = immed;
  uint32_t alu_out = a-b;
  proc.cpu.cpsr.n = alu_out&(1<<31);
  proc.cpu.cpsr.z = !alu_out;
  proc.cpu.cpsr.c = a>=b;
  proc.cpu.cpsr.v = ((a^b)&(a^alu_out))>>31;
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_cmp1::display(std::ostream& os) const {
  return os <<"cmp\t" <<(ARM_AsmId) Rn <<", #" <<(int) immed;
}

/**********************************************************************************/

THUMB_cmp2::THUMB_cmp2(uint8_t m,uint8_t n):
  THUMB_Instruction(), Rm(m), Rn(n) {}

void THUMB_cmp2::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rn];
  uint32_t b = proc.cpu.regs[Rm];
  uint32_t alu_out = a-b;
  proc.cpu.cpsr.n = alu_out&(1<<31);
  proc.cpu.cpsr.z = !alu_out;
  proc.cpu.cpsr.c = a>=b;
  proc.cpu.cpsr.v = ((a^b)&(a^alu_out))>>31;
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_cmp2::display(std::ostream& os) const {
  return os <<"cmp\t" <<(ARM_AsmId) Rn <<", " <<(ARM_AsmId) Rm;
}

/***********************************************************************************/

THUMB_cmp3::THUMB_cmp3( uint8_t m, uint8_t n):
  THUMB_Instruction(), Rm(m), Rn(n) {}

void THUMB_cmp3::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rn];
  uint32_t b = proc.cpu.regs[Rm];
  uint32_t alu_out = a-b;
  proc.cpu.cpsr.n = alu_out&(1<<31);
  proc.cpu.cpsr.z = !alu_out;
  proc.cpu.cpsr.c = a>=b;
  proc.cpu.cpsr.v = ((a^b)&(a^alu_out))>>31;
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_cmp3::display(std::ostream& os) const {
  return os <<"cmp\t" <<(ARM_AsmId) Rn <<", " <<(ARM_AsmId) Rm;
}

/***********************************************************************************/

THUMB_eor::THUMB_eor( uint8_t m, uint8_t d):
  THUMB_Instruction(), Rm(m), Rd(d) {}

void THUMB_eor::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rd];
  uint32_t b = proc.cpu.regs[Rm];
  proc.cpu.regs[Rd] = a^b;
  proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_eor::display(std::ostream& os) const {
  return os <<"eor\t" <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rm;
}

/**********************************************************************************/

THUMB_lsl1::THUMB_lsl1( uint8_t i, uint8_t m, uint8_t d):
  THUMB_Instruction(),immed(i), Rm(m), Rd(d) {}

void THUMB_lsl1::exec(ARM_Processor &proc){
  uint32_t value = proc.cpu.regs[Rm];
  if (immed==0)
    proc.cpu.regs[Rd] = value;
  else {
    proc.cpu.cpsr.c = value&(1<<(32-immed));
    proc.cpu.regs[Rd] = value<<immed;
  }
  proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_lsl1::display(std::ostream& os) const {
  return os <<"lsl\t" <<(ARM_AsmId) Rd  <<", " <<(ARM_AsmId) Rm <<", #" <<(int) immed;
}

/**********************************************************************************/

THUMB_lsl2::THUMB_lsl2( uint8_t s, uint8_t d):
  THUMB_Instruction(), Rs(s), Rd(d) {}

void THUMB_lsl2::exec(ARM_Processor &proc){
  uint8_t shift = proc.cpu.regs[Rs];
  uint32_t value = proc.cpu.regs[Rd];
  if (shift>=32) {
    proc.cpu.regs[Rd] = 0;
    proc.cpu.cpsr.c = (shift==32)? value&1: 0;
  } else if (shift>0) {
    proc.cpu.regs[Rd] = value<<shift;
    proc.cpu.cpsr.c = value&(1<<(32-shift));
  }
  proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_lsl2::display(std::ostream& os) const {
  return os <<"lsl\t" <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rs;
}

/**********************************************************************************/

THUMB_lsr1::THUMB_lsr1( uint8_t i, uint8_t m, uint8_t d):
  THUMB_Instruction(), immed(i?i:32), Rm(m), Rd(d) {}

void THUMB_lsr1::exec(ARM_Processor &proc){
  uint32_t value = proc.cpu.regs[Rm];
  if (immed==32) {
    proc.cpu.cpsr.c = proc.cpu.regs[Rd]&(1<<31);
    proc.cpu.regs[Rd] = 0;
  } else {
    proc.cpu.cpsr.c = value&(1<<(immed-1));
    proc.cpu.regs[Rd] = value>>immed;
  }
  proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_lsr1::display(std::ostream& os) const {
  return os <<"lsr\t" <<(ARM_AsmId) Rd  <<", " <<(ARM_AsmId) Rm <<", #" <<(int) immed;
}
/**********************************************************************************/

THUMB_lsr2::THUMB_lsr2( uint8_t s, uint8_t d):
  THUMB_Instruction(), Rs(s), Rd(d) {}

void THUMB_lsr2::exec(ARM_Processor &proc){
  uint8_t shift = proc.cpu.regs[Rs];
  uint32_t value = proc.cpu.regs[Rd];
  if (shift>32) {
    proc.cpu.cpsr.c = 0;
    proc.cpu.regs[Rd] = 0;
  } else if (shift==32){
    proc.cpu.cpsr.c = value&(1<<31);
    proc.cpu.regs[Rd] = 0;
  } else if (shift>0) {
    proc.cpu.cpsr.c = value&(1<<(shift-1));
    proc.cpu.regs[Rd] = value>>shift;
  }
  proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_lsr2::display(std::ostream& os) const {
  return os <<"lsr\t" <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rs;
}

/***********************************************************************************/

THUMB_mov1::THUMB_mov1( uint8_t d, uint8_t i):
  THUMB_Instruction(), Rd(d), immed(i) {}

void THUMB_mov1::exec(ARM_Processor &proc){
  uint32_t a = immed;
  proc.cpu.regs[Rd] = a;
  proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_mov1::display(std::ostream& os) const {
  return os <<"mov\t" <<(ARM_AsmId) Rd  <<", " <<"#" <<(int) immed;
}

/***********************************************************************************/

THUMB_mov3::THUMB_mov3( uint8_t m, uint8_t d):
  THUMB_Instruction(), Rm(m), Rd(d) {}

void THUMB_mov3::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rm];
  if (Rd==ARM_CPU::PC) {
    proc.cpu.regs[ARM_CPU::PC] = a+4;
  } else {
    proc.cpu.regs[Rd] = a;
    proc.cpu.regs[ARM_CPU::PC] += 2;
  }
}

std::ostream& THUMB_mov3::display(std::ostream& os) const {
  return os <<"mov\t" <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rm;
}

/***********************************************************************************/

THUMB_mul::THUMB_mul( uint8_t m, uint8_t d):
  THUMB_Instruction(), Rm(m), Rd(d) {}

void THUMB_mul::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rm];
  uint32_t b = proc.cpu.regs[Rd];
  proc.cpu.regs[Rd] = (a*b)&0xFFFFFFFF;
  proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_mul::display(std::ostream& os) const {
  return os <<"mul\t" <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rm;
}

/***********************************************************************************/

THUMB_mvn::THUMB_mvn( uint8_t m, uint8_t d):
  THUMB_Instruction(), Rm(m), Rd(d) {}

void THUMB_mvn::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rm];
  proc.cpu.regs[Rd] = ~a;
  proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_mvn::display(std::ostream& os) const {
  return os <<"mvn\t" <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rm;
}

/***********************************************************************************/

THUMB_neg::THUMB_neg( uint8_t m, uint8_t d):
  THUMB_Instruction(), Rm(m), Rd(d) {}

void THUMB_neg::exec(ARM_Processor &proc){
  uint32_t b = proc.cpu.regs[Rm];
  proc.cpu.regs[Rd] = 0-b;
  proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
  proc.cpu.cpsr.c = 0>=b;
  proc.cpu.cpsr.v = ((b^0)&(0^proc.cpu.regs[Rd]))>>31;
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_neg::display(std::ostream& os) const {
  return os <<"neg\t" <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rm;
}

/***********************************************************************************/

THUMB_orr::THUMB_orr( uint8_t m, uint8_t d):
  THUMB_Instruction(), Rm(m), Rd(d) {}

void THUMB_orr::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rm];
  uint32_t b = proc.cpu.regs[Rd];
  proc.cpu.regs[Rd] = a|b;
  proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_orr::display(std::ostream& os) const {
  return os <<"orr\t" <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rm;
}

/***********************************************************************************/

THUMB_ror::THUMB_ror( uint8_t s, uint8_t d):
  THUMB_Instruction(), Rs(s), Rd(d) {}

void THUMB_ror::exec(ARM_Processor &proc){
  uint8_t a = proc.cpu.regs[Rs];
  uint32_t b = proc.cpu.regs[Rd];
  if((a&0x1F) == 0)
    proc.cpu.cpsr.c = b&(1<<31);
  else if (a==0) {
    proc.cpu.cpsr.c = proc.cpu.cpsr.c;
    proc.cpu.regs[Rd] = b;
  } else if ((a&0x1F)>0) {
    proc.cpu.cpsr.c = b&(1<<((a&0x1F)-1));
    proc.cpu.regs[Rd] = valueROR(b,a&0x1F);
  }
  proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_ror::display(std::ostream& os) const {
  return os <<"ror\t" <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rs;
}

/***********************************************************************************/

THUMB_sbc::THUMB_sbc( uint8_t m, uint8_t d):
  THUMB_Instruction(), Rm(m), Rd(d) {}

void THUMB_sbc::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rd];
  uint32_t b = proc.cpu.regs[Rm];
  proc.cpu.regs[Rd] = a-b-!proc.cpu.cpsr.c;
  proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
  proc.cpu.cpsr.c = a>=b && a-b>=(proc.cpu.cpsr.c? 0: 1);
  proc.cpu.cpsr.v = ((b^a)&(a^proc.cpu.regs[Rd]))>>31;
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_sbc::display(std::ostream& os) const {
  return os <<"sbc\t" <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rm;
}

/**********************************************************************************/

THUMB_sub1::THUMB_sub1(uint8_t i,uint8_t d,uint8_t n):
  THUMB_Instruction(),immed(i), Rd(d), Rn(n) {}

void THUMB_sub1::exec(ARM_Processor &proc){
  uint8_t a = immed;
  uint32_t b = proc.cpu.regs[Rn];
  proc.cpu.regs[Rd] = b-a;
  proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
  proc.cpu.cpsr.c = b>=a;
  proc.cpu.cpsr.v = ((a^b)&(b^proc.cpu.regs[Rd]))>>31;
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_sub1::display(std::ostream& os) const {
  return os <<"sub\t" <<(ARM_AsmId) Rd  <<", " <<(ARM_AsmId) Rn <<", " <<"#" <<(int) immed;
}

/***********************************************************************************/

THUMB_sub2::THUMB_sub2(uint8_t i,uint8_t d):
  THUMB_Instruction(),immed(i), Rd(d) {}

void THUMB_sub2::exec(ARM_Processor &proc){
  uint32_t a = immed;
  uint32_t b = proc.cpu.regs[Rd];
  proc.cpu.regs[Rd] = b-a;
  proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
  proc.cpu.cpsr.c = b>=a;
  proc.cpu.cpsr.v = ((b^a)&(b^proc.cpu.regs[Rd]))>>31;
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_sub2::display(std::ostream& os) const {
  return os <<"sub\t" <<(ARM_AsmId) Rd  <<", " <<"#" <<(int) immed;
}

/**********************************************************************************/

THUMB_sub3::THUMB_sub3(uint8_t m,uint8_t d,uint8_t n):
  THUMB_Instruction(), Rm(m), Rd(d), Rn(n) {}

void THUMB_sub3::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rm];
  uint32_t b = proc.cpu.regs[Rn];
  proc.cpu.regs[Rd] = b-a;
  proc.cpu.cpsr.n = proc.cpu.regs[Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[Rd];
  proc.cpu.cpsr.c = b>=a;
  proc.cpu.cpsr.v = ((b^a)&(b^proc.cpu.regs[Rd]))>>31;
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_sub3::display(std::ostream& os) const {
  return os <<"sub\t" <<(ARM_AsmId) Rd <<", " <<(ARM_AsmId) Rn <<", " <<(ARM_AsmId) Rm;
}

/***********************************************************************************/

THUMB_sub4::THUMB_sub4(uint8_t i):
 THUMB_Instruction(),immed(i) {}

void THUMB_sub4::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[ARM_CPU::SP];
  proc.cpu.regs[ARM_CPU::SP] = a - (immed<<2);
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_sub4::display(std::ostream& os) const {
  return os <<"sub\t"  <<" sp, #" <<(int) immed*4;
}

/***********************************************************************************/

THUMB_tst::THUMB_tst(uint8_t m,uint8_t n):
  THUMB_Instruction(), Rm(m), Rn(n) {}

void THUMB_tst::exec(ARM_Processor &proc){
  uint32_t a = proc.cpu.regs[Rn];
  uint32_t b = proc.cpu.regs[Rm];
  uint32_t alu_out = a&b;
  proc.cpu.cpsr.n = alu_out&(1<<31);
  proc.cpu.cpsr.z = !alu_out;
  proc.cpu.regs[ARM_CPU::PC] += 2;
}

std::ostream& THUMB_tst::display(std::ostream& os) const {
  return os <<"tst\t" <<(ARM_AsmId) Rn <<", " <<(ARM_AsmId) Rm;
}

} // namespace simsoc
