//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARMPI_HPP
#define ARMPI_HPP

#include <iostream>
#include "libsimsoc/processors/common.hpp"
#include "libsimsoc/processors/arm/arm_condition.hpp"
#include "libsimsoc/processors/arm/arm_shift.hpp"
#include "libsimsoc/processors/arm/arm_dpi.hpp"
#include "libsimsoc/processors/arm/arm_loadstore.hpp"

namespace simsoc {

class ARM_Processor;
class ARM_Instruction;

class ARM_PseudoInstruction;

typedef PseudoStatus (*ARM_PseudoFunction) (ARM_Processor &proc,
                                            const ARM_PseudoInstruction& p);

/******************************************************************************/

/******************************************************************************/

struct ARM_PseudoAny {
  ARM_Condition cond;
};
// There must be NO translator for ARM_PseudoAny

struct ARM_PseudoAnyReg {
  ARM_Condition cond;
  uint8_t Rd;
  uint8_t Rn;
  uint8_t Rm;
  uint8_t Rs;
};
// There must be NO translator for ARM_PseudoAnyReg

void armTranslateNextPage(ARM_PseudoInstruction& pi);

struct ARM_PseudoGeneric {
  ARM_Instruction * instr;
};

void armTranslateGeneric(ARM_PseudoInstruction& pi, ARM_Instruction * instr);
bool isPseudoGeneric(const ARM_PseudoInstruction& pi);
void destructPseudo(ARM_PseudoInstruction& pi);

PseudoStatus arm_pi_nop(ARM_Processor &proc, const ARM_PseudoInstruction& p);

/******************************************************************************/

void armTranslateDPI_IntImm(ARM_PseudoInstruction& pi,
                            DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                            uint8_t Rd, uint8_t Rn,
                            uint8_t immed, uint8_t rotate_amount);

void armTranslateDPI_IntIS(ARM_PseudoInstruction& pi,
                           DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                           uint8_t Rd, uint8_t Rn,
                           uint8_t Rm, ARM_Shift shift, uint8_t immed);

void armTranslateDPI_IntIS_lsr_32(ARM_PseudoInstruction& pi,
                                  DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                                  uint8_t Rd, uint8_t Rn,uint8_t Rm);

void armTranslateDPI_IntIS_asr_32(ARM_PseudoInstruction& pi,
                                  DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                                  uint8_t Rd, uint8_t Rn,uint8_t Rm);

void armTranslateDPI_IntRS(ARM_PseudoInstruction& pi,
                           DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                           uint8_t Rd, uint8_t Rn,
                           uint8_t Rm, ARM_Shift shift, uint8_t Rs);

void armTranslateDPI_BoolImm(ARM_PseudoInstruction& pi,
                             DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                             uint8_t Rd, uint8_t Rn,
                             uint8_t immed, uint8_t rotate_amount);

void armTranslateDPI_BoolIS(ARM_PseudoInstruction& pi,
                            DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                            uint8_t Rd, uint8_t Rn,
                            uint8_t Rm, ARM_Shift shift, uint8_t immed);
void armTranslateDPI_BoolIS_lsr_32(ARM_PseudoInstruction& pi,
                                   DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                                   uint8_t Rd, uint8_t Rn,uint8_t Rm);
void armTranslateDPI_BoolIS_asr_32(ARM_PseudoInstruction& pi,
                                   DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                                   uint8_t Rd, uint8_t Rn,uint8_t Rm);

void armTranslateDPI_BoolRS(ARM_PseudoInstruction& pi,
                            DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                            uint8_t Rd, uint8_t Rn,
                            uint8_t Rm, ARM_Shift shift, uint8_t Rs);

void armTranslateDPI_MoveImm(ARM_PseudoInstruction& pi,
                             DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                             uint8_t Rd,
                             uint8_t immed, uint8_t rotate_amount);

void armTranslateDPI_MoveIS(ARM_PseudoInstruction& pi,
                            DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                            uint8_t Rd,
                            uint8_t Rm, ARM_Shift shift, uint8_t immed);

void armTranslateDPI_MoveIS_lsr_32(ARM_PseudoInstruction& pi,
                                   DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                                   uint8_t Rd,uint8_t Rm);
void armTranslateDPI_MoveIS_asr_32(ARM_PseudoInstruction& pi,
                                   DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                                   uint8_t Rd,uint8_t Rm);

void armTranslateDPI_MoveRS(ARM_PseudoInstruction& pi,
                            DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                            uint8_t Rd,
                            uint8_t Rm, ARM_Shift shift, uint8_t Rs);

void armTranslateMLI_32(ARM_PseudoInstruction& pi,
                        uint8_t op,
                        bool s, ARM_Condition cond, bool a,
                        uint8_t Rd,uint8_t Rm,
                        uint8_t Rs,uint8_t Rn);

void armTranslateMLI_64(ARM_PseudoInstruction& pi,
                        uint8_t op,
                        bool s, ARM_Condition cond, bool a,
                        uint8_t RdHi,uint8_t RdLo,
                        uint8_t Rm,uint8_t Rs);

void armTranslateLS_Imm(ARM_PseudoInstruction& pi,
                        LoadStoreOpcode op,
                        bool u,ARM_Condition cond, bool a,
                        AddressingMode adm,
                        uint8_t Rd,uint8_t Rn,
                        uint16_t immed);

void armTranslateLS_Reg(ARM_PseudoInstruction& pi,
                         LoadStoreOpcode op,
                        bool u,ARM_Condition cond, bool a,
                        AddressingMode adm,
                        uint8_t Rd,uint8_t Rn,
                        uint8_t Rm);

void armTranslateLS_RS(ARM_PseudoInstruction& pi,
                        LoadStoreOpcode op,
                       bool u,ARM_Condition cond, bool a,
                       AddressingMode adm, LSOperandMode opm,
                       uint8_t Rd, uint8_t Rn,
                       uint8_t Rm, uint8_t immed);

void armTranslateSWP(ARM_PseudoInstruction& pi,
                      uint8_t op,
                     ARM_Condition cond, bool a,
                     uint8_t Rd, uint8_t Rm,
                     uint8_t Rn);

void armTranslateBImm(ARM_PseudoInstruction& pi,
                       uint8_t op,
                      bool same_page,
                      ARM_Condition cond, bool a,
                      int32_t branch_offset);

void armTranslateBReg(ARM_PseudoInstruction& pi,
                       uint8_t op,
                      ARM_Condition cond, bool a,
                      uint8_t Rm);

void armTranslateCLZ(ARM_PseudoInstruction& pi,
                     ARM_Condition cond, bool a,
                     uint8_t Rd,uint8_t Rm);

void armTranslateSWI(ARM_PseudoInstruction& pi,
                     ARM_Condition cond, bool a,
                     bool m,uint32_t immed);

void armTranslateSTM(ARM_PseudoInstruction& pi,
                     ARM_Condition cond, bool a,
                     uint8_t op,bool w,uint8_t addr_m,
                     uint8_t Rn, uint8_t nb_reg,uint16_t registers);

void armTranslateLDM(ARM_PseudoInstruction& pi,
                     ARM_Condition cond, bool a,
                     uint8_t op,bool w,bool reg_pc,uint8_t addr_m,
                     uint8_t Rn, uint8_t nb_reg,uint16_t registers);

void armTranslateMRS(ARM_PseudoInstruction& pi,
                    ARM_Condition cond, bool a,
                     bool r,uint8_t Rd);

void armTranslateMSRReg(ARM_PseudoInstruction& pi,
                       ARM_Condition cond, bool a,
                        bool r,uint8_t field,uint8_t Rm);

void armTranslateMSRImm(ARM_PseudoInstruction& pi,
                        ARM_Condition cond, bool a,
                        bool r, uint8_t field, uint32_t immed);

  void armTranslateSetRegister(ARM_PseudoInstruction& pi,
                               ARM_Condition cond, uint8_t Rd, uint32_t data);

/******************************************************************************/
// code below is private, excepted "union ARM_PseudoInstruction;".

struct ARM_PseudoDpiImm {
  ARM_Condition cond;
  uint8_t Rd;
  uint8_t Rn;
  bool set_carry;
  uint8_t unused;
  uint32_t immed;
};

struct ARM_PseudoDpiShiftImm {
  ARM_Condition cond;
  uint8_t Rd;
  uint8_t Rn;
  uint8_t Rm;
  uint8_t imm_s;
};

struct ARM_PseudoDpiShiftReg {
  ARM_Condition cond;
  uint8_t Rd;
  uint8_t Rn;
  uint8_t Rm;
  uint8_t Rs;
};


struct ARM_PseudoMli32 {
  ARM_Condition cond;
  uint8_t Rd;
  uint8_t Rn;
  uint8_t Rm;
  uint8_t Rs;
};
struct ARM_PseudoMli64 {
  ARM_Condition cond;
  uint8_t RdHi;
  uint8_t RdLo;
  uint8_t Rm;
  uint8_t Rs;
};

struct ARM_PseudoLSoffset {
  ARM_Condition cond;
  uint8_t Rd;
  uint8_t Rn;
  uint16_t offset;
};
struct ARM_PseudoLSshift {
  ARM_Condition cond;
  uint8_t Rd;
  uint8_t Rn;
  uint8_t Rm;
  uint8_t immed;
};

struct ARM_PseudoSwp {
  ARM_Condition cond;
  uint8_t Rd;
  uint8_t Rn;
  uint8_t Rm;
};

struct ARM_PseudoBImm {
  ARM_Condition cond;
  int32_t offset;
};

struct ARM_PseudoBReg {
  ARM_Condition cond;
  uint8_t dummy1;
  uint8_t dummy2;
  uint8_t Rm;
};

struct ARM_PseudoCLZ {
  ARM_Condition cond;
  uint8_t Rd;
  uint8_t dummy1;
  uint8_t Rm;
};

struct ARM_PseudoSWI{
  ARM_Condition cond;
  uint32_t immed;
};

struct ARM_PseudoLSM {
  ARM_Condition cond;
  uint8_t nb_reg;
  uint8_t Rn;
  uint16_t registers;
};

struct ARM_PseudoMRS {
  ARM_Condition cond;
  uint8_t Rd;
};

struct ARM_PseudoMSR {
  ARM_Condition cond;
  uint8_t Rm;
  uint8_t field;
  uint32_t immed;
};

struct THUMB_PseudoB{
  uint32_t immed;
  uint16_t cond;
  uint8_t  Rm;
  bool     exchange;
};

struct THUMB_PseudoLSM{
  uint8_t nb_reg;
  uint8_t Rn;
  uint16_t registers;
  bool R;
};

/*********************************************************************************/

typedef union arm_pi_data {
  ARM_PseudoAny         any;
  ARM_PseudoAnyReg      any_reg;
  ARM_PseudoGeneric     generic;
  ARM_PseudoDpiImm      dpi_imm;
  ARM_PseudoDpiShiftImm dpi_shift_imm;
  ARM_PseudoDpiShiftReg dpi_shift_reg;
  ARM_PseudoMli32       mli_32;
  ARM_PseudoMli64       mli_64;
  ARM_PseudoLSoffset    ls_offset;
  ARM_PseudoLSshift     ls_immed;
  ARM_PseudoSwp         swp_2;
  ARM_PseudoBImm        b_imm;
  ARM_PseudoBReg        b_reg;
  ARM_PseudoCLZ         clz_reg;
  ARM_PseudoSWI         swi_imm;
  ARM_PseudoLSM         load_store_mult;
  ARM_PseudoMRS         mrs_no;
  ARM_PseudoMSR         msr_imm_reg;
  THUMB_PseudoB         thumbb_b;
  THUMB_PseudoLSM       thumb_lsm;
} ARM_PI_data;

struct ARM_PseudoInstruction {
  ARM_PseudoFunction f;
  ARM_PI_data args;
};

} // namespace simsoc

#endif //ARMPI_HPP
