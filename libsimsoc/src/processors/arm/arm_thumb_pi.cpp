//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "arm_thumb_pi.hpp"
#include <assert.h>
#include "libsimsoc/processors/arm/armis.hpp"
#include "libsimsoc/bitwise_operator.hpp"
#include "libsimsoc/processors/arm/arm_processor.hpp"
#include "libsimsoc/display.hpp"
#include "libsimsoc/processors/arm/arm_shift.hpp"

using namespace std;

namespace simsoc {

PseudoStatus thumb_pi_nop(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  return OK;
}

/*********************************************************************************/
PseudoStatus thumbdpi_adc(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_adc" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rd] ;
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rm];
  const uint32_t c = static_cast<uint32_t>(proc.cpu.cpsr.c);
  const uint32_t r = a+b+c;
  proc.cpu.regs[p.args.any_reg.Rd] = r;
  proc.cpu.cpsr.n = r&(1<<31);
  proc.cpu.cpsr.z = r==0;
  proc.cpu.cpsr.c = r<b+c || b+c<c;
  proc.cpu.cpsr.v = ((b^~a)&(b^r))>>31;
  return OK;
}


PseudoStatus thumbdpi_mov2(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_mov2" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rn];
  proc.cpu.regs[p.args.any_reg.Rd] = a;
  proc.cpu.cpsr.n = proc.cpu.regs[p.args.any_reg.Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[p.args.any_reg.Rd];
  proc.cpu.cpsr.c = 0;
  proc.cpu.cpsr.v = 0;
  return OK;
}


PseudoStatus thumbdpi_add3(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_add3" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rm];
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rn];
  proc.cpu.regs[p.args.any_reg.Rd] = a+b;
  proc.cpu.cpsr.n = proc.cpu.regs[p.args.any_reg.Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[p.args.any_reg.Rd];
  proc.cpu.cpsr.c = proc.cpu.regs[p.args.any_reg.Rd]<b;
  proc.cpu.cpsr.v = ((b^~a)&(b^proc.cpu.regs[p.args.any_reg.Rd]))>>31;
  return OK;
}

PseudoStatus thumbdpi_add4(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_add4" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rd];
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rm];
  if (p.args.any_reg.Rd==ARM_CPU::PC) {
    proc.cpu.regs[ARM_CPU::PC] = a+b+4;
    return BRANCH;
  } else {
    proc.cpu.regs[p.args.any_reg.Rd] = a+b;
    return OK;
  }
}
PseudoStatus thumbdpi_and(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_and" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rd];
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rm];
  proc.cpu.regs[p.args.any_reg.Rd] = a&b;
  proc.cpu.cpsr.n = proc.cpu.regs[p.args.any_reg.Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[p.args.any_reg.Rd];
  return OK;
}


PseudoStatus thumbdpi_asr2(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_asr2" <<endl;
  uint8_t shift = proc.cpu.regs[p.args.any_reg.Rs];
  const uint32_t value = proc.cpu.regs[p.args.any_reg.Rd];
  if (shift>=32) {
    proc.cpu.cpsr.c = value&(1<<31);
    proc.cpu.regs[p.args.any_reg.Rd] = proc.cpu.cpsr.c? ~0: 0;
  } else if (shift>0) {
    proc.cpu.cpsr.c = value&(1<<(shift-1));
    proc.cpu.regs[p.args.any_reg.Rd] = (int32_t) value >>shift;
  }
  proc.cpu.cpsr.n = proc.cpu.regs[p.args.any_reg.Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[p.args.any_reg.Rd];
  return OK;
}


PseudoStatus thumbdpi_bic(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_bic" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rd];
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rm];
  proc.cpu.regs[p.args.any_reg.Rd] = a&~b;
  proc.cpu.cpsr.n = proc.cpu.regs[p.args.any_reg.Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[p.args.any_reg.Rd];
  return OK;
}


PseudoStatus thumbdpi_cmn(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_cmn" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rn];
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rm];
  const uint32_t alu_out = a+b;
  proc.cpu.cpsr.n = alu_out&(1<<31);
  proc.cpu.cpsr.z = !alu_out;
  proc.cpu.cpsr.c = alu_out<b;
  proc.cpu.cpsr.v = ((b^~a)&(b^alu_out))>>31;
  return OK;
}


PseudoStatus thumbdpi_cmp2(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_cmp2" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rn];
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rm];
  const uint32_t alu_out = a-b;
  proc.cpu.cpsr.n = alu_out&(1<<31);
  proc.cpu.cpsr.z = !alu_out;
  proc.cpu.cpsr.c = a>=b;
  proc.cpu.cpsr.v = ((a^b)&(a^alu_out))>>31;
  return OK;
}

PseudoStatus thumbdpi_cmp3(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_cmp3" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rn];
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rm];
  const uint32_t alu_out = a-b;
  proc.cpu.cpsr.n = alu_out&(1<<31);
  proc.cpu.cpsr.z = !alu_out;
  proc.cpu.cpsr.c = a>=b;
  proc.cpu.cpsr.v = ((a^b)&(a^alu_out))>>31;
  return OK;
}

PseudoStatus thumbdpi_eor(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_eor" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rd];
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rm];
  proc.cpu.regs[p.args.any_reg.Rd] = a^b;
  proc.cpu.cpsr.n = proc.cpu.regs[p.args.any_reg.Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[p.args.any_reg.Rd];
  return OK;
}

PseudoStatus thumbdpi_lsl2(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_lsl2" <<endl;
  uint8_t shift = proc.cpu.regs[p.args.any_reg.Rs];
  const uint32_t value = proc.cpu.regs[p.args.any_reg.Rd];
  if (shift>=32) {
    proc.cpu.regs[p.args.any_reg.Rd] = 0;
    proc.cpu.cpsr.c = (shift==32)? value&1: 00;
  } else if (shift>0) {
    proc.cpu.regs[p.args.any_reg.Rd] = value<<shift;
    proc.cpu.cpsr.c = value&(1<<(32-shift));
  }
  proc.cpu.cpsr.n = proc.cpu.regs[p.args.any_reg.Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[p.args.any_reg.Rd];
  return OK;
}


PseudoStatus thumbdpi_lsr2(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_lsr2" <<endl;
  uint8_t a = proc.cpu.regs[p.args.any_reg.Rs];
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rd];
  if (a>=32) {
    proc.cpu.cpsr.c = (a==32)? b&(1<<31): 0;
    proc.cpu.regs[p.args.any_reg.Rd] = 0;
  } else if (a>0) {
    proc.cpu.cpsr.c = b&(1<<(a-1));
    proc.cpu.regs[p.args.any_reg.Rd] = b>>a;
  }
  proc.cpu.cpsr.n = proc.cpu.regs[p.args.any_reg.Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[p.args.any_reg.Rd];
  return OK;
}


PseudoStatus thumbdpi_mov3(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_mov3" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rm];
  if (p.args.any_reg.Rd==ARM_CPU::PC) {
    proc.cpu.regs[ARM_CPU::PC] = a+4;
    return BRANCH;
  } else {
    proc.cpu.regs[p.args.any_reg.Rd] = a;
    return OK;
  }
}
PseudoStatus thumbdpi_mul(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_mul" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rm];
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rd];
  proc.cpu.regs[p.args.any_reg.Rd] = (a*b)&0xFFFFFFFF;
  proc.cpu.cpsr.n = proc.cpu.regs[p.args.any_reg.Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[p.args.any_reg.Rd];
  return OK;
}

PseudoStatus thumbdpi_mvn(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_mvn" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rm];
  proc.cpu.regs[p.args.any_reg.Rd] = ~a;
  proc.cpu.cpsr.n = proc.cpu.regs[p.args.any_reg.Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[p.args.any_reg.Rd];
  return OK;
}

PseudoStatus thumbdpi_neg(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_neg" <<endl;
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rm];
  proc.cpu.regs[p.args.any_reg.Rd] = 0-b;
  proc.cpu.cpsr.n = proc.cpu.regs[p.args.any_reg.Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[p.args.any_reg.Rd];
  proc.cpu.cpsr.c = 0>=b;
  proc.cpu.cpsr.v = ((b^0)&(0^proc.cpu.regs[p.args.any_reg.Rd]))>>31;
  return OK;
}


PseudoStatus thumbdpi_orr(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_orr" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rm];
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rd];
  proc.cpu.regs[p.args.any_reg.Rd] = a|b;
  proc.cpu.cpsr.n = proc.cpu.regs[p.args.any_reg.Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[p.args.any_reg.Rd];
  return OK;
}


PseudoStatus thumbdpi_ror(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_ror" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rs];
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rd];
  if((a&0x1F) == 0)
    proc.cpu.cpsr.c = b&(1<<31);
  else if ((a&0xFF) == 0){
    proc.cpu.cpsr.c = proc.cpu.cpsr.c;
    proc.cpu.regs[p.args.any_reg.Rd] = b;
  }
  else if ((a&0x1F)>0) {
    proc.cpu.cpsr.c = b&(1<<((a&0x1F)-1));
    proc.cpu.regs[p.args.any_reg.Rd] = valueROR(b,a&0x1F);
  }
  proc.cpu.cpsr.n = proc.cpu.regs[p.args.any_reg.Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[p.args.any_reg.Rd];
  return OK;
}

PseudoStatus thumbdpi_sbc(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_sbc" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rd];
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rm];
  const uint32_t not_c = proc.cpu.cpsr.c? 0: 1;
  const uint32_t r = a-b-not_c;
  proc.cpu.regs[p.args.any_reg.Rd] = r;
  proc.cpu.cpsr.n = r&(1<<31);
  proc.cpu.cpsr.z = r==0;
  proc.cpu.cpsr.c = a>=b && a-b>=not_c;
  proc.cpu.cpsr.v = ((b^a)&(a^proc.cpu.regs[p.args.any_reg.Rd]))>>31;
  return OK;
}

PseudoStatus thumbdpi_sub3(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_sub3" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rm];
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rn];
  proc.cpu.regs[p.args.any_reg.Rd] = b-a;
  proc.cpu.cpsr.n = proc.cpu.regs[p.args.any_reg.Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[p.args.any_reg.Rd];
  proc.cpu.cpsr.c = b>=a;
  proc.cpu.cpsr.v = ((b^a)&(b^proc.cpu.regs[p.args.any_reg.Rd]))>>31;
  return OK;
}

PseudoStatus thumbdpi_tst(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_tst" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rn];
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rm];
  const uint32_t alu_out = a&b;
  proc.cpu.cpsr.n = alu_out&(1<<31);
  proc.cpu.cpsr.z = !alu_out;
  return OK;
}

PseudoStatus thumbdpi_add1(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_add1" <<endl;
  uint8_t a = p.args.dpi_shift_imm.imm_s;
  const uint32_t b = proc.cpu.regs[p.args.dpi_shift_imm.Rn];
  proc.cpu.regs[p.args.dpi_shift_imm.Rd] = a+b;
  proc.cpu.cpsr.n = proc.cpu.regs[p.args.dpi_shift_imm.Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[p.args.dpi_shift_imm.Rd];
  proc.cpu.cpsr.c = proc.cpu.regs[p.args.dpi_shift_imm.Rd]<b;
  proc.cpu.cpsr.v = ((b^~a)&(b^proc.cpu.regs[p.args.dpi_shift_imm.Rd]))>>31;
  return OK;
}

PseudoStatus thumbdpi_add2(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_add2" <<endl;
  const uint32_t a = p.args.dpi_shift_imm.imm_s;
  const uint32_t b = proc.cpu.regs[p.args.dpi_shift_imm.Rd];
  proc.cpu.regs[p.args.dpi_shift_imm.Rd] = a+b;
  proc.cpu.cpsr.n = proc.cpu.regs[p.args.dpi_shift_imm.Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[p.args.dpi_shift_imm.Rd];
  proc.cpu.cpsr.c = proc.cpu.regs[p.args.dpi_shift_imm.Rd]<b;
  proc.cpu.cpsr.v = ((b^~a)&(b^proc.cpu.regs[p.args.dpi_shift_imm.Rd]))>>31;
  return OK;
}


PseudoStatus thumbdpi_add5(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_add5" <<endl;
  const uint32_t a = proc.cpu.regs[ARM_CPU::PC];
  proc.cpu.regs[p.args.dpi_shift_imm.Rd] =
    (a&0xFFFFFFFC) + (p.args.dpi_shift_imm.imm_s<<2);
  return OK;
}

PseudoStatus thumbdpi_add6(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_add6" <<endl;
  const uint32_t a = proc.cpu.regs[ARM_CPU::SP];
  proc.cpu.regs[p.args.dpi_shift_imm.Rd] = a + (p.args.dpi_shift_imm.imm_s<<2);
  return OK;
}

PseudoStatus thumbdpi_add7(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_add7" <<endl;
  const uint32_t a = proc.cpu.regs[ARM_CPU::SP];
  proc.cpu.regs[ARM_CPU::SP] = a + (p.args.dpi_shift_imm.imm_s<<2);
  return OK;
}

PseudoStatus thumbdpi_asr1(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_asr1" <<endl;
  const uint32_t a = p.args.dpi_shift_imm.imm_s;
  const uint32_t b = proc.cpu.regs[p.args.dpi_shift_imm.Rm];
  proc.cpu.cpsr.c = b&(1<<(a-1));
  if (a==32)
    proc.cpu.regs[p.args.dpi_shift_imm.Rd] = proc.cpu.cpsr.c? ~0: 0;
  else
    proc.cpu.regs[p.args.dpi_shift_imm.Rd] = (int32_t) b >>a;
  proc.cpu.cpsr.n = proc.cpu.regs[p.args.dpi_shift_imm.Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[p.args.dpi_shift_imm.Rd];
  return OK;
}

PseudoStatus thumbdpi_cmp1(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_cmp1" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.dpi_shift_imm.Rn];
  const uint32_t b = p.args.dpi_shift_imm.imm_s;
  const uint32_t alu_out = a-b;
  proc.cpu.cpsr.n = alu_out&(1<<31);
  proc.cpu.cpsr.z = !alu_out;
  proc.cpu.cpsr.c = a>=b;
  proc.cpu.cpsr.v = ((a^b)&(a^alu_out))>>31;
  return OK;
}

PseudoStatus thumbdpi_lsl1_zero(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_lsl1" <<endl;
  const uint32_t b = proc.cpu.regs[p.args.dpi_shift_imm.Rm];
  proc.cpu.regs[p.args.dpi_shift_imm.Rd] = b;
  proc.cpu.cpsr.n = proc.cpu.regs[p.args.dpi_shift_imm.Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[p.args.dpi_shift_imm.Rd];
  return OK;
}
PseudoStatus thumbdpi_lsl1(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_lsl1" <<endl;
  uint8_t a = p.args.dpi_shift_imm.imm_s;
  const uint32_t b = proc.cpu.regs[p.args.dpi_shift_imm.Rm];
  proc.cpu.cpsr.c = b&(1<<(32-a));
  proc.cpu.regs[p.args.dpi_shift_imm.Rd] = b<<a;
  proc.cpu.cpsr.n = proc.cpu.regs[p.args.dpi_shift_imm.Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[p.args.dpi_shift_imm.Rd];
  return OK;
}

PseudoStatus thumbdpi_lsr1(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_lsr1" <<endl;
  const uint32_t a = p.args.dpi_shift_imm.imm_s;
  const uint32_t b = proc.cpu.regs[p.args.dpi_shift_imm.Rm];
  if (a==32) {
    proc.cpu.cpsr.c = proc.cpu.regs[p.args.dpi_shift_imm.Rd]&(1<<31);
    proc.cpu.regs[p.args.dpi_shift_imm.Rd] = 0;
  } else {
    proc.cpu.cpsr.c = b&(1<<(a-1));
    proc.cpu.regs[p.args.dpi_shift_imm.Rd] = b>>a;
  }
  proc.cpu.cpsr.n = proc.cpu.regs[p.args.dpi_shift_imm.Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[p.args.dpi_shift_imm.Rd];
  return OK;
}


PseudoStatus thumbdpi_mov1(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_mov1" <<endl;
  proc.cpu.regs[p.args.dpi_shift_imm.Rd] = p.args.dpi_shift_imm.imm_s;
  proc.cpu.cpsr.n = proc.cpu.regs[p.args.dpi_shift_imm.Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[p.args.dpi_shift_imm.Rd];
  return OK;
}

PseudoStatus thumbdpi_sub1(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_sub1" <<endl;
  uint8_t a = p.args.dpi_shift_imm.imm_s;
  const uint32_t b = proc.cpu.regs[p.args.dpi_shift_imm.Rn];
  proc.cpu.regs[p.args.dpi_shift_imm.Rd] = b-a;
  proc.cpu.cpsr.n = proc.cpu.regs[p.args.dpi_shift_imm.Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[p.args.dpi_shift_imm.Rd];
  proc.cpu.cpsr.c = b>=a;
  proc.cpu.cpsr.v = ((a^b)&(b^proc.cpu.regs[p.args.dpi_shift_imm.Rd]))>>31;
  return OK;
}

PseudoStatus thumbdpi_sub2(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_sub2" <<endl;
  const uint32_t a = p.args.dpi_shift_imm.imm_s;
  const uint32_t b = proc.cpu.regs[p.args.dpi_shift_imm.Rd];
  proc.cpu.regs[p.args.dpi_shift_imm.Rd] = b-a;
  proc.cpu.cpsr.n = proc.cpu.regs[p.args.dpi_shift_imm.Rd]&(1<<31);
  proc.cpu.cpsr.z = !proc.cpu.regs[p.args.dpi_shift_imm.Rd];
  proc.cpu.cpsr.c = b>=a;
  proc.cpu.cpsr.v = ((b^a)&(b^proc.cpu.regs[p.args.dpi_shift_imm.Rd]))>>31;
  return OK;
}

PseudoStatus thumbdpi_sub4(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbdpi_sub4" <<endl;
  const uint32_t a = proc.cpu.regs[ARM_CPU::SP];
  proc.cpu.regs[ARM_CPU::SP] = a - (p.args.dpi_shift_imm.imm_s<<2);
  return OK;
}

PseudoStatus thumbb_b(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbb_b" <<endl;
  if (conditionPassed(proc.cpu.cpsr,(ARM_Condition) p.args.thumbb_b.cond)){
    proc.cpu.regs[ARM_CPU::PC] += p.args.thumbb_b.immed;
    return BRANCH;
  } else
    return OK;
}

PseudoStatus thumbb_bl_blx(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbb_bl_blx" <<endl;
  proc.cpu.regs[ARM_CPU::LR] = proc.cpu.regs[ARM_CPU::PC]|1;
  proc.cpu.regs[ARM_CPU::PC] += p.args.thumbb_b.immed;
  if (p.args.thumbb_b.exchange)
    proc.cpu.unset_thumb_mode();
  return BRANCH;
}

PseudoStatus thumbb_bx_blx2(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbb_bx_blx2" <<endl;
  const uint32_t target = proc.cpu.regs[p.args.thumbb_b.Rm];
  if (p.args.thumbb_b.exchange)
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
  return BRANCH;
}

PseudoStatus thumbis_swi(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbis_swi" <<endl;
  proc.software_interrupt();
  return BRANCH;
}

PseudoStatus thumb_pi_bkpt(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  TODO("THUMB BKPT instruction (DT=2)");
}

PseudoStatus thumbls_ldr1(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbls_ldr1" <<endl;
  const uint32_t addr =
    proc.cpu.regs[p.args.dpi_shift_imm.Rn]+p.args.dpi_shift_imm.imm_s;
  if (addr&3) {
    proc.error() <<"unpredictable word access to a non-aligned address" <<endl;
    exit(5);
  }
  proc.cpu.regs[p.args.dpi_shift_imm.Rd] = proc.mmu.read_word(addr);
  return OK;
}

PseudoStatus thumbls_ldr1_zero(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbls_ldr1_zero" <<endl;
  const uint32_t addr =
    proc.cpu.regs[p.args.dpi_shift_imm.Rn];
  if (addr&3) {
    proc.error() <<"unpredictable word access to a non-aligned address" <<endl;
    exit(5);
  }
  proc.cpu.regs[p.args.dpi_shift_imm.Rd] = proc.mmu.read_word(addr);
  return OK;
}

PseudoStatus thumbls_ldr2(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbls_ldr2" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rm];
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rn];
  const uint32_t addr = b + a;
  if ((addr&3) == 0) {
    proc.cpu.regs[p.args.any_reg.Rd] = proc.mmu.read_word(addr);
  } else {
    proc.error() <<"unpredictable word access to a non-aligned address" <<endl;
    exit(5);
  }
  return OK;
}

// PseudoStatus thumbls_ldr3(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
//   proc.debug() <<"thumbls_ldr3" <<endl;
//   const uint32_t a = proc.cpu.regs[ARM_CPU::PC];
//   const uint32_t b = p.args.dpi_shift_imm.imm_s;
//   const uint32_t addr = (a&~3) + b*4;
//   proc.cpu.regs[p.args.dpi_shift_imm.Rd] = proc.mmu.read_word(addr);
//   return OK;
// }

PseudoStatus thumbls_ldr3_opt(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbls_ldr3_opt" <<endl;
  proc.cpu.regs[p.args.dpi_imm.Rd] = p.args.dpi_imm.immed;
  return OK;
}

PseudoStatus thumbls_ldr4(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbls_ldr4" <<endl;
  const uint32_t a = proc.cpu.regs[ARM_CPU::SP];
  const uint32_t b = p.args.dpi_shift_imm.imm_s;
  const uint32_t addr = a + b*4;
  if ((addr&3) == 0) {
    proc.cpu.regs[p.args.dpi_shift_imm.Rd] = proc.mmu.read_word(addr);
  } else {
    proc.error() <<"unpredictable word access to a non-aligned address" <<endl;
    exit(5);
  }
  return OK;
}

PseudoStatus thumbls_ldrb1(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbls_ldrb1" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.dpi_shift_imm.Rn];
  const uint32_t b = p.args.dpi_shift_imm.imm_s;
  const uint32_t addr = a + b;
  proc.cpu.regs[p.args.dpi_shift_imm.Rd] = proc.mmu.read_byte(addr);
  return OK;
}

PseudoStatus thumbls_ldrb2(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbls_ldrb2" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rn];
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rm];
  const uint32_t addr = a + b;
  proc.cpu.regs[p.args.any_reg.Rd] = proc.mmu.read_byte(addr);
  return OK;
}

PseudoStatus thumbls_ldrh1(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbls_ldrh1" <<endl;
  const uint32_t a =p.args.dpi_shift_imm. imm_s;
  const uint32_t b = proc.cpu.regs[p.args.dpi_shift_imm.Rn];
  const uint32_t addr = b + a*2;
  if ((addr&1) == 0) {
    proc.cpu.regs[p.args.dpi_shift_imm.Rd] = proc.mmu.read_half(addr);
  } else {
    proc.error() <<"unpredictable half_word access to a non-aligned address" <<endl;
    exit(5);
  }
  return OK;
}


PseudoStatus thumbls_ldrh2(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbls_ldrh2" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rm];
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rn];
  const uint32_t addr = b + a;
  if ((addr&1) == 0) {
    proc.cpu.regs[p.args.any_reg.Rd] = proc.mmu.read_half(addr);
  } else {
    proc.error() <<"unpredictable half_word access to a non-aligned address" <<endl;
    exit(5);
  }
  return OK;
}

PseudoStatus thumbls_ldrsb(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbls_ldrsb" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rm];
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rn];
  const uint32_t addr = b + a;
  proc.cpu.regs[p.args.any_reg.Rd] = (int32_t) (int8_t) proc.mmu.read_byte(addr);
 return OK;
}


PseudoStatus thumbls_ldrsh(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbls_ldrsh" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rm];
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rn];
  const uint32_t addr = b + a;
  int16_t data;
  if ((addr&1) == 0)
    data = proc.mmu.read_half(addr);
  else{
    proc.error() <<"unpredictable half_word access to a non-aligned address" <<endl;
    exit(5);
  }
  proc.cpu.regs[p.args.any_reg.Rd] = (int32_t) data;
 return OK;
}


PseudoStatus thumbls_str1(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbls_str1" <<endl;
  const uint32_t addr =
    proc.cpu.regs[p.args.dpi_shift_imm.Rn]+p.args.dpi_shift_imm.imm_s;
  if (addr&3) {
    proc.error() <<"unpredictable word access to a non-aligned address" <<endl;
    exit(5);
  }
  proc.mmu.write_word(addr,proc.cpu.regs[p.args.dpi_shift_imm.Rd]);
  return OK;
}


PseudoStatus thumbls_str2(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbls_str2" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rm];
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rn];
  const uint32_t addr = b + a;
  if ((addr&3) == 0)
    proc.mmu.write_word(addr,proc.cpu.regs[p.args.any_reg.Rd]);
  else{
    proc.error() <<"unpredictable word access to a non-aligned address" <<endl;
    exit(5);
  }
  return OK;
}

PseudoStatus thumbls_str3(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbls_str3" <<endl;
  const uint32_t a = proc.cpu.regs[ARM_CPU::SP];
  const uint32_t b = p.args.dpi_shift_imm.imm_s;
  const uint32_t addr = a + b*4;
  if ((addr&3) == 0)
    proc.mmu.write_word(addr,proc.cpu.regs[p.args.dpi_shift_imm.Rd]);
  else{
    proc.error() <<"unpredictable word access to a non-aligned address" <<endl;
    exit(5);
  }
  return OK;
}


PseudoStatus thumbls_strb1(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbls_strb1" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.dpi_shift_imm.Rn];
  const uint32_t b = p.args.dpi_shift_imm.imm_s;
  const uint32_t addr = a + b;
  proc.mmu.write_byte(addr,proc.cpu.regs[p.args.dpi_shift_imm.Rd]);
  return OK;
}


PseudoStatus thumbls_strb2(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbls_lstrb2" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rn];
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rm];
  const uint32_t addr = a + b;
  proc.mmu.write_byte(addr,proc.cpu.regs[p.args.any_reg.Rd]&0xFF);
  return OK;
}

PseudoStatus thumbls_strh1(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbls_strh1" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.dpi_shift_imm.Rn];
  const uint32_t b = p.args.dpi_shift_imm.imm_s;
  const uint32_t addr = a + b*2;
  if ((addr&1) == 0)
    proc.mmu.write_half(addr,proc.cpu.regs[p.args.dpi_shift_imm.Rd]);
  else{
    proc.error() <<"unpredictable half access to a non-aligned address" <<endl;
    exit(5);
  }
  return OK;
}


PseudoStatus thumbls_strh2(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumbls_strh2" <<endl;
  const uint32_t a = proc.cpu.regs[p.args.any_reg.Rn];
  const uint32_t b = proc.cpu.regs[p.args.any_reg.Rm];
  const uint32_t addr = a + b;
  if ((addr&1) == 0)
    proc.mmu.write_half(addr,proc.cpu.regs[p.args.any_reg.Rd]);
  else{
    proc.error() <<"unpredictable half access to a non-aligned address" <<endl;
    exit(5);
  }
  return OK;
}


PseudoStatus thumblsm_ldmia(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumblsm_ldmia" <<endl;
  const uint32_t start_addr = proc.cpu.regs[p.args.thumb_lsm.Rn];
  const uint32_t end_addr =
    proc.cpu.regs[p.args.thumb_lsm.Rn] + p.args.thumb_lsm.nb_reg*4 -4;
  uint32_t addr = start_addr;
  for (uint8_t i = 0; i<8; ++i)
    if (p.args.thumb_lsm.registers&(1<<i)) {
      proc.cpu.regs[i] = proc.mmu.read_word(addr);
      addr += 4;
    }
  if (end_addr!=addr-4)
    UNREACHABLE;
  if (!(p.args.thumb_lsm.registers&(1<<p.args.thumb_lsm.Rn)))
    proc.cpu.regs[p.args.thumb_lsm.Rn] =
      proc.cpu.regs[p.args.thumb_lsm.Rn] + p.args.thumb_lsm.nb_reg*4;
  return OK;
}


PseudoStatus thumblsm_stmia(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumblsm_stmia" <<endl;
  const uint32_t start_addr = proc.cpu.regs[p.args.thumb_lsm.Rn];
  const uint32_t end_addr =
    proc.cpu.regs[p.args.thumb_lsm.Rn] + p.args.thumb_lsm.nb_reg*4 -4;
  uint32_t addr = start_addr;
  for (uint8_t i = 0; i<8; ++i)
    if (p.args.thumb_lsm.registers&(1<<i)) {
      proc.mmu.write_word(addr,proc.cpu.regs[i]);
      addr += 4;
    }
  if (end_addr!=addr-4)
    UNREACHABLE;
  proc.cpu.regs[p.args.thumb_lsm.Rn] =
    proc.cpu.regs[p.args.thumb_lsm.Rn] + p.args.thumb_lsm.nb_reg*4;
  return OK;
}


PseudoStatus thumblsm_pop(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumblsm_pop" <<endl;
  const uint32_t start_addr = proc.cpu.regs[ARM_CPU::SP];
  const uint32_t end_addr =
    proc.cpu.regs[ARM_CPU::SP] +(p.args.thumb_lsm.R+p.args.thumb_lsm.nb_reg)*4 ;
  uint32_t addr = start_addr;
  for (int i = 0; i<=7; ++i)
    if (p.args.thumb_lsm.registers&(1<<i)) {
      proc.cpu.regs[i] = proc.mmu.read_word(addr); ;
      addr += 4;
    }
  if (p.args.thumb_lsm.R) {
    const uint32_t value = proc.mmu.read_word(addr);
    switch (value&3) {
    case 0: // 00
      proc.cpu.unset_thumb_mode();
      proc.cpu.regs[ARM_CPU::PC] = value+8;
      break;
    case 2: // 10
      proc.error() <<"unpredictable word access to a non-aligned address" <<endl;
      exit(5);
    case 1: // 01
    case 3: // 11
      proc.cpu.regs[ARM_CPU::PC] = (value&~1)+4;
    }
    addr +=4;
    if (end_addr!=addr)
      UNREACHABLE;
    proc.cpu.regs[ARM_CPU::SP] = end_addr;
    return BRANCH;
  } else {
    if (end_addr!=addr)
      UNREACHABLE;
    proc.cpu.regs[ARM_CPU::SP] = end_addr;
    return OK;
  }
}

PseudoStatus thumblsm_push(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"thumblsm_push" <<endl;
  const uint32_t start_addr =
    proc.cpu.regs[ARM_CPU::SP] - (p.args.thumb_lsm.R+p.args.thumb_lsm.nb_reg)*4 ;
  const uint32_t end_addr = proc.cpu.regs[ARM_CPU::SP]-4;
  uint32_t addr = start_addr;
  for (int i = 0; i<=7; ++i)
    if (p.args.thumb_lsm.registers&(1<<i)) {
      proc.mmu.write_word(addr,proc.cpu.regs[i]);
      addr += 4;
    }
  if (p.args.thumb_lsm.R) {
    proc.mmu.write_word(addr,proc.cpu.regs[ARM_CPU::LR]); ;
    addr +=4;
  }
  if (end_addr!=addr-4)
    UNREACHABLE;
  proc.cpu.regs[ARM_CPU::SP] =
    proc.cpu.regs[ARM_CPU::SP] - 4*(p.args.thumb_lsm.R+p.args.thumb_lsm.nb_reg);
  return OK;
}

} // namespace simsoc
