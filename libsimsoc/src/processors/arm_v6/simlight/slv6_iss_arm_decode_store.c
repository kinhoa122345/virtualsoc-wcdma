#include "slv6_iss_c_prelude.h"

/* A4.1.23--A5.2.2
 * LDR -- Load and Store Word or Unsigned Byte - Immediate offset */
static bool try_store_LDR_M2_ImmOff(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t offset_12 = get_bits(bincode,11,0);
  if (!(((W == 0) || (n != d)))) return false;
  const uint32_t signed_offset_12 = (U ? offset_12 : -offset_12);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_LDR_M2_ImmOff_NC_ID;
  else
    instr->args.g0.id = SLV6_LDR_M2_ImmOff_ID;
  instr->args.g1.d = d;
  instr->args.g1.n = n;
  instr->args.g1.cond = cond;
  instr->args.g1.signed_offset_12 = signed_offset_12;
  return true;
}

/* A4.1.99--A5.2.2
 * STR -- Load and Store Word or Unsigned Byte - Immediate offset */
static bool try_store_STR_M2_ImmOff(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t offset_12 = get_bits(bincode,11,0);
  if (!(((W == 0) || (n != d)))) return false;
  const uint32_t signed_offset_12 = (U ? offset_12 : -offset_12);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_STR_M2_ImmOff_NC_ID;
  else
    instr->args.g0.id = SLV6_STR_M2_ImmOff_ID;
  instr->args.g1.d = d;
  instr->args.g1.n = n;
  instr->args.g1.cond = cond;
  instr->args.g1.signed_offset_12 = signed_offset_12;
  return true;
}

/* A4.1.5
 * B, BL (L=1) */
static bool try_store_B_L1(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  bool L = get_bit(bincode,24);
  uint32_t signed_immed_24 = get_bits(bincode,23,0);
  const uint32_t pc_offset = SignExtend_30(signed_immed_24) << 2;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_B_L1_NC_ID;
  else
    instr->args.g0.id = SLV6_B_L1_ID;
  instr->args.g2.cond = cond;
  instr->args.g2.pc_offset = pc_offset;
  return true;
}

/* A4.1.5
 * B, BL (L=0) */
static bool try_store_B_L0(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  bool L = get_bit(bincode,24);
  uint32_t signed_immed_24 = get_bits(bincode,23,0);
  const uint32_t pc_offset = SignExtend_30(signed_immed_24) << 2;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_B_L0_NC_ID;
  else
    instr->args.g0.id = SLV6_B_L0_ID;
  instr->args.g2.cond = cond;
  instr->args.g2.pc_offset = pc_offset;
  return true;
}

/* A4.1.106--A5.1.3
 * SUB -- Data processing operands - Immediate (S=1) */
static bool try_store_SUB_M1_Imm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_SUB_M1_Imm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_SUB_M1_Imm_S1_ID;
  instr->args.g3.d = d;
  instr->args.g3.n = n;
  instr->args.g3.rotate_imm = rotate_imm;
  instr->args.g3.cond = cond;
  instr->args.g3.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.106--A5.1.3
 * SUB -- Data processing operands - Immediate (S=0) */
static bool try_store_SUB_M1_Imm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_SUB_M1_Imm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_SUB_M1_Imm_S0_ID;
  instr->args.g3.d = d;
  instr->args.g3.n = n;
  instr->args.g3.rotate_imm = rotate_imm;
  instr->args.g3.cond = cond;
  instr->args.g3.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.15--A5.1.4
 * CMP -- Data processing operands - Register */
static bool try_store_CMP_M1_Reg(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_CMP_M1_Reg_NC_ID;
  else
    instr->args.g0.id = SLV6_CMP_M1_Reg_ID;
  instr->args.g4.m = m;
  instr->args.g4.n = n;
  instr->args.g4.cond = cond;
  return true;
}

/* A4.1.3--A5.1.3
 * ADD -- Data processing operands - Immediate (S=1) */
static bool try_store_ADD_M1_Imm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_ADD_M1_Imm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_ADD_M1_Imm_S1_ID;
  instr->args.g3.d = d;
  instr->args.g3.n = n;
  instr->args.g3.rotate_imm = rotate_imm;
  instr->args.g3.cond = cond;
  instr->args.g3.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.3--A5.1.3
 * ADD -- Data processing operands - Immediate (S=0) */
static bool try_store_ADD_M1_Imm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_ADD_M1_Imm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_ADD_M1_Imm_S0_ID;
  instr->args.g3.d = d;
  instr->args.g3.n = n;
  instr->args.g3.rotate_imm = rotate_imm;
  instr->args.g3.cond = cond;
  instr->args.g3.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.3--A5.1.4
 * ADD -- Data processing operands - Register (S=1) */
static bool try_store_ADD_M1_Reg_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_ADD_M1_Reg_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_ADD_M1_Reg_S1_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.3--A5.1.4
 * ADD -- Data processing operands - Register (S=0) */
static bool try_store_ADD_M1_Reg_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_ADD_M1_Reg_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_ADD_M1_Reg_S0_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.18--A5.1.4
 * EOR -- Data processing operands - Register (S=1) */
static bool try_store_EOR_M1_Reg_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_EOR_M1_Reg_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_EOR_M1_Reg_S1_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.18--A5.1.4
 * EOR -- Data processing operands - Register (S=0) */
static bool try_store_EOR_M1_Reg_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_EOR_M1_Reg_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_EOR_M1_Reg_S0_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.4--A5.1.3
 * AND -- Data processing operands - Immediate (S=1) */
static bool try_store_AND_M1_Imm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_AND_M1_Imm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_AND_M1_Imm_S1_ID;
  instr->args.g3.d = d;
  instr->args.g3.n = n;
  instr->args.g3.rotate_imm = rotate_imm;
  instr->args.g3.cond = cond;
  instr->args.g3.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.4--A5.1.3
 * AND -- Data processing operands - Immediate (S=0) */
static bool try_store_AND_M1_Imm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_AND_M1_Imm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_AND_M1_Imm_S0_ID;
  instr->args.g3.d = d;
  instr->args.g3.n = n;
  instr->args.g3.rotate_imm = rotate_imm;
  instr->args.g3.cond = cond;
  instr->args.g3.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.35--A5.1.7
 * MOV -- Data processing operands - Logical shift right by immediate (S=1) */
static bool try_store_MOV_M1_LSRImm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!(not_cpy_instr(bincode))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_MOV_M1_LSRImm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_MOV_M1_LSRImm_S1_ID;
  instr->args.g6.d = d;
  instr->args.g6.m = m;
  instr->args.g6.shift_imm = shift_imm;
  instr->args.g6.cond = cond;
  return true;
}

/* A4.1.35--A5.1.7
 * MOV -- Data processing operands - Logical shift right by immediate (S=0) */
static bool try_store_MOV_M1_LSRImm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!(not_cpy_instr(bincode))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_MOV_M1_LSRImm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_MOV_M1_LSRImm_S0_ID;
  instr->args.g6.d = d;
  instr->args.g6.m = m;
  instr->args.g6.shift_imm = shift_imm;
  instr->args.g6.cond = cond;
  return true;
}

/* A4.1.17
 * CPY */
static bool try_store_CPY(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_CPY_NC_ID;
  else
    instr->args.g0.id = SLV6_CPY_ID;
  instr->args.g7.d = d;
  instr->args.g7.m = m;
  instr->args.g7.cond = cond;
  return true;
}

/* A4.1.35--A5.1.5
 * MOV -- Data processing operands - Logical shift left by immediate (S=1) */
static bool try_store_MOV_M1_LSLImm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((not_cpy_instr(bincode) && (shift_imm != 0)))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_MOV_M1_LSLImm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_MOV_M1_LSLImm_S1_ID;
  instr->args.g6.d = d;
  instr->args.g6.m = m;
  instr->args.g6.shift_imm = shift_imm;
  instr->args.g6.cond = cond;
  return true;
}

/* A4.1.35--A5.1.5
 * MOV -- Data processing operands - Logical shift left by immediate (S=0) */
static bool try_store_MOV_M1_LSLImm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((not_cpy_instr(bincode) && (shift_imm != 0)))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_MOV_M1_LSLImm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_MOV_M1_LSLImm_S0_ID;
  instr->args.g6.d = d;
  instr->args.g6.m = m;
  instr->args.g6.shift_imm = shift_imm;
  instr->args.g6.cond = cond;
  return true;
}

/* A4.1.35--A5.1.3
 * MOV -- Data processing operands - Immediate (S=1) */
static bool try_store_MOV_M1_Imm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  if (!(not_cpy_instr(bincode))) return false;
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_MOV_M1_Imm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_MOV_M1_Imm_S1_ID;
  instr->args.g8.d = d;
  instr->args.g8.rotate_imm = rotate_imm;
  instr->args.g8.cond = cond;
  instr->args.g8.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.35--A5.1.3
 * MOV -- Data processing operands - Immediate (S=0) */
static bool try_store_MOV_M1_Imm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  if (!(not_cpy_instr(bincode))) return false;
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_MOV_M1_Imm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_MOV_M1_Imm_S0_ID;
  instr->args.g8.d = d;
  instr->args.g8.rotate_imm = rotate_imm;
  instr->args.g8.cond = cond;
  instr->args.g8.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.20--A5.4.2
 * LDM (1) -- Load and Store Multiple - Increment after (W=1) */
static bool try_store_LDM1_M4_IA_W1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!(((n != 15) && (register_list != 0)))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_LDM1_M4_IA_W1_NC_ID;
  else
    instr->args.g0.id = SLV6_LDM1_M4_IA_W1_ID;
  instr->args.g9.n = n;
  instr->args.g9.nb_reg_x4 = nb_reg_x4;
  instr->args.g9.cond = cond;
  instr->args.g9.register_list = register_list;
  return true;
}

/* A4.1.20--A5.4.2
 * LDM (1) -- Load and Store Multiple - Increment after (W=0) */
static bool try_store_LDM1_M4_IA_W0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!(((n != 15) && (register_list != 0)))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_LDM1_M4_IA_W0_NC_ID;
  else
    instr->args.g0.id = SLV6_LDM1_M4_IA_W0_ID;
  instr->args.g9.n = n;
  instr->args.g9.nb_reg_x4 = nb_reg_x4;
  instr->args.g9.cond = cond;
  instr->args.g9.register_list = register_list;
  return true;
}

/* A4.1.15--A5.1.3
 * CMP -- Data processing operands - Immediate */
static bool try_store_CMP_M1_Imm(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_CMP_M1_Imm_NC_ID;
  else
    instr->args.g0.id = SLV6_CMP_M1_Imm_ID;
  instr->args.g10.n = n;
  instr->args.g10.rotate_imm = rotate_imm;
  instr->args.g10.cond = cond;
  instr->args.g10.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.23--A5.2.4
 * LDR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) */
static bool try_store_LDR_M2_ScRegOff_U1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift = get_bits(bincode,6,5);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((((W == 0) || (n != d)) && ((m != 15) && ((shift != 0) || (shift_imm != 0)))))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_LDR_M2_ScRegOff_U1_NC_ID;
  else
    instr->args.g0.id = SLV6_LDR_M2_ScRegOff_U1_ID;
  instr->args.g11.d = d;
  instr->args.g11.m = m;
  instr->args.g11.n = n;
  instr->args.g11.shift = shift;
  instr->args.g11.shift_imm = shift_imm;
  instr->args.g11.cond = cond;
  return true;
}

/* A4.1.23--A5.2.4
 * LDR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) */
static bool try_store_LDR_M2_ScRegOff_U0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift = get_bits(bincode,6,5);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((((W == 0) || (n != d)) && ((m != 15) && ((shift != 0) || (shift_imm != 0)))))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_LDR_M2_ScRegOff_U0_NC_ID;
  else
    instr->args.g0.id = SLV6_LDR_M2_ScRegOff_U0_ID;
  instr->args.g11.d = d;
  instr->args.g11.m = m;
  instr->args.g11.n = n;
  instr->args.g11.shift = shift;
  instr->args.g11.shift_imm = shift_imm;
  instr->args.g11.cond = cond;
  return true;
}

/* A4.1.10
 * BX */
static bool try_store_BX(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_BX_NC_ID;
  else
    instr->args.g0.id = SLV6_BX_ID;
  instr->args.g12.m = m;
  instr->args.g12.cond = cond;
  return true;
}

/* A4.1.3--A5.1.5
 * ADD -- Data processing operands - Logical shift left by immediate (S=1) */
static bool try_store_ADD_M1_LSLImm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_ADD_M1_LSLImm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_ADD_M1_LSLImm_S1_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.3--A5.1.5
 * ADD -- Data processing operands - Logical shift left by immediate (S=0) */
static bool try_store_ADD_M1_LSLImm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_ADD_M1_LSLImm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_ADD_M1_LSLImm_S0_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.24--A5.2.2
 * LDRB -- Load and Store Word or Unsigned Byte - Immediate offset */
static bool try_store_LDRB_M2_ImmOff(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t offset_12 = get_bits(bincode,11,0);
  if (!(((d != 15) && ((W == 0) || (n != d))))) return false;
  const uint32_t signed_offset_12 = (U ? offset_12 : -offset_12);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_LDRB_M2_ImmOff_NC_ID;
  else
    instr->args.g0.id = SLV6_LDRB_M2_ImmOff_ID;
  instr->args.g1.d = d;
  instr->args.g1.n = n;
  instr->args.g1.cond = cond;
  instr->args.g1.signed_offset_12 = signed_offset_12;
  return true;
}

/* A4.1.42--A5.1.4
 * ORR -- Data processing operands - Register (S=1) */
static bool try_store_ORR_M1_Reg_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_ORR_M1_Reg_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_ORR_M1_Reg_S1_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.42--A5.1.4
 * ORR -- Data processing operands - Register (S=0) */
static bool try_store_ORR_M1_Reg_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_ORR_M1_Reg_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_ORR_M1_Reg_S0_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.35--A5.1.11
 * MOV -- Data processing operands - Rotate right by immediate (S=1) */
static bool try_store_MOV_M1_RRImm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((not_cpy_instr(bincode) && (shift_imm != 0)))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_MOV_M1_RRImm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_MOV_M1_RRImm_S1_ID;
  instr->args.g6.d = d;
  instr->args.g6.m = m;
  instr->args.g6.shift_imm = shift_imm;
  instr->args.g6.cond = cond;
  return true;
}

/* A4.1.35--A5.1.11
 * MOV -- Data processing operands - Rotate right by immediate (S=0) */
static bool try_store_MOV_M1_RRImm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((not_cpy_instr(bincode) && (shift_imm != 0)))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_MOV_M1_RRImm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_MOV_M1_RRImm_S0_ID;
  instr->args.g6.d = d;
  instr->args.g6.m = m;
  instr->args.g6.shift_imm = shift_imm;
  instr->args.g6.cond = cond;
  return true;
}

/* A4.1.23--A5.2.8
 * LDR -- Load and Store Word or Unsigned Byte - Immediate post indexed */
static bool try_store_LDR_M2_Imm_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t offset_12 = get_bits(bincode,11,0);
  if (!((((W == 0) || (n != d)) && (n != 15)))) return false;
  const uint32_t signed_offset_12 = (U ? offset_12 : -offset_12);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_LDR_M2_Imm_postInd_NC_ID;
  else
    instr->args.g0.id = SLV6_LDR_M2_Imm_postInd_ID;
  instr->args.g1.d = d;
  instr->args.g1.n = n;
  instr->args.g1.cond = cond;
  instr->args.g1.signed_offset_12 = signed_offset_12;
  return true;
}

/* A4.1.18--A5.1.11
 * EOR -- Data processing operands - Rotate right by immediate (S=1) */
static bool try_store_EOR_M1_RRImm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_EOR_M1_RRImm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_EOR_M1_RRImm_S1_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.18--A5.1.11
 * EOR -- Data processing operands - Rotate right by immediate (S=0) */
static bool try_store_EOR_M1_RRImm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_EOR_M1_RRImm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_EOR_M1_RRImm_S0_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.4--A5.1.4
 * AND -- Data processing operands - Register (S=1) */
static bool try_store_AND_M1_Reg_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_AND_M1_Reg_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_AND_M1_Reg_S1_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.4--A5.1.4
 * AND -- Data processing operands - Register (S=0) */
static bool try_store_AND_M1_Reg_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_AND_M1_Reg_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_AND_M1_Reg_S0_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.99--A5.2.5
 * STR -- Load and Store Word or Unsigned Byte - Immediate pre indexed */
static bool try_store_STR_M2_Imm_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t offset_12 = get_bits(bincode,11,0);
  if (!((((W == 0) || (n != d)) && (n != 15)))) return false;
  const uint32_t signed_offset_12 = (U ? offset_12 : -offset_12);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_STR_M2_Imm_preInd_NC_ID;
  else
    instr->args.g0.id = SLV6_STR_M2_Imm_preInd_ID;
  instr->args.g1.d = d;
  instr->args.g1.n = n;
  instr->args.g1.cond = cond;
  instr->args.g1.signed_offset_12 = signed_offset_12;
  return true;
}

/* A4.1.100--A5.2.2
 * STRB -- Load and Store Word or Unsigned Byte - Immediate offset */
static bool try_store_STRB_M2_ImmOff(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t offset_12 = get_bits(bincode,11,0);
  if (!((((W == 0) || (n != d)) && (d != 15)))) return false;
  const uint32_t signed_offset_12 = (U ? offset_12 : -offset_12);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_STRB_M2_ImmOff_NC_ID;
  else
    instr->args.g0.id = SLV6_STRB_M2_ImmOff_ID;
  instr->args.g1.d = d;
  instr->args.g1.n = n;
  instr->args.g1.cond = cond;
  instr->args.g1.signed_offset_12 = signed_offset_12;
  return true;
}

/* A4.1.42--A5.1.5
 * ORR -- Data processing operands - Logical shift left by immediate (S=1) */
static bool try_store_ORR_M1_LSLImm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_ORR_M1_LSLImm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_ORR_M1_LSLImm_S1_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.42--A5.1.5
 * ORR -- Data processing operands - Logical shift left by immediate (S=0) */
static bool try_store_ORR_M1_LSLImm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_ORR_M1_LSLImm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_ORR_M1_LSLImm_S0_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.2--A5.1.4
 * ADC -- Data processing operands - Register (S=1) */
static bool try_store_ADC_M1_Reg_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_ADC_M1_Reg_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_ADC_M1_Reg_S1_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.2--A5.1.4
 * ADC -- Data processing operands - Register (S=0) */
static bool try_store_ADC_M1_Reg_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_ADC_M1_Reg_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_ADC_M1_Reg_S0_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.24--A5.2.3
 * LDRB -- Load and Store Word or Unsigned Byte - Register offset (U=1) */
static bool try_store_LDRB_M2_RegOff_U1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && (((W == 0) || (n != d)) && (m != 15))))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_LDRB_M2_RegOff_U1_NC_ID;
  else
    instr->args.g0.id = SLV6_LDRB_M2_RegOff_U1_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.24--A5.2.3
 * LDRB -- Load and Store Word or Unsigned Byte - Register offset (U=0) */
static bool try_store_LDRB_M2_RegOff_U0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && (((W == 0) || (n != d)) && (m != 15))))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_LDRB_M2_RegOff_U0_NC_ID;
  else
    instr->args.g0.id = SLV6_LDRB_M2_RegOff_U0_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.60--A5.1.4
 * RSB -- Data processing operands - Register (S=1) */
static bool try_store_RSB_M1_Reg_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_RSB_M1_Reg_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_RSB_M1_Reg_S1_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.60--A5.1.4
 * RSB -- Data processing operands - Register (S=0) */
static bool try_store_RSB_M1_Reg_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_RSB_M1_Reg_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_RSB_M1_Reg_S0_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.6--A5.1.3
 * BIC -- Data processing operands - Immediate (S=1) */
static bool try_store_BIC_M1_Imm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_BIC_M1_Imm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_BIC_M1_Imm_S1_ID;
  instr->args.g3.d = d;
  instr->args.g3.n = n;
  instr->args.g3.rotate_imm = rotate_imm;
  instr->args.g3.cond = cond;
  instr->args.g3.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.6--A5.1.3
 * BIC -- Data processing operands - Immediate (S=0) */
static bool try_store_BIC_M1_Imm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_BIC_M1_Imm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_BIC_M1_Imm_S0_ID;
  instr->args.g3.d = d;
  instr->args.g3.n = n;
  instr->args.g3.rotate_imm = rotate_imm;
  instr->args.g3.cond = cond;
  instr->args.g3.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.41--A5.1.3
 * MVN -- Data processing operands - Immediate (S=1) */
static bool try_store_MVN_M1_Imm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_MVN_M1_Imm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_MVN_M1_Imm_S1_ID;
  instr->args.g8.d = d;
  instr->args.g8.rotate_imm = rotate_imm;
  instr->args.g8.cond = cond;
  instr->args.g8.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.41--A5.1.3
 * MVN -- Data processing operands - Immediate (S=0) */
static bool try_store_MVN_M1_Imm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_MVN_M1_Imm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_MVN_M1_Imm_S0_ID;
  instr->args.g8.d = d;
  instr->args.g8.rotate_imm = rotate_imm;
  instr->args.g8.cond = cond;
  instr->args.g8.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.42--A5.1.7
 * ORR -- Data processing operands - Logical shift right by immediate (S=1) */
static bool try_store_ORR_M1_LSRImm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_ORR_M1_LSRImm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_ORR_M1_LSRImm_S1_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.42--A5.1.7
 * ORR -- Data processing operands - Logical shift right by immediate (S=0) */
static bool try_store_ORR_M1_LSRImm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_ORR_M1_LSRImm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_ORR_M1_LSRImm_S0_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.18--A5.1.7
 * EOR -- Data processing operands - Logical shift right by immediate (S=1) */
static bool try_store_EOR_M1_LSRImm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_EOR_M1_LSRImm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_EOR_M1_LSRImm_S1_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.18--A5.1.7
 * EOR -- Data processing operands - Logical shift right by immediate (S=0) */
static bool try_store_EOR_M1_LSRImm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_EOR_M1_LSRImm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_EOR_M1_LSRImm_S0_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.23--A5.2.3
 * LDR -- Load and Store Word or Unsigned Byte - Register offset (U=1) */
static bool try_store_LDR_M2_RegOff_U1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!((((W == 0) || (n != d)) && (m != 15)))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_LDR_M2_RegOff_U1_NC_ID;
  else
    instr->args.g0.id = SLV6_LDR_M2_RegOff_U1_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.23--A5.2.3
 * LDR -- Load and Store Word or Unsigned Byte - Register offset (U=0) */
static bool try_store_LDR_M2_RegOff_U0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!((((W == 0) || (n != d)) && (m != 15)))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_LDR_M2_RegOff_U0_NC_ID;
  else
    instr->args.g0.id = SLV6_LDR_M2_RegOff_U0_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.35--A5.1.8
 * MOV -- Data processing operands - Logical shift right by register (S=1) */
static bool try_store_MOV_M1_LSRReg_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!((not_cpy_instr(bincode) && ((d != 15) && ((m != 15) && ((s != 15) && (n != 15))))))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_MOV_M1_LSRReg_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_MOV_M1_LSRReg_S1_ID;
  instr->args.g14.d = d;
  instr->args.g14.m = m;
  instr->args.g14.s = s;
  instr->args.g14.cond = cond;
  return true;
}

/* A4.1.35--A5.1.8
 * MOV -- Data processing operands - Logical shift right by register (S=0) */
static bool try_store_MOV_M1_LSRReg_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!((not_cpy_instr(bincode) && ((d != 15) && ((m != 15) && ((s != 15) && (n != 15))))))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_MOV_M1_LSRReg_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_MOV_M1_LSRReg_S0_ID;
  instr->args.g14.d = d;
  instr->args.g14.m = m;
  instr->args.g14.s = s;
  instr->args.g14.cond = cond;
  return true;
}

/* A4.1.100--A5.2.3
 * STRB -- Load and Store Word or Unsigned Byte - Register offset (U=1) */
static bool try_store_STRB_M2_RegOff_U1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!((((W == 0) || (n != d)) && ((d != 15) && (m != 15))))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_STRB_M2_RegOff_U1_NC_ID;
  else
    instr->args.g0.id = SLV6_STRB_M2_RegOff_U1_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.100--A5.2.3
 * STRB -- Load and Store Word or Unsigned Byte - Register offset (U=0) */
static bool try_store_STRB_M2_RegOff_U0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!((((W == 0) || (n != d)) && ((d != 15) && (m != 15))))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_STRB_M2_RegOff_U0_NC_ID;
  else
    instr->args.g0.id = SLV6_STRB_M2_RegOff_U0_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.99--A5.2.4
 * STR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) */
static bool try_store_STR_M2_ScRegOff_U1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift = get_bits(bincode,6,5);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((((W == 0) || (n != d)) && ((m != 15) && ((shift != 0) || (shift_imm != 0)))))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_STR_M2_ScRegOff_U1_NC_ID;
  else
    instr->args.g0.id = SLV6_STR_M2_ScRegOff_U1_ID;
  instr->args.g11.d = d;
  instr->args.g11.m = m;
  instr->args.g11.n = n;
  instr->args.g11.shift = shift;
  instr->args.g11.shift_imm = shift_imm;
  instr->args.g11.cond = cond;
  return true;
}

/* A4.1.99--A5.2.4
 * STR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) */
static bool try_store_STR_M2_ScRegOff_U0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift = get_bits(bincode,6,5);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((((W == 0) || (n != d)) && ((m != 15) && ((shift != 0) || (shift_imm != 0)))))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_STR_M2_ScRegOff_U0_NC_ID;
  else
    instr->args.g0.id = SLV6_STR_M2_ScRegOff_U0_ID;
  instr->args.g11.d = d;
  instr->args.g11.m = m;
  instr->args.g11.n = n;
  instr->args.g11.shift = shift;
  instr->args.g11.shift_imm = shift_imm;
  instr->args.g11.cond = cond;
  return true;
}

/* A4.1.14--A5.1.4
 * CMN -- Data processing operands - Register */
static bool try_store_CMN_M1_Reg(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_CMN_M1_Reg_NC_ID;
  else
    instr->args.g0.id = SLV6_CMN_M1_Reg_ID;
  instr->args.g4.m = m;
  instr->args.g4.n = n;
  instr->args.g4.cond = cond;
  return true;
}

/* A4.1.99--A5.2.9
 * STR -- Load and Store Word or Unsigned Byte - Register post indexed (U=1) */
static bool try_store_STR_M2_Reg_postInd_U1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!((((W == 0) || (n != d)) && ((n != 15) && (m != 15))))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_STR_M2_Reg_postInd_U1_NC_ID;
  else
    instr->args.g0.id = SLV6_STR_M2_Reg_postInd_U1_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.99--A5.2.9
 * STR -- Load and Store Word or Unsigned Byte - Register post indexed (U=0) */
static bool try_store_STR_M2_Reg_postInd_U0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!((((W == 0) || (n != d)) && ((n != 15) && (m != 15))))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_STR_M2_Reg_postInd_U0_NC_ID;
  else
    instr->args.g0.id = SLV6_STR_M2_Reg_postInd_U0_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.99--A5.2.3
 * STR -- Load and Store Word or Unsigned Byte - Register offset (U=1) */
static bool try_store_STR_M2_RegOff_U1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!((((W == 0) || (n != d)) && (m != 15)))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_STR_M2_RegOff_U1_NC_ID;
  else
    instr->args.g0.id = SLV6_STR_M2_RegOff_U1_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.99--A5.2.3
 * STR -- Load and Store Word or Unsigned Byte - Register offset (U=0) */
static bool try_store_STR_M2_RegOff_U0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!((((W == 0) || (n != d)) && (m != 15)))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_STR_M2_RegOff_U0_NC_ID;
  else
    instr->args.g0.id = SLV6_STR_M2_RegOff_U0_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.18--A5.1.5
 * EOR -- Data processing operands - Logical shift left by immediate (S=1) */
static bool try_store_EOR_M1_LSLImm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_EOR_M1_LSLImm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_EOR_M1_LSLImm_S1_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.18--A5.1.5
 * EOR -- Data processing operands - Logical shift left by immediate (S=0) */
static bool try_store_EOR_M1_LSLImm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_EOR_M1_LSLImm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_EOR_M1_LSLImm_S0_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.60--A5.1.3
 * RSB -- Data processing operands - Immediate (S=1) */
static bool try_store_RSB_M1_Imm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_RSB_M1_Imm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_RSB_M1_Imm_S1_ID;
  instr->args.g3.d = d;
  instr->args.g3.n = n;
  instr->args.g3.rotate_imm = rotate_imm;
  instr->args.g3.cond = cond;
  instr->args.g3.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.60--A5.1.3
 * RSB -- Data processing operands - Immediate (S=0) */
static bool try_store_RSB_M1_Imm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_RSB_M1_Imm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_RSB_M1_Imm_S0_ID;
  instr->args.g3.d = d;
  instr->args.g3.n = n;
  instr->args.g3.rotate_imm = rotate_imm;
  instr->args.g3.cond = cond;
  instr->args.g3.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.35--A5.1.9
 * MOV -- Data processing operands - Arithmetic shift right by immediate (S=1) */
static bool try_store_MOV_M1_ASRImm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!(not_cpy_instr(bincode))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_MOV_M1_ASRImm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_MOV_M1_ASRImm_S1_ID;
  instr->args.g6.d = d;
  instr->args.g6.m = m;
  instr->args.g6.shift_imm = shift_imm;
  instr->args.g6.cond = cond;
  return true;
}

/* A4.1.35--A5.1.9
 * MOV -- Data processing operands - Arithmetic shift right by immediate (S=0) */
static bool try_store_MOV_M1_ASRImm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!(not_cpy_instr(bincode))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_MOV_M1_ASRImm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_MOV_M1_ASRImm_S0_ID;
  instr->args.g6.d = d;
  instr->args.g6.m = m;
  instr->args.g6.shift_imm = shift_imm;
  instr->args.g6.cond = cond;
  return true;
}

/* A4.1.3--A5.1.11
 * ADD -- Data processing operands - Rotate right by immediate (S=1) */
static bool try_store_ADD_M1_RRImm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_ADD_M1_RRImm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_ADD_M1_RRImm_S1_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.3--A5.1.11
 * ADD -- Data processing operands - Rotate right by immediate (S=0) */
static bool try_store_ADD_M1_RRImm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_ADD_M1_RRImm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_ADD_M1_RRImm_S0_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.60--A5.1.5
 * RSB -- Data processing operands - Logical shift left by immediate (S=1) */
static bool try_store_RSB_M1_LSLImm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_RSB_M1_LSLImm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_RSB_M1_LSLImm_S1_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.60--A5.1.5
 * RSB -- Data processing operands - Logical shift left by immediate (S=0) */
static bool try_store_RSB_M1_LSLImm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_RSB_M1_LSLImm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_RSB_M1_LSLImm_S0_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.100--A5.2.8
 * STRB -- Load and Store Word or Unsigned Byte - Immediate post indexed */
static bool try_store_STRB_M2_Imm_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t offset_12 = get_bits(bincode,11,0);
  if (!((((W == 0) || (n != d)) && ((d != 15) && (n != 15))))) return false;
  const uint32_t signed_offset_12 = (U ? offset_12 : -offset_12);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_STRB_M2_Imm_postInd_NC_ID;
  else
    instr->args.g0.id = SLV6_STRB_M2_Imm_postInd_ID;
  instr->args.g1.d = d;
  instr->args.g1.n = n;
  instr->args.g1.cond = cond;
  instr->args.g1.signed_offset_12 = signed_offset_12;
  return true;
}

/* A4.1.97--A5.4.2
 * STM (1) -- Load and Store Multiple - Increment after (W=1) */
static bool try_store_STM1_M4_IA_W1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!(((n != 15) && (register_list != 0)))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_STM1_M4_IA_W1_NC_ID;
  else
    instr->args.g0.id = SLV6_STM1_M4_IA_W1_ID;
  instr->args.g9.n = n;
  instr->args.g9.nb_reg_x4 = nb_reg_x4;
  instr->args.g9.cond = cond;
  instr->args.g9.register_list = register_list;
  return true;
}

/* A4.1.97--A5.4.2
 * STM (1) -- Load and Store Multiple - Increment after (W=0) */
static bool try_store_STM1_M4_IA_W0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!(((n != 15) && (register_list != 0)))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_STM1_M4_IA_W0_NC_ID;
  else
    instr->args.g0.id = SLV6_STM1_M4_IA_W0_ID;
  instr->args.g9.n = n;
  instr->args.g9.nb_reg_x4 = nb_reg_x4;
  instr->args.g9.cond = cond;
  instr->args.g9.register_list = register_list;
  return true;
}

/* A4.1.117--A5.1.3
 * TST -- Data processing operands - Immediate */
static bool try_store_TST_M1_Imm(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_TST_M1_Imm_NC_ID;
  else
    instr->args.g0.id = SLV6_TST_M1_Imm_ID;
  instr->args.g10.n = n;
  instr->args.g10.rotate_imm = rotate_imm;
  instr->args.g10.cond = cond;
  instr->args.g10.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.97--A5.4.5
 * STM (1) -- Load and Store Multiple - Decrement before (W=1) */
static bool try_store_STM1_M4_DB_W1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!(((n != 15) && (register_list != 0)))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_STM1_M4_DB_W1_NC_ID;
  else
    instr->args.g0.id = SLV6_STM1_M4_DB_W1_ID;
  instr->args.g9.n = n;
  instr->args.g9.nb_reg_x4 = nb_reg_x4;
  instr->args.g9.cond = cond;
  instr->args.g9.register_list = register_list;
  return true;
}

/* A4.1.97--A5.4.5
 * STM (1) -- Load and Store Multiple - Decrement before (W=0) */
static bool try_store_STM1_M4_DB_W0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!(((n != 15) && (register_list != 0)))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_STM1_M4_DB_W0_NC_ID;
  else
    instr->args.g0.id = SLV6_STM1_M4_DB_W0_ID;
  instr->args.g9.n = n;
  instr->args.g9.nb_reg_x4 = nb_reg_x4;
  instr->args.g9.cond = cond;
  instr->args.g9.register_list = register_list;
  return true;
}

/* A4.1.41--A5.1.4
 * MVN -- Data processing operands - Register (S=1) */
static bool try_store_MVN_M1_Reg_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_MVN_M1_Reg_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_MVN_M1_Reg_S1_ID;
  instr->args.g7.d = d;
  instr->args.g7.m = m;
  instr->args.g7.cond = cond;
  return true;
}

/* A4.1.41--A5.1.4
 * MVN -- Data processing operands - Register (S=0) */
static bool try_store_MVN_M1_Reg_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_MVN_M1_Reg_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_MVN_M1_Reg_S0_ID;
  instr->args.g7.d = d;
  instr->args.g7.m = m;
  instr->args.g7.cond = cond;
  return true;
}

/* A4.1.97--A5.4.3
 * STM (1) -- Load and Store Multiple - Increment before (W=1) */
static bool try_store_STM1_M4_IB_W1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!(((n != 15) && (register_list != 0)))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_STM1_M4_IB_W1_NC_ID;
  else
    instr->args.g0.id = SLV6_STM1_M4_IB_W1_ID;
  instr->args.g9.n = n;
  instr->args.g9.nb_reg_x4 = nb_reg_x4;
  instr->args.g9.cond = cond;
  instr->args.g9.register_list = register_list;
  return true;
}

/* A4.1.97--A5.4.3
 * STM (1) -- Load and Store Multiple - Increment before (W=0) */
static bool try_store_STM1_M4_IB_W0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!(((n != 15) && (register_list != 0)))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_STM1_M4_IB_W0_NC_ID;
  else
    instr->args.g0.id = SLV6_STM1_M4_IB_W0_ID;
  instr->args.g9.n = n;
  instr->args.g9.nb_reg_x4 = nb_reg_x4;
  instr->args.g9.cond = cond;
  instr->args.g9.register_list = register_list;
  return true;
}

/* A4.1.3--A5.1.7
 * ADD -- Data processing operands - Logical shift right by immediate (S=1) */
static bool try_store_ADD_M1_LSRImm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_ADD_M1_LSRImm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_ADD_M1_LSRImm_S1_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.3--A5.1.7
 * ADD -- Data processing operands - Logical shift right by immediate (S=0) */
static bool try_store_ADD_M1_LSRImm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_ADD_M1_LSRImm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_ADD_M1_LSRImm_S0_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.99--A5.2.8
 * STR -- Load and Store Word or Unsigned Byte - Immediate post indexed */
static bool try_store_STR_M2_Imm_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t offset_12 = get_bits(bincode,11,0);
  if (!((((W == 0) || (n != d)) && (n != 15)))) return false;
  const uint32_t signed_offset_12 = (U ? offset_12 : -offset_12);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_STR_M2_Imm_postInd_NC_ID;
  else
    instr->args.g0.id = SLV6_STR_M2_Imm_postInd_ID;
  instr->args.g1.d = d;
  instr->args.g1.n = n;
  instr->args.g1.cond = cond;
  instr->args.g1.signed_offset_12 = signed_offset_12;
  return true;
}

/* A4.1.24--A5.2.4
 * LDRB -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) */
static bool try_store_LDRB_M2_ScRegOff_U1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift = get_bits(bincode,6,5);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!(((d != 15) && (((W == 0) || (n != d)) && ((m != 15) && ((shift != 0) || (shift_imm != 0))))))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_LDRB_M2_ScRegOff_U1_NC_ID;
  else
    instr->args.g0.id = SLV6_LDRB_M2_ScRegOff_U1_ID;
  instr->args.g11.d = d;
  instr->args.g11.m = m;
  instr->args.g11.n = n;
  instr->args.g11.shift = shift;
  instr->args.g11.shift_imm = shift_imm;
  instr->args.g11.cond = cond;
  return true;
}

/* A4.1.24--A5.2.4
 * LDRB -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) */
static bool try_store_LDRB_M2_ScRegOff_U0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift = get_bits(bincode,6,5);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!(((d != 15) && (((W == 0) || (n != d)) && ((m != 15) && ((shift != 0) || (shift_imm != 0))))))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_LDRB_M2_ScRegOff_U0_NC_ID;
  else
    instr->args.g0.id = SLV6_LDRB_M2_ScRegOff_U0_ID;
  instr->args.g11.d = d;
  instr->args.g11.m = m;
  instr->args.g11.n = n;
  instr->args.g11.shift = shift;
  instr->args.g11.shift_imm = shift_imm;
  instr->args.g11.cond = cond;
  return true;
}

/* A4.1.106--A5.1.5
 * SUB -- Data processing operands - Logical shift left by immediate (S=1) */
static bool try_store_SUB_M1_LSLImm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_SUB_M1_LSLImm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_SUB_M1_LSLImm_S1_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.106--A5.1.5
 * SUB -- Data processing operands - Logical shift left by immediate (S=0) */
static bool try_store_SUB_M1_LSLImm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_SUB_M1_LSLImm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_SUB_M1_LSLImm_S0_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.20--A5.4.3
 * LDM (1) -- Load and Store Multiple - Increment before (W=1) */
static bool try_store_LDM1_M4_IB_W1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!(((n != 15) && (register_list != 0)))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_LDM1_M4_IB_W1_NC_ID;
  else
    instr->args.g0.id = SLV6_LDM1_M4_IB_W1_ID;
  instr->args.g9.n = n;
  instr->args.g9.nb_reg_x4 = nb_reg_x4;
  instr->args.g9.cond = cond;
  instr->args.g9.register_list = register_list;
  return true;
}

/* A4.1.20--A5.4.3
 * LDM (1) -- Load and Store Multiple - Increment before (W=0) */
static bool try_store_LDM1_M4_IB_W0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!(((n != 15) && (register_list != 0)))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_LDM1_M4_IB_W0_NC_ID;
  else
    instr->args.g0.id = SLV6_LDM1_M4_IB_W0_ID;
  instr->args.g9.n = n;
  instr->args.g9.nb_reg_x4 = nb_reg_x4;
  instr->args.g9.cond = cond;
  instr->args.g9.register_list = register_list;
  return true;
}

/* A4.1.28--A5.3.2
 * LDRH -- Miscellaneous Loads and Stores - Immediate offset (U=1) */
static bool try_store_LDRH_M3_ImmOff_U1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immedH = get_bits(bincode,11,8);
  uint8_t immedL = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && ((W == 0) || (n != d))))) return false;
  const uint8_t immedHL = (immedH << 4) | immedL;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_LDRH_M3_ImmOff_U1_NC_ID;
  else
    instr->args.g0.id = SLV6_LDRH_M3_ImmOff_U1_ID;
  instr->args.g15.d = d;
  instr->args.g15.n = n;
  instr->args.g15.immedHL = immedHL;
  instr->args.g15.cond = cond;
  return true;
}

/* A4.1.28--A5.3.2
 * LDRH -- Miscellaneous Loads and Stores - Immediate offset (U=0) */
static bool try_store_LDRH_M3_ImmOff_U0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immedH = get_bits(bincode,11,8);
  uint8_t immedL = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && ((W == 0) || (n != d))))) return false;
  const uint8_t immedHL = (immedH << 4) | immedL;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_LDRH_M3_ImmOff_U0_NC_ID;
  else
    instr->args.g0.id = SLV6_LDRH_M3_ImmOff_U0_ID;
  instr->args.g15.d = d;
  instr->args.g15.n = n;
  instr->args.g15.immedHL = immedHL;
  instr->args.g15.cond = cond;
  return true;
}

/* A4.1.23--A5.2.5
 * LDR -- Load and Store Word or Unsigned Byte - Immediate pre indexed */
static bool try_store_LDR_M2_Imm_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t offset_12 = get_bits(bincode,11,0);
  if (!((((W == 0) || (n != d)) && (n != 15)))) return false;
  const uint32_t signed_offset_12 = (U ? offset_12 : -offset_12);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_LDR_M2_Imm_preInd_NC_ID;
  else
    instr->args.g0.id = SLV6_LDR_M2_Imm_preInd_ID;
  instr->args.g1.d = d;
  instr->args.g1.n = n;
  instr->args.g1.cond = cond;
  instr->args.g1.signed_offset_12 = signed_offset_12;
  return true;
}

/* A4.1.87
 * SMULL (S=1) */
static bool try_store_SMULL_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  bool S = get_bit(bincode,20);
  uint8_t dHi = get_bits(bincode,19,16);
  uint8_t dLo = get_bits(bincode,15,12);
  uint8_t s = get_bits(bincode,11,8);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((dHi != 15) && ((dLo != 15) && ((m != 15) && ((s != 15) && (dHi != dLo))))))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_SMULL_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_SMULL_S1_ID;
  instr->args.g16.dHi = dHi;
  instr->args.g16.dLo = dLo;
  instr->args.g16.m = m;
  instr->args.g16.s = s;
  instr->args.g16.cond = cond;
  return true;
}

/* A4.1.87
 * SMULL (S=0) */
static bool try_store_SMULL_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  bool S = get_bit(bincode,20);
  uint8_t dHi = get_bits(bincode,19,16);
  uint8_t dLo = get_bits(bincode,15,12);
  uint8_t s = get_bits(bincode,11,8);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((dHi != 15) && ((dLo != 15) && ((m != 15) && ((s != 15) && (dHi != dLo))))))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_SMULL_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_SMULL_S0_ID;
  instr->args.g16.dHi = dHi;
  instr->args.g16.dLo = dLo;
  instr->args.g16.m = m;
  instr->args.g16.s = s;
  instr->args.g16.cond = cond;
  return true;
}

/* A4.1.60--A5.1.9
 * RSB -- Data processing operands - Arithmetic shift right by immediate (S=1) */
static bool try_store_RSB_M1_ASRImm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_RSB_M1_ASRImm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_RSB_M1_ASRImm_S1_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.60--A5.1.9
 * RSB -- Data processing operands - Arithmetic shift right by immediate (S=0) */
static bool try_store_RSB_M1_ASRImm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_RSB_M1_ASRImm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_RSB_M1_ASRImm_S0_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.117--A5.1.4
 * TST -- Data processing operands - Register */
static bool try_store_TST_M1_Reg(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_TST_M1_Reg_NC_ID;
  else
    instr->args.g0.id = SLV6_TST_M1_Reg_ID;
  instr->args.g4.m = m;
  instr->args.g4.n = n;
  instr->args.g4.cond = cond;
  return true;
}

/* A4.1.18--A5.1.3
 * EOR -- Data processing operands - Immediate (S=1) */
static bool try_store_EOR_M1_Imm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_EOR_M1_Imm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_EOR_M1_Imm_S1_ID;
  instr->args.g3.d = d;
  instr->args.g3.n = n;
  instr->args.g3.rotate_imm = rotate_imm;
  instr->args.g3.cond = cond;
  instr->args.g3.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.18--A5.1.3
 * EOR -- Data processing operands - Immediate (S=0) */
static bool try_store_EOR_M1_Imm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_EOR_M1_Imm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_EOR_M1_Imm_S0_ID;
  instr->args.g3.d = d;
  instr->args.g3.n = n;
  instr->args.g3.rotate_imm = rotate_imm;
  instr->args.g3.cond = cond;
  instr->args.g3.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.42--A5.1.9
 * ORR -- Data processing operands - Arithmetic shift right by immediate (S=1) */
static bool try_store_ORR_M1_ASRImm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_ORR_M1_ASRImm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_ORR_M1_ASRImm_S1_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.42--A5.1.9
 * ORR -- Data processing operands - Arithmetic shift right by immediate (S=0) */
static bool try_store_ORR_M1_ASRImm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_ORR_M1_ASRImm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_ORR_M1_ASRImm_S0_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.42--A5.1.3
 * ORR -- Data processing operands - Immediate (S=1) */
static bool try_store_ORR_M1_Imm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_ORR_M1_Imm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_ORR_M1_Imm_S1_ID;
  instr->args.g3.d = d;
  instr->args.g3.n = n;
  instr->args.g3.rotate_imm = rotate_imm;
  instr->args.g3.cond = cond;
  instr->args.g3.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.42--A5.1.3
 * ORR -- Data processing operands - Immediate (S=0) */
static bool try_store_ORR_M1_Imm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_ORR_M1_Imm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_ORR_M1_Imm_S0_ID;
  instr->args.g3.d = d;
  instr->args.g3.n = n;
  instr->args.g3.rotate_imm = rotate_imm;
  instr->args.g3.cond = cond;
  instr->args.g3.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.106--A5.1.9
 * SUB -- Data processing operands - Arithmetic shift right by immediate (S=1) */
static bool try_store_SUB_M1_ASRImm_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_SUB_M1_ASRImm_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_SUB_M1_ASRImm_S1_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.106--A5.1.9
 * SUB -- Data processing operands - Arithmetic shift right by immediate (S=0) */
static bool try_store_SUB_M1_ASRImm_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_SUB_M1_ASRImm_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_SUB_M1_ASRImm_S0_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.35--A5.1.6
 * MOV -- Data processing operands - Logical shift left by register (S=1) */
static bool try_store_MOV_M1_LSLReg_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!((not_cpy_instr(bincode) && ((d != 15) && ((m != 15) && ((s != 15) && (n != 15))))))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_MOV_M1_LSLReg_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_MOV_M1_LSLReg_S1_ID;
  instr->args.g14.d = d;
  instr->args.g14.m = m;
  instr->args.g14.s = s;
  instr->args.g14.cond = cond;
  return true;
}

/* A4.1.35--A5.1.6
 * MOV -- Data processing operands - Logical shift left by register (S=0) */
static bool try_store_MOV_M1_LSLReg_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!((not_cpy_instr(bincode) && ((d != 15) && ((m != 15) && ((s != 15) && (n != 15))))))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_MOV_M1_LSLReg_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_MOV_M1_LSLReg_S0_ID;
  instr->args.g14.d = d;
  instr->args.g14.m = m;
  instr->args.g14.s = s;
  instr->args.g14.cond = cond;
  return true;
}

/* A4.1.40
 * MUL (S=1) */
static bool try_store_MUL_S1(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  bool S = get_bit(bincode,20);
  uint8_t d = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (s != 15))))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_MUL_S1_NC_ID;
  else
    instr->args.g0.id = SLV6_MUL_S1_ID;
  instr->args.g14.d = d;
  instr->args.g14.m = m;
  instr->args.g14.s = s;
  instr->args.g14.cond = cond;
  return true;
}

/* A4.1.40
 * MUL (S=0) */
static bool try_store_MUL_S0(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  bool S = get_bit(bincode,20);
  uint8_t d = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (s != 15))))) return false;
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_MUL_S0_NC_ID;
  else
    instr->args.g0.id = SLV6_MUL_S0_ID;
  instr->args.g14.d = d;
  instr->args.g14.m = m;
  instr->args.g14.s = s;
  instr->args.g14.cond = cond;
  return true;
}

/* A4.1.14--A5.1.3
 * CMN -- Data processing operands - Immediate */
static bool try_store_CMN_M1_Imm(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  if (cond==SLV6_AL)
    instr->args.g0.id = SLV6_CMN_M1_Imm_NC_ID;
  else
    instr->args.g0.id = SLV6_CMN_M1_Imm_ID;
  instr->args.g10.n = n;
  instr->args.g10.rotate_imm = rotate_imm;
  instr->args.g10.cond = cond;
  instr->args.g10.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.2--A5.1.3
 * ADC -- Data processing operands - Immediate */
static bool try_store_ADC_M1_Imm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  instr->args.g0.id = SLV6_ADC_M1_Imm_ID;
  instr->args.g17.S = S;
  instr->args.g17.d = d;
  instr->args.g17.n = n;
  instr->args.g17.rotate_imm = rotate_imm;
  instr->args.g17.cond = cond;
  instr->args.g17.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.2--A5.1.5
 * ADC -- Data processing operands - Logical shift left by immediate */
static bool try_store_ADC_M1_LSLImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  instr->args.g0.id = SLV6_ADC_M1_LSLImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.2--A5.1.6
 * ADC -- Data processing operands - Logical shift left by register */
static bool try_store_ADC_M1_LSLReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_ADC_M1_LSLReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.2--A5.1.7
 * ADC -- Data processing operands - Logical shift right by immediate */
static bool try_store_ADC_M1_LSRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_ADC_M1_LSRImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.2--A5.1.8
 * ADC -- Data processing operands - Logical shift right by register */
static bool try_store_ADC_M1_LSRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_ADC_M1_LSRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.2--A5.1.9
 * ADC -- Data processing operands - Arithmetic shift right by immediate */
static bool try_store_ADC_M1_ASRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_ADC_M1_ASRImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.2--A5.1.10
 * ADC -- Data processing operands - Arithmetic shift right by register */
static bool try_store_ADC_M1_ASRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_ADC_M1_ASRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.2--A5.1.11
 * ADC -- Data processing operands - Rotate right by immediate */
static bool try_store_ADC_M1_RRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  instr->args.g0.id = SLV6_ADC_M1_RRImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.2--A5.1.12
 * ADC -- Data processing operands - Rotate right by register */
static bool try_store_ADC_M1_RRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_ADC_M1_RRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.2--A5.1.13
 * ADC -- Data processing operands - Rotate right with extend */
static bool try_store_ADC_M1_RRE(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  instr->args.g0.id = SLV6_ADC_M1_RRE_ID;
  instr->args.g20.S = S;
  instr->args.g20.d = d;
  instr->args.g20.m = m;
  instr->args.g20.n = n;
  instr->args.g20.cond = cond;
  return true;
}

/* A4.1.3--A5.1.6
 * ADD -- Data processing operands - Logical shift left by register */
static bool try_store_ADD_M1_LSLReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_ADD_M1_LSLReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.3--A5.1.8
 * ADD -- Data processing operands - Logical shift right by register */
static bool try_store_ADD_M1_LSRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_ADD_M1_LSRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.3--A5.1.9
 * ADD -- Data processing operands - Arithmetic shift right by immediate */
static bool try_store_ADD_M1_ASRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_ADD_M1_ASRImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.3--A5.1.10
 * ADD -- Data processing operands - Arithmetic shift right by register */
static bool try_store_ADD_M1_ASRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_ADD_M1_ASRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.3--A5.1.12
 * ADD -- Data processing operands - Rotate right by register */
static bool try_store_ADD_M1_RRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_ADD_M1_RRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.3--A5.1.13
 * ADD -- Data processing operands - Rotate right with extend */
static bool try_store_ADD_M1_RRE(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  instr->args.g0.id = SLV6_ADD_M1_RRE_ID;
  instr->args.g20.S = S;
  instr->args.g20.d = d;
  instr->args.g20.m = m;
  instr->args.g20.n = n;
  instr->args.g20.cond = cond;
  return true;
}

/* A4.1.4--A5.1.5
 * AND -- Data processing operands - Logical shift left by immediate */
static bool try_store_AND_M1_LSLImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  instr->args.g0.id = SLV6_AND_M1_LSLImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.4--A5.1.6
 * AND -- Data processing operands - Logical shift left by register */
static bool try_store_AND_M1_LSLReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_AND_M1_LSLReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.4--A5.1.7
 * AND -- Data processing operands - Logical shift right by immediate */
static bool try_store_AND_M1_LSRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_AND_M1_LSRImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.4--A5.1.8
 * AND -- Data processing operands - Logical shift right by register */
static bool try_store_AND_M1_LSRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_AND_M1_LSRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.4--A5.1.9
 * AND -- Data processing operands - Arithmetic shift right by immediate */
static bool try_store_AND_M1_ASRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_AND_M1_ASRImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.4--A5.1.10
 * AND -- Data processing operands - Arithmetic shift right by register */
static bool try_store_AND_M1_ASRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_AND_M1_ASRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.4--A5.1.11
 * AND -- Data processing operands - Rotate right by immediate */
static bool try_store_AND_M1_RRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  instr->args.g0.id = SLV6_AND_M1_RRImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.4--A5.1.12
 * AND -- Data processing operands - Rotate right by register */
static bool try_store_AND_M1_RRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_AND_M1_RRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.4--A5.1.13
 * AND -- Data processing operands - Rotate right with extend */
static bool try_store_AND_M1_RRE(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  instr->args.g0.id = SLV6_AND_M1_RRE_ID;
  instr->args.g20.S = S;
  instr->args.g20.d = d;
  instr->args.g20.m = m;
  instr->args.g20.n = n;
  instr->args.g20.cond = cond;
  return true;
}

/* A4.1.6--A5.1.4
 * BIC -- Data processing operands - Register */
static bool try_store_BIC_M1_Reg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  instr->args.g0.id = SLV6_BIC_M1_Reg_ID;
  instr->args.g20.S = S;
  instr->args.g20.d = d;
  instr->args.g20.m = m;
  instr->args.g20.n = n;
  instr->args.g20.cond = cond;
  return true;
}

/* A4.1.6--A5.1.5
 * BIC -- Data processing operands - Logical shift left by immediate */
static bool try_store_BIC_M1_LSLImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  instr->args.g0.id = SLV6_BIC_M1_LSLImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.6--A5.1.6
 * BIC -- Data processing operands - Logical shift left by register */
static bool try_store_BIC_M1_LSLReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_BIC_M1_LSLReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.6--A5.1.7
 * BIC -- Data processing operands - Logical shift right by immediate */
static bool try_store_BIC_M1_LSRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_BIC_M1_LSRImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.6--A5.1.8
 * BIC -- Data processing operands - Logical shift right by register */
static bool try_store_BIC_M1_LSRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_BIC_M1_LSRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.6--A5.1.9
 * BIC -- Data processing operands - Arithmetic shift right by immediate */
static bool try_store_BIC_M1_ASRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_BIC_M1_ASRImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.6--A5.1.10
 * BIC -- Data processing operands - Arithmetic shift right by register */
static bool try_store_BIC_M1_ASRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_BIC_M1_ASRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.6--A5.1.11
 * BIC -- Data processing operands - Rotate right by immediate */
static bool try_store_BIC_M1_RRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  instr->args.g0.id = SLV6_BIC_M1_RRImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.6--A5.1.12
 * BIC -- Data processing operands - Rotate right by register */
static bool try_store_BIC_M1_RRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_BIC_M1_RRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.6--A5.1.13
 * BIC -- Data processing operands - Rotate right with extend */
static bool try_store_BIC_M1_RRE(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  instr->args.g0.id = SLV6_BIC_M1_RRE_ID;
  instr->args.g20.S = S;
  instr->args.g20.d = d;
  instr->args.g20.m = m;
  instr->args.g20.n = n;
  instr->args.g20.cond = cond;
  return true;
}

/* A4.1.7
 * BKPT */
static bool try_store_BKPT(struct SLv6_Instruction *instr, uint32_t bincode) {
  instr->args.g0.id = SLV6_BKPT_ID;
  return true;
}

/* A4.1.8
 * BLX (1) */
static bool try_store_BLX1(struct SLv6_Instruction *instr, uint32_t bincode) {
  uint32_t H = get_bit(bincode,24);
  uint32_t signed_immed_24 = get_bits(bincode,23,0);
  const uint32_t pc_offset_h = (SignExtend_30(signed_immed_24) << 2) + (H << 1);
  instr->args.g0.id = SLV6_BLX1_ID;
  instr->args.g21.pc_offset_h = pc_offset_h;
  return true;
}

/* A4.1.9
 * BLX (2) */
static bool try_store_BLX2(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  if (!((m != 15))) return false;
  instr->args.g0.id = SLV6_BLX2_ID;
  instr->args.g12.m = m;
  instr->args.g12.cond = cond;
  return true;
}

/* A4.1.11
 * BXJ */
static bool try_store_BXJ(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  if (!((m != 15))) return false;
  instr->args.g0.id = SLV6_BXJ_ID;
  instr->args.g12.m = m;
  instr->args.g12.cond = cond;
  return true;
}

/* A4.1.12
 * CDP */
static bool try_store_CDP(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t cp_num = get_bits(bincode,11,8);
  instr->args.g0.id = SLV6_CDP_ID;
  instr->args.g22.cp_num = cp_num;
  instr->args.g22.cond = cond;
  return true;
}

/* A4.1.13
 * CLZ */
static bool try_store_CLZ(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((m != 15) && (d != 15)))) return false;
  instr->args.g0.id = SLV6_CLZ_ID;
  instr->args.g7.d = d;
  instr->args.g7.m = m;
  instr->args.g7.cond = cond;
  return true;
}

/* A4.1.14--A5.1.5
 * CMN -- Data processing operands - Logical shift left by immediate */
static bool try_store_CMN_M1_LSLImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  instr->args.g0.id = SLV6_CMN_M1_LSLImm_ID;
  instr->args.g23.m = m;
  instr->args.g23.n = n;
  instr->args.g23.shift_imm = shift_imm;
  instr->args.g23.cond = cond;
  return true;
}

/* A4.1.14--A5.1.6
 * CMN -- Data processing operands - Logical shift left by register */
static bool try_store_CMN_M1_LSLReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_CMN_M1_LSLReg_ID;
  instr->args.g24.m = m;
  instr->args.g24.n = n;
  instr->args.g24.s = s;
  instr->args.g24.cond = cond;
  return true;
}

/* A4.1.14--A5.1.7
 * CMN -- Data processing operands - Logical shift right by immediate */
static bool try_store_CMN_M1_LSRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_CMN_M1_LSRImm_ID;
  instr->args.g23.m = m;
  instr->args.g23.n = n;
  instr->args.g23.shift_imm = shift_imm;
  instr->args.g23.cond = cond;
  return true;
}

/* A4.1.14--A5.1.8
 * CMN -- Data processing operands - Logical shift right by register */
static bool try_store_CMN_M1_LSRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_CMN_M1_LSRReg_ID;
  instr->args.g24.m = m;
  instr->args.g24.n = n;
  instr->args.g24.s = s;
  instr->args.g24.cond = cond;
  return true;
}

/* A4.1.14--A5.1.9
 * CMN -- Data processing operands - Arithmetic shift right by immediate */
static bool try_store_CMN_M1_ASRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_CMN_M1_ASRImm_ID;
  instr->args.g23.m = m;
  instr->args.g23.n = n;
  instr->args.g23.shift_imm = shift_imm;
  instr->args.g23.cond = cond;
  return true;
}

/* A4.1.14--A5.1.10
 * CMN -- Data processing operands - Arithmetic shift right by register */
static bool try_store_CMN_M1_ASRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_CMN_M1_ASRReg_ID;
  instr->args.g24.m = m;
  instr->args.g24.n = n;
  instr->args.g24.s = s;
  instr->args.g24.cond = cond;
  return true;
}

/* A4.1.14--A5.1.11
 * CMN -- Data processing operands - Rotate right by immediate */
static bool try_store_CMN_M1_RRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  instr->args.g0.id = SLV6_CMN_M1_RRImm_ID;
  instr->args.g23.m = m;
  instr->args.g23.n = n;
  instr->args.g23.shift_imm = shift_imm;
  instr->args.g23.cond = cond;
  return true;
}

/* A4.1.14--A5.1.12
 * CMN -- Data processing operands - Rotate right by register */
static bool try_store_CMN_M1_RRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_CMN_M1_RRReg_ID;
  instr->args.g24.m = m;
  instr->args.g24.n = n;
  instr->args.g24.s = s;
  instr->args.g24.cond = cond;
  return true;
}

/* A4.1.14--A5.1.13
 * CMN -- Data processing operands - Rotate right with extend */
static bool try_store_CMN_M1_RRE(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  instr->args.g0.id = SLV6_CMN_M1_RRE_ID;
  instr->args.g4.m = m;
  instr->args.g4.n = n;
  instr->args.g4.cond = cond;
  return true;
}

/* A4.1.15--A5.1.5
 * CMP -- Data processing operands - Logical shift left by immediate */
static bool try_store_CMP_M1_LSLImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  instr->args.g0.id = SLV6_CMP_M1_LSLImm_ID;
  instr->args.g23.m = m;
  instr->args.g23.n = n;
  instr->args.g23.shift_imm = shift_imm;
  instr->args.g23.cond = cond;
  return true;
}

/* A4.1.15--A5.1.6
 * CMP -- Data processing operands - Logical shift left by register */
static bool try_store_CMP_M1_LSLReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_CMP_M1_LSLReg_ID;
  instr->args.g24.m = m;
  instr->args.g24.n = n;
  instr->args.g24.s = s;
  instr->args.g24.cond = cond;
  return true;
}

/* A4.1.15--A5.1.7
 * CMP -- Data processing operands - Logical shift right by immediate */
static bool try_store_CMP_M1_LSRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_CMP_M1_LSRImm_ID;
  instr->args.g23.m = m;
  instr->args.g23.n = n;
  instr->args.g23.shift_imm = shift_imm;
  instr->args.g23.cond = cond;
  return true;
}

/* A4.1.15--A5.1.8
 * CMP -- Data processing operands - Logical shift right by register */
static bool try_store_CMP_M1_LSRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_CMP_M1_LSRReg_ID;
  instr->args.g24.m = m;
  instr->args.g24.n = n;
  instr->args.g24.s = s;
  instr->args.g24.cond = cond;
  return true;
}

/* A4.1.15--A5.1.9
 * CMP -- Data processing operands - Arithmetic shift right by immediate */
static bool try_store_CMP_M1_ASRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_CMP_M1_ASRImm_ID;
  instr->args.g23.m = m;
  instr->args.g23.n = n;
  instr->args.g23.shift_imm = shift_imm;
  instr->args.g23.cond = cond;
  return true;
}

/* A4.1.15--A5.1.10
 * CMP -- Data processing operands - Arithmetic shift right by register */
static bool try_store_CMP_M1_ASRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_CMP_M1_ASRReg_ID;
  instr->args.g24.m = m;
  instr->args.g24.n = n;
  instr->args.g24.s = s;
  instr->args.g24.cond = cond;
  return true;
}

/* A4.1.15--A5.1.11
 * CMP -- Data processing operands - Rotate right by immediate */
static bool try_store_CMP_M1_RRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  instr->args.g0.id = SLV6_CMP_M1_RRImm_ID;
  instr->args.g23.m = m;
  instr->args.g23.n = n;
  instr->args.g23.shift_imm = shift_imm;
  instr->args.g23.cond = cond;
  return true;
}

/* A4.1.15--A5.1.12
 * CMP -- Data processing operands - Rotate right by register */
static bool try_store_CMP_M1_RRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_CMP_M1_RRReg_ID;
  instr->args.g24.m = m;
  instr->args.g24.n = n;
  instr->args.g24.s = s;
  instr->args.g24.cond = cond;
  return true;
}

/* A4.1.15--A5.1.13
 * CMP -- Data processing operands - Rotate right with extend */
static bool try_store_CMP_M1_RRE(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  instr->args.g0.id = SLV6_CMP_M1_RRE_ID;
  instr->args.g4.m = m;
  instr->args.g4.n = n;
  instr->args.g4.cond = cond;
  return true;
}

/* A4.1.16
 * CPS */
static bool try_store_CPS(struct SLv6_Instruction *instr, uint32_t bincode) {
  uint8_t imod = get_bits(bincode,19,18);
  bool mmod = get_bit(bincode,17);
  bool A = get_bit(bincode,8);
  bool I = get_bit(bincode,7);
  bool F = get_bit(bincode,6);
  const uint32_t mode_tmp = get_bits(bincode,4,0);
  SLv6_Mode mode;
  if (!decode_mode(&mode,bincode)) return false;
  instr->args.g0.id = SLV6_CPS_ID;
  instr->args.g25.A = A;
  instr->args.g25.F = F;
  instr->args.g25.I = I;
  instr->args.g25.imod = imod;
  instr->args.g25.mmod = mmod;
  instr->args.g25.mode = mode;
  return true;
}

/* A4.1.18--A5.1.6
 * EOR -- Data processing operands - Logical shift left by register */
static bool try_store_EOR_M1_LSLReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_EOR_M1_LSLReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.18--A5.1.8
 * EOR -- Data processing operands - Logical shift right by register */
static bool try_store_EOR_M1_LSRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_EOR_M1_LSRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.18--A5.1.9
 * EOR -- Data processing operands - Arithmetic shift right by immediate */
static bool try_store_EOR_M1_ASRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_EOR_M1_ASRImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.18--A5.1.10
 * EOR -- Data processing operands - Arithmetic shift right by register */
static bool try_store_EOR_M1_ASRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_EOR_M1_ASRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.18--A5.1.12
 * EOR -- Data processing operands - Rotate right by register */
static bool try_store_EOR_M1_RRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_EOR_M1_RRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.18--A5.1.13
 * EOR -- Data processing operands - Rotate right with extend */
static bool try_store_EOR_M1_RRE(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  instr->args.g0.id = SLV6_EOR_M1_RRE_ID;
  instr->args.g20.S = S;
  instr->args.g20.d = d;
  instr->args.g20.m = m;
  instr->args.g20.n = n;
  instr->args.g20.cond = cond;
  return true;
}

/* A4.1.19--A5.5.2
 * LDC -- Load and Store Coprocessor - Immediate offset */
static bool try_store_LDC_M5_ImmOff(struct SLv6_Instruction *instr, uint32_t bincode) {
  instr->args.g0.id = SLV6_LDC_M5_ImmOff_ID;
  return true;
}

/* A4.1.19--A5.5.3
 * LDC -- Load and Store Coprocessor - Immediate pre indexed */
static bool try_store_LDC_M5_Imm_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  uint8_t n = get_bits(bincode,19,16);
  if (!((n != 15))) return false;
  instr->args.g0.id = SLV6_LDC_M5_Imm_preInd_ID;
  return true;
}

/* A4.1.19--A5.5.4
 * LDC -- Load and Store Coprocessor - Immediate post indexed */
static bool try_store_LDC_M5_Imm_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  uint8_t n = get_bits(bincode,19,16);
  if (!((n != 15))) return false;
  instr->args.g0.id = SLV6_LDC_M5_Imm_postInd_ID;
  return true;
}

/* A4.1.19--A5.5.5
 * LDC -- Load and Store Coprocessor - Unindexed */
static bool try_store_LDC_M5_U(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  if (!((U != 0))) return false;
  instr->args.g0.id = SLV6_LDC_M5_U_ID;
  return true;
}

/* A4.1.20--A5.4.4
 * LDM (1) -- Load and Store Multiple - Decrement after */
static bool try_store_LDM1_M4_DA(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!(((n != 15) && (register_list != 0)))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  instr->args.g0.id = SLV6_LDM1_M4_DA_ID;
  instr->args.g26.W = W;
  instr->args.g26.n = n;
  instr->args.g26.nb_reg_x4 = nb_reg_x4;
  instr->args.g26.cond = cond;
  instr->args.g26.register_list = register_list;
  return true;
}

/* A4.1.20--A5.4.5
 * LDM (1) -- Load and Store Multiple - Decrement before */
static bool try_store_LDM1_M4_DB(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!(((n != 15) && (register_list != 0)))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  instr->args.g0.id = SLV6_LDM1_M4_DB_ID;
  instr->args.g26.W = W;
  instr->args.g26.n = n;
  instr->args.g26.nb_reg_x4 = nb_reg_x4;
  instr->args.g26.cond = cond;
  instr->args.g26.register_list = register_list;
  return true;
}

/* A4.1.21--A5.4.2
 * LDM (2) -- Load and Store Multiple - Increment after */
static bool try_store_LDM2_M4_IA(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!(((n != 15) && (register_list != 0)))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  instr->args.g0.id = SLV6_LDM2_M4_IA_ID;
  instr->args.g9.n = n;
  instr->args.g9.nb_reg_x4 = nb_reg_x4;
  instr->args.g9.cond = cond;
  instr->args.g9.register_list = register_list;
  return true;
}

/* A4.1.21--A5.4.3
 * LDM (2) -- Load and Store Multiple - Increment before */
static bool try_store_LDM2_M4_IB(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!(((n != 15) && (register_list != 0)))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  instr->args.g0.id = SLV6_LDM2_M4_IB_ID;
  instr->args.g9.n = n;
  instr->args.g9.nb_reg_x4 = nb_reg_x4;
  instr->args.g9.cond = cond;
  instr->args.g9.register_list = register_list;
  return true;
}

/* A4.1.21--A5.4.4
 * LDM (2) -- Load and Store Multiple - Decrement after */
static bool try_store_LDM2_M4_DA(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!(((n != 15) && (register_list != 0)))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  instr->args.g0.id = SLV6_LDM2_M4_DA_ID;
  instr->args.g9.n = n;
  instr->args.g9.nb_reg_x4 = nb_reg_x4;
  instr->args.g9.cond = cond;
  instr->args.g9.register_list = register_list;
  return true;
}

/* A4.1.21--A5.4.5
 * LDM (2) -- Load and Store Multiple - Decrement before */
static bool try_store_LDM2_M4_DB(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!(((n != 15) && (register_list != 0)))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  instr->args.g0.id = SLV6_LDM2_M4_DB_ID;
  instr->args.g9.n = n;
  instr->args.g9.nb_reg_x4 = nb_reg_x4;
  instr->args.g9.cond = cond;
  instr->args.g9.register_list = register_list;
  return true;
}

/* A4.1.22--A5.4.2
 * LDM (3) -- Load and Store Multiple - Increment after */
static bool try_store_LDM3_M4_IA(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!((n != 15))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  instr->args.g0.id = SLV6_LDM3_M4_IA_ID;
  instr->args.g26.W = W;
  instr->args.g26.n = n;
  instr->args.g26.nb_reg_x4 = nb_reg_x4;
  instr->args.g26.cond = cond;
  instr->args.g26.register_list = register_list;
  return true;
}

/* A4.1.22--A5.4.3
 * LDM (3) -- Load and Store Multiple - Increment before */
static bool try_store_LDM3_M4_IB(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!((n != 15))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  instr->args.g0.id = SLV6_LDM3_M4_IB_ID;
  instr->args.g26.W = W;
  instr->args.g26.n = n;
  instr->args.g26.nb_reg_x4 = nb_reg_x4;
  instr->args.g26.cond = cond;
  instr->args.g26.register_list = register_list;
  return true;
}

/* A4.1.22--A5.4.4
 * LDM (3) -- Load and Store Multiple - Decrement after */
static bool try_store_LDM3_M4_DA(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!((n != 15))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  instr->args.g0.id = SLV6_LDM3_M4_DA_ID;
  instr->args.g26.W = W;
  instr->args.g26.n = n;
  instr->args.g26.nb_reg_x4 = nb_reg_x4;
  instr->args.g26.cond = cond;
  instr->args.g26.register_list = register_list;
  return true;
}

/* A4.1.22--A5.4.5
 * LDM (3) -- Load and Store Multiple - Decrement before */
static bool try_store_LDM3_M4_DB(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!((n != 15))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  instr->args.g0.id = SLV6_LDM3_M4_DB_ID;
  instr->args.g26.W = W;
  instr->args.g26.n = n;
  instr->args.g26.nb_reg_x4 = nb_reg_x4;
  instr->args.g26.cond = cond;
  instr->args.g26.register_list = register_list;
  return true;
}

/* A4.1.23--A5.2.6
 * LDR -- Load and Store Word or Unsigned Byte - Register pre indexed */
static bool try_store_LDR_M2_Reg_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!((((W == 0) || (n != d)) && ((n != 15) && (m != 15))))) return false;
  instr->args.g0.id = SLV6_LDR_M2_Reg_preInd_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.23--A5.2.7
 * LDR -- Load and Store Word or Unsigned Byte - Scaled register pre indexed */
static bool try_store_LDR_M2_ScReg_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift = get_bits(bincode,6,5);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((((W == 0) || (n != d)) && ((n != 15) && ((m != 15) && ((shift != 0) || (shift_imm != 0))))))) return false;
  instr->args.g0.id = SLV6_LDR_M2_ScReg_preInd_ID;
  instr->args.g28.U = U;
  instr->args.g28.d = d;
  instr->args.g28.m = m;
  instr->args.g28.n = n;
  instr->args.g28.shift = shift;
  instr->args.g28.shift_imm = shift_imm;
  instr->args.g28.cond = cond;
  return true;
}

/* A4.1.23--A5.2.9
 * LDR -- Load and Store Word or Unsigned Byte - Register post indexed */
static bool try_store_LDR_M2_Reg_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!((((W == 0) || (n != d)) && ((n != 15) && (m != 15))))) return false;
  instr->args.g0.id = SLV6_LDR_M2_Reg_postInd_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.23--A5.2.10
 * LDR -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
static bool try_store_LDR_M2_ScReg_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift = get_bits(bincode,6,5);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((((W == 0) || (n != d)) && ((n != 15) && ((m != 15) && ((shift != 0) || (shift_imm != 0))))))) return false;
  instr->args.g0.id = SLV6_LDR_M2_ScReg_postInd_ID;
  instr->args.g28.U = U;
  instr->args.g28.d = d;
  instr->args.g28.m = m;
  instr->args.g28.n = n;
  instr->args.g28.shift = shift;
  instr->args.g28.shift_imm = shift_imm;
  instr->args.g28.cond = cond;
  return true;
}

/* A4.1.24--A5.2.5
 * LDRB -- Load and Store Word or Unsigned Byte - Immediate pre indexed */
static bool try_store_LDRB_M2_Imm_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t offset_12 = get_bits(bincode,11,0);
  if (!(((d != 15) && (((W == 0) || (n != d)) && (n != 15))))) return false;
  const uint32_t signed_offset_12 = (U ? offset_12 : -offset_12);
  instr->args.g0.id = SLV6_LDRB_M2_Imm_preInd_ID;
  instr->args.g1.d = d;
  instr->args.g1.n = n;
  instr->args.g1.cond = cond;
  instr->args.g1.signed_offset_12 = signed_offset_12;
  return true;
}

/* A4.1.24--A5.2.6
 * LDRB -- Load and Store Word or Unsigned Byte - Register pre indexed */
static bool try_store_LDRB_M2_Reg_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && (((W == 0) || (n != d)) && ((n != 15) && (m != 15)))))) return false;
  instr->args.g0.id = SLV6_LDRB_M2_Reg_preInd_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.24--A5.2.7
 * LDRB -- Load and Store Word or Unsigned Byte - Scaled register pre indexed */
static bool try_store_LDRB_M2_ScReg_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift = get_bits(bincode,6,5);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!(((d != 15) && (((W == 0) || (n != d)) && ((n != 15) && ((m != 15) && ((shift != 0) || (shift_imm != 0)))))))) return false;
  instr->args.g0.id = SLV6_LDRB_M2_ScReg_preInd_ID;
  instr->args.g28.U = U;
  instr->args.g28.d = d;
  instr->args.g28.m = m;
  instr->args.g28.n = n;
  instr->args.g28.shift = shift;
  instr->args.g28.shift_imm = shift_imm;
  instr->args.g28.cond = cond;
  return true;
}

/* A4.1.24--A5.2.8
 * LDRB -- Load and Store Word or Unsigned Byte - Immediate post indexed */
static bool try_store_LDRB_M2_Imm_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t offset_12 = get_bits(bincode,11,0);
  if (!(((d != 15) && (((W == 0) || (n != d)) && (n != 15))))) return false;
  const uint32_t signed_offset_12 = (U ? offset_12 : -offset_12);
  instr->args.g0.id = SLV6_LDRB_M2_Imm_postInd_ID;
  instr->args.g1.d = d;
  instr->args.g1.n = n;
  instr->args.g1.cond = cond;
  instr->args.g1.signed_offset_12 = signed_offset_12;
  return true;
}

/* A4.1.24--A5.2.9
 * LDRB -- Load and Store Word or Unsigned Byte - Register post indexed */
static bool try_store_LDRB_M2_Reg_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && (((W == 0) || (n != d)) && ((n != 15) && (m != 15)))))) return false;
  instr->args.g0.id = SLV6_LDRB_M2_Reg_postInd_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.24--A5.2.10
 * LDRB -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
static bool try_store_LDRB_M2_ScReg_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift = get_bits(bincode,6,5);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!(((d != 15) && (((W == 0) || (n != d)) && ((n != 15) && ((m != 15) && ((shift != 0) || (shift_imm != 0)))))))) return false;
  instr->args.g0.id = SLV6_LDRB_M2_ScReg_postInd_ID;
  instr->args.g28.U = U;
  instr->args.g28.d = d;
  instr->args.g28.m = m;
  instr->args.g28.n = n;
  instr->args.g28.shift = shift;
  instr->args.g28.shift_imm = shift_imm;
  instr->args.g28.cond = cond;
  return true;
}

/* A4.1.25--A5.2.8
 * LDRBT -- Load and Store Word or Unsigned Byte - Immediate post indexed */
static bool try_store_LDRBT_M2_Imm_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t offset_12 = get_bits(bincode,11,0);
  if (!(((d != 15) && ((d != n) && (n != 15))))) return false;
  const uint32_t signed_offset_12 = (U ? offset_12 : -offset_12);
  instr->args.g0.id = SLV6_LDRBT_M2_Imm_postInd_ID;
  instr->args.g1.d = d;
  instr->args.g1.n = n;
  instr->args.g1.cond = cond;
  instr->args.g1.signed_offset_12 = signed_offset_12;
  return true;
}

/* A4.1.25--A5.2.9
 * LDRBT -- Load and Store Word or Unsigned Byte - Register post indexed */
static bool try_store_LDRBT_M2_Reg_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && ((d != n) && ((n != 15) && (m != 15)))))) return false;
  instr->args.g0.id = SLV6_LDRBT_M2_Reg_postInd_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.25--A5.2.10
 * LDRBT -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
static bool try_store_LDRBT_M2_ScReg_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift = get_bits(bincode,6,5);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!(((d != 15) && ((d != n) && ((n != 15) && ((m != 15) && ((shift != 0) || (shift_imm != 0)))))))) return false;
  instr->args.g0.id = SLV6_LDRBT_M2_ScReg_postInd_ID;
  instr->args.g28.U = U;
  instr->args.g28.d = d;
  instr->args.g28.m = m;
  instr->args.g28.n = n;
  instr->args.g28.shift = shift;
  instr->args.g28.shift_imm = shift_imm;
  instr->args.g28.cond = cond;
  return true;
}

/* A4.1.26--A5.3.2
 * LDRD -- Miscellaneous Loads and Stores - Immediate offset */
static bool try_store_LDRD_M3_ImmOff(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immedH = get_bits(bincode,11,8);
  uint8_t immedL = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && ((d != 14) && is_even(d))))) return false;
  const uint8_t immedHL = (immedH << 4) | immedL;
  instr->args.g0.id = SLV6_LDRD_M3_ImmOff_ID;
  instr->args.g29.U = U;
  instr->args.g29.d = d;
  instr->args.g29.n = n;
  instr->args.g29.immedHL = immedHL;
  instr->args.g29.cond = cond;
  return true;
}

/* A4.1.26--A5.3.3
 * LDRD -- Miscellaneous Loads and Stores - Register offset */
static bool try_store_LDRD_M3_RegOff(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && ((d != 14) && (is_even(d) && (m != 15)))))) return false;
  instr->args.g0.id = SLV6_LDRD_M3_RegOff_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.26--A5.3.4
 * LDRD -- Miscellaneous Loads and Stores - Immediate pre indexed */
static bool try_store_LDRD_M3_Imm_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immedH = get_bits(bincode,11,8);
  uint8_t immedL = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && ((d != 14) && (is_even(d) && (n != 15)))))) return false;
  const uint8_t immedHL = (immedH << 4) | immedL;
  instr->args.g0.id = SLV6_LDRD_M3_Imm_preInd_ID;
  instr->args.g29.U = U;
  instr->args.g29.d = d;
  instr->args.g29.n = n;
  instr->args.g29.immedHL = immedHL;
  instr->args.g29.cond = cond;
  return true;
}

/* A4.1.26--A5.3.5
 * LDRD -- Miscellaneous Loads and Stores - Register pre indexed */
static bool try_store_LDRD_M3_Reg_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && ((d != 14) && (is_even(d) && ((n != 15) && (m != 15))))))) return false;
  instr->args.g0.id = SLV6_LDRD_M3_Reg_preInd_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.26--A5.3.6
 * LDRD -- Miscellaneous Loads and Stores - Immediate post indexed */
static bool try_store_LDRD_M3_Imm_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immedH = get_bits(bincode,11,8);
  uint8_t immedL = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && ((d != 14) && is_even(d))))) return false;
  const uint8_t immedHL = (immedH << 4) | immedL;
  instr->args.g0.id = SLV6_LDRD_M3_Imm_postInd_ID;
  instr->args.g29.U = U;
  instr->args.g29.d = d;
  instr->args.g29.n = n;
  instr->args.g29.immedHL = immedHL;
  instr->args.g29.cond = cond;
  return true;
}

/* A4.1.26--A5.3.7
 * LDRD -- Miscellaneous Loads and Stores - Register post indexed */
static bool try_store_LDRD_M3_Reg_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && ((d != 14) && is_even(d))))) return false;
  instr->args.g0.id = SLV6_LDRD_M3_Reg_postInd_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.27
 * LDREX */
static bool try_store_LDREX(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  if (!(((d != 15) && (n != 15)))) return false;
  instr->args.g0.id = SLV6_LDREX_ID;
  instr->args.g30.d = d;
  instr->args.g30.n = n;
  instr->args.g30.cond = cond;
  return true;
}

/* A4.1.28--A5.3.3
 * LDRH -- Miscellaneous Loads and Stores - Register offset */
static bool try_store_LDRH_M3_RegOff(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && (((W == 0) || (n != d)) && (m != 15))))) return false;
  instr->args.g0.id = SLV6_LDRH_M3_RegOff_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.28--A5.3.4
 * LDRH -- Miscellaneous Loads and Stores - Immediate pre indexed */
static bool try_store_LDRH_M3_Imm_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immedH = get_bits(bincode,11,8);
  uint8_t immedL = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && (((W == 0) || (n != d)) && (n != 15))))) return false;
  const uint8_t immedHL = (immedH << 4) | immedL;
  instr->args.g0.id = SLV6_LDRH_M3_Imm_preInd_ID;
  instr->args.g29.U = U;
  instr->args.g29.d = d;
  instr->args.g29.n = n;
  instr->args.g29.immedHL = immedHL;
  instr->args.g29.cond = cond;
  return true;
}

/* A4.1.28--A5.3.5
 * LDRH -- Miscellaneous Loads and Stores - Register pre indexed */
static bool try_store_LDRH_M3_Reg_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && (((W == 0) || (n != d)) && ((n != 15) && (m != 15)))))) return false;
  instr->args.g0.id = SLV6_LDRH_M3_Reg_preInd_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.28--A5.3.6
 * LDRH -- Miscellaneous Loads and Stores - Immediate post indexed */
static bool try_store_LDRH_M3_Imm_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immedH = get_bits(bincode,11,8);
  uint8_t immedL = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && ((W == 0) || (n != d))))) return false;
  const uint8_t immedHL = (immedH << 4) | immedL;
  instr->args.g0.id = SLV6_LDRH_M3_Imm_postInd_ID;
  instr->args.g29.U = U;
  instr->args.g29.d = d;
  instr->args.g29.n = n;
  instr->args.g29.immedHL = immedHL;
  instr->args.g29.cond = cond;
  return true;
}

/* A4.1.28--A5.3.7
 * LDRH -- Miscellaneous Loads and Stores - Register post indexed */
static bool try_store_LDRH_M3_Reg_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && ((W == 0) || (n != d))))) return false;
  instr->args.g0.id = SLV6_LDRH_M3_Reg_postInd_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.29--A5.3.2
 * LDRSB -- Miscellaneous Loads and Stores - Immediate offset */
static bool try_store_LDRSB_M3_ImmOff(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immedH = get_bits(bincode,11,8);
  uint8_t immedL = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && ((W == 0) || (n != d))))) return false;
  const uint8_t immedHL = (immedH << 4) | immedL;
  instr->args.g0.id = SLV6_LDRSB_M3_ImmOff_ID;
  instr->args.g29.U = U;
  instr->args.g29.d = d;
  instr->args.g29.n = n;
  instr->args.g29.immedHL = immedHL;
  instr->args.g29.cond = cond;
  return true;
}

/* A4.1.29--A5.3.3
 * LDRSB -- Miscellaneous Loads and Stores - Register offset */
static bool try_store_LDRSB_M3_RegOff(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && (((W == 0) || (n != d)) && (m != 15))))) return false;
  instr->args.g0.id = SLV6_LDRSB_M3_RegOff_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.29--A5.3.4
 * LDRSB -- Miscellaneous Loads and Stores - Immediate pre indexed */
static bool try_store_LDRSB_M3_Imm_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immedH = get_bits(bincode,11,8);
  uint8_t immedL = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && (((W == 0) || (n != d)) && (n != 15))))) return false;
  const uint8_t immedHL = (immedH << 4) | immedL;
  instr->args.g0.id = SLV6_LDRSB_M3_Imm_preInd_ID;
  instr->args.g29.U = U;
  instr->args.g29.d = d;
  instr->args.g29.n = n;
  instr->args.g29.immedHL = immedHL;
  instr->args.g29.cond = cond;
  return true;
}

/* A4.1.29--A5.3.5
 * LDRSB -- Miscellaneous Loads and Stores - Register pre indexed */
static bool try_store_LDRSB_M3_Reg_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && (((W == 0) || (n != d)) && ((n != 15) && (m != 15)))))) return false;
  instr->args.g0.id = SLV6_LDRSB_M3_Reg_preInd_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.29--A5.3.6
 * LDRSB -- Miscellaneous Loads and Stores - Immediate post indexed */
static bool try_store_LDRSB_M3_Imm_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immedH = get_bits(bincode,11,8);
  uint8_t immedL = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && ((W == 0) || (n != d))))) return false;
  const uint8_t immedHL = (immedH << 4) | immedL;
  instr->args.g0.id = SLV6_LDRSB_M3_Imm_postInd_ID;
  instr->args.g29.U = U;
  instr->args.g29.d = d;
  instr->args.g29.n = n;
  instr->args.g29.immedHL = immedHL;
  instr->args.g29.cond = cond;
  return true;
}

/* A4.1.29--A5.3.7
 * LDRSB -- Miscellaneous Loads and Stores - Register post indexed */
static bool try_store_LDRSB_M3_Reg_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && ((W == 0) || (n != d))))) return false;
  instr->args.g0.id = SLV6_LDRSB_M3_Reg_postInd_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.30--A5.3.2
 * LDRSH -- Miscellaneous Loads and Stores - Immediate offset */
static bool try_store_LDRSH_M3_ImmOff(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immedH = get_bits(bincode,11,8);
  uint8_t immedL = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && ((W == 0) || (n != d))))) return false;
  const uint8_t immedHL = (immedH << 4) | immedL;
  instr->args.g0.id = SLV6_LDRSH_M3_ImmOff_ID;
  instr->args.g29.U = U;
  instr->args.g29.d = d;
  instr->args.g29.n = n;
  instr->args.g29.immedHL = immedHL;
  instr->args.g29.cond = cond;
  return true;
}

/* A4.1.30--A5.3.3
 * LDRSH -- Miscellaneous Loads and Stores - Register offset */
static bool try_store_LDRSH_M3_RegOff(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && (((W == 0) || (n != d)) && (m != 15))))) return false;
  instr->args.g0.id = SLV6_LDRSH_M3_RegOff_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.30--A5.3.4
 * LDRSH -- Miscellaneous Loads and Stores - Immediate pre indexed */
static bool try_store_LDRSH_M3_Imm_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immedH = get_bits(bincode,11,8);
  uint8_t immedL = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && (((W == 0) || (n != d)) && (n != 15))))) return false;
  const uint8_t immedHL = (immedH << 4) | immedL;
  instr->args.g0.id = SLV6_LDRSH_M3_Imm_preInd_ID;
  instr->args.g29.U = U;
  instr->args.g29.d = d;
  instr->args.g29.n = n;
  instr->args.g29.immedHL = immedHL;
  instr->args.g29.cond = cond;
  return true;
}

/* A4.1.30--A5.3.5
 * LDRSH -- Miscellaneous Loads and Stores - Register pre indexed */
static bool try_store_LDRSH_M3_Reg_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && (((W == 0) || (n != d)) && ((n != 15) && (m != 15)))))) return false;
  instr->args.g0.id = SLV6_LDRSH_M3_Reg_preInd_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.30--A5.3.6
 * LDRSH -- Miscellaneous Loads and Stores - Immediate post indexed */
static bool try_store_LDRSH_M3_Imm_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immedH = get_bits(bincode,11,8);
  uint8_t immedL = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && ((W == 0) || (n != d))))) return false;
  const uint8_t immedHL = (immedH << 4) | immedL;
  instr->args.g0.id = SLV6_LDRSH_M3_Imm_postInd_ID;
  instr->args.g29.U = U;
  instr->args.g29.d = d;
  instr->args.g29.n = n;
  instr->args.g29.immedHL = immedHL;
  instr->args.g29.cond = cond;
  return true;
}

/* A4.1.30--A5.3.7
 * LDRSH -- Miscellaneous Loads and Stores - Register post indexed */
static bool try_store_LDRSH_M3_Reg_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && ((W == 0) || (n != d))))) return false;
  instr->args.g0.id = SLV6_LDRSH_M3_Reg_postInd_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.31--A5.2.8
 * LDRT -- Load and Store Word or Unsigned Byte - Immediate post indexed */
static bool try_store_LDRT_M2_Imm_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t offset_12 = get_bits(bincode,11,0);
  if (!(((d != 15) && ((d != n) && (n != 15))))) return false;
  const uint32_t signed_offset_12 = (U ? offset_12 : -offset_12);
  instr->args.g0.id = SLV6_LDRT_M2_Imm_postInd_ID;
  instr->args.g1.d = d;
  instr->args.g1.n = n;
  instr->args.g1.cond = cond;
  instr->args.g1.signed_offset_12 = signed_offset_12;
  return true;
}

/* A4.1.31--A5.2.9
 * LDRT -- Load and Store Word or Unsigned Byte - Register post indexed */
static bool try_store_LDRT_M2_Reg_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && ((d != n) && ((n != 15) && (m != 15)))))) return false;
  instr->args.g0.id = SLV6_LDRT_M2_Reg_postInd_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.31--A5.2.10
 * LDRT -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
static bool try_store_LDRT_M2_ScReg_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift = get_bits(bincode,6,5);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!(((d != 15) && ((d != n) && ((n != 15) && ((m != 15) && ((shift != 0) || (shift_imm != 0)))))))) return false;
  instr->args.g0.id = SLV6_LDRT_M2_ScReg_postInd_ID;
  instr->args.g28.U = U;
  instr->args.g28.d = d;
  instr->args.g28.m = m;
  instr->args.g28.n = n;
  instr->args.g28.shift = shift;
  instr->args.g28.shift_imm = shift_imm;
  instr->args.g28.cond = cond;
  return true;
}

/* A4.1.32
 * MCR */
static bool try_store_MCR(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t opcode_1 = get_bits(bincode,23,21);
  uint8_t CRn = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t cp_num = get_bits(bincode,11,8);
  uint8_t opcode_2 = get_bits(bincode,7,5);
  uint8_t CRm = get_bits(bincode,3,0);
  if (!((d != 15))) return false;
  instr->args.g0.id = SLV6_MCR_ID;
  instr->args.g31.CRm = CRm;
  instr->args.g31.CRn = CRn;
  instr->args.g31.cp_num = cp_num;
  instr->args.g31.d = d;
  instr->args.g31.opcode_1 = opcode_1;
  instr->args.g31.opcode_2 = opcode_2;
  instr->args.g31.cond = cond;
  return true;
}

/* A4.1.33
 * MCRR */
static bool try_store_MCRR(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t cp_num = get_bits(bincode,11,8);
  if (!(((d != 15) && ((n != 15) && (d != n))))) return false;
  instr->args.g0.id = SLV6_MCRR_ID;
  instr->args.g32.cp_num = cp_num;
  instr->args.g32.d = d;
  instr->args.g32.n = n;
  instr->args.g32.cond = cond;
  return true;
}

/* A4.1.34
 * MLA */
static bool try_store_MLA(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  bool S = get_bit(bincode,20);
  uint8_t d = get_bits(bincode,19,16);
  uint8_t n = get_bits(bincode,15,12);
  uint8_t s = get_bits(bincode,11,8);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_MLA_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.35--A5.1.4
 * MOV -- Data processing operands - Register */
static bool try_store_MOV_M1_Reg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(not_cpy_instr(bincode))) return false;
  instr->args.g0.id = SLV6_MOV_M1_Reg_ID;
  instr->args.g33.S = S;
  instr->args.g33.d = d;
  instr->args.g33.m = m;
  instr->args.g33.cond = cond;
  return true;
}

/* A4.1.35--A5.1.10
 * MOV -- Data processing operands - Arithmetic shift right by register */
static bool try_store_MOV_M1_ASRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!((not_cpy_instr(bincode) && ((d != 15) && ((m != 15) && ((s != 15) && (n != 15))))))) return false;
  instr->args.g0.id = SLV6_MOV_M1_ASRReg_ID;
  instr->args.g34.S = S;
  instr->args.g34.d = d;
  instr->args.g34.m = m;
  instr->args.g34.s = s;
  instr->args.g34.cond = cond;
  return true;
}

/* A4.1.35--A5.1.12
 * MOV -- Data processing operands - Rotate right by register */
static bool try_store_MOV_M1_RRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!((not_cpy_instr(bincode) && ((d != 15) && ((m != 15) && ((s != 15) && (n != 15))))))) return false;
  instr->args.g0.id = SLV6_MOV_M1_RRReg_ID;
  instr->args.g34.S = S;
  instr->args.g34.d = d;
  instr->args.g34.m = m;
  instr->args.g34.s = s;
  instr->args.g34.cond = cond;
  return true;
}

/* A4.1.35--A5.1.13
 * MOV -- Data processing operands - Rotate right with extend */
static bool try_store_MOV_M1_RRE(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(not_cpy_instr(bincode))) return false;
  instr->args.g0.id = SLV6_MOV_M1_RRE_ID;
  instr->args.g33.S = S;
  instr->args.g33.d = d;
  instr->args.g33.m = m;
  instr->args.g33.cond = cond;
  return true;
}

/* A4.1.36
 * MRC */
static bool try_store_MRC(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t opcode_1 = get_bits(bincode,23,21);
  uint8_t CRn = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t cp_num = get_bits(bincode,11,8);
  uint8_t opcode_2 = get_bits(bincode,7,5);
  uint8_t CRm = get_bits(bincode,3,0);
  instr->args.g0.id = SLV6_MRC_ID;
  instr->args.g31.CRm = CRm;
  instr->args.g31.CRn = CRn;
  instr->args.g31.cp_num = cp_num;
  instr->args.g31.d = d;
  instr->args.g31.opcode_1 = opcode_1;
  instr->args.g31.opcode_2 = opcode_2;
  instr->args.g31.cond = cond;
  return true;
}

/* A4.1.37
 * MRRC */
static bool try_store_MRRC(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t cp_num = get_bits(bincode,11,8);
  if (!(((d != 15) && ((n != 15) && (d != n))))) return false;
  instr->args.g0.id = SLV6_MRRC_ID;
  instr->args.g32.cp_num = cp_num;
  instr->args.g32.d = d;
  instr->args.g32.n = n;
  instr->args.g32.cond = cond;
  return true;
}

/* A4.1.38
 * MRS */
static bool try_store_MRS(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  bool R = get_bit(bincode,22);
  uint8_t d = get_bits(bincode,15,12);
  if (!((d != 15))) return false;
  instr->args.g0.id = SLV6_MRS_ID;
  instr->args.g35.R = R;
  instr->args.g35.d = d;
  instr->args.g35.cond = cond;
  return true;
}

/* A4.1.39
 * MSRimm */
static bool try_store_MSRimm(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  bool R = get_bit(bincode,22);
  uint8_t field_mask = get_bits(bincode,19,16);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  uint8_t immed_8 = get_bits(bincode,7,0);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  instr->args.g0.id = SLV6_MSRimm_ID;
  instr->args.g36.R = R;
  instr->args.g36.field_mask = field_mask;
  instr->args.g36.rotate_imm = rotate_imm;
  instr->args.g36.cond = cond;
  instr->args.g36.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.39
 * MSRreg */
static bool try_store_MSRreg(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  bool R = get_bit(bincode,22);
  uint8_t field_mask = get_bits(bincode,19,16);
  uint8_t m = get_bits(bincode,3,0);
  instr->args.g0.id = SLV6_MSRreg_ID;
  instr->args.g37.R = R;
  instr->args.g37.field_mask = field_mask;
  instr->args.g37.m = m;
  instr->args.g37.cond = cond;
  return true;
}

/* A4.1.41--A5.1.5
 * MVN -- Data processing operands - Logical shift left by immediate */
static bool try_store_MVN_M1_LSLImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  instr->args.g0.id = SLV6_MVN_M1_LSLImm_ID;
  instr->args.g38.S = S;
  instr->args.g38.d = d;
  instr->args.g38.m = m;
  instr->args.g38.shift_imm = shift_imm;
  instr->args.g38.cond = cond;
  return true;
}

/* A4.1.41--A5.1.6
 * MVN -- Data processing operands - Logical shift left by register */
static bool try_store_MVN_M1_LSLReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_MVN_M1_LSLReg_ID;
  instr->args.g34.S = S;
  instr->args.g34.d = d;
  instr->args.g34.m = m;
  instr->args.g34.s = s;
  instr->args.g34.cond = cond;
  return true;
}

/* A4.1.41--A5.1.7
 * MVN -- Data processing operands - Logical shift right by immediate */
static bool try_store_MVN_M1_LSRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_MVN_M1_LSRImm_ID;
  instr->args.g38.S = S;
  instr->args.g38.d = d;
  instr->args.g38.m = m;
  instr->args.g38.shift_imm = shift_imm;
  instr->args.g38.cond = cond;
  return true;
}

/* A4.1.41--A5.1.8
 * MVN -- Data processing operands - Logical shift right by register */
static bool try_store_MVN_M1_LSRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_MVN_M1_LSRReg_ID;
  instr->args.g34.S = S;
  instr->args.g34.d = d;
  instr->args.g34.m = m;
  instr->args.g34.s = s;
  instr->args.g34.cond = cond;
  return true;
}

/* A4.1.41--A5.1.9
 * MVN -- Data processing operands - Arithmetic shift right by immediate */
static bool try_store_MVN_M1_ASRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_MVN_M1_ASRImm_ID;
  instr->args.g38.S = S;
  instr->args.g38.d = d;
  instr->args.g38.m = m;
  instr->args.g38.shift_imm = shift_imm;
  instr->args.g38.cond = cond;
  return true;
}

/* A4.1.41--A5.1.10
 * MVN -- Data processing operands - Arithmetic shift right by register */
static bool try_store_MVN_M1_ASRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_MVN_M1_ASRReg_ID;
  instr->args.g34.S = S;
  instr->args.g34.d = d;
  instr->args.g34.m = m;
  instr->args.g34.s = s;
  instr->args.g34.cond = cond;
  return true;
}

/* A4.1.41--A5.1.11
 * MVN -- Data processing operands - Rotate right by immediate */
static bool try_store_MVN_M1_RRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  instr->args.g0.id = SLV6_MVN_M1_RRImm_ID;
  instr->args.g38.S = S;
  instr->args.g38.d = d;
  instr->args.g38.m = m;
  instr->args.g38.shift_imm = shift_imm;
  instr->args.g38.cond = cond;
  return true;
}

/* A4.1.41--A5.1.12
 * MVN -- Data processing operands - Rotate right by register */
static bool try_store_MVN_M1_RRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_MVN_M1_RRReg_ID;
  instr->args.g34.S = S;
  instr->args.g34.d = d;
  instr->args.g34.m = m;
  instr->args.g34.s = s;
  instr->args.g34.cond = cond;
  return true;
}

/* A4.1.41--A5.1.13
 * MVN -- Data processing operands - Rotate right with extend */
static bool try_store_MVN_M1_RRE(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  instr->args.g0.id = SLV6_MVN_M1_RRE_ID;
  instr->args.g33.S = S;
  instr->args.g33.d = d;
  instr->args.g33.m = m;
  instr->args.g33.cond = cond;
  return true;
}

/* A4.1.42--A5.1.6
 * ORR -- Data processing operands - Logical shift left by register */
static bool try_store_ORR_M1_LSLReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_ORR_M1_LSLReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.42--A5.1.8
 * ORR -- Data processing operands - Logical shift right by register */
static bool try_store_ORR_M1_LSRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_ORR_M1_LSRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.42--A5.1.10
 * ORR -- Data processing operands - Arithmetic shift right by register */
static bool try_store_ORR_M1_ASRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_ORR_M1_ASRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.42--A5.1.11
 * ORR -- Data processing operands - Rotate right by immediate */
static bool try_store_ORR_M1_RRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  instr->args.g0.id = SLV6_ORR_M1_RRImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.42--A5.1.12
 * ORR -- Data processing operands - Rotate right by register */
static bool try_store_ORR_M1_RRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_ORR_M1_RRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.42--A5.1.13
 * ORR -- Data processing operands - Rotate right with extend */
static bool try_store_ORR_M1_RRE(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  instr->args.g0.id = SLV6_ORR_M1_RRE_ID;
  instr->args.g20.S = S;
  instr->args.g20.d = d;
  instr->args.g20.m = m;
  instr->args.g20.n = n;
  instr->args.g20.cond = cond;
  return true;
}

/* A4.1.43
 * PKHBT */
static bool try_store_PKHBT(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t shift_imm = get_bits(bincode,11,7);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_PKHBT_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.44
 * PKHTB */
static bool try_store_PKHTB(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t shift_imm = get_bits(bincode,11,7);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_PKHTB_ID;
  instr->args.g13.d = d;
  instr->args.g13.m = m;
  instr->args.g13.n = n;
  instr->args.g13.shift_imm = shift_imm;
  instr->args.g13.cond = cond;
  return true;
}

/* A4.1.45--A5.2.2
 * PLD -- Load and Store Word or Unsigned Byte - Immediate offset */
static bool try_store_PLD_M2_ImmOff(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t offset_12 = get_bits(bincode,11,0);
  const uint32_t signed_offset_12 = (U ? offset_12 : -offset_12);
  instr->args.g0.id = SLV6_PLD_M2_ImmOff_ID;
  instr->args.g39.n = n;
  instr->args.g39.signed_offset_12 = signed_offset_12;
  return true;
}

/* A4.1.45--A5.2.3
 * PLD -- Load and Store Word or Unsigned Byte - Register offset */
static bool try_store_PLD_M2_RegOff(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!((m != 15))) return false;
  instr->args.g0.id = SLV6_PLD_M2_RegOff_ID;
  instr->args.g40.U = U;
  instr->args.g40.m = m;
  instr->args.g40.n = n;
  return true;
}

/* A4.1.45--A5.2.4
 * PLD -- Load and Store Word or Unsigned Byte - Scaled register offset */
static bool try_store_PLD_M2_ScRegOff(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift = get_bits(bincode,6,5);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!(((m != 15) && ((shift != 0) || (shift_imm != 0))))) return false;
  instr->args.g0.id = SLV6_PLD_M2_ScRegOff_ID;
  instr->args.g41.U = U;
  instr->args.g41.m = m;
  instr->args.g41.n = n;
  instr->args.g41.shift = shift;
  instr->args.g41.shift_imm = shift_imm;
  return true;
}

/* A4.1.46
 * QADD */
static bool try_store_QADD(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_QADD_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.47
 * QADD16 */
static bool try_store_QADD16(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_QADD16_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.48
 * QADD8 */
static bool try_store_QADD8(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_QADD8_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.49
 * QADDSUBX */
static bool try_store_QADDSUBX(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_QADDSUBX_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.50
 * QDADD */
static bool try_store_QDADD(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_QDADD_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.51
 * QDSUB */
static bool try_store_QDSUB(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_QDSUB_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.52
 * QSUB */
static bool try_store_QSUB(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_QSUB_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.53
 * QSUB16 */
static bool try_store_QSUB16(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_QSUB16_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.54
 * QSUB8 */
static bool try_store_QSUB8(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_QSUB8_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.55
 * QSUBADDX */
static bool try_store_QSUBADDX(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_QSUBADDX_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.56
 * REV */
static bool try_store_REV(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && (m != 15)))) return false;
  instr->args.g0.id = SLV6_REV_ID;
  instr->args.g7.d = d;
  instr->args.g7.m = m;
  instr->args.g7.cond = cond;
  return true;
}

/* A4.1.57
 * REV16 */
static bool try_store_REV16(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && (m != 15)))) return false;
  instr->args.g0.id = SLV6_REV16_ID;
  instr->args.g7.d = d;
  instr->args.g7.m = m;
  instr->args.g7.cond = cond;
  return true;
}

/* A4.1.58
 * REVSH */
static bool try_store_REVSH(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && (m != 15)))) return false;
  instr->args.g0.id = SLV6_REVSH_ID;
  instr->args.g7.d = d;
  instr->args.g7.m = m;
  instr->args.g7.cond = cond;
  return true;
}

/* A4.1.59--A5.4.2
 * RFE -- Load and Store Multiple - Increment after */
static bool try_store_RFE_M4_IA(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  uint8_t n = get_bits(bincode,19,16);
  if (!((n != 15))) return false;
  instr->args.g0.id = SLV6_RFE_M4_IA_ID;
  instr->args.g42.W = W;
  instr->args.g42.n = n;
  return true;
}

/* A4.1.59--A5.4.3
 * RFE -- Load and Store Multiple - Increment before */
static bool try_store_RFE_M4_IB(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  uint8_t n = get_bits(bincode,19,16);
  if (!((n != 15))) return false;
  instr->args.g0.id = SLV6_RFE_M4_IB_ID;
  instr->args.g42.W = W;
  instr->args.g42.n = n;
  return true;
}

/* A4.1.59--A5.4.4
 * RFE -- Load and Store Multiple - Decrement after */
static bool try_store_RFE_M4_DA(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  uint8_t n = get_bits(bincode,19,16);
  if (!((n != 15))) return false;
  instr->args.g0.id = SLV6_RFE_M4_DA_ID;
  instr->args.g42.W = W;
  instr->args.g42.n = n;
  return true;
}

/* A4.1.59--A5.4.5
 * RFE -- Load and Store Multiple - Decrement before */
static bool try_store_RFE_M4_DB(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  uint8_t n = get_bits(bincode,19,16);
  if (!((n != 15))) return false;
  instr->args.g0.id = SLV6_RFE_M4_DB_ID;
  instr->args.g42.W = W;
  instr->args.g42.n = n;
  return true;
}

/* A4.1.60--A5.1.6
 * RSB -- Data processing operands - Logical shift left by register */
static bool try_store_RSB_M1_LSLReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_RSB_M1_LSLReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.60--A5.1.7
 * RSB -- Data processing operands - Logical shift right by immediate */
static bool try_store_RSB_M1_LSRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_RSB_M1_LSRImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.60--A5.1.8
 * RSB -- Data processing operands - Logical shift right by register */
static bool try_store_RSB_M1_LSRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_RSB_M1_LSRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.60--A5.1.10
 * RSB -- Data processing operands - Arithmetic shift right by register */
static bool try_store_RSB_M1_ASRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_RSB_M1_ASRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.60--A5.1.11
 * RSB -- Data processing operands - Rotate right by immediate */
static bool try_store_RSB_M1_RRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  instr->args.g0.id = SLV6_RSB_M1_RRImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.60--A5.1.12
 * RSB -- Data processing operands - Rotate right by register */
static bool try_store_RSB_M1_RRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_RSB_M1_RRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.60--A5.1.13
 * RSB -- Data processing operands - Rotate right with extend */
static bool try_store_RSB_M1_RRE(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  instr->args.g0.id = SLV6_RSB_M1_RRE_ID;
  instr->args.g20.S = S;
  instr->args.g20.d = d;
  instr->args.g20.m = m;
  instr->args.g20.n = n;
  instr->args.g20.cond = cond;
  return true;
}

/* A4.1.61--A5.1.3
 * RSC -- Data processing operands - Immediate */
static bool try_store_RSC_M1_Imm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  instr->args.g0.id = SLV6_RSC_M1_Imm_ID;
  instr->args.g17.S = S;
  instr->args.g17.d = d;
  instr->args.g17.n = n;
  instr->args.g17.rotate_imm = rotate_imm;
  instr->args.g17.cond = cond;
  instr->args.g17.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.61--A5.1.4
 * RSC -- Data processing operands - Register */
static bool try_store_RSC_M1_Reg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  instr->args.g0.id = SLV6_RSC_M1_Reg_ID;
  instr->args.g20.S = S;
  instr->args.g20.d = d;
  instr->args.g20.m = m;
  instr->args.g20.n = n;
  instr->args.g20.cond = cond;
  return true;
}

/* A4.1.61--A5.1.5
 * RSC -- Data processing operands - Logical shift left by immediate */
static bool try_store_RSC_M1_LSLImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  instr->args.g0.id = SLV6_RSC_M1_LSLImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.61--A5.1.6
 * RSC -- Data processing operands - Logical shift left by register */
static bool try_store_RSC_M1_LSLReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_RSC_M1_LSLReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.61--A5.1.7
 * RSC -- Data processing operands - Logical shift right by immediate */
static bool try_store_RSC_M1_LSRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_RSC_M1_LSRImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.61--A5.1.8
 * RSC -- Data processing operands - Logical shift right by register */
static bool try_store_RSC_M1_LSRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_RSC_M1_LSRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.61--A5.1.9
 * RSC -- Data processing operands - Arithmetic shift right by immediate */
static bool try_store_RSC_M1_ASRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_RSC_M1_ASRImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.61--A5.1.10
 * RSC -- Data processing operands - Arithmetic shift right by register */
static bool try_store_RSC_M1_ASRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_RSC_M1_ASRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.61--A5.1.11
 * RSC -- Data processing operands - Rotate right by immediate */
static bool try_store_RSC_M1_RRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  instr->args.g0.id = SLV6_RSC_M1_RRImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.61--A5.1.12
 * RSC -- Data processing operands - Rotate right by register */
static bool try_store_RSC_M1_RRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_RSC_M1_RRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.61--A5.1.13
 * RSC -- Data processing operands - Rotate right with extend */
static bool try_store_RSC_M1_RRE(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  instr->args.g0.id = SLV6_RSC_M1_RRE_ID;
  instr->args.g20.S = S;
  instr->args.g20.d = d;
  instr->args.g20.m = m;
  instr->args.g20.n = n;
  instr->args.g20.cond = cond;
  return true;
}

/* A4.1.62
 * SADD16 */
static bool try_store_SADD16(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_SADD16_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.63
 * SADD8 */
static bool try_store_SADD8(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_SADD8_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.64
 * SADDSUBX */
static bool try_store_SADDSUBX(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_SADDSUBX_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.65--A5.1.3
 * SBC -- Data processing operands - Immediate */
static bool try_store_SBC_M1_Imm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  instr->args.g0.id = SLV6_SBC_M1_Imm_ID;
  instr->args.g17.S = S;
  instr->args.g17.d = d;
  instr->args.g17.n = n;
  instr->args.g17.rotate_imm = rotate_imm;
  instr->args.g17.cond = cond;
  instr->args.g17.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.65--A5.1.4
 * SBC -- Data processing operands - Register */
static bool try_store_SBC_M1_Reg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  instr->args.g0.id = SLV6_SBC_M1_Reg_ID;
  instr->args.g20.S = S;
  instr->args.g20.d = d;
  instr->args.g20.m = m;
  instr->args.g20.n = n;
  instr->args.g20.cond = cond;
  return true;
}

/* A4.1.65--A5.1.5
 * SBC -- Data processing operands - Logical shift left by immediate */
static bool try_store_SBC_M1_LSLImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  instr->args.g0.id = SLV6_SBC_M1_LSLImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.65--A5.1.6
 * SBC -- Data processing operands - Logical shift left by register */
static bool try_store_SBC_M1_LSLReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_SBC_M1_LSLReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.65--A5.1.7
 * SBC -- Data processing operands - Logical shift right by immediate */
static bool try_store_SBC_M1_LSRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_SBC_M1_LSRImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.65--A5.1.8
 * SBC -- Data processing operands - Logical shift right by register */
static bool try_store_SBC_M1_LSRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_SBC_M1_LSRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.65--A5.1.9
 * SBC -- Data processing operands - Arithmetic shift right by immediate */
static bool try_store_SBC_M1_ASRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_SBC_M1_ASRImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.65--A5.1.10
 * SBC -- Data processing operands - Arithmetic shift right by register */
static bool try_store_SBC_M1_ASRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_SBC_M1_ASRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.65--A5.1.11
 * SBC -- Data processing operands - Rotate right by immediate */
static bool try_store_SBC_M1_RRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  instr->args.g0.id = SLV6_SBC_M1_RRImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.65--A5.1.12
 * SBC -- Data processing operands - Rotate right by register */
static bool try_store_SBC_M1_RRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_SBC_M1_RRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.65--A5.1.13
 * SBC -- Data processing operands - Rotate right with extend */
static bool try_store_SBC_M1_RRE(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  instr->args.g0.id = SLV6_SBC_M1_RRE_ID;
  instr->args.g20.S = S;
  instr->args.g20.d = d;
  instr->args.g20.m = m;
  instr->args.g20.n = n;
  instr->args.g20.cond = cond;
  return true;
}

/* A4.1.66
 * SEL */
static bool try_store_SEL(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_SEL_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.67
 * SETEND */
static bool try_store_SETEND(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool E = get_bit(bincode,9);
  instr->args.g0.id = SLV6_SETEND_ID;
  instr->args.g43.E = E;
  return true;
}

/* A4.1.68
 * SHADD16 */
static bool try_store_SHADD16(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_SHADD16_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.69
 * SHADD8 */
static bool try_store_SHADD8(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_SHADD8_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.70
 * SHADDSUBX */
static bool try_store_SHADDSUBX(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_SHADDSUBX_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.71
 * SHSUB16 */
static bool try_store_SHSUB16(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_SHSUB16_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.72
 * SHSUB8 */
static bool try_store_SHSUB8(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_SHSUB8_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.73
 * SHSUBADDX */
static bool try_store_SHSUBADDX(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_SHSUBADDX_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.74
 * SMLA<x><y> */
static bool try_store_SMLAxy(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,19,16);
  uint8_t n = get_bits(bincode,15,12);
  uint8_t s = get_bits(bincode,11,8);
  bool y = get_bit(bincode,6);
  bool x = get_bit(bincode,5);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_SMLAxy_ID;
  instr->args.g44.d = d;
  instr->args.g44.m = m;
  instr->args.g44.n = n;
  instr->args.g44.s = s;
  instr->args.g44.x = x;
  instr->args.g44.y = y;
  instr->args.g44.cond = cond;
  return true;
}

/* A4.1.75
 * SMLAD */
static bool try_store_SMLAD(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,19,16);
  uint8_t n = get_bits(bincode,15,12);
  uint8_t s = get_bits(bincode,11,8);
  bool X = get_bit(bincode,5);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_SMLAD_ID;
  instr->args.g45.X = X;
  instr->args.g45.d = d;
  instr->args.g45.m = m;
  instr->args.g45.n = n;
  instr->args.g45.s = s;
  instr->args.g45.cond = cond;
  return true;
}

/* A4.1.76
 * SMLAL */
static bool try_store_SMLAL(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  bool S = get_bit(bincode,20);
  uint8_t dHi = get_bits(bincode,19,16);
  uint8_t dLo = get_bits(bincode,15,12);
  uint8_t s = get_bits(bincode,11,8);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((dHi != 15) && ((dLo != 15) && ((m != 15) && ((s != 15) && (dHi != dLo))))))) return false;
  instr->args.g0.id = SLV6_SMLAL_ID;
  instr->args.g46.S = S;
  instr->args.g46.dHi = dHi;
  instr->args.g46.dLo = dLo;
  instr->args.g46.m = m;
  instr->args.g46.s = s;
  instr->args.g46.cond = cond;
  return true;
}

/* A4.1.77
 * SMLAL<x><y> */
static bool try_store_SMLALxy(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t dHi = get_bits(bincode,19,16);
  uint8_t dLo = get_bits(bincode,15,12);
  uint8_t s = get_bits(bincode,11,8);
  bool y = get_bit(bincode,6);
  bool x = get_bit(bincode,5);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((dHi != 15) && ((dLo != 15) && ((m != 15) && ((s != 15) && (dHi != dLo))))))) return false;
  instr->args.g0.id = SLV6_SMLALxy_ID;
  instr->args.g47.dHi = dHi;
  instr->args.g47.dLo = dLo;
  instr->args.g47.m = m;
  instr->args.g47.s = s;
  instr->args.g47.x = x;
  instr->args.g47.y = y;
  instr->args.g47.cond = cond;
  return true;
}

/* A4.1.78
 * SMLALD */
static bool try_store_SMLALD(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t dHi = get_bits(bincode,19,16);
  uint8_t dLo = get_bits(bincode,15,12);
  uint8_t s = get_bits(bincode,11,8);
  bool X = get_bit(bincode,5);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((dHi != 15) && ((dLo != 15) && ((m != 15) && ((s != 15) && (dHi != dLo))))))) return false;
  instr->args.g0.id = SLV6_SMLALD_ID;
  instr->args.g48.X = X;
  instr->args.g48.dHi = dHi;
  instr->args.g48.dLo = dLo;
  instr->args.g48.m = m;
  instr->args.g48.s = s;
  instr->args.g48.cond = cond;
  return true;
}

/* A4.1.79
 * SMLAW<y> */
static bool try_store_SMLAWy(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,19,16);
  uint8_t n = get_bits(bincode,15,12);
  uint8_t s = get_bits(bincode,11,8);
  bool y = get_bit(bincode,6);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_SMLAWy_ID;
  instr->args.g49.d = d;
  instr->args.g49.m = m;
  instr->args.g49.n = n;
  instr->args.g49.s = s;
  instr->args.g49.y = y;
  instr->args.g49.cond = cond;
  return true;
}

/* A4.1.80
 * SMLSD */
static bool try_store_SMLSD(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,19,16);
  uint8_t n = get_bits(bincode,15,12);
  uint8_t s = get_bits(bincode,11,8);
  bool X = get_bit(bincode,5);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_SMLSD_ID;
  instr->args.g45.X = X;
  instr->args.g45.d = d;
  instr->args.g45.m = m;
  instr->args.g45.n = n;
  instr->args.g45.s = s;
  instr->args.g45.cond = cond;
  return true;
}

/* A4.1.81
 * SMLSLD */
static bool try_store_SMLSLD(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t dHi = get_bits(bincode,19,16);
  uint8_t dLo = get_bits(bincode,15,12);
  uint8_t s = get_bits(bincode,11,8);
  bool X = get_bit(bincode,5);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((dHi != 15) && ((dLo != 15) && ((m != 15) && ((s != 15) && (dHi != dLo))))))) return false;
  instr->args.g0.id = SLV6_SMLSLD_ID;
  instr->args.g48.X = X;
  instr->args.g48.dHi = dHi;
  instr->args.g48.dLo = dLo;
  instr->args.g48.m = m;
  instr->args.g48.s = s;
  instr->args.g48.cond = cond;
  return true;
}

/* A4.1.82
 * SMMLA */
static bool try_store_SMMLA(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,19,16);
  uint8_t n = get_bits(bincode,15,12);
  uint8_t s = get_bits(bincode,11,8);
  bool R = get_bit(bincode,5);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_SMMLA_ID;
  instr->args.g50.R = R;
  instr->args.g50.d = d;
  instr->args.g50.m = m;
  instr->args.g50.n = n;
  instr->args.g50.s = s;
  instr->args.g50.cond = cond;
  return true;
}

/* A4.1.83
 * SMMLS */
static bool try_store_SMMLS(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,19,16);
  uint8_t n = get_bits(bincode,15,12);
  uint8_t s = get_bits(bincode,11,8);
  bool R = get_bit(bincode,5);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_SMMLS_ID;
  instr->args.g50.R = R;
  instr->args.g50.d = d;
  instr->args.g50.m = m;
  instr->args.g50.n = n;
  instr->args.g50.s = s;
  instr->args.g50.cond = cond;
  return true;
}

/* A4.1.84
 * SMMUL */
static bool try_store_SMMUL(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  bool R = get_bit(bincode,5);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (s != 15))))) return false;
  instr->args.g0.id = SLV6_SMMUL_ID;
  instr->args.g51.R = R;
  instr->args.g51.d = d;
  instr->args.g51.m = m;
  instr->args.g51.s = s;
  instr->args.g51.cond = cond;
  return true;
}

/* A4.1.85
 * SMUAD */
static bool try_store_SMUAD(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  bool X = get_bit(bincode,5);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (s != 15))))) return false;
  instr->args.g0.id = SLV6_SMUAD_ID;
  instr->args.g52.X = X;
  instr->args.g52.d = d;
  instr->args.g52.m = m;
  instr->args.g52.s = s;
  instr->args.g52.cond = cond;
  return true;
}

/* A4.1.86
 * SMUL<x><y> */
static bool try_store_SMULxy(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  bool y = get_bit(bincode,6);
  bool x = get_bit(bincode,5);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (s != 15))))) return false;
  instr->args.g0.id = SLV6_SMULxy_ID;
  instr->args.g53.d = d;
  instr->args.g53.m = m;
  instr->args.g53.s = s;
  instr->args.g53.x = x;
  instr->args.g53.y = y;
  instr->args.g53.cond = cond;
  return true;
}

/* A4.1.88
 * SMULW<y> */
static bool try_store_SMULWy(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  bool y = get_bit(bincode,6);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (s != 15))))) return false;
  instr->args.g0.id = SLV6_SMULWy_ID;
  instr->args.g54.d = d;
  instr->args.g54.m = m;
  instr->args.g54.s = s;
  instr->args.g54.y = y;
  instr->args.g54.cond = cond;
  return true;
}

/* A4.1.89
 * SMUSD */
static bool try_store_SMUSD(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  bool X = get_bit(bincode,5);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (s != 15))))) return false;
  instr->args.g0.id = SLV6_SMUSD_ID;
  instr->args.g52.X = X;
  instr->args.g52.d = d;
  instr->args.g52.m = m;
  instr->args.g52.s = s;
  instr->args.g52.cond = cond;
  return true;
}

/* A4.1.90--A5.4.2
 * SRS -- Load and Store Multiple - Increment after */
static bool try_store_SRS_M4_IA(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t mode_tmp = get_bits(bincode,4,0);
  SLv6_Mode mode;
  if (!decode_mode(&mode,bincode)) return false;
  instr->args.g0.id = SLV6_SRS_M4_IA_ID;
  instr->args.g55.W = W;
  instr->args.g55.mode = mode;
  return true;
}

/* A4.1.90--A5.4.3
 * SRS -- Load and Store Multiple - Increment before */
static bool try_store_SRS_M4_IB(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t mode_tmp = get_bits(bincode,4,0);
  SLv6_Mode mode;
  if (!decode_mode(&mode,bincode)) return false;
  instr->args.g0.id = SLV6_SRS_M4_IB_ID;
  instr->args.g55.W = W;
  instr->args.g55.mode = mode;
  return true;
}

/* A4.1.90--A5.4.4
 * SRS -- Load and Store Multiple - Decrement after */
static bool try_store_SRS_M4_DA(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t mode_tmp = get_bits(bincode,4,0);
  SLv6_Mode mode;
  if (!decode_mode(&mode,bincode)) return false;
  instr->args.g0.id = SLV6_SRS_M4_DA_ID;
  instr->args.g55.W = W;
  instr->args.g55.mode = mode;
  return true;
}

/* A4.1.90--A5.4.5
 * SRS -- Load and Store Multiple - Decrement before */
static bool try_store_SRS_M4_DB(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t mode_tmp = get_bits(bincode,4,0);
  SLv6_Mode mode;
  if (!decode_mode(&mode,bincode)) return false;
  instr->args.g0.id = SLV6_SRS_M4_DB_ID;
  instr->args.g55.W = W;
  instr->args.g55.mode = mode;
  return true;
}

/* A4.1.91
 * SSAT */
static bool try_store_SSAT(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t sat_imm = get_bits(bincode,20,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t shift_imm = get_bits(bincode,11,7);
  uint8_t shift = get_bit(bincode,6);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && (m != 15)))) return false;
  instr->args.g0.id = SLV6_SSAT_ID;
  instr->args.g56.d = d;
  instr->args.g56.m = m;
  instr->args.g56.sat_imm = sat_imm;
  instr->args.g56.shift = shift;
  instr->args.g56.shift_imm = shift_imm;
  instr->args.g56.cond = cond;
  return true;
}

/* A4.1.92
 * SSAT16 */
static bool try_store_SSAT16(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t sat_imm = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && (m != 15)))) return false;
  instr->args.g0.id = SLV6_SSAT16_ID;
  instr->args.g57.d = d;
  instr->args.g57.m = m;
  instr->args.g57.sat_imm = sat_imm;
  instr->args.g57.cond = cond;
  return true;
}

/* A4.1.93
 * SSUB16 */
static bool try_store_SSUB16(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_SSUB16_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.94
 * SSUB8 */
static bool try_store_SSUB8(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_SSUB8_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.95
 * SSUBADDX */
static bool try_store_SSUBADDX(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_SSUBADDX_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.96--A5.5.2
 * STC -- Load and Store Coprocessor - Immediate offset */
static bool try_store_STC_M5_ImmOff(struct SLv6_Instruction *instr, uint32_t bincode) {
  instr->args.g0.id = SLV6_STC_M5_ImmOff_ID;
  return true;
}

/* A4.1.96--A5.5.3
 * STC -- Load and Store Coprocessor - Immediate pre indexed */
static bool try_store_STC_M5_Imm_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  uint8_t n = get_bits(bincode,19,16);
  if (!((n != 15))) return false;
  instr->args.g0.id = SLV6_STC_M5_Imm_preInd_ID;
  return true;
}

/* A4.1.96--A5.5.4
 * STC -- Load and Store Coprocessor - Immediate post indexed */
static bool try_store_STC_M5_Imm_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  uint8_t n = get_bits(bincode,19,16);
  if (!((n != 15))) return false;
  instr->args.g0.id = SLV6_STC_M5_Imm_postInd_ID;
  return true;
}

/* A4.1.96--A5.5.5
 * STC -- Load and Store Coprocessor - Unindexed */
static bool try_store_STC_M5_U(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  if (!((U != 0))) return false;
  instr->args.g0.id = SLV6_STC_M5_U_ID;
  return true;
}

/* A4.1.97--A5.4.4
 * STM (1) -- Load and Store Multiple - Decrement after */
static bool try_store_STM1_M4_DA(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!(((n != 15) && (register_list != 0)))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  instr->args.g0.id = SLV6_STM1_M4_DA_ID;
  instr->args.g26.W = W;
  instr->args.g26.n = n;
  instr->args.g26.nb_reg_x4 = nb_reg_x4;
  instr->args.g26.cond = cond;
  instr->args.g26.register_list = register_list;
  return true;
}

/* A4.1.98--A5.4.2
 * STM (2) -- Load and Store Multiple - Increment after */
static bool try_store_STM2_M4_IA(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!(((n != 15) && (register_list != 0)))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  instr->args.g0.id = SLV6_STM2_M4_IA_ID;
  instr->args.g9.n = n;
  instr->args.g9.nb_reg_x4 = nb_reg_x4;
  instr->args.g9.cond = cond;
  instr->args.g9.register_list = register_list;
  return true;
}

/* A4.1.98--A5.4.3
 * STM (2) -- Load and Store Multiple - Increment before */
static bool try_store_STM2_M4_IB(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!(((n != 15) && (register_list != 0)))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  instr->args.g0.id = SLV6_STM2_M4_IB_ID;
  instr->args.g9.n = n;
  instr->args.g9.nb_reg_x4 = nb_reg_x4;
  instr->args.g9.cond = cond;
  instr->args.g9.register_list = register_list;
  return true;
}

/* A4.1.98--A5.4.4
 * STM (2) -- Load and Store Multiple - Decrement after */
static bool try_store_STM2_M4_DA(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!(((n != 15) && (register_list != 0)))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  instr->args.g0.id = SLV6_STM2_M4_DA_ID;
  instr->args.g9.n = n;
  instr->args.g9.nb_reg_x4 = nb_reg_x4;
  instr->args.g9.cond = cond;
  instr->args.g9.register_list = register_list;
  return true;
}

/* A4.1.98--A5.4.5
 * STM (2) -- Load and Store Multiple - Decrement before */
static bool try_store_STM2_M4_DB(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t register_list = get_bits(bincode,15,0);
  if (!(((n != 15) && (register_list != 0)))) return false;
  const uint8_t nb_reg_x4 = Number_Of_Set_Bits_In(register_list) * 4;
  instr->args.g0.id = SLV6_STM2_M4_DB_ID;
  instr->args.g9.n = n;
  instr->args.g9.nb_reg_x4 = nb_reg_x4;
  instr->args.g9.cond = cond;
  instr->args.g9.register_list = register_list;
  return true;
}

/* A4.1.99--A5.2.6
 * STR -- Load and Store Word or Unsigned Byte - Register pre indexed */
static bool try_store_STR_M2_Reg_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!((((W == 0) || (n != d)) && ((n != 15) && (m != 15))))) return false;
  instr->args.g0.id = SLV6_STR_M2_Reg_preInd_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.99--A5.2.7
 * STR -- Load and Store Word or Unsigned Byte - Scaled register pre indexed */
static bool try_store_STR_M2_ScReg_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift = get_bits(bincode,6,5);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((((W == 0) || (n != d)) && ((n != 15) && ((m != 15) && ((shift != 0) || (shift_imm != 0))))))) return false;
  instr->args.g0.id = SLV6_STR_M2_ScReg_preInd_ID;
  instr->args.g28.U = U;
  instr->args.g28.d = d;
  instr->args.g28.m = m;
  instr->args.g28.n = n;
  instr->args.g28.shift = shift;
  instr->args.g28.shift_imm = shift_imm;
  instr->args.g28.cond = cond;
  return true;
}

/* A4.1.99--A5.2.10
 * STR -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
static bool try_store_STR_M2_ScReg_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift = get_bits(bincode,6,5);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((((W == 0) || (n != d)) && ((n != 15) && ((m != 15) && ((shift != 0) || (shift_imm != 0))))))) return false;
  instr->args.g0.id = SLV6_STR_M2_ScReg_postInd_ID;
  instr->args.g28.U = U;
  instr->args.g28.d = d;
  instr->args.g28.m = m;
  instr->args.g28.n = n;
  instr->args.g28.shift = shift;
  instr->args.g28.shift_imm = shift_imm;
  instr->args.g28.cond = cond;
  return true;
}

/* A4.1.100--A5.2.4
 * STRB -- Load and Store Word or Unsigned Byte - Scaled register offset */
static bool try_store_STRB_M2_ScRegOff(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift = get_bits(bincode,6,5);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((((W == 0) || (n != d)) && ((d != 15) && ((m != 15) && ((shift != 0) || (shift_imm != 0))))))) return false;
  instr->args.g0.id = SLV6_STRB_M2_ScRegOff_ID;
  instr->args.g28.U = U;
  instr->args.g28.d = d;
  instr->args.g28.m = m;
  instr->args.g28.n = n;
  instr->args.g28.shift = shift;
  instr->args.g28.shift_imm = shift_imm;
  instr->args.g28.cond = cond;
  return true;
}

/* A4.1.100--A5.2.5
 * STRB -- Load and Store Word or Unsigned Byte - Immediate pre indexed */
static bool try_store_STRB_M2_Imm_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t offset_12 = get_bits(bincode,11,0);
  if (!((((W == 0) || (n != d)) && ((d != 15) && (n != 15))))) return false;
  const uint32_t signed_offset_12 = (U ? offset_12 : -offset_12);
  instr->args.g0.id = SLV6_STRB_M2_Imm_preInd_ID;
  instr->args.g1.d = d;
  instr->args.g1.n = n;
  instr->args.g1.cond = cond;
  instr->args.g1.signed_offset_12 = signed_offset_12;
  return true;
}

/* A4.1.100--A5.2.6
 * STRB -- Load and Store Word or Unsigned Byte - Register pre indexed */
static bool try_store_STRB_M2_Reg_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!((((W == 0) || (n != d)) && ((d != 15) && ((n != 15) && (m != 15)))))) return false;
  instr->args.g0.id = SLV6_STRB_M2_Reg_preInd_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.100--A5.2.7
 * STRB -- Load and Store Word or Unsigned Byte - Scaled register pre indexed */
static bool try_store_STRB_M2_ScReg_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift = get_bits(bincode,6,5);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((((W == 0) || (n != d)) && ((d != 15) && ((n != 15) && ((m != 15) && ((shift != 0) || (shift_imm != 0)))))))) return false;
  instr->args.g0.id = SLV6_STRB_M2_ScReg_preInd_ID;
  instr->args.g28.U = U;
  instr->args.g28.d = d;
  instr->args.g28.m = m;
  instr->args.g28.n = n;
  instr->args.g28.shift = shift;
  instr->args.g28.shift_imm = shift_imm;
  instr->args.g28.cond = cond;
  return true;
}

/* A4.1.100--A5.2.9
 * STRB -- Load and Store Word or Unsigned Byte - Register post indexed */
static bool try_store_STRB_M2_Reg_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!((((W == 0) || (n != d)) && ((d != 15) && ((n != 15) && (m != 15)))))) return false;
  instr->args.g0.id = SLV6_STRB_M2_Reg_postInd_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.100--A5.2.10
 * STRB -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
static bool try_store_STRB_M2_ScReg_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift = get_bits(bincode,6,5);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((((W == 0) || (n != d)) && ((d != 15) && ((n != 15) && ((m != 15) && ((shift != 0) || (shift_imm != 0)))))))) return false;
  instr->args.g0.id = SLV6_STRB_M2_ScReg_postInd_ID;
  instr->args.g28.U = U;
  instr->args.g28.d = d;
  instr->args.g28.m = m;
  instr->args.g28.n = n;
  instr->args.g28.shift = shift;
  instr->args.g28.shift_imm = shift_imm;
  instr->args.g28.cond = cond;
  return true;
}

/* A4.1.101--A5.2.8
 * STRBT -- Load and Store Word or Unsigned Byte - Immediate post indexed */
static bool try_store_STRBT_M2_Imm_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t offset_12 = get_bits(bincode,11,0);
  if (!(((d != 15) && ((d != n) && (n != 15))))) return false;
  const uint32_t signed_offset_12 = (U ? offset_12 : -offset_12);
  instr->args.g0.id = SLV6_STRBT_M2_Imm_postInd_ID;
  instr->args.g1.d = d;
  instr->args.g1.n = n;
  instr->args.g1.cond = cond;
  instr->args.g1.signed_offset_12 = signed_offset_12;
  return true;
}

/* A4.1.101--A5.2.9
 * STRBT -- Load and Store Word or Unsigned Byte - Register post indexed */
static bool try_store_STRBT_M2_Reg_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 15) && ((d != n) && ((n != 15) && (m != 15)))))) return false;
  instr->args.g0.id = SLV6_STRBT_M2_Reg_postInd_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.101--A5.2.10
 * STRBT -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
static bool try_store_STRBT_M2_ScReg_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift = get_bits(bincode,6,5);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!(((d != 15) && ((d != n) && ((n != 15) && ((m != 15) && ((shift != 0) || (shift_imm != 0)))))))) return false;
  instr->args.g0.id = SLV6_STRBT_M2_ScReg_postInd_ID;
  instr->args.g28.U = U;
  instr->args.g28.d = d;
  instr->args.g28.m = m;
  instr->args.g28.n = n;
  instr->args.g28.shift = shift;
  instr->args.g28.shift_imm = shift_imm;
  instr->args.g28.cond = cond;
  return true;
}

/* A4.1.102--A5.3.2
 * STRD -- Miscellaneous Loads and Stores - Immediate offset */
static bool try_store_STRD_M3_ImmOff(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immedH = get_bits(bincode,11,8);
  uint8_t immedL = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 14) && is_even(d)))) return false;
  const uint8_t immedHL = (immedH << 4) | immedL;
  instr->args.g0.id = SLV6_STRD_M3_ImmOff_ID;
  instr->args.g29.U = U;
  instr->args.g29.d = d;
  instr->args.g29.n = n;
  instr->args.g29.immedHL = immedHL;
  instr->args.g29.cond = cond;
  return true;
}

/* A4.1.102--A5.3.3
 * STRD -- Miscellaneous Loads and Stores - Register offset */
static bool try_store_STRD_M3_RegOff(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 14) && (is_even(d) && (m != 15))))) return false;
  instr->args.g0.id = SLV6_STRD_M3_RegOff_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.102--A5.3.4
 * STRD -- Miscellaneous Loads and Stores - Immediate pre indexed */
static bool try_store_STRD_M3_Imm_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immedH = get_bits(bincode,11,8);
  uint8_t immedL = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 14) && (is_even(d) && (n != 15))))) return false;
  const uint8_t immedHL = (immedH << 4) | immedL;
  instr->args.g0.id = SLV6_STRD_M3_Imm_preInd_ID;
  instr->args.g29.U = U;
  instr->args.g29.d = d;
  instr->args.g29.n = n;
  instr->args.g29.immedHL = immedHL;
  instr->args.g29.cond = cond;
  return true;
}

/* A4.1.102--A5.3.5
 * STRD -- Miscellaneous Loads and Stores - Register pre indexed */
static bool try_store_STRD_M3_Reg_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 14) && (is_even(d) && ((n != 15) && (m != 15)))))) return false;
  instr->args.g0.id = SLV6_STRD_M3_Reg_preInd_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.102--A5.3.6
 * STRD -- Miscellaneous Loads and Stores - Immediate post indexed */
static bool try_store_STRD_M3_Imm_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immedH = get_bits(bincode,11,8);
  uint8_t immedL = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 14) && is_even(d)))) return false;
  const uint8_t immedHL = (immedH << 4) | immedL;
  instr->args.g0.id = SLV6_STRD_M3_Imm_postInd_ID;
  instr->args.g29.U = U;
  instr->args.g29.d = d;
  instr->args.g29.n = n;
  instr->args.g29.immedHL = immedHL;
  instr->args.g29.cond = cond;
  return true;
}

/* A4.1.102--A5.3.7
 * STRD -- Miscellaneous Loads and Stores - Register post indexed */
static bool try_store_STRD_M3_Reg_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != 14) && is_even(d)))) return false;
  instr->args.g0.id = SLV6_STRD_M3_Reg_postInd_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.103
 * STREX */
static bool try_store_STREX(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((n != 15) && ((m != 15) && ((d != n) && (d != m))))))) return false;
  instr->args.g0.id = SLV6_STREX_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.104--A5.3.2
 * STRH -- Miscellaneous Loads and Stores - Immediate offset */
static bool try_store_STRH_M3_ImmOff(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immedH = get_bits(bincode,11,8);
  uint8_t immedL = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!((((W == 0) || (n != d)) && (d != 15)))) return false;
  const uint8_t immedHL = (immedH << 4) | immedL;
  instr->args.g0.id = SLV6_STRH_M3_ImmOff_ID;
  instr->args.g29.U = U;
  instr->args.g29.d = d;
  instr->args.g29.n = n;
  instr->args.g29.immedHL = immedHL;
  instr->args.g29.cond = cond;
  return true;
}

/* A4.1.104--A5.3.3
 * STRH -- Miscellaneous Loads and Stores - Register offset */
static bool try_store_STRH_M3_RegOff(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!((((W == 0) || (n != d)) && ((d != 15) && (m != 15))))) return false;
  instr->args.g0.id = SLV6_STRH_M3_RegOff_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.104--A5.3.4
 * STRH -- Miscellaneous Loads and Stores - Immediate pre indexed */
static bool try_store_STRH_M3_Imm_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immedH = get_bits(bincode,11,8);
  uint8_t immedL = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!((((W == 0) || (n != d)) && ((d != 15) && (n != 15))))) return false;
  const uint8_t immedHL = (immedH << 4) | immedL;
  instr->args.g0.id = SLV6_STRH_M3_Imm_preInd_ID;
  instr->args.g29.U = U;
  instr->args.g29.d = d;
  instr->args.g29.n = n;
  instr->args.g29.immedHL = immedHL;
  instr->args.g29.cond = cond;
  return true;
}

/* A4.1.104--A5.3.5
 * STRH -- Miscellaneous Loads and Stores - Register pre indexed */
static bool try_store_STRH_M3_Reg_preInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!((((W == 0) || (n != d)) && ((d != 15) && ((n != 15) && (m != 15)))))) return false;
  instr->args.g0.id = SLV6_STRH_M3_Reg_preInd_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.104--A5.3.6
 * STRH -- Miscellaneous Loads and Stores - Immediate post indexed */
static bool try_store_STRH_M3_Imm_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t immedH = get_bits(bincode,11,8);
  uint8_t immedL = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!((((W == 0) || (n != d)) && (d != 15)))) return false;
  const uint8_t immedHL = (immedH << 4) | immedL;
  instr->args.g0.id = SLV6_STRH_M3_Imm_postInd_ID;
  instr->args.g29.U = U;
  instr->args.g29.d = d;
  instr->args.g29.n = n;
  instr->args.g29.immedHL = immedHL;
  instr->args.g29.cond = cond;
  return true;
}

/* A4.1.104--A5.3.7
 * STRH -- Miscellaneous Loads and Stores - Register post indexed */
static bool try_store_STRH_M3_Reg_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  bool W = get_bit(bincode,21);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!((((W == 0) || (n != d)) && (d != 15)))) return false;
  instr->args.g0.id = SLV6_STRH_M3_Reg_postInd_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.105--A5.2.8
 * STRT -- Load and Store Word or Unsigned Byte - Immediate post indexed */
static bool try_store_STRT_M2_Imm_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t n = get_bits(bincode,19,16);
  uint32_t offset_12 = get_bits(bincode,11,0);
  if (!(((d != n) && (n != 15)))) return false;
  const uint32_t signed_offset_12 = (U ? offset_12 : -offset_12);
  instr->args.g0.id = SLV6_STRT_M2_Imm_postInd_ID;
  instr->args.g1.d = d;
  instr->args.g1.n = n;
  instr->args.g1.cond = cond;
  instr->args.g1.signed_offset_12 = signed_offset_12;
  return true;
}

/* A4.1.105--A5.2.9
 * STRT -- Load and Store Word or Unsigned Byte - Register post indexed */
static bool try_store_STRT_M2_Reg_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  if (!(((d != n) && ((n != 15) && (m != 15))))) return false;
  instr->args.g0.id = SLV6_STRT_M2_Reg_postInd_ID;
  instr->args.g27.U = U;
  instr->args.g27.d = d;
  instr->args.g27.m = m;
  instr->args.g27.n = n;
  instr->args.g27.cond = cond;
  return true;
}

/* A4.1.105--A5.2.10
 * STRT -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
static bool try_store_STRT_M2_ScReg_postInd(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool U = get_bit(bincode,23);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift = get_bits(bincode,6,5);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!(((d != n) && ((n != 15) && ((m != 15) && ((shift != 0) || (shift_imm != 0))))))) return false;
  instr->args.g0.id = SLV6_STRT_M2_ScReg_postInd_ID;
  instr->args.g28.U = U;
  instr->args.g28.d = d;
  instr->args.g28.m = m;
  instr->args.g28.n = n;
  instr->args.g28.shift = shift;
  instr->args.g28.shift_imm = shift_imm;
  instr->args.g28.cond = cond;
  return true;
}

/* A4.1.106--A5.1.4
 * SUB -- Data processing operands - Register */
static bool try_store_SUB_M1_Reg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  instr->args.g0.id = SLV6_SUB_M1_Reg_ID;
  instr->args.g20.S = S;
  instr->args.g20.d = d;
  instr->args.g20.m = m;
  instr->args.g20.n = n;
  instr->args.g20.cond = cond;
  return true;
}

/* A4.1.106--A5.1.6
 * SUB -- Data processing operands - Logical shift left by register */
static bool try_store_SUB_M1_LSLReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_SUB_M1_LSLReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.106--A5.1.7
 * SUB -- Data processing operands - Logical shift right by immediate */
static bool try_store_SUB_M1_LSRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_SUB_M1_LSRImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.106--A5.1.8
 * SUB -- Data processing operands - Logical shift right by register */
static bool try_store_SUB_M1_LSRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_SUB_M1_LSRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.106--A5.1.10
 * SUB -- Data processing operands - Arithmetic shift right by register */
static bool try_store_SUB_M1_ASRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_SUB_M1_ASRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.106--A5.1.11
 * SUB -- Data processing operands - Rotate right by immediate */
static bool try_store_SUB_M1_RRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  instr->args.g0.id = SLV6_SUB_M1_RRImm_ID;
  instr->args.g18.S = S;
  instr->args.g18.d = d;
  instr->args.g18.m = m;
  instr->args.g18.n = n;
  instr->args.g18.shift_imm = shift_imm;
  instr->args.g18.cond = cond;
  return true;
}

/* A4.1.106--A5.1.12
 * SUB -- Data processing operands - Rotate right by register */
static bool try_store_SUB_M1_RRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_SUB_M1_RRReg_ID;
  instr->args.g19.S = S;
  instr->args.g19.d = d;
  instr->args.g19.m = m;
  instr->args.g19.n = n;
  instr->args.g19.s = s;
  instr->args.g19.cond = cond;
  return true;
}

/* A4.1.106--A5.1.13
 * SUB -- Data processing operands - Rotate right with extend */
static bool try_store_SUB_M1_RRE(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool S = get_bit(bincode,20);
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  instr->args.g0.id = SLV6_SUB_M1_RRE_ID;
  instr->args.g20.S = S;
  instr->args.g20.d = d;
  instr->args.g20.m = m;
  instr->args.g20.n = n;
  instr->args.g20.cond = cond;
  return true;
}

/* A4.1.107
 * SWI */
static bool try_store_SWI(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  instr->args.g0.id = SLV6_SWI_ID;
  instr->args.g58.cond = cond;
  return true;
}

/* A4.1.108
 * SWP */
static bool try_store_SWP(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((n != 15) && ((m != 15) && ((n != m) && (n != d))))))) return false;
  instr->args.g0.id = SLV6_SWP_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.109
 * SWPB */
static bool try_store_SWPB(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((n != 15) && ((m != 15) && ((n != m) && (n != d))))))) return false;
  instr->args.g0.id = SLV6_SWPB_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.110
 * SXTAB */
static bool try_store_SXTAB(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t rotate = get_bits(bincode,11,10);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_SXTAB_ID;
  instr->args.g59.d = d;
  instr->args.g59.m = m;
  instr->args.g59.n = n;
  instr->args.g59.rotate = rotate;
  instr->args.g59.cond = cond;
  return true;
}

/* A4.1.111
 * SXTAB16 */
static bool try_store_SXTAB16(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t rotate = get_bits(bincode,11,10);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_SXTAB16_ID;
  instr->args.g59.d = d;
  instr->args.g59.m = m;
  instr->args.g59.n = n;
  instr->args.g59.rotate = rotate;
  instr->args.g59.cond = cond;
  return true;
}

/* A4.1.112
 * SXTAH */
static bool try_store_SXTAH(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t rotate = get_bits(bincode,11,10);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_SXTAH_ID;
  instr->args.g59.d = d;
  instr->args.g59.m = m;
  instr->args.g59.n = n;
  instr->args.g59.rotate = rotate;
  instr->args.g59.cond = cond;
  return true;
}

/* A4.1.113
 * SXTB */
static bool try_store_SXTB(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t rotate = get_bits(bincode,11,10);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && (m != 15)))) return false;
  instr->args.g0.id = SLV6_SXTB_ID;
  instr->args.g60.d = d;
  instr->args.g60.m = m;
  instr->args.g60.rotate = rotate;
  instr->args.g60.cond = cond;
  return true;
}

/* A4.1.114
 * SXTB16 */
static bool try_store_SXTB16(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t rotate = get_bits(bincode,11,10);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && (m != 15)))) return false;
  instr->args.g0.id = SLV6_SXTB16_ID;
  instr->args.g60.d = d;
  instr->args.g60.m = m;
  instr->args.g60.rotate = rotate;
  instr->args.g60.cond = cond;
  return true;
}

/* A4.1.115
 * SXTH */
static bool try_store_SXTH(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t rotate = get_bits(bincode,11,10);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && (m != 15)))) return false;
  instr->args.g0.id = SLV6_SXTH_ID;
  instr->args.g60.d = d;
  instr->args.g60.m = m;
  instr->args.g60.rotate = rotate;
  instr->args.g60.cond = cond;
  return true;
}

/* A4.1.116--A5.1.3
 * TEQ -- Data processing operands - Immediate */
static bool try_store_TEQ_M1_Imm(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t immed_8 = get_bits(bincode,7,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t rotate_imm = get_bits(bincode,11,8);
  const uint32_t immed_rotated = rotate_right(immed_8,rotate_imm*2);
  instr->args.g0.id = SLV6_TEQ_M1_Imm_ID;
  instr->args.g10.n = n;
  instr->args.g10.rotate_imm = rotate_imm;
  instr->args.g10.cond = cond;
  instr->args.g10.immed_rotated = immed_rotated;
  return true;
}

/* A4.1.116--A5.1.4
 * TEQ -- Data processing operands - Register */
static bool try_store_TEQ_M1_Reg(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  instr->args.g0.id = SLV6_TEQ_M1_Reg_ID;
  instr->args.g4.m = m;
  instr->args.g4.n = n;
  instr->args.g4.cond = cond;
  return true;
}

/* A4.1.116--A5.1.5
 * TEQ -- Data processing operands - Logical shift left by immediate */
static bool try_store_TEQ_M1_LSLImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  instr->args.g0.id = SLV6_TEQ_M1_LSLImm_ID;
  instr->args.g23.m = m;
  instr->args.g23.n = n;
  instr->args.g23.shift_imm = shift_imm;
  instr->args.g23.cond = cond;
  return true;
}

/* A4.1.116--A5.1.6
 * TEQ -- Data processing operands - Logical shift left by register */
static bool try_store_TEQ_M1_LSLReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_TEQ_M1_LSLReg_ID;
  instr->args.g24.m = m;
  instr->args.g24.n = n;
  instr->args.g24.s = s;
  instr->args.g24.cond = cond;
  return true;
}

/* A4.1.116--A5.1.7
 * TEQ -- Data processing operands - Logical shift right by immediate */
static bool try_store_TEQ_M1_LSRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_TEQ_M1_LSRImm_ID;
  instr->args.g23.m = m;
  instr->args.g23.n = n;
  instr->args.g23.shift_imm = shift_imm;
  instr->args.g23.cond = cond;
  return true;
}

/* A4.1.116--A5.1.8
 * TEQ -- Data processing operands - Logical shift right by register */
static bool try_store_TEQ_M1_LSRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_TEQ_M1_LSRReg_ID;
  instr->args.g24.m = m;
  instr->args.g24.n = n;
  instr->args.g24.s = s;
  instr->args.g24.cond = cond;
  return true;
}

/* A4.1.116--A5.1.9
 * TEQ -- Data processing operands - Arithmetic shift right by immediate */
static bool try_store_TEQ_M1_ASRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_TEQ_M1_ASRImm_ID;
  instr->args.g23.m = m;
  instr->args.g23.n = n;
  instr->args.g23.shift_imm = shift_imm;
  instr->args.g23.cond = cond;
  return true;
}

/* A4.1.116--A5.1.10
 * TEQ -- Data processing operands - Arithmetic shift right by register */
static bool try_store_TEQ_M1_ASRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_TEQ_M1_ASRReg_ID;
  instr->args.g24.m = m;
  instr->args.g24.n = n;
  instr->args.g24.s = s;
  instr->args.g24.cond = cond;
  return true;
}

/* A4.1.116--A5.1.11
 * TEQ -- Data processing operands - Rotate right by immediate */
static bool try_store_TEQ_M1_RRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  instr->args.g0.id = SLV6_TEQ_M1_RRImm_ID;
  instr->args.g23.m = m;
  instr->args.g23.n = n;
  instr->args.g23.shift_imm = shift_imm;
  instr->args.g23.cond = cond;
  return true;
}

/* A4.1.116--A5.1.12
 * TEQ -- Data processing operands - Rotate right by register */
static bool try_store_TEQ_M1_RRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_TEQ_M1_RRReg_ID;
  instr->args.g24.m = m;
  instr->args.g24.n = n;
  instr->args.g24.s = s;
  instr->args.g24.cond = cond;
  return true;
}

/* A4.1.116--A5.1.13
 * TEQ -- Data processing operands - Rotate right with extend */
static bool try_store_TEQ_M1_RRE(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  instr->args.g0.id = SLV6_TEQ_M1_RRE_ID;
  instr->args.g4.m = m;
  instr->args.g4.n = n;
  instr->args.g4.cond = cond;
  return true;
}

/* A4.1.117--A5.1.5
 * TST -- Data processing operands - Logical shift left by immediate */
static bool try_store_TST_M1_LSLImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  instr->args.g0.id = SLV6_TST_M1_LSLImm_ID;
  instr->args.g23.m = m;
  instr->args.g23.n = n;
  instr->args.g23.shift_imm = shift_imm;
  instr->args.g23.cond = cond;
  return true;
}

/* A4.1.117--A5.1.6
 * TST -- Data processing operands - Logical shift left by register */
static bool try_store_TST_M1_LSLReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_TST_M1_LSLReg_ID;
  instr->args.g24.m = m;
  instr->args.g24.n = n;
  instr->args.g24.s = s;
  instr->args.g24.cond = cond;
  return true;
}

/* A4.1.117--A5.1.7
 * TST -- Data processing operands - Logical shift right by immediate */
static bool try_store_TST_M1_LSRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_TST_M1_LSRImm_ID;
  instr->args.g23.m = m;
  instr->args.g23.n = n;
  instr->args.g23.shift_imm = shift_imm;
  instr->args.g23.cond = cond;
  return true;
}

/* A4.1.117--A5.1.8
 * TST -- Data processing operands - Logical shift right by register */
static bool try_store_TST_M1_LSRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_TST_M1_LSRReg_ID;
  instr->args.g24.m = m;
  instr->args.g24.n = n;
  instr->args.g24.s = s;
  instr->args.g24.cond = cond;
  return true;
}

/* A4.1.117--A5.1.9
 * TST -- Data processing operands - Arithmetic shift right by immediate */
static bool try_store_TST_M1_ASRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  instr->args.g0.id = SLV6_TST_M1_ASRImm_ID;
  instr->args.g23.m = m;
  instr->args.g23.n = n;
  instr->args.g23.shift_imm = shift_imm;
  instr->args.g23.cond = cond;
  return true;
}

/* A4.1.117--A5.1.10
 * TST -- Data processing operands - Arithmetic shift right by register */
static bool try_store_TST_M1_ASRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_TST_M1_ASRReg_ID;
  instr->args.g24.m = m;
  instr->args.g24.n = n;
  instr->args.g24.s = s;
  instr->args.g24.cond = cond;
  return true;
}

/* A4.1.117--A5.1.11
 * TST -- Data processing operands - Rotate right by immediate */
static bool try_store_TST_M1_RRImm(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t shift_imm = get_bits(bincode,11,7);
  if (!((shift_imm != 0))) return false;
  instr->args.g0.id = SLV6_TST_M1_RRImm_ID;
  instr->args.g23.m = m;
  instr->args.g23.n = n;
  instr->args.g23.shift_imm = shift_imm;
  instr->args.g23.cond = cond;
  return true;
}

/* A4.1.117--A5.1.12
 * TST -- Data processing operands - Rotate right by register */
static bool try_store_TST_M1_RRReg(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_TST_M1_RRReg_ID;
  instr->args.g24.m = m;
  instr->args.g24.n = n;
  instr->args.g24.s = s;
  instr->args.g24.cond = cond;
  return true;
}

/* A4.1.117--A5.1.13
 * TST -- Data processing operands - Rotate right with extend */
static bool try_store_TST_M1_RRE(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t m = get_bits(bincode,3,0);
  uint8_t n = get_bits(bincode,19,16);
  instr->args.g0.id = SLV6_TST_M1_RRE_ID;
  instr->args.g4.m = m;
  instr->args.g4.n = n;
  instr->args.g4.cond = cond;
  return true;
}

/* A4.1.118
 * UADD16 */
static bool try_store_UADD16(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_UADD16_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.119
 * UADD8 */
static bool try_store_UADD8(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_UADD8_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.120
 * UADDSUBX */
static bool try_store_UADDSUBX(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_UADDSUBX_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.121
 * UHADD16 */
static bool try_store_UHADD16(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_UHADD16_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.122
 * UHADD8 */
static bool try_store_UHADD8(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_UHADD8_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.123
 * UHADDSUBX */
static bool try_store_UHADDSUBX(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_UHADDSUBX_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.124
 * UHSUB16 */
static bool try_store_UHSUB16(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_UHSUB16_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.125
 * UHSUB8 */
static bool try_store_UHSUB8(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_UHSUB8_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.126
 * UHSUBADDX */
static bool try_store_UHSUBADDX(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_UHSUBADDX_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.127
 * UMAAL */
static bool try_store_UMAAL(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t dHi = get_bits(bincode,19,16);
  uint8_t dLo = get_bits(bincode,15,12);
  uint8_t s = get_bits(bincode,11,8);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((dHi != 15) && ((dLo != 15) && ((m != 15) && ((s != 15) && (dHi != dLo))))))) return false;
  instr->args.g0.id = SLV6_UMAAL_ID;
  instr->args.g16.dHi = dHi;
  instr->args.g16.dLo = dLo;
  instr->args.g16.m = m;
  instr->args.g16.s = s;
  instr->args.g16.cond = cond;
  return true;
}

/* A4.1.128
 * UMLAL */
static bool try_store_UMLAL(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  bool S = get_bit(bincode,20);
  uint8_t dHi = get_bits(bincode,19,16);
  uint8_t dLo = get_bits(bincode,15,12);
  uint8_t s = get_bits(bincode,11,8);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((dHi != 15) && ((dLo != 15) && ((m != 15) && ((s != 15) && (dHi != dLo))))))) return false;
  instr->args.g0.id = SLV6_UMLAL_ID;
  instr->args.g46.S = S;
  instr->args.g46.dHi = dHi;
  instr->args.g46.dLo = dLo;
  instr->args.g46.m = m;
  instr->args.g46.s = s;
  instr->args.g46.cond = cond;
  return true;
}

/* A4.1.129
 * UMULL */
static bool try_store_UMULL(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  bool S = get_bit(bincode,20);
  uint8_t dHi = get_bits(bincode,19,16);
  uint8_t dLo = get_bits(bincode,15,12);
  uint8_t s = get_bits(bincode,11,8);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((dHi != 15) && ((dLo != 15) && ((m != 15) && ((s != 15) && (dHi != dLo))))))) return false;
  instr->args.g0.id = SLV6_UMULL_ID;
  instr->args.g46.S = S;
  instr->args.g46.dHi = dHi;
  instr->args.g46.dLo = dLo;
  instr->args.g46.m = m;
  instr->args.g46.s = s;
  instr->args.g46.cond = cond;
  return true;
}

/* A4.1.130
 * UQADD16 */
static bool try_store_UQADD16(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_UQADD16_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.131
 * UQADD8 */
static bool try_store_UQADD8(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_UQADD8_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.132
 * UQADDSUBX */
static bool try_store_UQADDSUBX(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_UQADDSUBX_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.133
 * UQSUB16 */
static bool try_store_UQSUB16(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_UQSUB16_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.134
 * UQSUB8 */
static bool try_store_UQSUB8(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_UQSUB8_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.135
 * UQSUBADDX */
static bool try_store_UQSUBADDX(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_UQSUBADDX_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.136
 * USAD8 */
static bool try_store_USAD8(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,19,16);
  uint8_t s = get_bits(bincode,11,8);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (s != 15))))) return false;
  instr->args.g0.id = SLV6_USAD8_ID;
  instr->args.g14.d = d;
  instr->args.g14.m = m;
  instr->args.g14.s = s;
  instr->args.g14.cond = cond;
  return true;
}

/* A4.1.137
 * USADA8 */
static bool try_store_USADA8(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,19,16);
  uint8_t n = get_bits(bincode,15,12);
  uint8_t s = get_bits(bincode,11,8);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && ((s != 15) && (n != 15)))))) return false;
  instr->args.g0.id = SLV6_USADA8_ID;
  instr->args.g61.d = d;
  instr->args.g61.m = m;
  instr->args.g61.n = n;
  instr->args.g61.s = s;
  instr->args.g61.cond = cond;
  return true;
}

/* A4.1.138
 * USAT */
static bool try_store_USAT(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t sat_imm = get_bits(bincode,20,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t shift_imm = get_bits(bincode,11,7);
  uint8_t shift = get_bit(bincode,6);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && (m != 15)))) return false;
  instr->args.g0.id = SLV6_USAT_ID;
  instr->args.g56.d = d;
  instr->args.g56.m = m;
  instr->args.g56.sat_imm = sat_imm;
  instr->args.g56.shift = shift;
  instr->args.g56.shift_imm = shift_imm;
  instr->args.g56.cond = cond;
  return true;
}

/* A4.1.139
 * USAT16 */
static bool try_store_USAT16(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t sat_imm = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && (m != 15)))) return false;
  instr->args.g0.id = SLV6_USAT16_ID;
  instr->args.g57.d = d;
  instr->args.g57.m = m;
  instr->args.g57.sat_imm = sat_imm;
  instr->args.g57.cond = cond;
  return true;
}

/* A4.1.140
 * USUB16 */
static bool try_store_USUB16(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_USUB16_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.141
 * USUB8 */
static bool try_store_USUB8(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_USUB8_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.142
 * USUBADDX */
static bool try_store_USUBADDX(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_USUBADDX_ID;
  instr->args.g5.d = d;
  instr->args.g5.m = m;
  instr->args.g5.n = n;
  instr->args.g5.cond = cond;
  return true;
}

/* A4.1.143
 * UXTAB */
static bool try_store_UXTAB(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t rotate = get_bits(bincode,11,10);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_UXTAB_ID;
  instr->args.g59.d = d;
  instr->args.g59.m = m;
  instr->args.g59.n = n;
  instr->args.g59.rotate = rotate;
  instr->args.g59.cond = cond;
  return true;
}

/* A4.1.144
 * UXTAB16 */
static bool try_store_UXTAB16(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t rotate = get_bits(bincode,11,10);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_UXTAB16_ID;
  instr->args.g59.d = d;
  instr->args.g59.m = m;
  instr->args.g59.n = n;
  instr->args.g59.rotate = rotate;
  instr->args.g59.cond = cond;
  return true;
}

/* A4.1.145
 * UXTAH */
static bool try_store_UXTAH(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t n = get_bits(bincode,19,16);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t rotate = get_bits(bincode,11,10);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && ((m != 15) && (n != 15))))) return false;
  instr->args.g0.id = SLV6_UXTAH_ID;
  instr->args.g59.d = d;
  instr->args.g59.m = m;
  instr->args.g59.n = n;
  instr->args.g59.rotate = rotate;
  instr->args.g59.cond = cond;
  return true;
}

/* A4.1.146
 * UXTB */
static bool try_store_UXTB(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t rotate = get_bits(bincode,11,10);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && (m != 15)))) return false;
  instr->args.g0.id = SLV6_UXTB_ID;
  instr->args.g60.d = d;
  instr->args.g60.m = m;
  instr->args.g60.rotate = rotate;
  instr->args.g60.cond = cond;
  return true;
}

/* A4.1.147
 * UXTB16 */
static bool try_store_UXTB16(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t rotate = get_bits(bincode,11,10);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && (m != 15)))) return false;
  instr->args.g0.id = SLV6_UXTB16_ID;
  instr->args.g60.d = d;
  instr->args.g60.m = m;
  instr->args.g60.rotate = rotate;
  instr->args.g60.cond = cond;
  return true;
}

/* A4.1.148
 * UXTH */
static bool try_store_UXTH(struct SLv6_Instruction *instr, uint32_t bincode) {
  const uint32_t cond_tmp = get_bits(bincode,31,28);
  if (cond_tmp>14) return false;
  const SLv6_Condition cond =
    ((SLv6_Condition) cond_tmp);
  uint8_t d = get_bits(bincode,15,12);
  uint8_t rotate = get_bits(bincode,11,10);
  uint8_t m = get_bits(bincode,3,0);
  if (!(((d != 15) && (m != 15)))) return false;
  instr->args.g0.id = SLV6_UXTH_ID;
  instr->args.g60.d = d;
  instr->args.g60.m = m;
  instr->args.g60.rotate = rotate;
  instr->args.g60.cond = cond;
  return true;
}

/* the main function, used by the ISS loop */
void arm_decode_and_store(struct SLv6_Instruction *instr, uint32_t bincode) {
  bool found = false;
  const uint32_t c = bincode>>28;
  const uint32_t opcode = (c==15 ? 0x100 : 0) | (bincode<<4)>>24;
  switch (opcode) {
  case 0: /* 000000000 */
    if ((bincode&0x0f700ff0)==0x000000b0 && try_store_STRH_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x000000f0 && try_store_STRD_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x000000d0 && try_store_LDRD_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00000060 && try_store_AND_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00000070 && try_store_AND_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00000060 && try_store_AND_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00000050 && try_store_AND_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00000040 && try_store_AND_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00000030 && try_store_AND_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00000020 && try_store_AND_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00000010 && try_store_AND_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00000000 && try_store_AND_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x00000090 && try_store_MUL_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x00000000 && try_store_AND_M1_Reg_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 1: /* 000000001 */
    if ((bincode&0x0f700ff0)==0x001000f0 && try_store_LDRSH_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x001000d0 && try_store_LDRSB_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x001000b0 && try_store_LDRH_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00000060 && try_store_AND_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00000070 && try_store_AND_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00000060 && try_store_AND_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00000050 && try_store_AND_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00000040 && try_store_AND_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00000030 && try_store_AND_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00000020 && try_store_AND_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00000010 && try_store_AND_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00000000 && try_store_AND_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x00100090 && try_store_MUL_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x00100000 && try_store_AND_M1_Reg_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 2: /* 000000010 */
    if ((bincode&0x0fe000f0)==0x00200090 && try_store_MLA(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00200060 && try_store_EOR_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00200070 && try_store_EOR_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00200050 && try_store_EOR_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00200040 && try_store_EOR_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00200030 && try_store_EOR_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00200010 && try_store_EOR_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00200000 && try_store_EOR_M1_LSLImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00200020 && try_store_EOR_M1_LSRImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00200060 && try_store_EOR_M1_RRImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x00200000 && try_store_EOR_M1_Reg_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 3: /* 000000011 */
    if ((bincode&0x0fe000f0)==0x00200090 && try_store_MLA(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00200060 && try_store_EOR_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00200070 && try_store_EOR_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00200050 && try_store_EOR_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00200040 && try_store_EOR_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00200030 && try_store_EOR_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00200010 && try_store_EOR_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00300000 && try_store_EOR_M1_LSLImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00300020 && try_store_EOR_M1_LSRImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00300060 && try_store_EOR_M1_RRImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x00300000 && try_store_EOR_M1_Reg_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 4: /* 000000100 */
    if ((bincode&0x0ff000f0)==0x00400090 && try_store_UMAAL(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00400060 && try_store_SUB_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00400070 && try_store_SUB_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00400060 && try_store_SUB_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00400050 && try_store_SUB_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00400030 && try_store_SUB_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00400020 && try_store_SUB_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00400010 && try_store_SUB_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00400000 && try_store_SUB_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x004000b0 && try_store_STRH_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x004000f0 && try_store_STRD_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x004000d0 && try_store_LDRD_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00400040 && try_store_SUB_M1_ASRImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00400000 && try_store_SUB_M1_LSLImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 5: /* 000000101 */
    if ((bincode&0x0fe00ff0)==0x00400060 && try_store_SUB_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00400070 && try_store_SUB_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00400060 && try_store_SUB_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00400050 && try_store_SUB_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00400030 && try_store_SUB_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00400020 && try_store_SUB_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00400010 && try_store_SUB_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00400000 && try_store_SUB_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x005000f0 && try_store_LDRSH_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x005000d0 && try_store_LDRSB_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x005000b0 && try_store_LDRH_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00500040 && try_store_SUB_M1_ASRImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00500000 && try_store_SUB_M1_LSLImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 6: /* 000000110 */
    if ((bincode&0x0fe00ff0)==0x00600060 && try_store_RSB_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00600070 && try_store_RSB_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00600060 && try_store_RSB_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00600050 && try_store_RSB_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00600030 && try_store_RSB_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00600020 && try_store_RSB_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00600010 && try_store_RSB_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00600040 && try_store_RSB_M1_ASRImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00600000 && try_store_RSB_M1_LSLImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x00600000 && try_store_RSB_M1_Reg_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 7: /* 000000111 */
    if ((bincode&0x0fe00ff0)==0x00600060 && try_store_RSB_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00600070 && try_store_RSB_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00600060 && try_store_RSB_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00600050 && try_store_RSB_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00600030 && try_store_RSB_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00600020 && try_store_RSB_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00600010 && try_store_RSB_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00700040 && try_store_RSB_M1_ASRImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00700000 && try_store_RSB_M1_LSLImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x00700000 && try_store_RSB_M1_Reg_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 8: /* 000001000 */
    if ((bincode&0x0fe000f0)==0x00800090 && try_store_UMULL(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x000000b0 && try_store_STRH_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x000000f0 && try_store_STRD_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x000000d0 && try_store_LDRD_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00800060 && try_store_ADD_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00800070 && try_store_ADD_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00800050 && try_store_ADD_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00800040 && try_store_ADD_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00800030 && try_store_ADD_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00800010 && try_store_ADD_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00800020 && try_store_ADD_M1_LSRImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00800060 && try_store_ADD_M1_RRImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00800000 && try_store_ADD_M1_LSLImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x00800000 && try_store_ADD_M1_Reg_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 9: /* 000001001 */
    if ((bincode&0x0fe000f0)==0x00800090 && try_store_UMULL(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x001000f0 && try_store_LDRSH_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x001000d0 && try_store_LDRSB_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x001000b0 && try_store_LDRH_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00800060 && try_store_ADD_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00800070 && try_store_ADD_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00800050 && try_store_ADD_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00800040 && try_store_ADD_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00800030 && try_store_ADD_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00800010 && try_store_ADD_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00900020 && try_store_ADD_M1_LSRImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00900060 && try_store_ADD_M1_RRImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00900000 && try_store_ADD_M1_LSLImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x00900000 && try_store_ADD_M1_Reg_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 10: /* 000001010 */
    if ((bincode&0x0fe000f0)==0x00a00090 && try_store_UMLAL(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00a00060 && try_store_ADC_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00a00070 && try_store_ADC_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00a00060 && try_store_ADC_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00a00050 && try_store_ADC_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00a00040 && try_store_ADC_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00a00030 && try_store_ADC_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00a00020 && try_store_ADC_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00a00010 && try_store_ADC_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00a00000 && try_store_ADC_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x00a00000 && try_store_ADC_M1_Reg_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 11: /* 000001011 */
    if ((bincode&0x0fe000f0)==0x00a00090 && try_store_UMLAL(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00a00060 && try_store_ADC_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00a00070 && try_store_ADC_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00a00060 && try_store_ADC_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00a00050 && try_store_ADC_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00a00040 && try_store_ADC_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00a00030 && try_store_ADC_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00a00020 && try_store_ADC_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00a00010 && try_store_ADC_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00a00000 && try_store_ADC_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x00b00000 && try_store_ADC_M1_Reg_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 12: /* 000001100 */
    if ((bincode&0x0f7000f0)==0x004000b0 && try_store_STRH_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x004000f0 && try_store_STRD_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00c00060 && try_store_SBC_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00c00070 && try_store_SBC_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00c00060 && try_store_SBC_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00c00050 && try_store_SBC_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00c00040 && try_store_SBC_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00c00030 && try_store_SBC_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00c00020 && try_store_SBC_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00c00010 && try_store_SBC_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00c00000 && try_store_SBC_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00c00000 && try_store_SBC_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x004000d0 && try_store_LDRD_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff000f0)==0x00c00090 && try_store_SMULL_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 13: /* 000001101 */
    if ((bincode&0x0fe00ff0)==0x00c00060 && try_store_SBC_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00c00070 && try_store_SBC_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00c00060 && try_store_SBC_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00c00050 && try_store_SBC_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00c00040 && try_store_SBC_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00c00030 && try_store_SBC_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00c00020 && try_store_SBC_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00c00010 && try_store_SBC_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00c00000 && try_store_SBC_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00c00000 && try_store_SBC_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x005000f0 && try_store_LDRSH_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x005000d0 && try_store_LDRSB_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x005000b0 && try_store_LDRH_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff000f0)==0x00d00090 && try_store_SMULL_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 14: /* 000001110 */
  case 15: /* 000001111 */
    if ((bincode&0x0fe000f0)==0x00e00090 && try_store_SMLAL(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00e00060 && try_store_RSC_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00e00070 && try_store_RSC_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00e00060 && try_store_RSC_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00e00050 && try_store_RSC_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00e00040 && try_store_RSC_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00e00030 && try_store_RSC_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00e00020 && try_store_RSC_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00e00010 && try_store_RSC_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00e00000 && try_store_RSC_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00e00000 && try_store_RSC_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 16: /* 000010000 */
    if ((bincode&0x0ff00ff0)==0x01000090 && try_store_SWP(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x010000b0 && try_store_STRH_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x010000f0 && try_store_STRD_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00090)==0x01000080 && try_store_SMLAxy(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x01000050 && try_store_QADD(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fbf0fff)==0x010f0000 && try_store_MRS(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x010000d0 && try_store_LDRD_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 17: /* 000010001 */
    if ((bincode&0x0ff0fff0)==0x01100060 && try_store_TST_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01100070 && try_store_TST_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01100060 && try_store_TST_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01100050 && try_store_TST_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01100040 && try_store_TST_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01100030 && try_store_TST_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01100020 && try_store_TST_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01100010 && try_store_TST_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01100000 && try_store_TST_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x011000f0 && try_store_LDRSH_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x011000d0 && try_store_LDRSB_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x011000b0 && try_store_LDRH_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0fff0)==0x01100000 && try_store_TST_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 18: /* 000010010 */
    if ((bincode&0x0f700ff0)==0x012000b0 && try_store_STRH_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x012000f0 && try_store_STRD_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0b0)==0x012000a0 && try_store_SMULWy(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff000b0)==0x01200080 && try_store_SMLAWy(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x01200050 && try_store_QSUB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fb0fff0)==0x0120f000 && try_store_MSRreg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x012000d0 && try_store_LDRD_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ffffff0)==0x012fff20 && try_store_BXJ(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ffffff0)==0x012fff30 && try_store_BLX2(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0xfff000f0)==0xe1200070 && try_store_BKPT(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ffffff0)==0x012fff10 && try_store_BX(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 19: /* 000010011 */
    if ((bincode&0x0ff0fff0)==0x01300060 && try_store_TEQ_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01300070 && try_store_TEQ_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01300060 && try_store_TEQ_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01300050 && try_store_TEQ_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01300040 && try_store_TEQ_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01300030 && try_store_TEQ_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01300020 && try_store_TEQ_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01300010 && try_store_TEQ_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01300000 && try_store_TEQ_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0fff0)==0x01300000 && try_store_TEQ_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x013000f0 && try_store_LDRSH_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x013000d0 && try_store_LDRSB_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x013000b0 && try_store_LDRH_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 20: /* 000010100 */
    if ((bincode&0x0ff00ff0)==0x01400090 && try_store_SWPB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x014000b0 && try_store_STRH_M3_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x014000f0 && try_store_STRD_M3_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00090)==0x01400080 && try_store_SMLALxy(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x01400050 && try_store_QDADD(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fbf0fff)==0x010f0000 && try_store_MRS(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x014000d0 && try_store_LDRD_M3_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 21: /* 000010101 */
    if ((bincode&0x0f7000f0)==0x015000f0 && try_store_LDRSH_M3_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x015000d0 && try_store_LDRSB_M3_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0fff0)==0x01500060 && try_store_CMP_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01500070 && try_store_CMP_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01500060 && try_store_CMP_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01500050 && try_store_CMP_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01500040 && try_store_CMP_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01500030 && try_store_CMP_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01500020 && try_store_CMP_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01500010 && try_store_CMP_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01500000 && try_store_CMP_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff000f0)==0x015000b0 && try_store_LDRH_M3_ImmOff_U0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0fff0)==0x01500000 && try_store_CMP_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 22: /* 000010110 */
    if ((bincode&0x0f7000f0)==0x016000b0 && try_store_STRH_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x016000f0 && try_store_STRD_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f090)==0x01600080 && try_store_SMULxy(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x01600050 && try_store_QDSUB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fb0fff0)==0x0120f000 && try_store_MSRreg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x016000d0 && try_store_LDRD_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0ff0)==0x016f0f10 && try_store_CLZ(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 23: /* 000010111 */
    if ((bincode&0x0f7000f0)==0x017000f0 && try_store_LDRSH_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x017000d0 && try_store_LDRSB_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x017000b0 && try_store_LDRH_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0fff0)==0x01700060 && try_store_CMN_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01700070 && try_store_CMN_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01700060 && try_store_CMN_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01700050 && try_store_CMN_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01700040 && try_store_CMN_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01700030 && try_store_CMN_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01700020 && try_store_CMN_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01700010 && try_store_CMN_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01700000 && try_store_CMN_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0fff0)==0x01700000 && try_store_CMN_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 24: /* 000011000 */
    if ((bincode&0x0f700ff0)==0x010000b0 && try_store_STRH_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x01800f90 && try_store_STREX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x010000f0 && try_store_STRD_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x01800060 && try_store_ORR_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01800070 && try_store_ORR_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x01800060 && try_store_ORR_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01800050 && try_store_ORR_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01800030 && try_store_ORR_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01800010 && try_store_ORR_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x010000d0 && try_store_LDRD_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x01800040 && try_store_ORR_M1_ASRImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x01800020 && try_store_ORR_M1_LSRImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x01800000 && try_store_ORR_M1_LSLImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x01800000 && try_store_ORR_M1_Reg_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 25: /* 000011001 */
    if ((bincode&0x0fe00ff0)==0x01800060 && try_store_ORR_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01800070 && try_store_ORR_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x01800060 && try_store_ORR_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01800050 && try_store_ORR_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01800030 && try_store_ORR_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01800010 && try_store_ORR_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x011000f0 && try_store_LDRSH_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x011000d0 && try_store_LDRSB_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x011000b0 && try_store_LDRH_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00fff)==0x01900f9f && try_store_LDREX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x01900040 && try_store_ORR_M1_ASRImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x01900020 && try_store_ORR_M1_LSRImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x01900000 && try_store_ORR_M1_LSLImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x01900000 && try_store_ORR_M1_Reg_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 26: /* 000011010 */
    if ((bincode&0x0f700ff0)==0x012000b0 && try_store_STRH_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x012000f0 && try_store_STRD_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0ff0)==0x01a00060 && try_store_MOV_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01a00070 && try_store_MOV_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01a00050 && try_store_MOV_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0ff0)==0x01a00000 && try_store_MOV_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x012000d0 && try_store_LDRD_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff00f0)==0x01a00010 && try_store_MOV_M1_LSLReg_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0070)==0x01a00040 && try_store_MOV_M1_ASRImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff00f0)==0x01a00030 && try_store_MOV_M1_LSRReg_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0070)==0x01a00060 && try_store_MOV_M1_RRImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0070)==0x01a00000 && try_store_MOV_M1_LSLImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0ff0)==0x01a00000 && try_store_CPY(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0070)==0x01a00020 && try_store_MOV_M1_LSRImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 27: /* 000011011 */
    if ((bincode&0x0fef0ff0)==0x01a00060 && try_store_MOV_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01a00070 && try_store_MOV_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01a00050 && try_store_MOV_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0ff0)==0x01a00000 && try_store_MOV_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x013000f0 && try_store_LDRSH_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x013000d0 && try_store_LDRSB_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x013000b0 && try_store_LDRH_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff00f0)==0x01b00010 && try_store_MOV_M1_LSLReg_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0070)==0x01b00040 && try_store_MOV_M1_ASRImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff00f0)==0x01b00030 && try_store_MOV_M1_LSRReg_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0070)==0x01b00060 && try_store_MOV_M1_RRImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0070)==0x01b00000 && try_store_MOV_M1_LSLImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0070)==0x01b00020 && try_store_MOV_M1_LSRImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 28: /* 000011100 */
    if ((bincode&0x0f7000f0)==0x014000b0 && try_store_STRH_M3_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x014000f0 && try_store_STRD_M3_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x014000d0 && try_store_LDRD_M3_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x01c00060 && try_store_BIC_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01c00070 && try_store_BIC_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x01c00060 && try_store_BIC_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01c00050 && try_store_BIC_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x01c00040 && try_store_BIC_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01c00030 && try_store_BIC_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x01c00020 && try_store_BIC_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01c00010 && try_store_BIC_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x01c00000 && try_store_BIC_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x01c00000 && try_store_BIC_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 29: /* 000011101 */
    if ((bincode&0x0f7000f0)==0x015000f0 && try_store_LDRSH_M3_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x015000d0 && try_store_LDRSB_M3_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x01c00060 && try_store_BIC_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01c00070 && try_store_BIC_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x01c00060 && try_store_BIC_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01c00050 && try_store_BIC_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x01c00040 && try_store_BIC_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01c00030 && try_store_BIC_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x01c00020 && try_store_BIC_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01c00010 && try_store_BIC_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x01c00000 && try_store_BIC_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x01c00000 && try_store_BIC_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff000f0)==0x01d000b0 && try_store_LDRH_M3_ImmOff_U1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 30: /* 000011110 */
    if ((bincode&0x0f7000f0)==0x016000b0 && try_store_STRH_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x016000f0 && try_store_STRD_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0ff0)==0x01e00060 && try_store_MVN_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01e00070 && try_store_MVN_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0070)==0x01e00060 && try_store_MVN_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01e00050 && try_store_MVN_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0070)==0x01e00040 && try_store_MVN_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01e00030 && try_store_MVN_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0070)==0x01e00020 && try_store_MVN_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01e00010 && try_store_MVN_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0070)==0x01e00000 && try_store_MVN_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x016000d0 && try_store_LDRD_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0ff0)==0x01e00000 && try_store_MVN_M1_Reg_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 31: /* 000011111 */
    if ((bincode&0x0fef0ff0)==0x01e00060 && try_store_MVN_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01e00070 && try_store_MVN_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0070)==0x01e00060 && try_store_MVN_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01e00050 && try_store_MVN_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0070)==0x01e00040 && try_store_MVN_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01e00030 && try_store_MVN_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0070)==0x01e00020 && try_store_MVN_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01e00010 && try_store_MVN_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0070)==0x01e00000 && try_store_MVN_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x017000f0 && try_store_LDRSH_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x017000d0 && try_store_LDRSB_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x017000b0 && try_store_LDRH_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0ff0)==0x01f00000 && try_store_MVN_M1_Reg_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 32: /* 000100000 */
    if ((bincode&0x0ff00000)==0x02000000 && try_store_AND_M1_Imm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 33: /* 000100001 */
    if ((bincode&0x0ff00000)==0x02100000 && try_store_AND_M1_Imm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 34: /* 000100010 */
    if ((bincode&0x0ff00000)==0x02200000 && try_store_EOR_M1_Imm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 35: /* 000100011 */
    if ((bincode&0x0ff00000)==0x02300000 && try_store_EOR_M1_Imm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 36: /* 000100100 */
    if ((bincode&0x0ff00000)==0x02400000 && try_store_SUB_M1_Imm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 37: /* 000100101 */
    if ((bincode&0x0ff00000)==0x02500000 && try_store_SUB_M1_Imm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 38: /* 000100110 */
    if ((bincode&0x0ff00000)==0x02600000 && try_store_RSB_M1_Imm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 39: /* 000100111 */
    if ((bincode&0x0ff00000)==0x02700000 && try_store_RSB_M1_Imm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 40: /* 000101000 */
    if ((bincode&0x0ff00000)==0x02800000 && try_store_ADD_M1_Imm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 41: /* 000101001 */
    if ((bincode&0x0ff00000)==0x02900000 && try_store_ADD_M1_Imm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 42: /* 000101010 */
  case 43: /* 000101011 */
    if ((bincode&0x0fe00000)==0x02a00000 && try_store_ADC_M1_Imm(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 44: /* 000101100 */
  case 45: /* 000101101 */
    if ((bincode&0x0fe00000)==0x02c00000 && try_store_SBC_M1_Imm(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 46: /* 000101110 */
  case 47: /* 000101111 */
    if ((bincode&0x0fe00000)==0x02e00000 && try_store_RSC_M1_Imm(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 48: /* 000110000 */
    break;
  case 49: /* 000110001 */
    if ((bincode&0x0ff0f000)==0x03100000 && try_store_TST_M1_Imm(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 50: /* 000110010 */
    if ((bincode&0x0fb0f000)==0x0320f000 && try_store_MSRimm(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 51: /* 000110011 */
    if ((bincode&0x0ff0f000)==0x03300000 && try_store_TEQ_M1_Imm(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 52: /* 000110100 */
    break;
  case 53: /* 000110101 */
    if ((bincode&0x0ff0f000)==0x03500000 && try_store_CMP_M1_Imm(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 54: /* 000110110 */
    if ((bincode&0x0fb0f000)==0x0320f000 && try_store_MSRimm(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 55: /* 000110111 */
    if ((bincode&0x0ff0f000)==0x03700000 && try_store_CMN_M1_Imm(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 56: /* 000111000 */
    if ((bincode&0x0ff00000)==0x03800000 && try_store_ORR_M1_Imm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 57: /* 000111001 */
    if ((bincode&0x0ff00000)==0x03900000 && try_store_ORR_M1_Imm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 58: /* 000111010 */
    if ((bincode&0x0fff0000)==0x03a00000 && try_store_MOV_M1_Imm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 59: /* 000111011 */
    if ((bincode&0x0fff0000)==0x03b00000 && try_store_MOV_M1_Imm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 60: /* 000111100 */
    if ((bincode&0x0ff00000)==0x03c00000 && try_store_BIC_M1_Imm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 61: /* 000111101 */
    if ((bincode&0x0ff00000)==0x03d00000 && try_store_BIC_M1_Imm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 62: /* 000111110 */
    if ((bincode&0x0fff0000)==0x03e00000 && try_store_MVN_M1_Imm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 63: /* 000111111 */
    if ((bincode&0x0fff0000)==0x03f00000 && try_store_MVN_M1_Imm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 64: /* 001000000 */
    if ((bincode&0x0f700000)==0x04000000 && try_store_STR_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 65: /* 001000001 */
    if ((bincode&0x0f700000)==0x04100000 && try_store_LDR_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 66: /* 001000010 */
    if ((bincode&0x0f700000)==0x04200000 && try_store_STRT_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 67: /* 001000011 */
    if ((bincode&0x0f700000)==0x04300000 && try_store_LDRT_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 68: /* 001000100 */
    if ((bincode&0x0f700000)==0x04400000 && try_store_STRB_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 69: /* 001000101 */
    if ((bincode&0x0f700000)==0x04500000 && try_store_LDRB_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 70: /* 001000110 */
    if ((bincode&0x0f700000)==0x04600000 && try_store_STRBT_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 71: /* 001000111 */
    if ((bincode&0x0f700000)==0x04700000 && try_store_LDRBT_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 72: /* 001001000 */
    if ((bincode&0x0f700000)==0x04000000 && try_store_STR_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 73: /* 001001001 */
    if ((bincode&0x0f700000)==0x04100000 && try_store_LDR_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 74: /* 001001010 */
    if ((bincode&0x0f700000)==0x04200000 && try_store_STRT_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 75: /* 001001011 */
    if ((bincode&0x0f700000)==0x04300000 && try_store_LDRT_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 76: /* 001001100 */
    if ((bincode&0x0f700000)==0x04400000 && try_store_STRB_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 77: /* 001001101 */
    if ((bincode&0x0f700000)==0x04500000 && try_store_LDRB_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 78: /* 001001110 */
    if ((bincode&0x0f700000)==0x04600000 && try_store_STRBT_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 79: /* 001001111 */
    if ((bincode&0x0f700000)==0x04700000 && try_store_LDRBT_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 80: /* 001010000 */
    if ((bincode&0x0f700000)==0x05000000 && try_store_STR_M2_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 81: /* 001010001 */
    if ((bincode&0x0f700000)==0x05100000 && try_store_LDR_M2_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 82: /* 001010010 */
    if ((bincode&0x0f700000)==0x05200000 && try_store_STR_M2_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 83: /* 001010011 */
    if ((bincode&0x0f700000)==0x05300000 && try_store_LDR_M2_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 84: /* 001010100 */
    if ((bincode&0x0f700000)==0x05400000 && try_store_STRB_M2_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 85: /* 001010101 */
    if ((bincode&0x0f700000)==0x05500000 && try_store_LDRB_M2_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 86: /* 001010110 */
    if ((bincode&0x0f700000)==0x05600000 && try_store_STRB_M2_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 87: /* 001010111 */
    if ((bincode&0x0f700000)==0x05700000 && try_store_LDRB_M2_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 88: /* 001011000 */
    if ((bincode&0x0f700000)==0x05000000 && try_store_STR_M2_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 89: /* 001011001 */
    if ((bincode&0x0f700000)==0x05100000 && try_store_LDR_M2_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 90: /* 001011010 */
    if ((bincode&0x0f700000)==0x05200000 && try_store_STR_M2_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 91: /* 001011011 */
    if ((bincode&0x0f700000)==0x05300000 && try_store_LDR_M2_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 92: /* 001011100 */
    if ((bincode&0x0f700000)==0x05400000 && try_store_STRB_M2_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 93: /* 001011101 */
    if ((bincode&0x0f700000)==0x05500000 && try_store_LDRB_M2_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 94: /* 001011110 */
    if ((bincode&0x0f700000)==0x05600000 && try_store_STRB_M2_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 95: /* 001011111 */
    if ((bincode&0x0f700000)==0x05700000 && try_store_LDRB_M2_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 96: /* 001100000 */
    if ((bincode&0x0f700010)==0x06000000 && try_store_STR_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06000000 && try_store_STR_M2_Reg_postInd_U0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 97: /* 001100001 */
    if ((bincode&0x0ff00ff0)==0x06100f50 && try_store_SSUBADDX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06100ff0 && try_store_SSUB8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06100f70 && try_store_SSUB16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06100f30 && try_store_SADDSUBX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06100f90 && try_store_SADD8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06100f10 && try_store_SADD16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700010)==0x06100000 && try_store_LDR_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06100000 && try_store_LDR_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 98: /* 001100010 */
    if ((bincode&0x0f700010)==0x06200000 && try_store_STRT_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06200000 && try_store_STRT_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06200f50 && try_store_QSUBADDX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06200ff0 && try_store_QSUB8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06200f70 && try_store_QSUB16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06200f30 && try_store_QADDSUBX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06200f90 && try_store_QADD8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06200f10 && try_store_QADD16(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 99: /* 001100011 */
    if ((bincode&0x0ff00ff0)==0x06300f50 && try_store_SHSUBADDX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06300ff0 && try_store_SHSUB8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06300f70 && try_store_SHSUB16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06300f30 && try_store_SHADDSUBX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06300f90 && try_store_SHADD8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06300f10 && try_store_SHADD16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700010)==0x06300000 && try_store_LDRT_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06300000 && try_store_LDRT_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 100: /* 001100100 */
    if ((bincode&0x0f700010)==0x06400000 && try_store_STRB_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06400000 && try_store_STRB_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 101: /* 001100101 */
    if ((bincode&0x0ff00ff0)==0x06500f50 && try_store_USUBADDX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06500ff0 && try_store_USUB8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06500f70 && try_store_USUB16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06500f30 && try_store_UADDSUBX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06500f90 && try_store_UADD8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06500f10 && try_store_UADD16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700010)==0x06500000 && try_store_LDRB_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06500000 && try_store_LDRB_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 102: /* 001100110 */
    if ((bincode&0x0ff00ff0)==0x06600f50 && try_store_UQSUBADDX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06600ff0 && try_store_UQSUB8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06600f70 && try_store_UQSUB16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06600f30 && try_store_UQADDSUBX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06600f90 && try_store_UQADD8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06600f10 && try_store_UQADD16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700010)==0x06600000 && try_store_STRBT_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06600000 && try_store_STRBT_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 103: /* 001100111 */
    if ((bincode&0x0ff00ff0)==0x06700f50 && try_store_UHSUBADDX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06700ff0 && try_store_UHSUB8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06700f70 && try_store_UHSUB16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06700f30 && try_store_UHADDSUBX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06700f90 && try_store_UHADD8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06700f10 && try_store_UHADD16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700010)==0x06700000 && try_store_LDRBT_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06700000 && try_store_LDRBT_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 104: /* 001101000 */
    if ((bincode&0x0fff03f0)==0x068f0070 && try_store_SXTB16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff003f0)==0x06800070 && try_store_SXTAB16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700010)==0x06000000 && try_store_STR_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06800fb0 && try_store_SEL(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x06800050 && try_store_PKHTB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x06800010 && try_store_PKHBT(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06800000 && try_store_STR_M2_Reg_postInd_U1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 105: /* 001101001 */
    if ((bincode&0x0f700010)==0x06100000 && try_store_LDR_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06100000 && try_store_LDR_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 106: /* 001101010 */
    if ((bincode&0x0fff03f0)==0x06af0070 && try_store_SXTB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff003f0)==0x06a00070 && try_store_SXTAB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700010)==0x06200000 && try_store_STRT_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06200000 && try_store_STRT_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06a00f30 && try_store_SSAT16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00030)==0x06a00010 && try_store_SSAT(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 107: /* 001101011 */
    if ((bincode&0x0fff03f0)==0x06bf0070 && try_store_SXTH(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff003f0)==0x06b00070 && try_store_SXTAH(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00030)==0x06a00010 && try_store_SSAT(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0ff0)==0x06bf0fb0 && try_store_REV16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0ff0)==0x06bf0f30 && try_store_REV(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700010)==0x06300000 && try_store_LDRT_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06300000 && try_store_LDRT_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 108: /* 001101100 */
    if ((bincode&0x0fff03f0)==0x06cf0070 && try_store_UXTB16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff003f0)==0x06c00070 && try_store_UXTAB16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700010)==0x06400000 && try_store_STRB_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06400000 && try_store_STRB_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 109: /* 001101101 */
    if ((bincode&0x0f700010)==0x06500000 && try_store_LDRB_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06500000 && try_store_LDRB_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 110: /* 001101110 */
    if ((bincode&0x0fff03f0)==0x06ef0070 && try_store_UXTB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff003f0)==0x06e00070 && try_store_UXTAB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06e00f30 && try_store_USAT16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00030)==0x06e00010 && try_store_USAT(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700010)==0x06600000 && try_store_STRBT_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06600000 && try_store_STRBT_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 111: /* 001101111 */
    if ((bincode&0x0fff03f0)==0x06ff0070 && try_store_UXTH(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff003f0)==0x06f00070 && try_store_UXTAH(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00030)==0x06e00010 && try_store_USAT(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0ff0)==0x06ff0fb0 && try_store_REVSH(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700010)==0x06700000 && try_store_LDRBT_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06700000 && try_store_LDRBT_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 112: /* 001110000 */
    if ((bincode&0x0ff0f0d0)==0x0700f050 && try_store_SMUSD(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0d0)==0x0700f010 && try_store_SMUAD(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff000d0)==0x07000050 && try_store_SMLSD(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff000d0)==0x07000010 && try_store_SMLAD(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x07000000 && try_store_STR_M2_RegOff_U0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00010)==0x07000000 && try_store_STR_M2_ScRegOff_U0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 113: /* 001110001 */
    if ((bincode&0x0ff00ff0)==0x07100000 && try_store_LDR_M2_RegOff_U0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00010)==0x07100000 && try_store_LDR_M2_ScRegOff_U0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 114: /* 001110010 */
    if ((bincode&0x0f700010)==0x07200000 && try_store_STR_M2_ScReg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x07200000 && try_store_STR_M2_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 115: /* 001110011 */
    if ((bincode&0x0f700010)==0x07300000 && try_store_LDR_M2_ScReg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x07300000 && try_store_LDR_M2_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 116: /* 001110100 */
    if ((bincode&0x0f700010)==0x07400000 && try_store_STRB_M2_ScRegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff000d0)==0x07400050 && try_store_SMLSLD(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff000d0)==0x07400010 && try_store_SMLALD(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x07400000 && try_store_STRB_M2_RegOff_U0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 117: /* 001110101 */
    if ((bincode&0x0ff0f0d0)==0x0750f010 && try_store_SMMUL(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff000d0)==0x075000d0 && try_store_SMMLS(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff000d0)==0x07500010 && try_store_SMMLA(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00010)==0x07500000 && try_store_LDRB_M2_ScRegOff_U0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x07500000 && try_store_LDRB_M2_RegOff_U0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 118: /* 001110110 */
    if ((bincode&0x0f700010)==0x07600000 && try_store_STRB_M2_ScReg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x07600000 && try_store_STRB_M2_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 119: /* 001110111 */
    if ((bincode&0x0f700010)==0x07700000 && try_store_LDRB_M2_ScReg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x07700000 && try_store_LDRB_M2_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 120: /* 001111000 */
    if ((bincode&0x0ff000f0)==0x07800010 && try_store_USADA8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x0780f010 && try_store_USAD8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x07800000 && try_store_STR_M2_RegOff_U1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00010)==0x07800000 && try_store_STR_M2_ScRegOff_U1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 121: /* 001111001 */
    if ((bincode&0x0ff00ff0)==0x07900000 && try_store_LDR_M2_RegOff_U1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00010)==0x07900000 && try_store_LDR_M2_ScRegOff_U1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 122: /* 001111010 */
    if ((bincode&0x0f700010)==0x07200000 && try_store_STR_M2_ScReg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x07200000 && try_store_STR_M2_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 123: /* 001111011 */
    if ((bincode&0x0f700010)==0x07300000 && try_store_LDR_M2_ScReg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x07300000 && try_store_LDR_M2_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 124: /* 001111100 */
    if ((bincode&0x0f700010)==0x07400000 && try_store_STRB_M2_ScRegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x07c00000 && try_store_STRB_M2_RegOff_U1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 125: /* 001111101 */
    if ((bincode&0x0ff00010)==0x07d00000 && try_store_LDRB_M2_ScRegOff_U1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x07d00000 && try_store_LDRB_M2_RegOff_U1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 126: /* 001111110 */
    if ((bincode&0x0f700010)==0x07600000 && try_store_STRB_M2_ScReg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x07600000 && try_store_STRB_M2_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 127: /* 001111111 */
    if ((bincode&0x0f700010)==0x07700000 && try_store_LDRB_M2_ScReg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x07700000 && try_store_LDRB_M2_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 128: /* 010000000 */
    if ((bincode&0x0fd00000)==0x08000000 && try_store_STM1_M4_DA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 129: /* 010000001 */
    if ((bincode&0x0fd00000)==0x08100000 && try_store_LDM1_M4_DA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 130: /* 010000010 */
    if ((bincode&0x0fd00000)==0x08000000 && try_store_STM1_M4_DA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 131: /* 010000011 */
    if ((bincode&0x0fd00000)==0x08100000 && try_store_LDM1_M4_DA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 132: /* 010000100 */
    if ((bincode&0x0ff00000)==0x08400000 && try_store_STM2_M4_DA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 133: /* 010000101 */
    if ((bincode&0x0fd08000)==0x08508000 && try_store_LDM3_M4_DA(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff08000)==0x08500000 && try_store_LDM2_M4_DA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 134: /* 010000110 */
    break;
  case 135: /* 010000111 */
    if ((bincode&0x0fd08000)==0x08508000 && try_store_LDM3_M4_DA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 136: /* 010001000 */
    if ((bincode&0x0ff00000)==0x08800000 && try_store_STM1_M4_IA_W0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 137: /* 010001001 */
    if ((bincode&0x0ff00000)==0x08900000 && try_store_LDM1_M4_IA_W0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 138: /* 010001010 */
    if ((bincode&0x0ff00000)==0x08a00000 && try_store_STM1_M4_IA_W1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 139: /* 010001011 */
    if ((bincode&0x0ff00000)==0x08b00000 && try_store_LDM1_M4_IA_W1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 140: /* 010001100 */
    if ((bincode&0x0ff00000)==0x08c00000 && try_store_STM2_M4_IA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 141: /* 010001101 */
    if ((bincode&0x0fd08000)==0x08d08000 && try_store_LDM3_M4_IA(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff08000)==0x08d00000 && try_store_LDM2_M4_IA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 142: /* 010001110 */
    break;
  case 143: /* 010001111 */
    if ((bincode&0x0fd08000)==0x08d08000 && try_store_LDM3_M4_IA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 144: /* 010010000 */
    if ((bincode&0x0ff00000)==0x09000000 && try_store_STM1_M4_DB_W0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 145: /* 010010001 */
    if ((bincode&0x0fd00000)==0x09100000 && try_store_LDM1_M4_DB(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 146: /* 010010010 */
    if ((bincode&0x0ff00000)==0x09200000 && try_store_STM1_M4_DB_W1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 147: /* 010010011 */
    if ((bincode&0x0fd00000)==0x09100000 && try_store_LDM1_M4_DB(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 148: /* 010010100 */
    if ((bincode&0x0ff00000)==0x09400000 && try_store_STM2_M4_DB(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 149: /* 010010101 */
    if ((bincode&0x0fd08000)==0x09508000 && try_store_LDM3_M4_DB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff08000)==0x09500000 && try_store_LDM2_M4_DB(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 150: /* 010010110 */
    break;
  case 151: /* 010010111 */
    if ((bincode&0x0fd08000)==0x09508000 && try_store_LDM3_M4_DB(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 152: /* 010011000 */
    if ((bincode&0x0ff00000)==0x09800000 && try_store_STM1_M4_IB_W0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 153: /* 010011001 */
    if ((bincode&0x0ff00000)==0x09900000 && try_store_LDM1_M4_IB_W0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 154: /* 010011010 */
    if ((bincode&0x0ff00000)==0x09a00000 && try_store_STM1_M4_IB_W1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 155: /* 010011011 */
    if ((bincode&0x0ff00000)==0x09b00000 && try_store_LDM1_M4_IB_W1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 156: /* 010011100 */
    if ((bincode&0x0ff00000)==0x09c00000 && try_store_STM2_M4_IB(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 157: /* 010011101 */
    if ((bincode&0x0fd08000)==0x09d08000 && try_store_LDM3_M4_IB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff08000)==0x09d00000 && try_store_LDM2_M4_IB(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 158: /* 010011110 */
    break;
  case 159: /* 010011111 */
    if ((bincode&0x0fd08000)==0x09d08000 && try_store_LDM3_M4_IB(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 160: /* 010100000 */
  case 161: /* 010100001 */
  case 162: /* 010100010 */
  case 163: /* 010100011 */
  case 164: /* 010100100 */
  case 165: /* 010100101 */
  case 166: /* 010100110 */
  case 167: /* 010100111 */
  case 168: /* 010101000 */
  case 169: /* 010101001 */
  case 170: /* 010101010 */
  case 171: /* 010101011 */
  case 172: /* 010101100 */
  case 173: /* 010101101 */
  case 174: /* 010101110 */
  case 175: /* 010101111 */
    if ((bincode&0x0f000000)==0x0a000000 && try_store_B_L0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 176: /* 010110000 */
  case 177: /* 010110001 */
  case 178: /* 010110010 */
  case 179: /* 010110011 */
  case 180: /* 010110100 */
  case 181: /* 010110101 */
  case 182: /* 010110110 */
  case 183: /* 010110111 */
  case 184: /* 010111000 */
  case 185: /* 010111001 */
  case 186: /* 010111010 */
  case 187: /* 010111011 */
  case 188: /* 010111100 */
  case 189: /* 010111101 */
  case 190: /* 010111110 */
  case 191: /* 010111111 */
    if ((bincode&0x0f000000)==0x0b000000 && try_store_B_L1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 192: /* 011000000 */
    if ((bincode&0x0f300000)==0x0c000000 && try_store_STC_M5_U(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 193: /* 011000001 */
    if ((bincode&0x0f300000)==0x0c100000 && try_store_LDC_M5_U(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 194: /* 011000010 */
    if ((bincode&0x0f300000)==0x0c200000 && try_store_STC_M5_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 195: /* 011000011 */
    if ((bincode&0x0f300000)==0x0c300000 && try_store_LDC_M5_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 196: /* 011000100 */
    if ((bincode&0x0f300000)==0x0c000000 && try_store_STC_M5_U(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00000)==0x0c400000 && try_store_MCRR(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 197: /* 011000101 */
    if ((bincode&0x0ff00000)==0x0c500000 && try_store_MRRC(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f300000)==0x0c100000 && try_store_LDC_M5_U(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 198: /* 011000110 */
    if ((bincode&0x0f300000)==0x0c200000 && try_store_STC_M5_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 199: /* 011000111 */
    if ((bincode&0x0f300000)==0x0c300000 && try_store_LDC_M5_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 200: /* 011001000 */
    if ((bincode&0x0f300000)==0x0c000000 && try_store_STC_M5_U(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 201: /* 011001001 */
    if ((bincode&0x0f300000)==0x0c100000 && try_store_LDC_M5_U(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 202: /* 011001010 */
    if ((bincode&0x0f300000)==0x0c200000 && try_store_STC_M5_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 203: /* 011001011 */
    if ((bincode&0x0f300000)==0x0c300000 && try_store_LDC_M5_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 204: /* 011001100 */
    if ((bincode&0x0f300000)==0x0c000000 && try_store_STC_M5_U(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 205: /* 011001101 */
    if ((bincode&0x0f300000)==0x0c100000 && try_store_LDC_M5_U(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 206: /* 011001110 */
    if ((bincode&0x0f300000)==0x0c200000 && try_store_STC_M5_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 207: /* 011001111 */
    if ((bincode&0x0f300000)==0x0c300000 && try_store_LDC_M5_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 208: /* 011010000 */
    if ((bincode&0x0f300000)==0x0d000000 && try_store_STC_M5_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 209: /* 011010001 */
    if ((bincode&0x0f300000)==0x0d100000 && try_store_LDC_M5_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 210: /* 011010010 */
    if ((bincode&0x0f300000)==0x0d200000 && try_store_STC_M5_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 211: /* 011010011 */
    if ((bincode&0x0f300000)==0x0d300000 && try_store_LDC_M5_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 212: /* 011010100 */
    if ((bincode&0x0f300000)==0x0d000000 && try_store_STC_M5_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 213: /* 011010101 */
    if ((bincode&0x0f300000)==0x0d100000 && try_store_LDC_M5_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 214: /* 011010110 */
    if ((bincode&0x0f300000)==0x0d200000 && try_store_STC_M5_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 215: /* 011010111 */
    if ((bincode&0x0f300000)==0x0d300000 && try_store_LDC_M5_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 216: /* 011011000 */
    if ((bincode&0x0f300000)==0x0d000000 && try_store_STC_M5_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 217: /* 011011001 */
    if ((bincode&0x0f300000)==0x0d100000 && try_store_LDC_M5_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 218: /* 011011010 */
    if ((bincode&0x0f300000)==0x0d200000 && try_store_STC_M5_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 219: /* 011011011 */
    if ((bincode&0x0f300000)==0x0d300000 && try_store_LDC_M5_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 220: /* 011011100 */
    if ((bincode&0x0f300000)==0x0d000000 && try_store_STC_M5_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 221: /* 011011101 */
    if ((bincode&0x0f300000)==0x0d100000 && try_store_LDC_M5_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 222: /* 011011110 */
    if ((bincode&0x0f300000)==0x0d200000 && try_store_STC_M5_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 223: /* 011011111 */
    if ((bincode&0x0f300000)==0x0d300000 && try_store_LDC_M5_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 224: /* 011100000 */
    if ((bincode&0x0f100010)==0x0e000010 && try_store_MCR(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 225: /* 011100001 */
    if ((bincode&0x0f100010)==0x0e100010 && try_store_MRC(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 226: /* 011100010 */
    if ((bincode&0x0f100010)==0x0e000010 && try_store_MCR(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 227: /* 011100011 */
    if ((bincode&0x0f100010)==0x0e100010 && try_store_MRC(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 228: /* 011100100 */
    if ((bincode&0x0f100010)==0x0e000010 && try_store_MCR(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 229: /* 011100101 */
    if ((bincode&0x0f100010)==0x0e100010 && try_store_MRC(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 230: /* 011100110 */
    if ((bincode&0x0f100010)==0x0e000010 && try_store_MCR(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 231: /* 011100111 */
    if ((bincode&0x0f100010)==0x0e100010 && try_store_MRC(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 232: /* 011101000 */
    if ((bincode&0x0f100010)==0x0e000010 && try_store_MCR(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 233: /* 011101001 */
    if ((bincode&0x0f100010)==0x0e100010 && try_store_MRC(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 234: /* 011101010 */
    if ((bincode&0x0f100010)==0x0e000010 && try_store_MCR(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 235: /* 011101011 */
    if ((bincode&0x0f100010)==0x0e100010 && try_store_MRC(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 236: /* 011101100 */
    if ((bincode&0x0f100010)==0x0e000010 && try_store_MCR(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 237: /* 011101101 */
    if ((bincode&0x0f100010)==0x0e100010 && try_store_MRC(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 238: /* 011101110 */
    if ((bincode&0x0f100010)==0x0e000010 && try_store_MCR(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 239: /* 011101111 */
    if ((bincode&0x0f100010)==0x0e100010 && try_store_MRC(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 240: /* 011110000 */
  case 241: /* 011110001 */
  case 242: /* 011110010 */
  case 243: /* 011110011 */
  case 244: /* 011110100 */
  case 245: /* 011110101 */
  case 246: /* 011110110 */
  case 247: /* 011110111 */
  case 248: /* 011111000 */
  case 249: /* 011111001 */
  case 250: /* 011111010 */
  case 251: /* 011111011 */
  case 252: /* 011111100 */
  case 253: /* 011111101 */
  case 254: /* 011111110 */
  case 255: /* 011111111 */
    if ((bincode&0x0f000000)==0x0f000000 && try_store_SWI(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 256: /* 100000000 */
    if ((bincode&0x0f700ff0)==0x000000b0 && try_store_STRH_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x000000f0 && try_store_STRD_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x000000d0 && try_store_LDRD_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00000060 && try_store_AND_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00000070 && try_store_AND_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00000060 && try_store_AND_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00000050 && try_store_AND_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00000040 && try_store_AND_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00000030 && try_store_AND_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00000020 && try_store_AND_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00000010 && try_store_AND_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00000000 && try_store_AND_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x00000090 && try_store_MUL_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x00000000 && try_store_AND_M1_Reg_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 257: /* 100000001 */
    if ((bincode&0x0f700ff0)==0x001000f0 && try_store_LDRSH_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x001000d0 && try_store_LDRSB_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x001000b0 && try_store_LDRH_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00000060 && try_store_AND_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00000070 && try_store_AND_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00000060 && try_store_AND_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00000050 && try_store_AND_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00000040 && try_store_AND_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00000030 && try_store_AND_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00000020 && try_store_AND_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00000010 && try_store_AND_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00000000 && try_store_AND_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x00100090 && try_store_MUL_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x00100000 && try_store_AND_M1_Reg_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 258: /* 100000010 */
    if ((bincode&0x0fe000f0)==0x00200090 && try_store_MLA(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00200060 && try_store_EOR_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00200070 && try_store_EOR_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00200050 && try_store_EOR_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00200040 && try_store_EOR_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00200030 && try_store_EOR_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00200010 && try_store_EOR_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00200000 && try_store_EOR_M1_LSLImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00200020 && try_store_EOR_M1_LSRImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00200060 && try_store_EOR_M1_RRImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x00200000 && try_store_EOR_M1_Reg_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 259: /* 100000011 */
    if ((bincode&0x0fe000f0)==0x00200090 && try_store_MLA(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00200060 && try_store_EOR_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00200070 && try_store_EOR_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00200050 && try_store_EOR_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00200040 && try_store_EOR_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00200030 && try_store_EOR_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00200010 && try_store_EOR_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00300000 && try_store_EOR_M1_LSLImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00300020 && try_store_EOR_M1_LSRImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00300060 && try_store_EOR_M1_RRImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x00300000 && try_store_EOR_M1_Reg_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 260: /* 100000100 */
    if ((bincode&0x0ff000f0)==0x00400090 && try_store_UMAAL(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00400060 && try_store_SUB_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00400070 && try_store_SUB_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00400060 && try_store_SUB_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00400050 && try_store_SUB_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00400030 && try_store_SUB_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00400020 && try_store_SUB_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00400010 && try_store_SUB_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00400000 && try_store_SUB_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x004000b0 && try_store_STRH_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x004000f0 && try_store_STRD_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x004000d0 && try_store_LDRD_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00400040 && try_store_SUB_M1_ASRImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00400000 && try_store_SUB_M1_LSLImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 261: /* 100000101 */
    if ((bincode&0x0fe00ff0)==0x00400060 && try_store_SUB_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00400070 && try_store_SUB_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00400060 && try_store_SUB_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00400050 && try_store_SUB_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00400030 && try_store_SUB_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00400020 && try_store_SUB_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00400010 && try_store_SUB_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00400000 && try_store_SUB_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x005000f0 && try_store_LDRSH_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x005000d0 && try_store_LDRSB_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x005000b0 && try_store_LDRH_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00500040 && try_store_SUB_M1_ASRImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00500000 && try_store_SUB_M1_LSLImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 262: /* 100000110 */
    if ((bincode&0x0fe00ff0)==0x00600060 && try_store_RSB_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00600070 && try_store_RSB_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00600060 && try_store_RSB_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00600050 && try_store_RSB_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00600030 && try_store_RSB_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00600020 && try_store_RSB_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00600010 && try_store_RSB_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00600040 && try_store_RSB_M1_ASRImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00600000 && try_store_RSB_M1_LSLImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x00600000 && try_store_RSB_M1_Reg_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 263: /* 100000111 */
    if ((bincode&0x0fe00ff0)==0x00600060 && try_store_RSB_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00600070 && try_store_RSB_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00600060 && try_store_RSB_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00600050 && try_store_RSB_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00600030 && try_store_RSB_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00600020 && try_store_RSB_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00600010 && try_store_RSB_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00700040 && try_store_RSB_M1_ASRImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00700000 && try_store_RSB_M1_LSLImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x00700000 && try_store_RSB_M1_Reg_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 264: /* 100001000 */
    if ((bincode&0x0fe000f0)==0x00800090 && try_store_UMULL(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x000000b0 && try_store_STRH_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x000000f0 && try_store_STRD_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x000000d0 && try_store_LDRD_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00800060 && try_store_ADD_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00800070 && try_store_ADD_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00800050 && try_store_ADD_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00800040 && try_store_ADD_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00800030 && try_store_ADD_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00800010 && try_store_ADD_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00800020 && try_store_ADD_M1_LSRImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00800060 && try_store_ADD_M1_RRImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00800000 && try_store_ADD_M1_LSLImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x00800000 && try_store_ADD_M1_Reg_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 265: /* 100001001 */
    if ((bincode&0x0fe000f0)==0x00800090 && try_store_UMULL(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x001000f0 && try_store_LDRSH_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x001000d0 && try_store_LDRSB_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x001000b0 && try_store_LDRH_M3_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00800060 && try_store_ADD_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00800070 && try_store_ADD_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00800050 && try_store_ADD_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00800040 && try_store_ADD_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00800030 && try_store_ADD_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00800010 && try_store_ADD_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00900020 && try_store_ADD_M1_LSRImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00900060 && try_store_ADD_M1_RRImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x00900000 && try_store_ADD_M1_LSLImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x00900000 && try_store_ADD_M1_Reg_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 266: /* 100001010 */
    if ((bincode&0x0fe000f0)==0x00a00090 && try_store_UMLAL(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00a00060 && try_store_ADC_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00a00070 && try_store_ADC_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00a00060 && try_store_ADC_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00a00050 && try_store_ADC_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00a00040 && try_store_ADC_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00a00030 && try_store_ADC_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00a00020 && try_store_ADC_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00a00010 && try_store_ADC_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00a00000 && try_store_ADC_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x00a00000 && try_store_ADC_M1_Reg_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 267: /* 100001011 */
    if ((bincode&0x0fe000f0)==0x00a00090 && try_store_UMLAL(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00a00060 && try_store_ADC_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00a00070 && try_store_ADC_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00a00060 && try_store_ADC_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00a00050 && try_store_ADC_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00a00040 && try_store_ADC_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00a00030 && try_store_ADC_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00a00020 && try_store_ADC_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00a00010 && try_store_ADC_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00a00000 && try_store_ADC_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x00b00000 && try_store_ADC_M1_Reg_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 268: /* 100001100 */
    if ((bincode&0x0f7000f0)==0x004000b0 && try_store_STRH_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x004000f0 && try_store_STRD_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00c00060 && try_store_SBC_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00c00070 && try_store_SBC_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00c00060 && try_store_SBC_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00c00050 && try_store_SBC_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00c00040 && try_store_SBC_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00c00030 && try_store_SBC_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00c00020 && try_store_SBC_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00c00010 && try_store_SBC_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00c00000 && try_store_SBC_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00c00000 && try_store_SBC_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x004000d0 && try_store_LDRD_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff000f0)==0x00c00090 && try_store_SMULL_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 269: /* 100001101 */
    if ((bincode&0x0fe00ff0)==0x00c00060 && try_store_SBC_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00c00070 && try_store_SBC_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00c00060 && try_store_SBC_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00c00050 && try_store_SBC_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00c00040 && try_store_SBC_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00c00030 && try_store_SBC_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00c00020 && try_store_SBC_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00c00010 && try_store_SBC_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00c00000 && try_store_SBC_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00c00000 && try_store_SBC_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x005000f0 && try_store_LDRSH_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x005000d0 && try_store_LDRSB_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x005000b0 && try_store_LDRH_M3_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff000f0)==0x00d00090 && try_store_SMULL_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 270: /* 100001110 */
  case 271: /* 100001111 */
    if ((bincode&0x0fe000f0)==0x00e00090 && try_store_SMLAL(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00e00060 && try_store_RSC_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00e00070 && try_store_RSC_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00e00060 && try_store_RSC_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00e00050 && try_store_RSC_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00e00040 && try_store_RSC_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00e00030 && try_store_RSC_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00e00020 && try_store_RSC_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x00e00010 && try_store_RSC_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x00e00000 && try_store_RSC_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x00e00000 && try_store_RSC_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 272: /* 100010000 */
    if ((bincode&0x0ff00ff0)==0x01000090 && try_store_SWP(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x010000b0 && try_store_STRH_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x010000f0 && try_store_STRD_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00090)==0x01000080 && try_store_SMLAxy(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0xfffffdff)==0xf1010000 && try_store_SETEND(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x01000050 && try_store_QADD(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fbf0fff)==0x010f0000 && try_store_MRS(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x010000d0 && try_store_LDRD_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0xfff1fe20)==0xf1000000 && try_store_CPS(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 273: /* 100010001 */
    if ((bincode&0x0ff0fff0)==0x01100060 && try_store_TST_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01100070 && try_store_TST_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01100060 && try_store_TST_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01100050 && try_store_TST_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01100040 && try_store_TST_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01100030 && try_store_TST_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01100020 && try_store_TST_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01100010 && try_store_TST_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01100000 && try_store_TST_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x011000f0 && try_store_LDRSH_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x011000d0 && try_store_LDRSB_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x011000b0 && try_store_LDRH_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0fff0)==0x01100000 && try_store_TST_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 274: /* 100010010 */
    if ((bincode&0x0f700ff0)==0x012000b0 && try_store_STRH_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x012000f0 && try_store_STRD_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0b0)==0x012000a0 && try_store_SMULWy(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff000b0)==0x01200080 && try_store_SMLAWy(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x01200050 && try_store_QSUB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fb0fff0)==0x0120f000 && try_store_MSRreg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x012000d0 && try_store_LDRD_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ffffff0)==0x012fff20 && try_store_BXJ(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ffffff0)==0x012fff30 && try_store_BLX2(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0xfff000f0)==0xe1200070 && try_store_BKPT(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ffffff0)==0x012fff10 && try_store_BX(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 275: /* 100010011 */
    if ((bincode&0x0ff0fff0)==0x01300060 && try_store_TEQ_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01300070 && try_store_TEQ_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01300060 && try_store_TEQ_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01300050 && try_store_TEQ_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01300040 && try_store_TEQ_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01300030 && try_store_TEQ_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01300020 && try_store_TEQ_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01300010 && try_store_TEQ_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01300000 && try_store_TEQ_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0fff0)==0x01300000 && try_store_TEQ_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x013000f0 && try_store_LDRSH_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x013000d0 && try_store_LDRSB_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x013000b0 && try_store_LDRH_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 276: /* 100010100 */
    if ((bincode&0x0ff00ff0)==0x01400090 && try_store_SWPB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x014000b0 && try_store_STRH_M3_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x014000f0 && try_store_STRD_M3_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00090)==0x01400080 && try_store_SMLALxy(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x01400050 && try_store_QDADD(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fbf0fff)==0x010f0000 && try_store_MRS(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x014000d0 && try_store_LDRD_M3_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 277: /* 100010101 */
    if ((bincode&0x0f7000f0)==0x015000f0 && try_store_LDRSH_M3_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x015000d0 && try_store_LDRSB_M3_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0fff0)==0x01500060 && try_store_CMP_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01500070 && try_store_CMP_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01500060 && try_store_CMP_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01500050 && try_store_CMP_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01500040 && try_store_CMP_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01500030 && try_store_CMP_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01500020 && try_store_CMP_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01500010 && try_store_CMP_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01500000 && try_store_CMP_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff000f0)==0x015000b0 && try_store_LDRH_M3_ImmOff_U0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0fff0)==0x01500000 && try_store_CMP_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 278: /* 100010110 */
    if ((bincode&0x0f7000f0)==0x016000b0 && try_store_STRH_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x016000f0 && try_store_STRD_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f090)==0x01600080 && try_store_SMULxy(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x01600050 && try_store_QDSUB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fb0fff0)==0x0120f000 && try_store_MSRreg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x016000d0 && try_store_LDRD_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0ff0)==0x016f0f10 && try_store_CLZ(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 279: /* 100010111 */
    if ((bincode&0x0f7000f0)==0x017000f0 && try_store_LDRSH_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x017000d0 && try_store_LDRSB_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x017000b0 && try_store_LDRH_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0fff0)==0x01700060 && try_store_CMN_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01700070 && try_store_CMN_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01700060 && try_store_CMN_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01700050 && try_store_CMN_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01700040 && try_store_CMN_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01700030 && try_store_CMN_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01700020 && try_store_CMN_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x01700010 && try_store_CMN_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f070)==0x01700000 && try_store_CMN_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0fff0)==0x01700000 && try_store_CMN_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 280: /* 100011000 */
    if ((bincode&0x0f700ff0)==0x010000b0 && try_store_STRH_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x01800f90 && try_store_STREX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x010000f0 && try_store_STRD_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x01800060 && try_store_ORR_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01800070 && try_store_ORR_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x01800060 && try_store_ORR_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01800050 && try_store_ORR_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01800030 && try_store_ORR_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01800010 && try_store_ORR_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x010000d0 && try_store_LDRD_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x01800040 && try_store_ORR_M1_ASRImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x01800020 && try_store_ORR_M1_LSRImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x01800000 && try_store_ORR_M1_LSLImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x01800000 && try_store_ORR_M1_Reg_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 281: /* 100011001 */
    if ((bincode&0x0fe00ff0)==0x01800060 && try_store_ORR_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01800070 && try_store_ORR_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x01800060 && try_store_ORR_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01800050 && try_store_ORR_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01800030 && try_store_ORR_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01800010 && try_store_ORR_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x011000f0 && try_store_LDRSH_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x011000d0 && try_store_LDRSB_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x011000b0 && try_store_LDRH_M3_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00fff)==0x01900f9f && try_store_LDREX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x01900040 && try_store_ORR_M1_ASRImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x01900020 && try_store_ORR_M1_LSRImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x01900000 && try_store_ORR_M1_LSLImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x01900000 && try_store_ORR_M1_Reg_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 282: /* 100011010 */
    if ((bincode&0x0f700ff0)==0x012000b0 && try_store_STRH_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x012000f0 && try_store_STRD_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0ff0)==0x01a00060 && try_store_MOV_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01a00070 && try_store_MOV_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01a00050 && try_store_MOV_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0ff0)==0x01a00000 && try_store_MOV_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x012000d0 && try_store_LDRD_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff00f0)==0x01a00010 && try_store_MOV_M1_LSLReg_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0070)==0x01a00040 && try_store_MOV_M1_ASRImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff00f0)==0x01a00030 && try_store_MOV_M1_LSRReg_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0070)==0x01a00060 && try_store_MOV_M1_RRImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0070)==0x01a00000 && try_store_MOV_M1_LSLImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0ff0)==0x01a00000 && try_store_CPY(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0070)==0x01a00020 && try_store_MOV_M1_LSRImm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 283: /* 100011011 */
    if ((bincode&0x0fef0ff0)==0x01a00060 && try_store_MOV_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01a00070 && try_store_MOV_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01a00050 && try_store_MOV_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0ff0)==0x01a00000 && try_store_MOV_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x013000f0 && try_store_LDRSH_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x013000d0 && try_store_LDRSB_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x013000b0 && try_store_LDRH_M3_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff00f0)==0x01b00010 && try_store_MOV_M1_LSLReg_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0070)==0x01b00040 && try_store_MOV_M1_ASRImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff00f0)==0x01b00030 && try_store_MOV_M1_LSRReg_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0070)==0x01b00060 && try_store_MOV_M1_RRImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0070)==0x01b00000 && try_store_MOV_M1_LSLImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0070)==0x01b00020 && try_store_MOV_M1_LSRImm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 284: /* 100011100 */
    if ((bincode&0x0f7000f0)==0x014000b0 && try_store_STRH_M3_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x014000f0 && try_store_STRD_M3_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x014000d0 && try_store_LDRD_M3_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x01c00060 && try_store_BIC_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01c00070 && try_store_BIC_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x01c00060 && try_store_BIC_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01c00050 && try_store_BIC_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x01c00040 && try_store_BIC_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01c00030 && try_store_BIC_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x01c00020 && try_store_BIC_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01c00010 && try_store_BIC_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x01c00000 && try_store_BIC_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x01c00000 && try_store_BIC_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 285: /* 100011101 */
    if ((bincode&0x0f7000f0)==0x015000f0 && try_store_LDRSH_M3_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x015000d0 && try_store_LDRSB_M3_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x01c00060 && try_store_BIC_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01c00070 && try_store_BIC_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x01c00060 && try_store_BIC_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01c00050 && try_store_BIC_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x01c00040 && try_store_BIC_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01c00030 && try_store_BIC_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x01c00020 && try_store_BIC_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe000f0)==0x01c00010 && try_store_BIC_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00070)==0x01c00000 && try_store_BIC_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00ff0)==0x01c00000 && try_store_BIC_M1_Reg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff000f0)==0x01d000b0 && try_store_LDRH_M3_ImmOff_U1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 286: /* 100011110 */
    if ((bincode&0x0f7000f0)==0x016000b0 && try_store_STRH_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x016000f0 && try_store_STRD_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0ff0)==0x01e00060 && try_store_MVN_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01e00070 && try_store_MVN_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0070)==0x01e00060 && try_store_MVN_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01e00050 && try_store_MVN_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0070)==0x01e00040 && try_store_MVN_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01e00030 && try_store_MVN_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0070)==0x01e00020 && try_store_MVN_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01e00010 && try_store_MVN_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0070)==0x01e00000 && try_store_MVN_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x016000d0 && try_store_LDRD_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0ff0)==0x01e00000 && try_store_MVN_M1_Reg_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 287: /* 100011111 */
    if ((bincode&0x0fef0ff0)==0x01e00060 && try_store_MVN_M1_RRE(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01e00070 && try_store_MVN_M1_RRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0070)==0x01e00060 && try_store_MVN_M1_RRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01e00050 && try_store_MVN_M1_ASRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0070)==0x01e00040 && try_store_MVN_M1_ASRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01e00030 && try_store_MVN_M1_LSRReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0070)==0x01e00020 && try_store_MVN_M1_LSRImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef00f0)==0x01e00010 && try_store_MVN_M1_LSLReg(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fef0070)==0x01e00000 && try_store_MVN_M1_LSLImm(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x017000f0 && try_store_LDRSH_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x017000d0 && try_store_LDRSB_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f7000f0)==0x017000b0 && try_store_LDRH_M3_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0ff0)==0x01f00000 && try_store_MVN_M1_Reg_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 288: /* 100100000 */
    if ((bincode&0x0ff00000)==0x02000000 && try_store_AND_M1_Imm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 289: /* 100100001 */
    if ((bincode&0x0ff00000)==0x02100000 && try_store_AND_M1_Imm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 290: /* 100100010 */
    if ((bincode&0x0ff00000)==0x02200000 && try_store_EOR_M1_Imm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 291: /* 100100011 */
    if ((bincode&0x0ff00000)==0x02300000 && try_store_EOR_M1_Imm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 292: /* 100100100 */
    if ((bincode&0x0ff00000)==0x02400000 && try_store_SUB_M1_Imm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 293: /* 100100101 */
    if ((bincode&0x0ff00000)==0x02500000 && try_store_SUB_M1_Imm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 294: /* 100100110 */
    if ((bincode&0x0ff00000)==0x02600000 && try_store_RSB_M1_Imm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 295: /* 100100111 */
    if ((bincode&0x0ff00000)==0x02700000 && try_store_RSB_M1_Imm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 296: /* 100101000 */
    if ((bincode&0x0ff00000)==0x02800000 && try_store_ADD_M1_Imm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 297: /* 100101001 */
    if ((bincode&0x0ff00000)==0x02900000 && try_store_ADD_M1_Imm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 298: /* 100101010 */
  case 299: /* 100101011 */
    if ((bincode&0x0fe00000)==0x02a00000 && try_store_ADC_M1_Imm(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 300: /* 100101100 */
  case 301: /* 100101101 */
    if ((bincode&0x0fe00000)==0x02c00000 && try_store_SBC_M1_Imm(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 302: /* 100101110 */
  case 303: /* 100101111 */
    if ((bincode&0x0fe00000)==0x02e00000 && try_store_RSC_M1_Imm(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 304: /* 100110000 */
    break;
  case 305: /* 100110001 */
    if ((bincode&0x0ff0f000)==0x03100000 && try_store_TST_M1_Imm(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 306: /* 100110010 */
    if ((bincode&0x0fb0f000)==0x0320f000 && try_store_MSRimm(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 307: /* 100110011 */
    if ((bincode&0x0ff0f000)==0x03300000 && try_store_TEQ_M1_Imm(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 308: /* 100110100 */
    break;
  case 309: /* 100110101 */
    if ((bincode&0x0ff0f000)==0x03500000 && try_store_CMP_M1_Imm(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 310: /* 100110110 */
    if ((bincode&0x0fb0f000)==0x0320f000 && try_store_MSRimm(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 311: /* 100110111 */
    if ((bincode&0x0ff0f000)==0x03700000 && try_store_CMN_M1_Imm(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 312: /* 100111000 */
    if ((bincode&0x0ff00000)==0x03800000 && try_store_ORR_M1_Imm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 313: /* 100111001 */
    if ((bincode&0x0ff00000)==0x03900000 && try_store_ORR_M1_Imm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 314: /* 100111010 */
    if ((bincode&0x0fff0000)==0x03a00000 && try_store_MOV_M1_Imm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 315: /* 100111011 */
    if ((bincode&0x0fff0000)==0x03b00000 && try_store_MOV_M1_Imm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 316: /* 100111100 */
    if ((bincode&0x0ff00000)==0x03c00000 && try_store_BIC_M1_Imm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 317: /* 100111101 */
    if ((bincode&0x0ff00000)==0x03d00000 && try_store_BIC_M1_Imm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 318: /* 100111110 */
    if ((bincode&0x0fff0000)==0x03e00000 && try_store_MVN_M1_Imm_S0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 319: /* 100111111 */
    if ((bincode&0x0fff0000)==0x03f00000 && try_store_MVN_M1_Imm_S1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 320: /* 101000000 */
    if ((bincode&0x0f700000)==0x04000000 && try_store_STR_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 321: /* 101000001 */
    if ((bincode&0x0f700000)==0x04100000 && try_store_LDR_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 322: /* 101000010 */
    if ((bincode&0x0f700000)==0x04200000 && try_store_STRT_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 323: /* 101000011 */
    if ((bincode&0x0f700000)==0x04300000 && try_store_LDRT_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 324: /* 101000100 */
    if ((bincode&0x0f700000)==0x04400000 && try_store_STRB_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 325: /* 101000101 */
    if ((bincode&0x0f700000)==0x04500000 && try_store_LDRB_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 326: /* 101000110 */
    if ((bincode&0x0f700000)==0x04600000 && try_store_STRBT_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 327: /* 101000111 */
    if ((bincode&0x0f700000)==0x04700000 && try_store_LDRBT_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 328: /* 101001000 */
    if ((bincode&0x0f700000)==0x04000000 && try_store_STR_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 329: /* 101001001 */
    if ((bincode&0x0f700000)==0x04100000 && try_store_LDR_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 330: /* 101001010 */
    if ((bincode&0x0f700000)==0x04200000 && try_store_STRT_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 331: /* 101001011 */
    if ((bincode&0x0f700000)==0x04300000 && try_store_LDRT_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 332: /* 101001100 */
    if ((bincode&0x0f700000)==0x04400000 && try_store_STRB_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 333: /* 101001101 */
    if ((bincode&0x0f700000)==0x04500000 && try_store_LDRB_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 334: /* 101001110 */
    if ((bincode&0x0f700000)==0x04600000 && try_store_STRBT_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 335: /* 101001111 */
    if ((bincode&0x0f700000)==0x04700000 && try_store_LDRBT_M2_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 336: /* 101010000 */
    if ((bincode&0x0f700000)==0x05000000 && try_store_STR_M2_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 337: /* 101010001 */
    if ((bincode&0x0f700000)==0x05100000 && try_store_LDR_M2_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 338: /* 101010010 */
    if ((bincode&0x0f700000)==0x05200000 && try_store_STR_M2_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 339: /* 101010011 */
    if ((bincode&0x0f700000)==0x05300000 && try_store_LDR_M2_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 340: /* 101010100 */
    if ((bincode&0x0f700000)==0x05400000 && try_store_STRB_M2_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 341: /* 101010101 */
    if ((bincode&0xff70f000)==0xf550f000 && try_store_PLD_M2_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700000)==0x05500000 && try_store_LDRB_M2_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 342: /* 101010110 */
    if ((bincode&0x0f700000)==0x05600000 && try_store_STRB_M2_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 343: /* 101010111 */
    if ((bincode&0x0f700000)==0x05700000 && try_store_LDRB_M2_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 344: /* 101011000 */
    if ((bincode&0x0f700000)==0x05000000 && try_store_STR_M2_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 345: /* 101011001 */
    if ((bincode&0x0f700000)==0x05100000 && try_store_LDR_M2_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 346: /* 101011010 */
    if ((bincode&0x0f700000)==0x05200000 && try_store_STR_M2_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 347: /* 101011011 */
    if ((bincode&0x0f700000)==0x05300000 && try_store_LDR_M2_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 348: /* 101011100 */
    if ((bincode&0x0f700000)==0x05400000 && try_store_STRB_M2_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 349: /* 101011101 */
    if ((bincode&0xff70f000)==0xf550f000 && try_store_PLD_M2_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700000)==0x05500000 && try_store_LDRB_M2_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 350: /* 101011110 */
    if ((bincode&0x0f700000)==0x05600000 && try_store_STRB_M2_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 351: /* 101011111 */
    if ((bincode&0x0f700000)==0x05700000 && try_store_LDRB_M2_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 352: /* 101100000 */
    if ((bincode&0x0f700010)==0x06000000 && try_store_STR_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06000000 && try_store_STR_M2_Reg_postInd_U0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 353: /* 101100001 */
    if ((bincode&0x0ff00ff0)==0x06100f50 && try_store_SSUBADDX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06100ff0 && try_store_SSUB8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06100f70 && try_store_SSUB16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06100f30 && try_store_SADDSUBX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06100f90 && try_store_SADD8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06100f10 && try_store_SADD16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700010)==0x06100000 && try_store_LDR_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06100000 && try_store_LDR_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 354: /* 101100010 */
    if ((bincode&0x0f700010)==0x06200000 && try_store_STRT_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06200000 && try_store_STRT_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06200f50 && try_store_QSUBADDX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06200ff0 && try_store_QSUB8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06200f70 && try_store_QSUB16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06200f30 && try_store_QADDSUBX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06200f90 && try_store_QADD8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06200f10 && try_store_QADD16(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 355: /* 101100011 */
    if ((bincode&0x0ff00ff0)==0x06300f50 && try_store_SHSUBADDX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06300ff0 && try_store_SHSUB8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06300f70 && try_store_SHSUB16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06300f30 && try_store_SHADDSUBX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06300f90 && try_store_SHADD8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06300f10 && try_store_SHADD16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700010)==0x06300000 && try_store_LDRT_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06300000 && try_store_LDRT_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 356: /* 101100100 */
    if ((bincode&0x0f700010)==0x06400000 && try_store_STRB_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06400000 && try_store_STRB_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 357: /* 101100101 */
    if ((bincode&0x0ff00ff0)==0x06500f50 && try_store_USUBADDX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06500ff0 && try_store_USUB8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06500f70 && try_store_USUB16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06500f30 && try_store_UADDSUBX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06500f90 && try_store_UADD8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06500f10 && try_store_UADD16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700010)==0x06500000 && try_store_LDRB_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06500000 && try_store_LDRB_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 358: /* 101100110 */
    if ((bincode&0x0ff00ff0)==0x06600f50 && try_store_UQSUBADDX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06600ff0 && try_store_UQSUB8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06600f70 && try_store_UQSUB16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06600f30 && try_store_UQADDSUBX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06600f90 && try_store_UQADD8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06600f10 && try_store_UQADD16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700010)==0x06600000 && try_store_STRBT_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06600000 && try_store_STRBT_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 359: /* 101100111 */
    if ((bincode&0x0ff00ff0)==0x06700f50 && try_store_UHSUBADDX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06700ff0 && try_store_UHSUB8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06700f70 && try_store_UHSUB16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06700f30 && try_store_UHADDSUBX(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06700f90 && try_store_UHADD8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06700f10 && try_store_UHADD16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700010)==0x06700000 && try_store_LDRBT_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06700000 && try_store_LDRBT_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 360: /* 101101000 */
    if ((bincode&0x0fff03f0)==0x068f0070 && try_store_SXTB16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff003f0)==0x06800070 && try_store_SXTAB16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700010)==0x06000000 && try_store_STR_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06800fb0 && try_store_SEL(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x06800050 && try_store_PKHTB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00070)==0x06800010 && try_store_PKHBT(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06800000 && try_store_STR_M2_Reg_postInd_U1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 361: /* 101101001 */
    if ((bincode&0x0f700010)==0x06100000 && try_store_LDR_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06100000 && try_store_LDR_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 362: /* 101101010 */
    if ((bincode&0x0fff03f0)==0x06af0070 && try_store_SXTB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff003f0)==0x06a00070 && try_store_SXTAB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700010)==0x06200000 && try_store_STRT_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06200000 && try_store_STRT_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06a00f30 && try_store_SSAT16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00030)==0x06a00010 && try_store_SSAT(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 363: /* 101101011 */
    if ((bincode&0x0fff03f0)==0x06bf0070 && try_store_SXTH(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff003f0)==0x06b00070 && try_store_SXTAH(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00030)==0x06a00010 && try_store_SSAT(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0ff0)==0x06bf0fb0 && try_store_REV16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0ff0)==0x06bf0f30 && try_store_REV(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700010)==0x06300000 && try_store_LDRT_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06300000 && try_store_LDRT_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 364: /* 101101100 */
    if ((bincode&0x0fff03f0)==0x06cf0070 && try_store_UXTB16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff003f0)==0x06c00070 && try_store_UXTAB16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700010)==0x06400000 && try_store_STRB_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06400000 && try_store_STRB_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 365: /* 101101101 */
    if ((bincode&0x0f700010)==0x06500000 && try_store_LDRB_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06500000 && try_store_LDRB_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 366: /* 101101110 */
    if ((bincode&0x0fff03f0)==0x06ef0070 && try_store_UXTB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff003f0)==0x06e00070 && try_store_UXTAB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x06e00f30 && try_store_USAT16(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00030)==0x06e00010 && try_store_USAT(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700010)==0x06600000 && try_store_STRBT_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06600000 && try_store_STRBT_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 367: /* 101101111 */
    if ((bincode&0x0fff03f0)==0x06ff0070 && try_store_UXTH(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff003f0)==0x06f00070 && try_store_UXTAH(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fe00030)==0x06e00010 && try_store_USAT(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fff0ff0)==0x06ff0fb0 && try_store_REVSH(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700010)==0x06700000 && try_store_LDRBT_M2_ScReg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x06700000 && try_store_LDRBT_M2_Reg_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 368: /* 101110000 */
    if ((bincode&0x0ff0f0d0)==0x0700f050 && try_store_SMUSD(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0d0)==0x0700f010 && try_store_SMUAD(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff000d0)==0x07000050 && try_store_SMLSD(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff000d0)==0x07000010 && try_store_SMLAD(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x07000000 && try_store_STR_M2_RegOff_U0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00010)==0x07000000 && try_store_STR_M2_ScRegOff_U0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 369: /* 101110001 */
    if ((bincode&0x0ff00ff0)==0x07100000 && try_store_LDR_M2_RegOff_U0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00010)==0x07100000 && try_store_LDR_M2_ScRegOff_U0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 370: /* 101110010 */
    if ((bincode&0x0f700010)==0x07200000 && try_store_STR_M2_ScReg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x07200000 && try_store_STR_M2_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 371: /* 101110011 */
    if ((bincode&0x0f700010)==0x07300000 && try_store_LDR_M2_ScReg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x07300000 && try_store_LDR_M2_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 372: /* 101110100 */
    if ((bincode&0x0f700010)==0x07400000 && try_store_STRB_M2_ScRegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff000d0)==0x07400050 && try_store_SMLSLD(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff000d0)==0x07400010 && try_store_SMLALD(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x07400000 && try_store_STRB_M2_RegOff_U0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 373: /* 101110101 */
    if ((bincode&0x0ff0f0d0)==0x0750f010 && try_store_SMMUL(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff000d0)==0x075000d0 && try_store_SMMLS(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff000d0)==0x07500010 && try_store_SMMLA(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0xff70f010)==0xf750f000 && try_store_PLD_M2_ScRegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0xff70fff0)==0xf750f000 && try_store_PLD_M2_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00010)==0x07500000 && try_store_LDRB_M2_ScRegOff_U0(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x07500000 && try_store_LDRB_M2_RegOff_U0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 374: /* 101110110 */
    if ((bincode&0x0f700010)==0x07600000 && try_store_STRB_M2_ScReg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x07600000 && try_store_STRB_M2_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 375: /* 101110111 */
    if ((bincode&0x0f700010)==0x07700000 && try_store_LDRB_M2_ScReg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x07700000 && try_store_LDRB_M2_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 376: /* 101111000 */
    if ((bincode&0x0ff000f0)==0x07800010 && try_store_USADA8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff0f0f0)==0x0780f010 && try_store_USAD8(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x07800000 && try_store_STR_M2_RegOff_U1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00010)==0x07800000 && try_store_STR_M2_ScRegOff_U1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 377: /* 101111001 */
    if ((bincode&0x0ff00ff0)==0x07900000 && try_store_LDR_M2_RegOff_U1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00010)==0x07900000 && try_store_LDR_M2_ScRegOff_U1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 378: /* 101111010 */
    if ((bincode&0x0f700010)==0x07200000 && try_store_STR_M2_ScReg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x07200000 && try_store_STR_M2_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 379: /* 101111011 */
    if ((bincode&0x0f700010)==0x07300000 && try_store_LDR_M2_ScReg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x07300000 && try_store_LDR_M2_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 380: /* 101111100 */
    if ((bincode&0x0f700010)==0x07400000 && try_store_STRB_M2_ScRegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x07c00000 && try_store_STRB_M2_RegOff_U1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 381: /* 101111101 */
    if ((bincode&0xff70f010)==0xf750f000 && try_store_PLD_M2_ScRegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0xff70fff0)==0xf750f000 && try_store_PLD_M2_RegOff(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00010)==0x07d00000 && try_store_LDRB_M2_ScRegOff_U1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00ff0)==0x07d00000 && try_store_LDRB_M2_RegOff_U1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 382: /* 101111110 */
    if ((bincode&0x0f700010)==0x07600000 && try_store_STRB_M2_ScReg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x07600000 && try_store_STRB_M2_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 383: /* 101111111 */
    if ((bincode&0x0f700010)==0x07700000 && try_store_LDRB_M2_ScReg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f700ff0)==0x07700000 && try_store_LDRB_M2_Reg_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 384: /* 110000000 */
    if ((bincode&0x0fd00000)==0x08000000 && try_store_STM1_M4_DA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 385: /* 110000001 */
    if ((bincode&0xffd0ffff)==0xf8100a00 && try_store_RFE_M4_DA(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fd00000)==0x08100000 && try_store_LDM1_M4_DA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 386: /* 110000010 */
    if ((bincode&0x0fd00000)==0x08000000 && try_store_STM1_M4_DA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 387: /* 110000011 */
    if ((bincode&0xffd0ffff)==0xf8100a00 && try_store_RFE_M4_DA(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fd00000)==0x08100000 && try_store_LDM1_M4_DA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 388: /* 110000100 */
    if ((bincode&0x0ff00000)==0x08400000 && try_store_STM2_M4_DA(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0xffdfffe0)==0xf84d0500 && try_store_SRS_M4_DA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 389: /* 110000101 */
    if ((bincode&0x0fd08000)==0x08508000 && try_store_LDM3_M4_DA(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff08000)==0x08500000 && try_store_LDM2_M4_DA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 390: /* 110000110 */
    if ((bincode&0xffdfffe0)==0xf84d0500 && try_store_SRS_M4_DA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 391: /* 110000111 */
    if ((bincode&0x0fd08000)==0x08508000 && try_store_LDM3_M4_DA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 392: /* 110001000 */
    if ((bincode&0x0ff00000)==0x08800000 && try_store_STM1_M4_IA_W0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 393: /* 110001001 */
    if ((bincode&0xffd0ffff)==0xf8900a00 && try_store_RFE_M4_IA(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00000)==0x08900000 && try_store_LDM1_M4_IA_W0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 394: /* 110001010 */
    if ((bincode&0x0ff00000)==0x08a00000 && try_store_STM1_M4_IA_W1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 395: /* 110001011 */
    if ((bincode&0xffd0ffff)==0xf8900a00 && try_store_RFE_M4_IA(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00000)==0x08b00000 && try_store_LDM1_M4_IA_W1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 396: /* 110001100 */
    if ((bincode&0x0ff00000)==0x08c00000 && try_store_STM2_M4_IA(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0xffdfffe0)==0xf8cd0500 && try_store_SRS_M4_IA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 397: /* 110001101 */
    if ((bincode&0x0fd08000)==0x08d08000 && try_store_LDM3_M4_IA(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff08000)==0x08d00000 && try_store_LDM2_M4_IA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 398: /* 110001110 */
    if ((bincode&0xffdfffe0)==0xf8cd0500 && try_store_SRS_M4_IA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 399: /* 110001111 */
    if ((bincode&0x0fd08000)==0x08d08000 && try_store_LDM3_M4_IA(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 400: /* 110010000 */
    if ((bincode&0x0ff00000)==0x09000000 && try_store_STM1_M4_DB_W0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 401: /* 110010001 */
    if ((bincode&0xffd0ffff)==0xf9100a00 && try_store_RFE_M4_DB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fd00000)==0x09100000 && try_store_LDM1_M4_DB(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 402: /* 110010010 */
    if ((bincode&0x0ff00000)==0x09200000 && try_store_STM1_M4_DB_W1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 403: /* 110010011 */
    if ((bincode&0xffd0ffff)==0xf9100a00 && try_store_RFE_M4_DB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0fd00000)==0x09100000 && try_store_LDM1_M4_DB(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 404: /* 110010100 */
    if ((bincode&0x0ff00000)==0x09400000 && try_store_STM2_M4_DB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0xffdfffe0)==0xf94d0500 && try_store_SRS_M4_DB(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 405: /* 110010101 */
    if ((bincode&0x0fd08000)==0x09508000 && try_store_LDM3_M4_DB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff08000)==0x09500000 && try_store_LDM2_M4_DB(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 406: /* 110010110 */
    if ((bincode&0xffdfffe0)==0xf94d0500 && try_store_SRS_M4_DB(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 407: /* 110010111 */
    if ((bincode&0x0fd08000)==0x09508000 && try_store_LDM3_M4_DB(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 408: /* 110011000 */
    if ((bincode&0x0ff00000)==0x09800000 && try_store_STM1_M4_IB_W0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 409: /* 110011001 */
    if ((bincode&0xffd0ffff)==0xf9900a00 && try_store_RFE_M4_IB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00000)==0x09900000 && try_store_LDM1_M4_IB_W0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 410: /* 110011010 */
    if ((bincode&0x0ff00000)==0x09a00000 && try_store_STM1_M4_IB_W1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 411: /* 110011011 */
    if ((bincode&0xffd0ffff)==0xf9900a00 && try_store_RFE_M4_IB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00000)==0x09b00000 && try_store_LDM1_M4_IB_W1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 412: /* 110011100 */
    if ((bincode&0x0ff00000)==0x09c00000 && try_store_STM2_M4_IB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0xffdfffe0)==0xf9cd0500 && try_store_SRS_M4_IB(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 413: /* 110011101 */
    if ((bincode&0x0fd08000)==0x09d08000 && try_store_LDM3_M4_IB(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff08000)==0x09d00000 && try_store_LDM2_M4_IB(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 414: /* 110011110 */
    if ((bincode&0xffdfffe0)==0xf9cd0500 && try_store_SRS_M4_IB(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 415: /* 110011111 */
    if ((bincode&0x0fd08000)==0x09d08000 && try_store_LDM3_M4_IB(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 416: /* 110100000 */
  case 417: /* 110100001 */
  case 418: /* 110100010 */
  case 419: /* 110100011 */
  case 420: /* 110100100 */
  case 421: /* 110100101 */
  case 422: /* 110100110 */
  case 423: /* 110100111 */
  case 424: /* 110101000 */
  case 425: /* 110101001 */
  case 426: /* 110101010 */
  case 427: /* 110101011 */
  case 428: /* 110101100 */
  case 429: /* 110101101 */
  case 430: /* 110101110 */
  case 431: /* 110101111 */
    if ((bincode&0xfe000000)==0xfa000000 && try_store_BLX1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000000)==0x0a000000 && try_store_B_L0(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 432: /* 110110000 */
  case 433: /* 110110001 */
  case 434: /* 110110010 */
  case 435: /* 110110011 */
  case 436: /* 110110100 */
  case 437: /* 110110101 */
  case 438: /* 110110110 */
  case 439: /* 110110111 */
  case 440: /* 110111000 */
  case 441: /* 110111001 */
  case 442: /* 110111010 */
  case 443: /* 110111011 */
  case 444: /* 110111100 */
  case 445: /* 110111101 */
  case 446: /* 110111110 */
  case 447: /* 110111111 */
    if ((bincode&0xfe000000)==0xfa000000 && try_store_BLX1(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000000)==0x0b000000 && try_store_B_L1(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 448: /* 111000000 */
    if ((bincode&0x0f300000)==0x0c000000 && try_store_STC_M5_U(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 449: /* 111000001 */
    if ((bincode&0x0f300000)==0x0c100000 && try_store_LDC_M5_U(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 450: /* 111000010 */
    if ((bincode&0x0f300000)==0x0c200000 && try_store_STC_M5_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 451: /* 111000011 */
    if ((bincode&0x0f300000)==0x0c300000 && try_store_LDC_M5_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 452: /* 111000100 */
    if ((bincode&0x0f300000)==0x0c000000 && try_store_STC_M5_U(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0ff00000)==0x0c400000 && try_store_MCRR(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 453: /* 111000101 */
    if ((bincode&0x0ff00000)==0x0c500000 && try_store_MRRC(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f300000)==0x0c100000 && try_store_LDC_M5_U(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 454: /* 111000110 */
    if ((bincode&0x0f300000)==0x0c200000 && try_store_STC_M5_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 455: /* 111000111 */
    if ((bincode&0x0f300000)==0x0c300000 && try_store_LDC_M5_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 456: /* 111001000 */
    if ((bincode&0x0f300000)==0x0c000000 && try_store_STC_M5_U(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 457: /* 111001001 */
    if ((bincode&0x0f300000)==0x0c100000 && try_store_LDC_M5_U(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 458: /* 111001010 */
    if ((bincode&0x0f300000)==0x0c200000 && try_store_STC_M5_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 459: /* 111001011 */
    if ((bincode&0x0f300000)==0x0c300000 && try_store_LDC_M5_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 460: /* 111001100 */
    if ((bincode&0x0f300000)==0x0c000000 && try_store_STC_M5_U(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 461: /* 111001101 */
    if ((bincode&0x0f300000)==0x0c100000 && try_store_LDC_M5_U(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 462: /* 111001110 */
    if ((bincode&0x0f300000)==0x0c200000 && try_store_STC_M5_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 463: /* 111001111 */
    if ((bincode&0x0f300000)==0x0c300000 && try_store_LDC_M5_Imm_postInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 464: /* 111010000 */
    if ((bincode&0x0f300000)==0x0d000000 && try_store_STC_M5_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 465: /* 111010001 */
    if ((bincode&0x0f300000)==0x0d100000 && try_store_LDC_M5_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 466: /* 111010010 */
    if ((bincode&0x0f300000)==0x0d200000 && try_store_STC_M5_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 467: /* 111010011 */
    if ((bincode&0x0f300000)==0x0d300000 && try_store_LDC_M5_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 468: /* 111010100 */
    if ((bincode&0x0f300000)==0x0d000000 && try_store_STC_M5_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 469: /* 111010101 */
    if ((bincode&0x0f300000)==0x0d100000 && try_store_LDC_M5_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 470: /* 111010110 */
    if ((bincode&0x0f300000)==0x0d200000 && try_store_STC_M5_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 471: /* 111010111 */
    if ((bincode&0x0f300000)==0x0d300000 && try_store_LDC_M5_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 472: /* 111011000 */
    if ((bincode&0x0f300000)==0x0d000000 && try_store_STC_M5_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 473: /* 111011001 */
    if ((bincode&0x0f300000)==0x0d100000 && try_store_LDC_M5_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 474: /* 111011010 */
    if ((bincode&0x0f300000)==0x0d200000 && try_store_STC_M5_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 475: /* 111011011 */
    if ((bincode&0x0f300000)==0x0d300000 && try_store_LDC_M5_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 476: /* 111011100 */
    if ((bincode&0x0f300000)==0x0d000000 && try_store_STC_M5_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 477: /* 111011101 */
    if ((bincode&0x0f300000)==0x0d100000 && try_store_LDC_M5_ImmOff(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 478: /* 111011110 */
    if ((bincode&0x0f300000)==0x0d200000 && try_store_STC_M5_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 479: /* 111011111 */
    if ((bincode&0x0f300000)==0x0d300000 && try_store_LDC_M5_Imm_preInd(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 480: /* 111100000 */
    if ((bincode&0x0f100010)==0x0e000010 && try_store_MCR(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 481: /* 111100001 */
    if ((bincode&0x0f100010)==0x0e100010 && try_store_MRC(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 482: /* 111100010 */
    if ((bincode&0x0f100010)==0x0e000010 && try_store_MCR(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 483: /* 111100011 */
    if ((bincode&0x0f100010)==0x0e100010 && try_store_MRC(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 484: /* 111100100 */
    if ((bincode&0x0f100010)==0x0e000010 && try_store_MCR(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 485: /* 111100101 */
    if ((bincode&0x0f100010)==0x0e100010 && try_store_MRC(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 486: /* 111100110 */
    if ((bincode&0x0f100010)==0x0e000010 && try_store_MCR(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 487: /* 111100111 */
    if ((bincode&0x0f100010)==0x0e100010 && try_store_MRC(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 488: /* 111101000 */
    if ((bincode&0x0f100010)==0x0e000010 && try_store_MCR(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 489: /* 111101001 */
    if ((bincode&0x0f100010)==0x0e100010 && try_store_MRC(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 490: /* 111101010 */
    if ((bincode&0x0f100010)==0x0e000010 && try_store_MCR(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 491: /* 111101011 */
    if ((bincode&0x0f100010)==0x0e100010 && try_store_MRC(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 492: /* 111101100 */
    if ((bincode&0x0f100010)==0x0e000010 && try_store_MCR(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 493: /* 111101101 */
    if ((bincode&0x0f100010)==0x0e100010 && try_store_MRC(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 494: /* 111101110 */
    if ((bincode&0x0f100010)==0x0e000010 && try_store_MCR(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 495: /* 111101111 */
    if ((bincode&0x0f100010)==0x0e100010 && try_store_MRC(instr,bincode)) {
      assert(!found); found = true;
    }
    if ((bincode&0x0f000010)==0x0e000000 && try_store_CDP(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  case 496: /* 111110000 */
  case 497: /* 111110001 */
  case 498: /* 111110010 */
  case 499: /* 111110011 */
  case 500: /* 111110100 */
  case 501: /* 111110101 */
  case 502: /* 111110110 */
  case 503: /* 111110111 */
  case 504: /* 111111000 */
  case 505: /* 111111001 */
  case 506: /* 111111010 */
  case 507: /* 111111011 */
  case 508: /* 111111100 */
  case 509: /* 111111101 */
  case 510: /* 111111110 */
  case 511: /* 111111111 */
    if ((bincode&0x0f000000)==0x0f000000 && try_store_SWI(instr,bincode)) {
      assert(!found); found = true;
    }
    break;
  }
  if (!found) instr->args.g0.id = SLV6_UNPRED_OR_UNDEF_ID;
}

END_SIMSOC_NAMESPACE
