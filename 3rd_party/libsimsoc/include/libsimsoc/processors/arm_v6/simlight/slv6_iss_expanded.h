#ifndef SLV6_ISS_expanded_H
#define SLV6_ISS_expanded_H

#include "common.h"
#include "slv6_mode.h"
#include "slv6_condition.h"

BEGIN_SIMSOC_NAMESPACE

struct SLv6_Processor;
struct SLv6_Instruction;

/* A4.1.23--A5.2.2
 * LDR -- Load and Store Word or Unsigned Byte - Immediate offset */
EXTERN_C void slv6_X_LDR_M2_ImmOff(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12);

/* A4.1.99--A5.2.2
 * STR -- Load and Store Word or Unsigned Byte - Immediate offset */
EXTERN_C void slv6_X_STR_M2_ImmOff(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12);

/* A4.1.5
 * B, BL (L=1) */
EXTERN_C void slv6_X_B_L1(struct SLv6_Processor*,
    const SLv6_Condition cond,
    const uint32_t pc_offset);

/* A4.1.5
 * B, BL (L=0) */
EXTERN_C void slv6_X_B_L0(struct SLv6_Processor*,
    const SLv6_Condition cond,
    const uint32_t pc_offset);

/* A4.1.106--A5.1.3
 * SUB -- Data processing operands - Immediate (S=1) */
EXTERN_C void slv6_X_SUB_M1_Imm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.106--A5.1.3
 * SUB -- Data processing operands - Immediate (S=0) */
EXTERN_C void slv6_X_SUB_M1_Imm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.15--A5.1.4
 * CMP -- Data processing operands - Register */
EXTERN_C void slv6_X_CMP_M1_Reg(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.3--A5.1.3
 * ADD -- Data processing operands - Immediate (S=1) */
EXTERN_C void slv6_X_ADD_M1_Imm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.3--A5.1.3
 * ADD -- Data processing operands - Immediate (S=0) */
EXTERN_C void slv6_X_ADD_M1_Imm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.3--A5.1.4
 * ADD -- Data processing operands - Register (S=1) */
EXTERN_C void slv6_X_ADD_M1_Reg_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.3--A5.1.4
 * ADD -- Data processing operands - Register (S=0) */
EXTERN_C void slv6_X_ADD_M1_Reg_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.18--A5.1.4
 * EOR -- Data processing operands - Register (S=1) */
EXTERN_C void slv6_X_EOR_M1_Reg_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.18--A5.1.4
 * EOR -- Data processing operands - Register (S=0) */
EXTERN_C void slv6_X_EOR_M1_Reg_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.4--A5.1.3
 * AND -- Data processing operands - Immediate (S=1) */
EXTERN_C void slv6_X_AND_M1_Imm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.4--A5.1.3
 * AND -- Data processing operands - Immediate (S=0) */
EXTERN_C void slv6_X_AND_M1_Imm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.35--A5.1.7
 * MOV -- Data processing operands - Logical shift right by immediate (S=1) */
EXTERN_C void slv6_X_MOV_M1_LSRImm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.35--A5.1.7
 * MOV -- Data processing operands - Logical shift right by immediate (S=0) */
EXTERN_C void slv6_X_MOV_M1_LSRImm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.17
 * CPY */
EXTERN_C void slv6_X_CPY(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const SLv6_Condition cond);

/* A4.1.35--A5.1.5
 * MOV -- Data processing operands - Logical shift left by immediate (S=1) */
EXTERN_C void slv6_X_MOV_M1_LSLImm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.35--A5.1.5
 * MOV -- Data processing operands - Logical shift left by immediate (S=0) */
EXTERN_C void slv6_X_MOV_M1_LSLImm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.35--A5.1.3
 * MOV -- Data processing operands - Immediate (S=1) */
EXTERN_C void slv6_X_MOV_M1_Imm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.35--A5.1.3
 * MOV -- Data processing operands - Immediate (S=0) */
EXTERN_C void slv6_X_MOV_M1_Imm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.20--A5.4.2
 * LDM (1) -- Load and Store Multiple - Increment after (W=1) */
EXTERN_C void slv6_X_LDM1_M4_IA_W1(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.20--A5.4.2
 * LDM (1) -- Load and Store Multiple - Increment after (W=0) */
EXTERN_C void slv6_X_LDM1_M4_IA_W0(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.15--A5.1.3
 * CMP -- Data processing operands - Immediate */
EXTERN_C void slv6_X_CMP_M1_Imm(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.23--A5.2.4
 * LDR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) */
EXTERN_C void slv6_X_LDR_M2_ScRegOff_U1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.23--A5.2.4
 * LDR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) */
EXTERN_C void slv6_X_LDR_M2_ScRegOff_U0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.10
 * BX */
EXTERN_C void slv6_X_BX(struct SLv6_Processor*,
    const uint8_t m,
    const SLv6_Condition cond);

/* A4.1.3--A5.1.5
 * ADD -- Data processing operands - Logical shift left by immediate (S=1) */
EXTERN_C void slv6_X_ADD_M1_LSLImm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.3--A5.1.5
 * ADD -- Data processing operands - Logical shift left by immediate (S=0) */
EXTERN_C void slv6_X_ADD_M1_LSLImm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.24--A5.2.2
 * LDRB -- Load and Store Word or Unsigned Byte - Immediate offset */
EXTERN_C void slv6_X_LDRB_M2_ImmOff(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12);

/* A4.1.42--A5.1.4
 * ORR -- Data processing operands - Register (S=1) */
EXTERN_C void slv6_X_ORR_M1_Reg_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.42--A5.1.4
 * ORR -- Data processing operands - Register (S=0) */
EXTERN_C void slv6_X_ORR_M1_Reg_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.35--A5.1.11
 * MOV -- Data processing operands - Rotate right by immediate (S=1) */
EXTERN_C void slv6_X_MOV_M1_RRImm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.35--A5.1.11
 * MOV -- Data processing operands - Rotate right by immediate (S=0) */
EXTERN_C void slv6_X_MOV_M1_RRImm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.23--A5.2.8
 * LDR -- Load and Store Word or Unsigned Byte - Immediate post indexed */
EXTERN_C void slv6_X_LDR_M2_Imm_postInd(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12);

/* A4.1.18--A5.1.11
 * EOR -- Data processing operands - Rotate right by immediate (S=1) */
EXTERN_C void slv6_X_EOR_M1_RRImm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.18--A5.1.11
 * EOR -- Data processing operands - Rotate right by immediate (S=0) */
EXTERN_C void slv6_X_EOR_M1_RRImm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.4--A5.1.4
 * AND -- Data processing operands - Register (S=1) */
EXTERN_C void slv6_X_AND_M1_Reg_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.4--A5.1.4
 * AND -- Data processing operands - Register (S=0) */
EXTERN_C void slv6_X_AND_M1_Reg_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.99--A5.2.5
 * STR -- Load and Store Word or Unsigned Byte - Immediate pre indexed */
EXTERN_C void slv6_X_STR_M2_Imm_preInd(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12);

/* A4.1.100--A5.2.2
 * STRB -- Load and Store Word or Unsigned Byte - Immediate offset */
EXTERN_C void slv6_X_STRB_M2_ImmOff(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12);

/* A4.1.42--A5.1.5
 * ORR -- Data processing operands - Logical shift left by immediate (S=1) */
EXTERN_C void slv6_X_ORR_M1_LSLImm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.42--A5.1.5
 * ORR -- Data processing operands - Logical shift left by immediate (S=0) */
EXTERN_C void slv6_X_ORR_M1_LSLImm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.2--A5.1.4
 * ADC -- Data processing operands - Register (S=1) */
EXTERN_C void slv6_X_ADC_M1_Reg_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.2--A5.1.4
 * ADC -- Data processing operands - Register (S=0) */
EXTERN_C void slv6_X_ADC_M1_Reg_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.24--A5.2.3
 * LDRB -- Load and Store Word or Unsigned Byte - Register offset (U=1) */
EXTERN_C void slv6_X_LDRB_M2_RegOff_U1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.24--A5.2.3
 * LDRB -- Load and Store Word or Unsigned Byte - Register offset (U=0) */
EXTERN_C void slv6_X_LDRB_M2_RegOff_U0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.60--A5.1.4
 * RSB -- Data processing operands - Register (S=1) */
EXTERN_C void slv6_X_RSB_M1_Reg_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.60--A5.1.4
 * RSB -- Data processing operands - Register (S=0) */
EXTERN_C void slv6_X_RSB_M1_Reg_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.6--A5.1.3
 * BIC -- Data processing operands - Immediate (S=1) */
EXTERN_C void slv6_X_BIC_M1_Imm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.6--A5.1.3
 * BIC -- Data processing operands - Immediate (S=0) */
EXTERN_C void slv6_X_BIC_M1_Imm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.41--A5.1.3
 * MVN -- Data processing operands - Immediate (S=1) */
EXTERN_C void slv6_X_MVN_M1_Imm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.41--A5.1.3
 * MVN -- Data processing operands - Immediate (S=0) */
EXTERN_C void slv6_X_MVN_M1_Imm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.42--A5.1.7
 * ORR -- Data processing operands - Logical shift right by immediate (S=1) */
EXTERN_C void slv6_X_ORR_M1_LSRImm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.42--A5.1.7
 * ORR -- Data processing operands - Logical shift right by immediate (S=0) */
EXTERN_C void slv6_X_ORR_M1_LSRImm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.18--A5.1.7
 * EOR -- Data processing operands - Logical shift right by immediate (S=1) */
EXTERN_C void slv6_X_EOR_M1_LSRImm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.18--A5.1.7
 * EOR -- Data processing operands - Logical shift right by immediate (S=0) */
EXTERN_C void slv6_X_EOR_M1_LSRImm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.23--A5.2.3
 * LDR -- Load and Store Word or Unsigned Byte - Register offset (U=1) */
EXTERN_C void slv6_X_LDR_M2_RegOff_U1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.23--A5.2.3
 * LDR -- Load and Store Word or Unsigned Byte - Register offset (U=0) */
EXTERN_C void slv6_X_LDR_M2_RegOff_U0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.35--A5.1.8
 * MOV -- Data processing operands - Logical shift right by register (S=1) */
EXTERN_C void slv6_X_MOV_M1_LSRReg_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.35--A5.1.8
 * MOV -- Data processing operands - Logical shift right by register (S=0) */
EXTERN_C void slv6_X_MOV_M1_LSRReg_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.100--A5.2.3
 * STRB -- Load and Store Word or Unsigned Byte - Register offset (U=1) */
EXTERN_C void slv6_X_STRB_M2_RegOff_U1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.100--A5.2.3
 * STRB -- Load and Store Word or Unsigned Byte - Register offset (U=0) */
EXTERN_C void slv6_X_STRB_M2_RegOff_U0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.99--A5.2.4
 * STR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) */
EXTERN_C void slv6_X_STR_M2_ScRegOff_U1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.99--A5.2.4
 * STR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) */
EXTERN_C void slv6_X_STR_M2_ScRegOff_U0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.14--A5.1.4
 * CMN -- Data processing operands - Register */
EXTERN_C void slv6_X_CMN_M1_Reg(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.99--A5.2.9
 * STR -- Load and Store Word or Unsigned Byte - Register post indexed (U=1) */
EXTERN_C void slv6_X_STR_M2_Reg_postInd_U1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.99--A5.2.9
 * STR -- Load and Store Word or Unsigned Byte - Register post indexed (U=0) */
EXTERN_C void slv6_X_STR_M2_Reg_postInd_U0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.99--A5.2.3
 * STR -- Load and Store Word or Unsigned Byte - Register offset (U=1) */
EXTERN_C void slv6_X_STR_M2_RegOff_U1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.99--A5.2.3
 * STR -- Load and Store Word or Unsigned Byte - Register offset (U=0) */
EXTERN_C void slv6_X_STR_M2_RegOff_U0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.18--A5.1.5
 * EOR -- Data processing operands - Logical shift left by immediate (S=1) */
EXTERN_C void slv6_X_EOR_M1_LSLImm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.18--A5.1.5
 * EOR -- Data processing operands - Logical shift left by immediate (S=0) */
EXTERN_C void slv6_X_EOR_M1_LSLImm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.60--A5.1.3
 * RSB -- Data processing operands - Immediate (S=1) */
EXTERN_C void slv6_X_RSB_M1_Imm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.60--A5.1.3
 * RSB -- Data processing operands - Immediate (S=0) */
EXTERN_C void slv6_X_RSB_M1_Imm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.35--A5.1.9
 * MOV -- Data processing operands - Arithmetic shift right by immediate (S=1) */
EXTERN_C void slv6_X_MOV_M1_ASRImm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.35--A5.1.9
 * MOV -- Data processing operands - Arithmetic shift right by immediate (S=0) */
EXTERN_C void slv6_X_MOV_M1_ASRImm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.3--A5.1.11
 * ADD -- Data processing operands - Rotate right by immediate (S=1) */
EXTERN_C void slv6_X_ADD_M1_RRImm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.3--A5.1.11
 * ADD -- Data processing operands - Rotate right by immediate (S=0) */
EXTERN_C void slv6_X_ADD_M1_RRImm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.60--A5.1.5
 * RSB -- Data processing operands - Logical shift left by immediate (S=1) */
EXTERN_C void slv6_X_RSB_M1_LSLImm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.60--A5.1.5
 * RSB -- Data processing operands - Logical shift left by immediate (S=0) */
EXTERN_C void slv6_X_RSB_M1_LSLImm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.100--A5.2.8
 * STRB -- Load and Store Word or Unsigned Byte - Immediate post indexed */
EXTERN_C void slv6_X_STRB_M2_Imm_postInd(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12);

/* A4.1.97--A5.4.2
 * STM (1) -- Load and Store Multiple - Increment after (W=1) */
EXTERN_C void slv6_X_STM1_M4_IA_W1(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.97--A5.4.2
 * STM (1) -- Load and Store Multiple - Increment after (W=0) */
EXTERN_C void slv6_X_STM1_M4_IA_W0(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.117--A5.1.3
 * TST -- Data processing operands - Immediate */
EXTERN_C void slv6_X_TST_M1_Imm(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.97--A5.4.5
 * STM (1) -- Load and Store Multiple - Decrement before (W=1) */
EXTERN_C void slv6_X_STM1_M4_DB_W1(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.97--A5.4.5
 * STM (1) -- Load and Store Multiple - Decrement before (W=0) */
EXTERN_C void slv6_X_STM1_M4_DB_W0(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.41--A5.1.4
 * MVN -- Data processing operands - Register (S=1) */
EXTERN_C void slv6_X_MVN_M1_Reg_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const SLv6_Condition cond);

/* A4.1.41--A5.1.4
 * MVN -- Data processing operands - Register (S=0) */
EXTERN_C void slv6_X_MVN_M1_Reg_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const SLv6_Condition cond);

/* A4.1.97--A5.4.3
 * STM (1) -- Load and Store Multiple - Increment before (W=1) */
EXTERN_C void slv6_X_STM1_M4_IB_W1(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.97--A5.4.3
 * STM (1) -- Load and Store Multiple - Increment before (W=0) */
EXTERN_C void slv6_X_STM1_M4_IB_W0(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.3--A5.1.7
 * ADD -- Data processing operands - Logical shift right by immediate (S=1) */
EXTERN_C void slv6_X_ADD_M1_LSRImm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.3--A5.1.7
 * ADD -- Data processing operands - Logical shift right by immediate (S=0) */
EXTERN_C void slv6_X_ADD_M1_LSRImm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.99--A5.2.8
 * STR -- Load and Store Word or Unsigned Byte - Immediate post indexed */
EXTERN_C void slv6_X_STR_M2_Imm_postInd(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12);

/* A4.1.24--A5.2.4
 * LDRB -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) */
EXTERN_C void slv6_X_LDRB_M2_ScRegOff_U1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.24--A5.2.4
 * LDRB -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) */
EXTERN_C void slv6_X_LDRB_M2_ScRegOff_U0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.106--A5.1.5
 * SUB -- Data processing operands - Logical shift left by immediate (S=1) */
EXTERN_C void slv6_X_SUB_M1_LSLImm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.106--A5.1.5
 * SUB -- Data processing operands - Logical shift left by immediate (S=0) */
EXTERN_C void slv6_X_SUB_M1_LSLImm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.20--A5.4.3
 * LDM (1) -- Load and Store Multiple - Increment before (W=1) */
EXTERN_C void slv6_X_LDM1_M4_IB_W1(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.20--A5.4.3
 * LDM (1) -- Load and Store Multiple - Increment before (W=0) */
EXTERN_C void slv6_X_LDM1_M4_IB_W0(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.28--A5.3.2
 * LDRH -- Miscellaneous Loads and Stores - Immediate offset (U=1) */
EXTERN_C void slv6_X_LDRH_M3_ImmOff_U1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond);

/* A4.1.28--A5.3.2
 * LDRH -- Miscellaneous Loads and Stores - Immediate offset (U=0) */
EXTERN_C void slv6_X_LDRH_M3_ImmOff_U0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond);

/* A4.1.23--A5.2.5
 * LDR -- Load and Store Word or Unsigned Byte - Immediate pre indexed */
EXTERN_C void slv6_X_LDR_M2_Imm_preInd(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12);

/* A4.1.87
 * SMULL (S=1) */
EXTERN_C void slv6_X_SMULL_S1(struct SLv6_Processor*,
    const uint8_t dHi,
    const uint8_t dLo,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.87
 * SMULL (S=0) */
EXTERN_C void slv6_X_SMULL_S0(struct SLv6_Processor*,
    const uint8_t dHi,
    const uint8_t dLo,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.60--A5.1.9
 * RSB -- Data processing operands - Arithmetic shift right by immediate (S=1) */
EXTERN_C void slv6_X_RSB_M1_ASRImm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.60--A5.1.9
 * RSB -- Data processing operands - Arithmetic shift right by immediate (S=0) */
EXTERN_C void slv6_X_RSB_M1_ASRImm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.117--A5.1.4
 * TST -- Data processing operands - Register */
EXTERN_C void slv6_X_TST_M1_Reg(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.18--A5.1.3
 * EOR -- Data processing operands - Immediate (S=1) */
EXTERN_C void slv6_X_EOR_M1_Imm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.18--A5.1.3
 * EOR -- Data processing operands - Immediate (S=0) */
EXTERN_C void slv6_X_EOR_M1_Imm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.42--A5.1.9
 * ORR -- Data processing operands - Arithmetic shift right by immediate (S=1) */
EXTERN_C void slv6_X_ORR_M1_ASRImm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.42--A5.1.9
 * ORR -- Data processing operands - Arithmetic shift right by immediate (S=0) */
EXTERN_C void slv6_X_ORR_M1_ASRImm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.42--A5.1.3
 * ORR -- Data processing operands - Immediate (S=1) */
EXTERN_C void slv6_X_ORR_M1_Imm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.42--A5.1.3
 * ORR -- Data processing operands - Immediate (S=0) */
EXTERN_C void slv6_X_ORR_M1_Imm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.106--A5.1.9
 * SUB -- Data processing operands - Arithmetic shift right by immediate (S=1) */
EXTERN_C void slv6_X_SUB_M1_ASRImm_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.106--A5.1.9
 * SUB -- Data processing operands - Arithmetic shift right by immediate (S=0) */
EXTERN_C void slv6_X_SUB_M1_ASRImm_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.35--A5.1.6
 * MOV -- Data processing operands - Logical shift left by register (S=1) */
EXTERN_C void slv6_X_MOV_M1_LSLReg_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.35--A5.1.6
 * MOV -- Data processing operands - Logical shift left by register (S=0) */
EXTERN_C void slv6_X_MOV_M1_LSLReg_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.40
 * MUL (S=1) */
EXTERN_C void slv6_X_MUL_S1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.40
 * MUL (S=0) */
EXTERN_C void slv6_X_MUL_S0(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.14--A5.1.3
 * CMN -- Data processing operands - Immediate */
EXTERN_C void slv6_X_CMN_M1_Imm(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.2--A5.1.3
 * ADC -- Data processing operands - Immediate */
EXTERN_C void slv6_X_ADC_M1_Imm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.2--A5.1.5
 * ADC -- Data processing operands - Logical shift left by immediate */
EXTERN_C void slv6_X_ADC_M1_LSLImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.2--A5.1.6
 * ADC -- Data processing operands - Logical shift left by register */
EXTERN_C void slv6_X_ADC_M1_LSLReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.2--A5.1.7
 * ADC -- Data processing operands - Logical shift right by immediate */
EXTERN_C void slv6_X_ADC_M1_LSRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.2--A5.1.8
 * ADC -- Data processing operands - Logical shift right by register */
EXTERN_C void slv6_X_ADC_M1_LSRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.2--A5.1.9
 * ADC -- Data processing operands - Arithmetic shift right by immediate */
EXTERN_C void slv6_X_ADC_M1_ASRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.2--A5.1.10
 * ADC -- Data processing operands - Arithmetic shift right by register */
EXTERN_C void slv6_X_ADC_M1_ASRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.2--A5.1.11
 * ADC -- Data processing operands - Rotate right by immediate */
EXTERN_C void slv6_X_ADC_M1_RRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.2--A5.1.12
 * ADC -- Data processing operands - Rotate right by register */
EXTERN_C void slv6_X_ADC_M1_RRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.2--A5.1.13
 * ADC -- Data processing operands - Rotate right with extend */
EXTERN_C void slv6_X_ADC_M1_RRE(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.3--A5.1.6
 * ADD -- Data processing operands - Logical shift left by register */
EXTERN_C void slv6_X_ADD_M1_LSLReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.3--A5.1.8
 * ADD -- Data processing operands - Logical shift right by register */
EXTERN_C void slv6_X_ADD_M1_LSRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.3--A5.1.9
 * ADD -- Data processing operands - Arithmetic shift right by immediate */
EXTERN_C void slv6_X_ADD_M1_ASRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.3--A5.1.10
 * ADD -- Data processing operands - Arithmetic shift right by register */
EXTERN_C void slv6_X_ADD_M1_ASRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.3--A5.1.12
 * ADD -- Data processing operands - Rotate right by register */
EXTERN_C void slv6_X_ADD_M1_RRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.3--A5.1.13
 * ADD -- Data processing operands - Rotate right with extend */
EXTERN_C void slv6_X_ADD_M1_RRE(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.4--A5.1.5
 * AND -- Data processing operands - Logical shift left by immediate */
EXTERN_C void slv6_X_AND_M1_LSLImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.4--A5.1.6
 * AND -- Data processing operands - Logical shift left by register */
EXTERN_C void slv6_X_AND_M1_LSLReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.4--A5.1.7
 * AND -- Data processing operands - Logical shift right by immediate */
EXTERN_C void slv6_X_AND_M1_LSRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.4--A5.1.8
 * AND -- Data processing operands - Logical shift right by register */
EXTERN_C void slv6_X_AND_M1_LSRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.4--A5.1.9
 * AND -- Data processing operands - Arithmetic shift right by immediate */
EXTERN_C void slv6_X_AND_M1_ASRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.4--A5.1.10
 * AND -- Data processing operands - Arithmetic shift right by register */
EXTERN_C void slv6_X_AND_M1_ASRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.4--A5.1.11
 * AND -- Data processing operands - Rotate right by immediate */
EXTERN_C void slv6_X_AND_M1_RRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.4--A5.1.12
 * AND -- Data processing operands - Rotate right by register */
EXTERN_C void slv6_X_AND_M1_RRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.4--A5.1.13
 * AND -- Data processing operands - Rotate right with extend */
EXTERN_C void slv6_X_AND_M1_RRE(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.6--A5.1.4
 * BIC -- Data processing operands - Register */
EXTERN_C void slv6_X_BIC_M1_Reg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.6--A5.1.5
 * BIC -- Data processing operands - Logical shift left by immediate */
EXTERN_C void slv6_X_BIC_M1_LSLImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.6--A5.1.6
 * BIC -- Data processing operands - Logical shift left by register */
EXTERN_C void slv6_X_BIC_M1_LSLReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.6--A5.1.7
 * BIC -- Data processing operands - Logical shift right by immediate */
EXTERN_C void slv6_X_BIC_M1_LSRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.6--A5.1.8
 * BIC -- Data processing operands - Logical shift right by register */
EXTERN_C void slv6_X_BIC_M1_LSRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.6--A5.1.9
 * BIC -- Data processing operands - Arithmetic shift right by immediate */
EXTERN_C void slv6_X_BIC_M1_ASRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.6--A5.1.10
 * BIC -- Data processing operands - Arithmetic shift right by register */
EXTERN_C void slv6_X_BIC_M1_ASRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.6--A5.1.11
 * BIC -- Data processing operands - Rotate right by immediate */
EXTERN_C void slv6_X_BIC_M1_RRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.6--A5.1.12
 * BIC -- Data processing operands - Rotate right by register */
EXTERN_C void slv6_X_BIC_M1_RRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.6--A5.1.13
 * BIC -- Data processing operands - Rotate right with extend */
EXTERN_C void slv6_X_BIC_M1_RRE(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.7
 * BKPT */
EXTERN_C void slv6_X_BKPT(struct SLv6_Processor*);

/* A4.1.8
 * BLX (1) */
EXTERN_C void slv6_X_BLX1(struct SLv6_Processor*,
    const uint32_t pc_offset_h);

/* A4.1.9
 * BLX (2) */
EXTERN_C void slv6_X_BLX2(struct SLv6_Processor*,
    const uint8_t m,
    const SLv6_Condition cond);

/* A4.1.11
 * BXJ */
EXTERN_C void slv6_X_BXJ(struct SLv6_Processor*,
    const uint8_t m,
    const SLv6_Condition cond);

/* A4.1.12
 * CDP */
EXTERN_C void slv6_X_CDP(struct SLv6_Processor*,
    const uint8_t cp_num,
    const SLv6_Condition cond);

/* A4.1.13
 * CLZ */
EXTERN_C void slv6_X_CLZ(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const SLv6_Condition cond);

/* A4.1.14--A5.1.5
 * CMN -- Data processing operands - Logical shift left by immediate */
EXTERN_C void slv6_X_CMN_M1_LSLImm(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.14--A5.1.6
 * CMN -- Data processing operands - Logical shift left by register */
EXTERN_C void slv6_X_CMN_M1_LSLReg(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.14--A5.1.7
 * CMN -- Data processing operands - Logical shift right by immediate */
EXTERN_C void slv6_X_CMN_M1_LSRImm(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.14--A5.1.8
 * CMN -- Data processing operands - Logical shift right by register */
EXTERN_C void slv6_X_CMN_M1_LSRReg(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.14--A5.1.9
 * CMN -- Data processing operands - Arithmetic shift right by immediate */
EXTERN_C void slv6_X_CMN_M1_ASRImm(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.14--A5.1.10
 * CMN -- Data processing operands - Arithmetic shift right by register */
EXTERN_C void slv6_X_CMN_M1_ASRReg(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.14--A5.1.11
 * CMN -- Data processing operands - Rotate right by immediate */
EXTERN_C void slv6_X_CMN_M1_RRImm(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.14--A5.1.12
 * CMN -- Data processing operands - Rotate right by register */
EXTERN_C void slv6_X_CMN_M1_RRReg(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.14--A5.1.13
 * CMN -- Data processing operands - Rotate right with extend */
EXTERN_C void slv6_X_CMN_M1_RRE(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.15--A5.1.5
 * CMP -- Data processing operands - Logical shift left by immediate */
EXTERN_C void slv6_X_CMP_M1_LSLImm(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.15--A5.1.6
 * CMP -- Data processing operands - Logical shift left by register */
EXTERN_C void slv6_X_CMP_M1_LSLReg(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.15--A5.1.7
 * CMP -- Data processing operands - Logical shift right by immediate */
EXTERN_C void slv6_X_CMP_M1_LSRImm(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.15--A5.1.8
 * CMP -- Data processing operands - Logical shift right by register */
EXTERN_C void slv6_X_CMP_M1_LSRReg(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.15--A5.1.9
 * CMP -- Data processing operands - Arithmetic shift right by immediate */
EXTERN_C void slv6_X_CMP_M1_ASRImm(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.15--A5.1.10
 * CMP -- Data processing operands - Arithmetic shift right by register */
EXTERN_C void slv6_X_CMP_M1_ASRReg(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.15--A5.1.11
 * CMP -- Data processing operands - Rotate right by immediate */
EXTERN_C void slv6_X_CMP_M1_RRImm(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.15--A5.1.12
 * CMP -- Data processing operands - Rotate right by register */
EXTERN_C void slv6_X_CMP_M1_RRReg(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.15--A5.1.13
 * CMP -- Data processing operands - Rotate right with extend */
EXTERN_C void slv6_X_CMP_M1_RRE(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.16
 * CPS */
EXTERN_C void slv6_X_CPS(struct SLv6_Processor*,
    const bool A,
    const bool F,
    const bool I,
    const uint8_t imod,
    const bool mmod,
    const SLv6_Mode mode);

/* A4.1.18--A5.1.6
 * EOR -- Data processing operands - Logical shift left by register */
EXTERN_C void slv6_X_EOR_M1_LSLReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.18--A5.1.8
 * EOR -- Data processing operands - Logical shift right by register */
EXTERN_C void slv6_X_EOR_M1_LSRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.18--A5.1.9
 * EOR -- Data processing operands - Arithmetic shift right by immediate */
EXTERN_C void slv6_X_EOR_M1_ASRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.18--A5.1.10
 * EOR -- Data processing operands - Arithmetic shift right by register */
EXTERN_C void slv6_X_EOR_M1_ASRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.18--A5.1.12
 * EOR -- Data processing operands - Rotate right by register */
EXTERN_C void slv6_X_EOR_M1_RRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.18--A5.1.13
 * EOR -- Data processing operands - Rotate right with extend */
EXTERN_C void slv6_X_EOR_M1_RRE(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.19--A5.5.2
 * LDC -- Load and Store Coprocessor - Immediate offset */
EXTERN_C void slv6_X_LDC_M5_ImmOff(struct SLv6_Processor*);

/* A4.1.19--A5.5.3
 * LDC -- Load and Store Coprocessor - Immediate pre indexed */
EXTERN_C void slv6_X_LDC_M5_Imm_preInd(struct SLv6_Processor*);

/* A4.1.19--A5.5.4
 * LDC -- Load and Store Coprocessor - Immediate post indexed */
EXTERN_C void slv6_X_LDC_M5_Imm_postInd(struct SLv6_Processor*);

/* A4.1.19--A5.5.5
 * LDC -- Load and Store Coprocessor - Unindexed */
EXTERN_C void slv6_X_LDC_M5_U(struct SLv6_Processor*);

/* A4.1.20--A5.4.4
 * LDM (1) -- Load and Store Multiple - Decrement after */
EXTERN_C void slv6_X_LDM1_M4_DA(struct SLv6_Processor*,
    const bool W,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.20--A5.4.5
 * LDM (1) -- Load and Store Multiple - Decrement before */
EXTERN_C void slv6_X_LDM1_M4_DB(struct SLv6_Processor*,
    const bool W,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.21--A5.4.2
 * LDM (2) -- Load and Store Multiple - Increment after */
EXTERN_C void slv6_X_LDM2_M4_IA(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.21--A5.4.3
 * LDM (2) -- Load and Store Multiple - Increment before */
EXTERN_C void slv6_X_LDM2_M4_IB(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.21--A5.4.4
 * LDM (2) -- Load and Store Multiple - Decrement after */
EXTERN_C void slv6_X_LDM2_M4_DA(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.21--A5.4.5
 * LDM (2) -- Load and Store Multiple - Decrement before */
EXTERN_C void slv6_X_LDM2_M4_DB(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.22--A5.4.2
 * LDM (3) -- Load and Store Multiple - Increment after */
EXTERN_C void slv6_X_LDM3_M4_IA(struct SLv6_Processor*,
    const bool W,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.22--A5.4.3
 * LDM (3) -- Load and Store Multiple - Increment before */
EXTERN_C void slv6_X_LDM3_M4_IB(struct SLv6_Processor*,
    const bool W,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.22--A5.4.4
 * LDM (3) -- Load and Store Multiple - Decrement after */
EXTERN_C void slv6_X_LDM3_M4_DA(struct SLv6_Processor*,
    const bool W,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.22--A5.4.5
 * LDM (3) -- Load and Store Multiple - Decrement before */
EXTERN_C void slv6_X_LDM3_M4_DB(struct SLv6_Processor*,
    const bool W,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.23--A5.2.6
 * LDR -- Load and Store Word or Unsigned Byte - Register pre indexed */
EXTERN_C void slv6_X_LDR_M2_Reg_preInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.23--A5.2.7
 * LDR -- Load and Store Word or Unsigned Byte - Scaled register pre indexed */
EXTERN_C void slv6_X_LDR_M2_ScReg_preInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.23--A5.2.9
 * LDR -- Load and Store Word or Unsigned Byte - Register post indexed */
EXTERN_C void slv6_X_LDR_M2_Reg_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.23--A5.2.10
 * LDR -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
EXTERN_C void slv6_X_LDR_M2_ScReg_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.24--A5.2.5
 * LDRB -- Load and Store Word or Unsigned Byte - Immediate pre indexed */
EXTERN_C void slv6_X_LDRB_M2_Imm_preInd(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12);

/* A4.1.24--A5.2.6
 * LDRB -- Load and Store Word or Unsigned Byte - Register pre indexed */
EXTERN_C void slv6_X_LDRB_M2_Reg_preInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.24--A5.2.7
 * LDRB -- Load and Store Word or Unsigned Byte - Scaled register pre indexed */
EXTERN_C void slv6_X_LDRB_M2_ScReg_preInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.24--A5.2.8
 * LDRB -- Load and Store Word or Unsigned Byte - Immediate post indexed */
EXTERN_C void slv6_X_LDRB_M2_Imm_postInd(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12);

/* A4.1.24--A5.2.9
 * LDRB -- Load and Store Word or Unsigned Byte - Register post indexed */
EXTERN_C void slv6_X_LDRB_M2_Reg_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.24--A5.2.10
 * LDRB -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
EXTERN_C void slv6_X_LDRB_M2_ScReg_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.25--A5.2.8
 * LDRBT -- Load and Store Word or Unsigned Byte - Immediate post indexed */
EXTERN_C void slv6_X_LDRBT_M2_Imm_postInd(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12);

/* A4.1.25--A5.2.9
 * LDRBT -- Load and Store Word or Unsigned Byte - Register post indexed */
EXTERN_C void slv6_X_LDRBT_M2_Reg_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.25--A5.2.10
 * LDRBT -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
EXTERN_C void slv6_X_LDRBT_M2_ScReg_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.26--A5.3.2
 * LDRD -- Miscellaneous Loads and Stores - Immediate offset */
EXTERN_C void slv6_X_LDRD_M3_ImmOff(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond);

/* A4.1.26--A5.3.3
 * LDRD -- Miscellaneous Loads and Stores - Register offset */
EXTERN_C void slv6_X_LDRD_M3_RegOff(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.26--A5.3.4
 * LDRD -- Miscellaneous Loads and Stores - Immediate pre indexed */
EXTERN_C void slv6_X_LDRD_M3_Imm_preInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond);

/* A4.1.26--A5.3.5
 * LDRD -- Miscellaneous Loads and Stores - Register pre indexed */
EXTERN_C void slv6_X_LDRD_M3_Reg_preInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.26--A5.3.6
 * LDRD -- Miscellaneous Loads and Stores - Immediate post indexed */
EXTERN_C void slv6_X_LDRD_M3_Imm_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond);

/* A4.1.26--A5.3.7
 * LDRD -- Miscellaneous Loads and Stores - Register post indexed */
EXTERN_C void slv6_X_LDRD_M3_Reg_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.27
 * LDREX */
EXTERN_C void slv6_X_LDREX(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.28--A5.3.3
 * LDRH -- Miscellaneous Loads and Stores - Register offset */
EXTERN_C void slv6_X_LDRH_M3_RegOff(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.28--A5.3.4
 * LDRH -- Miscellaneous Loads and Stores - Immediate pre indexed */
EXTERN_C void slv6_X_LDRH_M3_Imm_preInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond);

/* A4.1.28--A5.3.5
 * LDRH -- Miscellaneous Loads and Stores - Register pre indexed */
EXTERN_C void slv6_X_LDRH_M3_Reg_preInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.28--A5.3.6
 * LDRH -- Miscellaneous Loads and Stores - Immediate post indexed */
EXTERN_C void slv6_X_LDRH_M3_Imm_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond);

/* A4.1.28--A5.3.7
 * LDRH -- Miscellaneous Loads and Stores - Register post indexed */
EXTERN_C void slv6_X_LDRH_M3_Reg_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.29--A5.3.2
 * LDRSB -- Miscellaneous Loads and Stores - Immediate offset */
EXTERN_C void slv6_X_LDRSB_M3_ImmOff(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond);

/* A4.1.29--A5.3.3
 * LDRSB -- Miscellaneous Loads and Stores - Register offset */
EXTERN_C void slv6_X_LDRSB_M3_RegOff(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.29--A5.3.4
 * LDRSB -- Miscellaneous Loads and Stores - Immediate pre indexed */
EXTERN_C void slv6_X_LDRSB_M3_Imm_preInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond);

/* A4.1.29--A5.3.5
 * LDRSB -- Miscellaneous Loads and Stores - Register pre indexed */
EXTERN_C void slv6_X_LDRSB_M3_Reg_preInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.29--A5.3.6
 * LDRSB -- Miscellaneous Loads and Stores - Immediate post indexed */
EXTERN_C void slv6_X_LDRSB_M3_Imm_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond);

/* A4.1.29--A5.3.7
 * LDRSB -- Miscellaneous Loads and Stores - Register post indexed */
EXTERN_C void slv6_X_LDRSB_M3_Reg_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.30--A5.3.2
 * LDRSH -- Miscellaneous Loads and Stores - Immediate offset */
EXTERN_C void slv6_X_LDRSH_M3_ImmOff(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond);

/* A4.1.30--A5.3.3
 * LDRSH -- Miscellaneous Loads and Stores - Register offset */
EXTERN_C void slv6_X_LDRSH_M3_RegOff(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.30--A5.3.4
 * LDRSH -- Miscellaneous Loads and Stores - Immediate pre indexed */
EXTERN_C void slv6_X_LDRSH_M3_Imm_preInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond);

/* A4.1.30--A5.3.5
 * LDRSH -- Miscellaneous Loads and Stores - Register pre indexed */
EXTERN_C void slv6_X_LDRSH_M3_Reg_preInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.30--A5.3.6
 * LDRSH -- Miscellaneous Loads and Stores - Immediate post indexed */
EXTERN_C void slv6_X_LDRSH_M3_Imm_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond);

/* A4.1.30--A5.3.7
 * LDRSH -- Miscellaneous Loads and Stores - Register post indexed */
EXTERN_C void slv6_X_LDRSH_M3_Reg_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.31--A5.2.8
 * LDRT -- Load and Store Word or Unsigned Byte - Immediate post indexed */
EXTERN_C void slv6_X_LDRT_M2_Imm_postInd(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12);

/* A4.1.31--A5.2.9
 * LDRT -- Load and Store Word or Unsigned Byte - Register post indexed */
EXTERN_C void slv6_X_LDRT_M2_Reg_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.31--A5.2.10
 * LDRT -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
EXTERN_C void slv6_X_LDRT_M2_ScReg_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.32
 * MCR */
EXTERN_C void slv6_X_MCR(struct SLv6_Processor*,
    const uint8_t CRm,
    const uint8_t CRn,
    const uint8_t cp_num,
    const uint8_t d,
    const uint8_t opcode_1,
    const uint8_t opcode_2,
    const SLv6_Condition cond);

/* A4.1.33
 * MCRR */
EXTERN_C void slv6_X_MCRR(struct SLv6_Processor*,
    const uint8_t cp_num,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.34
 * MLA */
EXTERN_C void slv6_X_MLA(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.35--A5.1.4
 * MOV -- Data processing operands - Register */
EXTERN_C void slv6_X_MOV_M1_Reg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const SLv6_Condition cond);

/* A4.1.35--A5.1.10
 * MOV -- Data processing operands - Arithmetic shift right by register */
EXTERN_C void slv6_X_MOV_M1_ASRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.35--A5.1.12
 * MOV -- Data processing operands - Rotate right by register */
EXTERN_C void slv6_X_MOV_M1_RRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.35--A5.1.13
 * MOV -- Data processing operands - Rotate right with extend */
EXTERN_C void slv6_X_MOV_M1_RRE(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const SLv6_Condition cond);

/* A4.1.36
 * MRC */
EXTERN_C void slv6_X_MRC(struct SLv6_Processor*,
    const uint8_t CRm,
    const uint8_t CRn,
    const uint8_t cp_num,
    const uint8_t d,
    const uint8_t opcode_1,
    const uint8_t opcode_2,
    const SLv6_Condition cond);

/* A4.1.37
 * MRRC */
EXTERN_C void slv6_X_MRRC(struct SLv6_Processor*,
    const uint8_t cp_num,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.38
 * MRS */
EXTERN_C void slv6_X_MRS(struct SLv6_Processor*,
    const bool R,
    const uint8_t d,
    const SLv6_Condition cond);

/* A4.1.39
 * MSRimm */
EXTERN_C void slv6_X_MSRimm(struct SLv6_Processor*,
    const bool R,
    const uint8_t field_mask,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.39
 * MSRreg */
EXTERN_C void slv6_X_MSRreg(struct SLv6_Processor*,
    const bool R,
    const uint8_t field_mask,
    const uint8_t m,
    const SLv6_Condition cond);

/* A4.1.41--A5.1.5
 * MVN -- Data processing operands - Logical shift left by immediate */
EXTERN_C void slv6_X_MVN_M1_LSLImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.41--A5.1.6
 * MVN -- Data processing operands - Logical shift left by register */
EXTERN_C void slv6_X_MVN_M1_LSLReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.41--A5.1.7
 * MVN -- Data processing operands - Logical shift right by immediate */
EXTERN_C void slv6_X_MVN_M1_LSRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.41--A5.1.8
 * MVN -- Data processing operands - Logical shift right by register */
EXTERN_C void slv6_X_MVN_M1_LSRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.41--A5.1.9
 * MVN -- Data processing operands - Arithmetic shift right by immediate */
EXTERN_C void slv6_X_MVN_M1_ASRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.41--A5.1.10
 * MVN -- Data processing operands - Arithmetic shift right by register */
EXTERN_C void slv6_X_MVN_M1_ASRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.41--A5.1.11
 * MVN -- Data processing operands - Rotate right by immediate */
EXTERN_C void slv6_X_MVN_M1_RRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.41--A5.1.12
 * MVN -- Data processing operands - Rotate right by register */
EXTERN_C void slv6_X_MVN_M1_RRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.41--A5.1.13
 * MVN -- Data processing operands - Rotate right with extend */
EXTERN_C void slv6_X_MVN_M1_RRE(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const SLv6_Condition cond);

/* A4.1.42--A5.1.6
 * ORR -- Data processing operands - Logical shift left by register */
EXTERN_C void slv6_X_ORR_M1_LSLReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.42--A5.1.8
 * ORR -- Data processing operands - Logical shift right by register */
EXTERN_C void slv6_X_ORR_M1_LSRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.42--A5.1.10
 * ORR -- Data processing operands - Arithmetic shift right by register */
EXTERN_C void slv6_X_ORR_M1_ASRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.42--A5.1.11
 * ORR -- Data processing operands - Rotate right by immediate */
EXTERN_C void slv6_X_ORR_M1_RRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.42--A5.1.12
 * ORR -- Data processing operands - Rotate right by register */
EXTERN_C void slv6_X_ORR_M1_RRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.42--A5.1.13
 * ORR -- Data processing operands - Rotate right with extend */
EXTERN_C void slv6_X_ORR_M1_RRE(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.43
 * PKHBT */
EXTERN_C void slv6_X_PKHBT(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.44
 * PKHTB */
EXTERN_C void slv6_X_PKHTB(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.45--A5.2.2
 * PLD -- Load and Store Word or Unsigned Byte - Immediate offset */
EXTERN_C void slv6_X_PLD_M2_ImmOff(struct SLv6_Processor*,
    const uint8_t n,
    const uint32_t signed_offset_12);

/* A4.1.45--A5.2.3
 * PLD -- Load and Store Word or Unsigned Byte - Register offset */
EXTERN_C void slv6_X_PLD_M2_RegOff(struct SLv6_Processor*,
    const bool U,
    const uint8_t m,
    const uint8_t n);

/* A4.1.45--A5.2.4
 * PLD -- Load and Store Word or Unsigned Byte - Scaled register offset */
EXTERN_C void slv6_X_PLD_M2_ScRegOff(struct SLv6_Processor*,
    const bool U,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm);

/* A4.1.46
 * QADD */
EXTERN_C void slv6_X_QADD(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.47
 * QADD16 */
EXTERN_C void slv6_X_QADD16(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.48
 * QADD8 */
EXTERN_C void slv6_X_QADD8(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.49
 * QADDSUBX */
EXTERN_C void slv6_X_QADDSUBX(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.50
 * QDADD */
EXTERN_C void slv6_X_QDADD(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.51
 * QDSUB */
EXTERN_C void slv6_X_QDSUB(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.52
 * QSUB */
EXTERN_C void slv6_X_QSUB(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.53
 * QSUB16 */
EXTERN_C void slv6_X_QSUB16(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.54
 * QSUB8 */
EXTERN_C void slv6_X_QSUB8(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.55
 * QSUBADDX */
EXTERN_C void slv6_X_QSUBADDX(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.56
 * REV */
EXTERN_C void slv6_X_REV(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const SLv6_Condition cond);

/* A4.1.57
 * REV16 */
EXTERN_C void slv6_X_REV16(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const SLv6_Condition cond);

/* A4.1.58
 * REVSH */
EXTERN_C void slv6_X_REVSH(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const SLv6_Condition cond);

/* A4.1.59--A5.4.2
 * RFE -- Load and Store Multiple - Increment after */
EXTERN_C void slv6_X_RFE_M4_IA(struct SLv6_Processor*,
    const bool W,
    const uint8_t n);

/* A4.1.59--A5.4.3
 * RFE -- Load and Store Multiple - Increment before */
EXTERN_C void slv6_X_RFE_M4_IB(struct SLv6_Processor*,
    const bool W,
    const uint8_t n);

/* A4.1.59--A5.4.4
 * RFE -- Load and Store Multiple - Decrement after */
EXTERN_C void slv6_X_RFE_M4_DA(struct SLv6_Processor*,
    const bool W,
    const uint8_t n);

/* A4.1.59--A5.4.5
 * RFE -- Load and Store Multiple - Decrement before */
EXTERN_C void slv6_X_RFE_M4_DB(struct SLv6_Processor*,
    const bool W,
    const uint8_t n);

/* A4.1.60--A5.1.6
 * RSB -- Data processing operands - Logical shift left by register */
EXTERN_C void slv6_X_RSB_M1_LSLReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.60--A5.1.7
 * RSB -- Data processing operands - Logical shift right by immediate */
EXTERN_C void slv6_X_RSB_M1_LSRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.60--A5.1.8
 * RSB -- Data processing operands - Logical shift right by register */
EXTERN_C void slv6_X_RSB_M1_LSRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.60--A5.1.10
 * RSB -- Data processing operands - Arithmetic shift right by register */
EXTERN_C void slv6_X_RSB_M1_ASRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.60--A5.1.11
 * RSB -- Data processing operands - Rotate right by immediate */
EXTERN_C void slv6_X_RSB_M1_RRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.60--A5.1.12
 * RSB -- Data processing operands - Rotate right by register */
EXTERN_C void slv6_X_RSB_M1_RRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.60--A5.1.13
 * RSB -- Data processing operands - Rotate right with extend */
EXTERN_C void slv6_X_RSB_M1_RRE(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.61--A5.1.3
 * RSC -- Data processing operands - Immediate */
EXTERN_C void slv6_X_RSC_M1_Imm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.61--A5.1.4
 * RSC -- Data processing operands - Register */
EXTERN_C void slv6_X_RSC_M1_Reg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.61--A5.1.5
 * RSC -- Data processing operands - Logical shift left by immediate */
EXTERN_C void slv6_X_RSC_M1_LSLImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.61--A5.1.6
 * RSC -- Data processing operands - Logical shift left by register */
EXTERN_C void slv6_X_RSC_M1_LSLReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.61--A5.1.7
 * RSC -- Data processing operands - Logical shift right by immediate */
EXTERN_C void slv6_X_RSC_M1_LSRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.61--A5.1.8
 * RSC -- Data processing operands - Logical shift right by register */
EXTERN_C void slv6_X_RSC_M1_LSRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.61--A5.1.9
 * RSC -- Data processing operands - Arithmetic shift right by immediate */
EXTERN_C void slv6_X_RSC_M1_ASRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.61--A5.1.10
 * RSC -- Data processing operands - Arithmetic shift right by register */
EXTERN_C void slv6_X_RSC_M1_ASRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.61--A5.1.11
 * RSC -- Data processing operands - Rotate right by immediate */
EXTERN_C void slv6_X_RSC_M1_RRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.61--A5.1.12
 * RSC -- Data processing operands - Rotate right by register */
EXTERN_C void slv6_X_RSC_M1_RRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.61--A5.1.13
 * RSC -- Data processing operands - Rotate right with extend */
EXTERN_C void slv6_X_RSC_M1_RRE(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.62
 * SADD16 */
EXTERN_C void slv6_X_SADD16(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.63
 * SADD8 */
EXTERN_C void slv6_X_SADD8(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.64
 * SADDSUBX */
EXTERN_C void slv6_X_SADDSUBX(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.65--A5.1.3
 * SBC -- Data processing operands - Immediate */
EXTERN_C void slv6_X_SBC_M1_Imm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.65--A5.1.4
 * SBC -- Data processing operands - Register */
EXTERN_C void slv6_X_SBC_M1_Reg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.65--A5.1.5
 * SBC -- Data processing operands - Logical shift left by immediate */
EXTERN_C void slv6_X_SBC_M1_LSLImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.65--A5.1.6
 * SBC -- Data processing operands - Logical shift left by register */
EXTERN_C void slv6_X_SBC_M1_LSLReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.65--A5.1.7
 * SBC -- Data processing operands - Logical shift right by immediate */
EXTERN_C void slv6_X_SBC_M1_LSRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.65--A5.1.8
 * SBC -- Data processing operands - Logical shift right by register */
EXTERN_C void slv6_X_SBC_M1_LSRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.65--A5.1.9
 * SBC -- Data processing operands - Arithmetic shift right by immediate */
EXTERN_C void slv6_X_SBC_M1_ASRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.65--A5.1.10
 * SBC -- Data processing operands - Arithmetic shift right by register */
EXTERN_C void slv6_X_SBC_M1_ASRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.65--A5.1.11
 * SBC -- Data processing operands - Rotate right by immediate */
EXTERN_C void slv6_X_SBC_M1_RRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.65--A5.1.12
 * SBC -- Data processing operands - Rotate right by register */
EXTERN_C void slv6_X_SBC_M1_RRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.65--A5.1.13
 * SBC -- Data processing operands - Rotate right with extend */
EXTERN_C void slv6_X_SBC_M1_RRE(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.66
 * SEL */
EXTERN_C void slv6_X_SEL(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.67
 * SETEND */
EXTERN_C void slv6_X_SETEND(struct SLv6_Processor*,
    const bool E);

/* A4.1.68
 * SHADD16 */
EXTERN_C void slv6_X_SHADD16(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.69
 * SHADD8 */
EXTERN_C void slv6_X_SHADD8(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.70
 * SHADDSUBX */
EXTERN_C void slv6_X_SHADDSUBX(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.71
 * SHSUB16 */
EXTERN_C void slv6_X_SHSUB16(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.72
 * SHSUB8 */
EXTERN_C void slv6_X_SHSUB8(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.73
 * SHSUBADDX */
EXTERN_C void slv6_X_SHSUBADDX(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.74
 * SMLA<x><y> */
EXTERN_C void slv6_X_SMLAxy(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const bool x,
    const bool y,
    const SLv6_Condition cond);

/* A4.1.75
 * SMLAD */
EXTERN_C void slv6_X_SMLAD(struct SLv6_Processor*,
    const bool X,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.76
 * SMLAL */
EXTERN_C void slv6_X_SMLAL(struct SLv6_Processor*,
    const bool S,
    const uint8_t dHi,
    const uint8_t dLo,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.77
 * SMLAL<x><y> */
EXTERN_C void slv6_X_SMLALxy(struct SLv6_Processor*,
    const uint8_t dHi,
    const uint8_t dLo,
    const uint8_t m,
    const uint8_t s,
    const bool x,
    const bool y,
    const SLv6_Condition cond);

/* A4.1.78
 * SMLALD */
EXTERN_C void slv6_X_SMLALD(struct SLv6_Processor*,
    const bool X,
    const uint8_t dHi,
    const uint8_t dLo,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.79
 * SMLAW<y> */
EXTERN_C void slv6_X_SMLAWy(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const bool y,
    const SLv6_Condition cond);

/* A4.1.80
 * SMLSD */
EXTERN_C void slv6_X_SMLSD(struct SLv6_Processor*,
    const bool X,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.81
 * SMLSLD */
EXTERN_C void slv6_X_SMLSLD(struct SLv6_Processor*,
    const bool X,
    const uint8_t dHi,
    const uint8_t dLo,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.82
 * SMMLA */
EXTERN_C void slv6_X_SMMLA(struct SLv6_Processor*,
    const bool R,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.83
 * SMMLS */
EXTERN_C void slv6_X_SMMLS(struct SLv6_Processor*,
    const bool R,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.84
 * SMMUL */
EXTERN_C void slv6_X_SMMUL(struct SLv6_Processor*,
    const bool R,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.85
 * SMUAD */
EXTERN_C void slv6_X_SMUAD(struct SLv6_Processor*,
    const bool X,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.86
 * SMUL<x><y> */
EXTERN_C void slv6_X_SMULxy(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const bool x,
    const bool y,
    const SLv6_Condition cond);

/* A4.1.88
 * SMULW<y> */
EXTERN_C void slv6_X_SMULWy(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const bool y,
    const SLv6_Condition cond);

/* A4.1.89
 * SMUSD */
EXTERN_C void slv6_X_SMUSD(struct SLv6_Processor*,
    const bool X,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.90--A5.4.2
 * SRS -- Load and Store Multiple - Increment after */
EXTERN_C void slv6_X_SRS_M4_IA(struct SLv6_Processor*,
    const bool W,
    const SLv6_Mode mode);

/* A4.1.90--A5.4.3
 * SRS -- Load and Store Multiple - Increment before */
EXTERN_C void slv6_X_SRS_M4_IB(struct SLv6_Processor*,
    const bool W,
    const SLv6_Mode mode);

/* A4.1.90--A5.4.4
 * SRS -- Load and Store Multiple - Decrement after */
EXTERN_C void slv6_X_SRS_M4_DA(struct SLv6_Processor*,
    const bool W,
    const SLv6_Mode mode);

/* A4.1.90--A5.4.5
 * SRS -- Load and Store Multiple - Decrement before */
EXTERN_C void slv6_X_SRS_M4_DB(struct SLv6_Processor*,
    const bool W,
    const SLv6_Mode mode);

/* A4.1.91
 * SSAT */
EXTERN_C void slv6_X_SSAT(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t sat_imm,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.92
 * SSAT16 */
EXTERN_C void slv6_X_SSAT16(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t sat_imm,
    const SLv6_Condition cond);

/* A4.1.93
 * SSUB16 */
EXTERN_C void slv6_X_SSUB16(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.94
 * SSUB8 */
EXTERN_C void slv6_X_SSUB8(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.95
 * SSUBADDX */
EXTERN_C void slv6_X_SSUBADDX(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.96--A5.5.2
 * STC -- Load and Store Coprocessor - Immediate offset */
EXTERN_C void slv6_X_STC_M5_ImmOff(struct SLv6_Processor*);

/* A4.1.96--A5.5.3
 * STC -- Load and Store Coprocessor - Immediate pre indexed */
EXTERN_C void slv6_X_STC_M5_Imm_preInd(struct SLv6_Processor*);

/* A4.1.96--A5.5.4
 * STC -- Load and Store Coprocessor - Immediate post indexed */
EXTERN_C void slv6_X_STC_M5_Imm_postInd(struct SLv6_Processor*);

/* A4.1.96--A5.5.5
 * STC -- Load and Store Coprocessor - Unindexed */
EXTERN_C void slv6_X_STC_M5_U(struct SLv6_Processor*);

/* A4.1.97--A5.4.4
 * STM (1) -- Load and Store Multiple - Decrement after */
EXTERN_C void slv6_X_STM1_M4_DA(struct SLv6_Processor*,
    const bool W,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.98--A5.4.2
 * STM (2) -- Load and Store Multiple - Increment after */
EXTERN_C void slv6_X_STM2_M4_IA(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.98--A5.4.3
 * STM (2) -- Load and Store Multiple - Increment before */
EXTERN_C void slv6_X_STM2_M4_IB(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.98--A5.4.4
 * STM (2) -- Load and Store Multiple - Decrement after */
EXTERN_C void slv6_X_STM2_M4_DA(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.98--A5.4.5
 * STM (2) -- Load and Store Multiple - Decrement before */
EXTERN_C void slv6_X_STM2_M4_DB(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list);

/* A4.1.99--A5.2.6
 * STR -- Load and Store Word or Unsigned Byte - Register pre indexed */
EXTERN_C void slv6_X_STR_M2_Reg_preInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.99--A5.2.7
 * STR -- Load and Store Word or Unsigned Byte - Scaled register pre indexed */
EXTERN_C void slv6_X_STR_M2_ScReg_preInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.99--A5.2.10
 * STR -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
EXTERN_C void slv6_X_STR_M2_ScReg_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.100--A5.2.4
 * STRB -- Load and Store Word or Unsigned Byte - Scaled register offset */
EXTERN_C void slv6_X_STRB_M2_ScRegOff(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.100--A5.2.5
 * STRB -- Load and Store Word or Unsigned Byte - Immediate pre indexed */
EXTERN_C void slv6_X_STRB_M2_Imm_preInd(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12);

/* A4.1.100--A5.2.6
 * STRB -- Load and Store Word or Unsigned Byte - Register pre indexed */
EXTERN_C void slv6_X_STRB_M2_Reg_preInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.100--A5.2.7
 * STRB -- Load and Store Word or Unsigned Byte - Scaled register pre indexed */
EXTERN_C void slv6_X_STRB_M2_ScReg_preInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.100--A5.2.9
 * STRB -- Load and Store Word or Unsigned Byte - Register post indexed */
EXTERN_C void slv6_X_STRB_M2_Reg_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.100--A5.2.10
 * STRB -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
EXTERN_C void slv6_X_STRB_M2_ScReg_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.101--A5.2.8
 * STRBT -- Load and Store Word or Unsigned Byte - Immediate post indexed */
EXTERN_C void slv6_X_STRBT_M2_Imm_postInd(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12);

/* A4.1.101--A5.2.9
 * STRBT -- Load and Store Word or Unsigned Byte - Register post indexed */
EXTERN_C void slv6_X_STRBT_M2_Reg_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.101--A5.2.10
 * STRBT -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
EXTERN_C void slv6_X_STRBT_M2_ScReg_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.102--A5.3.2
 * STRD -- Miscellaneous Loads and Stores - Immediate offset */
EXTERN_C void slv6_X_STRD_M3_ImmOff(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond);

/* A4.1.102--A5.3.3
 * STRD -- Miscellaneous Loads and Stores - Register offset */
EXTERN_C void slv6_X_STRD_M3_RegOff(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.102--A5.3.4
 * STRD -- Miscellaneous Loads and Stores - Immediate pre indexed */
EXTERN_C void slv6_X_STRD_M3_Imm_preInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond);

/* A4.1.102--A5.3.5
 * STRD -- Miscellaneous Loads and Stores - Register pre indexed */
EXTERN_C void slv6_X_STRD_M3_Reg_preInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.102--A5.3.6
 * STRD -- Miscellaneous Loads and Stores - Immediate post indexed */
EXTERN_C void slv6_X_STRD_M3_Imm_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond);

/* A4.1.102--A5.3.7
 * STRD -- Miscellaneous Loads and Stores - Register post indexed */
EXTERN_C void slv6_X_STRD_M3_Reg_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.103
 * STREX */
EXTERN_C void slv6_X_STREX(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.104--A5.3.2
 * STRH -- Miscellaneous Loads and Stores - Immediate offset */
EXTERN_C void slv6_X_STRH_M3_ImmOff(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond);

/* A4.1.104--A5.3.3
 * STRH -- Miscellaneous Loads and Stores - Register offset */
EXTERN_C void slv6_X_STRH_M3_RegOff(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.104--A5.3.4
 * STRH -- Miscellaneous Loads and Stores - Immediate pre indexed */
EXTERN_C void slv6_X_STRH_M3_Imm_preInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond);

/* A4.1.104--A5.3.5
 * STRH -- Miscellaneous Loads and Stores - Register pre indexed */
EXTERN_C void slv6_X_STRH_M3_Reg_preInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.104--A5.3.6
 * STRH -- Miscellaneous Loads and Stores - Immediate post indexed */
EXTERN_C void slv6_X_STRH_M3_Imm_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond);

/* A4.1.104--A5.3.7
 * STRH -- Miscellaneous Loads and Stores - Register post indexed */
EXTERN_C void slv6_X_STRH_M3_Reg_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.105--A5.2.8
 * STRT -- Load and Store Word or Unsigned Byte - Immediate post indexed */
EXTERN_C void slv6_X_STRT_M2_Imm_postInd(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12);

/* A4.1.105--A5.2.9
 * STRT -- Load and Store Word or Unsigned Byte - Register post indexed */
EXTERN_C void slv6_X_STRT_M2_Reg_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.105--A5.2.10
 * STRT -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
EXTERN_C void slv6_X_STRT_M2_ScReg_postInd(struct SLv6_Processor*,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.106--A5.1.4
 * SUB -- Data processing operands - Register */
EXTERN_C void slv6_X_SUB_M1_Reg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.106--A5.1.6
 * SUB -- Data processing operands - Logical shift left by register */
EXTERN_C void slv6_X_SUB_M1_LSLReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.106--A5.1.7
 * SUB -- Data processing operands - Logical shift right by immediate */
EXTERN_C void slv6_X_SUB_M1_LSRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.106--A5.1.8
 * SUB -- Data processing operands - Logical shift right by register */
EXTERN_C void slv6_X_SUB_M1_LSRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.106--A5.1.10
 * SUB -- Data processing operands - Arithmetic shift right by register */
EXTERN_C void slv6_X_SUB_M1_ASRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.106--A5.1.11
 * SUB -- Data processing operands - Rotate right by immediate */
EXTERN_C void slv6_X_SUB_M1_RRImm(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.106--A5.1.12
 * SUB -- Data processing operands - Rotate right by register */
EXTERN_C void slv6_X_SUB_M1_RRReg(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.106--A5.1.13
 * SUB -- Data processing operands - Rotate right with extend */
EXTERN_C void slv6_X_SUB_M1_RRE(struct SLv6_Processor*,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.107
 * SWI */
EXTERN_C void slv6_X_SWI(struct SLv6_Processor*,
    const SLv6_Condition cond);

/* A4.1.108
 * SWP */
EXTERN_C void slv6_X_SWP(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.109
 * SWPB */
EXTERN_C void slv6_X_SWPB(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.110
 * SXTAB */
EXTERN_C void slv6_X_SXTAB(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t rotate,
    const SLv6_Condition cond);

/* A4.1.111
 * SXTAB16 */
EXTERN_C void slv6_X_SXTAB16(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t rotate,
    const SLv6_Condition cond);

/* A4.1.112
 * SXTAH */
EXTERN_C void slv6_X_SXTAH(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t rotate,
    const SLv6_Condition cond);

/* A4.1.113
 * SXTB */
EXTERN_C void slv6_X_SXTB(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t rotate,
    const SLv6_Condition cond);

/* A4.1.114
 * SXTB16 */
EXTERN_C void slv6_X_SXTB16(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t rotate,
    const SLv6_Condition cond);

/* A4.1.115
 * SXTH */
EXTERN_C void slv6_X_SXTH(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t rotate,
    const SLv6_Condition cond);

/* A4.1.116--A5.1.3
 * TEQ -- Data processing operands - Immediate */
EXTERN_C void slv6_X_TEQ_M1_Imm(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated);

/* A4.1.116--A5.1.4
 * TEQ -- Data processing operands - Register */
EXTERN_C void slv6_X_TEQ_M1_Reg(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.116--A5.1.5
 * TEQ -- Data processing operands - Logical shift left by immediate */
EXTERN_C void slv6_X_TEQ_M1_LSLImm(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.116--A5.1.6
 * TEQ -- Data processing operands - Logical shift left by register */
EXTERN_C void slv6_X_TEQ_M1_LSLReg(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.116--A5.1.7
 * TEQ -- Data processing operands - Logical shift right by immediate */
EXTERN_C void slv6_X_TEQ_M1_LSRImm(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.116--A5.1.8
 * TEQ -- Data processing operands - Logical shift right by register */
EXTERN_C void slv6_X_TEQ_M1_LSRReg(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.116--A5.1.9
 * TEQ -- Data processing operands - Arithmetic shift right by immediate */
EXTERN_C void slv6_X_TEQ_M1_ASRImm(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.116--A5.1.10
 * TEQ -- Data processing operands - Arithmetic shift right by register */
EXTERN_C void slv6_X_TEQ_M1_ASRReg(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.116--A5.1.11
 * TEQ -- Data processing operands - Rotate right by immediate */
EXTERN_C void slv6_X_TEQ_M1_RRImm(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.116--A5.1.12
 * TEQ -- Data processing operands - Rotate right by register */
EXTERN_C void slv6_X_TEQ_M1_RRReg(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.116--A5.1.13
 * TEQ -- Data processing operands - Rotate right with extend */
EXTERN_C void slv6_X_TEQ_M1_RRE(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.117--A5.1.5
 * TST -- Data processing operands - Logical shift left by immediate */
EXTERN_C void slv6_X_TST_M1_LSLImm(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.117--A5.1.6
 * TST -- Data processing operands - Logical shift left by register */
EXTERN_C void slv6_X_TST_M1_LSLReg(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.117--A5.1.7
 * TST -- Data processing operands - Logical shift right by immediate */
EXTERN_C void slv6_X_TST_M1_LSRImm(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.117--A5.1.8
 * TST -- Data processing operands - Logical shift right by register */
EXTERN_C void slv6_X_TST_M1_LSRReg(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.117--A5.1.9
 * TST -- Data processing operands - Arithmetic shift right by immediate */
EXTERN_C void slv6_X_TST_M1_ASRImm(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.117--A5.1.10
 * TST -- Data processing operands - Arithmetic shift right by register */
EXTERN_C void slv6_X_TST_M1_ASRReg(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.117--A5.1.11
 * TST -- Data processing operands - Rotate right by immediate */
EXTERN_C void slv6_X_TST_M1_RRImm(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.117--A5.1.12
 * TST -- Data processing operands - Rotate right by register */
EXTERN_C void slv6_X_TST_M1_RRReg(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.117--A5.1.13
 * TST -- Data processing operands - Rotate right with extend */
EXTERN_C void slv6_X_TST_M1_RRE(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.118
 * UADD16 */
EXTERN_C void slv6_X_UADD16(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.119
 * UADD8 */
EXTERN_C void slv6_X_UADD8(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.120
 * UADDSUBX */
EXTERN_C void slv6_X_UADDSUBX(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.121
 * UHADD16 */
EXTERN_C void slv6_X_UHADD16(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.122
 * UHADD8 */
EXTERN_C void slv6_X_UHADD8(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.123
 * UHADDSUBX */
EXTERN_C void slv6_X_UHADDSUBX(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.124
 * UHSUB16 */
EXTERN_C void slv6_X_UHSUB16(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.125
 * UHSUB8 */
EXTERN_C void slv6_X_UHSUB8(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.126
 * UHSUBADDX */
EXTERN_C void slv6_X_UHSUBADDX(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.127
 * UMAAL */
EXTERN_C void slv6_X_UMAAL(struct SLv6_Processor*,
    const uint8_t dHi,
    const uint8_t dLo,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.128
 * UMLAL */
EXTERN_C void slv6_X_UMLAL(struct SLv6_Processor*,
    const bool S,
    const uint8_t dHi,
    const uint8_t dLo,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.129
 * UMULL */
EXTERN_C void slv6_X_UMULL(struct SLv6_Processor*,
    const bool S,
    const uint8_t dHi,
    const uint8_t dLo,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.130
 * UQADD16 */
EXTERN_C void slv6_X_UQADD16(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.131
 * UQADD8 */
EXTERN_C void slv6_X_UQADD8(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.132
 * UQADDSUBX */
EXTERN_C void slv6_X_UQADDSUBX(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.133
 * UQSUB16 */
EXTERN_C void slv6_X_UQSUB16(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.134
 * UQSUB8 */
EXTERN_C void slv6_X_UQSUB8(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.135
 * UQSUBADDX */
EXTERN_C void slv6_X_UQSUBADDX(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.136
 * USAD8 */
EXTERN_C void slv6_X_USAD8(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.137
 * USADA8 */
EXTERN_C void slv6_X_USADA8(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond);

/* A4.1.138
 * USAT */
EXTERN_C void slv6_X_USAT(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t sat_imm,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond);

/* A4.1.139
 * USAT16 */
EXTERN_C void slv6_X_USAT16(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t sat_imm,
    const SLv6_Condition cond);

/* A4.1.140
 * USUB16 */
EXTERN_C void slv6_X_USUB16(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.141
 * USUB8 */
EXTERN_C void slv6_X_USUB8(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.142
 * USUBADDX */
EXTERN_C void slv6_X_USUBADDX(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond);

/* A4.1.143
 * UXTAB */
EXTERN_C void slv6_X_UXTAB(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t rotate,
    const SLv6_Condition cond);

/* A4.1.144
 * UXTAB16 */
EXTERN_C void slv6_X_UXTAB16(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t rotate,
    const SLv6_Condition cond);

/* A4.1.145
 * UXTAH */
EXTERN_C void slv6_X_UXTAH(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t rotate,
    const SLv6_Condition cond);

/* A4.1.146
 * UXTB */
EXTERN_C void slv6_X_UXTB(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t rotate,
    const SLv6_Condition cond);

/* A4.1.147
 * UXTB16 */
EXTERN_C void slv6_X_UXTB16(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t rotate,
    const SLv6_Condition cond);

/* A4.1.148
 * UXTH */
EXTERN_C void slv6_X_UXTH(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t rotate,
    const SLv6_Condition cond);

/* A7.1.28
 * LDR (1) */
EXTERN_C void slv6_X_Tb_LDR1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint32_t immed_5);

/* A7.1.25
 * CPY */
EXTERN_C void slv6_X_Tb_CPY(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m);

/* A7.1.58
 * STR (1) */
EXTERN_C void slv6_X_Tb_STR1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint32_t immed_5);

/* A7.1.13
 * B (1) */
EXTERN_C void slv6_X_Tb_B1(struct SLv6_Processor*,
    const SLv6_Condition cond,
    const uint32_t simmed_8_ext);

/* A7.1.38
 * LSL (1) */
EXTERN_C void slv6_X_Tb_LSL1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint32_t immed_5);

/* A7.1.5
 * ADD (3) */
EXTERN_C void slv6_X_Tb_ADD3(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A7.1.42
 * MOV (1) */
EXTERN_C void slv6_X_Tb_MOV1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t immed_8);

/* A7.1.22
 * CMP (2) */
EXTERN_C void slv6_X_Tb_CMP2(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n);

/* A7.1.30
 * LDR (3) */
EXTERN_C void slv6_X_Tb_LDR3(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t immed_8);

/* A7.1.26
 * EOR */
EXTERN_C void slv6_X_Tb_EOR(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m);

/* A7.1.66
 * SUB (2) */
EXTERN_C void slv6_X_Tb_SUB2(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t immed_8);

/* A7.1.43
 * MOV (2) */
EXTERN_C void slv6_X_Tb_MOV2(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n);

/* A7.1.4
 * ADD (2) */
EXTERN_C void slv6_X_Tb_ADD2(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t immed_8);

/* A7.1.31
 * LDR (4) */
EXTERN_C void slv6_X_Tb_LDR4(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t immed_8);

/* A7.1.10
 * AND */
EXTERN_C void slv6_X_Tb_AND(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m);

/* A7.1.40
 * LSR (1) */
EXTERN_C void slv6_X_Tb_LSR1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint32_t immed_5);

/* A7.1.29
 * LDR (2) */
EXTERN_C void slv6_X_Tb_LDR2(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A7.1.6
 * ADD (4) */
EXTERN_C void slv6_X_Tb_ADD4(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m);

/* A7.1.21
 * CMP (1) */
EXTERN_C void slv6_X_Tb_CMP1(struct SLv6_Processor*,
    const uint8_t immed_8,
    const uint8_t n);

/* A7.1.48
 * ORR */
EXTERN_C void slv6_X_Tb_ORR(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m);

/* A7.1.60
 * STR (3) */
EXTERN_C void slv6_X_Tb_STR3(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t immed_8);

/* A7.1.54
 * ROR */
EXTERN_C void slv6_X_Tb_ROR(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t s);

/* A7.1.17
 * BL, BLX (1) */
EXTERN_C void slv6_X_Tb_BL(struct SLv6_Processor*,
    const uint32_t H,
    const uint32_t offset_11);

/* A7.1.14
 * B (2) */
EXTERN_C void slv6_X_Tb_B2(struct SLv6_Processor*,
    const uint32_t simmed_11_ext);

/* A7.1.47
 * NEG */
EXTERN_C void slv6_X_Tb_NEG(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m);

/* A7.1.32
 * LDRB (1) */
EXTERN_C void slv6_X_Tb_LDRB1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint32_t immed_5);

/* A7.1.50
 * PUSH */
EXTERN_C void slv6_X_Tb_PUSH(struct SLv6_Processor*,
    const bool R,
    const uint32_t register_list);

/* A7.1.49
 * POP */
EXTERN_C void slv6_X_Tb_POP(struct SLv6_Processor*,
    const bool R,
    const uint32_t register_list);

/* A7.1.23
 * CMP (3) */
EXTERN_C void slv6_X_Tb_CMP3(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n);

/* A7.1.68
 * SUB (4) */
EXTERN_C void slv6_X_Tb_SUB4(struct SLv6_Processor*,
    const uint32_t immed_7);

/* A7.1.9
 * ADD (7) */
EXTERN_C void slv6_X_Tb_ADD7(struct SLv6_Processor*,
    const uint32_t immed_7);

/* A7.1.8
 * ADD (6) */
EXTERN_C void slv6_X_Tb_ADD6(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t immed_8);

/* A7.1.19
 * BX */
EXTERN_C void slv6_X_Tb_BX(struct SLv6_Processor*,
    const uint8_t m);

/* A7.1.61
 * STRB (1) */
EXTERN_C void slv6_X_Tb_STRB1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint32_t immed_5);

/* A7.1.33
 * LDRB (2) */
EXTERN_C void slv6_X_Tb_LDRB2(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A7.1.2
 * ADC */
EXTERN_C void slv6_X_Tb_ADC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m);

/* A7.1.67
 * SUB (3) */
EXTERN_C void slv6_X_Tb_SUB3(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A7.1.65
 * SUB (1) */
EXTERN_C void slv6_X_Tb_SUB1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint32_t immed_3);

/* A7.1.41
 * LSR (2) */
EXTERN_C void slv6_X_Tb_LSR2(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t s);

/* A7.1.59
 * STR (2) */
EXTERN_C void slv6_X_Tb_STR2(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A7.1.62
 * STRB (2) */
EXTERN_C void slv6_X_Tb_STRB2(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A7.1.27
 * LDMIA */
EXTERN_C void slv6_X_Tb_LDMIA(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list);

/* A7.1.57
 * STMIA */
EXTERN_C void slv6_X_Tb_STMIA(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list);

/* A7.1.3
 * ADD (1) */
EXTERN_C void slv6_X_Tb_ADD1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint32_t immed_3);

/* A7.1.45
 * MUL */
EXTERN_C void slv6_X_Tb_MUL(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m);

/* A7.1.11
 * ASR (1) */
EXTERN_C void slv6_X_Tb_ASR1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint32_t immed_5);

/* A7.1.46
 * MVN */
EXTERN_C void slv6_X_Tb_MVN(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m);

/* A7.1.34
 * LDRH (1) */
EXTERN_C void slv6_X_Tb_LDRH1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint32_t immed_5);

/* A7.1.72
 * TST */
EXTERN_C void slv6_X_Tb_TST(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n);

/* A7.1.15
 * BIC */
EXTERN_C void slv6_X_Tb_BIC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m);

/* A7.1.39
 * LSL (2) */
EXTERN_C void slv6_X_Tb_LSL2(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t s);

/* A7.1.7
 * ADD (5) */
EXTERN_C void slv6_X_Tb_ADD5(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t immed_8);

/* A7.1.12
 * ASR (2) */
EXTERN_C void slv6_X_Tb_ASR2(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t s);

/* A7.1.16
 * BKPT */
EXTERN_C void slv6_X_Tb_BKPT(struct SLv6_Processor*);

/* A7.1.18
 * BLX (2) */
EXTERN_C void slv6_X_Tb_BLX2(struct SLv6_Processor*,
    const uint8_t m);

/* A7.1.20
 * CMN */
EXTERN_C void slv6_X_Tb_CMN(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n);

/* A7.1.24
 * CPS */
EXTERN_C void slv6_X_Tb_CPS(struct SLv6_Processor*,
    const bool A,
    const bool F,
    const bool I,
    const uint8_t imod);

/* A7.1.35
 * LDRH (2) */
EXTERN_C void slv6_X_Tb_LDRH2(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A7.1.36
 * LDRSB */
EXTERN_C void slv6_X_Tb_LDRSB(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A7.1.37
 * LDRSH */
EXTERN_C void slv6_X_Tb_LDRSH(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A7.1.51
 * REV */
EXTERN_C void slv6_X_Tb_REV(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n);

/* A7.1.52
 * REV16 */
EXTERN_C void slv6_X_Tb_REV16(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n);

/* A7.1.53
 * REVSH */
EXTERN_C void slv6_X_Tb_REVSH(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n);

/* A7.1.55
 * SBC */
EXTERN_C void slv6_X_Tb_SBC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m);

/* A7.1.56
 * SETEND */
EXTERN_C void slv6_X_Tb_SETEND(struct SLv6_Processor*,
    const bool E);

/* A7.1.63
 * STRH (1) */
EXTERN_C void slv6_X_Tb_STRH1(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint32_t immed_5);

/* A7.1.64
 * STRH (2) */
EXTERN_C void slv6_X_Tb_STRH2(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A7.1.69
 * SWI */
EXTERN_C void slv6_X_Tb_SWI(struct SLv6_Processor*);

/* A7.1.70
 * SXTB */
EXTERN_C void slv6_X_Tb_SXTB(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m);

/* A7.1.71
 * SXTH */
EXTERN_C void slv6_X_Tb_SXTH(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m);

/* A7.1.73
 * UXTB */
EXTERN_C void slv6_X_Tb_UXTB(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m);

/* A7.1.74
 * UXTH */
EXTERN_C void slv6_X_Tb_UXTH(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m);

/* A4.1.23--A5.2.2--NC
 * LDR -- Load and Store Word or Unsigned Byte - Immediate offset (no cond) */
EXTERN_C void slv6_X_LDR_M2_ImmOff_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint32_t signed_offset_12);

/* A4.1.99--A5.2.2--NC
 * STR -- Load and Store Word or Unsigned Byte - Immediate offset (no cond) */
EXTERN_C void slv6_X_STR_M2_ImmOff_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint32_t signed_offset_12);

/* A4.1.5--NC
 * B, BL (L=1) (no cond) */
EXTERN_C void slv6_X_B_L1_NC(struct SLv6_Processor*,
    const uint32_t pc_offset);

/* A4.1.5--NC
 * B, BL (L=0) (no cond) */
EXTERN_C void slv6_X_B_L0_NC(struct SLv6_Processor*,
    const uint32_t pc_offset);

/* A4.1.106--A5.1.3--NC
 * SUB -- Data processing operands - Immediate (S=1) (no cond) */
EXTERN_C void slv6_X_SUB_M1_Imm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated);

/* A4.1.106--A5.1.3--NC
 * SUB -- Data processing operands - Immediate (S=0) (no cond) */
EXTERN_C void slv6_X_SUB_M1_Imm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated);

/* A4.1.15--A5.1.4--NC
 * CMP -- Data processing operands - Register (no cond) */
EXTERN_C void slv6_X_CMP_M1_Reg_NC(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n);

/* A4.1.3--A5.1.3--NC
 * ADD -- Data processing operands - Immediate (S=1) (no cond) */
EXTERN_C void slv6_X_ADD_M1_Imm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated);

/* A4.1.3--A5.1.3--NC
 * ADD -- Data processing operands - Immediate (S=0) (no cond) */
EXTERN_C void slv6_X_ADD_M1_Imm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated);

/* A4.1.3--A5.1.4--NC
 * ADD -- Data processing operands - Register (S=1) (no cond) */
EXTERN_C void slv6_X_ADD_M1_Reg_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A4.1.3--A5.1.4--NC
 * ADD -- Data processing operands - Register (S=0) (no cond) */
EXTERN_C void slv6_X_ADD_M1_Reg_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A4.1.18--A5.1.4--NC
 * EOR -- Data processing operands - Register (S=1) (no cond) */
EXTERN_C void slv6_X_EOR_M1_Reg_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A4.1.18--A5.1.4--NC
 * EOR -- Data processing operands - Register (S=0) (no cond) */
EXTERN_C void slv6_X_EOR_M1_Reg_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A4.1.4--A5.1.3--NC
 * AND -- Data processing operands - Immediate (S=1) (no cond) */
EXTERN_C void slv6_X_AND_M1_Imm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated);

/* A4.1.4--A5.1.3--NC
 * AND -- Data processing operands - Immediate (S=0) (no cond) */
EXTERN_C void slv6_X_AND_M1_Imm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated);

/* A4.1.35--A5.1.7--NC
 * MOV -- Data processing operands - Logical shift right by immediate (S=1) (no cond) */
EXTERN_C void slv6_X_MOV_M1_LSRImm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm);

/* A4.1.35--A5.1.7--NC
 * MOV -- Data processing operands - Logical shift right by immediate (S=0) (no cond) */
EXTERN_C void slv6_X_MOV_M1_LSRImm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm);

/* A4.1.17--NC
 * CPY (no cond) */
EXTERN_C void slv6_X_CPY_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m);

/* A4.1.35--A5.1.5--NC
 * MOV -- Data processing operands - Logical shift left by immediate (S=1) (no cond) */
EXTERN_C void slv6_X_MOV_M1_LSLImm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm);

/* A4.1.35--A5.1.5--NC
 * MOV -- Data processing operands - Logical shift left by immediate (S=0) (no cond) */
EXTERN_C void slv6_X_MOV_M1_LSLImm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm);

/* A4.1.35--A5.1.3--NC
 * MOV -- Data processing operands - Immediate (S=1) (no cond) */
EXTERN_C void slv6_X_MOV_M1_Imm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated);

/* A4.1.35--A5.1.3--NC
 * MOV -- Data processing operands - Immediate (S=0) (no cond) */
EXTERN_C void slv6_X_MOV_M1_Imm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated);

/* A4.1.20--A5.4.2--NC
 * LDM (1) -- Load and Store Multiple - Increment after (W=1) (no cond) */
EXTERN_C void slv6_X_LDM1_M4_IA_W1_NC(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list);

/* A4.1.20--A5.4.2--NC
 * LDM (1) -- Load and Store Multiple - Increment after (W=0) (no cond) */
EXTERN_C void slv6_X_LDM1_M4_IA_W0_NC(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list);

/* A4.1.15--A5.1.3--NC
 * CMP -- Data processing operands - Immediate (no cond) */
EXTERN_C void slv6_X_CMP_M1_Imm_NC(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated);

/* A4.1.23--A5.2.4--NC
 * LDR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) (no cond) */
EXTERN_C void slv6_X_LDR_M2_ScRegOff_U1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm);

/* A4.1.23--A5.2.4--NC
 * LDR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) (no cond) */
EXTERN_C void slv6_X_LDR_M2_ScRegOff_U0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm);

/* A4.1.10--NC
 * BX (no cond) */
EXTERN_C void slv6_X_BX_NC(struct SLv6_Processor*,
    const uint8_t m);

/* A4.1.3--A5.1.5--NC
 * ADD -- Data processing operands - Logical shift left by immediate (S=1) (no cond) */
EXTERN_C void slv6_X_ADD_M1_LSLImm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.3--A5.1.5--NC
 * ADD -- Data processing operands - Logical shift left by immediate (S=0) (no cond) */
EXTERN_C void slv6_X_ADD_M1_LSLImm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.24--A5.2.2--NC
 * LDRB -- Load and Store Word or Unsigned Byte - Immediate offset (no cond) */
EXTERN_C void slv6_X_LDRB_M2_ImmOff_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint32_t signed_offset_12);

/* A4.1.42--A5.1.4--NC
 * ORR -- Data processing operands - Register (S=1) (no cond) */
EXTERN_C void slv6_X_ORR_M1_Reg_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A4.1.42--A5.1.4--NC
 * ORR -- Data processing operands - Register (S=0) (no cond) */
EXTERN_C void slv6_X_ORR_M1_Reg_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A4.1.35--A5.1.11--NC
 * MOV -- Data processing operands - Rotate right by immediate (S=1) (no cond) */
EXTERN_C void slv6_X_MOV_M1_RRImm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm);

/* A4.1.35--A5.1.11--NC
 * MOV -- Data processing operands - Rotate right by immediate (S=0) (no cond) */
EXTERN_C void slv6_X_MOV_M1_RRImm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm);

/* A4.1.23--A5.2.8--NC
 * LDR -- Load and Store Word or Unsigned Byte - Immediate post indexed (no cond) */
EXTERN_C void slv6_X_LDR_M2_Imm_postInd_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint32_t signed_offset_12);

/* A4.1.18--A5.1.11--NC
 * EOR -- Data processing operands - Rotate right by immediate (S=1) (no cond) */
EXTERN_C void slv6_X_EOR_M1_RRImm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.18--A5.1.11--NC
 * EOR -- Data processing operands - Rotate right by immediate (S=0) (no cond) */
EXTERN_C void slv6_X_EOR_M1_RRImm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.4--A5.1.4--NC
 * AND -- Data processing operands - Register (S=1) (no cond) */
EXTERN_C void slv6_X_AND_M1_Reg_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A4.1.4--A5.1.4--NC
 * AND -- Data processing operands - Register (S=0) (no cond) */
EXTERN_C void slv6_X_AND_M1_Reg_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A4.1.99--A5.2.5--NC
 * STR -- Load and Store Word or Unsigned Byte - Immediate pre indexed (no cond) */
EXTERN_C void slv6_X_STR_M2_Imm_preInd_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint32_t signed_offset_12);

/* A4.1.100--A5.2.2--NC
 * STRB -- Load and Store Word or Unsigned Byte - Immediate offset (no cond) */
EXTERN_C void slv6_X_STRB_M2_ImmOff_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint32_t signed_offset_12);

/* A4.1.42--A5.1.5--NC
 * ORR -- Data processing operands - Logical shift left by immediate (S=1) (no cond) */
EXTERN_C void slv6_X_ORR_M1_LSLImm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.42--A5.1.5--NC
 * ORR -- Data processing operands - Logical shift left by immediate (S=0) (no cond) */
EXTERN_C void slv6_X_ORR_M1_LSLImm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.2--A5.1.4--NC
 * ADC -- Data processing operands - Register (S=1) (no cond) */
EXTERN_C void slv6_X_ADC_M1_Reg_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A4.1.2--A5.1.4--NC
 * ADC -- Data processing operands - Register (S=0) (no cond) */
EXTERN_C void slv6_X_ADC_M1_Reg_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A4.1.24--A5.2.3--NC
 * LDRB -- Load and Store Word or Unsigned Byte - Register offset (U=1) (no cond) */
EXTERN_C void slv6_X_LDRB_M2_RegOff_U1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A4.1.24--A5.2.3--NC
 * LDRB -- Load and Store Word or Unsigned Byte - Register offset (U=0) (no cond) */
EXTERN_C void slv6_X_LDRB_M2_RegOff_U0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A4.1.60--A5.1.4--NC
 * RSB -- Data processing operands - Register (S=1) (no cond) */
EXTERN_C void slv6_X_RSB_M1_Reg_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A4.1.60--A5.1.4--NC
 * RSB -- Data processing operands - Register (S=0) (no cond) */
EXTERN_C void slv6_X_RSB_M1_Reg_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A4.1.6--A5.1.3--NC
 * BIC -- Data processing operands - Immediate (S=1) (no cond) */
EXTERN_C void slv6_X_BIC_M1_Imm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated);

/* A4.1.6--A5.1.3--NC
 * BIC -- Data processing operands - Immediate (S=0) (no cond) */
EXTERN_C void slv6_X_BIC_M1_Imm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated);

/* A4.1.41--A5.1.3--NC
 * MVN -- Data processing operands - Immediate (S=1) (no cond) */
EXTERN_C void slv6_X_MVN_M1_Imm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated);

/* A4.1.41--A5.1.3--NC
 * MVN -- Data processing operands - Immediate (S=0) (no cond) */
EXTERN_C void slv6_X_MVN_M1_Imm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated);

/* A4.1.42--A5.1.7--NC
 * ORR -- Data processing operands - Logical shift right by immediate (S=1) (no cond) */
EXTERN_C void slv6_X_ORR_M1_LSRImm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.42--A5.1.7--NC
 * ORR -- Data processing operands - Logical shift right by immediate (S=0) (no cond) */
EXTERN_C void slv6_X_ORR_M1_LSRImm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.18--A5.1.7--NC
 * EOR -- Data processing operands - Logical shift right by immediate (S=1) (no cond) */
EXTERN_C void slv6_X_EOR_M1_LSRImm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.18--A5.1.7--NC
 * EOR -- Data processing operands - Logical shift right by immediate (S=0) (no cond) */
EXTERN_C void slv6_X_EOR_M1_LSRImm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.23--A5.2.3--NC
 * LDR -- Load and Store Word or Unsigned Byte - Register offset (U=1) (no cond) */
EXTERN_C void slv6_X_LDR_M2_RegOff_U1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A4.1.23--A5.2.3--NC
 * LDR -- Load and Store Word or Unsigned Byte - Register offset (U=0) (no cond) */
EXTERN_C void slv6_X_LDR_M2_RegOff_U0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A4.1.35--A5.1.8--NC
 * MOV -- Data processing operands - Logical shift right by register (S=1) (no cond) */
EXTERN_C void slv6_X_MOV_M1_LSRReg_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s);

/* A4.1.35--A5.1.8--NC
 * MOV -- Data processing operands - Logical shift right by register (S=0) (no cond) */
EXTERN_C void slv6_X_MOV_M1_LSRReg_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s);

/* A4.1.100--A5.2.3--NC
 * STRB -- Load and Store Word or Unsigned Byte - Register offset (U=1) (no cond) */
EXTERN_C void slv6_X_STRB_M2_RegOff_U1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A4.1.100--A5.2.3--NC
 * STRB -- Load and Store Word or Unsigned Byte - Register offset (U=0) (no cond) */
EXTERN_C void slv6_X_STRB_M2_RegOff_U0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A4.1.99--A5.2.4--NC
 * STR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) (no cond) */
EXTERN_C void slv6_X_STR_M2_ScRegOff_U1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm);

/* A4.1.99--A5.2.4--NC
 * STR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) (no cond) */
EXTERN_C void slv6_X_STR_M2_ScRegOff_U0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm);

/* A4.1.14--A5.1.4--NC
 * CMN -- Data processing operands - Register (no cond) */
EXTERN_C void slv6_X_CMN_M1_Reg_NC(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n);

/* A4.1.99--A5.2.9--NC
 * STR -- Load and Store Word or Unsigned Byte - Register post indexed (U=1) (no cond) */
EXTERN_C void slv6_X_STR_M2_Reg_postInd_U1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A4.1.99--A5.2.9--NC
 * STR -- Load and Store Word or Unsigned Byte - Register post indexed (U=0) (no cond) */
EXTERN_C void slv6_X_STR_M2_Reg_postInd_U0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A4.1.99--A5.2.3--NC
 * STR -- Load and Store Word or Unsigned Byte - Register offset (U=1) (no cond) */
EXTERN_C void slv6_X_STR_M2_RegOff_U1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A4.1.99--A5.2.3--NC
 * STR -- Load and Store Word or Unsigned Byte - Register offset (U=0) (no cond) */
EXTERN_C void slv6_X_STR_M2_RegOff_U0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n);

/* A4.1.18--A5.1.5--NC
 * EOR -- Data processing operands - Logical shift left by immediate (S=1) (no cond) */
EXTERN_C void slv6_X_EOR_M1_LSLImm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.18--A5.1.5--NC
 * EOR -- Data processing operands - Logical shift left by immediate (S=0) (no cond) */
EXTERN_C void slv6_X_EOR_M1_LSLImm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.60--A5.1.3--NC
 * RSB -- Data processing operands - Immediate (S=1) (no cond) */
EXTERN_C void slv6_X_RSB_M1_Imm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated);

/* A4.1.60--A5.1.3--NC
 * RSB -- Data processing operands - Immediate (S=0) (no cond) */
EXTERN_C void slv6_X_RSB_M1_Imm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated);

/* A4.1.35--A5.1.9--NC
 * MOV -- Data processing operands - Arithmetic shift right by immediate (S=1) (no cond) */
EXTERN_C void slv6_X_MOV_M1_ASRImm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm);

/* A4.1.35--A5.1.9--NC
 * MOV -- Data processing operands - Arithmetic shift right by immediate (S=0) (no cond) */
EXTERN_C void slv6_X_MOV_M1_ASRImm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm);

/* A4.1.3--A5.1.11--NC
 * ADD -- Data processing operands - Rotate right by immediate (S=1) (no cond) */
EXTERN_C void slv6_X_ADD_M1_RRImm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.3--A5.1.11--NC
 * ADD -- Data processing operands - Rotate right by immediate (S=0) (no cond) */
EXTERN_C void slv6_X_ADD_M1_RRImm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.60--A5.1.5--NC
 * RSB -- Data processing operands - Logical shift left by immediate (S=1) (no cond) */
EXTERN_C void slv6_X_RSB_M1_LSLImm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.60--A5.1.5--NC
 * RSB -- Data processing operands - Logical shift left by immediate (S=0) (no cond) */
EXTERN_C void slv6_X_RSB_M1_LSLImm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.100--A5.2.8--NC
 * STRB -- Load and Store Word or Unsigned Byte - Immediate post indexed (no cond) */
EXTERN_C void slv6_X_STRB_M2_Imm_postInd_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint32_t signed_offset_12);

/* A4.1.97--A5.4.2--NC
 * STM (1) -- Load and Store Multiple - Increment after (W=1) (no cond) */
EXTERN_C void slv6_X_STM1_M4_IA_W1_NC(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list);

/* A4.1.97--A5.4.2--NC
 * STM (1) -- Load and Store Multiple - Increment after (W=0) (no cond) */
EXTERN_C void slv6_X_STM1_M4_IA_W0_NC(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list);

/* A4.1.117--A5.1.3--NC
 * TST -- Data processing operands - Immediate (no cond) */
EXTERN_C void slv6_X_TST_M1_Imm_NC(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated);

/* A4.1.97--A5.4.5--NC
 * STM (1) -- Load and Store Multiple - Decrement before (W=1) (no cond) */
EXTERN_C void slv6_X_STM1_M4_DB_W1_NC(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list);

/* A4.1.97--A5.4.5--NC
 * STM (1) -- Load and Store Multiple - Decrement before (W=0) (no cond) */
EXTERN_C void slv6_X_STM1_M4_DB_W0_NC(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list);

/* A4.1.41--A5.1.4--NC
 * MVN -- Data processing operands - Register (S=1) (no cond) */
EXTERN_C void slv6_X_MVN_M1_Reg_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m);

/* A4.1.41--A5.1.4--NC
 * MVN -- Data processing operands - Register (S=0) (no cond) */
EXTERN_C void slv6_X_MVN_M1_Reg_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m);

/* A4.1.97--A5.4.3--NC
 * STM (1) -- Load and Store Multiple - Increment before (W=1) (no cond) */
EXTERN_C void slv6_X_STM1_M4_IB_W1_NC(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list);

/* A4.1.97--A5.4.3--NC
 * STM (1) -- Load and Store Multiple - Increment before (W=0) (no cond) */
EXTERN_C void slv6_X_STM1_M4_IB_W0_NC(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list);

/* A4.1.3--A5.1.7--NC
 * ADD -- Data processing operands - Logical shift right by immediate (S=1) (no cond) */
EXTERN_C void slv6_X_ADD_M1_LSRImm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.3--A5.1.7--NC
 * ADD -- Data processing operands - Logical shift right by immediate (S=0) (no cond) */
EXTERN_C void slv6_X_ADD_M1_LSRImm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.99--A5.2.8--NC
 * STR -- Load and Store Word or Unsigned Byte - Immediate post indexed (no cond) */
EXTERN_C void slv6_X_STR_M2_Imm_postInd_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint32_t signed_offset_12);

/* A4.1.24--A5.2.4--NC
 * LDRB -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) (no cond) */
EXTERN_C void slv6_X_LDRB_M2_ScRegOff_U1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm);

/* A4.1.24--A5.2.4--NC
 * LDRB -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) (no cond) */
EXTERN_C void slv6_X_LDRB_M2_ScRegOff_U0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm);

/* A4.1.106--A5.1.5--NC
 * SUB -- Data processing operands - Logical shift left by immediate (S=1) (no cond) */
EXTERN_C void slv6_X_SUB_M1_LSLImm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.106--A5.1.5--NC
 * SUB -- Data processing operands - Logical shift left by immediate (S=0) (no cond) */
EXTERN_C void slv6_X_SUB_M1_LSLImm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.20--A5.4.3--NC
 * LDM (1) -- Load and Store Multiple - Increment before (W=1) (no cond) */
EXTERN_C void slv6_X_LDM1_M4_IB_W1_NC(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list);

/* A4.1.20--A5.4.3--NC
 * LDM (1) -- Load and Store Multiple - Increment before (W=0) (no cond) */
EXTERN_C void slv6_X_LDM1_M4_IB_W0_NC(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list);

/* A4.1.28--A5.3.2--NC
 * LDRH -- Miscellaneous Loads and Stores - Immediate offset (U=1) (no cond) */
EXTERN_C void slv6_X_LDRH_M3_ImmOff_U1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL);

/* A4.1.28--A5.3.2--NC
 * LDRH -- Miscellaneous Loads and Stores - Immediate offset (U=0) (no cond) */
EXTERN_C void slv6_X_LDRH_M3_ImmOff_U0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL);

/* A4.1.23--A5.2.5--NC
 * LDR -- Load and Store Word or Unsigned Byte - Immediate pre indexed (no cond) */
EXTERN_C void slv6_X_LDR_M2_Imm_preInd_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint32_t signed_offset_12);

/* A4.1.87--NC
 * SMULL (S=1) (no cond) */
EXTERN_C void slv6_X_SMULL_S1_NC(struct SLv6_Processor*,
    const uint8_t dHi,
    const uint8_t dLo,
    const uint8_t m,
    const uint8_t s);

/* A4.1.87--NC
 * SMULL (S=0) (no cond) */
EXTERN_C void slv6_X_SMULL_S0_NC(struct SLv6_Processor*,
    const uint8_t dHi,
    const uint8_t dLo,
    const uint8_t m,
    const uint8_t s);

/* A4.1.60--A5.1.9--NC
 * RSB -- Data processing operands - Arithmetic shift right by immediate (S=1) (no cond) */
EXTERN_C void slv6_X_RSB_M1_ASRImm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.60--A5.1.9--NC
 * RSB -- Data processing operands - Arithmetic shift right by immediate (S=0) (no cond) */
EXTERN_C void slv6_X_RSB_M1_ASRImm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.117--A5.1.4--NC
 * TST -- Data processing operands - Register (no cond) */
EXTERN_C void slv6_X_TST_M1_Reg_NC(struct SLv6_Processor*,
    const uint8_t m,
    const uint8_t n);

/* A4.1.18--A5.1.3--NC
 * EOR -- Data processing operands - Immediate (S=1) (no cond) */
EXTERN_C void slv6_X_EOR_M1_Imm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated);

/* A4.1.18--A5.1.3--NC
 * EOR -- Data processing operands - Immediate (S=0) (no cond) */
EXTERN_C void slv6_X_EOR_M1_Imm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated);

/* A4.1.42--A5.1.9--NC
 * ORR -- Data processing operands - Arithmetic shift right by immediate (S=1) (no cond) */
EXTERN_C void slv6_X_ORR_M1_ASRImm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.42--A5.1.9--NC
 * ORR -- Data processing operands - Arithmetic shift right by immediate (S=0) (no cond) */
EXTERN_C void slv6_X_ORR_M1_ASRImm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.42--A5.1.3--NC
 * ORR -- Data processing operands - Immediate (S=1) (no cond) */
EXTERN_C void slv6_X_ORR_M1_Imm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated);

/* A4.1.42--A5.1.3--NC
 * ORR -- Data processing operands - Immediate (S=0) (no cond) */
EXTERN_C void slv6_X_ORR_M1_Imm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated);

/* A4.1.106--A5.1.9--NC
 * SUB -- Data processing operands - Arithmetic shift right by immediate (S=1) (no cond) */
EXTERN_C void slv6_X_SUB_M1_ASRImm_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.106--A5.1.9--NC
 * SUB -- Data processing operands - Arithmetic shift right by immediate (S=0) (no cond) */
EXTERN_C void slv6_X_SUB_M1_ASRImm_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm);

/* A4.1.35--A5.1.6--NC
 * MOV -- Data processing operands - Logical shift left by register (S=1) (no cond) */
EXTERN_C void slv6_X_MOV_M1_LSLReg_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s);

/* A4.1.35--A5.1.6--NC
 * MOV -- Data processing operands - Logical shift left by register (S=0) (no cond) */
EXTERN_C void slv6_X_MOV_M1_LSLReg_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s);

/* A4.1.40--NC
 * MUL (S=1) (no cond) */
EXTERN_C void slv6_X_MUL_S1_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s);

/* A4.1.40--NC
 * MUL (S=0) (no cond) */
EXTERN_C void slv6_X_MUL_S0_NC(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s);

/* A4.1.14--A5.1.3--NC
 * CMN -- Data processing operands - Immediate (no cond) */
EXTERN_C void slv6_X_CMN_M1_Imm_NC(struct SLv6_Processor*,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated);

/* A7.1.28--NI
 * LDR (1) (no immed) */
EXTERN_C void slv6_X_Tb_LDR1_NI(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t n);

/* A7.1.38--NI
 * LSL (1) (no immed) */
EXTERN_C void slv6_X_Tb_LSL1_NI(struct SLv6_Processor*,
    const uint8_t d,
    const uint8_t m);

END_SIMSOC_NAMESPACE

#endif /* SLV6_ISS_expanded_H */
