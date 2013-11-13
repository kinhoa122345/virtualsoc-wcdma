//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "armis_visitor.hpp"
#include "armis.hpp"
#include "armis_arithmetic.hpp"
#include "armis_control.hpp"
#include "armis_coproc.hpp"
#include "armis_edsp.hpp"
#include "armis_loadstore.hpp"
#include "thumbis_arithmetic.hpp"
#include "thumbis_control.hpp"
#include "thumbis_loadstore.hpp"

namespace simsoc {

  // instructions defined in armis.hpp

  void ARM_InstructionVisitor::visit(ARM_Instruction &i) {
    error() <<"internal error: visitor not implemented for instruction: " <<i <<std::endl;
    exit(1);
  }

  void ARM_InstructionVisitor::visit(ARM_Undefined &i) {visit(*static_cast<ARM_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_Unpredictable &i) {visit(*static_cast<ARM_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_Nop &i) {visit(*static_cast<ARM_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM32_Instruction &i) {visit(*static_cast<ARM_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_Instruction &i) {visit(*static_cast<ARM_Instruction*>(&i));}

  // instructions defined in armis_arithmetic.hpp
  void ARM_InstructionVisitor::visit(ARM_DPI_ShiftImm &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_DPI_ShiftReg &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_DPI_Imm &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_NumericIS<ARM_adc> &i) {visit(*static_cast<ARM_DPI_ShiftImm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_NumericIS<ARM_add> &i) {visit(*static_cast<ARM_DPI_ShiftImm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_NumericIS<ARM_rsb> &i) {visit(*static_cast<ARM_DPI_ShiftImm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_NumericIS<ARM_rsc> &i) {visit(*static_cast<ARM_DPI_ShiftImm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_NumericIS<ARM_sbc> &i) {visit(*static_cast<ARM_DPI_ShiftImm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_NumericIS<ARM_sub> &i) {visit(*static_cast<ARM_DPI_ShiftImm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_NumericRS<ARM_adc> &i) {visit(*static_cast<ARM_DPI_ShiftReg*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_NumericRS<ARM_add> &i) {visit(*static_cast<ARM_DPI_ShiftReg*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_NumericRS<ARM_rsb> &i) {visit(*static_cast<ARM_DPI_ShiftReg*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_NumericRS<ARM_rsc> &i) {visit(*static_cast<ARM_DPI_ShiftReg*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_NumericRS<ARM_sbc> &i) {visit(*static_cast<ARM_DPI_ShiftReg*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_NumericRS<ARM_sub> &i) {visit(*static_cast<ARM_DPI_ShiftReg*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_NumericImm<ARM_adc> &i) {visit(*static_cast<ARM_DPI_Imm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_NumericImm<ARM_add> &i) {visit(*static_cast<ARM_DPI_Imm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_NumericImm<ARM_rsb> &i) {visit(*static_cast<ARM_DPI_Imm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_NumericImm<ARM_rsc> &i) {visit(*static_cast<ARM_DPI_Imm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_NumericImm<ARM_sbc> &i) {visit(*static_cast<ARM_DPI_Imm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_NumericImm<ARM_sub> &i) {visit(*static_cast<ARM_DPI_Imm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_BooleanIS<ARM_and> &i) {visit(*static_cast<ARM_DPI_ShiftImm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_BooleanIS<ARM_bic> &i) {visit(*static_cast<ARM_DPI_ShiftImm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_BooleanIS<ARM_eor> &i) {visit(*static_cast<ARM_DPI_ShiftImm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_BooleanIS<ARM_orr> &i) {visit(*static_cast<ARM_DPI_ShiftImm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_BooleanRS<ARM_and> &i) {visit(*static_cast<ARM_DPI_ShiftReg*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_BooleanRS<ARM_bic> &i) {visit(*static_cast<ARM_DPI_ShiftReg*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_BooleanRS<ARM_eor> &i) {visit(*static_cast<ARM_DPI_ShiftReg*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_BooleanRS<ARM_orr> &i) {visit(*static_cast<ARM_DPI_ShiftReg*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_BooleanImm<ARM_and> &i) {visit(*static_cast<ARM_DPI_Imm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_BooleanImm<ARM_bic> &i) {visit(*static_cast<ARM_DPI_Imm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_BooleanImm<ARM_eor> &i) {visit(*static_cast<ARM_DPI_Imm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_BooleanImm<ARM_orr> &i) {visit(*static_cast<ARM_DPI_Imm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_CompareIS<ARM_cmn> &i) {visit(*static_cast<ARM_DPI_ShiftImm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_CompareIS<ARM_cmp> &i) {visit(*static_cast<ARM_DPI_ShiftImm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_CompareRS<ARM_cmn> &i) {visit(*static_cast<ARM_DPI_ShiftReg*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_CompareRS<ARM_cmp> &i) {visit(*static_cast<ARM_DPI_ShiftReg*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_CompareImm<ARM_cmn> &i) {visit(*static_cast<ARM_DPI_Imm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_CompareImm<ARM_cmp> &i) {visit(*static_cast<ARM_DPI_Imm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_TestIS<ARM_teq> &i) {visit(*static_cast<ARM_DPI_ShiftImm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_TestIS<ARM_tst> &i) {visit(*static_cast<ARM_DPI_ShiftImm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_TestRS<ARM_teq> &i) {visit(*static_cast<ARM_DPI_ShiftReg*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_TestRS<ARM_tst> &i) {visit(*static_cast<ARM_DPI_ShiftReg*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_TestImm<ARM_teq> &i) {visit(*static_cast<ARM_DPI_Imm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_TestImm<ARM_tst> &i) {visit(*static_cast<ARM_DPI_Imm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_MoveIS<ARM_mov> &i) {visit(*static_cast<ARM_DPI_ShiftImm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_MoveIS<ARM_mvn> &i) {visit(*static_cast<ARM_DPI_ShiftImm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_MoveRS<ARM_mov> &i) {visit(*static_cast<ARM_DPI_ShiftReg*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_MoveRS<ARM_mvn> &i) {visit(*static_cast<ARM_DPI_ShiftReg*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_MoveImm<ARM_mov> &i) {visit(*static_cast<ARM_DPI_Imm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_MoveImm<ARM_mvn> &i) {visit(*static_cast<ARM_DPI_Imm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_clz &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_mla &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_mul &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_longmult<ARM_smlal> &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_longmult<ARM_smull> &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_longmult<ARM_umlal> &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_longmult<ARM_umull> &i) {visit(*static_cast<ARM32_Instruction*>(&i));}

  // instructions defined in armis_control.hpp
  void ARM_InstructionVisitor::visit(ARM_InstrWithTargetAddr &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_b &i) {visit(*static_cast<ARM_InstrWithTargetAddr*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_Idle &i) {visit(*static_cast<ARM_InstrWithTargetAddr*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_bl &i) {visit(*static_cast<ARM_InstrWithTargetAddr*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_bx &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_blx &i) {visit(*static_cast<ARM_InstrWithTargetAddr*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_blx2 &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_bkpt &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_mrs &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_msr_imm &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_msr_reg &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_swi &i) {visit(*static_cast<ARM32_Instruction*>(&i));}

  // instructions defined in armis_coproc.hpp
  void ARM_InstructionVisitor::visit(ARM_cdp &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_cdp2 &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_ldc &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_ldc2 &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_stc &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_stc2 &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_mcr &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_mcr2 &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_mrc &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_mrc2 &i) {visit(*static_cast<ARM32_Instruction*>(&i));}

  // instructions defined in armis_edsp.hpp
  void ARM_InstructionVisitor::visit(ARM_EDSP_qarith<ARM_EDSP_qadd_traits > &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_EDSP_qarith<ARM_EDSP_qdadd_traits> &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_EDSP_qarith<ARM_EDSP_qsub_traits > &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_EDSP_qarith<ARM_EDSP_qdsub_traits> &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_EDSP_smla &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_EDSP_smlal &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_EDSP_smlaw &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_EDSP_smul &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_EDSP_smulw &i) {visit(*static_cast<ARM32_Instruction*>(&i));}

  // instructions defined in armis_loadstore.hpp
  void ARM_InstructionVisitor::visit(ARM_LoadStoreImmBase &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreImm<ARM_ldr> &i) {visit(*static_cast<ARM_LoadStoreImmBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreImm<ARM_ldrb> &i) {visit(*static_cast<ARM_LoadStoreImmBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreImm<ARM_str> &i) {visit(*static_cast<ARM_LoadStoreImmBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreImm<ARM_strb> &i) {visit(*static_cast<ARM_LoadStoreImmBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreImm<ARM_ldrt> &i) {visit(*static_cast<ARM_LoadStoreImmBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreImm<ARM_ldrbt> &i) {visit(*static_cast<ARM_LoadStoreImmBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreImm<ARM_strt> &i) {visit(*static_cast<ARM_LoadStoreImmBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreImm<ARM_strbt> &i) {visit(*static_cast<ARM_LoadStoreImmBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreImm<ARM_ldrh> &i) {visit(*static_cast<ARM_LoadStoreImmBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreImm<ARM_ldrsb> &i) {visit(*static_cast<ARM_LoadStoreImmBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreImm<ARM_ldrsh> &i) {visit(*static_cast<ARM_LoadStoreImmBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreImm<ARM_strh> &i) {visit(*static_cast<ARM_LoadStoreImmBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreImm<ARM_ldrd> &i) {visit(*static_cast<ARM_LoadStoreImmBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreImm<ARM_strd> &i) {visit(*static_cast<ARM_LoadStoreImmBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreRegBase &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreReg<ARM_ldr> &i) {visit(*static_cast<ARM_LoadStoreRegBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreReg<ARM_ldrb> &i) {visit(*static_cast<ARM_LoadStoreRegBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreReg<ARM_str> &i) {visit(*static_cast<ARM_LoadStoreRegBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreReg<ARM_strb> &i) {visit(*static_cast<ARM_LoadStoreRegBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreReg<ARM_ldrt> &i) {visit(*static_cast<ARM_LoadStoreRegBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreReg<ARM_ldrbt> &i) {visit(*static_cast<ARM_LoadStoreRegBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreReg<ARM_strt> &i) {visit(*static_cast<ARM_LoadStoreRegBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreReg<ARM_strbt> &i) {visit(*static_cast<ARM_LoadStoreRegBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreReg<ARM_ldrh> &i) {visit(*static_cast<ARM_LoadStoreRegBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreReg<ARM_ldrsb> &i) {visit(*static_cast<ARM_LoadStoreRegBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreReg<ARM_ldrsh> &i) {visit(*static_cast<ARM_LoadStoreRegBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreReg<ARM_strh> &i) {visit(*static_cast<ARM_LoadStoreRegBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreReg<ARM_ldrd> &i) {visit(*static_cast<ARM_LoadStoreRegBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreReg<ARM_strd> &i) {visit(*static_cast<ARM_LoadStoreRegBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreScRgBase &i) {visit(*static_cast<ARM_LoadStoreScRgBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreScRg<ARM_ldr> &i) {visit(*static_cast<ARM_LoadStoreScRgBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreScRg<ARM_ldrb> &i) {visit(*static_cast<ARM_LoadStoreScRgBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreScRg<ARM_str> &i) {visit(*static_cast<ARM_LoadStoreScRgBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreScRg<ARM_strb> &i) {visit(*static_cast<ARM_LoadStoreScRgBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreScRg<ARM_ldrt> &i) {visit(*static_cast<ARM_LoadStoreScRgBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreScRg<ARM_ldrbt> &i){visit(*static_cast<ARM_LoadStoreScRgBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreScRg<ARM_strt> &i) {visit(*static_cast<ARM_LoadStoreScRgBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_LoadStoreScRg<ARM_strbt> &i){visit(*static_cast<ARM_LoadStoreScRgBase*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_lsm &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_ldm &i) {visit(*static_cast<ARM_lsm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_ldm_2 &i) {visit(*static_cast<ARM_ldm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_ldm_3 &i) {visit(*static_cast<ARM_ldm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_stm &i) {visit(*static_cast<ARM_lsm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_stm_2 &i) {visit(*static_cast<ARM_stm*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_swp &i) {visit(*static_cast<ARM32_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(ARM_swpb &i) {visit(*static_cast<ARM32_Instruction*>(&i));}

  // instructions defined in thumbis_arithmetic.hpp
  void ARM_InstructionVisitor::visit(THUMB_adc &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_mov2 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_add1 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_add2 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_add3 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_add4 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_add5 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_add6 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_add7 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_and &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_asr1 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_asr2 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_bic &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_cmn &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_cmp1 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_cmp2 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_cmp3 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_eor &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_lsl1 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_lsl2 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_lsr1 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_lsr2 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_mov1 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_mov3 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_mul &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_mvn &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_neg &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_orr &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_sbc &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_ror &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_sub1 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_sub2 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_sub3 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_sub4 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_tst &i) {visit(*static_cast<THUMB_Instruction*>(&i));}

  // instructions defined in thumbis_control.hpp
  void ARM_InstructionVisitor::visit(THUMB_b &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_bl_blx1 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_bx_blx2 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_swi &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_bkpt &i) {visit(*static_cast<THUMB_Instruction*>(&i));}

  // instructions defined in thumbis_loadstore.hpp
  void ARM_InstructionVisitor::visit(THUMB_ldr1 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_ldr2 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_ldr3 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_ldr4 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_ldrb1 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_ldrb2 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_ldrh1 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_ldrh2 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_ldrsb &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_ldrsh &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_str1 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_str2 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_str3 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_strb1 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_strb2 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_strh1 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_strh2 &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_ldmia &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_stmia &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_pop &i) {visit(*static_cast<THUMB_Instruction*>(&i));}
  void ARM_InstructionVisitor::visit(THUMB_push &i) {visit(*static_cast<THUMB_Instruction*>(&i));}

} // namespace simsoc
