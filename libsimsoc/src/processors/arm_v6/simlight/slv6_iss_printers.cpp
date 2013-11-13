#include "slv6_iss_printers.hpp"
#include "slv6_math.h"
#include "slv6_processor.h"

namespace simsoc {

extern void slv6_print_cond(std::ostream&, SLv6_Condition);
extern void slv6_print_mode(std::ostream&, SLv6_Mode);
extern void slv6_print_reg(std::ostream&, uint8_t);

extern void slv6_print_reglist(std::ostream&, uint16_t);

void slv6_P_LDR_M2_ImmOff(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g1.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g1.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
  os <<"]";
}

void slv6_P_STR_M2_ImmOff(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g1.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g1.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
  os <<"]";
}

void slv6_P_B_L1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"B";
  if (get_bit(bincode,24))  os <<'L';
  if (instr->args.g2.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g2.cond);
  os <<"\t";
  if (instr->args.g2.pc_offset>>31) {
    os <<"PC-#";
    os <<std::hex <<(uint32_t)(-instr->args.g2.pc_offset);
  } else {
    os <<"PC+#";
  os <<std::hex <<(uint32_t)(instr->args.g2.pc_offset);
  }
}

void slv6_P_B_L0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"B";
  if (get_bit(bincode,24))  os <<'L';
  if (instr->args.g2.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g2.cond);
  os <<"\t";
  if (instr->args.g2.pc_offset>>31) {
    os <<"PC-#";
    os <<std::hex <<(uint32_t)(-instr->args.g2.pc_offset);
  } else {
    os <<"PC+#";
  os <<std::hex <<(uint32_t)(instr->args.g2.pc_offset);
  }
}

void slv6_P_SUB_M1_Imm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB";
  if (instr->args.g3.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g3.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_SUB_M1_Imm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB";
  if (instr->args.g3.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g3.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_CMP_M1_Reg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMP";
  if (instr->args.g4.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g4.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g4.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g4.m);
}

void slv6_P_ADD_M1_Imm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (instr->args.g3.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g3.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_ADD_M1_Imm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (instr->args.g3.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g3.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_ADD_M1_Reg_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_ADD_M1_Reg_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_EOR_M1_Reg_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_EOR_M1_Reg_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_AND_M1_Imm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"AND";
  if (instr->args.g3.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g3.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_AND_M1_Imm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"AND";
  if (instr->args.g3.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g3.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_MOV_M1_LSRImm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (instr->args.g6.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g6.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g6.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g6.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g6.shift_imm ? instr->args.g6.shift_imm : 32);
}

void slv6_P_MOV_M1_LSRImm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (instr->args.g6.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g6.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g6.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g6.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g6.shift_imm ? instr->args.g6.shift_imm : 32);
}

void slv6_P_CPY(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CPY";
  if (instr->args.g7.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g7.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g7.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g7.m);
}

void slv6_P_MOV_M1_LSLImm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (instr->args.g6.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g6.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g6.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g6.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g6.shift_imm ? instr->args.g6.shift_imm : 32);
}

void slv6_P_MOV_M1_LSLImm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (instr->args.g6.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g6.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g6.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g6.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g6.shift_imm ? instr->args.g6.shift_imm : 32);
}

void slv6_P_MOV_M1_Imm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (instr->args.g8.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g8.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g8.d);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g8.immed_rotated);
}

void slv6_P_MOV_M1_Imm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (instr->args.g8.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g8.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g8.d);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g8.immed_rotated);
}

void slv6_P_LDM1_M4_IA_W1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDM";
  if (instr->args.g9.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g9.cond);
  os <<"IA";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  if (get_bit(bincode,21))  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
}

void slv6_P_LDM1_M4_IA_W0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDM";
  if (instr->args.g9.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g9.cond);
  os <<"IA";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  if (get_bit(bincode,21))  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
}

void slv6_P_CMP_M1_Imm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMP";
  if (instr->args.g10.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g10.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g10.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g10.immed_rotated);
}

void slv6_P_LDR_M2_ScRegOff_U1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g11.shift) {
case 0: {
  os <<"LDR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 1: {
  os <<"LDR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 2: {
  os <<"LDR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 3: if (instr->args.g11.shift_imm) {
  os <<"LDR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} else {
  os <<"LDR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", RRX]";
} return;
}
}

void slv6_P_LDR_M2_ScRegOff_U0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g11.shift) {
case 0: {
  os <<"LDR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 1: {
  os <<"LDR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 2: {
  os <<"LDR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 3: if (instr->args.g11.shift_imm) {
  os <<"LDR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} else {
  os <<"LDR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", RRX]";
} return;
}
}

void slv6_P_BX(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BX";
  if (instr->args.g12.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g12.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g12.m);
}

void slv6_P_ADD_M1_LSLImm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_ADD_M1_LSLImm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_LDRB_M2_ImmOff(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g1.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g1.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
  os <<"]";
}

void slv6_P_ORR_M1_Reg_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_ORR_M1_Reg_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_MOV_M1_RRImm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (instr->args.g6.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g6.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g6.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g6.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g6.shift_imm ? instr->args.g6.shift_imm : 32);
}

void slv6_P_MOV_M1_RRImm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (instr->args.g6.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g6.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g6.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g6.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g6.shift_imm ? instr->args.g6.shift_imm : 32);
}

void slv6_P_LDR_M2_Imm_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g1.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g1.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<"], #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
}

void slv6_P_EOR_M1_RRImm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_EOR_M1_RRImm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_AND_M1_Reg_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"AND";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_AND_M1_Reg_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"AND";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_STR_M2_Imm_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g1.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g1.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
  os <<"]!";
}

void slv6_P_STRB_M2_ImmOff(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g1.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g1.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
  os <<"]";
}

void slv6_P_ORR_M1_LSLImm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_ORR_M1_LSLImm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_ADC_M1_Reg_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADC";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_ADC_M1_Reg_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADC";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_LDRB_M2_RegOff_U1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g5.m);
  os <<"]";
}

void slv6_P_LDRB_M2_RegOff_U0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g5.m);
  os <<"]";
}

void slv6_P_RSB_M1_Reg_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSB";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_RSB_M1_Reg_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSB";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_BIC_M1_Imm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BIC";
  if (instr->args.g3.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g3.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_BIC_M1_Imm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BIC";
  if (instr->args.g3.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g3.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_MVN_M1_Imm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MVN";
  if (instr->args.g8.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g8.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g8.d);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g8.immed_rotated);
}

void slv6_P_MVN_M1_Imm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MVN";
  if (instr->args.g8.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g8.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g8.d);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g8.immed_rotated);
}

void slv6_P_ORR_M1_LSRImm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_ORR_M1_LSRImm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_EOR_M1_LSRImm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_EOR_M1_LSRImm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_LDR_M2_RegOff_U1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g5.m);
  os <<"]";
}

void slv6_P_LDR_M2_RegOff_U0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g5.m);
  os <<"]";
}

void slv6_P_MOV_M1_LSRReg_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (instr->args.g14.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g14.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g14.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g14.m);
  os <<", LSR ";
  slv6_print_reg(os,instr->args.g14.s);
}

void slv6_P_MOV_M1_LSRReg_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (instr->args.g14.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g14.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g14.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g14.m);
  os <<", LSR ";
  slv6_print_reg(os,instr->args.g14.s);
}

void slv6_P_STRB_M2_RegOff_U1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g5.m);
  os <<"]";
}

void slv6_P_STRB_M2_RegOff_U0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g5.m);
  os <<"]";
}

void slv6_P_STR_M2_ScRegOff_U1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g11.shift) {
case 0: {
  os <<"STR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 1: {
  os <<"STR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 2: {
  os <<"STR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 3: if (instr->args.g11.shift_imm) {
  os <<"STR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} else {
  os <<"STR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", RRX]";
} return;
}
}

void slv6_P_STR_M2_ScRegOff_U0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g11.shift) {
case 0: {
  os <<"STR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 1: {
  os <<"STR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 2: {
  os <<"STR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 3: if (instr->args.g11.shift_imm) {
  os <<"STR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} else {
  os <<"STR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", RRX]";
} return;
}
}

void slv6_P_CMN_M1_Reg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMN";
  if (instr->args.g4.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g4.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g4.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g4.m);
}

void slv6_P_STR_M2_Reg_postInd_U1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g5.n);
  os <<"], ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_STR_M2_Reg_postInd_U0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g5.n);
  os <<"], ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_STR_M2_RegOff_U1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g5.m);
  os <<"]";
}

void slv6_P_STR_M2_RegOff_U0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g5.m);
  os <<"]";
}

void slv6_P_EOR_M1_LSLImm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_EOR_M1_LSLImm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_RSB_M1_Imm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSB";
  if (instr->args.g3.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g3.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_RSB_M1_Imm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSB";
  if (instr->args.g3.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g3.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_MOV_M1_ASRImm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (instr->args.g6.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g6.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g6.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g6.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g6.shift_imm ? instr->args.g6.shift_imm : 32);
}

void slv6_P_MOV_M1_ASRImm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (instr->args.g6.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g6.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g6.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g6.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g6.shift_imm ? instr->args.g6.shift_imm : 32);
}

void slv6_P_ADD_M1_RRImm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_ADD_M1_RRImm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_RSB_M1_LSLImm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSB";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_RSB_M1_LSLImm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSB";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_STRB_M2_Imm_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g1.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g1.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<"], #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
}

void slv6_P_STM1_M4_IA_W1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STM";
  if (instr->args.g9.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g9.cond);
  os <<"IA";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  if (get_bit(bincode,21))  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
}

void slv6_P_STM1_M4_IA_W0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STM";
  if (instr->args.g9.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g9.cond);
  os <<"IA";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  if (get_bit(bincode,21))  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
}

void slv6_P_TST_M1_Imm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TST";
  if (instr->args.g10.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g10.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g10.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g10.immed_rotated);
}

void slv6_P_STM1_M4_DB_W1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STM";
  if (instr->args.g9.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g9.cond);
  os <<"DB";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  if (get_bit(bincode,21))  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
}

void slv6_P_STM1_M4_DB_W0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STM";
  if (instr->args.g9.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g9.cond);
  os <<"DB";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  if (get_bit(bincode,21))  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
}

void slv6_P_MVN_M1_Reg_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MVN";
  if (instr->args.g7.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g7.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g7.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g7.m);
}

void slv6_P_MVN_M1_Reg_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MVN";
  if (instr->args.g7.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g7.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g7.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g7.m);
}

void slv6_P_STM1_M4_IB_W1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STM";
  if (instr->args.g9.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g9.cond);
  os <<"IB";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  if (get_bit(bincode,21))  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
}

void slv6_P_STM1_M4_IB_W0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STM";
  if (instr->args.g9.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g9.cond);
  os <<"IB";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  if (get_bit(bincode,21))  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
}

void slv6_P_ADD_M1_LSRImm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_ADD_M1_LSRImm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_STR_M2_Imm_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g1.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g1.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<"], #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
}

void slv6_P_LDRB_M2_ScRegOff_U1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g11.shift) {
case 0: {
  os <<"LDR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 1: {
  os <<"LDR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 2: {
  os <<"LDR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 3: if (instr->args.g11.shift_imm) {
  os <<"LDR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} else {
  os <<"LDR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", RRX]";
} return;
}
}

void slv6_P_LDRB_M2_ScRegOff_U0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g11.shift) {
case 0: {
  os <<"LDR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 1: {
  os <<"LDR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 2: {
  os <<"LDR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 3: if (instr->args.g11.shift_imm) {
  os <<"LDR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} else {
  os <<"LDR";
  if (instr->args.g11.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g11.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", RRX]";
} return;
}
}

void slv6_P_SUB_M1_LSLImm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_SUB_M1_LSLImm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_LDM1_M4_IB_W1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDM";
  if (instr->args.g9.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g9.cond);
  os <<"IB";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  if (get_bit(bincode,21))  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
}

void slv6_P_LDM1_M4_IB_W0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDM";
  if (instr->args.g9.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g9.cond);
  os <<"IB";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  if (get_bit(bincode,21))  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
}

void slv6_P_LDRH_M3_ImmOff_U1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g15.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g15.cond);
  os <<"H\t";
  slv6_print_reg(os,instr->args.g15.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g15.n);
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(instr->args.g15.immedHL);
  os <<"]";
}

void slv6_P_LDRH_M3_ImmOff_U0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g15.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g15.cond);
  os <<"H\t";
  slv6_print_reg(os,instr->args.g15.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g15.n);
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(instr->args.g15.immedHL);
  os <<"]";
}

void slv6_P_LDR_M2_Imm_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g1.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g1.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
  os <<"]!";
}

void slv6_P_SMULL_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SMULL";
  if (instr->args.g16.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g16.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g16.dLo);
  os <<", ";
  slv6_print_reg(os,instr->args.g16.dHi);
  os <<", ";
  slv6_print_reg(os,instr->args.g16.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g16.s);
}

void slv6_P_SMULL_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SMULL";
  if (instr->args.g16.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g16.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g16.dLo);
  os <<", ";
  slv6_print_reg(os,instr->args.g16.dHi);
  os <<", ";
  slv6_print_reg(os,instr->args.g16.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g16.s);
}

void slv6_P_RSB_M1_ASRImm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSB";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_RSB_M1_ASRImm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSB";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_TST_M1_Reg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TST";
  if (instr->args.g4.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g4.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g4.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g4.m);
}

void slv6_P_EOR_M1_Imm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (instr->args.g3.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g3.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_EOR_M1_Imm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (instr->args.g3.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g3.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_ORR_M1_ASRImm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_ORR_M1_ASRImm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_ORR_M1_Imm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (instr->args.g3.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g3.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_ORR_M1_Imm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (instr->args.g3.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g3.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_SUB_M1_ASRImm_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_SUB_M1_ASRImm_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_MOV_M1_LSLReg_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (instr->args.g14.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g14.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g14.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g14.m);
  os <<", LSL ";
  slv6_print_reg(os,instr->args.g14.s);
}

void slv6_P_MOV_M1_LSLReg_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (instr->args.g14.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g14.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g14.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g14.m);
  os <<", LSL ";
  slv6_print_reg(os,instr->args.g14.s);
}

void slv6_P_MUL_S1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MUL";
  if (instr->args.g14.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g14.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g14.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g14.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g14.s);
}

void slv6_P_MUL_S0(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MUL";
  if (instr->args.g14.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g14.cond);
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g14.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g14.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g14.s);
}

void slv6_P_CMN_M1_Imm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMN";
  if (instr->args.g10.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g10.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g10.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g10.immed_rotated);
}

void slv6_P_ADC_M1_Imm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADC";
  if (instr->args.g17.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g17.cond);
  if (instr->args.g17.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g17.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g17.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g17.immed_rotated);
}

void slv6_P_ADC_M1_LSLImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADC";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_ADC_M1_LSLReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADC";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", LSL ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_ADC_M1_LSRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADC";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_ADC_M1_LSRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADC";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", LSR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_ADC_M1_ASRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADC";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_ADC_M1_ASRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADC";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", ASR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_ADC_M1_RRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADC";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_ADC_M1_RRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADC";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", ROR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_ADC_M1_RRE(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADC";
  if (instr->args.g20.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g20.cond);
  if (instr->args.g20.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g20.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.m);
  os <<", RRX";
}

void slv6_P_ADD_M1_LSLReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", LSL ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_ADD_M1_LSRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", LSR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_ADD_M1_ASRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_ADD_M1_ASRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", ASR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_ADD_M1_RRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", ROR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_ADD_M1_RRE(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (instr->args.g20.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g20.cond);
  if (instr->args.g20.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g20.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.m);
  os <<", RRX";
}

void slv6_P_AND_M1_LSLImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"AND";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_AND_M1_LSLReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"AND";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", LSL ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_AND_M1_LSRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"AND";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_AND_M1_LSRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"AND";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", LSR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_AND_M1_ASRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"AND";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_AND_M1_ASRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"AND";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", ASR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_AND_M1_RRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"AND";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_AND_M1_RRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"AND";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", ROR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_AND_M1_RRE(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"AND";
  if (instr->args.g20.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g20.cond);
  if (instr->args.g20.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g20.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.m);
  os <<", RRX";
}

void slv6_P_BIC_M1_Reg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BIC";
  if (instr->args.g20.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g20.cond);
  if (instr->args.g20.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g20.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.m);
}

void slv6_P_BIC_M1_LSLImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BIC";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_BIC_M1_LSLReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BIC";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", LSL ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_BIC_M1_LSRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BIC";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_BIC_M1_LSRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BIC";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", LSR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_BIC_M1_ASRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BIC";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_BIC_M1_ASRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BIC";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", ASR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_BIC_M1_RRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BIC";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_BIC_M1_RRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BIC";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", ROR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_BIC_M1_RRE(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BIC";
  if (instr->args.g20.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g20.cond);
  if (instr->args.g20.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g20.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.m);
  os <<", RRX";
}

void slv6_P_BKPT(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BKPT\t";
  os <<std::hex <<(uint32_t)((get_bits(bincode,19,8)<<4)|get_bits(bincode,3,0));
}

void slv6_P_BLX1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BLX\t";
  if (instr->args.g21.pc_offset_h>>31) {
    os <<"PC-#";
    os <<std::hex <<(uint32_t)(-instr->args.g21.pc_offset_h);
  } else {
    os <<"PC+#";
  os <<std::hex <<(uint32_t)(instr->args.g21.pc_offset_h);
  }
}

void slv6_P_BLX2(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BLX";
  if (instr->args.g12.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g12.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g12.m);
}

void slv6_P_BXJ(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BXJ";
  if (instr->args.g12.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g12.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g12.m);
}

void slv6_P_CDP(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
if (bincode>>28==0xf) {
  os <<"CDP2\t";
  os <<"p";
  os <<std::dec <<(int32_t)(instr->args.g22.cp_num);
  os <<", ";
  os <<std::dec <<(int32_t)(get_bits(bincode,23,20));
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,15,12));
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,19,16));
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,3,0));
  os <<", ";
  os <<std::dec <<(int32_t)(get_bits(bincode,7,5));
} else {
  os <<"CDP";
  if (instr->args.g22.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g22.cond);
  os <<"\t";
  os <<"p";
  os <<std::dec <<(int32_t)(instr->args.g22.cp_num);
  os <<", ";
  os <<std::dec <<(int32_t)(get_bits(bincode,23,20));
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,15,12));
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,19,16));
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,3,0));
  os <<", ";
  os <<std::dec <<(int32_t)(get_bits(bincode,7,5));
}
}

void slv6_P_CLZ(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CLZ";
  if (instr->args.g7.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g7.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g7.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g7.m);
}

void slv6_P_CMN_M1_LSLImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMN";
  if (instr->args.g23.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g23.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g23.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g23.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g23.shift_imm ? instr->args.g23.shift_imm : 32);
}

void slv6_P_CMN_M1_LSLReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMN";
  if (instr->args.g24.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g24.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g24.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g24.m);
  os <<", LSL ";
  slv6_print_reg(os,instr->args.g24.s);
}

void slv6_P_CMN_M1_LSRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMN";
  if (instr->args.g23.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g23.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g23.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g23.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g23.shift_imm ? instr->args.g23.shift_imm : 32);
}

void slv6_P_CMN_M1_LSRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMN";
  if (instr->args.g24.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g24.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g24.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g24.m);
  os <<", LSR ";
  slv6_print_reg(os,instr->args.g24.s);
}

void slv6_P_CMN_M1_ASRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMN";
  if (instr->args.g23.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g23.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g23.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g23.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g23.shift_imm ? instr->args.g23.shift_imm : 32);
}

void slv6_P_CMN_M1_ASRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMN";
  if (instr->args.g24.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g24.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g24.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g24.m);
  os <<", ASR ";
  slv6_print_reg(os,instr->args.g24.s);
}

void slv6_P_CMN_M1_RRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMN";
  if (instr->args.g23.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g23.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g23.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g23.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g23.shift_imm ? instr->args.g23.shift_imm : 32);
}

void slv6_P_CMN_M1_RRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMN";
  if (instr->args.g24.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g24.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g24.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g24.m);
  os <<", ROR ";
  slv6_print_reg(os,instr->args.g24.s);
}

void slv6_P_CMN_M1_RRE(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMN";
  if (instr->args.g4.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g4.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g4.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g4.m);
  os <<", RRX";
}

void slv6_P_CMP_M1_LSLImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMP";
  if (instr->args.g23.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g23.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g23.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g23.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g23.shift_imm ? instr->args.g23.shift_imm : 32);
}

void slv6_P_CMP_M1_LSLReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMP";
  if (instr->args.g24.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g24.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g24.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g24.m);
  os <<", LSL ";
  slv6_print_reg(os,instr->args.g24.s);
}

void slv6_P_CMP_M1_LSRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMP";
  if (instr->args.g23.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g23.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g23.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g23.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g23.shift_imm ? instr->args.g23.shift_imm : 32);
}

void slv6_P_CMP_M1_LSRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMP";
  if (instr->args.g24.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g24.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g24.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g24.m);
  os <<", LSR ";
  slv6_print_reg(os,instr->args.g24.s);
}

void slv6_P_CMP_M1_ASRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMP";
  if (instr->args.g23.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g23.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g23.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g23.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g23.shift_imm ? instr->args.g23.shift_imm : 32);
}

void slv6_P_CMP_M1_ASRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMP";
  if (instr->args.g24.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g24.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g24.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g24.m);
  os <<", ASR ";
  slv6_print_reg(os,instr->args.g24.s);
}

void slv6_P_CMP_M1_RRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMP";
  if (instr->args.g23.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g23.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g23.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g23.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g23.shift_imm ? instr->args.g23.shift_imm : 32);
}

void slv6_P_CMP_M1_RRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMP";
  if (instr->args.g24.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g24.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g24.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g24.m);
  os <<", ROR ";
  slv6_print_reg(os,instr->args.g24.s);
}

void slv6_P_CMP_M1_RRE(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMP";
  if (instr->args.g4.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g4.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g4.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g4.m);
  os <<", RRX";
}

void slv6_P_CPS(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
if (instr->args.g25.imod<=1) {
  os <<"CPS\t#";
  slv6_print_mode(os,instr->args.g25.mode);
} else {
  os <<"CPS";
  if (instr->args.g25.imod==2)  os <<"IE";
  else if (instr->args.g25.imod==3)  os <<"ID";
  os <<"\t";
  if (instr->args.g25.A)  os <<'a';
  if (instr->args.g25.I)  os <<'i';
  if (instr->args.g25.F)  os <<'f';
  os <<" ";
  if (instr->args.g25.mmod) {
    os <<", #";
    slv6_print_mode(os,instr->args.g25.mode);
  }
}
}

void slv6_P_EOR_M1_LSLReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", LSL ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_EOR_M1_LSRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", LSR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_EOR_M1_ASRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_EOR_M1_ASRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", ASR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_EOR_M1_RRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", ROR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_EOR_M1_RRE(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (instr->args.g20.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g20.cond);
  if (instr->args.g20.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g20.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.m);
  os <<", RRX";
}

void slv6_P_LDC_M5_ImmOff(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
if (bincode>>28==0xf) {
  os <<"LDC2";
  if (get_bit(bincode,20))  os <<'L';
  os <<"\t";
  os <<"p";
  os <<std::dec <<(int32_t)(get_bits(bincode,11,8));
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,15,12));
  os <<", ";
  os <<"[";
  slv6_print_reg(os,get_bits(bincode,19,16));
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,7,0));
  os <<"*4]";
} else {
  os <<"LDC";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'L';
  os <<"\t";
  os <<"p";
  os <<std::dec <<(int32_t)(get_bits(bincode,11,8));
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,15,12));
  os <<", ";
  os <<"[";
  slv6_print_reg(os,get_bits(bincode,19,16));
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,7,0));
  os <<"*4]";
}
}

void slv6_P_LDC_M5_Imm_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
if (bincode>>28==0xf) {
  os <<"LDC2";
  if (get_bit(bincode,20))  os <<'L';
  os <<"\t";
  os <<"p";
  os <<std::dec <<(int32_t)(get_bits(bincode,11,8));
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,15,12));
  os <<", ";
  os <<"[";
  slv6_print_reg(os,get_bits(bincode,19,16));
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,7,0));
  os <<"*4]!";
} else {
  os <<"LDC";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'L';
  os <<"\t";
  os <<"p";
  os <<std::dec <<(int32_t)(get_bits(bincode,11,8));
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,15,12));
  os <<", ";
  os <<"[";
  slv6_print_reg(os,get_bits(bincode,19,16));
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,7,0));
  os <<"*4]!";
}
}

void slv6_P_LDC_M5_Imm_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
if (bincode>>28==0xf) {
  os <<"LDC2";
  if (get_bit(bincode,20))  os <<'L';
  os <<"\t";
  os <<"p";
  os <<std::dec <<(int32_t)(get_bits(bincode,11,8));
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,15,12));
  os <<", ";
  os <<"[";
  slv6_print_reg(os,get_bits(bincode,19,16));
  os <<"], #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,7,0));
  os <<"*4";
} else {
  os <<"LDC";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'L';
  os <<"\t";
  os <<"p";
  os <<std::dec <<(int32_t)(get_bits(bincode,11,8));
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,15,12));
  os <<", ";
  os <<"[";
  slv6_print_reg(os,get_bits(bincode,19,16));
  os <<"], #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,7,0));
  os <<"*4";
}
}

void slv6_P_LDC_M5_U(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
if (bincode>>28==0xf) {
  os <<"LDC2";
  if (get_bit(bincode,20))  os <<'L';
  os <<"\t";
  os <<"p";
  os <<std::dec <<(int32_t)(get_bits(bincode,11,8));
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,15,12));
  os <<", ";
  os <<"[";
  slv6_print_reg(os,get_bits(bincode,19,16));
  os <<"], ";
  os <<"{";
  os <<std::hex <<(uint32_t)(get_bits(bincode,7,0));
  os <<"}";
} else {
  os <<"LDC";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'L';
  os <<"\t";
  os <<"p";
  os <<std::dec <<(int32_t)(get_bits(bincode,11,8));
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,15,12));
  os <<", ";
  os <<"[";
  slv6_print_reg(os,get_bits(bincode,19,16));
  os <<"], ";
  os <<"{";
  os <<std::hex <<(uint32_t)(get_bits(bincode,7,0));
  os <<"}";
}
}

void slv6_P_LDM1_M4_DA(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDM";
  if (instr->args.g26.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g26.cond);
  os <<"DA";
  os <<"\t";
  slv6_print_reg(os,instr->args.g26.n);
  if (instr->args.g26.W)  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g26.register_list);
}

void slv6_P_LDM1_M4_DB(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDM";
  if (instr->args.g26.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g26.cond);
  os <<"DB";
  os <<"\t";
  slv6_print_reg(os,instr->args.g26.n);
  if (instr->args.g26.W)  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g26.register_list);
}

void slv6_P_LDM2_M4_IA(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDM";
  if (instr->args.g9.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g9.cond);
  os <<"IA";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
  os <<"^";
}

void slv6_P_LDM2_M4_IB(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDM";
  if (instr->args.g9.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g9.cond);
  os <<"IB";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
  os <<"^";
}

void slv6_P_LDM2_M4_DA(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDM";
  if (instr->args.g9.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g9.cond);
  os <<"DA";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
  os <<"^";
}

void slv6_P_LDM2_M4_DB(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDM";
  if (instr->args.g9.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g9.cond);
  os <<"DB";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
  os <<"^";
}

void slv6_P_LDM3_M4_IA(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDM";
  if (instr->args.g26.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g26.cond);
  os <<"IA";
  os <<"\t";
  slv6_print_reg(os,instr->args.g26.n);
  if (instr->args.g26.W)  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g26.register_list);
  os <<"^";
}

void slv6_P_LDM3_M4_IB(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDM";
  if (instr->args.g26.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g26.cond);
  os <<"IB";
  os <<"\t";
  slv6_print_reg(os,instr->args.g26.n);
  if (instr->args.g26.W)  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g26.register_list);
  os <<"^";
}

void slv6_P_LDM3_M4_DA(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDM";
  if (instr->args.g26.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g26.cond);
  os <<"DA";
  os <<"\t";
  slv6_print_reg(os,instr->args.g26.n);
  if (instr->args.g26.W)  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g26.register_list);
  os <<"^";
}

void slv6_P_LDM3_M4_DB(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDM";
  if (instr->args.g26.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g26.cond);
  os <<"DB";
  os <<"\t";
  slv6_print_reg(os,instr->args.g26.n);
  if (instr->args.g26.W)  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g26.register_list);
  os <<"^";
}

void slv6_P_LDR_M2_Reg_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<", ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
  os <<"]!";
}

void slv6_P_LDR_M2_ScReg_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g28.shift) {
case 0: {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
  os <<"]!";
} return;
case 1: {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
  os <<"]!";
} return;
case 2: {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
  os <<"]!";
} return;
case 3: if (instr->args.g28.shift_imm) {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
  os <<"]!";
} else {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", RRX]!";
} return;
}
}

void slv6_P_LDR_M2_Reg_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<"], ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
}

void slv6_P_LDR_M2_ScReg_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g28.shift) {
case 0: {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 1: {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 2: {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 3: if (instr->args.g28.shift_imm) {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} else {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", RRX";
} return;
}
}

void slv6_P_LDRB_M2_Imm_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g1.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g1.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
  os <<"]!";
}

void slv6_P_LDRB_M2_Reg_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<", ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
  os <<"]!";
}

void slv6_P_LDRB_M2_ScReg_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g28.shift) {
case 0: {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
  os <<"]!";
} return;
case 1: {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
  os <<"]!";
} return;
case 2: {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
  os <<"]!";
} return;
case 3: if (instr->args.g28.shift_imm) {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
  os <<"]!";
} else {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", RRX]!";
} return;
}
}

void slv6_P_LDRB_M2_Imm_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g1.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g1.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<"], #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
}

void slv6_P_LDRB_M2_Reg_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<"], ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
}

void slv6_P_LDRB_M2_ScReg_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g28.shift) {
case 0: {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 1: {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 2: {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 3: if (instr->args.g28.shift_imm) {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} else {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", RRX";
} return;
}
}

void slv6_P_LDRBT_M2_Imm_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g1.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g1.cond);
  os <<"BT\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<"], #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
}

void slv6_P_LDRBT_M2_Reg_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"BT\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<"], ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
}

void slv6_P_LDRBT_M2_ScReg_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g28.shift) {
case 0: {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"BT\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 1: {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"BT\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 2: {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"BT\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 3: if (instr->args.g28.shift_imm) {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"BT\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} else {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"BT\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", RRX";
} return;
}
}

void slv6_P_LDRD_M3_ImmOff(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g29.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g29.cond);
  os <<"D\t";
  slv6_print_reg(os,instr->args.g29.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g29.n);
  os <<", #";
  os <<((instr->args.g29.U ? '+' : '-'));
  os <<std::hex <<(uint32_t)(instr->args.g29.immedHL);
  os <<"]";
}

void slv6_P_LDRD_M3_RegOff(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"D\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<", ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
  os <<"]";
}

void slv6_P_LDRD_M3_Imm_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g29.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g29.cond);
  os <<"D\t";
  slv6_print_reg(os,instr->args.g29.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g29.n);
  os <<", #";
  os <<((instr->args.g29.U ? '+' : '-'));
  os <<std::hex <<(uint32_t)(instr->args.g29.immedHL);
  os <<"]!";
}

void slv6_P_LDRD_M3_Reg_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"D\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<", ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
  os <<"]!";
}

void slv6_P_LDRD_M3_Imm_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g29.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g29.cond);
  os <<"D\t";
  slv6_print_reg(os,instr->args.g29.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g29.n);
  os <<"], #";
  os <<((instr->args.g29.U ? '+' : '-'));
  os <<std::hex <<(uint32_t)(instr->args.g29.immedHL);
}

void slv6_P_LDRD_M3_Reg_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"D\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<"], ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
}

void slv6_P_LDREX(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDREX";
  if (instr->args.g30.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g30.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g30.d);
  os <<", [";
  slv6_print_reg(os,instr->args.g30.n);
  os <<"]";
}

void slv6_P_LDRH_M3_RegOff(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"H\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<", ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
  os <<"]";
}

void slv6_P_LDRH_M3_Imm_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g29.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g29.cond);
  os <<"H\t";
  slv6_print_reg(os,instr->args.g29.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g29.n);
  os <<", #";
  os <<((instr->args.g29.U ? '+' : '-'));
  os <<std::hex <<(uint32_t)(instr->args.g29.immedHL);
  os <<"]!";
}

void slv6_P_LDRH_M3_Reg_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"H\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<", ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
  os <<"]!";
}

void slv6_P_LDRH_M3_Imm_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g29.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g29.cond);
  os <<"H\t";
  slv6_print_reg(os,instr->args.g29.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g29.n);
  os <<"], #";
  os <<((instr->args.g29.U ? '+' : '-'));
  os <<std::hex <<(uint32_t)(instr->args.g29.immedHL);
}

void slv6_P_LDRH_M3_Reg_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"H\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<"], ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
}

void slv6_P_LDRSB_M3_ImmOff(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g29.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g29.cond);
  os <<"SB\t";
  slv6_print_reg(os,instr->args.g29.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g29.n);
  os <<", #";
  os <<((instr->args.g29.U ? '+' : '-'));
  os <<std::hex <<(uint32_t)(instr->args.g29.immedHL);
  os <<"]";
}

void slv6_P_LDRSB_M3_RegOff(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"SB\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<", ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
  os <<"]";
}

void slv6_P_LDRSB_M3_Imm_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g29.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g29.cond);
  os <<"SB\t";
  slv6_print_reg(os,instr->args.g29.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g29.n);
  os <<", #";
  os <<((instr->args.g29.U ? '+' : '-'));
  os <<std::hex <<(uint32_t)(instr->args.g29.immedHL);
  os <<"]!";
}

void slv6_P_LDRSB_M3_Reg_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"SB\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<", ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
  os <<"]!";
}

void slv6_P_LDRSB_M3_Imm_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g29.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g29.cond);
  os <<"SB\t";
  slv6_print_reg(os,instr->args.g29.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g29.n);
  os <<"], #";
  os <<((instr->args.g29.U ? '+' : '-'));
  os <<std::hex <<(uint32_t)(instr->args.g29.immedHL);
}

void slv6_P_LDRSB_M3_Reg_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"SB\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<"], ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
}

void slv6_P_LDRSH_M3_ImmOff(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g29.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g29.cond);
  os <<"SH\t";
  slv6_print_reg(os,instr->args.g29.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g29.n);
  os <<", #";
  os <<((instr->args.g29.U ? '+' : '-'));
  os <<std::hex <<(uint32_t)(instr->args.g29.immedHL);
  os <<"]";
}

void slv6_P_LDRSH_M3_RegOff(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"SH\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<", ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
  os <<"]";
}

void slv6_P_LDRSH_M3_Imm_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g29.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g29.cond);
  os <<"SH\t";
  slv6_print_reg(os,instr->args.g29.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g29.n);
  os <<", #";
  os <<((instr->args.g29.U ? '+' : '-'));
  os <<std::hex <<(uint32_t)(instr->args.g29.immedHL);
  os <<"]!";
}

void slv6_P_LDRSH_M3_Reg_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"SH\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<", ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
  os <<"]!";
}

void slv6_P_LDRSH_M3_Imm_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g29.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g29.cond);
  os <<"SH\t";
  slv6_print_reg(os,instr->args.g29.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g29.n);
  os <<"], #";
  os <<((instr->args.g29.U ? '+' : '-'));
  os <<std::hex <<(uint32_t)(instr->args.g29.immedHL);
}

void slv6_P_LDRSH_M3_Reg_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"SH\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<"], ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
}

void slv6_P_LDRT_M2_Imm_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g1.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g1.cond);
  os <<"T\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<"], #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
}

void slv6_P_LDRT_M2_Reg_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"T\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<"], ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
}

void slv6_P_LDRT_M2_ScReg_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g28.shift) {
case 0: {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"T\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 1: {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"T\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 2: {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"T\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 3: if (instr->args.g28.shift_imm) {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"T\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} else {
  os <<"LDR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"T\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", RRX";
} return;
}
}

void slv6_P_MCR(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
if (bincode>>28==0xf) {
  os <<"MCR2\t";
  os <<"p";
  os <<std::dec <<(int32_t)(instr->args.g31.cp_num);
  os <<", ";
  os <<std::dec <<(int32_t)(instr->args.g31.opcode_1);
  os <<", ";
  slv6_print_reg(os,instr->args.g31.d);
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(instr->args.g31.CRn);
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(instr->args.g31.CRm);
  if (instr->args.g31.opcode_2) {
    os <<", ";
    os <<std::dec <<(int32_t)(instr->args.g31.opcode_2);
  }
} else {
  os <<"MCR";
  if (instr->args.g31.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g31.cond);
  os <<"\t";
  os <<"p";
  os <<std::dec <<(int32_t)(instr->args.g31.cp_num);
  os <<", ";
  os <<std::dec <<(int32_t)(instr->args.g31.opcode_1);
  os <<", ";
  slv6_print_reg(os,instr->args.g31.d);
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(instr->args.g31.CRn);
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(instr->args.g31.CRm);
  if (instr->args.g31.opcode_2) {
    os <<", ";
    os <<std::dec <<(int32_t)(instr->args.g31.opcode_2);
  }
}
}

void slv6_P_MCRR(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
if (bincode>>28==0xf) {
  os <<"MCRR2\t";
  os <<"p";
  os <<std::dec <<(int32_t)(instr->args.g32.cp_num);
  os <<", ";
  os <<std::dec <<(int32_t)(get_bits(bincode,7,4));
  os <<", ";
  slv6_print_reg(os,instr->args.g32.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g32.n);
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,3,0));
} else {
  os <<"MCRR";
  if (instr->args.g32.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g32.cond);
  os <<"\t";
  os <<"p";
  os <<std::dec <<(int32_t)(instr->args.g32.cp_num);
  os <<", ";
  os <<std::dec <<(int32_t)(get_bits(bincode,7,4));
  os <<", ";
  slv6_print_reg(os,instr->args.g32.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g32.n);
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,3,0));
}
}

void slv6_P_MLA(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MLA";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.s);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
}

void slv6_P_MOV_M1_Reg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (instr->args.g33.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g33.cond);
  if (instr->args.g33.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g33.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g33.m);
}

void slv6_P_MOV_M1_ASRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (instr->args.g34.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g34.cond);
  if (instr->args.g34.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g34.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g34.m);
  os <<", ASR ";
  slv6_print_reg(os,instr->args.g34.s);
}

void slv6_P_MOV_M1_RRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (instr->args.g34.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g34.cond);
  if (instr->args.g34.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g34.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g34.m);
  os <<", ROR ";
  slv6_print_reg(os,instr->args.g34.s);
}

void slv6_P_MOV_M1_RRE(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (instr->args.g33.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g33.cond);
  if (instr->args.g33.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g33.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g33.m);
  os <<", RRX";
}

void slv6_P_MRC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
if (bincode>>28==0xf) {
  os <<"MRC2\t";
  os <<"p";
  os <<std::dec <<(int32_t)(instr->args.g31.cp_num);
  os <<", ";
  os <<std::dec <<(int32_t)(instr->args.g31.opcode_1);
  os <<", ";
  slv6_print_reg(os,instr->args.g31.d);
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(instr->args.g31.CRn);
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(instr->args.g31.CRm);
  if (instr->args.g31.opcode_2) {
    os <<", ";
    os <<std::dec <<(int32_t)(instr->args.g31.opcode_2);
  }
} else {
  os <<"MRC";
  if (instr->args.g31.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g31.cond);
  os <<"\t";
  os <<"p";
  os <<std::dec <<(int32_t)(instr->args.g31.cp_num);
  os <<", ";
  os <<std::dec <<(int32_t)(instr->args.g31.opcode_1);
  os <<", ";
  slv6_print_reg(os,instr->args.g31.d);
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(instr->args.g31.CRn);
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(instr->args.g31.CRm);
  if (instr->args.g31.opcode_2) {
    os <<", ";
    os <<std::dec <<(int32_t)(instr->args.g31.opcode_2);
  }
}
}

void slv6_P_MRRC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
if (bincode>>28==0xf) {
  os <<"MRRC2\t";
  os <<"p";
  os <<std::dec <<(int32_t)(instr->args.g32.cp_num);
  os <<", ";
  os <<std::dec <<(int32_t)(get_bits(bincode,7,4));
  os <<", ";
  slv6_print_reg(os,instr->args.g32.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g32.n);
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,3,0));
} else {
  os <<"MRRC";
  if (instr->args.g32.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g32.cond);
  os <<"\t";
  os <<"p";
  os <<std::dec <<(int32_t)(instr->args.g32.cp_num);
  os <<", ";
  os <<std::dec <<(int32_t)(get_bits(bincode,7,4));
  os <<", ";
  slv6_print_reg(os,instr->args.g32.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g32.n);
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,3,0));
}
}

void slv6_P_MRS(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
if (instr->args.g35.R) {
  os <<"MRS";
  if (instr->args.g35.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g35.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g35.d);
  os <<", SPSR";
} else {
  os <<"MRS";
  if (instr->args.g35.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g35.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g35.d);
  os <<", CPSR";
}
}

void slv6_P_MSRimm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
if (instr->args.g36.R) {
  os <<"MSR";
  if (instr->args.g36.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g36.cond);
  os <<"\tSPSR_";
  if (instr->args.g36.field_mask&1)  os <<'c';
  if (instr->args.g36.field_mask&2)  os <<'x';
  if (instr->args.g36.field_mask&4)  os <<'s';
  if (instr->args.g36.field_mask&8)  os <<'f';
  os <<", #";
  os <<std::hex <<(uint32_t)(instr->args.g36.immed_rotated);
} else {
  os <<"MSR";
  if (instr->args.g36.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g36.cond);
  os <<"\tCPSR_";
  if (instr->args.g36.field_mask&1)  os <<'c';
  if (instr->args.g36.field_mask&2)  os <<'x';
  if (instr->args.g36.field_mask&4)  os <<'s';
  if (instr->args.g36.field_mask&8)  os <<'f';
  os <<", #";
  os <<std::hex <<(uint32_t)(instr->args.g36.immed_rotated);
}
}

void slv6_P_MSRreg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
if (instr->args.g37.R) {
  os <<"MSR";
  if (instr->args.g37.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g37.cond);
  os <<"\tSPSR_";
  if (instr->args.g37.field_mask&1)  os <<'c';
  if (instr->args.g37.field_mask&2)  os <<'x';
  if (instr->args.g37.field_mask&4)  os <<'s';
  if (instr->args.g37.field_mask&8)  os <<'f';
  os <<", ";
  slv6_print_reg(os,instr->args.g37.m);
} else {
  os <<"MSR";
  if (instr->args.g37.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g37.cond);
  os <<"\tCPSR_";
  if (instr->args.g37.field_mask&1)  os <<'c';
  if (instr->args.g37.field_mask&2)  os <<'x';
  if (instr->args.g37.field_mask&4)  os <<'s';
  if (instr->args.g37.field_mask&8)  os <<'f';
  os <<", ";
  slv6_print_reg(os,instr->args.g37.m);
}
}

void slv6_P_MVN_M1_LSLImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MVN";
  if (instr->args.g38.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g38.cond);
  if (instr->args.g38.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g38.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g38.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g38.shift_imm ? instr->args.g38.shift_imm : 32);
}

void slv6_P_MVN_M1_LSLReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MVN";
  if (instr->args.g34.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g34.cond);
  if (instr->args.g34.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g34.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g34.m);
  os <<", LSL ";
  slv6_print_reg(os,instr->args.g34.s);
}

void slv6_P_MVN_M1_LSRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MVN";
  if (instr->args.g38.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g38.cond);
  if (instr->args.g38.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g38.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g38.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g38.shift_imm ? instr->args.g38.shift_imm : 32);
}

void slv6_P_MVN_M1_LSRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MVN";
  if (instr->args.g34.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g34.cond);
  if (instr->args.g34.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g34.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g34.m);
  os <<", LSR ";
  slv6_print_reg(os,instr->args.g34.s);
}

void slv6_P_MVN_M1_ASRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MVN";
  if (instr->args.g38.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g38.cond);
  if (instr->args.g38.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g38.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g38.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g38.shift_imm ? instr->args.g38.shift_imm : 32);
}

void slv6_P_MVN_M1_ASRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MVN";
  if (instr->args.g34.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g34.cond);
  if (instr->args.g34.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g34.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g34.m);
  os <<", ASR ";
  slv6_print_reg(os,instr->args.g34.s);
}

void slv6_P_MVN_M1_RRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MVN";
  if (instr->args.g38.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g38.cond);
  if (instr->args.g38.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g38.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g38.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g38.shift_imm ? instr->args.g38.shift_imm : 32);
}

void slv6_P_MVN_M1_RRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MVN";
  if (instr->args.g34.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g34.cond);
  if (instr->args.g34.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g34.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g34.m);
  os <<", ROR ";
  slv6_print_reg(os,instr->args.g34.s);
}

void slv6_P_MVN_M1_RRE(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MVN";
  if (instr->args.g33.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g33.cond);
  if (instr->args.g33.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g33.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g33.m);
  os <<", RRX";
}

void slv6_P_ORR_M1_LSLReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", LSL ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_ORR_M1_LSRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", LSR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_ORR_M1_ASRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", ASR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_ORR_M1_RRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_ORR_M1_RRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", ROR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_ORR_M1_RRE(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (instr->args.g20.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g20.cond);
  if (instr->args.g20.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g20.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.m);
  os <<", RRX";
}

void slv6_P_PKHBT(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"PKHBT\t";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  os <<" ";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<" ";
  if (instr->args.g13.shift_imm) {
    os <<", LSL #";
    os <<std::dec <<(int32_t)(instr->args.g13.shift_imm);
  }
}

void slv6_P_PKHTB(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"PKHTB\t";
  if (instr->args.g13.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g13.cond);
  os <<" ";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<" ";
  os <<", ASR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_PLD_M2_ImmOff(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"PLD\t";
  os <<"[";
  slv6_print_reg(os,instr->args.g39.n);
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
  os <<"]";
}

void slv6_P_PLD_M2_RegOff(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"PLD\t";
  os <<"[";
  slv6_print_reg(os,instr->args.g40.n);
  os <<", ";
  os <<((instr->args.g40.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g40.m);
  os <<"]";
}

void slv6_P_PLD_M2_ScRegOff(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g41.shift) {
case 0: {
  os <<"PLD\t";
  os <<"[";
  slv6_print_reg(os,instr->args.g41.n);
  os <<", ";
  os <<((instr->args.g41.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g41.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g41.shift_imm ? instr->args.g41.shift_imm : 32);
  os <<"]";
} return;
case 1: {
  os <<"PLD\t";
  os <<"[";
  slv6_print_reg(os,instr->args.g41.n);
  os <<", ";
  os <<((instr->args.g41.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g41.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g41.shift_imm ? instr->args.g41.shift_imm : 32);
  os <<"]";
} return;
case 2: {
  os <<"PLD\t";
  os <<"[";
  slv6_print_reg(os,instr->args.g41.n);
  os <<", ";
  os <<((instr->args.g41.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g41.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g41.shift_imm ? instr->args.g41.shift_imm : 32);
  os <<"]";
} return;
case 3: if (instr->args.g41.shift_imm) {
  os <<"PLD\t";
  os <<"[";
  slv6_print_reg(os,instr->args.g41.n);
  os <<", ";
  os <<((instr->args.g41.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g41.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g41.shift_imm ? instr->args.g41.shift_imm : 32);
  os <<"]";
} else {
  os <<"PLD\t";
  os <<"[";
  slv6_print_reg(os,instr->args.g41.n);
  os <<", ";
  os <<((instr->args.g41.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g41.m);
  os <<", RRX]";
} return;
}
}

void slv6_P_QADD(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"QADD";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
}

void slv6_P_QADD16(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"QADD16";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_QADD8(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"QADD8";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_QADDSUBX(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"QADDSUBX";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_QDADD(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"QDADD";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
}

void slv6_P_QDSUB(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"QDSUB";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
}

void slv6_P_QSUB(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"QSUB";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
}

void slv6_P_QSUB16(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"QSUB16";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_QSUB8(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"QSUB8";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_QSUBADDX(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"QSUBADDX";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_REV(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"REV";
  if (instr->args.g7.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g7.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g7.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g7.m);
}

void slv6_P_REV16(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"REV16";
  if (instr->args.g7.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g7.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g7.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g7.m);
}

void slv6_P_REVSH(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"REVSH";
  if (instr->args.g7.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g7.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g7.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g7.m);
}

void slv6_P_RFE_M4_IA(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RFE";
  os <<"IA";
  os <<"\t";
  slv6_print_reg(os,instr->args.g42.n);
  if (instr->args.g42.W)  os <<'!';
}

void slv6_P_RFE_M4_IB(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RFE";
  os <<"IB";
  os <<"\t";
  slv6_print_reg(os,instr->args.g42.n);
  if (instr->args.g42.W)  os <<'!';
}

void slv6_P_RFE_M4_DA(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RFE";
  os <<"DA";
  os <<"\t";
  slv6_print_reg(os,instr->args.g42.n);
  if (instr->args.g42.W)  os <<'!';
}

void slv6_P_RFE_M4_DB(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RFE";
  os <<"DB";
  os <<"\t";
  slv6_print_reg(os,instr->args.g42.n);
  if (instr->args.g42.W)  os <<'!';
}

void slv6_P_RSB_M1_LSLReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSB";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", LSL ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_RSB_M1_LSRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSB";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_RSB_M1_LSRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSB";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", LSR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_RSB_M1_ASRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSB";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", ASR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_RSB_M1_RRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSB";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_RSB_M1_RRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSB";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", ROR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_RSB_M1_RRE(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSB";
  if (instr->args.g20.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g20.cond);
  if (instr->args.g20.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g20.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.m);
  os <<", RRX";
}

void slv6_P_RSC_M1_Imm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSC";
  if (instr->args.g17.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g17.cond);
  if (instr->args.g17.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g17.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g17.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g17.immed_rotated);
}

void slv6_P_RSC_M1_Reg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSC";
  if (instr->args.g20.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g20.cond);
  if (instr->args.g20.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g20.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.m);
}

void slv6_P_RSC_M1_LSLImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSC";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_RSC_M1_LSLReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSC";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", LSL ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_RSC_M1_LSRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSC";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_RSC_M1_LSRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSC";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", LSR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_RSC_M1_ASRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSC";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_RSC_M1_ASRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSC";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", ASR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_RSC_M1_RRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSC";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_RSC_M1_RRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSC";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", ROR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_RSC_M1_RRE(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSC";
  if (instr->args.g20.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g20.cond);
  if (instr->args.g20.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g20.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.m);
  os <<", RRX";
}

void slv6_P_SADD16(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SADD16";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_SADD8(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SADD8";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_SADDSUBX(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SADDSUBX";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_SBC_M1_Imm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SBC";
  if (instr->args.g17.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g17.cond);
  if (instr->args.g17.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g17.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g17.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g17.immed_rotated);
}

void slv6_P_SBC_M1_Reg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SBC";
  if (instr->args.g20.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g20.cond);
  if (instr->args.g20.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g20.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.m);
}

void slv6_P_SBC_M1_LSLImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SBC";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_SBC_M1_LSLReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SBC";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", LSL ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_SBC_M1_LSRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SBC";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_SBC_M1_LSRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SBC";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", LSR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_SBC_M1_ASRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SBC";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_SBC_M1_ASRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SBC";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", ASR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_SBC_M1_RRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SBC";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_SBC_M1_RRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SBC";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", ROR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_SBC_M1_RRE(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SBC";
  if (instr->args.g20.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g20.cond);
  if (instr->args.g20.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g20.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.m);
  os <<", RRX";
}

void slv6_P_SEL(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SEL";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_SETEND(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SETEND\t";
  os <<((instr->args.g43.E ? "BE" : "LE"));
}

void slv6_P_SHADD16(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SHADD16";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_SHADD8(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SHADD8";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_SHADDSUBX(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SHADDSUBX";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_SHSUB16(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SHSUB16";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_SHSUB8(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SHSUB8";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_SHSUBADDX(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SHSUBADDX";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_SMLAxy(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SMLA";
  os <<((instr->args.g44.x ? 'T' : 'B'));
  os <<((instr->args.g44.y ? 'T' : 'B'));
  if (instr->args.g44.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g44.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g44.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g44.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g44.s);
  os <<", ";
  slv6_print_reg(os,instr->args.g44.n);
}

void slv6_P_SMLAD(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SMLAD";
  if (instr->args.g45.X)  os <<'X';
  if (instr->args.g45.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g45.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g45.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g45.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g45.s);
  os <<", ";
  slv6_print_reg(os,instr->args.g45.n);
}

void slv6_P_SMLAL(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SMLAL";
  if (instr->args.g46.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g46.cond);
  if (instr->args.g46.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g46.dLo);
  os <<", ";
  slv6_print_reg(os,instr->args.g46.dHi);
  os <<", ";
  slv6_print_reg(os,instr->args.g46.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g46.s);
}

void slv6_P_SMLALxy(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SMLAL";
  os <<((instr->args.g47.x ? 'T' : 'B'));
  os <<((instr->args.g47.y ? 'T' : 'B'));
  if (instr->args.g47.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g47.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g47.dLo);
  os <<", ";
  slv6_print_reg(os,instr->args.g47.dHi);
  os <<", ";
  slv6_print_reg(os,instr->args.g47.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g47.s);
}

void slv6_P_SMLALD(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SMLALD";
  if (instr->args.g48.X)  os <<'X';
  if (instr->args.g48.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g48.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g48.dLo);
  os <<", ";
  slv6_print_reg(os,instr->args.g48.dHi);
  os <<", ";
  slv6_print_reg(os,instr->args.g48.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g48.s);
}

void slv6_P_SMLAWy(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SMLAW";
  os <<((instr->args.g49.y ? 'T' : 'B'));
  if (instr->args.g49.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g49.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g49.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g49.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g49.s);
  os <<", ";
  slv6_print_reg(os,instr->args.g49.n);
}

void slv6_P_SMLSD(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SMLSD";
  if (instr->args.g45.X)  os <<'X';
  if (instr->args.g45.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g45.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g45.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g45.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g45.s);
  os <<", ";
  slv6_print_reg(os,instr->args.g45.n);
}

void slv6_P_SMLSLD(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SMLSLD";
  if (instr->args.g48.X)  os <<'X';
  if (instr->args.g48.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g48.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g48.dLo);
  os <<", ";
  slv6_print_reg(os,instr->args.g48.dHi);
  os <<", ";
  slv6_print_reg(os,instr->args.g48.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g48.s);
}

void slv6_P_SMMLA(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SMMLA";
  if (instr->args.g50.R)  os <<'R';
  if (instr->args.g50.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g50.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g50.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g50.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g50.s);
  os <<", ";
  slv6_print_reg(os,instr->args.g50.n);
}

void slv6_P_SMMLS(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SMMLS";
  if (instr->args.g50.R)  os <<'R';
  if (instr->args.g50.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g50.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g50.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g50.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g50.s);
  os <<", ";
  slv6_print_reg(os,instr->args.g50.n);
}

void slv6_P_SMMUL(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SMMUL";
  if (instr->args.g51.R)  os <<'R';
  if (instr->args.g51.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g51.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g51.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g51.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g51.s);
}

void slv6_P_SMUAD(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SMUAD";
  if (instr->args.g52.X)  os <<'X';
  if (instr->args.g52.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g52.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g52.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g52.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g52.s);
}

void slv6_P_SMULxy(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SMUL";
  os <<((instr->args.g53.x ? 'T' : 'B'));
  os <<((instr->args.g53.y ? 'T' : 'B'));
  if (instr->args.g53.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g53.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g53.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g53.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g53.s);
}

void slv6_P_SMULWy(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SMULW";
  os <<((instr->args.g54.y ? 'T' : 'B'));
  if (instr->args.g54.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g54.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g54.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g54.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g54.s);
}

void slv6_P_SMUSD(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SMUSD";
  if (instr->args.g52.X)  os <<'X';
  if (instr->args.g52.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g52.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g52.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g52.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g52.s);
}

void slv6_P_SRS_M4_IA(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SRS";
  os <<"IA";
  os <<"\t#";
  slv6_print_mode(os,instr->args.g55.mode);
  if (instr->args.g55.W)  os <<'!';
}

void slv6_P_SRS_M4_IB(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SRS";
  os <<"IB";
  os <<"\t#";
  slv6_print_mode(os,instr->args.g55.mode);
  if (instr->args.g55.W)  os <<'!';
}

void slv6_P_SRS_M4_DA(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SRS";
  os <<"DA";
  os <<"\t#";
  slv6_print_mode(os,instr->args.g55.mode);
  if (instr->args.g55.W)  os <<'!';
}

void slv6_P_SRS_M4_DB(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SRS";
  os <<"DB";
  os <<"\t#";
  slv6_print_mode(os,instr->args.g55.mode);
  if (instr->args.g55.W)  os <<'!';
}

void slv6_P_SSAT(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SSAT";
  if (instr->args.g56.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g56.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g56.d);
  os <<", #";
  os <<std::dec <<(int32_t)(instr->args.g56.sat_imm);
  os <<", ";
  slv6_print_reg(os,instr->args.g56.m);
  if (instr->args.g56.shift) {
    os <<", ";
    os <<"  ASR #";
    os <<std::dec <<(instr->args.g56.shift_imm ? instr->args.g56.shift_imm : 32);
  } else if (instr->args.g56.shift_imm) {
    os <<", ";
    os <<"  LSL #";
    os <<std::dec <<(int32_t)(instr->args.g56.shift_imm);
  }
}

void slv6_P_SSAT16(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SSAT16";
  if (instr->args.g57.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g57.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g57.d);
  os <<", #";
  os <<std::dec <<(int32_t)(instr->args.g57.sat_imm);
  os <<", ";
  slv6_print_reg(os,instr->args.g57.m);
}

void slv6_P_SSUB16(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SSUB16";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_SSUB8(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SSUB8";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_SSUBADDX(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SSUBADDX";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_STC_M5_ImmOff(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
if (bincode>>28==0xf) {
  os <<"STC2";
  if (get_bit(bincode,20))  os <<'L';
  os <<"\t";
  os <<"p";
  os <<std::dec <<(int32_t)(get_bits(bincode,11,8));
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,15,12));
  os <<", ";
  os <<"[";
  slv6_print_reg(os,get_bits(bincode,19,16));
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,7,0));
  os <<"*4]";
} else {
  os <<"STC";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'L';
  os <<"\t";
  os <<"p";
  os <<std::dec <<(int32_t)(get_bits(bincode,11,8));
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,15,12));
  os <<", ";
  os <<"[";
  slv6_print_reg(os,get_bits(bincode,19,16));
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,7,0));
  os <<"*4]";
}
}

void slv6_P_STC_M5_Imm_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
if (bincode>>28==0xf) {
  os <<"STC2";
  if (get_bit(bincode,20))  os <<'L';
  os <<"\t";
  os <<"p";
  os <<std::dec <<(int32_t)(get_bits(bincode,11,8));
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,15,12));
  os <<", ";
  os <<"[";
  slv6_print_reg(os,get_bits(bincode,19,16));
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,7,0));
  os <<"*4]!";
} else {
  os <<"STC";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'L';
  os <<"\t";
  os <<"p";
  os <<std::dec <<(int32_t)(get_bits(bincode,11,8));
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,15,12));
  os <<", ";
  os <<"[";
  slv6_print_reg(os,get_bits(bincode,19,16));
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,7,0));
  os <<"*4]!";
}
}

void slv6_P_STC_M5_Imm_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
if (bincode>>28==0xf) {
  os <<"STC2";
  if (get_bit(bincode,20))  os <<'L';
  os <<"\t";
  os <<"p";
  os <<std::dec <<(int32_t)(get_bits(bincode,11,8));
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,15,12));
  os <<", ";
  os <<"[";
  slv6_print_reg(os,get_bits(bincode,19,16));
  os <<"], #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,7,0));
  os <<"*4";
} else {
  os <<"STC";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'L';
  os <<"\t";
  os <<"p";
  os <<std::dec <<(int32_t)(get_bits(bincode,11,8));
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,15,12));
  os <<", ";
  os <<"[";
  slv6_print_reg(os,get_bits(bincode,19,16));
  os <<"], #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,7,0));
  os <<"*4";
}
}

void slv6_P_STC_M5_U(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
if (bincode>>28==0xf) {
  os <<"STC2";
  if (get_bit(bincode,20))  os <<'L';
  os <<"\t";
  os <<"p";
  os <<std::dec <<(int32_t)(get_bits(bincode,11,8));
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,15,12));
  os <<", ";
  os <<"[";
  slv6_print_reg(os,get_bits(bincode,19,16));
  os <<"], ";
  os <<"{";
  os <<std::hex <<(uint32_t)(get_bits(bincode,7,0));
  os <<"}";
} else {
  os <<"STC";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'L';
  os <<"\t";
  os <<"p";
  os <<std::dec <<(int32_t)(get_bits(bincode,11,8));
  os <<", ";
  os <<"CR";
  os <<std::dec <<(int32_t)(get_bits(bincode,15,12));
  os <<", ";
  os <<"[";
  slv6_print_reg(os,get_bits(bincode,19,16));
  os <<"], ";
  os <<"{";
  os <<std::hex <<(uint32_t)(get_bits(bincode,7,0));
  os <<"}";
}
}

void slv6_P_STM1_M4_DA(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STM";
  if (instr->args.g26.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g26.cond);
  os <<"DA";
  os <<"\t";
  slv6_print_reg(os,instr->args.g26.n);
  if (instr->args.g26.W)  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g26.register_list);
}

void slv6_P_STM2_M4_IA(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STM";
  if (instr->args.g9.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g9.cond);
  os <<"IA";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
  os <<"^";
}

void slv6_P_STM2_M4_IB(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STM";
  if (instr->args.g9.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g9.cond);
  os <<"IB";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
  os <<"^";
}

void slv6_P_STM2_M4_DA(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STM";
  if (instr->args.g9.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g9.cond);
  os <<"DA";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
  os <<"^";
}

void slv6_P_STM2_M4_DB(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STM";
  if (instr->args.g9.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g9.cond);
  os <<"DB";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
  os <<"^";
}

void slv6_P_STR_M2_Reg_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<", ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
  os <<"]!";
}

void slv6_P_STR_M2_ScReg_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g28.shift) {
case 0: {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
  os <<"]!";
} return;
case 1: {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
  os <<"]!";
} return;
case 2: {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
  os <<"]!";
} return;
case 3: if (instr->args.g28.shift_imm) {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
  os <<"]!";
} else {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", RRX]!";
} return;
}
}

void slv6_P_STR_M2_ScReg_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g28.shift) {
case 0: {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 1: {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 2: {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 3: if (instr->args.g28.shift_imm) {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} else {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", RRX";
} return;
}
}

void slv6_P_STRB_M2_ScRegOff(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g28.shift) {
case 0: {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
  os <<"]";
} return;
case 1: {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
  os <<"]";
} return;
case 2: {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
  os <<"]";
} return;
case 3: if (instr->args.g28.shift_imm) {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
  os <<"]";
} else {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", RRX]";
} return;
}
}

void slv6_P_STRB_M2_Imm_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g1.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g1.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
  os <<"]!";
}

void slv6_P_STRB_M2_Reg_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<", ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
  os <<"]!";
}

void slv6_P_STRB_M2_ScReg_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g28.shift) {
case 0: {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
  os <<"]!";
} return;
case 1: {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
  os <<"]!";
} return;
case 2: {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
  os <<"]!";
} return;
case 3: if (instr->args.g28.shift_imm) {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
  os <<"]!";
} else {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<", ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", RRX]!";
} return;
}
}

void slv6_P_STRB_M2_Reg_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<"], ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
}

void slv6_P_STRB_M2_ScReg_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g28.shift) {
case 0: {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 1: {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 2: {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 3: if (instr->args.g28.shift_imm) {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} else {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", RRX";
} return;
}
}

void slv6_P_STRBT_M2_Imm_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g1.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g1.cond);
  os <<"BT\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<"], #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
}

void slv6_P_STRBT_M2_Reg_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"BT\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<"], ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
}

void slv6_P_STRBT_M2_ScReg_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g28.shift) {
case 0: {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"BT\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 1: {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"BT\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 2: {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"BT\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 3: if (instr->args.g28.shift_imm) {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"BT\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} else {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"BT\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", RRX";
} return;
}
}

void slv6_P_STRD_M3_ImmOff(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g29.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g29.cond);
  os <<"D\t";
  slv6_print_reg(os,instr->args.g29.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g29.n);
  os <<", #";
  os <<((instr->args.g29.U ? '+' : '-'));
  os <<std::hex <<(uint32_t)(instr->args.g29.immedHL);
  os <<"]";
}

void slv6_P_STRD_M3_RegOff(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"D\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<", ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
  os <<"]";
}

void slv6_P_STRD_M3_Imm_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g29.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g29.cond);
  os <<"D\t";
  slv6_print_reg(os,instr->args.g29.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g29.n);
  os <<", #";
  os <<((instr->args.g29.U ? '+' : '-'));
  os <<std::hex <<(uint32_t)(instr->args.g29.immedHL);
  os <<"]!";
}

void slv6_P_STRD_M3_Reg_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"D\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<", ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
  os <<"]!";
}

void slv6_P_STRD_M3_Imm_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g29.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g29.cond);
  os <<"D\t";
  slv6_print_reg(os,instr->args.g29.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g29.n);
  os <<"], #";
  os <<((instr->args.g29.U ? '+' : '-'));
  os <<std::hex <<(uint32_t)(instr->args.g29.immedHL);
}

void slv6_P_STRD_M3_Reg_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"D\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<"], ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
}

void slv6_P_STREX(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STREX";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
  os <<", [";
  slv6_print_reg(os,instr->args.g5.n);
  os <<"]";
}

void slv6_P_STRH_M3_ImmOff(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g29.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g29.cond);
  os <<"H\t";
  slv6_print_reg(os,instr->args.g29.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g29.n);
  os <<", #";
  os <<((instr->args.g29.U ? '+' : '-'));
  os <<std::hex <<(uint32_t)(instr->args.g29.immedHL);
  os <<"]";
}

void slv6_P_STRH_M3_RegOff(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"H\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<", ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
  os <<"]";
}

void slv6_P_STRH_M3_Imm_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g29.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g29.cond);
  os <<"H\t";
  slv6_print_reg(os,instr->args.g29.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g29.n);
  os <<", #";
  os <<((instr->args.g29.U ? '+' : '-'));
  os <<std::hex <<(uint32_t)(instr->args.g29.immedHL);
  os <<"]!";
}

void slv6_P_STRH_M3_Reg_preInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"H\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<", ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
  os <<"]!";
}

void slv6_P_STRH_M3_Imm_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g29.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g29.cond);
  os <<"H\t";
  slv6_print_reg(os,instr->args.g29.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g29.n);
  os <<"], #";
  os <<((instr->args.g29.U ? '+' : '-'));
  os <<std::hex <<(uint32_t)(instr->args.g29.immedHL);
}

void slv6_P_STRH_M3_Reg_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"H\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<"], ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
}

void slv6_P_STRT_M2_Imm_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g1.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g1.cond);
  os <<"T\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<"], #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
}

void slv6_P_STRT_M2_Reg_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (instr->args.g27.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g27.cond);
  os <<"T\t";
  slv6_print_reg(os,instr->args.g27.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g27.n);
  os <<"], ";
  os <<((instr->args.g27.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g27.m);
}

void slv6_P_STRT_M2_ScReg_postInd(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g28.shift) {
case 0: {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"T\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 1: {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"T\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 2: {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"T\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} return;
case 3: if (instr->args.g28.shift_imm) {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"T\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g28.shift_imm ? instr->args.g28.shift_imm : 32);
} else {
  os <<"STR";
  if (instr->args.g28.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g28.cond);
  os <<"T\t";
  slv6_print_reg(os,instr->args.g28.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g28.n);
  os <<"], ";
  os <<((instr->args.g28.U ? '+' : '-'));
  slv6_print_reg(os,instr->args.g28.m);
  os <<", RRX";
} return;
}
}

void slv6_P_SUB_M1_Reg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB";
  if (instr->args.g20.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g20.cond);
  if (instr->args.g20.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g20.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.m);
}

void slv6_P_SUB_M1_LSLReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", LSL ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_SUB_M1_LSRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_SUB_M1_LSRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", LSR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_SUB_M1_ASRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", ASR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_SUB_M1_RRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB";
  if (instr->args.g18.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g18.cond);
  if (instr->args.g18.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g18.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g18.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g18.shift_imm ? instr->args.g18.shift_imm : 32);
}

void slv6_P_SUB_M1_RRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB";
  if (instr->args.g19.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g19.cond);
  if (instr->args.g19.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g19.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g19.m);
  os <<", ROR ";
  slv6_print_reg(os,instr->args.g19.s);
}

void slv6_P_SUB_M1_RRE(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB";
  if (instr->args.g20.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g20.cond);
  if (instr->args.g20.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g20.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g20.m);
  os <<", RRX";
}

void slv6_P_SWI(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SWI";
  if (instr->args.g58.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g58.cond);
  os <<"\t";
  os <<std::hex <<(uint32_t)(get_bits(bincode,23,0));
}

void slv6_P_SWP(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SWP";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
  os <<", [";
  slv6_print_reg(os,instr->args.g5.n);
  os <<"]";
}

void slv6_P_SWPB(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SWP";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"B\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
  os <<", [";
  slv6_print_reg(os,instr->args.g5.n);
  os <<"]";
}

void slv6_P_SXTAB(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SXTAB";
  if (instr->args.g59.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g59.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g59.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g59.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g59.m);
  if (instr->args.g59.rotate) {
    os <<", ROR #";
    os <<std::dec <<(int32_t)((instr->args.g59.rotate)*8);
  }
}

void slv6_P_SXTAB16(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SXTAB16";
  if (instr->args.g59.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g59.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g59.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g59.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g59.m);
  if (instr->args.g59.rotate) {
    os <<", ROR #";
    os <<std::dec <<(int32_t)((instr->args.g59.rotate)*8);
  }
}

void slv6_P_SXTAH(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SXTAH";
  if (instr->args.g59.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g59.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g59.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g59.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g59.m);
  if (instr->args.g59.rotate) {
    os <<", ROR #";
    os <<std::dec <<(int32_t)((instr->args.g59.rotate)*8);
  }
}

void slv6_P_SXTB(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SXTB";
  if (instr->args.g60.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g60.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g60.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g60.m);
  if (instr->args.g60.rotate) {
    os <<", ROR #";
    os <<std::dec <<(int32_t)((instr->args.g60.rotate)*8);
  }
}

void slv6_P_SXTB16(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SXTB16";
  if (instr->args.g60.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g60.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g60.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g60.m);
  if (instr->args.g60.rotate) {
    os <<", ROR #";
    os <<std::dec <<(int32_t)((instr->args.g60.rotate)*8);
  }
}

void slv6_P_SXTH(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SXTH";
  if (instr->args.g60.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g60.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g60.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g60.m);
  if (instr->args.g60.rotate) {
    os <<", ROR #";
    os <<std::dec <<(int32_t)((instr->args.g60.rotate)*8);
  }
}

void slv6_P_TEQ_M1_Imm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TEQ";
  if (instr->args.g10.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g10.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g10.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g10.immed_rotated);
}

void slv6_P_TEQ_M1_Reg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TEQ";
  if (instr->args.g4.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g4.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g4.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g4.m);
}

void slv6_P_TEQ_M1_LSLImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TEQ";
  if (instr->args.g23.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g23.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g23.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g23.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g23.shift_imm ? instr->args.g23.shift_imm : 32);
}

void slv6_P_TEQ_M1_LSLReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TEQ";
  if (instr->args.g24.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g24.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g24.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g24.m);
  os <<", LSL ";
  slv6_print_reg(os,instr->args.g24.s);
}

void slv6_P_TEQ_M1_LSRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TEQ";
  if (instr->args.g23.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g23.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g23.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g23.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g23.shift_imm ? instr->args.g23.shift_imm : 32);
}

void slv6_P_TEQ_M1_LSRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TEQ";
  if (instr->args.g24.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g24.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g24.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g24.m);
  os <<", LSR ";
  slv6_print_reg(os,instr->args.g24.s);
}

void slv6_P_TEQ_M1_ASRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TEQ";
  if (instr->args.g23.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g23.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g23.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g23.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g23.shift_imm ? instr->args.g23.shift_imm : 32);
}

void slv6_P_TEQ_M1_ASRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TEQ";
  if (instr->args.g24.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g24.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g24.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g24.m);
  os <<", ASR ";
  slv6_print_reg(os,instr->args.g24.s);
}

void slv6_P_TEQ_M1_RRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TEQ";
  if (instr->args.g23.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g23.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g23.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g23.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g23.shift_imm ? instr->args.g23.shift_imm : 32);
}

void slv6_P_TEQ_M1_RRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TEQ";
  if (instr->args.g24.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g24.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g24.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g24.m);
  os <<", ROR ";
  slv6_print_reg(os,instr->args.g24.s);
}

void slv6_P_TEQ_M1_RRE(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TEQ";
  if (instr->args.g4.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g4.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g4.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g4.m);
  os <<", RRX";
}

void slv6_P_TST_M1_LSLImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TST";
  if (instr->args.g23.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g23.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g23.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g23.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g23.shift_imm ? instr->args.g23.shift_imm : 32);
}

void slv6_P_TST_M1_LSLReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TST";
  if (instr->args.g24.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g24.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g24.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g24.m);
  os <<", LSL ";
  slv6_print_reg(os,instr->args.g24.s);
}

void slv6_P_TST_M1_LSRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TST";
  if (instr->args.g23.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g23.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g23.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g23.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g23.shift_imm ? instr->args.g23.shift_imm : 32);
}

void slv6_P_TST_M1_LSRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TST";
  if (instr->args.g24.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g24.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g24.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g24.m);
  os <<", LSR ";
  slv6_print_reg(os,instr->args.g24.s);
}

void slv6_P_TST_M1_ASRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TST";
  if (instr->args.g23.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g23.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g23.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g23.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g23.shift_imm ? instr->args.g23.shift_imm : 32);
}

void slv6_P_TST_M1_ASRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TST";
  if (instr->args.g24.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g24.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g24.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g24.m);
  os <<", ASR ";
  slv6_print_reg(os,instr->args.g24.s);
}

void slv6_P_TST_M1_RRImm(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TST";
  if (instr->args.g23.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g23.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g23.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g23.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g23.shift_imm ? instr->args.g23.shift_imm : 32);
}

void slv6_P_TST_M1_RRReg(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TST";
  if (instr->args.g24.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g24.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g24.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g24.m);
  os <<", ROR ";
  slv6_print_reg(os,instr->args.g24.s);
}

void slv6_P_TST_M1_RRE(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TST";
  if (instr->args.g4.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g4.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g4.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g4.m);
  os <<", RRX";
}

void slv6_P_UADD16(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UADD16";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_UADD8(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UADD8";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_UADDSUBX(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UADDSUBX";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_UHADD16(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UHADD16";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_UHADD8(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UHADD8";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_UHADDSUBX(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UHADDSUBX";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_UHSUB16(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UHSUB16";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_UHSUB8(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UHSUB8";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_UHSUBADDX(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UHSUBADDX";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_UMAAL(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UMAAL";
  if (instr->args.g16.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g16.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g16.dLo);
  os <<", ";
  slv6_print_reg(os,instr->args.g16.dHi);
  os <<", ";
  slv6_print_reg(os,instr->args.g16.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g16.s);
}

void slv6_P_UMLAL(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UMLAL";
  if (instr->args.g46.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g46.cond);
  if (instr->args.g46.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g46.dLo);
  os <<", ";
  slv6_print_reg(os,instr->args.g46.dHi);
  os <<", ";
  slv6_print_reg(os,instr->args.g46.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g46.s);
}

void slv6_P_UMULL(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UMULL";
  if (instr->args.g46.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g46.cond);
  if (instr->args.g46.S)  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g46.dLo);
  os <<", ";
  slv6_print_reg(os,instr->args.g46.dHi);
  os <<", ";
  slv6_print_reg(os,instr->args.g46.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g46.s);
}

void slv6_P_UQADD16(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UQADD16";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_UQADD8(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UQADD8";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_UQADDSUBX(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UQADDSUBX";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_UQSUB16(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UQSUB16";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_UQSUB8(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UQSUB8";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_UQSUBADDX(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UQSUBADDX";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_USAD8(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"USAD8";
  if (instr->args.g14.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g14.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g14.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g14.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g14.s);
}

void slv6_P_USADA8(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"USADA8";
  if (instr->args.g61.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g61.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g61.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g61.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g61.s);
  os <<", ";
  slv6_print_reg(os,instr->args.g61.n);
}

void slv6_P_USAT(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"USAT";
  if (instr->args.g56.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g56.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g56.d);
  os <<", #";
  os <<std::dec <<(int32_t)(instr->args.g56.sat_imm);
  os <<", ";
  slv6_print_reg(os,instr->args.g56.m);
  if (instr->args.g56.shift) {
    os <<", ";
    os <<"  ASR #";
    os <<std::dec <<(instr->args.g56.shift_imm ? instr->args.g56.shift_imm : 32);
  } else if (instr->args.g56.shift_imm) {
    os <<", ";
    os <<"  LSL #";
    os <<std::dec <<(int32_t)(instr->args.g56.shift_imm);
  }
}

void slv6_P_USAT16(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"USAT16";
  if (instr->args.g57.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g57.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g57.d);
  os <<", #";
  os <<std::dec <<(int32_t)(instr->args.g57.sat_imm);
  os <<", ";
  slv6_print_reg(os,instr->args.g57.m);
}

void slv6_P_USUB16(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"USUB16";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_USUB8(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"USUB8";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_USUBADDX(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"USUBADDX";
  if (instr->args.g5.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g5.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_UXTAB(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UXTAB";
  if (instr->args.g59.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g59.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g59.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g59.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g59.m);
  if (instr->args.g59.rotate) {
    os <<", ROR #";
    os <<std::dec <<(int32_t)((instr->args.g59.rotate)*8);
  }
}

void slv6_P_UXTAB16(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UXTAB16";
  if (instr->args.g59.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g59.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g59.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g59.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g59.m);
  if (instr->args.g59.rotate) {
    os <<", ROR #";
    os <<std::dec <<(int32_t)((instr->args.g59.rotate)*8);
  }
}

void slv6_P_UXTAH(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UXTAH";
  if (instr->args.g59.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g59.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g59.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g59.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g59.m);
  if (instr->args.g59.rotate) {
    os <<", ROR #";
    os <<std::dec <<(int32_t)((instr->args.g59.rotate)*8);
  }
}

void slv6_P_UXTB(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UXTB";
  if (instr->args.g60.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g60.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g60.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g60.m);
  if (instr->args.g60.rotate) {
    os <<", ROR #";
    os <<std::dec <<(int32_t)((instr->args.g60.rotate)*8);
  }
}

void slv6_P_UXTB16(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UXTB16";
  if (instr->args.g60.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g60.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g60.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g60.m);
  if (instr->args.g60.rotate) {
    os <<", ROR #";
    os <<std::dec <<(int32_t)((instr->args.g60.rotate)*8);
  }
}

void slv6_P_UXTH(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UXTH";
  if (instr->args.g60.cond!=0xe) slv6_print_cond(os,(SLv6_Condition)instr->args.g60.cond);
  os <<"\t";
  slv6_print_reg(os,instr->args.g60.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g60.m);
  if (instr->args.g60.rotate) {
    os <<", ROR #";
    os <<std::dec <<(int32_t)((instr->args.g60.rotate)*8);
  }
}

void slv6_P_Tb_LDR1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR\t";
  slv6_print_reg(os,instr->args.g62.d);
  os <<", [";
  slv6_print_reg(os,instr->args.g62.n);
  os <<", #";
  os <<std::hex <<(uint32_t)(instr->args.g62.immed_5);
  os <<" * 4]";
}

void slv6_P_Tb_CPY(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CPY\t";
  slv6_print_reg(os,instr->args.g63.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g63.m);
}

void slv6_P_Tb_STR1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR\t";
  slv6_print_reg(os,instr->args.g62.d);
  os <<", [";
  slv6_print_reg(os,instr->args.g62.n);
  os <<", #";
  os <<std::hex <<(uint32_t)(instr->args.g62.immed_5);
  os <<" * 4]";
}

void slv6_P_Tb_B1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"B";
  slv6_print_cond(os,instr->args.g64.cond);
  os <<"\t";
  if (instr->args.g64.simmed_8_ext>>31) {
    os <<"PC-#";
    os <<std::hex <<(uint32_t)(-instr->args.g64.simmed_8_ext);
  } else {
    os <<"PC+#";
  os <<std::hex <<(uint32_t)(instr->args.g64.simmed_8_ext);
  }
}

void slv6_P_Tb_LSL1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LSL\t";
  slv6_print_reg(os,instr->args.g65.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g65.m);
  os <<", #";
  os <<std::hex <<(uint32_t)(instr->args.g65.immed_5);
}

void slv6_P_Tb_ADD3(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD\t";
  slv6_print_reg(os,instr->args.g66.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g66.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g66.m);
}

void slv6_P_Tb_MOV1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV\t";
  slv6_print_reg(os,instr->args.g67.d);
  os <<", #";
  os <<std::hex <<(uint32_t)(instr->args.g67.immed_8);
}

void slv6_P_Tb_CMP2(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMP\t";
  slv6_print_reg(os,instr->args.g68.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g68.m);
}

void slv6_P_Tb_LDR3(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR\t";
  slv6_print_reg(os,instr->args.g67.d);
  os <<", [PC, #";
  os <<std::hex <<(uint32_t)(instr->args.g67.immed_8);
  os <<" * 4]";
}

void slv6_P_Tb_EOR(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR\t";
  slv6_print_reg(os,instr->args.g63.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g63.m);
}

void slv6_P_Tb_SUB2(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB\t";
  slv6_print_reg(os,instr->args.g67.d);
  os <<", #";
  os <<std::hex <<(uint32_t)(instr->args.g67.immed_8);
}

void slv6_P_Tb_MOV2(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV\t";
  slv6_print_reg(os,instr->args.g69.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g69.n);
}

void slv6_P_Tb_ADD2(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD\t";
  slv6_print_reg(os,instr->args.g67.d);
  os <<", #";
  os <<std::hex <<(uint32_t)(instr->args.g67.immed_8);
}

void slv6_P_Tb_LDR4(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR\t";
  slv6_print_reg(os,instr->args.g67.d);
  os <<", [SP, #";
  os <<std::hex <<(uint32_t)(instr->args.g67.immed_8);
  os <<" * 4]";
}

void slv6_P_Tb_AND(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"AND\t";
  slv6_print_reg(os,instr->args.g63.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g63.m);
}

void slv6_P_Tb_LSR1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LSR\t";
  slv6_print_reg(os,instr->args.g65.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g65.m);
  os <<", #";
  os <<std::hex <<(uint32_t)(instr->args.g65.immed_5);
}

void slv6_P_Tb_LDR2(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR\t";
  slv6_print_reg(os,instr->args.g66.d);
  os <<", [";
  slv6_print_reg(os,instr->args.g66.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g66.m);
  os <<"]";
}

void slv6_P_Tb_ADD4(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD\t";
  slv6_print_reg(os,instr->args.g63.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g63.m);
}

void slv6_P_Tb_CMP1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMP\t";
  slv6_print_reg(os,instr->args.g70.n);
  os <<", #";
  os <<std::hex <<(uint32_t)(instr->args.g70.immed_8);
}

void slv6_P_Tb_ORR(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR\t";
  slv6_print_reg(os,instr->args.g63.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g63.m);
}

void slv6_P_Tb_STR3(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR\t";
  slv6_print_reg(os,instr->args.g67.d);
  os <<", [SP, #";
  os <<std::hex <<(uint32_t)(instr->args.g67.immed_8);
  os <<" * 4]";
}

void slv6_P_Tb_ROR(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ROR\t";
  slv6_print_reg(os,instr->args.g71.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g71.s);
}

void slv6_P_Tb_BL(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BL, BLX(1): prefix or suffix";
}

void slv6_P_Tb_B2(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"B\t";
  if (instr->args.g73.simmed_11_ext>>31) {
    os <<"PC-#";
    os <<std::hex <<(uint32_t)(-instr->args.g73.simmed_11_ext);
  } else {
    os <<"PC+#";
  os <<std::hex <<(uint32_t)(instr->args.g73.simmed_11_ext);
  }
}

void slv6_P_Tb_NEG(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"NEG\t";
  slv6_print_reg(os,instr->args.g63.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g63.m);
}

void slv6_P_Tb_LDRB1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDRB\t";
  slv6_print_reg(os,instr->args.g62.d);
  os <<", [";
  slv6_print_reg(os,instr->args.g62.n);
  os <<", #";
  os <<std::hex <<(uint32_t)(instr->args.g62.immed_5);
  os <<"]";
}

void slv6_P_Tb_PUSH(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"PUSH\t";
  slv6_print_reglist(os,instr->args.g74.register_list|((uint16_t)instr->args.g74.R<<14));
}

void slv6_P_Tb_POP(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"POP\t";
  slv6_print_reglist(os,instr->args.g74.register_list|((uint16_t)instr->args.g74.R<<15));
}

void slv6_P_Tb_CMP3(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMP\t";
  slv6_print_reg(os,instr->args.g68.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g68.m);
}

void slv6_P_Tb_SUB4(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB\tSP, #";
  os <<std::hex <<(uint32_t)(instr->args.g75.immed_7);
  os <<" * 4";
}

void slv6_P_Tb_ADD7(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD\tSP, #";
  os <<std::hex <<(uint32_t)(instr->args.g75.immed_7);
  os <<" * 4";
}

void slv6_P_Tb_ADD6(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD\t";
  slv6_print_reg(os,instr->args.g67.d);
  os <<", SP, #";
  os <<std::hex <<(uint32_t)(instr->args.g67.immed_8);
  os <<" * 4";
}

void slv6_P_Tb_BX(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BX\t";
  slv6_print_reg(os,instr->args.g76.m);
}

void slv6_P_Tb_STRB1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STRB\t";
  slv6_print_reg(os,instr->args.g62.d);
  os <<", [";
  slv6_print_reg(os,instr->args.g62.n);
  os <<", #";
  os <<std::hex <<(uint32_t)(instr->args.g62.immed_5);
  os <<"]";
}

void slv6_P_Tb_LDRB2(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDRB\t";
  slv6_print_reg(os,instr->args.g66.d);
  os <<", [";
  slv6_print_reg(os,instr->args.g66.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g66.m);
  os <<"]";
}

void slv6_P_Tb_ADC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADC\t";
  slv6_print_reg(os,instr->args.g63.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g63.m);
}

void slv6_P_Tb_SUB3(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB\t";
  slv6_print_reg(os,instr->args.g66.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g66.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g66.m);
}

void slv6_P_Tb_SUB1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB\t";
  slv6_print_reg(os,instr->args.g77.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g77.n);
  os <<", #";
  os <<std::hex <<(uint32_t)(instr->args.g77.immed_3);
}

void slv6_P_Tb_LSR2(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LSR\t";
  slv6_print_reg(os,instr->args.g71.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g71.s);
}

void slv6_P_Tb_STR2(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR\t";
  slv6_print_reg(os,instr->args.g66.d);
  os <<", [";
  slv6_print_reg(os,instr->args.g66.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g66.m);
  os <<"]";
}

void slv6_P_Tb_STRB2(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STRB\t";
  slv6_print_reg(os,instr->args.g66.d);
  os <<", [";
  slv6_print_reg(os,instr->args.g66.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g66.m);
  os <<"]";
}

void slv6_P_Tb_LDMIA(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDMIA\t";
  slv6_print_reg(os,instr->args.g78.n);
  os <<"!, ";
  slv6_print_reglist(os,instr->args.g78.register_list);
}

void slv6_P_Tb_STMIA(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STMIA\t";
  slv6_print_reg(os,instr->args.g78.n);
  os <<"!, ";
  slv6_print_reglist(os,instr->args.g78.register_list);
}

void slv6_P_Tb_ADD1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD\t";
  slv6_print_reg(os,instr->args.g77.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g77.n);
  os <<", #";
  os <<std::hex <<(uint32_t)(instr->args.g77.immed_3);
}

void slv6_P_Tb_MUL(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MUL\t";
  slv6_print_reg(os,instr->args.g63.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g63.m);
}

void slv6_P_Tb_ASR1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ASR\t";
  slv6_print_reg(os,instr->args.g65.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g65.m);
  os <<", #";
  os <<std::hex <<(uint32_t)(instr->args.g65.immed_5);
}

void slv6_P_Tb_MVN(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MVN\t";
  slv6_print_reg(os,instr->args.g63.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g63.m);
}

void slv6_P_Tb_LDRH1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDRH\t";
  slv6_print_reg(os,instr->args.g62.d);
  os <<", [";
  slv6_print_reg(os,instr->args.g62.n);
  os <<", #";
  os <<std::hex <<(uint32_t)(instr->args.g62.immed_5);
  os <<" * 2]";
}

void slv6_P_Tb_TST(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TST\t";
  slv6_print_reg(os,instr->args.g68.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g68.m);
}

void slv6_P_Tb_BIC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BIC\t";
  slv6_print_reg(os,instr->args.g63.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g63.m);
}

void slv6_P_Tb_LSL2(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LSL\t";
  slv6_print_reg(os,instr->args.g71.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g71.s);
}

void slv6_P_Tb_ADD5(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD\t";
  slv6_print_reg(os,instr->args.g67.d);
  os <<", PC, #";
  os <<std::hex <<(uint32_t)(instr->args.g67.immed_8);
  os <<" * 4";
}

void slv6_P_Tb_ASR2(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ASR\t";
  slv6_print_reg(os,instr->args.g71.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g71.s);
}

void slv6_P_Tb_BKPT(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BKPT\t";
  os <<std::hex <<(uint32_t)(get_bits(bincode,7,0));
}

void slv6_P_Tb_BLX2(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BLX\t";
  slv6_print_reg(os,instr->args.g76.m);
}

void slv6_P_Tb_CMN(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMN\t";
  slv6_print_reg(os,instr->args.g68.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g68.m);
}

void slv6_P_Tb_CPS(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CPS";
  if (instr->args.g79.imod==0)  os <<"IE";
  else if (instr->args.g79.imod==1)  os <<"ID";
  os <<"\t";
  if (instr->args.g79.A)  os <<'a';
  if (instr->args.g79.I)  os <<'i';
  if (instr->args.g79.F)  os <<'f';
}

void slv6_P_Tb_LDRH2(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDRH\t";
  slv6_print_reg(os,instr->args.g66.d);
  os <<", [";
  slv6_print_reg(os,instr->args.g66.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g66.m);
  os <<"]";
}

void slv6_P_Tb_LDRSB(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDRSB\t";
  slv6_print_reg(os,instr->args.g66.d);
  os <<", [";
  slv6_print_reg(os,instr->args.g66.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g66.m);
  os <<"]";
}

void slv6_P_Tb_LDRSH(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDRSH\t";
  slv6_print_reg(os,instr->args.g66.d);
  os <<", [";
  slv6_print_reg(os,instr->args.g66.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g66.m);
  os <<"]";
}

void slv6_P_Tb_REV(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"REV\t";
  slv6_print_reg(os,instr->args.g69.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g69.n);
}

void slv6_P_Tb_REV16(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"REV16\t";
  slv6_print_reg(os,instr->args.g69.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g69.n);
}

void slv6_P_Tb_REVSH(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"REVSH\t";
  slv6_print_reg(os,instr->args.g69.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g69.n);
}

void slv6_P_Tb_SBC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SBC\t";
  slv6_print_reg(os,instr->args.g63.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g63.m);
}

void slv6_P_Tb_SETEND(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SETEND\t";
  os <<((instr->args.g43.E ? "BE" : "LE"));
}

void slv6_P_Tb_STRH1(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STRH\t";
  slv6_print_reg(os,instr->args.g62.d);
  os <<", [";
  slv6_print_reg(os,instr->args.g62.n);
  os <<", #";
  os <<std::hex <<(uint32_t)(instr->args.g62.immed_5);
  os <<" * 2]";
}

void slv6_P_Tb_STRH2(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STRH\t";
  slv6_print_reg(os,instr->args.g66.d);
  os <<", [";
  slv6_print_reg(os,instr->args.g66.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g66.m);
  os <<"]";
}

void slv6_P_Tb_SWI(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SWI\t";
  os <<std::hex <<(uint32_t)(get_bits(bincode,7,0));
}

void slv6_P_Tb_SXTB(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SXTB\t";
  slv6_print_reg(os,instr->args.g63.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g63.m);
}

void slv6_P_Tb_SXTH(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SXTH\t";
  slv6_print_reg(os,instr->args.g63.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g63.m);
}

void slv6_P_Tb_UXTB(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UXTB\t";
  slv6_print_reg(os,instr->args.g63.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g63.m);
}

void slv6_P_Tb_UXTH(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"UXTH\t";
  slv6_print_reg(os,instr->args.g63.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g63.m);
}

void slv6_P_LDR_M2_ImmOff_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
  os <<"]";
}

void slv6_P_STR_M2_ImmOff_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
  os <<"]";
}

void slv6_P_B_L1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"B";
  if (get_bit(bincode,24))  os <<'L';
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  if (instr->args.g2.pc_offset>>31) {
    os <<"PC-#";
    os <<std::hex <<(uint32_t)(-instr->args.g2.pc_offset);
  } else {
    os <<"PC+#";
  os <<std::hex <<(uint32_t)(instr->args.g2.pc_offset);
  }
}

void slv6_P_B_L0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"B";
  if (get_bit(bincode,24))  os <<'L';
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  if (instr->args.g2.pc_offset>>31) {
    os <<"PC-#";
    os <<std::hex <<(uint32_t)(-instr->args.g2.pc_offset);
  } else {
    os <<"PC+#";
  os <<std::hex <<(uint32_t)(instr->args.g2.pc_offset);
  }
}

void slv6_P_SUB_M1_Imm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_SUB_M1_Imm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_CMP_M1_Reg_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMP";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g4.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g4.m);
}

void slv6_P_ADD_M1_Imm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_ADD_M1_Imm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_ADD_M1_Reg_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_ADD_M1_Reg_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_EOR_M1_Reg_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_EOR_M1_Reg_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_AND_M1_Imm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"AND";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_AND_M1_Imm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"AND";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_MOV_M1_LSRImm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g6.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g6.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g6.shift_imm ? instr->args.g6.shift_imm : 32);
}

void slv6_P_MOV_M1_LSRImm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g6.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g6.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g6.shift_imm ? instr->args.g6.shift_imm : 32);
}

void slv6_P_CPY_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CPY";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g7.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g7.m);
}

void slv6_P_MOV_M1_LSLImm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g6.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g6.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g6.shift_imm ? instr->args.g6.shift_imm : 32);
}

void slv6_P_MOV_M1_LSLImm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g6.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g6.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g6.shift_imm ? instr->args.g6.shift_imm : 32);
}

void slv6_P_MOV_M1_Imm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g8.d);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g8.immed_rotated);
}

void slv6_P_MOV_M1_Imm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g8.d);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g8.immed_rotated);
}

void slv6_P_LDM1_M4_IA_W1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDM";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"IA";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  if (get_bit(bincode,21))  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
}

void slv6_P_LDM1_M4_IA_W0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDM";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"IA";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  if (get_bit(bincode,21))  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
}

void slv6_P_CMP_M1_Imm_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMP";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g10.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g10.immed_rotated);
}

void slv6_P_LDR_M2_ScRegOff_U1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g11.shift) {
case 0: {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 1: {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 2: {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 3: if (instr->args.g11.shift_imm) {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} else {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", RRX]";
} return;
}
}

void slv6_P_LDR_M2_ScRegOff_U0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g11.shift) {
case 0: {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 1: {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 2: {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 3: if (instr->args.g11.shift_imm) {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} else {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", RRX]";
} return;
}
}

void slv6_P_BX_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BX";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g12.m);
}

void slv6_P_ADD_M1_LSLImm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_ADD_M1_LSLImm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_LDRB_M2_ImmOff_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"B\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
  os <<"]";
}

void slv6_P_ORR_M1_Reg_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_ORR_M1_Reg_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_MOV_M1_RRImm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g6.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g6.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g6.shift_imm ? instr->args.g6.shift_imm : 32);
}

void slv6_P_MOV_M1_RRImm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g6.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g6.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g6.shift_imm ? instr->args.g6.shift_imm : 32);
}

void slv6_P_LDR_M2_Imm_postInd_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<"], #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
}

void slv6_P_EOR_M1_RRImm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_EOR_M1_RRImm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_AND_M1_Reg_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"AND";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_AND_M1_Reg_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"AND";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_STR_M2_Imm_preInd_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
  os <<"]!";
}

void slv6_P_STRB_M2_ImmOff_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"B\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
  os <<"]";
}

void slv6_P_ORR_M1_LSLImm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_ORR_M1_LSLImm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_ADC_M1_Reg_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADC";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_ADC_M1_Reg_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADC";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_LDRB_M2_RegOff_U1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"B\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g5.m);
  os <<"]";
}

void slv6_P_LDRB_M2_RegOff_U0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"B\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g5.m);
  os <<"]";
}

void slv6_P_RSB_M1_Reg_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSB";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_RSB_M1_Reg_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSB";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_BIC_M1_Imm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BIC";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_BIC_M1_Imm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"BIC";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_MVN_M1_Imm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MVN";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g8.d);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g8.immed_rotated);
}

void slv6_P_MVN_M1_Imm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MVN";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g8.d);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g8.immed_rotated);
}

void slv6_P_ORR_M1_LSRImm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_ORR_M1_LSRImm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_EOR_M1_LSRImm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_EOR_M1_LSRImm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_LDR_M2_RegOff_U1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g5.m);
  os <<"]";
}

void slv6_P_LDR_M2_RegOff_U0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g5.m);
  os <<"]";
}

void slv6_P_MOV_M1_LSRReg_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g14.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g14.m);
  os <<", LSR ";
  slv6_print_reg(os,instr->args.g14.s);
}

void slv6_P_MOV_M1_LSRReg_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g14.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g14.m);
  os <<", LSR ";
  slv6_print_reg(os,instr->args.g14.s);
}

void slv6_P_STRB_M2_RegOff_U1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"B\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g5.m);
  os <<"]";
}

void slv6_P_STRB_M2_RegOff_U0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"B\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g5.m);
  os <<"]";
}

void slv6_P_STR_M2_ScRegOff_U1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g11.shift) {
case 0: {
  os <<"STR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 1: {
  os <<"STR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 2: {
  os <<"STR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 3: if (instr->args.g11.shift_imm) {
  os <<"STR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} else {
  os <<"STR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", RRX]";
} return;
}
}

void slv6_P_STR_M2_ScRegOff_U0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g11.shift) {
case 0: {
  os <<"STR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 1: {
  os <<"STR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 2: {
  os <<"STR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 3: if (instr->args.g11.shift_imm) {
  os <<"STR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} else {
  os <<"STR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", RRX]";
} return;
}
}

void slv6_P_CMN_M1_Reg_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMN";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g4.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g4.m);
}

void slv6_P_STR_M2_Reg_postInd_U1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g5.n);
  os <<"], ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_STR_M2_Reg_postInd_U0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g5.n);
  os <<"], ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g5.m);
}

void slv6_P_STR_M2_RegOff_U1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g5.m);
  os <<"]";
}

void slv6_P_STR_M2_RegOff_U0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g5.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g5.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g5.m);
  os <<"]";
}

void slv6_P_EOR_M1_LSLImm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_EOR_M1_LSLImm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_RSB_M1_Imm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSB";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_RSB_M1_Imm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSB";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_MOV_M1_ASRImm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g6.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g6.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g6.shift_imm ? instr->args.g6.shift_imm : 32);
}

void slv6_P_MOV_M1_ASRImm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g6.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g6.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g6.shift_imm ? instr->args.g6.shift_imm : 32);
}

void slv6_P_ADD_M1_RRImm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_ADD_M1_RRImm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_RSB_M1_LSLImm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSB";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_RSB_M1_LSLImm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSB";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_STRB_M2_Imm_postInd_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"B\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<"], #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
}

void slv6_P_STM1_M4_IA_W1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STM";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"IA";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  if (get_bit(bincode,21))  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
}

void slv6_P_STM1_M4_IA_W0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STM";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"IA";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  if (get_bit(bincode,21))  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
}

void slv6_P_TST_M1_Imm_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TST";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g10.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g10.immed_rotated);
}

void slv6_P_STM1_M4_DB_W1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STM";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"DB";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  if (get_bit(bincode,21))  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
}

void slv6_P_STM1_M4_DB_W0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STM";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"DB";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  if (get_bit(bincode,21))  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
}

void slv6_P_MVN_M1_Reg_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MVN";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g7.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g7.m);
}

void slv6_P_MVN_M1_Reg_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MVN";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g7.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g7.m);
}

void slv6_P_STM1_M4_IB_W1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STM";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"IB";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  if (get_bit(bincode,21))  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
}

void slv6_P_STM1_M4_IB_W0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STM";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"IB";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  if (get_bit(bincode,21))  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
}

void slv6_P_ADD_M1_LSRImm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_ADD_M1_LSRImm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ADD";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_STR_M2_Imm_postInd_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"STR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<"], #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
}

void slv6_P_LDRB_M2_ScRegOff_U1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g11.shift) {
case 0: {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"B\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 1: {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"B\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 2: {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"B\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 3: if (instr->args.g11.shift_imm) {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"B\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} else {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"B\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", RRX]";
} return;
}
}

void slv6_P_LDRB_M2_ScRegOff_U0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
switch (instr->args.g11.shift) {
case 0: {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"B\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 1: {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"B\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", LSR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 2: {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"B\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} return;
case 3: if (instr->args.g11.shift_imm) {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"B\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", ROR #";
  os <<std::dec <<(instr->args.g11.shift_imm ? instr->args.g11.shift_imm : 32);
  os <<"]";
} else {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"B\t";
  slv6_print_reg(os,instr->args.g11.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g11.n);
  os <<", ";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  slv6_print_reg(os,instr->args.g11.m);
  os <<", RRX]";
} return;
}
}

void slv6_P_SUB_M1_LSLImm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_SUB_M1_LSLImm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", LSL #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_LDM1_M4_IB_W1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDM";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"IB";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  if (get_bit(bincode,21))  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
}

void slv6_P_LDM1_M4_IB_W0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDM";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"IB";
  os <<"\t";
  slv6_print_reg(os,instr->args.g9.n);
  if (get_bit(bincode,21))  os <<'!';
  os <<", ";
  slv6_print_reglist(os,instr->args.g9.register_list);
}

void slv6_P_LDRH_M3_ImmOff_U1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"H\t";
  slv6_print_reg(os,instr->args.g15.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g15.n);
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(instr->args.g15.immedHL);
  os <<"]";
}

void slv6_P_LDRH_M3_ImmOff_U0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"H\t";
  slv6_print_reg(os,instr->args.g15.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g15.n);
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(instr->args.g15.immedHL);
  os <<"]";
}

void slv6_P_LDR_M2_Imm_preInd_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g1.d);
  os <<", ";
  os <<"[";
  slv6_print_reg(os,instr->args.g1.n);
  os <<", #";
  os <<((get_bit(bincode,23) ? '+' : '-'));
  os <<std::hex <<(uint32_t)(get_bits(bincode,11,0));
  os <<"]!";
}

void slv6_P_SMULL_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SMULL";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g16.dLo);
  os <<", ";
  slv6_print_reg(os,instr->args.g16.dHi);
  os <<", ";
  slv6_print_reg(os,instr->args.g16.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g16.s);
}

void slv6_P_SMULL_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SMULL";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g16.dLo);
  os <<", ";
  slv6_print_reg(os,instr->args.g16.dHi);
  os <<", ";
  slv6_print_reg(os,instr->args.g16.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g16.s);
}

void slv6_P_RSB_M1_ASRImm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSB";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_RSB_M1_ASRImm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"RSB";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_TST_M1_Reg_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"TST";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g4.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g4.m);
}

void slv6_P_EOR_M1_Imm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_EOR_M1_Imm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"EOR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_ORR_M1_ASRImm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_ORR_M1_ASRImm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_ORR_M1_Imm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_ORR_M1_Imm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"ORR";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g3.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g3.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g3.immed_rotated);
}

void slv6_P_SUB_M1_ASRImm_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_SUB_M1_ASRImm_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"SUB";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g13.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.n);
  os <<", ";
  slv6_print_reg(os,instr->args.g13.m);
  os <<", ASR #";
  os <<std::dec <<(instr->args.g13.shift_imm ? instr->args.g13.shift_imm : 32);
}

void slv6_P_MOV_M1_LSLReg_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g14.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g14.m);
  os <<", LSL ";
  slv6_print_reg(os,instr->args.g14.s);
}

void slv6_P_MOV_M1_LSLReg_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MOV";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g14.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g14.m);
  os <<", LSL ";
  slv6_print_reg(os,instr->args.g14.s);
}

void slv6_P_MUL_S1_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MUL";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g14.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g14.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g14.s);
}

void slv6_P_MUL_S0_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"MUL";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  if (get_bit(bincode,20))  os <<'S';
  os <<"\t";
  slv6_print_reg(os,instr->args.g14.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g14.m);
  os <<", ";
  slv6_print_reg(os,instr->args.g14.s);
}

void slv6_P_CMN_M1_Imm_NC(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"CMN";
  if (get_bits(bincode,31,28)!=0xe) slv6_print_cond(os,(SLv6_Condition)get_bits(bincode,31,28));
  os <<"\t";
  slv6_print_reg(os,instr->args.g10.n);
  os <<", ";
  os <<"#";
  os <<std::hex <<(uint32_t)(instr->args.g10.immed_rotated);
}

void slv6_P_Tb_LDR1_NI(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LDR\t";
  slv6_print_reg(os,instr->args.g62.d);
  os <<", [";
  slv6_print_reg(os,instr->args.g62.n);
  os <<", #";
  os <<std::hex <<(uint32_t)(get_bits(bincode,10,6));
  os <<" * 4]";
}

void slv6_P_Tb_LSL1_NI(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  os <<"LSL\t";
  slv6_print_reg(os,instr->args.g65.d);
  os <<", ";
  slv6_print_reg(os,instr->args.g65.m);
  os <<", #";
  os <<std::hex <<(uint32_t)(get_bits(bincode,10,6));
}

PrintFunction slv6_printers[SLV6_TABLE_SIZE] = {
  slv6_P_LDR_M2_ImmOff,
  slv6_P_STR_M2_ImmOff,
  slv6_P_B_L1,
  slv6_P_B_L0,
  slv6_P_SUB_M1_Imm_S1,
  slv6_P_SUB_M1_Imm_S0,
  slv6_P_CMP_M1_Reg,
  slv6_P_ADD_M1_Imm_S1,
  slv6_P_ADD_M1_Imm_S0,
  slv6_P_ADD_M1_Reg_S1,
  slv6_P_ADD_M1_Reg_S0,
  slv6_P_EOR_M1_Reg_S1,
  slv6_P_EOR_M1_Reg_S0,
  slv6_P_AND_M1_Imm_S1,
  slv6_P_AND_M1_Imm_S0,
  slv6_P_MOV_M1_LSRImm_S1,
  slv6_P_MOV_M1_LSRImm_S0,
  slv6_P_CPY,
  slv6_P_MOV_M1_LSLImm_S1,
  slv6_P_MOV_M1_LSLImm_S0,
  slv6_P_MOV_M1_Imm_S1,
  slv6_P_MOV_M1_Imm_S0,
  slv6_P_LDM1_M4_IA_W1,
  slv6_P_LDM1_M4_IA_W0,
  slv6_P_CMP_M1_Imm,
  slv6_P_LDR_M2_ScRegOff_U1,
  slv6_P_LDR_M2_ScRegOff_U0,
  slv6_P_BX,
  slv6_P_ADD_M1_LSLImm_S1,
  slv6_P_ADD_M1_LSLImm_S0,
  slv6_P_LDRB_M2_ImmOff,
  slv6_P_ORR_M1_Reg_S1,
  slv6_P_ORR_M1_Reg_S0,
  slv6_P_MOV_M1_RRImm_S1,
  slv6_P_MOV_M1_RRImm_S0,
  slv6_P_LDR_M2_Imm_postInd,
  slv6_P_EOR_M1_RRImm_S1,
  slv6_P_EOR_M1_RRImm_S0,
  slv6_P_AND_M1_Reg_S1,
  slv6_P_AND_M1_Reg_S0,
  slv6_P_STR_M2_Imm_preInd,
  slv6_P_STRB_M2_ImmOff,
  slv6_P_ORR_M1_LSLImm_S1,
  slv6_P_ORR_M1_LSLImm_S0,
  slv6_P_ADC_M1_Reg_S1,
  slv6_P_ADC_M1_Reg_S0,
  slv6_P_LDRB_M2_RegOff_U1,
  slv6_P_LDRB_M2_RegOff_U0,
  slv6_P_RSB_M1_Reg_S1,
  slv6_P_RSB_M1_Reg_S0,
  slv6_P_BIC_M1_Imm_S1,
  slv6_P_BIC_M1_Imm_S0,
  slv6_P_MVN_M1_Imm_S1,
  slv6_P_MVN_M1_Imm_S0,
  slv6_P_ORR_M1_LSRImm_S1,
  slv6_P_ORR_M1_LSRImm_S0,
  slv6_P_EOR_M1_LSRImm_S1,
  slv6_P_EOR_M1_LSRImm_S0,
  slv6_P_LDR_M2_RegOff_U1,
  slv6_P_LDR_M2_RegOff_U0,
  slv6_P_MOV_M1_LSRReg_S1,
  slv6_P_MOV_M1_LSRReg_S0,
  slv6_P_STRB_M2_RegOff_U1,
  slv6_P_STRB_M2_RegOff_U0,
  slv6_P_STR_M2_ScRegOff_U1,
  slv6_P_STR_M2_ScRegOff_U0,
  slv6_P_CMN_M1_Reg,
  slv6_P_STR_M2_Reg_postInd_U1,
  slv6_P_STR_M2_Reg_postInd_U0,
  slv6_P_STR_M2_RegOff_U1,
  slv6_P_STR_M2_RegOff_U0,
  slv6_P_EOR_M1_LSLImm_S1,
  slv6_P_EOR_M1_LSLImm_S0,
  slv6_P_RSB_M1_Imm_S1,
  slv6_P_RSB_M1_Imm_S0,
  slv6_P_MOV_M1_ASRImm_S1,
  slv6_P_MOV_M1_ASRImm_S0,
  slv6_P_ADD_M1_RRImm_S1,
  slv6_P_ADD_M1_RRImm_S0,
  slv6_P_RSB_M1_LSLImm_S1,
  slv6_P_RSB_M1_LSLImm_S0,
  slv6_P_STRB_M2_Imm_postInd,
  slv6_P_STM1_M4_IA_W1,
  slv6_P_STM1_M4_IA_W0,
  slv6_P_TST_M1_Imm,
  slv6_P_STM1_M4_DB_W1,
  slv6_P_STM1_M4_DB_W0,
  slv6_P_MVN_M1_Reg_S1,
  slv6_P_MVN_M1_Reg_S0,
  slv6_P_STM1_M4_IB_W1,
  slv6_P_STM1_M4_IB_W0,
  slv6_P_ADD_M1_LSRImm_S1,
  slv6_P_ADD_M1_LSRImm_S0,
  slv6_P_STR_M2_Imm_postInd,
  slv6_P_LDRB_M2_ScRegOff_U1,
  slv6_P_LDRB_M2_ScRegOff_U0,
  slv6_P_SUB_M1_LSLImm_S1,
  slv6_P_SUB_M1_LSLImm_S0,
  slv6_P_LDM1_M4_IB_W1,
  slv6_P_LDM1_M4_IB_W0,
  slv6_P_LDRH_M3_ImmOff_U1,
  slv6_P_LDRH_M3_ImmOff_U0,
  slv6_P_LDR_M2_Imm_preInd,
  slv6_P_SMULL_S1,
  slv6_P_SMULL_S0,
  slv6_P_RSB_M1_ASRImm_S1,
  slv6_P_RSB_M1_ASRImm_S0,
  slv6_P_TST_M1_Reg,
  slv6_P_EOR_M1_Imm_S1,
  slv6_P_EOR_M1_Imm_S0,
  slv6_P_ORR_M1_ASRImm_S1,
  slv6_P_ORR_M1_ASRImm_S0,
  slv6_P_ORR_M1_Imm_S1,
  slv6_P_ORR_M1_Imm_S0,
  slv6_P_SUB_M1_ASRImm_S1,
  slv6_P_SUB_M1_ASRImm_S0,
  slv6_P_MOV_M1_LSLReg_S1,
  slv6_P_MOV_M1_LSLReg_S0,
  slv6_P_MUL_S1,
  slv6_P_MUL_S0,
  slv6_P_CMN_M1_Imm,
  slv6_P_ADC_M1_Imm,
  slv6_P_ADC_M1_LSLImm,
  slv6_P_ADC_M1_LSLReg,
  slv6_P_ADC_M1_LSRImm,
  slv6_P_ADC_M1_LSRReg,
  slv6_P_ADC_M1_ASRImm,
  slv6_P_ADC_M1_ASRReg,
  slv6_P_ADC_M1_RRImm,
  slv6_P_ADC_M1_RRReg,
  slv6_P_ADC_M1_RRE,
  slv6_P_ADD_M1_LSLReg,
  slv6_P_ADD_M1_LSRReg,
  slv6_P_ADD_M1_ASRImm,
  slv6_P_ADD_M1_ASRReg,
  slv6_P_ADD_M1_RRReg,
  slv6_P_ADD_M1_RRE,
  slv6_P_AND_M1_LSLImm,
  slv6_P_AND_M1_LSLReg,
  slv6_P_AND_M1_LSRImm,
  slv6_P_AND_M1_LSRReg,
  slv6_P_AND_M1_ASRImm,
  slv6_P_AND_M1_ASRReg,
  slv6_P_AND_M1_RRImm,
  slv6_P_AND_M1_RRReg,
  slv6_P_AND_M1_RRE,
  slv6_P_BIC_M1_Reg,
  slv6_P_BIC_M1_LSLImm,
  slv6_P_BIC_M1_LSLReg,
  slv6_P_BIC_M1_LSRImm,
  slv6_P_BIC_M1_LSRReg,
  slv6_P_BIC_M1_ASRImm,
  slv6_P_BIC_M1_ASRReg,
  slv6_P_BIC_M1_RRImm,
  slv6_P_BIC_M1_RRReg,
  slv6_P_BIC_M1_RRE,
  slv6_P_BKPT,
  slv6_P_BLX1,
  slv6_P_BLX2,
  slv6_P_BXJ,
  slv6_P_CDP,
  slv6_P_CLZ,
  slv6_P_CMN_M1_LSLImm,
  slv6_P_CMN_M1_LSLReg,
  slv6_P_CMN_M1_LSRImm,
  slv6_P_CMN_M1_LSRReg,
  slv6_P_CMN_M1_ASRImm,
  slv6_P_CMN_M1_ASRReg,
  slv6_P_CMN_M1_RRImm,
  slv6_P_CMN_M1_RRReg,
  slv6_P_CMN_M1_RRE,
  slv6_P_CMP_M1_LSLImm,
  slv6_P_CMP_M1_LSLReg,
  slv6_P_CMP_M1_LSRImm,
  slv6_P_CMP_M1_LSRReg,
  slv6_P_CMP_M1_ASRImm,
  slv6_P_CMP_M1_ASRReg,
  slv6_P_CMP_M1_RRImm,
  slv6_P_CMP_M1_RRReg,
  slv6_P_CMP_M1_RRE,
  slv6_P_CPS,
  slv6_P_EOR_M1_LSLReg,
  slv6_P_EOR_M1_LSRReg,
  slv6_P_EOR_M1_ASRImm,
  slv6_P_EOR_M1_ASRReg,
  slv6_P_EOR_M1_RRReg,
  slv6_P_EOR_M1_RRE,
  slv6_P_LDC_M5_ImmOff,
  slv6_P_LDC_M5_Imm_preInd,
  slv6_P_LDC_M5_Imm_postInd,
  slv6_P_LDC_M5_U,
  slv6_P_LDM1_M4_DA,
  slv6_P_LDM1_M4_DB,
  slv6_P_LDM2_M4_IA,
  slv6_P_LDM2_M4_IB,
  slv6_P_LDM2_M4_DA,
  slv6_P_LDM2_M4_DB,
  slv6_P_LDM3_M4_IA,
  slv6_P_LDM3_M4_IB,
  slv6_P_LDM3_M4_DA,
  slv6_P_LDM3_M4_DB,
  slv6_P_LDR_M2_Reg_preInd,
  slv6_P_LDR_M2_ScReg_preInd,
  slv6_P_LDR_M2_Reg_postInd,
  slv6_P_LDR_M2_ScReg_postInd,
  slv6_P_LDRB_M2_Imm_preInd,
  slv6_P_LDRB_M2_Reg_preInd,
  slv6_P_LDRB_M2_ScReg_preInd,
  slv6_P_LDRB_M2_Imm_postInd,
  slv6_P_LDRB_M2_Reg_postInd,
  slv6_P_LDRB_M2_ScReg_postInd,
  slv6_P_LDRBT_M2_Imm_postInd,
  slv6_P_LDRBT_M2_Reg_postInd,
  slv6_P_LDRBT_M2_ScReg_postInd,
  slv6_P_LDRD_M3_ImmOff,
  slv6_P_LDRD_M3_RegOff,
  slv6_P_LDRD_M3_Imm_preInd,
  slv6_P_LDRD_M3_Reg_preInd,
  slv6_P_LDRD_M3_Imm_postInd,
  slv6_P_LDRD_M3_Reg_postInd,
  slv6_P_LDREX,
  slv6_P_LDRH_M3_RegOff,
  slv6_P_LDRH_M3_Imm_preInd,
  slv6_P_LDRH_M3_Reg_preInd,
  slv6_P_LDRH_M3_Imm_postInd,
  slv6_P_LDRH_M3_Reg_postInd,
  slv6_P_LDRSB_M3_ImmOff,
  slv6_P_LDRSB_M3_RegOff,
  slv6_P_LDRSB_M3_Imm_preInd,
  slv6_P_LDRSB_M3_Reg_preInd,
  slv6_P_LDRSB_M3_Imm_postInd,
  slv6_P_LDRSB_M3_Reg_postInd,
  slv6_P_LDRSH_M3_ImmOff,
  slv6_P_LDRSH_M3_RegOff,
  slv6_P_LDRSH_M3_Imm_preInd,
  slv6_P_LDRSH_M3_Reg_preInd,
  slv6_P_LDRSH_M3_Imm_postInd,
  slv6_P_LDRSH_M3_Reg_postInd,
  slv6_P_LDRT_M2_Imm_postInd,
  slv6_P_LDRT_M2_Reg_postInd,
  slv6_P_LDRT_M2_ScReg_postInd,
  slv6_P_MCR,
  slv6_P_MCRR,
  slv6_P_MLA,
  slv6_P_MOV_M1_Reg,
  slv6_P_MOV_M1_ASRReg,
  slv6_P_MOV_M1_RRReg,
  slv6_P_MOV_M1_RRE,
  slv6_P_MRC,
  slv6_P_MRRC,
  slv6_P_MRS,
  slv6_P_MSRimm,
  slv6_P_MSRreg,
  slv6_P_MVN_M1_LSLImm,
  slv6_P_MVN_M1_LSLReg,
  slv6_P_MVN_M1_LSRImm,
  slv6_P_MVN_M1_LSRReg,
  slv6_P_MVN_M1_ASRImm,
  slv6_P_MVN_M1_ASRReg,
  slv6_P_MVN_M1_RRImm,
  slv6_P_MVN_M1_RRReg,
  slv6_P_MVN_M1_RRE,
  slv6_P_ORR_M1_LSLReg,
  slv6_P_ORR_M1_LSRReg,
  slv6_P_ORR_M1_ASRReg,
  slv6_P_ORR_M1_RRImm,
  slv6_P_ORR_M1_RRReg,
  slv6_P_ORR_M1_RRE,
  slv6_P_PKHBT,
  slv6_P_PKHTB,
  slv6_P_PLD_M2_ImmOff,
  slv6_P_PLD_M2_RegOff,
  slv6_P_PLD_M2_ScRegOff,
  slv6_P_QADD,
  slv6_P_QADD16,
  slv6_P_QADD8,
  slv6_P_QADDSUBX,
  slv6_P_QDADD,
  slv6_P_QDSUB,
  slv6_P_QSUB,
  slv6_P_QSUB16,
  slv6_P_QSUB8,
  slv6_P_QSUBADDX,
  slv6_P_REV,
  slv6_P_REV16,
  slv6_P_REVSH,
  slv6_P_RFE_M4_IA,
  slv6_P_RFE_M4_IB,
  slv6_P_RFE_M4_DA,
  slv6_P_RFE_M4_DB,
  slv6_P_RSB_M1_LSLReg,
  slv6_P_RSB_M1_LSRImm,
  slv6_P_RSB_M1_LSRReg,
  slv6_P_RSB_M1_ASRReg,
  slv6_P_RSB_M1_RRImm,
  slv6_P_RSB_M1_RRReg,
  slv6_P_RSB_M1_RRE,
  slv6_P_RSC_M1_Imm,
  slv6_P_RSC_M1_Reg,
  slv6_P_RSC_M1_LSLImm,
  slv6_P_RSC_M1_LSLReg,
  slv6_P_RSC_M1_LSRImm,
  slv6_P_RSC_M1_LSRReg,
  slv6_P_RSC_M1_ASRImm,
  slv6_P_RSC_M1_ASRReg,
  slv6_P_RSC_M1_RRImm,
  slv6_P_RSC_M1_RRReg,
  slv6_P_RSC_M1_RRE,
  slv6_P_SADD16,
  slv6_P_SADD8,
  slv6_P_SADDSUBX,
  slv6_P_SBC_M1_Imm,
  slv6_P_SBC_M1_Reg,
  slv6_P_SBC_M1_LSLImm,
  slv6_P_SBC_M1_LSLReg,
  slv6_P_SBC_M1_LSRImm,
  slv6_P_SBC_M1_LSRReg,
  slv6_P_SBC_M1_ASRImm,
  slv6_P_SBC_M1_ASRReg,
  slv6_P_SBC_M1_RRImm,
  slv6_P_SBC_M1_RRReg,
  slv6_P_SBC_M1_RRE,
  slv6_P_SEL,
  slv6_P_SETEND,
  slv6_P_SHADD16,
  slv6_P_SHADD8,
  slv6_P_SHADDSUBX,
  slv6_P_SHSUB16,
  slv6_P_SHSUB8,
  slv6_P_SHSUBADDX,
  slv6_P_SMLAxy,
  slv6_P_SMLAD,
  slv6_P_SMLAL,
  slv6_P_SMLALxy,
  slv6_P_SMLALD,
  slv6_P_SMLAWy,
  slv6_P_SMLSD,
  slv6_P_SMLSLD,
  slv6_P_SMMLA,
  slv6_P_SMMLS,
  slv6_P_SMMUL,
  slv6_P_SMUAD,
  slv6_P_SMULxy,
  slv6_P_SMULWy,
  slv6_P_SMUSD,
  slv6_P_SRS_M4_IA,
  slv6_P_SRS_M4_IB,
  slv6_P_SRS_M4_DA,
  slv6_P_SRS_M4_DB,
  slv6_P_SSAT,
  slv6_P_SSAT16,
  slv6_P_SSUB16,
  slv6_P_SSUB8,
  slv6_P_SSUBADDX,
  slv6_P_STC_M5_ImmOff,
  slv6_P_STC_M5_Imm_preInd,
  slv6_P_STC_M5_Imm_postInd,
  slv6_P_STC_M5_U,
  slv6_P_STM1_M4_DA,
  slv6_P_STM2_M4_IA,
  slv6_P_STM2_M4_IB,
  slv6_P_STM2_M4_DA,
  slv6_P_STM2_M4_DB,
  slv6_P_STR_M2_Reg_preInd,
  slv6_P_STR_M2_ScReg_preInd,
  slv6_P_STR_M2_ScReg_postInd,
  slv6_P_STRB_M2_ScRegOff,
  slv6_P_STRB_M2_Imm_preInd,
  slv6_P_STRB_M2_Reg_preInd,
  slv6_P_STRB_M2_ScReg_preInd,
  slv6_P_STRB_M2_Reg_postInd,
  slv6_P_STRB_M2_ScReg_postInd,
  slv6_P_STRBT_M2_Imm_postInd,
  slv6_P_STRBT_M2_Reg_postInd,
  slv6_P_STRBT_M2_ScReg_postInd,
  slv6_P_STRD_M3_ImmOff,
  slv6_P_STRD_M3_RegOff,
  slv6_P_STRD_M3_Imm_preInd,
  slv6_P_STRD_M3_Reg_preInd,
  slv6_P_STRD_M3_Imm_postInd,
  slv6_P_STRD_M3_Reg_postInd,
  slv6_P_STREX,
  slv6_P_STRH_M3_ImmOff,
  slv6_P_STRH_M3_RegOff,
  slv6_P_STRH_M3_Imm_preInd,
  slv6_P_STRH_M3_Reg_preInd,
  slv6_P_STRH_M3_Imm_postInd,
  slv6_P_STRH_M3_Reg_postInd,
  slv6_P_STRT_M2_Imm_postInd,
  slv6_P_STRT_M2_Reg_postInd,
  slv6_P_STRT_M2_ScReg_postInd,
  slv6_P_SUB_M1_Reg,
  slv6_P_SUB_M1_LSLReg,
  slv6_P_SUB_M1_LSRImm,
  slv6_P_SUB_M1_LSRReg,
  slv6_P_SUB_M1_ASRReg,
  slv6_P_SUB_M1_RRImm,
  slv6_P_SUB_M1_RRReg,
  slv6_P_SUB_M1_RRE,
  slv6_P_SWI,
  slv6_P_SWP,
  slv6_P_SWPB,
  slv6_P_SXTAB,
  slv6_P_SXTAB16,
  slv6_P_SXTAH,
  slv6_P_SXTB,
  slv6_P_SXTB16,
  slv6_P_SXTH,
  slv6_P_TEQ_M1_Imm,
  slv6_P_TEQ_M1_Reg,
  slv6_P_TEQ_M1_LSLImm,
  slv6_P_TEQ_M1_LSLReg,
  slv6_P_TEQ_M1_LSRImm,
  slv6_P_TEQ_M1_LSRReg,
  slv6_P_TEQ_M1_ASRImm,
  slv6_P_TEQ_M1_ASRReg,
  slv6_P_TEQ_M1_RRImm,
  slv6_P_TEQ_M1_RRReg,
  slv6_P_TEQ_M1_RRE,
  slv6_P_TST_M1_LSLImm,
  slv6_P_TST_M1_LSLReg,
  slv6_P_TST_M1_LSRImm,
  slv6_P_TST_M1_LSRReg,
  slv6_P_TST_M1_ASRImm,
  slv6_P_TST_M1_ASRReg,
  slv6_P_TST_M1_RRImm,
  slv6_P_TST_M1_RRReg,
  slv6_P_TST_M1_RRE,
  slv6_P_UADD16,
  slv6_P_UADD8,
  slv6_P_UADDSUBX,
  slv6_P_UHADD16,
  slv6_P_UHADD8,
  slv6_P_UHADDSUBX,
  slv6_P_UHSUB16,
  slv6_P_UHSUB8,
  slv6_P_UHSUBADDX,
  slv6_P_UMAAL,
  slv6_P_UMLAL,
  slv6_P_UMULL,
  slv6_P_UQADD16,
  slv6_P_UQADD8,
  slv6_P_UQADDSUBX,
  slv6_P_UQSUB16,
  slv6_P_UQSUB8,
  slv6_P_UQSUBADDX,
  slv6_P_USAD8,
  slv6_P_USADA8,
  slv6_P_USAT,
  slv6_P_USAT16,
  slv6_P_USUB16,
  slv6_P_USUB8,
  slv6_P_USUBADDX,
  slv6_P_UXTAB,
  slv6_P_UXTAB16,
  slv6_P_UXTAH,
  slv6_P_UXTB,
  slv6_P_UXTB16,
  slv6_P_UXTH,
  slv6_P_Tb_LDR1,
  slv6_P_Tb_CPY,
  slv6_P_Tb_STR1,
  slv6_P_Tb_B1,
  slv6_P_Tb_LSL1,
  slv6_P_Tb_ADD3,
  slv6_P_Tb_MOV1,
  slv6_P_Tb_CMP2,
  slv6_P_Tb_LDR3,
  slv6_P_Tb_EOR,
  slv6_P_Tb_SUB2,
  slv6_P_Tb_MOV2,
  slv6_P_Tb_ADD2,
  slv6_P_Tb_LDR4,
  slv6_P_Tb_AND,
  slv6_P_Tb_LSR1,
  slv6_P_Tb_LDR2,
  slv6_P_Tb_ADD4,
  slv6_P_Tb_CMP1,
  slv6_P_Tb_ORR,
  slv6_P_Tb_STR3,
  slv6_P_Tb_ROR,
  slv6_P_Tb_BL,
  slv6_P_Tb_B2,
  slv6_P_Tb_NEG,
  slv6_P_Tb_LDRB1,
  slv6_P_Tb_PUSH,
  slv6_P_Tb_POP,
  slv6_P_Tb_CMP3,
  slv6_P_Tb_SUB4,
  slv6_P_Tb_ADD7,
  slv6_P_Tb_ADD6,
  slv6_P_Tb_BX,
  slv6_P_Tb_STRB1,
  slv6_P_Tb_LDRB2,
  slv6_P_Tb_ADC,
  slv6_P_Tb_SUB3,
  slv6_P_Tb_SUB1,
  slv6_P_Tb_LSR2,
  slv6_P_Tb_STR2,
  slv6_P_Tb_STRB2,
  slv6_P_Tb_LDMIA,
  slv6_P_Tb_STMIA,
  slv6_P_Tb_ADD1,
  slv6_P_Tb_MUL,
  slv6_P_Tb_ASR1,
  slv6_P_Tb_MVN,
  slv6_P_Tb_LDRH1,
  slv6_P_Tb_TST,
  slv6_P_Tb_BIC,
  slv6_P_Tb_LSL2,
  slv6_P_Tb_ADD5,
  slv6_P_Tb_ASR2,
  slv6_P_Tb_BKPT,
  slv6_P_Tb_BLX2,
  slv6_P_Tb_CMN,
  slv6_P_Tb_CPS,
  slv6_P_Tb_LDRH2,
  slv6_P_Tb_LDRSB,
  slv6_P_Tb_LDRSH,
  slv6_P_Tb_REV,
  slv6_P_Tb_REV16,
  slv6_P_Tb_REVSH,
  slv6_P_Tb_SBC,
  slv6_P_Tb_SETEND,
  slv6_P_Tb_STRH1,
  slv6_P_Tb_STRH2,
  slv6_P_Tb_SWI,
  slv6_P_Tb_SXTB,
  slv6_P_Tb_SXTH,
  slv6_P_Tb_UXTB,
  slv6_P_Tb_UXTH,
  slv6_P_LDR_M2_ImmOff_NC,
  slv6_P_STR_M2_ImmOff_NC,
  slv6_P_B_L1_NC,
  slv6_P_B_L0_NC,
  slv6_P_SUB_M1_Imm_S1_NC,
  slv6_P_SUB_M1_Imm_S0_NC,
  slv6_P_CMP_M1_Reg_NC,
  slv6_P_ADD_M1_Imm_S1_NC,
  slv6_P_ADD_M1_Imm_S0_NC,
  slv6_P_ADD_M1_Reg_S1_NC,
  slv6_P_ADD_M1_Reg_S0_NC,
  slv6_P_EOR_M1_Reg_S1_NC,
  slv6_P_EOR_M1_Reg_S0_NC,
  slv6_P_AND_M1_Imm_S1_NC,
  slv6_P_AND_M1_Imm_S0_NC,
  slv6_P_MOV_M1_LSRImm_S1_NC,
  slv6_P_MOV_M1_LSRImm_S0_NC,
  slv6_P_CPY_NC,
  slv6_P_MOV_M1_LSLImm_S1_NC,
  slv6_P_MOV_M1_LSLImm_S0_NC,
  slv6_P_MOV_M1_Imm_S1_NC,
  slv6_P_MOV_M1_Imm_S0_NC,
  slv6_P_LDM1_M4_IA_W1_NC,
  slv6_P_LDM1_M4_IA_W0_NC,
  slv6_P_CMP_M1_Imm_NC,
  slv6_P_LDR_M2_ScRegOff_U1_NC,
  slv6_P_LDR_M2_ScRegOff_U0_NC,
  slv6_P_BX_NC,
  slv6_P_ADD_M1_LSLImm_S1_NC,
  slv6_P_ADD_M1_LSLImm_S0_NC,
  slv6_P_LDRB_M2_ImmOff_NC,
  slv6_P_ORR_M1_Reg_S1_NC,
  slv6_P_ORR_M1_Reg_S0_NC,
  slv6_P_MOV_M1_RRImm_S1_NC,
  slv6_P_MOV_M1_RRImm_S0_NC,
  slv6_P_LDR_M2_Imm_postInd_NC,
  slv6_P_EOR_M1_RRImm_S1_NC,
  slv6_P_EOR_M1_RRImm_S0_NC,
  slv6_P_AND_M1_Reg_S1_NC,
  slv6_P_AND_M1_Reg_S0_NC,
  slv6_P_STR_M2_Imm_preInd_NC,
  slv6_P_STRB_M2_ImmOff_NC,
  slv6_P_ORR_M1_LSLImm_S1_NC,
  slv6_P_ORR_M1_LSLImm_S0_NC,
  slv6_P_ADC_M1_Reg_S1_NC,
  slv6_P_ADC_M1_Reg_S0_NC,
  slv6_P_LDRB_M2_RegOff_U1_NC,
  slv6_P_LDRB_M2_RegOff_U0_NC,
  slv6_P_RSB_M1_Reg_S1_NC,
  slv6_P_RSB_M1_Reg_S0_NC,
  slv6_P_BIC_M1_Imm_S1_NC,
  slv6_P_BIC_M1_Imm_S0_NC,
  slv6_P_MVN_M1_Imm_S1_NC,
  slv6_P_MVN_M1_Imm_S0_NC,
  slv6_P_ORR_M1_LSRImm_S1_NC,
  slv6_P_ORR_M1_LSRImm_S0_NC,
  slv6_P_EOR_M1_LSRImm_S1_NC,
  slv6_P_EOR_M1_LSRImm_S0_NC,
  slv6_P_LDR_M2_RegOff_U1_NC,
  slv6_P_LDR_M2_RegOff_U0_NC,
  slv6_P_MOV_M1_LSRReg_S1_NC,
  slv6_P_MOV_M1_LSRReg_S0_NC,
  slv6_P_STRB_M2_RegOff_U1_NC,
  slv6_P_STRB_M2_RegOff_U0_NC,
  slv6_P_STR_M2_ScRegOff_U1_NC,
  slv6_P_STR_M2_ScRegOff_U0_NC,
  slv6_P_CMN_M1_Reg_NC,
  slv6_P_STR_M2_Reg_postInd_U1_NC,
  slv6_P_STR_M2_Reg_postInd_U0_NC,
  slv6_P_STR_M2_RegOff_U1_NC,
  slv6_P_STR_M2_RegOff_U0_NC,
  slv6_P_EOR_M1_LSLImm_S1_NC,
  slv6_P_EOR_M1_LSLImm_S0_NC,
  slv6_P_RSB_M1_Imm_S1_NC,
  slv6_P_RSB_M1_Imm_S0_NC,
  slv6_P_MOV_M1_ASRImm_S1_NC,
  slv6_P_MOV_M1_ASRImm_S0_NC,
  slv6_P_ADD_M1_RRImm_S1_NC,
  slv6_P_ADD_M1_RRImm_S0_NC,
  slv6_P_RSB_M1_LSLImm_S1_NC,
  slv6_P_RSB_M1_LSLImm_S0_NC,
  slv6_P_STRB_M2_Imm_postInd_NC,
  slv6_P_STM1_M4_IA_W1_NC,
  slv6_P_STM1_M4_IA_W0_NC,
  slv6_P_TST_M1_Imm_NC,
  slv6_P_STM1_M4_DB_W1_NC,
  slv6_P_STM1_M4_DB_W0_NC,
  slv6_P_MVN_M1_Reg_S1_NC,
  slv6_P_MVN_M1_Reg_S0_NC,
  slv6_P_STM1_M4_IB_W1_NC,
  slv6_P_STM1_M4_IB_W0_NC,
  slv6_P_ADD_M1_LSRImm_S1_NC,
  slv6_P_ADD_M1_LSRImm_S0_NC,
  slv6_P_STR_M2_Imm_postInd_NC,
  slv6_P_LDRB_M2_ScRegOff_U1_NC,
  slv6_P_LDRB_M2_ScRegOff_U0_NC,
  slv6_P_SUB_M1_LSLImm_S1_NC,
  slv6_P_SUB_M1_LSLImm_S0_NC,
  slv6_P_LDM1_M4_IB_W1_NC,
  slv6_P_LDM1_M4_IB_W0_NC,
  slv6_P_LDRH_M3_ImmOff_U1_NC,
  slv6_P_LDRH_M3_ImmOff_U0_NC,
  slv6_P_LDR_M2_Imm_preInd_NC,
  slv6_P_SMULL_S1_NC,
  slv6_P_SMULL_S0_NC,
  slv6_P_RSB_M1_ASRImm_S1_NC,
  slv6_P_RSB_M1_ASRImm_S0_NC,
  slv6_P_TST_M1_Reg_NC,
  slv6_P_EOR_M1_Imm_S1_NC,
  slv6_P_EOR_M1_Imm_S0_NC,
  slv6_P_ORR_M1_ASRImm_S1_NC,
  slv6_P_ORR_M1_ASRImm_S0_NC,
  slv6_P_ORR_M1_Imm_S1_NC,
  slv6_P_ORR_M1_Imm_S0_NC,
  slv6_P_SUB_M1_ASRImm_S1_NC,
  slv6_P_SUB_M1_ASRImm_S0_NC,
  slv6_P_MOV_M1_LSLReg_S1_NC,
  slv6_P_MOV_M1_LSLReg_S0_NC,
  slv6_P_MUL_S1_NC,
  slv6_P_MUL_S0_NC,
  slv6_P_CMN_M1_Imm_NC,
  slv6_P_Tb_LDR1_NI,
  slv6_P_Tb_LSL1_NI};

void slv6_print_instr(std::ostream &os, struct SLv6_Instruction *instr, uint32_t bincode) {
  assert(instr->args.g0.id<SLV6_TABLE_SIZE);
  slv6_printers[instr->args.g0.id](os,instr,bincode);
}

} // namespace simsoc
