#include "slv6_iss_c_prelude.h"

/* A7.1.28
 * LDR (1) */
static bool try_store_Tb_LDR1(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint32_t immed_5 = get_bits(bincode,10,6);
  uint8_t n = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  if (immed_5==0)
    instr->args.g0.id = SLV6_Tb_LDR1_NI_ID;
  else
    instr->args.g0.id = SLV6_Tb_LDR1_ID;
  instr->args.g62.d = d;
  instr->args.g62.n = n;
  instr->args.g62.immed_5 = immed_5;
  return true;
}

/* A7.1.25
 * CPY */
static bool try_store_Tb_CPY(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t H1 = get_bit(bincode,7);
  uint8_t H2 = get_bit(bincode,6);
  uint8_t m = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  d |= H1 << 3;
  m |= H2 << 3;
  instr->args.g0.id = SLV6_Tb_CPY_ID;
  instr->args.g63.d = d;
  instr->args.g63.m = m;
  return true;
}

/* A7.1.58
 * STR (1) */
static bool try_store_Tb_STR1(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint32_t immed_5 = get_bits(bincode,10,6);
  uint8_t n = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_STR1_ID;
  instr->args.g62.d = d;
  instr->args.g62.n = n;
  instr->args.g62.immed_5 = immed_5;
  return true;
}

/* A7.1.13
 * B (1) */
static bool try_store_Tb_B1(struct SLv6_Instruction *instr, uint16_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,11,8);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint32_t signed_immed_8 = get_bits(bincode,7,0);
  if (!(not_AL_cond(cond))) return false;
  const uint32_t simmed_8_ext = SignExtend8(signed_immed_8) << 1;
  instr->args.g0.id = SLV6_Tb_B1_ID;
  instr->args.g64.cond = cond;
  instr->args.g64.simmed_8_ext = simmed_8_ext;
  return true;
}

/* A7.1.38
 * LSL (1) */
static bool try_store_Tb_LSL1(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint32_t immed_5 = get_bits(bincode,10,6);
  uint8_t m = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  if (immed_5==0)
    instr->args.g0.id = SLV6_Tb_LSL1_NI_ID;
  else
    instr->args.g0.id = SLV6_Tb_LSL1_ID;
  instr->args.g65.d = d;
  instr->args.g65.m = m;
  instr->args.g65.immed_5 = immed_5;
  return true;
}

/* A7.1.5
 * ADD (3) */
static bool try_store_Tb_ADD3(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,8,6);
  uint8_t n = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_ADD3_ID;
  instr->args.g66.d = d;
  instr->args.g66.m = m;
  instr->args.g66.n = n;
  return true;
}

/* A7.1.42
 * MOV (1) */
static bool try_store_Tb_MOV1(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t d = get_bits(bincode,10,8);
  uint8_t immed_8 = get_bits(bincode,7,0);
  instr->args.g0.id = SLV6_Tb_MOV1_ID;
  instr->args.g67.d = d;
  instr->args.g67.immed_8 = immed_8;
  return true;
}

/* A7.1.22
 * CMP (2) */
static bool try_store_Tb_CMP2(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,5,3);
  uint8_t n = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_CMP2_ID;
  instr->args.g68.m = m;
  instr->args.g68.n = n;
  return true;
}

/* A7.1.30
 * LDR (3) */
static bool try_store_Tb_LDR3(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t d = get_bits(bincode,10,8);
  uint8_t immed_8 = get_bits(bincode,7,0);
  instr->args.g0.id = SLV6_Tb_LDR3_ID;
  instr->args.g67.d = d;
  instr->args.g67.immed_8 = immed_8;
  return true;
}

/* A7.1.26
 * EOR */
static bool try_store_Tb_EOR(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_EOR_ID;
  instr->args.g63.d = d;
  instr->args.g63.m = m;
  return true;
}

/* A7.1.66
 * SUB (2) */
static bool try_store_Tb_SUB2(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t d = get_bits(bincode,10,8);
  uint8_t immed_8 = get_bits(bincode,7,0);
  instr->args.g0.id = SLV6_Tb_SUB2_ID;
  instr->args.g67.d = d;
  instr->args.g67.immed_8 = immed_8;
  return true;
}

/* A7.1.43
 * MOV (2) */
static bool try_store_Tb_MOV2(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t n = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_MOV2_ID;
  instr->args.g69.d = d;
  instr->args.g69.n = n;
  return true;
}

/* A7.1.4
 * ADD (2) */
static bool try_store_Tb_ADD2(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t d = get_bits(bincode,10,8);
  uint8_t immed_8 = get_bits(bincode,7,0);
  instr->args.g0.id = SLV6_Tb_ADD2_ID;
  instr->args.g67.d = d;
  instr->args.g67.immed_8 = immed_8;
  return true;
}

/* A7.1.31
 * LDR (4) */
static bool try_store_Tb_LDR4(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t d = get_bits(bincode,10,8);
  uint8_t immed_8 = get_bits(bincode,7,0);
  instr->args.g0.id = SLV6_Tb_LDR4_ID;
  instr->args.g67.d = d;
  instr->args.g67.immed_8 = immed_8;
  return true;
}

/* A7.1.10
 * AND */
static bool try_store_Tb_AND(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_AND_ID;
  instr->args.g63.d = d;
  instr->args.g63.m = m;
  return true;
}

/* A7.1.40
 * LSR (1) */
static bool try_store_Tb_LSR1(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint32_t immed_5 = get_bits(bincode,10,6);
  uint8_t m = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_LSR1_ID;
  instr->args.g65.d = d;
  instr->args.g65.m = m;
  instr->args.g65.immed_5 = immed_5;
  return true;
}

/* A7.1.29
 * LDR (2) */
static bool try_store_Tb_LDR2(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,8,6);
  uint8_t n = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_LDR2_ID;
  instr->args.g66.d = d;
  instr->args.g66.m = m;
  instr->args.g66.n = n;
  return true;
}

/* A7.1.6
 * ADD (4) */
static bool try_store_Tb_ADD4(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t H1 = get_bit(bincode,7);
  uint8_t H2 = get_bit(bincode,6);
  uint8_t m = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  d |= H1 << 3;
  m |= H2 << 3;
  if (!(((H1 != 0) || (H2 != 0)))) return false;
  instr->args.g0.id = SLV6_Tb_ADD4_ID;
  instr->args.g63.d = d;
  instr->args.g63.m = m;
  return true;
}

/* A7.1.21
 * CMP (1) */
static bool try_store_Tb_CMP1(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t n = get_bits(bincode,10,8);
  uint8_t immed_8 = get_bits(bincode,7,0);
  instr->args.g0.id = SLV6_Tb_CMP1_ID;
  instr->args.g70.immed_8 = immed_8;
  instr->args.g70.n = n;
  return true;
}

/* A7.1.48
 * ORR */
static bool try_store_Tb_ORR(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_ORR_ID;
  instr->args.g63.d = d;
  instr->args.g63.m = m;
  return true;
}

/* A7.1.60
 * STR (3) */
static bool try_store_Tb_STR3(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t d = get_bits(bincode,10,8);
  uint8_t immed_8 = get_bits(bincode,7,0);
  instr->args.g0.id = SLV6_Tb_STR3_ID;
  instr->args.g67.d = d;
  instr->args.g67.immed_8 = immed_8;
  return true;
}

/* A7.1.54
 * ROR */
static bool try_store_Tb_ROR(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t s = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_ROR_ID;
  instr->args.g71.d = d;
  instr->args.g71.s = s;
  return true;
}

/* A7.1.17
 * BL, BLX (1) */
static bool try_store_Tb_BL(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint32_t H = get_bits(bincode,12,11);
  uint32_t offset_11 = get_bits(bincode,10,0);
  if (!(((H != 0) && ((H != 1) || ((offset_11 & 1) == 0))))) return false;
  instr->args.g0.id = SLV6_Tb_BL_ID;
  instr->args.g72.H = H;
  instr->args.g72.offset_11 = offset_11;
  return true;
}

/* A7.1.14
 * B (2) */
static bool try_store_Tb_B2(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint32_t signed_immed_11 = get_bits(bincode,10,0);
  const uint32_t simmed_11_ext = SignExtend11(signed_immed_11) << 1;
  instr->args.g0.id = SLV6_Tb_B2_ID;
  instr->args.g73.simmed_11_ext = simmed_11_ext;
  return true;
}

/* A7.1.47
 * NEG */
static bool try_store_Tb_NEG(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_NEG_ID;
  instr->args.g63.d = d;
  instr->args.g63.m = m;
  return true;
}

/* A7.1.32
 * LDRB (1) */
static bool try_store_Tb_LDRB1(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint32_t immed_5 = get_bits(bincode,10,6);
  uint8_t n = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_LDRB1_ID;
  instr->args.g62.d = d;
  instr->args.g62.n = n;
  instr->args.g62.immed_5 = immed_5;
  return true;
}

/* A7.1.50
 * PUSH */
static bool try_store_Tb_PUSH(struct SLv6_Instruction *instr, uint16_t bincode) {
  bool R = get_bit(bincode,8);
  uint32_t register_list = get_bits(bincode,7,0);
  if (!(((R != 0) || (register_list != 0)))) return false;
  instr->args.g0.id = SLV6_Tb_PUSH_ID;
  instr->args.g74.R = R;
  instr->args.g74.register_list = register_list;
  return true;
}

/* A7.1.49
 * POP */
static bool try_store_Tb_POP(struct SLv6_Instruction *instr, uint16_t bincode) {
  bool R = get_bit(bincode,8);
  uint32_t register_list = get_bits(bincode,7,0);
  if (!(((R != 0) || (register_list != 0)))) return false;
  instr->args.g0.id = SLV6_Tb_POP_ID;
  instr->args.g74.R = R;
  instr->args.g74.register_list = register_list;
  return true;
}

/* A7.1.23
 * CMP (3) */
static bool try_store_Tb_CMP3(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t H1 = get_bit(bincode,7);
  uint8_t H2 = get_bit(bincode,6);
  uint8_t m = get_bits(bincode,5,3);
  uint8_t n = get_bits(bincode,2,0);
  n |= H1 << 3;
  m |= H2 << 3;
  if (!(((n != 15) && ((H1 != 0) || (H2 != 0))))) return false;
  instr->args.g0.id = SLV6_Tb_CMP3_ID;
  instr->args.g68.m = m;
  instr->args.g68.n = n;
  return true;
}

/* A7.1.68
 * SUB (4) */
static bool try_store_Tb_SUB4(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint32_t immed_7 = get_bits(bincode,6,0);
  instr->args.g0.id = SLV6_Tb_SUB4_ID;
  instr->args.g75.immed_7 = immed_7;
  return true;
}

/* A7.1.9
 * ADD (7) */
static bool try_store_Tb_ADD7(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint32_t immed_7 = get_bits(bincode,6,0);
  instr->args.g0.id = SLV6_Tb_ADD7_ID;
  instr->args.g75.immed_7 = immed_7;
  return true;
}

/* A7.1.8
 * ADD (6) */
static bool try_store_Tb_ADD6(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t d = get_bits(bincode,10,8);
  uint8_t immed_8 = get_bits(bincode,7,0);
  instr->args.g0.id = SLV6_Tb_ADD6_ID;
  instr->args.g67.d = d;
  instr->args.g67.immed_8 = immed_8;
  return true;
}

/* A7.1.19
 * BX */
static bool try_store_Tb_BX(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t H2 = get_bit(bincode,6);
  uint8_t m = get_bits(bincode,5,3);
  m |= H2 << 3;
  instr->args.g0.id = SLV6_Tb_BX_ID;
  instr->args.g76.m = m;
  return true;
}

/* A7.1.61
 * STRB (1) */
static bool try_store_Tb_STRB1(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint32_t immed_5 = get_bits(bincode,10,6);
  uint8_t n = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_STRB1_ID;
  instr->args.g62.d = d;
  instr->args.g62.n = n;
  instr->args.g62.immed_5 = immed_5;
  return true;
}

/* A7.1.33
 * LDRB (2) */
static bool try_store_Tb_LDRB2(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,8,6);
  uint8_t n = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_LDRB2_ID;
  instr->args.g66.d = d;
  instr->args.g66.m = m;
  instr->args.g66.n = n;
  return true;
}

/* A7.1.2
 * ADC */
static bool try_store_Tb_ADC(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_ADC_ID;
  instr->args.g63.d = d;
  instr->args.g63.m = m;
  return true;
}

/* A7.1.67
 * SUB (3) */
static bool try_store_Tb_SUB3(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,8,6);
  uint8_t n = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_SUB3_ID;
  instr->args.g66.d = d;
  instr->args.g66.m = m;
  instr->args.g66.n = n;
  return true;
}

/* A7.1.65
 * SUB (1) */
static bool try_store_Tb_SUB1(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint32_t immed_3 = get_bits(bincode,8,6);
  uint8_t n = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_SUB1_ID;
  instr->args.g77.d = d;
  instr->args.g77.n = n;
  instr->args.g77.immed_3 = immed_3;
  return true;
}

/* A7.1.41
 * LSR (2) */
static bool try_store_Tb_LSR2(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t s = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_LSR2_ID;
  instr->args.g71.d = d;
  instr->args.g71.s = s;
  return true;
}

/* A7.1.59
 * STR (2) */
static bool try_store_Tb_STR2(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,8,6);
  uint8_t n = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_STR2_ID;
  instr->args.g66.d = d;
  instr->args.g66.m = m;
  instr->args.g66.n = n;
  return true;
}

/* A7.1.62
 * STRB (2) */
static bool try_store_Tb_STRB2(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,8,6);
  uint8_t n = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_STRB2_ID;
  instr->args.g66.d = d;
  instr->args.g66.m = m;
  instr->args.g66.n = n;
  return true;
}

/* A7.1.27
 * LDMIA */
static bool try_store_Tb_LDMIA(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t n = get_bits(bincode,10,8);
  uint32_t register_list = get_bits(bincode,7,0);
  if (!((register_list != 0))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  instr->args.g0.id = SLV6_Tb_LDMIA_ID;
  instr->args.g78.n = n;
  instr->args.g78.nb_reg_x4 = nb_reg_x4;
  instr->args.g78.register_list = register_list;
  return true;
}

/* A7.1.57
 * STMIA */
static bool try_store_Tb_STMIA(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t n = get_bits(bincode,10,8);
  uint32_t register_list = get_bits(bincode,7,0);
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  instr->args.g0.id = SLV6_Tb_STMIA_ID;
  instr->args.g78.n = n;
  instr->args.g78.nb_reg_x4 = nb_reg_x4;
  instr->args.g78.register_list = register_list;
  return true;
}

/* A7.1.3
 * ADD (1) */
static bool try_store_Tb_ADD1(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint32_t immed_3 = get_bits(bincode,8,6);
  uint8_t n = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  if (!((immed_3 != 0))) return false;
  instr->args.g0.id = SLV6_Tb_ADD1_ID;
  instr->args.g77.d = d;
  instr->args.g77.n = n;
  instr->args.g77.immed_3 = immed_3;
  return true;
}

/* A7.1.45
 * MUL */
static bool try_store_Tb_MUL(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_MUL_ID;
  instr->args.g63.d = d;
  instr->args.g63.m = m;
  return true;
}

/* A7.1.11
 * ASR (1) */
static bool try_store_Tb_ASR1(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint32_t immed_5 = get_bits(bincode,10,6);
  uint8_t m = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_ASR1_ID;
  instr->args.g65.d = d;
  instr->args.g65.m = m;
  instr->args.g65.immed_5 = immed_5;
  return true;
}

/* A7.1.46
 * MVN */
static bool try_store_Tb_MVN(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_MVN_ID;
  instr->args.g63.d = d;
  instr->args.g63.m = m;
  return true;
}

/* A7.1.34
 * LDRH (1) */
static bool try_store_Tb_LDRH1(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint32_t immed_5 = get_bits(bincode,10,6);
  uint8_t n = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_LDRH1_ID;
  instr->args.g62.d = d;
  instr->args.g62.n = n;
  instr->args.g62.immed_5 = immed_5;
  return true;
}

/* A7.1.72
 * TST */
static bool try_store_Tb_TST(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,5,3);
  uint8_t n = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_TST_ID;
  instr->args.g68.m = m;
  instr->args.g68.n = n;
  return true;
}

/* A7.1.15
 * BIC */
static bool try_store_Tb_BIC(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_BIC_ID;
  instr->args.g63.d = d;
  instr->args.g63.m = m;
  return true;
}

/* A7.1.39
 * LSL (2) */
static bool try_store_Tb_LSL2(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t s = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_LSL2_ID;
  instr->args.g71.d = d;
  instr->args.g71.s = s;
  return true;
}

/* A7.1.7
 * ADD (5) */
static bool try_store_Tb_ADD5(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t d = get_bits(bincode,10,8);
  uint8_t immed_8 = get_bits(bincode,7,0);
  instr->args.g0.id = SLV6_Tb_ADD5_ID;
  instr->args.g67.d = d;
  instr->args.g67.immed_8 = immed_8;
  return true;
}

/* A7.1.12
 * ASR (2) */
static bool try_store_Tb_ASR2(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t s = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_ASR2_ID;
  instr->args.g71.d = d;
  instr->args.g71.s = s;
  return true;
}

/* A7.1.16
 * BKPT */
static bool try_store_Tb_BKPT(struct SLv6_Instruction *instr, uint16_t bincode) {
  instr->args.g0.id = SLV6_Tb_BKPT_ID;
  return true;
}

/* A7.1.18
 * BLX (2) */
static bool try_store_Tb_BLX2(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t H2 = get_bit(bincode,6);
  uint8_t m = get_bits(bincode,5,3);
  m |= H2 << 3;
  if (!((m != 15))) return false;
  instr->args.g0.id = SLV6_Tb_BLX2_ID;
  instr->args.g76.m = m;
  return true;
}

/* A7.1.20
 * CMN */
static bool try_store_Tb_CMN(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,5,3);
  uint8_t n = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_CMN_ID;
  instr->args.g68.m = m;
  instr->args.g68.n = n;
  return true;
}

/* A7.1.24
 * CPS */
static bool try_store_Tb_CPS(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t imod = get_bit(bincode,4);
  bool A = get_bit(bincode,2);
  bool I = get_bit(bincode,1);
  bool F = get_bit(bincode,0);
  instr->args.g0.id = SLV6_Tb_CPS_ID;
  instr->args.g79.A = A;
  instr->args.g79.F = F;
  instr->args.g79.I = I;
  instr->args.g79.imod = imod;
  return true;
}

/* A7.1.35
 * LDRH (2) */
static bool try_store_Tb_LDRH2(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,8,6);
  uint8_t n = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_LDRH2_ID;
  instr->args.g66.d = d;
  instr->args.g66.m = m;
  instr->args.g66.n = n;
  return true;
}

/* A7.1.36
 * LDRSB */
static bool try_store_Tb_LDRSB(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,8,6);
  uint8_t n = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_LDRSB_ID;
  instr->args.g66.d = d;
  instr->args.g66.m = m;
  instr->args.g66.n = n;
  return true;
}

/* A7.1.37
 * LDRSH */
static bool try_store_Tb_LDRSH(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,8,6);
  uint8_t n = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_LDRSH_ID;
  instr->args.g66.d = d;
  instr->args.g66.m = m;
  instr->args.g66.n = n;
  return true;
}

/* A7.1.51
 * REV */
static bool try_store_Tb_REV(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t n = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_REV_ID;
  instr->args.g69.d = d;
  instr->args.g69.n = n;
  return true;
}

/* A7.1.52
 * REV16 */
static bool try_store_Tb_REV16(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t n = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_REV16_ID;
  instr->args.g69.d = d;
  instr->args.g69.n = n;
  return true;
}

/* A7.1.53
 * REVSH */
static bool try_store_Tb_REVSH(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t n = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_REVSH_ID;
  instr->args.g69.d = d;
  instr->args.g69.n = n;
  return true;
}

/* A7.1.55
 * SBC */
static bool try_store_Tb_SBC(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_SBC_ID;
  instr->args.g63.d = d;
  instr->args.g63.m = m;
  return true;
}

/* A7.1.56
 * SETEND */
static bool try_store_Tb_SETEND(struct SLv6_Instruction *instr, uint16_t bincode) {
  bool E = get_bit(bincode,3);
  instr->args.g0.id = SLV6_Tb_SETEND_ID;
  instr->args.g43.E = E;
  return true;
}

/* A7.1.63
 * STRH (1) */
static bool try_store_Tb_STRH1(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint32_t immed_5 = get_bits(bincode,10,6);
  uint8_t n = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_STRH1_ID;
  instr->args.g62.d = d;
  instr->args.g62.n = n;
  instr->args.g62.immed_5 = immed_5;
  return true;
}

/* A7.1.64
 * STRH (2) */
static bool try_store_Tb_STRH2(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,8,6);
  uint8_t n = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_STRH2_ID;
  instr->args.g66.d = d;
  instr->args.g66.m = m;
  instr->args.g66.n = n;
  return true;
}

/* A7.1.69
 * SWI */
static bool try_store_Tb_SWI(struct SLv6_Instruction *instr, uint16_t bincode) {
  instr->args.g0.id = SLV6_Tb_SWI_ID;
  return true;
}

/* A7.1.70
 * SXTB */
static bool try_store_Tb_SXTB(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_SXTB_ID;
  instr->args.g63.d = d;
  instr->args.g63.m = m;
  return true;
}

/* A7.1.71
 * SXTH */
static bool try_store_Tb_SXTH(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_SXTH_ID;
  instr->args.g63.d = d;
  instr->args.g63.m = m;
  return true;
}

/* A7.1.73
 * UXTB */
static bool try_store_Tb_UXTB(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_UXTB_ID;
  instr->args.g63.d = d;
  instr->args.g63.m = m;
  return true;
}

/* A7.1.74
 * UXTH */
static bool try_store_Tb_UXTH(struct SLv6_Instruction *instr, uint16_t bincode) {
  uint8_t m = get_bits(bincode,5,3);
  uint8_t d = get_bits(bincode,2,0);
  instr->args.g0.id = SLV6_Tb_UXTH_ID;
  instr->args.g63.d = d;
  instr->args.g63.m = m;
  return true;
}

/* the main function, used by the ISS loop */
void thumb_decode_and_store(struct SLv6_Instruction *instr, uint16_t bincode) {
  bool found = false;
  const uint16_t opcode = bincode>>11;
  switch (opcode) {
  case 0: /* 00000 */
    if ((bincode&0x0000f800)==0x00000000 && try_store_Tb_LSL1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 1: /* 00001 */
    if ((bincode&0x0000f800)==0x00000800 && try_store_Tb_LSR1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 2: /* 00010 */
    if ((bincode&0x0000f800)==0x00001000 && try_store_Tb_ASR1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 3: /* 00011 */
    if ((bincode&0x0000fe00)==0x00001c00 && try_store_Tb_ADD1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000fe00)==0x00001e00 && try_store_Tb_SUB1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000fe00)==0x00001a00 && try_store_Tb_SUB3(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ffc0)==0x00001c00 && try_store_Tb_MOV2(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000fe00)==0x00001800 && try_store_Tb_ADD3(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 4: /* 00100 */
    if ((bincode&0x0000f800)==0x00002000 && try_store_Tb_MOV1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 5: /* 00101 */
    if ((bincode&0x0000f800)==0x00002800 && try_store_Tb_CMP1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 6: /* 00110 */
    if ((bincode&0x0000f800)==0x00003000 && try_store_Tb_ADD2(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 7: /* 00111 */
    if ((bincode&0x0000f800)==0x00003800 && try_store_Tb_SUB2(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 8: /* 01000 */
    if ((bincode&0x0000ffc0)==0x00004180 && try_store_Tb_SBC(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ffc0)==0x000042c0 && try_store_Tb_CMN(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ff87)==0x00004780 && try_store_Tb_BLX2(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ffc0)==0x00004100 && try_store_Tb_ASR2(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ffc0)==0x00004080 && try_store_Tb_LSL2(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ffc0)==0x00004380 && try_store_Tb_BIC(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ffc0)==0x00004200 && try_store_Tb_TST(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ffc0)==0x000043c0 && try_store_Tb_MVN(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ffc0)==0x00004340 && try_store_Tb_MUL(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ffc0)==0x000040c0 && try_store_Tb_LSR2(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ffc0)==0x00004140 && try_store_Tb_ADC(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ff87)==0x00004700 && try_store_Tb_BX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ff00)==0x00004500 && try_store_Tb_CMP3(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ffc0)==0x00004240 && try_store_Tb_NEG(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ffc0)==0x000041c0 && try_store_Tb_ROR(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ffc0)==0x00004300 && try_store_Tb_ORR(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ff00)==0x00004400 && try_store_Tb_ADD4(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ffc0)==0x00004000 && try_store_Tb_AND(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ffc0)==0x00004040 && try_store_Tb_EOR(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ffc0)==0x00004280 && try_store_Tb_CMP2(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ff00)==0x00004600 && try_store_Tb_CPY(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 9: /* 01001 */
    if ((bincode&0x0000f800)==0x00004800 && try_store_Tb_LDR3(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 10: /* 01010 */
    if ((bincode&0x0000fe00)==0x00005200 && try_store_Tb_STRH2(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000fe00)==0x00005600 && try_store_Tb_LDRSB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000fe00)==0x00005400 && try_store_Tb_STRB2(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000fe00)==0x00005000 && try_store_Tb_STR2(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 11: /* 01011 */
    if ((bincode&0x0000fe00)==0x00005e00 && try_store_Tb_LDRSH(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000fe00)==0x00005a00 && try_store_Tb_LDRH2(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000fe00)==0x00005c00 && try_store_Tb_LDRB2(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000fe00)==0x00005800 && try_store_Tb_LDR2(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 12: /* 01100 */
    if ((bincode&0x0000f800)==0x00006000 && try_store_Tb_STR1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 13: /* 01101 */
    if ((bincode&0x0000f800)==0x00006800 && try_store_Tb_LDR1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 14: /* 01110 */
    if ((bincode&0x0000f800)==0x00007000 && try_store_Tb_STRB1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 15: /* 01111 */
    if ((bincode&0x0000f800)==0x00007800 && try_store_Tb_LDRB1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 16: /* 10000 */
    if ((bincode&0x0000f800)==0x00008000 && try_store_Tb_STRH1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 17: /* 10001 */
    if ((bincode&0x0000f800)==0x00008800 && try_store_Tb_LDRH1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 18: /* 10010 */
    if ((bincode&0x0000f800)==0x00009000 && try_store_Tb_STR3(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 19: /* 10011 */
    if ((bincode&0x0000f800)==0x00009800 && try_store_Tb_LDR4(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 20: /* 10100 */
    if ((bincode&0x0000f800)==0x0000a000 && try_store_Tb_ADD5(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 21: /* 10101 */
    if ((bincode&0x0000f800)==0x0000a800 && try_store_Tb_ADD6(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 22: /* 10110 */
    if ((bincode&0x0000ffc0)==0x0000b280 && try_store_Tb_UXTH(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ffc0)==0x0000b2c0 && try_store_Tb_UXTB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ffc0)==0x0000b200 && try_store_Tb_SXTH(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ffc0)==0x0000b240 && try_store_Tb_SXTB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000fff7)==0x0000b650 && try_store_Tb_SETEND(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ffe8)==0x0000b660 && try_store_Tb_CPS(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ff80)==0x0000b000 && try_store_Tb_ADD7(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ff80)==0x0000b080 && try_store_Tb_SUB4(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000fe00)==0x0000b400 && try_store_Tb_PUSH(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 23: /* 10111 */
    if ((bincode&0x0000ffc0)==0x0000bac0 && try_store_Tb_REVSH(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ffc0)==0x0000ba40 && try_store_Tb_REV16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ffc0)==0x0000ba00 && try_store_Tb_REV(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000ff00)==0x0000be00 && try_store_Tb_BKPT(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000fe00)==0x0000bc00 && try_store_Tb_POP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 24: /* 11000 */
    if ((bincode&0x0000f800)==0x0000c000 && try_store_Tb_STMIA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 25: /* 11001 */
    if ((bincode&0x0000f800)==0x0000c800 && try_store_Tb_LDMIA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 26: /* 11010 */
    if ((bincode&0x0000f000)==0x0000d000 && try_store_Tb_B1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 27: /* 11011 */
    if ((bincode&0x0000ff00)==0x0000df00 && try_store_Tb_SWI(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000f000)==0x0000d000 && try_store_Tb_B1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 28: /* 11100 */
    if ((bincode&0x0000f800)==0x0000e000 && try_store_Tb_B2(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0000e000)==0x0000e000 && try_store_Tb_BL(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 29: /* 11101 */
  case 30: /* 11110 */
  case 31: /* 11111 */
    if ((bincode&0x0000e000)==0x0000e000 && try_store_Tb_BL(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  }
  if (!found) instr->args.g0.id = SLV6_UNPRED_OR_UNDEF_ID;
}

END_SIMSOC_NAMESPACE
