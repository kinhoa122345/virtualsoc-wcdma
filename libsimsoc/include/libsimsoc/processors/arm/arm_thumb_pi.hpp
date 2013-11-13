//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARMPI_THUMB_HPP
#define ARMPI_THUMB_HPP

#include "libsimsoc/processors/arm/armpi.hpp"

namespace simsoc {

PseudoStatus thumb_pi_nop(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_adc(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_mov2(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_add3(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_add4(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_and(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_asr2(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_bic(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_cmn(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_cmp2(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_cmp3(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_eor(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_lsl2(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_lsr2(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_mov3(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_mul(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_mvn(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_neg(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_orr(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_ror(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_sbc(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_sub3(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_tst(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_add1(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_add2(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_add5(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_add6(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_add7(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_asr1(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_cmp1(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_lsl1_zero(ARM_Processor &proc, const ARM_PseudoInstruction& p);
PseudoStatus thumbdpi_lsl1(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_lsr1(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_mov1(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_sub1(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_sub2(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbdpi_sub4(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbb_b(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbb_bl_blx(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbb_bx_blx2(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbis_swi(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumb_pi_bkpt(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbls_ldr1(ARM_Processor &proc, const ARM_PseudoInstruction& p);
PseudoStatus thumbls_ldr1_zero(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbls_ldr2(ARM_Processor &proc, const ARM_PseudoInstruction& p);

// PseudoStatus thumbls_ldr3(ARM_Processor &proc, const ARM_PseudoInstruction& p);
PseudoStatus thumbls_ldr3_opt(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbls_ldr4(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbls_ldrb1(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbls_ldrb2(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbls_ldrh1(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbls_ldrh2(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbls_ldrsb(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbls_ldrsh(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbls_str1(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbls_str2(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbls_str3(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbls_strb1(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbls_strb2(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbls_strh1(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumbls_strh2(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumblsm_ldmia(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumblsm_stmia(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumblsm_pop(ARM_Processor &proc, const ARM_PseudoInstruction& p);

PseudoStatus thumblsm_push(ARM_Processor &proc, const ARM_PseudoInstruction& p);

} // namespace simsoc

#endif //ARMPI_THUMB_HPP
