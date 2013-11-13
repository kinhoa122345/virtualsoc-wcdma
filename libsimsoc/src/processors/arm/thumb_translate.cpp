//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "thumb_translate.hpp"
#include "thumbis_arithmetic.hpp"
#include "thumbis_control.hpp"
#include "thumbis_loadstore.hpp"
#include "arm_thumb_pi.hpp"
#include "arm_processor.hpp"
#include <libsimsoc/translation_page.hpp>
#include <libsimsoc/display.hpp>
#include <cassert>

namespace simsoc {

  THUMB_Translate::THUMB_Translate(ARM_Processor &processor,
                                   ARM_Instruction *instr,
                                   ARM_PseudoInstruction &pseudo):
    proc(processor), pi(pseudo)
  {
    instr->accept(*this);
  }

  void THUMB_Translate::visit(ARM32_Instruction &instruction) {
    UNREACHABLE;
  }

  void THUMB_Translate::visit(ARM_Undefined &instruction) {
    armTranslateGeneric(pi,&instruction);
  }

  void THUMB_Translate::visit(ARM_Unpredictable &instruction) {
    armTranslateGeneric(pi,&instruction);
  }

  void THUMB_Translate::visit(ARM_Nop &instruction) {
    pi.f = thumb_pi_nop;
  }

  void THUMB_Translate::visit(THUMB_adc &i) {
    pi.f = thumbdpi_adc;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rm = i.Rm;
  }

  void THUMB_Translate::visit(THUMB_mov2 &i) {
    pi.f = thumbdpi_mov2;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rn = i.Rn;
  }

  void THUMB_Translate::visit(THUMB_add1 &i) {
    pi.f = thumbdpi_add1;
    pi.args.dpi_shift_imm.Rd = i.Rd;
    pi.args.dpi_shift_imm.Rn = i.Rn;
    pi.args.dpi_shift_imm.imm_s = i.immed;
  }

  void THUMB_Translate::visit(THUMB_add2 &i) {
    pi.f = thumbdpi_add2;
    pi.args.dpi_shift_imm.Rd = i.Rd;
    pi.args.dpi_shift_imm.imm_s = i.immed;
  }

  void THUMB_Translate::visit(THUMB_add3 &i) {
    pi.f = thumbdpi_add3;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rn = i.Rn;
    pi.args.any_reg.Rm = i.Rm;
  }

  void THUMB_Translate::visit(THUMB_add4 &i) {
    pi.f = thumbdpi_add4;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rm = i.Rm;
  }

  void THUMB_Translate::visit(THUMB_add5 &i) {
    pi.f = thumbdpi_add5;
    pi.args.dpi_shift_imm.Rd = i.Rd;
    pi.args.dpi_shift_imm.imm_s = i.immed;
  }

  void THUMB_Translate::visit(THUMB_add6 &i) {
    pi.f = thumbdpi_add6;
    pi.args.dpi_shift_imm.Rd = i.Rd;
    pi.args.dpi_shift_imm.imm_s = i.immed;
  }

  void THUMB_Translate::visit(THUMB_add7 &i) {
    pi.f = thumbdpi_add7;
    pi.args.dpi_shift_imm.imm_s = i.immed;
  }

  void THUMB_Translate::visit(THUMB_and &i) {
    pi.f = thumbdpi_and;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rm = i.Rm;
  }

  void THUMB_Translate::visit(THUMB_asr1 &i) {
    pi.f = thumbdpi_asr1;
    pi.args.dpi_shift_imm.Rm = i.Rm;
    pi.args.dpi_shift_imm.Rd = i.Rd;
    pi.args.dpi_shift_imm.imm_s = i.immed;
  }

  void THUMB_Translate::visit(THUMB_asr2 &i) {
    pi.f = thumbdpi_asr2;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rs = i.Rs;
  }

  void THUMB_Translate::visit(THUMB_bic &i) {
    pi.f = thumbdpi_bic;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rm = i.Rm;
  }

  void THUMB_Translate::visit(THUMB_cmn &i) {
    pi.f = thumbdpi_cmn;
    pi.args.any_reg.Rn = i.Rn;
    pi.args.any_reg.Rm = i.Rm;
  }

  void THUMB_Translate::visit(THUMB_cmp1 &i) {
    pi.f = thumbdpi_cmp1;
    pi.args.dpi_shift_imm.Rn = i.Rn;
    pi.args.dpi_shift_imm.imm_s = i.immed;
  }

  void THUMB_Translate::visit(THUMB_cmp2 &i) {
    pi.f = thumbdpi_cmp2;
    pi.args.any_reg.Rn = i.Rn;
    pi.args.any_reg.Rm = i.Rm;
  }

  void THUMB_Translate::visit(THUMB_cmp3 &i) {
    pi.f = thumbdpi_cmp3;
    pi.args.any_reg.Rn = i.Rn;
    pi.args.any_reg.Rm = i.Rm;
  }

  void THUMB_Translate::visit(THUMB_eor &i) {
    pi.f = thumbdpi_eor;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rm = i.Rm;
  }

  void THUMB_Translate::visit(THUMB_lsl1 &i) {
    if (i.immed==0)
      pi.f = thumbdpi_lsl1_zero;
    else
      pi.f = thumbdpi_lsl1;
    pi.args.dpi_shift_imm.Rm = i.Rm;
    pi.args.dpi_shift_imm.Rd = i.Rd;
    pi.args.dpi_shift_imm.imm_s = i.immed;
  }

  void THUMB_Translate::visit(THUMB_lsl2 &i) {
    pi.f = thumbdpi_lsl2;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rs = i.Rs;
  }

  void THUMB_Translate::visit(THUMB_lsr1 &i) {
    pi.f = thumbdpi_lsr1;
    pi.args.dpi_shift_imm.Rm = i.Rm;
    pi.args.dpi_shift_imm.Rd = i.Rd;
    pi.args.dpi_shift_imm.imm_s = i.immed;
  }

  void THUMB_Translate::visit(THUMB_lsr2 &i) {
    pi.f = thumbdpi_lsr2;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rs = i.Rs;
  }

  void THUMB_Translate::visit(THUMB_mov1 &i) {
    pi.f = thumbdpi_mov1;
    pi.args.dpi_shift_imm.Rd = i.Rd;
    pi.args.dpi_shift_imm.imm_s = i.immed;
  }

  void THUMB_Translate::visit(THUMB_mov3 &i) {
    pi.f = thumbdpi_mov3;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rm = i.Rm;
  }

  void THUMB_Translate::visit(THUMB_mul &i) {
    pi.f = thumbdpi_mul;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rm = i.Rm;
  }

  void THUMB_Translate::visit(THUMB_mvn &i) {
    pi.f = thumbdpi_mvn;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rm = i.Rm;
  }

  void THUMB_Translate::visit(THUMB_neg &i) {
    pi.f = thumbdpi_neg;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rm = i.Rm;
  }

  void THUMB_Translate::visit(THUMB_orr &i) {
    pi.f = thumbdpi_orr;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rm = i.Rm;
  }

  void THUMB_Translate::visit(THUMB_ror &i) {
    pi.f = thumbdpi_ror;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rs = i.Rs;
  }

  void THUMB_Translate::visit(THUMB_sbc &i) {
    pi.f = thumbdpi_sbc;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rm = i.Rm;
  }

  void THUMB_Translate::visit(THUMB_sub1 &i) {
    pi.f = thumbdpi_sub1;
    pi.args.dpi_shift_imm.Rd = i.Rd;
    pi.args.dpi_shift_imm.Rn = i.Rn;
    pi.args.dpi_shift_imm.imm_s = i.immed;
  }

  void THUMB_Translate::visit(THUMB_sub2 &i) {
    pi.f = thumbdpi_sub2;
    pi.args.dpi_shift_imm.Rd = i.Rd;
    pi.args.dpi_shift_imm.imm_s = i.immed;
  }

  void THUMB_Translate::visit(THUMB_sub3 &i) {
    pi.f = thumbdpi_sub3;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rm = i.Rm;
    pi.args.any_reg.Rn = i.Rn;
  }

  void THUMB_Translate::visit(THUMB_sub4 &i) {
    pi.f = thumbdpi_sub4;
    pi.args.dpi_shift_imm.imm_s = i.immed;
  }

  void THUMB_Translate::visit(THUMB_tst &i) {
    pi.f = thumbdpi_tst;
    pi.args.any_reg.Rm = i.Rm;
    pi.args.any_reg.Rn = i.Rn;
  }

  void THUMB_Translate::visit(THUMB_b &i){
    pi.f = thumbb_b;
    pi.args.thumbb_b.immed = i.offset;
    pi.args.thumbb_b.cond = i.cond;
  }

  void THUMB_Translate::visit(THUMB_bl_blx1 &i){
    pi.f = thumbb_bl_blx;
    pi.args.thumbb_b.immed = i.offset;
    pi.args.thumbb_b.exchange = i.exchange;
  }

  void THUMB_Translate::visit(THUMB_bx_blx2 &i){
    pi.f = thumbb_bx_blx2;
    pi.args.thumbb_b.Rm = i.Rm;
    pi.args.thumbb_b.exchange = i.set_lr;
  }

  void THUMB_Translate::visit(THUMB_swi &i){
    pi.f = thumbis_swi;
    pi.args.swi_imm.immed = i.immed;
  }

  void THUMB_Translate::visit(THUMB_bkpt &i){
    pi.f = thumb_pi_bkpt;
  }

  void THUMB_Translate::visit(THUMB_ldr1 &i) {
    pi.f = (i.immed==0) ? thumbls_ldr1_zero : thumbls_ldr1;
    pi.args.dpi_shift_imm.Rd = i.Rd;
    pi.args.dpi_shift_imm.Rn = i.Rn;
    pi.args.dpi_shift_imm.imm_s = i.immed;
  }

  void THUMB_Translate::visit(THUMB_ldr2 &i) {
    pi.f = thumbls_ldr2;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rm = i.Rm;
    pi.args.any_reg.Rn = i.Rn;
  }

  void THUMB_Translate::visit(THUMB_ldr3 &i) {
    // The instruction has just been executed, so the data is in Rd
    const uint32_t data = proc.cpu.regs[i.Rd];
    pi.f = thumbls_ldr3_opt;
    pi.args.dpi_imm.Rd = i.Rd;
    pi.args.dpi_imm.immed = data;
    debug() <<"\"ldr " <<ARM_AsmId(i.Rd) <<", [pc, #"
            <<std::hex <<i.immed <<"*4]\" replaced by \"" <<ARM_AsmId(i.Rd)
            <<" = " <<std::hex <<data <<"\".\n";
  }

  void THUMB_Translate::visit(THUMB_ldr4 &i) {
    pi.f = thumbls_ldr4;
    pi.args.dpi_shift_imm.Rd = i.Rd;
    pi.args.dpi_shift_imm.imm_s = i.immed;
  }

  void THUMB_Translate::visit(THUMB_ldrb1 &i) {
    pi.f = thumbls_ldrb1;
    pi.args.dpi_shift_imm.Rd = i.Rd;
    pi.args.dpi_shift_imm.Rn = i.Rn;
    pi.args.dpi_shift_imm.imm_s = i.immed;
  }

  void THUMB_Translate::visit(THUMB_ldrb2 &i) {
    pi.f = thumbls_ldrb2;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rm = i.Rm;
    pi.args.any_reg.Rn = i.Rn;
  }

  void THUMB_Translate::visit(THUMB_ldrh1 &i) {
    pi.f = thumbls_ldrh1;
    pi.args.dpi_shift_imm.Rd = i.Rd;
    pi.args.dpi_shift_imm.Rn = i.Rn;
    pi.args.dpi_shift_imm.imm_s = i.immed;
  }

  void THUMB_Translate::visit(THUMB_ldrh2 &i) {
    pi.f = thumbls_ldrh2;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rm = i.Rm;
    pi.args.any_reg.Rn = i.Rn;
  }

  void THUMB_Translate::visit(THUMB_ldrsb &i) {
    pi.f = thumbls_ldrsb;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rm = i.Rm;
    pi.args.any_reg.Rn = i.Rn;
  }

  void THUMB_Translate::visit(THUMB_ldrsh &i) {
    pi.f = thumbls_ldrsh;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rm = i.Rm;
    pi.args.any_reg.Rn = i.Rn;
  }

  void THUMB_Translate::visit(THUMB_str1 &i) {
    pi.f = thumbls_str1;
    pi.args.dpi_shift_imm.Rd = i.Rd;
    pi.args.dpi_shift_imm.Rn = i.Rn;
    pi.args.dpi_shift_imm.imm_s = i.immed;
  }

  void THUMB_Translate::visit(THUMB_str2 &i) {
    pi.f = thumbls_str2;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rm = i.Rm;
    pi.args.any_reg.Rn = i.Rn;
  }

  void THUMB_Translate::visit(THUMB_str3 &i) {
    pi.f = thumbls_str3;
    pi.args.dpi_shift_imm.Rd = i.Rd;
    pi.args.dpi_shift_imm.imm_s = i.immed;
  }

  void THUMB_Translate::visit(THUMB_strb1 &i) {
    pi.f = thumbls_strb1;
    pi.args.dpi_shift_imm.Rd = i.Rd;
    pi.args.dpi_shift_imm.Rn = i.Rn;
    pi.args.dpi_shift_imm.imm_s = i.immed;
  }

  void THUMB_Translate::visit(THUMB_strb2 &i) {
    pi.f = thumbls_strb2;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rm = i.Rm;
    pi.args.any_reg.Rn = i.Rn;
  }

  void THUMB_Translate::visit(THUMB_strh1 &i) {
    pi.f = thumbls_strh1;
    pi.args.dpi_shift_imm.Rd = i.Rd;
    pi.args.dpi_shift_imm.Rn = i.Rn;
    pi.args.dpi_shift_imm.imm_s = i.immed;
  }

  void THUMB_Translate::visit(THUMB_strh2 &i) {
    pi.f = thumbls_strh2;
    pi.args.any_reg.Rd = i.Rd;
    pi.args.any_reg.Rm = i.Rm;
    pi.args.any_reg.Rn = i.Rn;
  }

  void THUMB_Translate::visit(THUMB_ldmia &i) {
    pi.f = thumblsm_ldmia;
    pi.args.thumb_lsm.Rn = i.Rn;
    pi.args.thumb_lsm.nb_reg = i.nb_reg;
    pi.args.thumb_lsm.registers = i.registers;
  }

  void THUMB_Translate::visit(THUMB_stmia &i) {
    pi.f = thumblsm_stmia;
    pi.args.thumb_lsm.Rn = i.Rn;
    pi.args.thumb_lsm.nb_reg = i.nb_reg;
    pi.args.thumb_lsm.registers = i.registers;
  }

  void THUMB_Translate::visit(THUMB_pop &i) {
    pi.f = thumblsm_pop;
    pi.args.thumb_lsm.nb_reg = i.nb_reg;
    pi.args.thumb_lsm.registers = i.registers;
    pi.args.thumb_lsm.R = i.R;
  }

  void THUMB_Translate::visit(THUMB_push &i) {
    pi.f = thumblsm_push;
    pi.args.thumb_lsm.nb_reg = i.nb_reg;
    pi.args.thumb_lsm.registers = i.registers;
    pi.args.thumb_lsm.R = i.R;
  }

} // namespace simsoc
