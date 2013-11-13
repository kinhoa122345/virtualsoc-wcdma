//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "arm_translate.hpp"
#include "armis_arithmetic.hpp"
#include "armis_control.hpp"
#include "armis_coproc.hpp"
#include "armis_edsp.hpp"
#include "armis_loadstore.hpp"
#include "armpi.hpp"
#include <libsimsoc/translation_page.hpp>
#include <libsimsoc/display.hpp>
#include <cassert>

namespace simsoc {

  ARM_Translate::ARM_Translate(ARM_Processor &processor,
                               ARM_Instruction *instr,
                               ARM_PseudoInstruction &pseudo):
    proc(processor), pi(pseudo)
  {
    instr->accept(*this);
  }

  void ARM_Translate::visit(THUMB_Instruction &instruction) {
    UNREACHABLE;
  }

  void ARM_Translate::visit(ARM_Undefined &instruction) {
    armTranslateGeneric(pi,&instruction);
  }

  void ARM_Translate::visit(ARM_Unpredictable &instruction) {
    armTranslateGeneric(pi,&instruction);
  }

  void ARM_Translate::visit(ARM_Nop &instruction) {
    pi.f = arm_pi_nop;
  }

  template <class op> void ARM_Translate::visit_tp(ARM_NumericIS<op> &i) {
    const bool a = i.cond!=AL;
    if ((i.shift_amount == 32) && (i.shift == LSR))
      armTranslateDPI_IntIS_lsr_32(pi,op::opcode,i.s,a,i.cond,i.Rd,i.Rn,i.Rm);
    else if ((i.shift_amount == 32) && (i.shift == ASR))
      armTranslateDPI_IntIS_asr_32(pi,op::opcode,i.s,a,i.cond,i.Rd,i.Rn,i.Rm);
    else
      armTranslateDPI_IntIS(pi,op::opcode,i.s,a,i.cond,i.Rd,i.Rn,i.Rm,i.shift,i.shift_amount);
  }

  template <class op> void ARM_Translate::visit_tp(ARM_NumericRS<op> &i) {
    const bool a = i.cond!=AL;
    armTranslateDPI_IntRS(pi,op::opcode,i.s,a,i.cond,i.Rd,i.Rn,i.Rm,i.shift,i.Rs);
  }

  template <class op> void ARM_Translate::visit_tp(ARM_NumericImm<op> &i) {
    const bool a = i.cond!=AL;
    armTranslateDPI_IntImm(pi,op::opcode,i.s,a,i.cond,i.Rd,i.Rn,i.immed,i.rotate_amount);
  }

  template <class op> void ARM_Translate::visit_tp(ARM_BooleanIS<op> &i) {
    const bool a = i.cond!=AL;
    if ((i.shift_amount==32) && (i.shift==LSR))
      armTranslateDPI_BoolIS_lsr_32(pi,op::opcode,i.s,a,i.cond,i.Rd,i.Rn,i.Rm);
    else if ((i.shift_amount==32) && (i.shift==ASR))
      armTranslateDPI_BoolIS_asr_32(pi,op::opcode,i.s,a,i.cond,i.Rd,i.Rn,i.Rm);
    else
      armTranslateDPI_BoolIS(pi,op::opcode,i.s,a,i.cond,i.Rd,i.Rn,i.Rm,i.shift,i.shift_amount);
  }

  template <class op> void ARM_Translate::visit_tp(ARM_BooleanRS<op> &i) {
    const bool a = i.cond!=AL;
    armTranslateDPI_BoolRS(pi,op::opcode,i.s,a,i.cond,i.Rd,i.Rn,i.Rm,i.shift,i.Rs);
  }

  template <class op> void ARM_Translate::visit_tp(ARM_BooleanImm<op> &i) {
    const bool a = i.cond!=AL;
    armTranslateDPI_BoolImm(pi,op::opcode,i.s,a,i.cond,i.Rd,i.Rn,i.immed,i.rotate_amount);
  }

  template <class op> void ARM_Translate::visit_tp(ARM_CompareIS<op> &i) {
    const bool a = i.cond!=AL;
    if ((i.shift_amount==32) && (i.shift==LSR))
      armTranslateDPI_IntIS_lsr_32(pi,op::opcode,true,a,i.cond,0,i.Rn,i.Rm);
    else if ((i.shift_amount==32) && (i.shift==ASR))
      armTranslateDPI_IntIS_asr_32(pi,op::opcode,true,a,i.cond,0,i.Rn,i.Rm);
    else
      armTranslateDPI_IntIS(pi,op::opcode,true,a,i.cond,0,i.Rn,i.Rm,i.shift,i.shift_amount);
  }

  template <class op> void ARM_Translate::visit_tp(ARM_CompareRS<op> &i) {
    const bool a = i.cond!=AL;
    armTranslateDPI_IntRS(pi,op::opcode,true,a,i.cond,0,i.Rn,i.Rm,i.shift,i.Rs);
  }

  template <class op> void ARM_Translate::visit_tp(ARM_CompareImm<op> &i) {
    const bool a = i.cond!=AL;
    armTranslateDPI_IntImm(pi,op::opcode,true,a,i.cond,0,i.Rn,i.immed,i.rotate_amount);
  }

  template <class op> void ARM_Translate::visit_tp(ARM_TestIS<op> &i) {
    bool a = i.cond!=AL;
    if ((i.shift_amount == 32) && (i.shift == LSR))
      armTranslateDPI_BoolIS_lsr_32(pi,op::opcode,true,a,i.cond,0,i.Rn,i.Rm);
    else if ((i.shift_amount == 32) && (i.shift == ASR))
      armTranslateDPI_BoolIS_asr_32(pi,op::opcode,true,a,i.cond,0,i.Rn,i.Rm);
    else
      armTranslateDPI_BoolIS(pi,op::opcode,true,a,i.cond,0,i.Rn,i.Rm,i.shift,i.shift_amount);
  }

  template <class op> void ARM_Translate::visit_tp(ARM_TestRS<op> &i) {
    const bool a = i.cond!=AL;
    armTranslateDPI_BoolRS(pi,op::opcode,true,a,i.cond,0,i.Rn,i.Rm,i.shift,i.Rs);
  }

  template <class op> void ARM_Translate::visit_tp(ARM_TestImm<op> &i) {
    const bool a = i.cond!=AL;
    armTranslateDPI_BoolImm(pi,op::opcode,true,a,i.cond,0,i.Rn,i.immed,i.rotate_amount);
  }

  template <class op> void ARM_Translate::visit_tp(ARM_MoveIS<op> &i) {
    const bool a = i.cond!=AL;
    if ((i.shift_amount == 32) && (i.shift == LSR))
      armTranslateDPI_MoveIS_lsr_32(pi,op::opcode,i.s,a,i.cond,i.Rd,i.Rm);
    else if ((i.shift_amount == 32) && (i.shift == ASR))
      armTranslateDPI_MoveIS_asr_32(pi,op::opcode,i.s,a,i.cond,i.Rd,i.Rm);
    else
      armTranslateDPI_MoveIS(pi,op::opcode,i.s,a,i.cond,i.Rd,i.Rm,i.shift,i.shift_amount);
  }

  template <class op> void ARM_Translate::visit_tp(ARM_MoveRS<op> &i) {
    const bool a = i.cond!=AL;
    armTranslateDPI_MoveRS(pi,op::opcode,i.s,a,i.cond,i.Rd,i.Rm,i.shift,i.Rs);
  }

  template <class op> void ARM_Translate::visit_tp(ARM_MoveImm<op> &i) {
    const bool a = i.cond!=AL;
    armTranslateDPI_MoveImm(pi,op::opcode,i.s,a,i.cond,i.Rd,i.immed,i.rotate_amount);
  }

  void ARM_Translate::visit(ARM_NumericIS<ARM_adc> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_NumericIS<ARM_add> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_NumericIS<ARM_rsb> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_NumericIS<ARM_rsc> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_NumericIS<ARM_sbc> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_NumericIS<ARM_sub> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_NumericRS<ARM_adc> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_NumericRS<ARM_add> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_NumericRS<ARM_rsb> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_NumericRS<ARM_rsc> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_NumericRS<ARM_sbc> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_NumericRS<ARM_sub> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_NumericImm<ARM_adc> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_NumericImm<ARM_add> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_NumericImm<ARM_rsb> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_NumericImm<ARM_rsc> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_NumericImm<ARM_sbc> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_NumericImm<ARM_sub> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_BooleanIS<ARM_and> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_BooleanIS<ARM_bic> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_BooleanIS<ARM_eor> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_BooleanIS<ARM_orr> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_BooleanRS<ARM_and> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_BooleanRS<ARM_bic> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_BooleanRS<ARM_eor> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_BooleanRS<ARM_orr> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_BooleanImm<ARM_and> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_BooleanImm<ARM_bic> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_BooleanImm<ARM_eor> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_BooleanImm<ARM_orr> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_CompareIS<ARM_cmn> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_CompareIS<ARM_cmp> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_CompareRS<ARM_cmn> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_CompareRS<ARM_cmp> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_CompareImm<ARM_cmn> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_CompareImm<ARM_cmp> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_TestIS<ARM_teq> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_TestIS<ARM_tst> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_TestRS<ARM_teq> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_TestRS<ARM_tst> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_TestImm<ARM_teq> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_TestImm<ARM_tst> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_MoveIS<ARM_mov> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_MoveIS<ARM_mvn> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_MoveRS<ARM_mov> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_MoveRS<ARM_mvn> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_MoveImm<ARM_mov> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_MoveImm<ARM_mvn> &instruction) {visit_tp(instruction);}

  void ARM_Translate::visit(ARM_clz &i) {
    const bool a = i.cond!=AL;
    armTranslateCLZ(pi,i.cond,a,i.Rd,i.Rm);
  }

  void ARM_Translate::visit(ARM_mla &i) {
    const bool a = i.cond!=AL;
    armTranslateMLI_32(pi,1,i.s,i.cond,a,i.Rd,i.Rm,i.Rs,i.Rn);
 }

  void ARM_Translate::visit(ARM_mul &i) {
    const bool a = i.cond!=AL;
    armTranslateMLI_32(pi,0,i.s,i.cond,a,i.Rd,i.Rm,i.Rs,0);
  }

  template <class op> void ARM_Translate::visit_tp(ARM_longmult<op> &i) {
    const bool a = i.cond!=AL;
    armTranslateMLI_64(pi,op::opcode,i.s,i.cond,a,i.RdHi,i.RdLo,i.Rm,i.Rs);
  }

  void ARM_Translate::visit(ARM_longmult<ARM_smlal> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_longmult<ARM_smull> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_longmult<ARM_umlal> &instruction) {visit_tp(instruction);}
  void ARM_Translate::visit(ARM_longmult<ARM_umull> &instruction) {visit_tp(instruction);}

  void ARM_Translate::visit(ARM_b &i) {
    const bool same_page = false; //TODO
    const bool a = i.cond!=AL;
    armTranslateBImm(pi,0,same_page,i.cond,a,i.offset);
  }

  void ARM_Translate::visit(ARM_Idle &instruction) {
    armTranslateGeneric(pi,&instruction);
  }

  void ARM_Translate::visit(ARM_bl &i) {
    const bool same_page = false; //TODO
    const bool a = i.cond!=AL;
    armTranslateBImm(pi,1,same_page,i.cond,a,i.offset);
  }

  void ARM_Translate::visit(ARM_bx &i) {
    bool a = i.cond!=AL;
    armTranslateBReg(pi,4,i.cond,a,i.Rm);
  }

  void ARM_Translate::visit(ARM_blx &i) {
    const bool same_page = false; // TODO
    const bool a = false; // cond!=AL
    armTranslateBImm(pi,2,same_page,AL,a,i.offset);
  }

  void ARM_Translate::visit(ARM_blx2 &i) {
    const bool a = i.cond!=AL;
    armTranslateBReg(pi,3,i.cond,a,i.Rm);
  }

  void ARM_Translate::visit(ARM_bkpt &instruction) {
    armTranslateGeneric(pi,&instruction);
  }

  void ARM_Translate::visit(ARM_mrs &i) {
    const bool a = i.cond!=AL;
    armTranslateMRS(pi,i.cond,a,i.R,i.Rd);
  }

  void ARM_Translate::visit(ARM_msr_imm &i) {
    const bool a = i.cond!=AL;
    armTranslateMSRImm(pi,i.cond,a,i.R,i.fields,i.immed);
  }

  void ARM_Translate::visit(ARM_msr_reg &i) {
    const bool a = i.cond!=AL;
    armTranslateMSRReg(pi,i.cond,a,i.R,i.fields,i.Rm);
  }

  void ARM_Translate::visit(ARM_swi &i) {
    const bool a = i.cond!=AL;
    armTranslateSWI(pi,i.cond,a,i.m,i.immed);
  }

  void ARM_Translate::visit(ARM_cdp &i) {armTranslateGeneric(pi,&i);}
  void ARM_Translate::visit(ARM_cdp2 &i) {armTranslateGeneric(pi,&i);}
  void ARM_Translate::visit(ARM_ldc &i) {armTranslateGeneric(pi,&i);}
  void ARM_Translate::visit(ARM_ldc2 &i) {armTranslateGeneric(pi,&i);}
  void ARM_Translate::visit(ARM_stc &i) {armTranslateGeneric(pi,&i);}
  void ARM_Translate::visit(ARM_stc2 &i) {armTranslateGeneric(pi,&i);}
  void ARM_Translate::visit(ARM_mcr &i) {armTranslateGeneric(pi,&i);}
  void ARM_Translate::visit(ARM_mcr2 &i) {armTranslateGeneric(pi,&i);}
  void ARM_Translate::visit(ARM_mrc &i) {armTranslateGeneric(pi,&i);}
  void ARM_Translate::visit(ARM_mrc2 &i) {armTranslateGeneric(pi,&i);}

  template <class op> void ARM_Translate::visit_tp(ARM_EDSP_qarith<op> &i) {
    armTranslateGeneric(pi,&i);
  }
  void ARM_Translate::visit(ARM_EDSP_qarith<ARM_EDSP_qadd_traits > &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_EDSP_qarith<ARM_EDSP_qdadd_traits> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_EDSP_qarith<ARM_EDSP_qsub_traits > &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_EDSP_qarith<ARM_EDSP_qdsub_traits> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_EDSP_smla &i) {armTranslateGeneric(pi,&i);}
  void ARM_Translate::visit(ARM_EDSP_smlal &i) {armTranslateGeneric(pi,&i);}
  void ARM_Translate::visit(ARM_EDSP_smlaw &i) {armTranslateGeneric(pi,&i);}
  void ARM_Translate::visit(ARM_EDSP_smul &i) {armTranslateGeneric(pi,&i);}
  void ARM_Translate::visit(ARM_EDSP_smulw &i) {armTranslateGeneric(pi,&i);}

  template <class op> void ARM_Translate::visit_tp(ARM_LoadStoreImm<op> &i) {
    const AddressingMode adm =
      i.p? (i.w? arm32_pre_index: arm32_offset): arm32_post_index;
    if (i.Rn==ARM_CPU::PC && adm==arm32_offset && i.Rd!=ARM_CPU::PC &&
        conditionPassed(proc.cpu.cpsr,i.cond)) {
      // The instruction has just been executed, so the data is in Rd
      const uint32_t data = proc.cpu.regs[i.Rd];
      armTranslateSetRegister(pi,i.cond,i.Rd,data);
      debug() <<"\"ldr " <<ARM_AsmId(i.Rd) <<", [pc, " <<(i.u? "+#": "-#")
              <<std::hex <<i.immed <<"]\" replaced by \"" <<ARM_AsmId(i.Rd)
              <<" = " <<std::hex <<data <<"\".\n";
      return;
    }
    const bool a = i.cond!=AL;
    armTranslateLS_Imm(pi,op::opcode,i.u,i.cond,a,adm,i.Rd,i.Rn,i.immed);
  }

  template <class op> void ARM_Translate::visit_tp(ARM_LoadStoreReg<op> &i) {
    const bool a = i.cond!=AL;
    AddressingMode adm = i.p? (i.w? arm32_pre_index: arm32_offset): arm32_post_index;
    armTranslateLS_Reg(pi,op::opcode,i.u,i.cond,a,adm,i.Rd,i.Rn,i.Rm);
  }

  template <class op> void ARM_Translate::visit_tp(ARM_LoadStoreScRg<op> &i) {
    const bool a = i.cond!=AL;
    const AddressingMode adm = i.p? (i.w? arm32_pre_index:arm32_offset): arm32_post_index;
    const LSOperandMode opm = (LSOperandMode) ((uint8_t) i.shift + 2);
    armTranslateLS_RS(pi,op::opcode,i.u,i.cond,a,adm,opm,i.Rd,i.Rn,i.Rm,i.shift_imm);
  }

  void ARM_Translate::visit(ARM_LoadStoreImm<ARM_ldr> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreImm<ARM_ldrb> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreImm<ARM_str> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreImm<ARM_strb> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreImm<ARM_ldrt> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreImm<ARM_ldrbt> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreImm<ARM_strt> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreImm<ARM_strbt> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreImm<ARM_ldrh> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreImm<ARM_ldrsb> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreImm<ARM_ldrsh> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreImm<ARM_strh> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreImm<ARM_ldrd> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreImm<ARM_strd> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreReg<ARM_ldr> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreReg<ARM_ldrb> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreReg<ARM_str> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreReg<ARM_strb> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreReg<ARM_ldrt> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreReg<ARM_ldrbt> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreReg<ARM_strt> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreReg<ARM_strbt> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreReg<ARM_ldrh> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreReg<ARM_ldrsb> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreReg<ARM_ldrsh> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreReg<ARM_strh> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreReg<ARM_ldrd> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreReg<ARM_strd> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreScRg<ARM_ldr> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreScRg<ARM_ldrb> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreScRg<ARM_str> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreScRg<ARM_strb> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreScRg<ARM_ldrt> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreScRg<ARM_ldrbt> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreScRg<ARM_strt> &i) {visit_tp(i);}
  void ARM_Translate::visit(ARM_LoadStoreScRg<ARM_strbt> &i) {visit_tp(i);}

  void ARM_Translate::visit(ARM_ldm &i) {
    const bool a = i.cond!=AL;
    armTranslateLDM(pi,i.cond,a,0,i.w,i.registers&(1<<15),i.am,i.Rn,i.nb_reg,i.registers);
  }

  void ARM_Translate::visit(ARM_ldm_2 &i) {
    const bool a = i.cond!=AL;
    armTranslateSTM(pi,i.cond,a,2,i.w,i.am,i.Rn,i.nb_reg,i.registers);
  }

  void ARM_Translate::visit(ARM_ldm_3 &i) {
    const bool a = i.cond!=AL;
    armTranslateLDM(pi,i.cond,a,1,i.w,i.registers&(1<<15),i.am,i.Rn,i.nb_reg,i.registers);
  }

  void ARM_Translate::visit(ARM_stm &i) {
    const bool a = i.cond!=AL;
    armTranslateSTM(pi,i.cond,a,0,i.w,i.am,i.Rn,i.nb_reg,i.registers);
  }

  void ARM_Translate::visit(ARM_stm_2 &i) {
    const bool a = i.cond!=AL;
    armTranslateSTM(pi,i.cond,a,1,i.w,i.am,i.Rn,i.nb_reg,i.registers);
  }

  void ARM_Translate::visit(ARM_swp &i) {
    const bool a = i.cond!=AL;
    armTranslateSWP(pi,0,i.cond,a,i.Rd,i.Rm,i.Rn);
  }

  void ARM_Translate::visit(ARM_swpb &i) {
    const bool a = i.cond!=AL;
    armTranslateSWP(pi,1,i.cond,a,i.Rd,i.Rm,i.Rn);
  }

} // namespace simsoc
