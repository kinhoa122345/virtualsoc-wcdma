#ifndef SLV6_ISS_grouped_H
#define SLV6_ISS_grouped_H

#include "common.h"
#include "slv6_mode.h"
#include "slv6_condition.h"

BEGIN_SIMSOC_NAMESPACE

struct SLv6_Processor;
struct SLv6_Instruction;

/* A4.1.23--A5.2.2
 * LDR -- Load and Store Word or Unsigned Byte - Immediate offset */
/* weight = 253085083 */
extern void slv6_G_LDR_M2_ImmOff(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.99--A5.2.2
 * STR -- Load and Store Word or Unsigned Byte - Immediate offset */
/* weight = 101104185 */
extern void slv6_G_STR_M2_ImmOff(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.5
 * B, BL (L=1) */
/* weight = 69969620 */
extern void slv6_G_B_L1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.5
 * B, BL (L=0) */
/* weight = 69969620 */
extern void slv6_G_B_L0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.106--A5.1.3
 * SUB -- Data processing operands - Immediate (S=1) */
/* weight = 57119445 */
extern void slv6_G_SUB_M1_Imm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.106--A5.1.3
 * SUB -- Data processing operands - Immediate (S=0) */
/* weight = 57119445 */
extern void slv6_G_SUB_M1_Imm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.15--A5.1.4
 * CMP -- Data processing operands - Register */
/* weight = 55573782 */
extern void slv6_G_CMP_M1_Reg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.3--A5.1.3
 * ADD -- Data processing operands - Immediate (S=1) */
/* weight = 51883576 */
extern void slv6_G_ADD_M1_Imm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.3--A5.1.3
 * ADD -- Data processing operands - Immediate (S=0) */
/* weight = 51883576 */
extern void slv6_G_ADD_M1_Imm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.3--A5.1.4
 * ADD -- Data processing operands - Register (S=1) */
/* weight = 43627279 */
extern void slv6_G_ADD_M1_Reg_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.3--A5.1.4
 * ADD -- Data processing operands - Register (S=0) */
/* weight = 43627279 */
extern void slv6_G_ADD_M1_Reg_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.18--A5.1.4
 * EOR -- Data processing operands - Register (S=1) */
/* weight = 39333295 */
extern void slv6_G_EOR_M1_Reg_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.18--A5.1.4
 * EOR -- Data processing operands - Register (S=0) */
/* weight = 39333295 */
extern void slv6_G_EOR_M1_Reg_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.4--A5.1.3
 * AND -- Data processing operands - Immediate (S=1) */
/* weight = 27604337 */
extern void slv6_G_AND_M1_Imm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.4--A5.1.3
 * AND -- Data processing operands - Immediate (S=0) */
/* weight = 27604337 */
extern void slv6_G_AND_M1_Imm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.7
 * MOV -- Data processing operands - Logical shift right by immediate (S=1) */
/* weight = 24601166 */
extern void slv6_G_MOV_M1_LSRImm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.7
 * MOV -- Data processing operands - Logical shift right by immediate (S=0) */
/* weight = 24601166 */
extern void slv6_G_MOV_M1_LSRImm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.17
 * CPY */
/* weight = 19536208 */
extern void slv6_G_CPY(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.5
 * MOV -- Data processing operands - Logical shift left by immediate (S=1) */
/* weight = 18984950 */
extern void slv6_G_MOV_M1_LSLImm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.5
 * MOV -- Data processing operands - Logical shift left by immediate (S=0) */
/* weight = 18984950 */
extern void slv6_G_MOV_M1_LSLImm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.3
 * MOV -- Data processing operands - Immediate (S=1) */
/* weight = 14713777 */
extern void slv6_G_MOV_M1_Imm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.3
 * MOV -- Data processing operands - Immediate (S=0) */
/* weight = 14713777 */
extern void slv6_G_MOV_M1_Imm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.20--A5.4.2
 * LDM (1) -- Load and Store Multiple - Increment after (W=1) */
/* weight = 14139011 */
extern void slv6_G_LDM1_M4_IA_W1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.20--A5.4.2
 * LDM (1) -- Load and Store Multiple - Increment after (W=0) */
/* weight = 14139011 */
extern void slv6_G_LDM1_M4_IA_W0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.15--A5.1.3
 * CMP -- Data processing operands - Immediate */
/* weight = 12310848 */
extern void slv6_G_CMP_M1_Imm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.23--A5.2.4
 * LDR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) */
/* weight = 10681437 */
extern void slv6_G_LDR_M2_ScRegOff_U1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.23--A5.2.4
 * LDR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) */
/* weight = 10681437 */
extern void slv6_G_LDR_M2_ScRegOff_U0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.10
 * BX */
/* weight = 8065436 */
extern void slv6_G_BX(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.3--A5.1.5
 * ADD -- Data processing operands - Logical shift left by immediate (S=1) */
/* weight = 6931827 */
extern void slv6_G_ADD_M1_LSLImm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.3--A5.1.5
 * ADD -- Data processing operands - Logical shift left by immediate (S=0) */
/* weight = 6931827 */
extern void slv6_G_ADD_M1_LSLImm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.24--A5.2.2
 * LDRB -- Load and Store Word or Unsigned Byte - Immediate offset */
/* weight = 6906640 */
extern void slv6_G_LDRB_M2_ImmOff(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.42--A5.1.4
 * ORR -- Data processing operands - Register (S=1) */
/* weight = 6806204 */
extern void slv6_G_ORR_M1_Reg_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.42--A5.1.4
 * ORR -- Data processing operands - Register (S=0) */
/* weight = 6806204 */
extern void slv6_G_ORR_M1_Reg_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.11
 * MOV -- Data processing operands - Rotate right by immediate (S=1) */
/* weight = 5346301 */
extern void slv6_G_MOV_M1_RRImm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.11
 * MOV -- Data processing operands - Rotate right by immediate (S=0) */
/* weight = 5346301 */
extern void slv6_G_MOV_M1_RRImm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.23--A5.2.8
 * LDR -- Load and Store Word or Unsigned Byte - Immediate post indexed */
/* weight = 4918495 */
extern void slv6_G_LDR_M2_Imm_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.18--A5.1.11
 * EOR -- Data processing operands - Rotate right by immediate (S=1) */
/* weight = 4358144 */
extern void slv6_G_EOR_M1_RRImm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.18--A5.1.11
 * EOR -- Data processing operands - Rotate right by immediate (S=0) */
/* weight = 4358144 */
extern void slv6_G_EOR_M1_RRImm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.4--A5.1.4
 * AND -- Data processing operands - Register (S=1) */
/* weight = 4238848 */
extern void slv6_G_AND_M1_Reg_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.4--A5.1.4
 * AND -- Data processing operands - Register (S=0) */
/* weight = 4238848 */
extern void slv6_G_AND_M1_Reg_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.99--A5.2.5
 * STR -- Load and Store Word or Unsigned Byte - Immediate pre indexed */
/* weight = 3993434 */
extern void slv6_G_STR_M2_Imm_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.100--A5.2.2
 * STRB -- Load and Store Word or Unsigned Byte - Immediate offset */
/* weight = 3167635 */
extern void slv6_G_STRB_M2_ImmOff(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.42--A5.1.5
 * ORR -- Data processing operands - Logical shift left by immediate (S=1) */
/* weight = 3106144 */
extern void slv6_G_ORR_M1_LSLImm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.42--A5.1.5
 * ORR -- Data processing operands - Logical shift left by immediate (S=0) */
/* weight = 3106144 */
extern void slv6_G_ORR_M1_LSLImm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.2--A5.1.4
 * ADC -- Data processing operands - Register (S=1) */
/* weight = 2554368 */
extern void slv6_G_ADC_M1_Reg_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.2--A5.1.4
 * ADC -- Data processing operands - Register (S=0) */
/* weight = 2554368 */
extern void slv6_G_ADC_M1_Reg_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.24--A5.2.3
 * LDRB -- Load and Store Word or Unsigned Byte - Register offset (U=1) */
/* weight = 2327120 */
extern void slv6_G_LDRB_M2_RegOff_U1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.24--A5.2.3
 * LDRB -- Load and Store Word or Unsigned Byte - Register offset (U=0) */
/* weight = 2327120 */
extern void slv6_G_LDRB_M2_RegOff_U0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.60--A5.1.4
 * RSB -- Data processing operands - Register (S=1) */
/* weight = 2083886 */
extern void slv6_G_RSB_M1_Reg_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.60--A5.1.4
 * RSB -- Data processing operands - Register (S=0) */
/* weight = 2083886 */
extern void slv6_G_RSB_M1_Reg_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.6--A5.1.3
 * BIC -- Data processing operands - Immediate (S=1) */
/* weight = 1734061 */
extern void slv6_G_BIC_M1_Imm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.6--A5.1.3
 * BIC -- Data processing operands - Immediate (S=0) */
/* weight = 1734061 */
extern void slv6_G_BIC_M1_Imm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.41--A5.1.3
 * MVN -- Data processing operands - Immediate (S=1) */
/* weight = 1393258 */
extern void slv6_G_MVN_M1_Imm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.41--A5.1.3
 * MVN -- Data processing operands - Immediate (S=0) */
/* weight = 1393258 */
extern void slv6_G_MVN_M1_Imm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.42--A5.1.7
 * ORR -- Data processing operands - Logical shift right by immediate (S=1) */
/* weight = 1372157 */
extern void slv6_G_ORR_M1_LSRImm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.42--A5.1.7
 * ORR -- Data processing operands - Logical shift right by immediate (S=0) */
/* weight = 1372157 */
extern void slv6_G_ORR_M1_LSRImm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.18--A5.1.7
 * EOR -- Data processing operands - Logical shift right by immediate (S=1) */
/* weight = 1312720 */
extern void slv6_G_EOR_M1_LSRImm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.18--A5.1.7
 * EOR -- Data processing operands - Logical shift right by immediate (S=0) */
/* weight = 1312720 */
extern void slv6_G_EOR_M1_LSRImm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.23--A5.2.3
 * LDR -- Load and Store Word or Unsigned Byte - Register offset (U=1) */
/* weight = 1269491 */
extern void slv6_G_LDR_M2_RegOff_U1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.23--A5.2.3
 * LDR -- Load and Store Word or Unsigned Byte - Register offset (U=0) */
/* weight = 1269491 */
extern void slv6_G_LDR_M2_RegOff_U0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.8
 * MOV -- Data processing operands - Logical shift right by register (S=1) */
/* weight = 1056272 */
extern void slv6_G_MOV_M1_LSRReg_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.8
 * MOV -- Data processing operands - Logical shift right by register (S=0) */
/* weight = 1056272 */
extern void slv6_G_MOV_M1_LSRReg_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.100--A5.2.3
 * STRB -- Load and Store Word or Unsigned Byte - Register offset (U=1) */
/* weight = 968189 */
extern void slv6_G_STRB_M2_RegOff_U1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.100--A5.2.3
 * STRB -- Load and Store Word or Unsigned Byte - Register offset (U=0) */
/* weight = 968189 */
extern void slv6_G_STRB_M2_RegOff_U0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.99--A5.2.4
 * STR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) */
/* weight = 838541 */
extern void slv6_G_STR_M2_ScRegOff_U1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.99--A5.2.4
 * STR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) */
/* weight = 838541 */
extern void slv6_G_STR_M2_ScRegOff_U0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.14--A5.1.4
 * CMN -- Data processing operands - Register */
/* weight = 612640 */
extern void slv6_G_CMN_M1_Reg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.99--A5.2.9
 * STR -- Load and Store Word or Unsigned Byte - Register post indexed (U=1) */
/* weight = 612640 */
extern void slv6_G_STR_M2_Reg_postInd_U1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.99--A5.2.9
 * STR -- Load and Store Word or Unsigned Byte - Register post indexed (U=0) */
/* weight = 612640 */
extern void slv6_G_STR_M2_Reg_postInd_U0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.99--A5.2.3
 * STR -- Load and Store Word or Unsigned Byte - Register offset (U=1) */
/* weight = 542572 */
extern void slv6_G_STR_M2_RegOff_U1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.99--A5.2.3
 * STR -- Load and Store Word or Unsigned Byte - Register offset (U=0) */
/* weight = 542572 */
extern void slv6_G_STR_M2_RegOff_U0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.18--A5.1.5
 * EOR -- Data processing operands - Logical shift left by immediate (S=1) */
/* weight = 462398 */
extern void slv6_G_EOR_M1_LSLImm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.18--A5.1.5
 * EOR -- Data processing operands - Logical shift left by immediate (S=0) */
/* weight = 462398 */
extern void slv6_G_EOR_M1_LSLImm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.60--A5.1.3
 * RSB -- Data processing operands - Immediate (S=1) */
/* weight = 377779 */
extern void slv6_G_RSB_M1_Imm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.60--A5.1.3
 * RSB -- Data processing operands - Immediate (S=0) */
/* weight = 377779 */
extern void slv6_G_RSB_M1_Imm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.9
 * MOV -- Data processing operands - Arithmetic shift right by immediate (S=1) */
/* weight = 340365 */
extern void slv6_G_MOV_M1_ASRImm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.9
 * MOV -- Data processing operands - Arithmetic shift right by immediate (S=0) */
/* weight = 340365 */
extern void slv6_G_MOV_M1_ASRImm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.3--A5.1.11
 * ADD -- Data processing operands - Rotate right by immediate (S=1) */
/* weight = 266240 */
extern void slv6_G_ADD_M1_RRImm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.3--A5.1.11
 * ADD -- Data processing operands - Rotate right by immediate (S=0) */
/* weight = 266240 */
extern void slv6_G_ADD_M1_RRImm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.60--A5.1.5
 * RSB -- Data processing operands - Logical shift left by immediate (S=1) */
/* weight = 264959 */
extern void slv6_G_RSB_M1_LSLImm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.60--A5.1.5
 * RSB -- Data processing operands - Logical shift left by immediate (S=0) */
/* weight = 264959 */
extern void slv6_G_RSB_M1_LSLImm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.100--A5.2.8
 * STRB -- Load and Store Word or Unsigned Byte - Immediate post indexed */
/* weight = 262176 */
extern void slv6_G_STRB_M2_Imm_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.97--A5.4.2
 * STM (1) -- Load and Store Multiple - Increment after (W=1) */
/* weight = 252529 */
extern void slv6_G_STM1_M4_IA_W1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.97--A5.4.2
 * STM (1) -- Load and Store Multiple - Increment after (W=0) */
/* weight = 252529 */
extern void slv6_G_STM1_M4_IA_W0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.117--A5.1.3
 * TST -- Data processing operands - Immediate */
/* weight = 236793 */
extern void slv6_G_TST_M1_Imm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.97--A5.4.5
 * STM (1) -- Load and Store Multiple - Decrement before (W=1) */
/* weight = 236571 */
extern void slv6_G_STM1_M4_DB_W1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.97--A5.4.5
 * STM (1) -- Load and Store Multiple - Decrement before (W=0) */
/* weight = 236571 */
extern void slv6_G_STM1_M4_DB_W0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.41--A5.1.4
 * MVN -- Data processing operands - Register (S=1) */
/* weight = 99840 */
extern void slv6_G_MVN_M1_Reg_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.41--A5.1.4
 * MVN -- Data processing operands - Register (S=0) */
/* weight = 99840 */
extern void slv6_G_MVN_M1_Reg_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.97--A5.4.3
 * STM (1) -- Load and Store Multiple - Increment before (W=1) */
/* weight = 98338 */
extern void slv6_G_STM1_M4_IB_W1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.97--A5.4.3
 * STM (1) -- Load and Store Multiple - Increment before (W=0) */
/* weight = 98338 */
extern void slv6_G_STM1_M4_IB_W0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.3--A5.1.7
 * ADD -- Data processing operands - Logical shift right by immediate (S=1) */
/* weight = 98336 */
extern void slv6_G_ADD_M1_LSRImm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.3--A5.1.7
 * ADD -- Data processing operands - Logical shift right by immediate (S=0) */
/* weight = 98336 */
extern void slv6_G_ADD_M1_LSRImm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.99--A5.2.8
 * STR -- Load and Store Word or Unsigned Byte - Immediate post indexed */
/* weight = 96053 */
extern void slv6_G_STR_M2_Imm_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.24--A5.2.4
 * LDRB -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) */
/* weight = 79552 */
extern void slv6_G_LDRB_M2_ScRegOff_U1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.24--A5.2.4
 * LDRB -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) */
/* weight = 79552 */
extern void slv6_G_LDRB_M2_ScRegOff_U0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.106--A5.1.5
 * SUB -- Data processing operands - Logical shift left by immediate (S=1) */
/* weight = 63184 */
extern void slv6_G_SUB_M1_LSLImm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.106--A5.1.5
 * SUB -- Data processing operands - Logical shift left by immediate (S=0) */
/* weight = 63184 */
extern void slv6_G_SUB_M1_LSLImm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.20--A5.4.3
 * LDM (1) -- Load and Store Multiple - Increment before (W=1) */
/* weight = 37088 */
extern void slv6_G_LDM1_M4_IB_W1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.20--A5.4.3
 * LDM (1) -- Load and Store Multiple - Increment before (W=0) */
/* weight = 37088 */
extern void slv6_G_LDM1_M4_IB_W0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.28--A5.3.2
 * LDRH -- Miscellaneous Loads and Stores - Immediate offset (U=1) */
/* weight = 35072 */
extern void slv6_G_LDRH_M3_ImmOff_U1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.28--A5.3.2
 * LDRH -- Miscellaneous Loads and Stores - Immediate offset (U=0) */
/* weight = 35072 */
extern void slv6_G_LDRH_M3_ImmOff_U0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.23--A5.2.5
 * LDR -- Load and Store Word or Unsigned Byte - Immediate pre indexed */
/* weight = 11634 */
extern void slv6_G_LDR_M2_Imm_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.87
 * SMULL (S=1) */
/* weight = 2136 */
extern void slv6_G_SMULL_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.87
 * SMULL (S=0) */
/* weight = 2136 */
extern void slv6_G_SMULL_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.60--A5.1.9
 * RSB -- Data processing operands - Arithmetic shift right by immediate (S=1) */
/* weight = 1020 */
extern void slv6_G_RSB_M1_ASRImm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.60--A5.1.9
 * RSB -- Data processing operands - Arithmetic shift right by immediate (S=0) */
/* weight = 1020 */
extern void slv6_G_RSB_M1_ASRImm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.117--A5.1.4
 * TST -- Data processing operands - Register */
/* weight = 512 */
extern void slv6_G_TST_M1_Reg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.18--A5.1.3
 * EOR -- Data processing operands - Immediate (S=1) */
/* weight = 510 */
extern void slv6_G_EOR_M1_Imm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.18--A5.1.3
 * EOR -- Data processing operands - Immediate (S=0) */
/* weight = 510 */
extern void slv6_G_EOR_M1_Imm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.42--A5.1.9
 * ORR -- Data processing operands - Arithmetic shift right by immediate (S=1) */
/* weight = 255 */
extern void slv6_G_ORR_M1_ASRImm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.42--A5.1.9
 * ORR -- Data processing operands - Arithmetic shift right by immediate (S=0) */
/* weight = 255 */
extern void slv6_G_ORR_M1_ASRImm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.42--A5.1.3
 * ORR -- Data processing operands - Immediate (S=1) */
/* weight = 104 */
extern void slv6_G_ORR_M1_Imm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.42--A5.1.3
 * ORR -- Data processing operands - Immediate (S=0) */
/* weight = 104 */
extern void slv6_G_ORR_M1_Imm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.106--A5.1.9
 * SUB -- Data processing operands - Arithmetic shift right by immediate (S=1) */
/* weight = 64 */
extern void slv6_G_SUB_M1_ASRImm_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.106--A5.1.9
 * SUB -- Data processing operands - Arithmetic shift right by immediate (S=0) */
/* weight = 64 */
extern void slv6_G_SUB_M1_ASRImm_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.6
 * MOV -- Data processing operands - Logical shift left by register (S=1) */
/* weight = 20 */
extern void slv6_G_MOV_M1_LSLReg_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.6
 * MOV -- Data processing operands - Logical shift left by register (S=0) */
/* weight = 20 */
extern void slv6_G_MOV_M1_LSLReg_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.40
 * MUL (S=1) */
/* weight = 13 */
extern void slv6_G_MUL_S1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.40
 * MUL (S=0) */
/* weight = 13 */
extern void slv6_G_MUL_S0(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.14--A5.1.3
 * CMN -- Data processing operands - Immediate */
/* weight = 12 */
extern void slv6_G_CMN_M1_Imm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.2--A5.1.3
 * ADC -- Data processing operands - Immediate */
/* weight = 0 */
extern void slv6_G_ADC_M1_Imm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.2--A5.1.5
 * ADC -- Data processing operands - Logical shift left by immediate */
/* weight = 0 */
extern void slv6_G_ADC_M1_LSLImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.2--A5.1.6
 * ADC -- Data processing operands - Logical shift left by register */
/* weight = 0 */
extern void slv6_G_ADC_M1_LSLReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.2--A5.1.7
 * ADC -- Data processing operands - Logical shift right by immediate */
/* weight = 0 */
extern void slv6_G_ADC_M1_LSRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.2--A5.1.8
 * ADC -- Data processing operands - Logical shift right by register */
/* weight = 0 */
extern void slv6_G_ADC_M1_LSRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.2--A5.1.9
 * ADC -- Data processing operands - Arithmetic shift right by immediate */
/* weight = 0 */
extern void slv6_G_ADC_M1_ASRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.2--A5.1.10
 * ADC -- Data processing operands - Arithmetic shift right by register */
/* weight = 0 */
extern void slv6_G_ADC_M1_ASRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.2--A5.1.11
 * ADC -- Data processing operands - Rotate right by immediate */
/* weight = 0 */
extern void slv6_G_ADC_M1_RRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.2--A5.1.12
 * ADC -- Data processing operands - Rotate right by register */
/* weight = 0 */
extern void slv6_G_ADC_M1_RRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.2--A5.1.13
 * ADC -- Data processing operands - Rotate right with extend */
/* weight = 0 */
extern void slv6_G_ADC_M1_RRE(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.3--A5.1.6
 * ADD -- Data processing operands - Logical shift left by register */
/* weight = 0 */
extern void slv6_G_ADD_M1_LSLReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.3--A5.1.8
 * ADD -- Data processing operands - Logical shift right by register */
/* weight = 0 */
extern void slv6_G_ADD_M1_LSRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.3--A5.1.9
 * ADD -- Data processing operands - Arithmetic shift right by immediate */
/* weight = 0 */
extern void slv6_G_ADD_M1_ASRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.3--A5.1.10
 * ADD -- Data processing operands - Arithmetic shift right by register */
/* weight = 0 */
extern void slv6_G_ADD_M1_ASRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.3--A5.1.12
 * ADD -- Data processing operands - Rotate right by register */
/* weight = 0 */
extern void slv6_G_ADD_M1_RRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.3--A5.1.13
 * ADD -- Data processing operands - Rotate right with extend */
/* weight = 0 */
extern void slv6_G_ADD_M1_RRE(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.4--A5.1.5
 * AND -- Data processing operands - Logical shift left by immediate */
/* weight = 0 */
extern void slv6_G_AND_M1_LSLImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.4--A5.1.6
 * AND -- Data processing operands - Logical shift left by register */
/* weight = 0 */
extern void slv6_G_AND_M1_LSLReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.4--A5.1.7
 * AND -- Data processing operands - Logical shift right by immediate */
/* weight = 0 */
extern void slv6_G_AND_M1_LSRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.4--A5.1.8
 * AND -- Data processing operands - Logical shift right by register */
/* weight = 0 */
extern void slv6_G_AND_M1_LSRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.4--A5.1.9
 * AND -- Data processing operands - Arithmetic shift right by immediate */
/* weight = 0 */
extern void slv6_G_AND_M1_ASRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.4--A5.1.10
 * AND -- Data processing operands - Arithmetic shift right by register */
/* weight = 0 */
extern void slv6_G_AND_M1_ASRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.4--A5.1.11
 * AND -- Data processing operands - Rotate right by immediate */
/* weight = 0 */
extern void slv6_G_AND_M1_RRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.4--A5.1.12
 * AND -- Data processing operands - Rotate right by register */
/* weight = 0 */
extern void slv6_G_AND_M1_RRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.4--A5.1.13
 * AND -- Data processing operands - Rotate right with extend */
/* weight = 0 */
extern void slv6_G_AND_M1_RRE(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.6--A5.1.4
 * BIC -- Data processing operands - Register */
/* weight = 0 */
extern void slv6_G_BIC_M1_Reg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.6--A5.1.5
 * BIC -- Data processing operands - Logical shift left by immediate */
/* weight = 0 */
extern void slv6_G_BIC_M1_LSLImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.6--A5.1.6
 * BIC -- Data processing operands - Logical shift left by register */
/* weight = 0 */
extern void slv6_G_BIC_M1_LSLReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.6--A5.1.7
 * BIC -- Data processing operands - Logical shift right by immediate */
/* weight = 0 */
extern void slv6_G_BIC_M1_LSRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.6--A5.1.8
 * BIC -- Data processing operands - Logical shift right by register */
/* weight = 0 */
extern void slv6_G_BIC_M1_LSRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.6--A5.1.9
 * BIC -- Data processing operands - Arithmetic shift right by immediate */
/* weight = 0 */
extern void slv6_G_BIC_M1_ASRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.6--A5.1.10
 * BIC -- Data processing operands - Arithmetic shift right by register */
/* weight = 0 */
extern void slv6_G_BIC_M1_ASRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.6--A5.1.11
 * BIC -- Data processing operands - Rotate right by immediate */
/* weight = 0 */
extern void slv6_G_BIC_M1_RRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.6--A5.1.12
 * BIC -- Data processing operands - Rotate right by register */
/* weight = 0 */
extern void slv6_G_BIC_M1_RRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.6--A5.1.13
 * BIC -- Data processing operands - Rotate right with extend */
/* weight = 0 */
extern void slv6_G_BIC_M1_RRE(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.7
 * BKPT */
/* weight = 0 */
extern void slv6_G_BKPT(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.8
 * BLX (1) */
/* weight = 0 */
extern void slv6_G_BLX1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.9
 * BLX (2) */
/* weight = 0 */
extern void slv6_G_BLX2(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.11
 * BXJ */
/* weight = 0 */
extern void slv6_G_BXJ(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.12
 * CDP */
/* weight = 0 */
extern void slv6_G_CDP(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.13
 * CLZ */
/* weight = 0 */
extern void slv6_G_CLZ(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.14--A5.1.5
 * CMN -- Data processing operands - Logical shift left by immediate */
/* weight = 0 */
extern void slv6_G_CMN_M1_LSLImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.14--A5.1.6
 * CMN -- Data processing operands - Logical shift left by register */
/* weight = 0 */
extern void slv6_G_CMN_M1_LSLReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.14--A5.1.7
 * CMN -- Data processing operands - Logical shift right by immediate */
/* weight = 0 */
extern void slv6_G_CMN_M1_LSRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.14--A5.1.8
 * CMN -- Data processing operands - Logical shift right by register */
/* weight = 0 */
extern void slv6_G_CMN_M1_LSRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.14--A5.1.9
 * CMN -- Data processing operands - Arithmetic shift right by immediate */
/* weight = 0 */
extern void slv6_G_CMN_M1_ASRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.14--A5.1.10
 * CMN -- Data processing operands - Arithmetic shift right by register */
/* weight = 0 */
extern void slv6_G_CMN_M1_ASRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.14--A5.1.11
 * CMN -- Data processing operands - Rotate right by immediate */
/* weight = 0 */
extern void slv6_G_CMN_M1_RRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.14--A5.1.12
 * CMN -- Data processing operands - Rotate right by register */
/* weight = 0 */
extern void slv6_G_CMN_M1_RRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.14--A5.1.13
 * CMN -- Data processing operands - Rotate right with extend */
/* weight = 0 */
extern void slv6_G_CMN_M1_RRE(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.15--A5.1.5
 * CMP -- Data processing operands - Logical shift left by immediate */
/* weight = 0 */
extern void slv6_G_CMP_M1_LSLImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.15--A5.1.6
 * CMP -- Data processing operands - Logical shift left by register */
/* weight = 0 */
extern void slv6_G_CMP_M1_LSLReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.15--A5.1.7
 * CMP -- Data processing operands - Logical shift right by immediate */
/* weight = 0 */
extern void slv6_G_CMP_M1_LSRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.15--A5.1.8
 * CMP -- Data processing operands - Logical shift right by register */
/* weight = 0 */
extern void slv6_G_CMP_M1_LSRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.15--A5.1.9
 * CMP -- Data processing operands - Arithmetic shift right by immediate */
/* weight = 0 */
extern void slv6_G_CMP_M1_ASRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.15--A5.1.10
 * CMP -- Data processing operands - Arithmetic shift right by register */
/* weight = 0 */
extern void slv6_G_CMP_M1_ASRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.15--A5.1.11
 * CMP -- Data processing operands - Rotate right by immediate */
/* weight = 0 */
extern void slv6_G_CMP_M1_RRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.15--A5.1.12
 * CMP -- Data processing operands - Rotate right by register */
/* weight = 0 */
extern void slv6_G_CMP_M1_RRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.15--A5.1.13
 * CMP -- Data processing operands - Rotate right with extend */
/* weight = 0 */
extern void slv6_G_CMP_M1_RRE(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.16
 * CPS */
/* weight = 0 */
extern void slv6_G_CPS(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.18--A5.1.6
 * EOR -- Data processing operands - Logical shift left by register */
/* weight = 0 */
extern void slv6_G_EOR_M1_LSLReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.18--A5.1.8
 * EOR -- Data processing operands - Logical shift right by register */
/* weight = 0 */
extern void slv6_G_EOR_M1_LSRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.18--A5.1.9
 * EOR -- Data processing operands - Arithmetic shift right by immediate */
/* weight = 0 */
extern void slv6_G_EOR_M1_ASRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.18--A5.1.10
 * EOR -- Data processing operands - Arithmetic shift right by register */
/* weight = 0 */
extern void slv6_G_EOR_M1_ASRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.18--A5.1.12
 * EOR -- Data processing operands - Rotate right by register */
/* weight = 0 */
extern void slv6_G_EOR_M1_RRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.18--A5.1.13
 * EOR -- Data processing operands - Rotate right with extend */
/* weight = 0 */
extern void slv6_G_EOR_M1_RRE(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.19--A5.5.2
 * LDC -- Load and Store Coprocessor - Immediate offset */
/* weight = 0 */
extern void slv6_G_LDC_M5_ImmOff(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.19--A5.5.3
 * LDC -- Load and Store Coprocessor - Immediate pre indexed */
/* weight = 0 */
extern void slv6_G_LDC_M5_Imm_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.19--A5.5.4
 * LDC -- Load and Store Coprocessor - Immediate post indexed */
/* weight = 0 */
extern void slv6_G_LDC_M5_Imm_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.19--A5.5.5
 * LDC -- Load and Store Coprocessor - Unindexed */
/* weight = 0 */
extern void slv6_G_LDC_M5_U(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.20--A5.4.4
 * LDM (1) -- Load and Store Multiple - Decrement after */
/* weight = 0 */
extern void slv6_G_LDM1_M4_DA(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.20--A5.4.5
 * LDM (1) -- Load and Store Multiple - Decrement before */
/* weight = 0 */
extern void slv6_G_LDM1_M4_DB(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.21--A5.4.2
 * LDM (2) -- Load and Store Multiple - Increment after */
/* weight = 0 */
extern void slv6_G_LDM2_M4_IA(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.21--A5.4.3
 * LDM (2) -- Load and Store Multiple - Increment before */
/* weight = 0 */
extern void slv6_G_LDM2_M4_IB(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.21--A5.4.4
 * LDM (2) -- Load and Store Multiple - Decrement after */
/* weight = 0 */
extern void slv6_G_LDM2_M4_DA(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.21--A5.4.5
 * LDM (2) -- Load and Store Multiple - Decrement before */
/* weight = 0 */
extern void slv6_G_LDM2_M4_DB(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.22--A5.4.2
 * LDM (3) -- Load and Store Multiple - Increment after */
/* weight = 0 */
extern void slv6_G_LDM3_M4_IA(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.22--A5.4.3
 * LDM (3) -- Load and Store Multiple - Increment before */
/* weight = 0 */
extern void slv6_G_LDM3_M4_IB(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.22--A5.4.4
 * LDM (3) -- Load and Store Multiple - Decrement after */
/* weight = 0 */
extern void slv6_G_LDM3_M4_DA(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.22--A5.4.5
 * LDM (3) -- Load and Store Multiple - Decrement before */
/* weight = 0 */
extern void slv6_G_LDM3_M4_DB(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.23--A5.2.6
 * LDR -- Load and Store Word or Unsigned Byte - Register pre indexed */
/* weight = 0 */
extern void slv6_G_LDR_M2_Reg_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.23--A5.2.7
 * LDR -- Load and Store Word or Unsigned Byte - Scaled register pre indexed */
/* weight = 0 */
extern void slv6_G_LDR_M2_ScReg_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.23--A5.2.9
 * LDR -- Load and Store Word or Unsigned Byte - Register post indexed */
/* weight = 0 */
extern void slv6_G_LDR_M2_Reg_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.23--A5.2.10
 * LDR -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
/* weight = 0 */
extern void slv6_G_LDR_M2_ScReg_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.24--A5.2.5
 * LDRB -- Load and Store Word or Unsigned Byte - Immediate pre indexed */
/* weight = 0 */
extern void slv6_G_LDRB_M2_Imm_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.24--A5.2.6
 * LDRB -- Load and Store Word or Unsigned Byte - Register pre indexed */
/* weight = 0 */
extern void slv6_G_LDRB_M2_Reg_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.24--A5.2.7
 * LDRB -- Load and Store Word or Unsigned Byte - Scaled register pre indexed */
/* weight = 0 */
extern void slv6_G_LDRB_M2_ScReg_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.24--A5.2.8
 * LDRB -- Load and Store Word or Unsigned Byte - Immediate post indexed */
/* weight = 0 */
extern void slv6_G_LDRB_M2_Imm_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.24--A5.2.9
 * LDRB -- Load and Store Word or Unsigned Byte - Register post indexed */
/* weight = 0 */
extern void slv6_G_LDRB_M2_Reg_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.24--A5.2.10
 * LDRB -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
/* weight = 0 */
extern void slv6_G_LDRB_M2_ScReg_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.25--A5.2.8
 * LDRBT -- Load and Store Word or Unsigned Byte - Immediate post indexed */
/* weight = 0 */
extern void slv6_G_LDRBT_M2_Imm_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.25--A5.2.9
 * LDRBT -- Load and Store Word or Unsigned Byte - Register post indexed */
/* weight = 0 */
extern void slv6_G_LDRBT_M2_Reg_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.25--A5.2.10
 * LDRBT -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
/* weight = 0 */
extern void slv6_G_LDRBT_M2_ScReg_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.26--A5.3.2
 * LDRD -- Miscellaneous Loads and Stores - Immediate offset */
/* weight = 0 */
extern void slv6_G_LDRD_M3_ImmOff(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.26--A5.3.3
 * LDRD -- Miscellaneous Loads and Stores - Register offset */
/* weight = 0 */
extern void slv6_G_LDRD_M3_RegOff(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.26--A5.3.4
 * LDRD -- Miscellaneous Loads and Stores - Immediate pre indexed */
/* weight = 0 */
extern void slv6_G_LDRD_M3_Imm_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.26--A5.3.5
 * LDRD -- Miscellaneous Loads and Stores - Register pre indexed */
/* weight = 0 */
extern void slv6_G_LDRD_M3_Reg_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.26--A5.3.6
 * LDRD -- Miscellaneous Loads and Stores - Immediate post indexed */
/* weight = 0 */
extern void slv6_G_LDRD_M3_Imm_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.26--A5.3.7
 * LDRD -- Miscellaneous Loads and Stores - Register post indexed */
/* weight = 0 */
extern void slv6_G_LDRD_M3_Reg_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.27
 * LDREX */
/* weight = 0 */
extern void slv6_G_LDREX(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.28--A5.3.3
 * LDRH -- Miscellaneous Loads and Stores - Register offset */
/* weight = 0 */
extern void slv6_G_LDRH_M3_RegOff(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.28--A5.3.4
 * LDRH -- Miscellaneous Loads and Stores - Immediate pre indexed */
/* weight = 0 */
extern void slv6_G_LDRH_M3_Imm_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.28--A5.3.5
 * LDRH -- Miscellaneous Loads and Stores - Register pre indexed */
/* weight = 0 */
extern void slv6_G_LDRH_M3_Reg_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.28--A5.3.6
 * LDRH -- Miscellaneous Loads and Stores - Immediate post indexed */
/* weight = 0 */
extern void slv6_G_LDRH_M3_Imm_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.28--A5.3.7
 * LDRH -- Miscellaneous Loads and Stores - Register post indexed */
/* weight = 0 */
extern void slv6_G_LDRH_M3_Reg_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.29--A5.3.2
 * LDRSB -- Miscellaneous Loads and Stores - Immediate offset */
/* weight = 0 */
extern void slv6_G_LDRSB_M3_ImmOff(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.29--A5.3.3
 * LDRSB -- Miscellaneous Loads and Stores - Register offset */
/* weight = 0 */
extern void slv6_G_LDRSB_M3_RegOff(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.29--A5.3.4
 * LDRSB -- Miscellaneous Loads and Stores - Immediate pre indexed */
/* weight = 0 */
extern void slv6_G_LDRSB_M3_Imm_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.29--A5.3.5
 * LDRSB -- Miscellaneous Loads and Stores - Register pre indexed */
/* weight = 0 */
extern void slv6_G_LDRSB_M3_Reg_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.29--A5.3.6
 * LDRSB -- Miscellaneous Loads and Stores - Immediate post indexed */
/* weight = 0 */
extern void slv6_G_LDRSB_M3_Imm_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.29--A5.3.7
 * LDRSB -- Miscellaneous Loads and Stores - Register post indexed */
/* weight = 0 */
extern void slv6_G_LDRSB_M3_Reg_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.30--A5.3.2
 * LDRSH -- Miscellaneous Loads and Stores - Immediate offset */
/* weight = 0 */
extern void slv6_G_LDRSH_M3_ImmOff(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.30--A5.3.3
 * LDRSH -- Miscellaneous Loads and Stores - Register offset */
/* weight = 0 */
extern void slv6_G_LDRSH_M3_RegOff(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.30--A5.3.4
 * LDRSH -- Miscellaneous Loads and Stores - Immediate pre indexed */
/* weight = 0 */
extern void slv6_G_LDRSH_M3_Imm_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.30--A5.3.5
 * LDRSH -- Miscellaneous Loads and Stores - Register pre indexed */
/* weight = 0 */
extern void slv6_G_LDRSH_M3_Reg_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.30--A5.3.6
 * LDRSH -- Miscellaneous Loads and Stores - Immediate post indexed */
/* weight = 0 */
extern void slv6_G_LDRSH_M3_Imm_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.30--A5.3.7
 * LDRSH -- Miscellaneous Loads and Stores - Register post indexed */
/* weight = 0 */
extern void slv6_G_LDRSH_M3_Reg_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.31--A5.2.8
 * LDRT -- Load and Store Word or Unsigned Byte - Immediate post indexed */
/* weight = 0 */
extern void slv6_G_LDRT_M2_Imm_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.31--A5.2.9
 * LDRT -- Load and Store Word or Unsigned Byte - Register post indexed */
/* weight = 0 */
extern void slv6_G_LDRT_M2_Reg_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.31--A5.2.10
 * LDRT -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
/* weight = 0 */
extern void slv6_G_LDRT_M2_ScReg_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.32
 * MCR */
/* weight = 0 */
extern void slv6_G_MCR(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.33
 * MCRR */
/* weight = 0 */
extern void slv6_G_MCRR(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.34
 * MLA */
/* weight = 0 */
extern void slv6_G_MLA(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.35--A5.1.4
 * MOV -- Data processing operands - Register */
/* weight = 0 */
extern void slv6_G_MOV_M1_Reg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.35--A5.1.10
 * MOV -- Data processing operands - Arithmetic shift right by register */
/* weight = 0 */
extern void slv6_G_MOV_M1_ASRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.35--A5.1.12
 * MOV -- Data processing operands - Rotate right by register */
/* weight = 0 */
extern void slv6_G_MOV_M1_RRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.35--A5.1.13
 * MOV -- Data processing operands - Rotate right with extend */
/* weight = 0 */
extern void slv6_G_MOV_M1_RRE(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.36
 * MRC */
/* weight = 0 */
extern void slv6_G_MRC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.37
 * MRRC */
/* weight = 0 */
extern void slv6_G_MRRC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.38
 * MRS */
/* weight = 0 */
extern void slv6_G_MRS(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.39
 * MSRimm */
/* weight = 0 */
extern void slv6_G_MSRimm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.39
 * MSRreg */
/* weight = 0 */
extern void slv6_G_MSRreg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.41--A5.1.5
 * MVN -- Data processing operands - Logical shift left by immediate */
/* weight = 0 */
extern void slv6_G_MVN_M1_LSLImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.41--A5.1.6
 * MVN -- Data processing operands - Logical shift left by register */
/* weight = 0 */
extern void slv6_G_MVN_M1_LSLReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.41--A5.1.7
 * MVN -- Data processing operands - Logical shift right by immediate */
/* weight = 0 */
extern void slv6_G_MVN_M1_LSRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.41--A5.1.8
 * MVN -- Data processing operands - Logical shift right by register */
/* weight = 0 */
extern void slv6_G_MVN_M1_LSRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.41--A5.1.9
 * MVN -- Data processing operands - Arithmetic shift right by immediate */
/* weight = 0 */
extern void slv6_G_MVN_M1_ASRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.41--A5.1.10
 * MVN -- Data processing operands - Arithmetic shift right by register */
/* weight = 0 */
extern void slv6_G_MVN_M1_ASRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.41--A5.1.11
 * MVN -- Data processing operands - Rotate right by immediate */
/* weight = 0 */
extern void slv6_G_MVN_M1_RRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.41--A5.1.12
 * MVN -- Data processing operands - Rotate right by register */
/* weight = 0 */
extern void slv6_G_MVN_M1_RRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.41--A5.1.13
 * MVN -- Data processing operands - Rotate right with extend */
/* weight = 0 */
extern void slv6_G_MVN_M1_RRE(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.42--A5.1.6
 * ORR -- Data processing operands - Logical shift left by register */
/* weight = 0 */
extern void slv6_G_ORR_M1_LSLReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.42--A5.1.8
 * ORR -- Data processing operands - Logical shift right by register */
/* weight = 0 */
extern void slv6_G_ORR_M1_LSRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.42--A5.1.10
 * ORR -- Data processing operands - Arithmetic shift right by register */
/* weight = 0 */
extern void slv6_G_ORR_M1_ASRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.42--A5.1.11
 * ORR -- Data processing operands - Rotate right by immediate */
/* weight = 0 */
extern void slv6_G_ORR_M1_RRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.42--A5.1.12
 * ORR -- Data processing operands - Rotate right by register */
/* weight = 0 */
extern void slv6_G_ORR_M1_RRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.42--A5.1.13
 * ORR -- Data processing operands - Rotate right with extend */
/* weight = 0 */
extern void slv6_G_ORR_M1_RRE(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.43
 * PKHBT */
/* weight = 0 */
extern void slv6_G_PKHBT(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.44
 * PKHTB */
/* weight = 0 */
extern void slv6_G_PKHTB(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.45--A5.2.2
 * PLD -- Load and Store Word or Unsigned Byte - Immediate offset */
/* weight = 0 */
extern void slv6_G_PLD_M2_ImmOff(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.45--A5.2.3
 * PLD -- Load and Store Word or Unsigned Byte - Register offset */
/* weight = 0 */
extern void slv6_G_PLD_M2_RegOff(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.45--A5.2.4
 * PLD -- Load and Store Word or Unsigned Byte - Scaled register offset */
/* weight = 0 */
extern void slv6_G_PLD_M2_ScRegOff(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.46
 * QADD */
/* weight = 0 */
extern void slv6_G_QADD(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.47
 * QADD16 */
/* weight = 0 */
extern void slv6_G_QADD16(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.48
 * QADD8 */
/* weight = 0 */
extern void slv6_G_QADD8(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.49
 * QADDSUBX */
/* weight = 0 */
extern void slv6_G_QADDSUBX(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.50
 * QDADD */
/* weight = 0 */
extern void slv6_G_QDADD(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.51
 * QDSUB */
/* weight = 0 */
extern void slv6_G_QDSUB(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.52
 * QSUB */
/* weight = 0 */
extern void slv6_G_QSUB(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.53
 * QSUB16 */
/* weight = 0 */
extern void slv6_G_QSUB16(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.54
 * QSUB8 */
/* weight = 0 */
extern void slv6_G_QSUB8(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.55
 * QSUBADDX */
/* weight = 0 */
extern void slv6_G_QSUBADDX(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.56
 * REV */
/* weight = 0 */
extern void slv6_G_REV(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.57
 * REV16 */
/* weight = 0 */
extern void slv6_G_REV16(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.58
 * REVSH */
/* weight = 0 */
extern void slv6_G_REVSH(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.59--A5.4.2
 * RFE -- Load and Store Multiple - Increment after */
/* weight = 0 */
extern void slv6_G_RFE_M4_IA(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.59--A5.4.3
 * RFE -- Load and Store Multiple - Increment before */
/* weight = 0 */
extern void slv6_G_RFE_M4_IB(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.59--A5.4.4
 * RFE -- Load and Store Multiple - Decrement after */
/* weight = 0 */
extern void slv6_G_RFE_M4_DA(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.59--A5.4.5
 * RFE -- Load and Store Multiple - Decrement before */
/* weight = 0 */
extern void slv6_G_RFE_M4_DB(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.60--A5.1.6
 * RSB -- Data processing operands - Logical shift left by register */
/* weight = 0 */
extern void slv6_G_RSB_M1_LSLReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.60--A5.1.7
 * RSB -- Data processing operands - Logical shift right by immediate */
/* weight = 0 */
extern void slv6_G_RSB_M1_LSRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.60--A5.1.8
 * RSB -- Data processing operands - Logical shift right by register */
/* weight = 0 */
extern void slv6_G_RSB_M1_LSRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.60--A5.1.10
 * RSB -- Data processing operands - Arithmetic shift right by register */
/* weight = 0 */
extern void slv6_G_RSB_M1_ASRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.60--A5.1.11
 * RSB -- Data processing operands - Rotate right by immediate */
/* weight = 0 */
extern void slv6_G_RSB_M1_RRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.60--A5.1.12
 * RSB -- Data processing operands - Rotate right by register */
/* weight = 0 */
extern void slv6_G_RSB_M1_RRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.60--A5.1.13
 * RSB -- Data processing operands - Rotate right with extend */
/* weight = 0 */
extern void slv6_G_RSB_M1_RRE(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.61--A5.1.3
 * RSC -- Data processing operands - Immediate */
/* weight = 0 */
extern void slv6_G_RSC_M1_Imm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.61--A5.1.4
 * RSC -- Data processing operands - Register */
/* weight = 0 */
extern void slv6_G_RSC_M1_Reg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.61--A5.1.5
 * RSC -- Data processing operands - Logical shift left by immediate */
/* weight = 0 */
extern void slv6_G_RSC_M1_LSLImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.61--A5.1.6
 * RSC -- Data processing operands - Logical shift left by register */
/* weight = 0 */
extern void slv6_G_RSC_M1_LSLReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.61--A5.1.7
 * RSC -- Data processing operands - Logical shift right by immediate */
/* weight = 0 */
extern void slv6_G_RSC_M1_LSRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.61--A5.1.8
 * RSC -- Data processing operands - Logical shift right by register */
/* weight = 0 */
extern void slv6_G_RSC_M1_LSRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.61--A5.1.9
 * RSC -- Data processing operands - Arithmetic shift right by immediate */
/* weight = 0 */
extern void slv6_G_RSC_M1_ASRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.61--A5.1.10
 * RSC -- Data processing operands - Arithmetic shift right by register */
/* weight = 0 */
extern void slv6_G_RSC_M1_ASRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.61--A5.1.11
 * RSC -- Data processing operands - Rotate right by immediate */
/* weight = 0 */
extern void slv6_G_RSC_M1_RRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.61--A5.1.12
 * RSC -- Data processing operands - Rotate right by register */
/* weight = 0 */
extern void slv6_G_RSC_M1_RRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.61--A5.1.13
 * RSC -- Data processing operands - Rotate right with extend */
/* weight = 0 */
extern void slv6_G_RSC_M1_RRE(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.62
 * SADD16 */
/* weight = 0 */
extern void slv6_G_SADD16(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.63
 * SADD8 */
/* weight = 0 */
extern void slv6_G_SADD8(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.64
 * SADDSUBX */
/* weight = 0 */
extern void slv6_G_SADDSUBX(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.65--A5.1.3
 * SBC -- Data processing operands - Immediate */
/* weight = 0 */
extern void slv6_G_SBC_M1_Imm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.65--A5.1.4
 * SBC -- Data processing operands - Register */
/* weight = 0 */
extern void slv6_G_SBC_M1_Reg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.65--A5.1.5
 * SBC -- Data processing operands - Logical shift left by immediate */
/* weight = 0 */
extern void slv6_G_SBC_M1_LSLImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.65--A5.1.6
 * SBC -- Data processing operands - Logical shift left by register */
/* weight = 0 */
extern void slv6_G_SBC_M1_LSLReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.65--A5.1.7
 * SBC -- Data processing operands - Logical shift right by immediate */
/* weight = 0 */
extern void slv6_G_SBC_M1_LSRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.65--A5.1.8
 * SBC -- Data processing operands - Logical shift right by register */
/* weight = 0 */
extern void slv6_G_SBC_M1_LSRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.65--A5.1.9
 * SBC -- Data processing operands - Arithmetic shift right by immediate */
/* weight = 0 */
extern void slv6_G_SBC_M1_ASRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.65--A5.1.10
 * SBC -- Data processing operands - Arithmetic shift right by register */
/* weight = 0 */
extern void slv6_G_SBC_M1_ASRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.65--A5.1.11
 * SBC -- Data processing operands - Rotate right by immediate */
/* weight = 0 */
extern void slv6_G_SBC_M1_RRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.65--A5.1.12
 * SBC -- Data processing operands - Rotate right by register */
/* weight = 0 */
extern void slv6_G_SBC_M1_RRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.65--A5.1.13
 * SBC -- Data processing operands - Rotate right with extend */
/* weight = 0 */
extern void slv6_G_SBC_M1_RRE(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.66
 * SEL */
/* weight = 0 */
extern void slv6_G_SEL(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.67
 * SETEND */
/* weight = 0 */
extern void slv6_G_SETEND(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.68
 * SHADD16 */
/* weight = 0 */
extern void slv6_G_SHADD16(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.69
 * SHADD8 */
/* weight = 0 */
extern void slv6_G_SHADD8(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.70
 * SHADDSUBX */
/* weight = 0 */
extern void slv6_G_SHADDSUBX(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.71
 * SHSUB16 */
/* weight = 0 */
extern void slv6_G_SHSUB16(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.72
 * SHSUB8 */
/* weight = 0 */
extern void slv6_G_SHSUB8(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.73
 * SHSUBADDX */
/* weight = 0 */
extern void slv6_G_SHSUBADDX(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.74
 * SMLA<x><y> */
/* weight = 0 */
extern void slv6_G_SMLAxy(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.75
 * SMLAD */
/* weight = 0 */
extern void slv6_G_SMLAD(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.76
 * SMLAL */
/* weight = 0 */
extern void slv6_G_SMLAL(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.77
 * SMLAL<x><y> */
/* weight = 0 */
extern void slv6_G_SMLALxy(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.78
 * SMLALD */
/* weight = 0 */
extern void slv6_G_SMLALD(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.79
 * SMLAW<y> */
/* weight = 0 */
extern void slv6_G_SMLAWy(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.80
 * SMLSD */
/* weight = 0 */
extern void slv6_G_SMLSD(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.81
 * SMLSLD */
/* weight = 0 */
extern void slv6_G_SMLSLD(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.82
 * SMMLA */
/* weight = 0 */
extern void slv6_G_SMMLA(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.83
 * SMMLS */
/* weight = 0 */
extern void slv6_G_SMMLS(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.84
 * SMMUL */
/* weight = 0 */
extern void slv6_G_SMMUL(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.85
 * SMUAD */
/* weight = 0 */
extern void slv6_G_SMUAD(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.86
 * SMUL<x><y> */
/* weight = 0 */
extern void slv6_G_SMULxy(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.88
 * SMULW<y> */
/* weight = 0 */
extern void slv6_G_SMULWy(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.89
 * SMUSD */
/* weight = 0 */
extern void slv6_G_SMUSD(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.90--A5.4.2
 * SRS -- Load and Store Multiple - Increment after */
/* weight = 0 */
extern void slv6_G_SRS_M4_IA(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.90--A5.4.3
 * SRS -- Load and Store Multiple - Increment before */
/* weight = 0 */
extern void slv6_G_SRS_M4_IB(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.90--A5.4.4
 * SRS -- Load and Store Multiple - Decrement after */
/* weight = 0 */
extern void slv6_G_SRS_M4_DA(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.90--A5.4.5
 * SRS -- Load and Store Multiple - Decrement before */
/* weight = 0 */
extern void slv6_G_SRS_M4_DB(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.91
 * SSAT */
/* weight = 0 */
extern void slv6_G_SSAT(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.92
 * SSAT16 */
/* weight = 0 */
extern void slv6_G_SSAT16(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.93
 * SSUB16 */
/* weight = 0 */
extern void slv6_G_SSUB16(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.94
 * SSUB8 */
/* weight = 0 */
extern void slv6_G_SSUB8(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.95
 * SSUBADDX */
/* weight = 0 */
extern void slv6_G_SSUBADDX(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.96--A5.5.2
 * STC -- Load and Store Coprocessor - Immediate offset */
/* weight = 0 */
extern void slv6_G_STC_M5_ImmOff(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.96--A5.5.3
 * STC -- Load and Store Coprocessor - Immediate pre indexed */
/* weight = 0 */
extern void slv6_G_STC_M5_Imm_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.96--A5.5.4
 * STC -- Load and Store Coprocessor - Immediate post indexed */
/* weight = 0 */
extern void slv6_G_STC_M5_Imm_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.96--A5.5.5
 * STC -- Load and Store Coprocessor - Unindexed */
/* weight = 0 */
extern void slv6_G_STC_M5_U(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.97--A5.4.4
 * STM (1) -- Load and Store Multiple - Decrement after */
/* weight = 0 */
extern void slv6_G_STM1_M4_DA(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.98--A5.4.2
 * STM (2) -- Load and Store Multiple - Increment after */
/* weight = 0 */
extern void slv6_G_STM2_M4_IA(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.98--A5.4.3
 * STM (2) -- Load and Store Multiple - Increment before */
/* weight = 0 */
extern void slv6_G_STM2_M4_IB(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.98--A5.4.4
 * STM (2) -- Load and Store Multiple - Decrement after */
/* weight = 0 */
extern void slv6_G_STM2_M4_DA(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.98--A5.4.5
 * STM (2) -- Load and Store Multiple - Decrement before */
/* weight = 0 */
extern void slv6_G_STM2_M4_DB(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.99--A5.2.6
 * STR -- Load and Store Word or Unsigned Byte - Register pre indexed */
/* weight = 0 */
extern void slv6_G_STR_M2_Reg_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.99--A5.2.7
 * STR -- Load and Store Word or Unsigned Byte - Scaled register pre indexed */
/* weight = 0 */
extern void slv6_G_STR_M2_ScReg_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.99--A5.2.10
 * STR -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
/* weight = 0 */
extern void slv6_G_STR_M2_ScReg_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.100--A5.2.4
 * STRB -- Load and Store Word or Unsigned Byte - Scaled register offset */
/* weight = 0 */
extern void slv6_G_STRB_M2_ScRegOff(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.100--A5.2.5
 * STRB -- Load and Store Word or Unsigned Byte - Immediate pre indexed */
/* weight = 0 */
extern void slv6_G_STRB_M2_Imm_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.100--A5.2.6
 * STRB -- Load and Store Word or Unsigned Byte - Register pre indexed */
/* weight = 0 */
extern void slv6_G_STRB_M2_Reg_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.100--A5.2.7
 * STRB -- Load and Store Word or Unsigned Byte - Scaled register pre indexed */
/* weight = 0 */
extern void slv6_G_STRB_M2_ScReg_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.100--A5.2.9
 * STRB -- Load and Store Word or Unsigned Byte - Register post indexed */
/* weight = 0 */
extern void slv6_G_STRB_M2_Reg_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.100--A5.2.10
 * STRB -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
/* weight = 0 */
extern void slv6_G_STRB_M2_ScReg_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.101--A5.2.8
 * STRBT -- Load and Store Word or Unsigned Byte - Immediate post indexed */
/* weight = 0 */
extern void slv6_G_STRBT_M2_Imm_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.101--A5.2.9
 * STRBT -- Load and Store Word or Unsigned Byte - Register post indexed */
/* weight = 0 */
extern void slv6_G_STRBT_M2_Reg_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.101--A5.2.10
 * STRBT -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
/* weight = 0 */
extern void slv6_G_STRBT_M2_ScReg_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.102--A5.3.2
 * STRD -- Miscellaneous Loads and Stores - Immediate offset */
/* weight = 0 */
extern void slv6_G_STRD_M3_ImmOff(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.102--A5.3.3
 * STRD -- Miscellaneous Loads and Stores - Register offset */
/* weight = 0 */
extern void slv6_G_STRD_M3_RegOff(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.102--A5.3.4
 * STRD -- Miscellaneous Loads and Stores - Immediate pre indexed */
/* weight = 0 */
extern void slv6_G_STRD_M3_Imm_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.102--A5.3.5
 * STRD -- Miscellaneous Loads and Stores - Register pre indexed */
/* weight = 0 */
extern void slv6_G_STRD_M3_Reg_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.102--A5.3.6
 * STRD -- Miscellaneous Loads and Stores - Immediate post indexed */
/* weight = 0 */
extern void slv6_G_STRD_M3_Imm_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.102--A5.3.7
 * STRD -- Miscellaneous Loads and Stores - Register post indexed */
/* weight = 0 */
extern void slv6_G_STRD_M3_Reg_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.103
 * STREX */
/* weight = 0 */
extern void slv6_G_STREX(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.104--A5.3.2
 * STRH -- Miscellaneous Loads and Stores - Immediate offset */
/* weight = 0 */
extern void slv6_G_STRH_M3_ImmOff(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.104--A5.3.3
 * STRH -- Miscellaneous Loads and Stores - Register offset */
/* weight = 0 */
extern void slv6_G_STRH_M3_RegOff(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.104--A5.3.4
 * STRH -- Miscellaneous Loads and Stores - Immediate pre indexed */
/* weight = 0 */
extern void slv6_G_STRH_M3_Imm_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.104--A5.3.5
 * STRH -- Miscellaneous Loads and Stores - Register pre indexed */
/* weight = 0 */
extern void slv6_G_STRH_M3_Reg_preInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.104--A5.3.6
 * STRH -- Miscellaneous Loads and Stores - Immediate post indexed */
/* weight = 0 */
extern void slv6_G_STRH_M3_Imm_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.104--A5.3.7
 * STRH -- Miscellaneous Loads and Stores - Register post indexed */
/* weight = 0 */
extern void slv6_G_STRH_M3_Reg_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.105--A5.2.8
 * STRT -- Load and Store Word or Unsigned Byte - Immediate post indexed */
/* weight = 0 */
extern void slv6_G_STRT_M2_Imm_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.105--A5.2.9
 * STRT -- Load and Store Word or Unsigned Byte - Register post indexed */
/* weight = 0 */
extern void slv6_G_STRT_M2_Reg_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.105--A5.2.10
 * STRT -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
/* weight = 0 */
extern void slv6_G_STRT_M2_ScReg_postInd(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.106--A5.1.4
 * SUB -- Data processing operands - Register */
/* weight = 0 */
extern void slv6_G_SUB_M1_Reg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.106--A5.1.6
 * SUB -- Data processing operands - Logical shift left by register */
/* weight = 0 */
extern void slv6_G_SUB_M1_LSLReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.106--A5.1.7
 * SUB -- Data processing operands - Logical shift right by immediate */
/* weight = 0 */
extern void slv6_G_SUB_M1_LSRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.106--A5.1.8
 * SUB -- Data processing operands - Logical shift right by register */
/* weight = 0 */
extern void slv6_G_SUB_M1_LSRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.106--A5.1.10
 * SUB -- Data processing operands - Arithmetic shift right by register */
/* weight = 0 */
extern void slv6_G_SUB_M1_ASRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.106--A5.1.11
 * SUB -- Data processing operands - Rotate right by immediate */
/* weight = 0 */
extern void slv6_G_SUB_M1_RRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.106--A5.1.12
 * SUB -- Data processing operands - Rotate right by register */
/* weight = 0 */
extern void slv6_G_SUB_M1_RRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.106--A5.1.13
 * SUB -- Data processing operands - Rotate right with extend */
/* weight = 0 */
extern void slv6_G_SUB_M1_RRE(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.107
 * SWI */
/* weight = 0 */
extern void slv6_G_SWI(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.108
 * SWP */
/* weight = 0 */
extern void slv6_G_SWP(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.109
 * SWPB */
/* weight = 0 */
extern void slv6_G_SWPB(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.110
 * SXTAB */
/* weight = 0 */
extern void slv6_G_SXTAB(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.111
 * SXTAB16 */
/* weight = 0 */
extern void slv6_G_SXTAB16(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.112
 * SXTAH */
/* weight = 0 */
extern void slv6_G_SXTAH(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.113
 * SXTB */
/* weight = 0 */
extern void slv6_G_SXTB(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.114
 * SXTB16 */
/* weight = 0 */
extern void slv6_G_SXTB16(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.115
 * SXTH */
/* weight = 0 */
extern void slv6_G_SXTH(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.116--A5.1.3
 * TEQ -- Data processing operands - Immediate */
/* weight = 0 */
extern void slv6_G_TEQ_M1_Imm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.116--A5.1.4
 * TEQ -- Data processing operands - Register */
/* weight = 0 */
extern void slv6_G_TEQ_M1_Reg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.116--A5.1.5
 * TEQ -- Data processing operands - Logical shift left by immediate */
/* weight = 0 */
extern void slv6_G_TEQ_M1_LSLImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.116--A5.1.6
 * TEQ -- Data processing operands - Logical shift left by register */
/* weight = 0 */
extern void slv6_G_TEQ_M1_LSLReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.116--A5.1.7
 * TEQ -- Data processing operands - Logical shift right by immediate */
/* weight = 0 */
extern void slv6_G_TEQ_M1_LSRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.116--A5.1.8
 * TEQ -- Data processing operands - Logical shift right by register */
/* weight = 0 */
extern void slv6_G_TEQ_M1_LSRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.116--A5.1.9
 * TEQ -- Data processing operands - Arithmetic shift right by immediate */
/* weight = 0 */
extern void slv6_G_TEQ_M1_ASRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.116--A5.1.10
 * TEQ -- Data processing operands - Arithmetic shift right by register */
/* weight = 0 */
extern void slv6_G_TEQ_M1_ASRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.116--A5.1.11
 * TEQ -- Data processing operands - Rotate right by immediate */
/* weight = 0 */
extern void slv6_G_TEQ_M1_RRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.116--A5.1.12
 * TEQ -- Data processing operands - Rotate right by register */
/* weight = 0 */
extern void slv6_G_TEQ_M1_RRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.116--A5.1.13
 * TEQ -- Data processing operands - Rotate right with extend */
/* weight = 0 */
extern void slv6_G_TEQ_M1_RRE(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.117--A5.1.5
 * TST -- Data processing operands - Logical shift left by immediate */
/* weight = 0 */
extern void slv6_G_TST_M1_LSLImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.117--A5.1.6
 * TST -- Data processing operands - Logical shift left by register */
/* weight = 0 */
extern void slv6_G_TST_M1_LSLReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.117--A5.1.7
 * TST -- Data processing operands - Logical shift right by immediate */
/* weight = 0 */
extern void slv6_G_TST_M1_LSRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.117--A5.1.8
 * TST -- Data processing operands - Logical shift right by register */
/* weight = 0 */
extern void slv6_G_TST_M1_LSRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.117--A5.1.9
 * TST -- Data processing operands - Arithmetic shift right by immediate */
/* weight = 0 */
extern void slv6_G_TST_M1_ASRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.117--A5.1.10
 * TST -- Data processing operands - Arithmetic shift right by register */
/* weight = 0 */
extern void slv6_G_TST_M1_ASRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.117--A5.1.11
 * TST -- Data processing operands - Rotate right by immediate */
/* weight = 0 */
extern void slv6_G_TST_M1_RRImm(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.117--A5.1.12
 * TST -- Data processing operands - Rotate right by register */
/* weight = 0 */
extern void slv6_G_TST_M1_RRReg(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.117--A5.1.13
 * TST -- Data processing operands - Rotate right with extend */
/* weight = 0 */
extern void slv6_G_TST_M1_RRE(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.118
 * UADD16 */
/* weight = 0 */
extern void slv6_G_UADD16(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.119
 * UADD8 */
/* weight = 0 */
extern void slv6_G_UADD8(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.120
 * UADDSUBX */
/* weight = 0 */
extern void slv6_G_UADDSUBX(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.121
 * UHADD16 */
/* weight = 0 */
extern void slv6_G_UHADD16(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.122
 * UHADD8 */
/* weight = 0 */
extern void slv6_G_UHADD8(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.123
 * UHADDSUBX */
/* weight = 0 */
extern void slv6_G_UHADDSUBX(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.124
 * UHSUB16 */
/* weight = 0 */
extern void slv6_G_UHSUB16(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.125
 * UHSUB8 */
/* weight = 0 */
extern void slv6_G_UHSUB8(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.126
 * UHSUBADDX */
/* weight = 0 */
extern void slv6_G_UHSUBADDX(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.127
 * UMAAL */
/* weight = 0 */
extern void slv6_G_UMAAL(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.128
 * UMLAL */
/* weight = 0 */
extern void slv6_G_UMLAL(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.129
 * UMULL */
/* weight = 0 */
extern void slv6_G_UMULL(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.130
 * UQADD16 */
/* weight = 0 */
extern void slv6_G_UQADD16(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.131
 * UQADD8 */
/* weight = 0 */
extern void slv6_G_UQADD8(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.132
 * UQADDSUBX */
/* weight = 0 */
extern void slv6_G_UQADDSUBX(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.133
 * UQSUB16 */
/* weight = 0 */
extern void slv6_G_UQSUB16(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.134
 * UQSUB8 */
/* weight = 0 */
extern void slv6_G_UQSUB8(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.135
 * UQSUBADDX */
/* weight = 0 */
extern void slv6_G_UQSUBADDX(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.136
 * USAD8 */
/* weight = 0 */
extern void slv6_G_USAD8(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.137
 * USADA8 */
/* weight = 0 */
extern void slv6_G_USADA8(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.138
 * USAT */
/* weight = 0 */
extern void slv6_G_USAT(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.139
 * USAT16 */
/* weight = 0 */
extern void slv6_G_USAT16(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.140
 * USUB16 */
/* weight = 0 */
extern void slv6_G_USUB16(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.141
 * USUB8 */
/* weight = 0 */
extern void slv6_G_USUB8(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.142
 * USUBADDX */
/* weight = 0 */
extern void slv6_G_USUBADDX(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.143
 * UXTAB */
/* weight = 0 */
extern void slv6_G_UXTAB(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.144
 * UXTAB16 */
/* weight = 0 */
extern void slv6_G_UXTAB16(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.145
 * UXTAH */
/* weight = 0 */
extern void slv6_G_UXTAH(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.146
 * UXTB */
/* weight = 0 */
extern void slv6_G_UXTB(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.147
 * UXTB16 */
/* weight = 0 */
extern void slv6_G_UXTB16(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.148
 * UXTH */
/* weight = 0 */
extern void slv6_G_UXTH(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A7.1.28
 * LDR (1) */
/* weight = 204454071 */
extern void slv6_G_Tb_LDR1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.25
 * CPY */
/* weight = 93104768 */
extern void slv6_G_Tb_CPY(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.58
 * STR (1) */
/* weight = 74000836 */
extern void slv6_G_Tb_STR1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.13
 * B (1) */
/* weight = 72858121 */
extern void slv6_G_Tb_B1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.38
 * LSL (1) */
/* weight = 70354701 */
extern void slv6_G_Tb_LSL1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.5
 * ADD (3) */
/* weight = 59264545 */
extern void slv6_G_Tb_ADD3(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.42
 * MOV (1) */
/* weight = 58469263 */
extern void slv6_G_Tb_MOV1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.22
 * CMP (2) */
/* weight = 52655907 */
extern void slv6_G_Tb_CMP2(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.30
 * LDR (3) */
/* weight = 46820179 */
extern void slv6_G_Tb_LDR3(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.26
 * EOR */
/* weight = 45467676 */
extern void slv6_G_Tb_EOR(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.66
 * SUB (2) */
/* weight = 41320872 */
extern void slv6_G_Tb_SUB2(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.43
 * MOV (2) */
/* weight = 33939593 */
extern void slv6_G_Tb_MOV2(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.4
 * ADD (2) */
/* weight = 32342636 */
extern void slv6_G_Tb_ADD2(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.31
 * LDR (4) */
/* weight = 31197661 */
extern void slv6_G_Tb_LDR4(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.10
 * AND */
/* weight = 30377894 */
extern void slv6_G_Tb_AND(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.40
 * LSR (1) */
/* weight = 29487874 */
extern void slv6_G_Tb_LSR1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.29
 * LDR (2) */
/* weight = 27579672 */
extern void slv6_G_Tb_LDR2(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.6
 * ADD (4) */
/* weight = 16720308 */
extern void slv6_G_Tb_ADD4(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.21
 * CMP (1) */
/* weight = 15942914 */
extern void slv6_G_Tb_CMP1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.48
 * ORR */
/* weight = 10999950 */
extern void slv6_G_Tb_ORR(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.60
 * STR (3) */
/* weight = 10613807 */
extern void slv6_G_Tb_STR3(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.54
 * ROR */
/* weight = 9976477 */
extern void slv6_G_Tb_ROR(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.17
 * BL, BLX (1) */
/* weight = 8518000 */
extern void slv6_G_Tb_BL(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.14
 * B (2) */
/* weight = 7714354 */
extern void slv6_G_Tb_B2(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.47
 * NEG */
/* weight = 6798619 */
extern void slv6_G_Tb_NEG(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.32
 * LDRB (1) */
/* weight = 6378256 */
extern void slv6_G_Tb_LDRB1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.50
 * PUSH */
/* weight = 4309413 */
extern void slv6_G_Tb_PUSH(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.49
 * POP */
/* weight = 4309410 */
extern void slv6_G_Tb_POP(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.23
 * CMP (3) */
/* weight = 4184292 */
extern void slv6_G_Tb_CMP3(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.68
 * SUB (4) */
/* weight = 4063925 */
extern void slv6_G_Tb_SUB4(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.9
 * ADD (7) */
/* weight = 4063922 */
extern void slv6_G_Tb_ADD7(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.8
 * ADD (6) */
/* weight = 4000933 */
extern void slv6_G_Tb_ADD6(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.19
 * BX */
/* weight = 3878668 */
extern void slv6_G_Tb_BX(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.61
 * STRB (1) */
/* weight = 3425426 */
extern void slv6_G_Tb_STRB1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.33
 * LDRB (2) */
/* weight = 2929680 */
extern void slv6_G_Tb_LDRB2(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.2
 * ADC */
/* weight = 2816466 */
extern void slv6_G_Tb_ADC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.67
 * SUB (3) */
/* weight = 2255333 */
extern void slv6_G_Tb_SUB3(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.65
 * SUB (1) */
/* weight = 2108666 */
extern void slv6_G_Tb_SUB1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.41
 * LSR (2) */
/* weight = 1056272 */
extern void slv6_G_Tb_LSR2(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.59
 * STR (2) */
/* weight = 982915 */
extern void slv6_G_Tb_STR2(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.62
 * STRB (2) */
/* weight = 972542 */
extern void slv6_G_Tb_STRB2(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.27
 * LDMIA */
/* weight = 801698 */
extern void slv6_G_Tb_LDMIA(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.57
 * STMIA */
/* weight = 776395 */
extern void slv6_G_Tb_STMIA(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.3
 * ADD (1) */
/* weight = 368423 */
extern void slv6_G_Tb_ADD1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.45
 * MUL */
/* weight = 331344 */
extern void slv6_G_Tb_MUL(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.11
 * ASR (1) */
/* weight = 311900 */
extern void slv6_G_Tb_ASR1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.46
 * MVN */
/* weight = 99840 */
extern void slv6_G_Tb_MVN(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.34
 * LDRH (1) */
/* weight = 34560 */
extern void slv6_G_Tb_LDRH1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.72
 * TST */
/* weight = 9783 */
extern void slv6_G_Tb_TST(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.15
 * BIC */
/* weight = 82 */
extern void slv6_G_Tb_BIC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.39
 * LSL (2) */
/* weight = 20 */
extern void slv6_G_Tb_LSL2(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.7
 * ADD (5) */
/* weight = 0 */
extern void slv6_G_Tb_ADD5(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A7.1.12
 * ASR (2) */
/* weight = 0 */
extern void slv6_G_Tb_ASR2(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A7.1.16
 * BKPT */
/* weight = 0 */
extern void slv6_G_Tb_BKPT(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A7.1.18
 * BLX (2) */
/* weight = 0 */
extern void slv6_G_Tb_BLX2(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A7.1.20
 * CMN */
/* weight = 0 */
extern void slv6_G_Tb_CMN(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A7.1.24
 * CPS */
/* weight = 0 */
extern void slv6_G_Tb_CPS(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A7.1.35
 * LDRH (2) */
/* weight = 0 */
extern void slv6_G_Tb_LDRH2(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A7.1.36
 * LDRSB */
/* weight = 0 */
extern void slv6_G_Tb_LDRSB(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A7.1.37
 * LDRSH */
/* weight = 0 */
extern void slv6_G_Tb_LDRSH(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A7.1.51
 * REV */
/* weight = 0 */
extern void slv6_G_Tb_REV(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A7.1.52
 * REV16 */
/* weight = 0 */
extern void slv6_G_Tb_REV16(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A7.1.53
 * REVSH */
/* weight = 0 */
extern void slv6_G_Tb_REVSH(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A7.1.55
 * SBC */
/* weight = 0 */
extern void slv6_G_Tb_SBC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A7.1.56
 * SETEND */
/* weight = 0 */
extern void slv6_G_Tb_SETEND(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A7.1.63
 * STRH (1) */
/* weight = 0 */
extern void slv6_G_Tb_STRH1(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A7.1.64
 * STRH (2) */
/* weight = 0 */
extern void slv6_G_Tb_STRH2(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A7.1.69
 * SWI */
/* weight = 0 */
extern void slv6_G_Tb_SWI(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A7.1.70
 * SXTB */
/* weight = 0 */
extern void slv6_G_Tb_SXTB(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A7.1.71
 * SXTH */
/* weight = 0 */
extern void slv6_G_Tb_SXTH(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A7.1.73
 * UXTB */
/* weight = 0 */
extern void slv6_G_Tb_UXTB(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A7.1.74
 * UXTH */
/* weight = 0 */
extern void slv6_G_Tb_UXTH(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_COLD;

/* A4.1.23--A5.2.2--NC
 * LDR -- Load and Store Word or Unsigned Byte - Immediate offset (no cond) */
/* weight = 253085083 */
extern void slv6_G_LDR_M2_ImmOff_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.99--A5.2.2--NC
 * STR -- Load and Store Word or Unsigned Byte - Immediate offset (no cond) */
/* weight = 101104185 */
extern void slv6_G_STR_M2_ImmOff_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.5--NC
 * B, BL (L=1) (no cond) */
/* weight = 69969620 */
extern void slv6_G_B_L1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.5--NC
 * B, BL (L=0) (no cond) */
/* weight = 69969620 */
extern void slv6_G_B_L0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.106--A5.1.3--NC
 * SUB -- Data processing operands - Immediate (S=1) (no cond) */
/* weight = 57119445 */
extern void slv6_G_SUB_M1_Imm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.106--A5.1.3--NC
 * SUB -- Data processing operands - Immediate (S=0) (no cond) */
/* weight = 57119445 */
extern void slv6_G_SUB_M1_Imm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.15--A5.1.4--NC
 * CMP -- Data processing operands - Register (no cond) */
/* weight = 55573782 */
extern void slv6_G_CMP_M1_Reg_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.3--A5.1.3--NC
 * ADD -- Data processing operands - Immediate (S=1) (no cond) */
/* weight = 51883576 */
extern void slv6_G_ADD_M1_Imm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.3--A5.1.3--NC
 * ADD -- Data processing operands - Immediate (S=0) (no cond) */
/* weight = 51883576 */
extern void slv6_G_ADD_M1_Imm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.3--A5.1.4--NC
 * ADD -- Data processing operands - Register (S=1) (no cond) */
/* weight = 43627279 */
extern void slv6_G_ADD_M1_Reg_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.3--A5.1.4--NC
 * ADD -- Data processing operands - Register (S=0) (no cond) */
/* weight = 43627279 */
extern void slv6_G_ADD_M1_Reg_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.18--A5.1.4--NC
 * EOR -- Data processing operands - Register (S=1) (no cond) */
/* weight = 39333295 */
extern void slv6_G_EOR_M1_Reg_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.18--A5.1.4--NC
 * EOR -- Data processing operands - Register (S=0) (no cond) */
/* weight = 39333295 */
extern void slv6_G_EOR_M1_Reg_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.4--A5.1.3--NC
 * AND -- Data processing operands - Immediate (S=1) (no cond) */
/* weight = 27604337 */
extern void slv6_G_AND_M1_Imm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.4--A5.1.3--NC
 * AND -- Data processing operands - Immediate (S=0) (no cond) */
/* weight = 27604337 */
extern void slv6_G_AND_M1_Imm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.7--NC
 * MOV -- Data processing operands - Logical shift right by immediate (S=1) (no cond) */
/* weight = 24601166 */
extern void slv6_G_MOV_M1_LSRImm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.7--NC
 * MOV -- Data processing operands - Logical shift right by immediate (S=0) (no cond) */
/* weight = 24601166 */
extern void slv6_G_MOV_M1_LSRImm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.17--NC
 * CPY (no cond) */
/* weight = 19536208 */
extern void slv6_G_CPY_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.5--NC
 * MOV -- Data processing operands - Logical shift left by immediate (S=1) (no cond) */
/* weight = 18984950 */
extern void slv6_G_MOV_M1_LSLImm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.5--NC
 * MOV -- Data processing operands - Logical shift left by immediate (S=0) (no cond) */
/* weight = 18984950 */
extern void slv6_G_MOV_M1_LSLImm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.3--NC
 * MOV -- Data processing operands - Immediate (S=1) (no cond) */
/* weight = 14713777 */
extern void slv6_G_MOV_M1_Imm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.3--NC
 * MOV -- Data processing operands - Immediate (S=0) (no cond) */
/* weight = 14713777 */
extern void slv6_G_MOV_M1_Imm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.20--A5.4.2--NC
 * LDM (1) -- Load and Store Multiple - Increment after (W=1) (no cond) */
/* weight = 14139011 */
extern void slv6_G_LDM1_M4_IA_W1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.20--A5.4.2--NC
 * LDM (1) -- Load and Store Multiple - Increment after (W=0) (no cond) */
/* weight = 14139011 */
extern void slv6_G_LDM1_M4_IA_W0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.15--A5.1.3--NC
 * CMP -- Data processing operands - Immediate (no cond) */
/* weight = 12310848 */
extern void slv6_G_CMP_M1_Imm_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.23--A5.2.4--NC
 * LDR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) (no cond) */
/* weight = 10681437 */
extern void slv6_G_LDR_M2_ScRegOff_U1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.23--A5.2.4--NC
 * LDR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) (no cond) */
/* weight = 10681437 */
extern void slv6_G_LDR_M2_ScRegOff_U0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.10--NC
 * BX (no cond) */
/* weight = 8065436 */
extern void slv6_G_BX_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.3--A5.1.5--NC
 * ADD -- Data processing operands - Logical shift left by immediate (S=1) (no cond) */
/* weight = 6931827 */
extern void slv6_G_ADD_M1_LSLImm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.3--A5.1.5--NC
 * ADD -- Data processing operands - Logical shift left by immediate (S=0) (no cond) */
/* weight = 6931827 */
extern void slv6_G_ADD_M1_LSLImm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.24--A5.2.2--NC
 * LDRB -- Load and Store Word or Unsigned Byte - Immediate offset (no cond) */
/* weight = 6906640 */
extern void slv6_G_LDRB_M2_ImmOff_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.42--A5.1.4--NC
 * ORR -- Data processing operands - Register (S=1) (no cond) */
/* weight = 6806204 */
extern void slv6_G_ORR_M1_Reg_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.42--A5.1.4--NC
 * ORR -- Data processing operands - Register (S=0) (no cond) */
/* weight = 6806204 */
extern void slv6_G_ORR_M1_Reg_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.11--NC
 * MOV -- Data processing operands - Rotate right by immediate (S=1) (no cond) */
/* weight = 5346301 */
extern void slv6_G_MOV_M1_RRImm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.11--NC
 * MOV -- Data processing operands - Rotate right by immediate (S=0) (no cond) */
/* weight = 5346301 */
extern void slv6_G_MOV_M1_RRImm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.23--A5.2.8--NC
 * LDR -- Load and Store Word or Unsigned Byte - Immediate post indexed (no cond) */
/* weight = 4918495 */
extern void slv6_G_LDR_M2_Imm_postInd_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.18--A5.1.11--NC
 * EOR -- Data processing operands - Rotate right by immediate (S=1) (no cond) */
/* weight = 4358144 */
extern void slv6_G_EOR_M1_RRImm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.18--A5.1.11--NC
 * EOR -- Data processing operands - Rotate right by immediate (S=0) (no cond) */
/* weight = 4358144 */
extern void slv6_G_EOR_M1_RRImm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.4--A5.1.4--NC
 * AND -- Data processing operands - Register (S=1) (no cond) */
/* weight = 4238848 */
extern void slv6_G_AND_M1_Reg_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.4--A5.1.4--NC
 * AND -- Data processing operands - Register (S=0) (no cond) */
/* weight = 4238848 */
extern void slv6_G_AND_M1_Reg_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.99--A5.2.5--NC
 * STR -- Load and Store Word or Unsigned Byte - Immediate pre indexed (no cond) */
/* weight = 3993434 */
extern void slv6_G_STR_M2_Imm_preInd_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.100--A5.2.2--NC
 * STRB -- Load and Store Word or Unsigned Byte - Immediate offset (no cond) */
/* weight = 3167635 */
extern void slv6_G_STRB_M2_ImmOff_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.42--A5.1.5--NC
 * ORR -- Data processing operands - Logical shift left by immediate (S=1) (no cond) */
/* weight = 3106144 */
extern void slv6_G_ORR_M1_LSLImm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.42--A5.1.5--NC
 * ORR -- Data processing operands - Logical shift left by immediate (S=0) (no cond) */
/* weight = 3106144 */
extern void slv6_G_ORR_M1_LSLImm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.2--A5.1.4--NC
 * ADC -- Data processing operands - Register (S=1) (no cond) */
/* weight = 2554368 */
extern void slv6_G_ADC_M1_Reg_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.2--A5.1.4--NC
 * ADC -- Data processing operands - Register (S=0) (no cond) */
/* weight = 2554368 */
extern void slv6_G_ADC_M1_Reg_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.24--A5.2.3--NC
 * LDRB -- Load and Store Word or Unsigned Byte - Register offset (U=1) (no cond) */
/* weight = 2327120 */
extern void slv6_G_LDRB_M2_RegOff_U1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.24--A5.2.3--NC
 * LDRB -- Load and Store Word or Unsigned Byte - Register offset (U=0) (no cond) */
/* weight = 2327120 */
extern void slv6_G_LDRB_M2_RegOff_U0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.60--A5.1.4--NC
 * RSB -- Data processing operands - Register (S=1) (no cond) */
/* weight = 2083886 */
extern void slv6_G_RSB_M1_Reg_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.60--A5.1.4--NC
 * RSB -- Data processing operands - Register (S=0) (no cond) */
/* weight = 2083886 */
extern void slv6_G_RSB_M1_Reg_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.6--A5.1.3--NC
 * BIC -- Data processing operands - Immediate (S=1) (no cond) */
/* weight = 1734061 */
extern void slv6_G_BIC_M1_Imm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.6--A5.1.3--NC
 * BIC -- Data processing operands - Immediate (S=0) (no cond) */
/* weight = 1734061 */
extern void slv6_G_BIC_M1_Imm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.41--A5.1.3--NC
 * MVN -- Data processing operands - Immediate (S=1) (no cond) */
/* weight = 1393258 */
extern void slv6_G_MVN_M1_Imm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.41--A5.1.3--NC
 * MVN -- Data processing operands - Immediate (S=0) (no cond) */
/* weight = 1393258 */
extern void slv6_G_MVN_M1_Imm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.42--A5.1.7--NC
 * ORR -- Data processing operands - Logical shift right by immediate (S=1) (no cond) */
/* weight = 1372157 */
extern void slv6_G_ORR_M1_LSRImm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.42--A5.1.7--NC
 * ORR -- Data processing operands - Logical shift right by immediate (S=0) (no cond) */
/* weight = 1372157 */
extern void slv6_G_ORR_M1_LSRImm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.18--A5.1.7--NC
 * EOR -- Data processing operands - Logical shift right by immediate (S=1) (no cond) */
/* weight = 1312720 */
extern void slv6_G_EOR_M1_LSRImm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.18--A5.1.7--NC
 * EOR -- Data processing operands - Logical shift right by immediate (S=0) (no cond) */
/* weight = 1312720 */
extern void slv6_G_EOR_M1_LSRImm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.23--A5.2.3--NC
 * LDR -- Load and Store Word or Unsigned Byte - Register offset (U=1) (no cond) */
/* weight = 1269491 */
extern void slv6_G_LDR_M2_RegOff_U1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.23--A5.2.3--NC
 * LDR -- Load and Store Word or Unsigned Byte - Register offset (U=0) (no cond) */
/* weight = 1269491 */
extern void slv6_G_LDR_M2_RegOff_U0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.8--NC
 * MOV -- Data processing operands - Logical shift right by register (S=1) (no cond) */
/* weight = 1056272 */
extern void slv6_G_MOV_M1_LSRReg_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.8--NC
 * MOV -- Data processing operands - Logical shift right by register (S=0) (no cond) */
/* weight = 1056272 */
extern void slv6_G_MOV_M1_LSRReg_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.100--A5.2.3--NC
 * STRB -- Load and Store Word or Unsigned Byte - Register offset (U=1) (no cond) */
/* weight = 968189 */
extern void slv6_G_STRB_M2_RegOff_U1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.100--A5.2.3--NC
 * STRB -- Load and Store Word or Unsigned Byte - Register offset (U=0) (no cond) */
/* weight = 968189 */
extern void slv6_G_STRB_M2_RegOff_U0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.99--A5.2.4--NC
 * STR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) (no cond) */
/* weight = 838541 */
extern void slv6_G_STR_M2_ScRegOff_U1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.99--A5.2.4--NC
 * STR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) (no cond) */
/* weight = 838541 */
extern void slv6_G_STR_M2_ScRegOff_U0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.14--A5.1.4--NC
 * CMN -- Data processing operands - Register (no cond) */
/* weight = 612640 */
extern void slv6_G_CMN_M1_Reg_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.99--A5.2.9--NC
 * STR -- Load and Store Word or Unsigned Byte - Register post indexed (U=1) (no cond) */
/* weight = 612640 */
extern void slv6_G_STR_M2_Reg_postInd_U1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.99--A5.2.9--NC
 * STR -- Load and Store Word or Unsigned Byte - Register post indexed (U=0) (no cond) */
/* weight = 612640 */
extern void slv6_G_STR_M2_Reg_postInd_U0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.99--A5.2.3--NC
 * STR -- Load and Store Word or Unsigned Byte - Register offset (U=1) (no cond) */
/* weight = 542572 */
extern void slv6_G_STR_M2_RegOff_U1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.99--A5.2.3--NC
 * STR -- Load and Store Word or Unsigned Byte - Register offset (U=0) (no cond) */
/* weight = 542572 */
extern void slv6_G_STR_M2_RegOff_U0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.18--A5.1.5--NC
 * EOR -- Data processing operands - Logical shift left by immediate (S=1) (no cond) */
/* weight = 462398 */
extern void slv6_G_EOR_M1_LSLImm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.18--A5.1.5--NC
 * EOR -- Data processing operands - Logical shift left by immediate (S=0) (no cond) */
/* weight = 462398 */
extern void slv6_G_EOR_M1_LSLImm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.60--A5.1.3--NC
 * RSB -- Data processing operands - Immediate (S=1) (no cond) */
/* weight = 377779 */
extern void slv6_G_RSB_M1_Imm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.60--A5.1.3--NC
 * RSB -- Data processing operands - Immediate (S=0) (no cond) */
/* weight = 377779 */
extern void slv6_G_RSB_M1_Imm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.9--NC
 * MOV -- Data processing operands - Arithmetic shift right by immediate (S=1) (no cond) */
/* weight = 340365 */
extern void slv6_G_MOV_M1_ASRImm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.9--NC
 * MOV -- Data processing operands - Arithmetic shift right by immediate (S=0) (no cond) */
/* weight = 340365 */
extern void slv6_G_MOV_M1_ASRImm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.3--A5.1.11--NC
 * ADD -- Data processing operands - Rotate right by immediate (S=1) (no cond) */
/* weight = 266240 */
extern void slv6_G_ADD_M1_RRImm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.3--A5.1.11--NC
 * ADD -- Data processing operands - Rotate right by immediate (S=0) (no cond) */
/* weight = 266240 */
extern void slv6_G_ADD_M1_RRImm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.60--A5.1.5--NC
 * RSB -- Data processing operands - Logical shift left by immediate (S=1) (no cond) */
/* weight = 264959 */
extern void slv6_G_RSB_M1_LSLImm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.60--A5.1.5--NC
 * RSB -- Data processing operands - Logical shift left by immediate (S=0) (no cond) */
/* weight = 264959 */
extern void slv6_G_RSB_M1_LSLImm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.100--A5.2.8--NC
 * STRB -- Load and Store Word or Unsigned Byte - Immediate post indexed (no cond) */
/* weight = 262176 */
extern void slv6_G_STRB_M2_Imm_postInd_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.97--A5.4.2--NC
 * STM (1) -- Load and Store Multiple - Increment after (W=1) (no cond) */
/* weight = 252529 */
extern void slv6_G_STM1_M4_IA_W1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.97--A5.4.2--NC
 * STM (1) -- Load and Store Multiple - Increment after (W=0) (no cond) */
/* weight = 252529 */
extern void slv6_G_STM1_M4_IA_W0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.117--A5.1.3--NC
 * TST -- Data processing operands - Immediate (no cond) */
/* weight = 236793 */
extern void slv6_G_TST_M1_Imm_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.97--A5.4.5--NC
 * STM (1) -- Load and Store Multiple - Decrement before (W=1) (no cond) */
/* weight = 236571 */
extern void slv6_G_STM1_M4_DB_W1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.97--A5.4.5--NC
 * STM (1) -- Load and Store Multiple - Decrement before (W=0) (no cond) */
/* weight = 236571 */
extern void slv6_G_STM1_M4_DB_W0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.41--A5.1.4--NC
 * MVN -- Data processing operands - Register (S=1) (no cond) */
/* weight = 99840 */
extern void slv6_G_MVN_M1_Reg_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.41--A5.1.4--NC
 * MVN -- Data processing operands - Register (S=0) (no cond) */
/* weight = 99840 */
extern void slv6_G_MVN_M1_Reg_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.97--A5.4.3--NC
 * STM (1) -- Load and Store Multiple - Increment before (W=1) (no cond) */
/* weight = 98338 */
extern void slv6_G_STM1_M4_IB_W1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.97--A5.4.3--NC
 * STM (1) -- Load and Store Multiple - Increment before (W=0) (no cond) */
/* weight = 98338 */
extern void slv6_G_STM1_M4_IB_W0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.3--A5.1.7--NC
 * ADD -- Data processing operands - Logical shift right by immediate (S=1) (no cond) */
/* weight = 98336 */
extern void slv6_G_ADD_M1_LSRImm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.3--A5.1.7--NC
 * ADD -- Data processing operands - Logical shift right by immediate (S=0) (no cond) */
/* weight = 98336 */
extern void slv6_G_ADD_M1_LSRImm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.99--A5.2.8--NC
 * STR -- Load and Store Word or Unsigned Byte - Immediate post indexed (no cond) */
/* weight = 96053 */
extern void slv6_G_STR_M2_Imm_postInd_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.24--A5.2.4--NC
 * LDRB -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) (no cond) */
/* weight = 79552 */
extern void slv6_G_LDRB_M2_ScRegOff_U1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.24--A5.2.4--NC
 * LDRB -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) (no cond) */
/* weight = 79552 */
extern void slv6_G_LDRB_M2_ScRegOff_U0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.106--A5.1.5--NC
 * SUB -- Data processing operands - Logical shift left by immediate (S=1) (no cond) */
/* weight = 63184 */
extern void slv6_G_SUB_M1_LSLImm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.106--A5.1.5--NC
 * SUB -- Data processing operands - Logical shift left by immediate (S=0) (no cond) */
/* weight = 63184 */
extern void slv6_G_SUB_M1_LSLImm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.20--A5.4.3--NC
 * LDM (1) -- Load and Store Multiple - Increment before (W=1) (no cond) */
/* weight = 37088 */
extern void slv6_G_LDM1_M4_IB_W1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.20--A5.4.3--NC
 * LDM (1) -- Load and Store Multiple - Increment before (W=0) (no cond) */
/* weight = 37088 */
extern void slv6_G_LDM1_M4_IB_W0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.28--A5.3.2--NC
 * LDRH -- Miscellaneous Loads and Stores - Immediate offset (U=1) (no cond) */
/* weight = 35072 */
extern void slv6_G_LDRH_M3_ImmOff_U1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.28--A5.3.2--NC
 * LDRH -- Miscellaneous Loads and Stores - Immediate offset (U=0) (no cond) */
/* weight = 35072 */
extern void slv6_G_LDRH_M3_ImmOff_U0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.23--A5.2.5--NC
 * LDR -- Load and Store Word or Unsigned Byte - Immediate pre indexed (no cond) */
/* weight = 11634 */
extern void slv6_G_LDR_M2_Imm_preInd_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.87--NC
 * SMULL (S=1) (no cond) */
/* weight = 2136 */
extern void slv6_G_SMULL_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.87--NC
 * SMULL (S=0) (no cond) */
/* weight = 2136 */
extern void slv6_G_SMULL_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.60--A5.1.9--NC
 * RSB -- Data processing operands - Arithmetic shift right by immediate (S=1) (no cond) */
/* weight = 1020 */
extern void slv6_G_RSB_M1_ASRImm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.60--A5.1.9--NC
 * RSB -- Data processing operands - Arithmetic shift right by immediate (S=0) (no cond) */
/* weight = 1020 */
extern void slv6_G_RSB_M1_ASRImm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.117--A5.1.4--NC
 * TST -- Data processing operands - Register (no cond) */
/* weight = 512 */
extern void slv6_G_TST_M1_Reg_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.18--A5.1.3--NC
 * EOR -- Data processing operands - Immediate (S=1) (no cond) */
/* weight = 510 */
extern void slv6_G_EOR_M1_Imm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.18--A5.1.3--NC
 * EOR -- Data processing operands - Immediate (S=0) (no cond) */
/* weight = 510 */
extern void slv6_G_EOR_M1_Imm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.42--A5.1.9--NC
 * ORR -- Data processing operands - Arithmetic shift right by immediate (S=1) (no cond) */
/* weight = 255 */
extern void slv6_G_ORR_M1_ASRImm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.42--A5.1.9--NC
 * ORR -- Data processing operands - Arithmetic shift right by immediate (S=0) (no cond) */
/* weight = 255 */
extern void slv6_G_ORR_M1_ASRImm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.42--A5.1.3--NC
 * ORR -- Data processing operands - Immediate (S=1) (no cond) */
/* weight = 104 */
extern void slv6_G_ORR_M1_Imm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.42--A5.1.3--NC
 * ORR -- Data processing operands - Immediate (S=0) (no cond) */
/* weight = 104 */
extern void slv6_G_ORR_M1_Imm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.106--A5.1.9--NC
 * SUB -- Data processing operands - Arithmetic shift right by immediate (S=1) (no cond) */
/* weight = 64 */
extern void slv6_G_SUB_M1_ASRImm_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.106--A5.1.9--NC
 * SUB -- Data processing operands - Arithmetic shift right by immediate (S=0) (no cond) */
/* weight = 64 */
extern void slv6_G_SUB_M1_ASRImm_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.6--NC
 * MOV -- Data processing operands - Logical shift left by register (S=1) (no cond) */
/* weight = 20 */
extern void slv6_G_MOV_M1_LSLReg_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.35--A5.1.6--NC
 * MOV -- Data processing operands - Logical shift left by register (S=0) (no cond) */
/* weight = 20 */
extern void slv6_G_MOV_M1_LSLReg_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.40--NC
 * MUL (S=1) (no cond) */
/* weight = 13 */
extern void slv6_G_MUL_S1_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.40--NC
 * MUL (S=0) (no cond) */
/* weight = 13 */
extern void slv6_G_MUL_S0_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A4.1.14--A5.1.3--NC
 * CMN -- Data processing operands - Immediate (no cond) */
/* weight = 12 */
extern void slv6_G_CMN_M1_Imm_NC(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.28--NI
 * LDR (1) (no immed) */
/* weight = 204454071 */
extern void slv6_G_Tb_LDR1_NI(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

/* A7.1.38--NI
 * LSL (1) (no immed) */
/* weight = 70354701 */
extern void slv6_G_Tb_LSL1_NI(struct SLv6_Processor*, struct SLv6_Instruction*) SLV6_HOT;

END_SIMSOC_NAMESPACE

#endif /* SLV6_ISS_grouped_H */
