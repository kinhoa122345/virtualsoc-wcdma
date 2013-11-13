//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARM_TRANSLATE_HPP
#define ARM_TRANSLATE_HPP

#include "armis_visitor.hpp"
#include <inttypes.h>
#include <cstdlib>

namespace simsoc {

  class ARM_Processor;
  struct ARM_PseudoInstruction;

  class ARM_Translate: ARM_InstructionVisitor {
  public:
    ARM_Translate(ARM_Processor &processor,
                  ARM_Instruction *instruction,
                  ARM_PseudoInstruction &pseudo_instruction);

    void visit(THUMB_Instruction &instruction);
    void visit(ARM_Undefined &instruction);
    void visit(ARM_Unpredictable &instruction);
    void visit(ARM_Nop &instruction);

    // defined in armis_arithmetic_hpp
    template <class op> void visit_tp(ARM_NumericIS<op> &instruction);
    template <class op> void visit_tp(ARM_NumericRS<op> &instruction);
    template <class op> void visit_tp(ARM_NumericImm<op> &instruction);
    template <class op> void visit_tp(ARM_BooleanIS<op> &instruction);
    template <class op> void visit_tp(ARM_BooleanRS<op> &instruction);
    template <class op> void visit_tp(ARM_BooleanImm<op> &instruction);
    template <class op> void visit_tp(ARM_CompareIS<op> &instruction);
    template <class op> void visit_tp(ARM_CompareRS<op> &instruction);
    template <class op> void visit_tp(ARM_CompareImm<op> &instruction);
    template <class op> void visit_tp(ARM_TestIS<op> &instruction);
    template <class op> void visit_tp(ARM_TestRS<op> &instruction);
    template <class op> void visit_tp(ARM_TestImm<op> &instruction);
    template <class op> void visit_tp(ARM_MoveIS<op> &instruction);
    template <class op> void visit_tp(ARM_MoveRS<op> &instruction);
    template <class op> void visit_tp(ARM_MoveImm<op> &instruction);
    void visit(ARM_NumericIS<ARM_adc> &instruction);
    void visit(ARM_NumericIS<ARM_add> &instruction);
    void visit(ARM_NumericIS<ARM_rsb> &instruction);
    void visit(ARM_NumericIS<ARM_rsc> &instruction);
    void visit(ARM_NumericIS<ARM_sbc> &instruction);
    void visit(ARM_NumericIS<ARM_sub> &instruction);
    void visit(ARM_NumericRS<ARM_adc> &instruction);
    void visit(ARM_NumericRS<ARM_add> &instruction);
    void visit(ARM_NumericRS<ARM_rsb> &instruction);
    void visit(ARM_NumericRS<ARM_rsc> &instruction);
    void visit(ARM_NumericRS<ARM_sbc> &instruction);
    void visit(ARM_NumericRS<ARM_sub> &instruction);
    void visit(ARM_NumericImm<ARM_adc> &instruction);
    void visit(ARM_NumericImm<ARM_add> &instruction);
    void visit(ARM_NumericImm<ARM_rsb> &instruction);
    void visit(ARM_NumericImm<ARM_rsc> &instruction);
    void visit(ARM_NumericImm<ARM_sbc> &instruction);
    void visit(ARM_NumericImm<ARM_sub> &instruction);
    void visit(ARM_BooleanIS<ARM_and> &instruction);
    void visit(ARM_BooleanIS<ARM_bic> &instruction);
    void visit(ARM_BooleanIS<ARM_eor> &instruction);
    void visit(ARM_BooleanIS<ARM_orr> &instruction);
    void visit(ARM_BooleanRS<ARM_and> &instruction);
    void visit(ARM_BooleanRS<ARM_bic> &instruction);
    void visit(ARM_BooleanRS<ARM_eor> &instruction);
    void visit(ARM_BooleanRS<ARM_orr> &instruction);
    void visit(ARM_BooleanImm<ARM_and> &instruction);
    void visit(ARM_BooleanImm<ARM_bic> &instruction);
    void visit(ARM_BooleanImm<ARM_eor> &instruction);
    void visit(ARM_BooleanImm<ARM_orr> &instruction);
    void visit(ARM_CompareIS<ARM_cmn> &instruction);
    void visit(ARM_CompareIS<ARM_cmp> &instruction);
    void visit(ARM_CompareRS<ARM_cmn> &instruction);
    void visit(ARM_CompareRS<ARM_cmp> &instruction);
    void visit(ARM_CompareImm<ARM_cmn> &instruction);
    void visit(ARM_CompareImm<ARM_cmp> &instruction);
    void visit(ARM_TestIS<ARM_teq> &instruction);
    void visit(ARM_TestIS<ARM_tst> &instruction);
    void visit(ARM_TestRS<ARM_teq> &instruction);
    void visit(ARM_TestRS<ARM_tst> &instruction);
    void visit(ARM_TestImm<ARM_teq> &instruction);
    void visit(ARM_TestImm<ARM_tst> &instruction);
    void visit(ARM_MoveIS<ARM_mov> &instruction);
    void visit(ARM_MoveIS<ARM_mvn> &instruction);
    void visit(ARM_MoveRS<ARM_mov> &instruction);
    void visit(ARM_MoveRS<ARM_mvn> &instruction);
    void visit(ARM_MoveImm<ARM_mov> &instruction);
    void visit(ARM_MoveImm<ARM_mvn> &instruction);
    void visit(ARM_clz &instruction);
    void visit(ARM_mla &instruction);
    void visit(ARM_mul &instruction);
    template <class op> void visit_tp(ARM_longmult<op> &instruction);
    void visit(ARM_longmult<ARM_smlal> &instruction);
    void visit(ARM_longmult<ARM_smull> &instruction);
    void visit(ARM_longmult<ARM_umlal> &instruction);
    void visit(ARM_longmult<ARM_umull> &instruction);

    // defined in armis_control.hpp
    void visit(ARM_b &instruction);
    void visit(ARM_Idle &instruction);
    void visit(ARM_bl &instruction);
    void visit(ARM_bx &instruction);
    void visit(ARM_blx &instruction);
    void visit(ARM_blx2 &instruction);
    void visit(ARM_bkpt &instruction);
    void visit(ARM_mrs &instruction);
    void visit(ARM_msr_imm &instruction);
    void visit(ARM_msr_reg &instruction);
    void visit(ARM_swi &instruction);

    // defined in armis_coproc.hpp
    void visit(ARM_cdp &instruction);
    void visit(ARM_cdp2 &instruction);
    void visit(ARM_ldc &instruction);
    void visit(ARM_ldc2 &instruction);
    void visit(ARM_stc &instruction);
    void visit(ARM_stc2 &instruction);
    void visit(ARM_mcr &instruction);
    void visit(ARM_mcr2 &instruction);
    void visit(ARM_mrc &instruction);
    void visit(ARM_mrc2 &instruction);

    // defined in armis_edsp.hpp
    template <class op> void visit_tp(ARM_EDSP_qarith<op> &instruction);
    void visit(ARM_EDSP_qarith<ARM_EDSP_qadd_traits > &instruction);
    void visit(ARM_EDSP_qarith<ARM_EDSP_qdadd_traits> &instruction);
    void visit(ARM_EDSP_qarith<ARM_EDSP_qsub_traits > &instruction);
    void visit(ARM_EDSP_qarith<ARM_EDSP_qdsub_traits> &instruction);
    void visit(ARM_EDSP_smla &instruction);
    void visit(ARM_EDSP_smlal &instruction);
    void visit(ARM_EDSP_smlaw &instruction);
    void visit(ARM_EDSP_smul &instruction);
    void visit(ARM_EDSP_smulw &instruction);

    // defined in armis_loadstore.hpp
    template <class op> void visit_tp(ARM_LoadStoreImm<op> &instruction);
    template <class op> void visit_tp(ARM_LoadStoreReg<op> &instruction);
    template <class op> void visit_tp(ARM_LoadStoreScRg<op> &instruction);
    void visit(ARM_LoadStoreImm<ARM_ldr> &instruction);
    void visit(ARM_LoadStoreImm<ARM_ldrb> &instruction);
    void visit(ARM_LoadStoreImm<ARM_str> &instruction);
    void visit(ARM_LoadStoreImm<ARM_strb> &instruction);
    void visit(ARM_LoadStoreImm<ARM_ldrt> &instruction);
    void visit(ARM_LoadStoreImm<ARM_ldrbt> &instruction);
    void visit(ARM_LoadStoreImm<ARM_strt> &instruction);
    void visit(ARM_LoadStoreImm<ARM_strbt> &instruction);
    void visit(ARM_LoadStoreImm<ARM_ldrh> &instruction);
    void visit(ARM_LoadStoreImm<ARM_ldrsb> &instruction);
    void visit(ARM_LoadStoreImm<ARM_ldrsh> &instruction);
    void visit(ARM_LoadStoreImm<ARM_strh> &instruction);
    void visit(ARM_LoadStoreImm<ARM_ldrd> &instruction);
    void visit(ARM_LoadStoreImm<ARM_strd> &instruction);
    void visit(ARM_LoadStoreReg<ARM_ldr> &instruction);
    void visit(ARM_LoadStoreReg<ARM_ldrb> &instruction);
    void visit(ARM_LoadStoreReg<ARM_str> &instruction);
    void visit(ARM_LoadStoreReg<ARM_strb> &instruction);
    void visit(ARM_LoadStoreReg<ARM_ldrt> &instruction);
    void visit(ARM_LoadStoreReg<ARM_ldrbt> &instruction);
    void visit(ARM_LoadStoreReg<ARM_strt> &instruction);
    void visit(ARM_LoadStoreReg<ARM_strbt> &instruction);
    void visit(ARM_LoadStoreReg<ARM_ldrh> &instruction);
    void visit(ARM_LoadStoreReg<ARM_ldrsb> &instruction);
    void visit(ARM_LoadStoreReg<ARM_ldrsh> &instruction);
    void visit(ARM_LoadStoreReg<ARM_strh> &instruction);
    void visit(ARM_LoadStoreReg<ARM_ldrd> &instruction);
    void visit(ARM_LoadStoreReg<ARM_strd> &instruction);
    void visit(ARM_LoadStoreScRg<ARM_ldr> &instruction);
    void visit(ARM_LoadStoreScRg<ARM_ldrb> &instruction);
    void visit(ARM_LoadStoreScRg<ARM_str> &instruction);
    void visit(ARM_LoadStoreScRg<ARM_strb> &instruction);
    void visit(ARM_LoadStoreScRg<ARM_ldrt> &instruction);
    void visit(ARM_LoadStoreScRg<ARM_ldrbt> &instruction);
    void visit(ARM_LoadStoreScRg<ARM_strt> &instruction);
    void visit(ARM_LoadStoreScRg<ARM_strbt> &instruction);
    void visit(ARM_ldm &instruction);
    void visit(ARM_ldm_2 &instruction);
    void visit(ARM_ldm_3 &instruction);
    void visit(ARM_stm &instruction);
    void visit(ARM_stm_2 &instruction);
    void visit(ARM_swp &instruction);
    void visit(ARM_swpb &instruction);

  private:
    ARM_Processor &proc;
    ARM_PseudoInstruction &pi;
  };

} // namespace simsoc

#endif //ARM_TRANSLATE_HPP
