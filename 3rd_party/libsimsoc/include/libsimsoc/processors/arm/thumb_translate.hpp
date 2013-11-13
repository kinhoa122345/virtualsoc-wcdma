//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef THUMB_TRANSLATE_HPP
#define THUMB_TRANSLATE_HPP

#include "armis_visitor.hpp"
#include <inttypes.h>
#include <cstdlib>

namespace simsoc {

  class ARM_Processor;
  class ARM_Instruction;
  struct ARM_PseudoInstruction;

  class THUMB_Translate: ARM_InstructionVisitor {
  public:
    THUMB_Translate(ARM_Processor &processor,
                    ARM_Instruction *instruction,
                    ARM_PseudoInstruction &pseudo_instruction);

    void visit(ARM32_Instruction &instruction);
    void visit(ARM_Undefined &instruction);
    void visit(ARM_Unpredictable &instruction);
    void visit(ARM_Nop &instruction);

    // cf thumbis_arithmetic.hpp
    void visit(THUMB_adc &instruction);
    void visit(THUMB_mov2 &instruction);
    void visit(THUMB_add1 &instruction);
    void visit(THUMB_add2 &instruction);
    void visit(THUMB_add3 &instruction);
    void visit(THUMB_add4 &instruction);
    void visit(THUMB_add5 &instruction);
    void visit(THUMB_add6 &instruction);
    void visit(THUMB_add7 &instruction);
    void visit(THUMB_and &instruction);
    void visit(THUMB_asr1 &instruction);
    void visit(THUMB_asr2 &instruction);
    void visit(THUMB_bic &instruction);
    void visit(THUMB_cmn &instruction);
    void visit(THUMB_cmp1 &instruction);
    void visit(THUMB_cmp2 &instruction);
    void visit(THUMB_cmp3 &instruction);
    void visit(THUMB_eor &instruction);
    void visit(THUMB_lsl1 &instruction);
    void visit(THUMB_lsl2 &instruction);
    void visit(THUMB_lsr1 &instruction);
    void visit(THUMB_lsr2 &instruction);
    void visit(THUMB_mov1 &instruction);
    void visit(THUMB_mov3 &instruction);
    void visit(THUMB_mul &instruction);
    void visit(THUMB_mvn &instruction);
    void visit(THUMB_neg &instruction);
    void visit(THUMB_orr &instruction);
    void visit(THUMB_sbc &instruction);
    void visit(THUMB_ror &instruction);
    void visit(THUMB_sub1 &instruction);
    void visit(THUMB_sub2 &instruction);
    void visit(THUMB_sub3 &instruction);
    void visit(THUMB_sub4 &instruction);
    void visit(THUMB_tst &instruction);

    // cf thumbis_control.hpp
    void visit(THUMB_b &instruction);
    void visit(THUMB_bl_blx1 &instruction);
    void visit(THUMB_bx_blx2 &instruction);
    void visit(THUMB_swi &instruction);
    void visit(THUMB_bkpt &instruction);

    // cf thumbis_loadstore.hpp
    void visit(THUMB_ldr1 &instruction);
    void visit(THUMB_ldr2 &instruction);
    void visit(THUMB_ldr3 &instruction);
    void visit(THUMB_ldr4 &instruction);
    void visit(THUMB_ldrb1 &instruction);
    void visit(THUMB_ldrb2 &instruction);
    void visit(THUMB_ldrh1 &instruction);
    void visit(THUMB_ldrh2 &instruction);
    void visit(THUMB_ldrsb &instruction);
    void visit(THUMB_ldrsh &instruction);
    void visit(THUMB_str1 &instruction);
    void visit(THUMB_str2 &instruction);
    void visit(THUMB_str3 &instruction);
    void visit(THUMB_strb1 &instruction);
    void visit(THUMB_strb2 &instruction);
    void visit(THUMB_strh1 &instruction);
    void visit(THUMB_strh2 &instruction);
    void visit(THUMB_ldmia &instruction);
    void visit(THUMB_stmia &instruction);
    void visit(THUMB_pop &instruction);
    void visit(THUMB_push &instruction);

  private:
    ARM_Processor &proc;
    ARM_PseudoInstruction &pi;
  };

} // namespace simsoc

#endif //THUMB_TRANSLATE_HPP
