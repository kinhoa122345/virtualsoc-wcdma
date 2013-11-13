//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARMIS_VISITOR_HPP
#define ARMIS_VISITOR_HPP

namespace simsoc {

  // defined in armis.hpp
  class ARM_Instruction;
  class ARM_Undefined;
  class ARM_Unpredictable;
  class ARM_Nop;
  class ARM32_Instruction;
  class THUMB_Instruction;

  // defined in armis_arithmetic.hpp
  class ARM_DPI_ShiftImm;
  class ARM_DPI_ShiftReg;
  class ARM_DPI_Imm;
  template <class op> class ARM_NumericIS;
  template <class op> class ARM_NumericRS;
  template <class op> class ARM_NumericImm;
  struct ARM_adc;
  struct ARM_add;
  struct ARM_rsb;
  struct ARM_rsc;
  struct ARM_sbc;
  struct ARM_sub;
  template <class op> class ARM_BooleanIS;
  template <class op> class ARM_BooleanRS;
  template <class op> class ARM_BooleanImm;
  struct ARM_and;
  struct ARM_bic;
  struct ARM_eor;
  struct ARM_orr;
  template <class op> class ARM_CompareIS;
  template <class op> class ARM_CompareRS;
  template <class op> class ARM_CompareImm;
  struct ARM_cmn;
  struct ARM_cmp;
  template <class op> class ARM_TestIS;
  template <class op> class ARM_TestRS;
  template <class op> class ARM_TestImm;
  struct ARM_teq;
  struct ARM_tst;
  template <class op> class ARM_MoveIS;
  template <class op> class ARM_MoveRS;
  template <class op> class ARM_MoveImm;
  struct ARM_mov;
  struct ARM_mvn;
  class ARM_clz;
  class ARM_mla;
  class ARM_mul;
  template <class op> class ARM_longmult;
  struct ARM_smlal;
  struct ARM_smull;
  struct ARM_umlal;
  struct ARM_umull;

  // defined in armis_control.hpp
  class ARM_InstrWithTargetAddr;
  class ARM_b;
  class ARM_Idle;
  class ARM_bl;
  class ARM_bx;
  class ARM_blx;
  class ARM_blx2;
  class ARM_bkpt;
  class ARM_mrs;
  class ARM_msr_imm;
  class ARM_msr_reg;
  class ARM_swi;

  // defined in armis_coproc.hpp
  class ARM_cdp;
  class ARM_cdp2;
  class ARM_ldc;
  class ARM_ldc2;
  class ARM_stc;
  class ARM_stc2;
  class ARM_mcr;
  class ARM_mcr2;
  class ARM_mrc;
  class ARM_mrc2;

  // defined in armis_edsp.hpp
  template <class Compute> class ARM_EDSP_qarith;
  struct ARM_EDSP_qadd_traits ;
  struct ARM_EDSP_qdadd_traits;
  struct ARM_EDSP_qsub_traits ;
  struct ARM_EDSP_qdsub_traits;
  class ARM_EDSP_smla;
  class ARM_EDSP_smlal;
  class ARM_EDSP_smlaw;
  class ARM_EDSP_smul;
  class ARM_EDSP_smulw;

  // defined in armis_loadstore.hpp
  class ARM_LoadStoreImmBase;
  class ARM_LoadStoreRegBase;
  class ARM_LoadStoreScRgBase;
  template <class op> class ARM_LoadStoreImm;
  template <class op> class ARM_LoadStoreReg;
  template <class op> class ARM_LoadStoreScRg;
  struct ARM_ldr;
  struct ARM_ldrb;
  struct ARM_str;
  struct ARM_strb;
  struct ARM_ldrt;
  struct ARM_ldrbt;
  struct ARM_strt;
  struct ARM_strbt;
  struct ARM_ldrh;
  struct ARM_ldrsb;
  struct ARM_ldrsh;
  struct ARM_strh;
  struct ARM_ldrd;
  struct ARM_strd;
  class ARM_lsm;
  class ARM_ldm;
  class ARM_ldm_2;
  class ARM_ldm_3;
  class ARM_stm;
  class ARM_stm_2;
  class ARM_swp;
  class ARM_swpb;

  // defined in thumbis_arithmetic.hpp
  class THUMB_adc;
  class THUMB_mov2;
  class THUMB_add1;
  class THUMB_add2;
  class THUMB_add3;
  class THUMB_add4;
  class THUMB_add5;
  class THUMB_add6;
  class THUMB_add7;
  class THUMB_and;
  class THUMB_asr1;
  class THUMB_asr2;
  class THUMB_bic;
  class THUMB_cmn;
  class THUMB_cmp1;
  class THUMB_cmp2;
  class THUMB_cmp3;
  class THUMB_eor;
  class THUMB_lsl1;
  class THUMB_lsl2;
  class THUMB_lsr1;
  class THUMB_lsr2;
  class THUMB_mov1;
  class THUMB_mov3;
  class THUMB_mul;
  class THUMB_mvn;
  class THUMB_neg;
  class THUMB_orr;
  class THUMB_sbc;
  class THUMB_ror;
  class THUMB_sub1;
  class THUMB_sub2;
  class THUMB_sub3;
  class THUMB_sub4;
  class THUMB_tst;

  // defined in thumbis_control.hpp
  class THUMB_b;
  class THUMB_bl_blx1;
  class THUMB_bx_blx2;
  class THUMB_swi;
  class THUMB_bkpt;

  // defined in thumbis_loadstore.hpp
  class THUMB_ldr1;
  class THUMB_ldr2;
  class THUMB_ldr3;
  class THUMB_ldr4;
  class THUMB_ldrb1;
  class THUMB_ldrb2;
  class THUMB_ldrh1;
  class THUMB_ldrh2;
  class THUMB_ldrsb;
  class THUMB_ldrsh;
  class THUMB_str1;
  class THUMB_str2;
  class THUMB_str3;
  class THUMB_strb1;
  class THUMB_strb2;
  class THUMB_strh1;
  class THUMB_strh2;
  class THUMB_ldmia;
  class THUMB_stmia;
  class THUMB_pop;
  class THUMB_push;

  class ARM_InstructionVisitor {
  public:
    virtual ~ARM_InstructionVisitor() {}

    // defined in armis.hpp
    virtual void visit(ARM_Instruction &instruction);
    virtual void visit(ARM_Undefined &instruction);
    virtual void visit(ARM_Unpredictable &instruction);
    virtual void visit(ARM_Nop &instruction);
    virtual void visit(ARM32_Instruction &instruction);
    virtual void visit(THUMB_Instruction &instruction);

    // defined in armis_arithmetic_hpp
    virtual void visit(ARM_DPI_ShiftImm &instruction);
    virtual void visit(ARM_DPI_ShiftReg &instruction);
    virtual void visit(ARM_DPI_Imm &instruction);
    virtual void visit(ARM_NumericIS<ARM_adc> &instruction);
    virtual void visit(ARM_NumericIS<ARM_add> &instruction);
    virtual void visit(ARM_NumericIS<ARM_rsb> &instruction);
    virtual void visit(ARM_NumericIS<ARM_rsc> &instruction);
    virtual void visit(ARM_NumericIS<ARM_sbc> &instruction);
    virtual void visit(ARM_NumericIS<ARM_sub> &instruction);
    virtual void visit(ARM_NumericRS<ARM_adc> &instruction);
    virtual void visit(ARM_NumericRS<ARM_add> &instruction);
    virtual void visit(ARM_NumericRS<ARM_rsb> &instruction);
    virtual void visit(ARM_NumericRS<ARM_rsc> &instruction);
    virtual void visit(ARM_NumericRS<ARM_sbc> &instruction);
    virtual void visit(ARM_NumericRS<ARM_sub> &instruction);
    virtual void visit(ARM_NumericImm<ARM_adc> &instruction);
    virtual void visit(ARM_NumericImm<ARM_add> &instruction);
    virtual void visit(ARM_NumericImm<ARM_rsb> &instruction);
    virtual void visit(ARM_NumericImm<ARM_rsc> &instruction);
    virtual void visit(ARM_NumericImm<ARM_sbc> &instruction);
    virtual void visit(ARM_NumericImm<ARM_sub> &instruction);
    virtual void visit(ARM_BooleanIS<ARM_and> &instruction);
    virtual void visit(ARM_BooleanIS<ARM_bic> &instruction);
    virtual void visit(ARM_BooleanIS<ARM_eor> &instruction);
    virtual void visit(ARM_BooleanIS<ARM_orr> &instruction);
    virtual void visit(ARM_BooleanRS<ARM_and> &instruction);
    virtual void visit(ARM_BooleanRS<ARM_bic> &instruction);
    virtual void visit(ARM_BooleanRS<ARM_eor> &instruction);
    virtual void visit(ARM_BooleanRS<ARM_orr> &instruction);
    virtual void visit(ARM_BooleanImm<ARM_and> &instruction);
    virtual void visit(ARM_BooleanImm<ARM_bic> &instruction);
    virtual void visit(ARM_BooleanImm<ARM_eor> &instruction);
    virtual void visit(ARM_BooleanImm<ARM_orr> &instruction);
    virtual void visit(ARM_CompareIS<ARM_cmn> &instruction);
    virtual void visit(ARM_CompareIS<ARM_cmp> &instruction);
    virtual void visit(ARM_CompareRS<ARM_cmn> &instruction);
    virtual void visit(ARM_CompareRS<ARM_cmp> &instruction);
    virtual void visit(ARM_CompareImm<ARM_cmn> &instruction);
    virtual void visit(ARM_CompareImm<ARM_cmp> &instruction);
    virtual void visit(ARM_TestIS<ARM_teq> &instruction);
    virtual void visit(ARM_TestIS<ARM_tst> &instruction);
    virtual void visit(ARM_TestRS<ARM_teq> &instruction);
    virtual void visit(ARM_TestRS<ARM_tst> &instruction);
    virtual void visit(ARM_TestImm<ARM_teq> &instruction);
    virtual void visit(ARM_TestImm<ARM_tst> &instruction);
    virtual void visit(ARM_MoveIS<ARM_mov> &instruction);
    virtual void visit(ARM_MoveIS<ARM_mvn> &instruction);
    virtual void visit(ARM_MoveRS<ARM_mov> &instruction);
    virtual void visit(ARM_MoveRS<ARM_mvn> &instruction);
    virtual void visit(ARM_MoveImm<ARM_mov> &instruction);
    virtual void visit(ARM_MoveImm<ARM_mvn> &instruction);
    virtual void visit(ARM_clz &instruction);
    virtual void visit(ARM_mla &instruction);
    virtual void visit(ARM_mul &instruction);
    virtual void visit(ARM_longmult<ARM_smlal> &instruction);
    virtual void visit(ARM_longmult<ARM_smull> &instruction);
    virtual void visit(ARM_longmult<ARM_umlal> &instruction);
    virtual void visit(ARM_longmult<ARM_umull> &instruction);

    // defined in armis_control.hpp
    virtual void visit(ARM_InstrWithTargetAddr &instruction);
    virtual void visit(ARM_b &instruction);
    virtual void visit(ARM_Idle &instruction);
    virtual void visit(ARM_bl &instruction);
    virtual void visit(ARM_bx &instruction);
    virtual void visit(ARM_blx &instruction);
    virtual void visit(ARM_blx2 &instruction);
    virtual void visit(ARM_bkpt &instruction);
    virtual void visit(ARM_mrs &instruction);
    virtual void visit(ARM_msr_imm &instruction);
    virtual void visit(ARM_msr_reg &instruction);
    virtual void visit(ARM_swi &instruction);

    // defined in armis_coproc.hpp
    virtual void visit(ARM_cdp &instruction);
    virtual void visit(ARM_cdp2 &instruction);
    virtual void visit(ARM_ldc &instruction);
    virtual void visit(ARM_ldc2 &instruction);
    virtual void visit(ARM_stc &instruction);
    virtual void visit(ARM_stc2 &instruction);
    virtual void visit(ARM_mcr &instruction);
    virtual void visit(ARM_mcr2 &instruction);
    virtual void visit(ARM_mrc &instruction);
    virtual void visit(ARM_mrc2 &instruction);

    // defined in armis_edsp.hpp
    virtual void visit(ARM_EDSP_qarith<ARM_EDSP_qadd_traits > &instruction);
    virtual void visit(ARM_EDSP_qarith<ARM_EDSP_qdadd_traits> &instruction);
    virtual void visit(ARM_EDSP_qarith<ARM_EDSP_qsub_traits > &instruction);
    virtual void visit(ARM_EDSP_qarith<ARM_EDSP_qdsub_traits> &instruction);
    virtual void visit(ARM_EDSP_smla &instruction);
    virtual void visit(ARM_EDSP_smlal &instruction);
    virtual void visit(ARM_EDSP_smlaw &instruction);
    virtual void visit(ARM_EDSP_smul &instruction);
    virtual void visit(ARM_EDSP_smulw &instruction);

    // defined in armis_loadstore.hpp
    virtual void visit(ARM_LoadStoreImmBase &instruction);
    virtual void visit(ARM_LoadStoreImm<ARM_ldr> &instruction);
    virtual void visit(ARM_LoadStoreImm<ARM_ldrb> &instruction);
    virtual void visit(ARM_LoadStoreImm<ARM_str> &instruction);
    virtual void visit(ARM_LoadStoreImm<ARM_strb> &instruction);
    virtual void visit(ARM_LoadStoreImm<ARM_ldrt> &instruction);
    virtual void visit(ARM_LoadStoreImm<ARM_ldrbt> &instruction);
    virtual void visit(ARM_LoadStoreImm<ARM_strt> &instruction);
    virtual void visit(ARM_LoadStoreImm<ARM_strbt> &instruction);
    virtual void visit(ARM_LoadStoreImm<ARM_ldrh> &instruction);
    virtual void visit(ARM_LoadStoreImm<ARM_ldrsb> &instruction);
    virtual void visit(ARM_LoadStoreImm<ARM_ldrsh> &instruction);
    virtual void visit(ARM_LoadStoreImm<ARM_strh> &instruction);
    virtual void visit(ARM_LoadStoreImm<ARM_ldrd> &instruction);
    virtual void visit(ARM_LoadStoreImm<ARM_strd> &instruction);
    virtual void visit(ARM_LoadStoreRegBase &instruction);
    virtual void visit(ARM_LoadStoreReg<ARM_ldr> &instruction);
    virtual void visit(ARM_LoadStoreReg<ARM_ldrb> &instruction);
    virtual void visit(ARM_LoadStoreReg<ARM_str> &instruction);
    virtual void visit(ARM_LoadStoreReg<ARM_strb> &instruction);
    virtual void visit(ARM_LoadStoreReg<ARM_ldrt> &instruction);
    virtual void visit(ARM_LoadStoreReg<ARM_ldrbt> &instruction);
    virtual void visit(ARM_LoadStoreReg<ARM_strt> &instruction);
    virtual void visit(ARM_LoadStoreReg<ARM_strbt> &instruction);
    virtual void visit(ARM_LoadStoreReg<ARM_ldrh> &instruction);
    virtual void visit(ARM_LoadStoreReg<ARM_ldrsb> &instruction);
    virtual void visit(ARM_LoadStoreReg<ARM_ldrsh> &instruction);
    virtual void visit(ARM_LoadStoreReg<ARM_strh> &instruction);
    virtual void visit(ARM_LoadStoreReg<ARM_ldrd> &instruction);
    virtual void visit(ARM_LoadStoreReg<ARM_strd> &instruction);
    virtual void visit(ARM_LoadStoreScRgBase &instruction);
    virtual void visit(ARM_LoadStoreScRg<ARM_ldr> &instruction);
    virtual void visit(ARM_LoadStoreScRg<ARM_ldrb> &instruction);
    virtual void visit(ARM_LoadStoreScRg<ARM_str> &instruction);
    virtual void visit(ARM_LoadStoreScRg<ARM_strb> &instruction);
    virtual void visit(ARM_LoadStoreScRg<ARM_ldrt> &instruction);
    virtual void visit(ARM_LoadStoreScRg<ARM_ldrbt> &instruction);
    virtual void visit(ARM_LoadStoreScRg<ARM_strt> &instruction);
    virtual void visit(ARM_LoadStoreScRg<ARM_strbt> &instruction);
    virtual void visit(ARM_lsm &instruction);
    virtual void visit(ARM_ldm &instruction);
    virtual void visit(ARM_ldm_2 &instruction);
    virtual void visit(ARM_ldm_3 &instruction);
    virtual void visit(ARM_stm &instruction);
    virtual void visit(ARM_stm_2 &instruction);
    virtual void visit(ARM_swp &instruction);
    virtual void visit(ARM_swpb &instruction);

    // defined in thumbis_arithmetic.hpp
    virtual void visit(THUMB_adc &instruction);
    virtual void visit(THUMB_mov2 &instruction);
    virtual void visit(THUMB_add1 &instruction);
    virtual void visit(THUMB_add2 &instruction);
    virtual void visit(THUMB_add3 &instruction);
    virtual void visit(THUMB_add4 &instruction);
    virtual void visit(THUMB_add5 &instruction);
    virtual void visit(THUMB_add6 &instruction);
    virtual void visit(THUMB_add7 &instruction);
    virtual void visit(THUMB_and &instruction);
    virtual void visit(THUMB_asr1 &instruction);
    virtual void visit(THUMB_asr2 &instruction);
    virtual void visit(THUMB_bic &instruction);
    virtual void visit(THUMB_cmn &instruction);
    virtual void visit(THUMB_cmp1 &instruction);
    virtual void visit(THUMB_cmp2 &instruction);
    virtual void visit(THUMB_cmp3 &instruction);
    virtual void visit(THUMB_eor &instruction);
    virtual void visit(THUMB_lsl1 &instruction);
    virtual void visit(THUMB_lsl2 &instruction);
    virtual void visit(THUMB_lsr1 &instruction);
    virtual void visit(THUMB_lsr2 &instruction);
    virtual void visit(THUMB_mov1 &instruction);
    virtual void visit(THUMB_mov3 &instruction);
    virtual void visit(THUMB_mul &instruction);
    virtual void visit(THUMB_mvn &instruction);
    virtual void visit(THUMB_neg &instruction);
    virtual void visit(THUMB_orr &instruction);
    virtual void visit(THUMB_sbc &instruction);
    virtual void visit(THUMB_ror &instruction);
    virtual void visit(THUMB_sub1 &instruction);
    virtual void visit(THUMB_sub2 &instruction);
    virtual void visit(THUMB_sub3 &instruction);
    virtual void visit(THUMB_sub4 &instruction);
    virtual void visit(THUMB_tst &instruction);

    // defined in thumbis_control.hpp
    virtual void visit(THUMB_b &instruction);
    virtual void visit(THUMB_bl_blx1 &instruction);
    virtual void visit(THUMB_bx_blx2 &instruction);
    virtual void visit(THUMB_swi &instruction);
    virtual void visit(THUMB_bkpt &instruction);

    // defined in thumbis_loadstore.hpp
    virtual void visit(THUMB_ldr1 &instruction);
    virtual void visit(THUMB_ldr2 &instruction);
    virtual void visit(THUMB_ldr3 &instruction);
    virtual void visit(THUMB_ldr4 &instruction);
    virtual void visit(THUMB_ldrb1 &instruction);
    virtual void visit(THUMB_ldrb2 &instruction);
    virtual void visit(THUMB_ldrh1 &instruction);
    virtual void visit(THUMB_ldrh2 &instruction);
    virtual void visit(THUMB_ldrsb &instruction);
    virtual void visit(THUMB_ldrsh &instruction);
    virtual void visit(THUMB_str1 &instruction);
    virtual void visit(THUMB_str2 &instruction);
    virtual void visit(THUMB_str3 &instruction);
    virtual void visit(THUMB_strb1 &instruction);
    virtual void visit(THUMB_strb2 &instruction);
    virtual void visit(THUMB_strh1 &instruction);
    virtual void visit(THUMB_strh2 &instruction);
    virtual void visit(THUMB_ldmia &instruction);
    virtual void visit(THUMB_stmia &instruction);
    virtual void visit(THUMB_pop &instruction);
    virtual void visit(THUMB_push &instruction);

  }; // class ARM_InstructionVisitor

} // namespace simsoc

#endif //ARMIS_VISITOR_HPP
