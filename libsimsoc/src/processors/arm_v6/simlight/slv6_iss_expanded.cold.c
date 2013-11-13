#include "slv6_iss_c_prelude.h"

/* A4.1.2--A5.1.3
 * ADC -- Data processing operands - Immediate */
void slv6_X_ADC_M1_Imm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,((old_Rn + shifter_operand) + proc->cpsr.C_flag),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADC_M1_Imm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = CarryFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
      proc->cpsr.V_flag = OverflowFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
    }
  }
}

/* A4.1.2--A5.1.5
 * ADC -- Data processing operands - Logical shift left by immediate */
void slv6_X_ADC_M1_LSLImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? old_Rm: (old_Rm << shift_imm));
  shifter_carry_out = ((shift_imm == 0)? proc->cpsr.C_flag: get_bit(old_Rm,(32 - shift_imm)));
  set_reg_or_pc_ws(proc,d,((old_Rn + shifter_operand) + proc->cpsr.C_flag),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADC_M1_LSLImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = CarryFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
      proc->cpsr.V_flag = OverflowFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
    }
  }
}

/* A4.1.2--A5.1.6
 * ADC -- Data processing operands - Logical shift left by register */
void slv6_X_ADC_M1_LSLReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm << get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(32 - get_byte_0(old_Rs))): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,0): 0)));
  set_reg(proc,d,((old_Rn + shifter_operand) + proc->cpsr.C_flag));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADC_M1_LSLReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = CarryFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
      proc->cpsr.V_flag = OverflowFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
    }
  }
}

/* A4.1.2--A5.1.7
 * ADC -- Data processing operands - Logical shift right by immediate */
void slv6_X_ADC_M1_LSRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,((old_Rn + shifter_operand) + proc->cpsr.C_flag),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADC_M1_LSRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = CarryFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
      proc->cpsr.V_flag = OverflowFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
    }
  }
}

/* A4.1.2--A5.1.8
 * ADC -- Data processing operands - Logical shift right by register */
void slv6_X_ADC_M1_LSRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm >> get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,31): 0)));
  set_reg(proc,d,((old_Rn + shifter_operand) + proc->cpsr.C_flag));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADC_M1_LSRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = CarryFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
      proc->cpsr.V_flag = OverflowFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
    }
  }
}

/* A4.1.2--A5.1.9
 * ADC -- Data processing operands - Arithmetic shift right by immediate */
void slv6_X_ADC_M1_ASRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF): asr(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,((old_Rn + shifter_operand) + proc->cpsr.C_flag),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADC_M1_ASRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = CarryFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
      proc->cpsr.V_flag = OverflowFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
    }
  }
}

/* A4.1.2--A5.1.10
 * ADC -- Data processing operands - Arithmetic shift right by register */
void slv6_X_ADC_M1_ASRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? asr(old_Rm, get_byte_0(old_Rs)): ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF)));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): get_bit(old_Rm,31)));
  set_reg(proc,d,((old_Rn + shifter_operand) + proc->cpsr.C_flag));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADC_M1_ASRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = CarryFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
      proc->cpsr.V_flag = OverflowFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
    }
  }
}

/* A4.1.2--A5.1.11
 * ADC -- Data processing operands - Rotate right by immediate */
void slv6_X_ADC_M1_RRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,0): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,((old_Rn + shifter_operand) + proc->cpsr.C_flag),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADC_M1_RRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = CarryFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
      proc->cpsr.V_flag = OverflowFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
    }
  }
}

/* A4.1.2--A5.1.12
 * ADC -- Data processing operands - Rotate right by register */
void slv6_X_ADC_M1_RRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_bits(old_Rs,4,0) == 0)? old_Rm: rotate_right(old_Rm, get_bits(old_Rs,4,0))));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_bits(old_Rs,4,0) == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(get_bits(old_Rs,4,0) - 1))));
  set_reg(proc,d,((old_Rn + shifter_operand) + proc->cpsr.C_flag));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADC_M1_RRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = CarryFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
      proc->cpsr.V_flag = OverflowFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
    }
  }
}

/* A4.1.2--A5.1.13
 * ADC -- Data processing operands - Rotate right with extend */
void slv6_X_ADC_M1_RRE(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((proc->cpsr.C_flag << 31) | (old_Rm >> 1));
  shifter_carry_out = get_bit(old_Rm,0);
  set_reg_or_pc_ws(proc,d,((old_Rn + shifter_operand) + proc->cpsr.C_flag),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADC_M1_RRE");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = CarryFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
      proc->cpsr.V_flag = OverflowFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
    }
  }
}

/* A4.1.3--A5.1.6
 * ADD -- Data processing operands - Logical shift left by register */
void slv6_X_ADD_M1_LSLReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm << get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(32 - get_byte_0(old_Rs))): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,0): 0)));
  set_reg(proc,d,(old_Rn + shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADD_M1_LSLReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
      proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
    }
  }
}

/* A4.1.3--A5.1.8
 * ADD -- Data processing operands - Logical shift right by register */
void slv6_X_ADD_M1_LSRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm >> get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,31): 0)));
  set_reg(proc,d,(old_Rn + shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADD_M1_LSRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
      proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
    }
  }
}

/* A4.1.3--A5.1.9
 * ADD -- Data processing operands - Arithmetic shift right by immediate */
void slv6_X_ADD_M1_ASRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF): asr(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn + shifter_operand),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADD_M1_ASRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
      proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
    }
  }
}

/* A4.1.3--A5.1.10
 * ADD -- Data processing operands - Arithmetic shift right by register */
void slv6_X_ADD_M1_ASRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? asr(old_Rm, get_byte_0(old_Rs)): ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF)));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): get_bit(old_Rm,31)));
  set_reg(proc,d,(old_Rn + shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADD_M1_ASRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
      proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
    }
  }
}

/* A4.1.3--A5.1.12
 * ADD -- Data processing operands - Rotate right by register */
void slv6_X_ADD_M1_RRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_bits(old_Rs,4,0) == 0)? old_Rm: rotate_right(old_Rm, get_bits(old_Rs,4,0))));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_bits(old_Rs,4,0) == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(get_bits(old_Rs,4,0) - 1))));
  set_reg(proc,d,(old_Rn + shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADD_M1_RRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
      proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
    }
  }
}

/* A4.1.3--A5.1.13
 * ADD -- Data processing operands - Rotate right with extend */
void slv6_X_ADD_M1_RRE(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((proc->cpsr.C_flag << 31) | (old_Rm >> 1));
  shifter_carry_out = get_bit(old_Rm,0);
  set_reg_or_pc_ws(proc,d,(old_Rn + shifter_operand),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADD_M1_RRE");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
      proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
    }
  }
}

/* A4.1.4--A5.1.5
 * AND -- Data processing operands - Logical shift left by immediate */
void slv6_X_AND_M1_LSLImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? old_Rm: (old_Rm << shift_imm));
  shifter_carry_out = ((shift_imm == 0)? proc->cpsr.C_flag: get_bit(old_Rm,(32 - shift_imm)));
  set_reg_or_pc_ws(proc,d,(old_Rn & shifter_operand),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("AND_M1_LSLImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.4--A5.1.6
 * AND -- Data processing operands - Logical shift left by register */
void slv6_X_AND_M1_LSLReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm << get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(32 - get_byte_0(old_Rs))): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,0): 0)));
  set_reg(proc,d,(old_Rn & shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("AND_M1_LSLReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.4--A5.1.7
 * AND -- Data processing operands - Logical shift right by immediate */
void slv6_X_AND_M1_LSRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn & shifter_operand),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("AND_M1_LSRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.4--A5.1.8
 * AND -- Data processing operands - Logical shift right by register */
void slv6_X_AND_M1_LSRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm >> get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,31): 0)));
  set_reg(proc,d,(old_Rn & shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("AND_M1_LSRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.4--A5.1.9
 * AND -- Data processing operands - Arithmetic shift right by immediate */
void slv6_X_AND_M1_ASRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF): asr(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn & shifter_operand),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("AND_M1_ASRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.4--A5.1.10
 * AND -- Data processing operands - Arithmetic shift right by register */
void slv6_X_AND_M1_ASRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? asr(old_Rm, get_byte_0(old_Rs)): ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF)));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): get_bit(old_Rm,31)));
  set_reg(proc,d,(old_Rn & shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("AND_M1_ASRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.4--A5.1.11
 * AND -- Data processing operands - Rotate right by immediate */
void slv6_X_AND_M1_RRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,0): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn & shifter_operand),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("AND_M1_RRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.4--A5.1.12
 * AND -- Data processing operands - Rotate right by register */
void slv6_X_AND_M1_RRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_bits(old_Rs,4,0) == 0)? old_Rm: rotate_right(old_Rm, get_bits(old_Rs,4,0))));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_bits(old_Rs,4,0) == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(get_bits(old_Rs,4,0) - 1))));
  set_reg(proc,d,(old_Rn & shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("AND_M1_RRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.4--A5.1.13
 * AND -- Data processing operands - Rotate right with extend */
void slv6_X_AND_M1_RRE(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((proc->cpsr.C_flag << 31) | (old_Rm >> 1));
  shifter_carry_out = get_bit(old_Rm,0);
  set_reg_or_pc_ws(proc,d,(old_Rn & shifter_operand),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("AND_M1_RRE");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.6--A5.1.4
 * BIC -- Data processing operands - Register */
void slv6_X_BIC_M1_Reg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = old_Rm;
  shifter_carry_out = proc->cpsr.C_flag;
  set_reg_or_pc_ws(proc,d,(old_Rn & ~(shifter_operand)),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("BIC_M1_Reg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.6--A5.1.5
 * BIC -- Data processing operands - Logical shift left by immediate */
void slv6_X_BIC_M1_LSLImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? old_Rm: (old_Rm << shift_imm));
  shifter_carry_out = ((shift_imm == 0)? proc->cpsr.C_flag: get_bit(old_Rm,(32 - shift_imm)));
  set_reg_or_pc_ws(proc,d,(old_Rn & ~(shifter_operand)),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("BIC_M1_LSLImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.6--A5.1.6
 * BIC -- Data processing operands - Logical shift left by register */
void slv6_X_BIC_M1_LSLReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm << get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(32 - get_byte_0(old_Rs))): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,0): 0)));
  set_reg(proc,d,(old_Rn & ~(shifter_operand)));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("BIC_M1_LSLReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.6--A5.1.7
 * BIC -- Data processing operands - Logical shift right by immediate */
void slv6_X_BIC_M1_LSRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn & ~(shifter_operand)),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("BIC_M1_LSRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.6--A5.1.8
 * BIC -- Data processing operands - Logical shift right by register */
void slv6_X_BIC_M1_LSRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm >> get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,31): 0)));
  set_reg(proc,d,(old_Rn & ~(shifter_operand)));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("BIC_M1_LSRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.6--A5.1.9
 * BIC -- Data processing operands - Arithmetic shift right by immediate */
void slv6_X_BIC_M1_ASRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF): asr(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn & ~(shifter_operand)),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("BIC_M1_ASRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.6--A5.1.10
 * BIC -- Data processing operands - Arithmetic shift right by register */
void slv6_X_BIC_M1_ASRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? asr(old_Rm, get_byte_0(old_Rs)): ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF)));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): get_bit(old_Rm,31)));
  set_reg(proc,d,(old_Rn & ~(shifter_operand)));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("BIC_M1_ASRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.6--A5.1.11
 * BIC -- Data processing operands - Rotate right by immediate */
void slv6_X_BIC_M1_RRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,0): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn & ~(shifter_operand)),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("BIC_M1_RRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.6--A5.1.12
 * BIC -- Data processing operands - Rotate right by register */
void slv6_X_BIC_M1_RRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_bits(old_Rs,4,0) == 0)? old_Rm: rotate_right(old_Rm, get_bits(old_Rs,4,0))));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_bits(old_Rs,4,0) == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(get_bits(old_Rs,4,0) - 1))));
  set_reg(proc,d,(old_Rn & ~(shifter_operand)));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("BIC_M1_RRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.6--A5.1.13
 * BIC -- Data processing operands - Rotate right with extend */
void slv6_X_BIC_M1_RRE(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((proc->cpsr.C_flag << 31) | (old_Rm >> 1));
  shifter_carry_out = get_bit(old_Rm,0);
  set_reg_or_pc_ws(proc,d,(old_Rn & ~(shifter_operand)),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("BIC_M1_RRE");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.7
 * BKPT */
void slv6_X_BKPT(struct SLv6_Processor *proc)
{
  if (not_overridden_by_debug_hardware()) {
    set_reg_m(proc,14,abt,(address_of_current_instruction(proc) + 4));
    *spsr_m(proc,abt) = proc->cpsr;
    set_cpsr_mode(proc, abt);
    proc->cpsr.T_flag = 0;
    set_cpsr_I_flag(proc,1);
    set_cpsr_A_flag(proc,1);
    proc->cpsr.E_flag = CP15_reg1_EEbit(proc->cp15_ptr);
    if (high_vectors_configured(proc))
      set_pc_raw_ws(proc,0xFFFF000C,inst_size(proc));
    else
      set_pc_raw_ws(proc,0x0000000C,inst_size(proc));
  }
}

/* A4.1.8
 * BLX (1) */
void slv6_X_BLX1(struct SLv6_Processor *proc,
    const uint32_t pc_offset_h)
{
  uint32_t addr_of_next_instr;
  addr_of_next_instr = (reg(proc,15) - 4);
  set_reg(proc,14,addr_of_next_instr);
  proc->cpsr.T_flag = 1;
  set_pc_raw_ws(proc,(reg(proc,15) + pc_offset_h),inst_size(proc));
}

/* A4.1.9
 * BLX (2) */
void slv6_X_BLX2(struct SLv6_Processor *proc,
    const uint8_t m,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  uint32_t addr_of_next_instr;
  uint32_t target;
  addr_of_next_instr = (reg(proc,15) - 4);
  target = old_Rm;
  set_reg(proc,14,addr_of_next_instr);
  proc->cpsr.T_flag = get_bit(target,0);
  set_pc_raw_ws(proc,(target & 0xFFFFFFFE),inst_size(proc));
}

/* A4.1.11
 * BXJ */
void slv6_X_BXJ(struct SLv6_Processor *proc,
    const uint8_t m,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  uint32_t invalidhandler;
  uint32_t jpc;
  if ((JE_bit_of_Main_Configuration_register() == 0)) {
    proc->cpsr.T_flag = get_bit(old_Rm,0);
    set_pc_raw_ws(proc,(old_Rm & 0xFFFFFFFE),inst_size(proc));
  } else {
    jpc = jpc_SUB_ARCHITECTURE_DEFINED_value();
    invalidhandler = invalidhandler_SUB_ARCHITECTURE_DEFINED_value();
    if (Jazelle_Extension_accepts_opcode_at(jpc)) {
      if ((CV_bit_of_Jazelle_OS_Control_register() == 0))
        set_pc_raw_ws(proc,invalidhandler,inst_size(proc));
      else {
        proc->cpsr.J_flag = 1;
        Start_opcode_execution_at(jpc);
      }
    } else {
      if (((CV_bit_of_Jazelle_OS_Control_register() == 0) && IMPLEMENTATION_DEFINED_CONDITION()))
        set_pc_raw_ws(proc,invalidhandler,inst_size(proc));
      else {
        proc->cpsr.T_flag = get_bit(old_Rm,0);
        set_pc_raw_ws(proc,(old_Rm & 0xFFFFFFFE),inst_size(proc));
      }
    }
  }
}

/* A4.1.12
 * CDP */
void slv6_X_CDP(struct SLv6_Processor *proc,
    const uint8_t cp_num,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  if (!slv6_CDP_dependent_operation(proc,cp_num)) return;
}

/* A4.1.13
 * CLZ */
void slv6_X_CLZ(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  if ((old_Rm == 0))
    set_reg(proc,d,32);
  else
    set_reg(proc,d,(31 - bit_position_of_most_significant_1(old_Rm)));
}

/* A4.1.14--A5.1.5
 * CMN -- Data processing operands - Logical shift left by immediate */
void slv6_X_CMN_M1_LSLImm(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? old_Rm: (old_Rm << shift_imm));
  shifter_carry_out = ((shift_imm == 0)? proc->cpsr.C_flag: get_bit(old_Rm,(32 - shift_imm)));
  alu_out = (old_Rn + shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
  proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
}

/* A4.1.14--A5.1.6
 * CMN -- Data processing operands - Logical shift left by register */
void slv6_X_CMN_M1_LSLReg(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm << get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(32 - get_byte_0(old_Rs))): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,0): 0)));
  alu_out = (old_Rn + shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
  proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
}

/* A4.1.14--A5.1.7
 * CMN -- Data processing operands - Logical shift right by immediate */
void slv6_X_CMN_M1_LSRImm(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  alu_out = (old_Rn + shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
  proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
}

/* A4.1.14--A5.1.8
 * CMN -- Data processing operands - Logical shift right by register */
void slv6_X_CMN_M1_LSRReg(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm >> get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,31): 0)));
  alu_out = (old_Rn + shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
  proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
}

/* A4.1.14--A5.1.9
 * CMN -- Data processing operands - Arithmetic shift right by immediate */
void slv6_X_CMN_M1_ASRImm(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF): asr(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  alu_out = (old_Rn + shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
  proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
}

/* A4.1.14--A5.1.10
 * CMN -- Data processing operands - Arithmetic shift right by register */
void slv6_X_CMN_M1_ASRReg(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? asr(old_Rm, get_byte_0(old_Rs)): ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF)));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): get_bit(old_Rm,31)));
  alu_out = (old_Rn + shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
  proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
}

/* A4.1.14--A5.1.11
 * CMN -- Data processing operands - Rotate right by immediate */
void slv6_X_CMN_M1_RRImm(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,0): get_bit(old_Rm,(shift_imm - 1)));
  alu_out = (old_Rn + shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
  proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
}

/* A4.1.14--A5.1.12
 * CMN -- Data processing operands - Rotate right by register */
void slv6_X_CMN_M1_RRReg(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_bits(old_Rs,4,0) == 0)? old_Rm: rotate_right(old_Rm, get_bits(old_Rs,4,0))));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_bits(old_Rs,4,0) == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(get_bits(old_Rs,4,0) - 1))));
  alu_out = (old_Rn + shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
  proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
}

/* A4.1.14--A5.1.13
 * CMN -- Data processing operands - Rotate right with extend */
void slv6_X_CMN_M1_RRE(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((proc->cpsr.C_flag << 31) | (old_Rm >> 1));
  shifter_carry_out = get_bit(old_Rm,0);
  alu_out = (old_Rn + shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
  proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
}

/* A4.1.15--A5.1.5
 * CMP -- Data processing operands - Logical shift left by immediate */
void slv6_X_CMP_M1_LSLImm(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? old_Rm: (old_Rm << shift_imm));
  shifter_carry_out = ((shift_imm == 0)? proc->cpsr.C_flag: get_bit(old_Rm,(32 - shift_imm)));
  alu_out = (old_Rn - shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
  proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
}

/* A4.1.15--A5.1.6
 * CMP -- Data processing operands - Logical shift left by register */
void slv6_X_CMP_M1_LSLReg(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm << get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(32 - get_byte_0(old_Rs))): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,0): 0)));
  alu_out = (old_Rn - shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
  proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
}

/* A4.1.15--A5.1.7
 * CMP -- Data processing operands - Logical shift right by immediate */
void slv6_X_CMP_M1_LSRImm(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  alu_out = (old_Rn - shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
  proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
}

/* A4.1.15--A5.1.8
 * CMP -- Data processing operands - Logical shift right by register */
void slv6_X_CMP_M1_LSRReg(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm >> get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,31): 0)));
  alu_out = (old_Rn - shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
  proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
}

/* A4.1.15--A5.1.9
 * CMP -- Data processing operands - Arithmetic shift right by immediate */
void slv6_X_CMP_M1_ASRImm(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF): asr(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  alu_out = (old_Rn - shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
  proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
}

/* A4.1.15--A5.1.10
 * CMP -- Data processing operands - Arithmetic shift right by register */
void slv6_X_CMP_M1_ASRReg(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? asr(old_Rm, get_byte_0(old_Rs)): ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF)));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): get_bit(old_Rm,31)));
  alu_out = (old_Rn - shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
  proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
}

/* A4.1.15--A5.1.11
 * CMP -- Data processing operands - Rotate right by immediate */
void slv6_X_CMP_M1_RRImm(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,0): get_bit(old_Rm,(shift_imm - 1)));
  alu_out = (old_Rn - shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
  proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
}

/* A4.1.15--A5.1.12
 * CMP -- Data processing operands - Rotate right by register */
void slv6_X_CMP_M1_RRReg(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_bits(old_Rs,4,0) == 0)? old_Rm: rotate_right(old_Rm, get_bits(old_Rs,4,0))));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_bits(old_Rs,4,0) == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(get_bits(old_Rs,4,0) - 1))));
  alu_out = (old_Rn - shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
  proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
}

/* A4.1.15--A5.1.13
 * CMP -- Data processing operands - Rotate right with extend */
void slv6_X_CMP_M1_RRE(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((proc->cpsr.C_flag << 31) | (old_Rm >> 1));
  shifter_carry_out = get_bit(old_Rm,0);
  alu_out = (old_Rn - shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
  proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
}

/* A4.1.16
 * CPS */
void slv6_X_CPS(struct SLv6_Processor *proc,
    const bool A,
    const bool F,
    const bool I,
    const uint8_t imod,
    const bool mmod,
    const SLv6_Mode mode)
{
  if (InAPrivilegedMode(proc)) {
    if ((get_bit(imod,1) == 1)) {
      if ((A == 1))
        set_cpsr_A_flag(proc,get_bit(imod,0));
      if ((I == 1))
        set_cpsr_I_flag(proc,get_bit(imod,0));
      if ((F == 1))
        set_cpsr_F_flag(proc,get_bit(imod,0));
    }
    if ((mmod == 1))
      set_cpsr_mode(proc, mode);
  }
}

/* A4.1.18--A5.1.6
 * EOR -- Data processing operands - Logical shift left by register */
void slv6_X_EOR_M1_LSLReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm << get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(32 - get_byte_0(old_Rs))): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,0): 0)));
  set_reg(proc,d,(old_Rn ^ shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("EOR_M1_LSLReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.18--A5.1.8
 * EOR -- Data processing operands - Logical shift right by register */
void slv6_X_EOR_M1_LSRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm >> get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,31): 0)));
  set_reg(proc,d,(old_Rn ^ shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("EOR_M1_LSRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.18--A5.1.9
 * EOR -- Data processing operands - Arithmetic shift right by immediate */
void slv6_X_EOR_M1_ASRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF): asr(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn ^ shifter_operand),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("EOR_M1_ASRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.18--A5.1.10
 * EOR -- Data processing operands - Arithmetic shift right by register */
void slv6_X_EOR_M1_ASRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? asr(old_Rm, get_byte_0(old_Rs)): ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF)));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): get_bit(old_Rm,31)));
  set_reg(proc,d,(old_Rn ^ shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("EOR_M1_ASRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.18--A5.1.12
 * EOR -- Data processing operands - Rotate right by register */
void slv6_X_EOR_M1_RRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_bits(old_Rs,4,0) == 0)? old_Rm: rotate_right(old_Rm, get_bits(old_Rs,4,0))));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_bits(old_Rs,4,0) == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(get_bits(old_Rs,4,0) - 1))));
  set_reg(proc,d,(old_Rn ^ shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("EOR_M1_RRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.18--A5.1.13
 * EOR -- Data processing operands - Rotate right with extend */
void slv6_X_EOR_M1_RRE(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((proc->cpsr.C_flag << 31) | (old_Rm >> 1));
  shifter_carry_out = get_bit(old_Rm,0);
  set_reg_or_pc_ws(proc,d,(old_Rn ^ shifter_operand),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("EOR_M1_RRE");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.19--A5.5.2
 * LDC -- Load and Store Coprocessor - Immediate offset */
void slv6_X_LDC_M5_ImmOff(struct SLv6_Processor *proc)
{
  exec_undefined_instruction(proc, NULL);
}

/* A4.1.19--A5.5.3
 * LDC -- Load and Store Coprocessor - Immediate pre indexed */
void slv6_X_LDC_M5_Imm_preInd(struct SLv6_Processor *proc)
{
  exec_undefined_instruction(proc, NULL);
}

/* A4.1.19--A5.5.4
 * LDC -- Load and Store Coprocessor - Immediate post indexed */
void slv6_X_LDC_M5_Imm_postInd(struct SLv6_Processor *proc)
{
  exec_undefined_instruction(proc, NULL);
}

/* A4.1.19--A5.5.5
 * LDC -- Load and Store Coprocessor - Unindexed */
void slv6_X_LDC_M5_U(struct SLv6_Processor *proc)
{
  exec_undefined_instruction(proc, NULL);
}

/* A4.1.20--A5.4.4
 * LDM (1) -- Load and Store Multiple - Decrement after */
void slv6_X_LDM1_M4_DA(struct SLv6_Processor *proc,
    const bool W,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t end_address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t start_address;
  uint32_t value;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  start_address = ((old_Rn - nb_reg_x4) + 4);
  end_address = old_Rn;
  if ((W == 1))
    new_Rn = (old_Rn - nb_reg_x4);
  address = start_address;
  size_t i; for (i = 0; i<=14; ++i) {
    if ((get_bit(register_list,i) == 1)) {
      set_reg(proc,i,slv6_read_word(proc->mmu_ptr,address));
      address = (address + 4);
    }
}
  if ((get_bit(register_list,15) == 1)) {
    value = slv6_read_word(proc->mmu_ptr,address);
    set_pc_raw_ws(proc,(value & 0xFFFFFFFE),inst_size(proc));
    proc->cpsr.T_flag = get_bit(value,0);
    address = (address + 4);
  }
  if ((W == 1))
    set_reg(proc,n,new_Rn);
}

/* A4.1.20--A5.4.5
 * LDM (1) -- Load and Store Multiple - Decrement before */
void slv6_X_LDM1_M4_DB(struct SLv6_Processor *proc,
    const bool W,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t end_address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t start_address;
  uint32_t value;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  start_address = (old_Rn - nb_reg_x4);
  end_address = (old_Rn - 4);
  if ((W == 1))
    new_Rn = (old_Rn - nb_reg_x4);
  address = start_address;
  size_t i; for (i = 0; i<=14; ++i) {
    if ((get_bit(register_list,i) == 1)) {
      set_reg(proc,i,slv6_read_word(proc->mmu_ptr,address));
      address = (address + 4);
    }
}
  if ((get_bit(register_list,15) == 1)) {
    value = slv6_read_word(proc->mmu_ptr,address);
    set_pc_raw_ws(proc,(value & 0xFFFFFFFE),inst_size(proc));
    proc->cpsr.T_flag = get_bit(value,0);
    address = (address + 4);
  }
  if ((W == 1))
    set_reg(proc,n,new_Rn);
}

/* A4.1.21--A5.4.2
 * LDM (2) -- Load and Store Multiple - Increment after */
void slv6_X_LDM2_M4_IA(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t end_address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t start_address;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  start_address = old_Rn;
  end_address = ((old_Rn + (Number_Of_Set_Bits_In(register_list) * 4)) - 4);
  if ((0 == 1))
    new_Rn = (old_Rn + (Number_Of_Set_Bits_In(register_list) * 4));
  address = start_address;
  size_t i; for (i = 0; i<=14; ++i) {
    if ((get_bit(register_list,i) == 1)) {
      set_reg_m(proc,i,usr,slv6_read_word(proc->mmu_ptr,address));
      address = (address + 4);
    }
}
}

/* A4.1.21--A5.4.3
 * LDM (2) -- Load and Store Multiple - Increment before */
void slv6_X_LDM2_M4_IB(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t end_address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t start_address;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  start_address = (old_Rn + 4);
  end_address = (old_Rn + (Number_Of_Set_Bits_In(register_list) * 4));
  if ((0 == 1))
    new_Rn = (old_Rn + (Number_Of_Set_Bits_In(register_list) * 4));
  address = start_address;
  size_t i; for (i = 0; i<=14; ++i) {
    if ((get_bit(register_list,i) == 1)) {
      set_reg_m(proc,i,usr,slv6_read_word(proc->mmu_ptr,address));
      address = (address + 4);
    }
}
}

/* A4.1.21--A5.4.4
 * LDM (2) -- Load and Store Multiple - Decrement after */
void slv6_X_LDM2_M4_DA(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t end_address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t start_address;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  start_address = ((old_Rn - (Number_Of_Set_Bits_In(register_list) * 4)) + 4);
  end_address = old_Rn;
  if ((0 == 1))
    new_Rn = (old_Rn - (Number_Of_Set_Bits_In(register_list) * 4));
  address = start_address;
  size_t i; for (i = 0; i<=14; ++i) {
    if ((get_bit(register_list,i) == 1)) {
      set_reg_m(proc,i,usr,slv6_read_word(proc->mmu_ptr,address));
      address = (address + 4);
    }
}
}

/* A4.1.21--A5.4.5
 * LDM (2) -- Load and Store Multiple - Decrement before */
void slv6_X_LDM2_M4_DB(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t end_address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t start_address;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  start_address = (old_Rn - (Number_Of_Set_Bits_In(register_list) * 4));
  end_address = (old_Rn - 4);
  if ((0 == 1))
    new_Rn = (old_Rn - (Number_Of_Set_Bits_In(register_list) * 4));
  address = start_address;
  size_t i; for (i = 0; i<=14; ++i) {
    if ((get_bit(register_list,i) == 1)) {
      set_reg_m(proc,i,usr,slv6_read_word(proc->mmu_ptr,address));
      address = (address + 4);
    }
}
}

/* A4.1.22--A5.4.2
 * LDM (3) -- Load and Store Multiple - Increment after */
void slv6_X_LDM3_M4_IA(struct SLv6_Processor *proc,
    const bool W,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t end_address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t start_address;
  uint32_t value;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  start_address = old_Rn;
  end_address = ((old_Rn + nb_reg_x4) - 4);
  if ((W == 1))
    new_Rn = (old_Rn + nb_reg_x4);
  address = start_address;
  size_t i; for (i = 0; i<=14; ++i) {
    if ((get_bit(register_list,i) == 1)) {
      set_reg(proc,i,slv6_read_word(proc->mmu_ptr,address));
      address = (address + 4);
    }
}
  if (CurrentModeHasSPSR(proc))
    set_cpsr_sr(proc, *spsr(proc));
  else
    unpredictable("LDM3_M4_IA");
  value = slv6_read_word(proc->mmu_ptr,address);
  set_pc_raw_ws(proc,value,4);
  address = (address + 4);
  if ((W == 1))
    set_reg_m(proc, n, old_mode, new_Rn);
}

/* A4.1.22--A5.4.3
 * LDM (3) -- Load and Store Multiple - Increment before */
void slv6_X_LDM3_M4_IB(struct SLv6_Processor *proc,
    const bool W,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t end_address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t start_address;
  uint32_t value;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  start_address = (old_Rn + 4);
  end_address = (old_Rn + nb_reg_x4);
  if ((W == 1))
    new_Rn = (old_Rn + nb_reg_x4);
  address = start_address;
  size_t i; for (i = 0; i<=14; ++i) {
    if ((get_bit(register_list,i) == 1)) {
      set_reg(proc,i,slv6_read_word(proc->mmu_ptr,address));
      address = (address + 4);
    }
}
  if (CurrentModeHasSPSR(proc))
    set_cpsr_sr(proc, *spsr(proc));
  else
    unpredictable("LDM3_M4_IB");
  value = slv6_read_word(proc->mmu_ptr,address);
  set_pc_raw_ws(proc,value,4);
  address = (address + 4);
  if ((W == 1))
    set_reg_m(proc, n, old_mode, new_Rn);
}

/* A4.1.22--A5.4.4
 * LDM (3) -- Load and Store Multiple - Decrement after */
void slv6_X_LDM3_M4_DA(struct SLv6_Processor *proc,
    const bool W,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t end_address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t start_address;
  uint32_t value;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  start_address = ((old_Rn - nb_reg_x4) + 4);
  end_address = old_Rn;
  if ((W == 1))
    new_Rn = (old_Rn - nb_reg_x4);
  address = start_address;
  size_t i; for (i = 0; i<=14; ++i) {
    if ((get_bit(register_list,i) == 1)) {
      set_reg(proc,i,slv6_read_word(proc->mmu_ptr,address));
      address = (address + 4);
    }
}
  if (CurrentModeHasSPSR(proc))
    set_cpsr_sr(proc, *spsr(proc));
  else
    unpredictable("LDM3_M4_DA");
  value = slv6_read_word(proc->mmu_ptr,address);
  set_pc_raw_ws(proc,value,4);
  address = (address + 4);
  if ((W == 1))
    set_reg_m(proc, n, old_mode, new_Rn);
}

/* A4.1.22--A5.4.5
 * LDM (3) -- Load and Store Multiple - Decrement before */
void slv6_X_LDM3_M4_DB(struct SLv6_Processor *proc,
    const bool W,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t end_address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t start_address;
  uint32_t value;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  start_address = (old_Rn - nb_reg_x4);
  end_address = (old_Rn - 4);
  if ((W == 1))
    new_Rn = (old_Rn - nb_reg_x4);
  address = start_address;
  size_t i; for (i = 0; i<=14; ++i) {
    if ((get_bit(register_list,i) == 1)) {
      set_reg(proc,i,slv6_read_word(proc->mmu_ptr,address));
      address = (address + 4);
    }
}
  if (CurrentModeHasSPSR(proc))
    set_cpsr_sr(proc, *spsr(proc));
  else
    unpredictable("LDM3_M4_DB");
  value = slv6_read_word(proc->mmu_ptr,address);
  set_pc_raw_ws(proc,value,4);
  address = (address + 4);
  if ((W == 1))
    set_reg_m(proc, n, old_mode, new_Rn);
}

/* A4.1.23--A5.2.6
 * LDR -- Load and Store Word or Unsigned Byte - Register pre indexed */
void slv6_X_LDR_M2_Reg_preInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t data;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = ((U == 1)? (old_Rn + old_Rm): (old_Rn - old_Rm));
  new_Rn = address;
  data = ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)? rotate_right(slv6_read_word(proc->mmu_ptr,address), (get_bits(address,1,0) * 8)): slv6_read_word(proc->mmu_ptr,address));
  if ((d == 15)) {
    set_pc_raw_ws(proc,(data & 0xFFFFFFFE),inst_size(proc));
    proc->cpsr.T_flag = get_bit(data,0);
  } else
    set_reg_or_pc_ws(proc,d,data,inst_size(proc));
  set_reg(proc,n,new_Rn);
}

/* A4.1.23--A5.2.7
 * LDR -- Load and Store Word or Unsigned Byte - Scaled register pre indexed */
void slv6_X_LDR_M2_ScReg_preInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t data;
  uint32_t index;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  switch (shift) {
  case 0:
    index = (old_Rm << shift_imm);
    break;
  case 1:
    index = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
    break;
  case 2:
    index = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 1)? 0xFFFFFFFF: 0): asr(old_Rm, shift_imm));
    break;
  case 3:
    index = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
    break;
    default: abort();
  }
  address = ((U == 1)? (old_Rn + index): (old_Rn - index));
  new_Rn = address;
  data = ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)? rotate_right(slv6_read_word(proc->mmu_ptr,address), (get_bits(address,1,0) * 8)): slv6_read_word(proc->mmu_ptr,address));
  if ((d == 15)) {
    set_pc_raw_ws(proc,(data & 0xFFFFFFFE),inst_size(proc));
    proc->cpsr.T_flag = get_bit(data,0);
  } else
    set_reg_or_pc_ws(proc,d,data,inst_size(proc));
  set_reg(proc,n,new_Rn);
}

/* A4.1.23--A5.2.9
 * LDR -- Load and Store Word or Unsigned Byte - Register post indexed */
void slv6_X_LDR_M2_Reg_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t data;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  if ((U == 1))
    new_Rn = (old_Rn + old_Rm);
  else
    new_Rn = (old_Rn - old_Rm);
  data = ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)? rotate_right(slv6_read_word(proc->mmu_ptr,address), (get_bits(address,1,0) * 8)): slv6_read_word(proc->mmu_ptr,address));
  if ((d == 15)) {
    set_pc_raw_ws(proc,(data & 0xFFFFFFFE),inst_size(proc));
    proc->cpsr.T_flag = get_bit(data,0);
  } else
    set_reg_or_pc_ws(proc,d,data,inst_size(proc));
  set_reg(proc,n,new_Rn);
}

/* A4.1.23--A5.2.10
 * LDR -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
void slv6_X_LDR_M2_ScReg_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t data;
  uint32_t index;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  switch (shift) {
  case 0:
    index = (old_Rm << shift_imm);
    break;
  case 1:
    index = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
    break;
  case 2:
    index = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 1)? 0xFFFFFFFF: 0): asr(old_Rm, shift_imm));
    break;
  case 3:
    index = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
    break;
    default: abort();
  }
  if ((U == 1))
    new_Rn = (old_Rn + index);
  else
    new_Rn = (old_Rn - index);
  data = ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)? rotate_right(slv6_read_word(proc->mmu_ptr,address), (get_bits(address,1,0) * 8)): slv6_read_word(proc->mmu_ptr,address));
  if ((d == 15)) {
    set_pc_raw_ws(proc,(data & 0xFFFFFFFE),inst_size(proc));
    proc->cpsr.T_flag = get_bit(data,0);
  } else
    set_reg_or_pc_ws(proc,d,data,inst_size(proc));
  set_reg(proc,n,new_Rn);
}

/* A4.1.24--A5.2.5
 * LDRB -- Load and Store Word or Unsigned Byte - Immediate pre indexed */
void slv6_X_LDRB_M2_Imm_preInd(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = (old_Rn + signed_offset_12);
  new_Rn = address;
  set_reg(proc,d,slv6_read_byte(proc->mmu_ptr,address));
  set_reg(proc,n,new_Rn);
}

/* A4.1.24--A5.2.6
 * LDRB -- Load and Store Word or Unsigned Byte - Register pre indexed */
void slv6_X_LDRB_M2_Reg_preInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = ((U == 1)? (old_Rn + old_Rm): (old_Rn - old_Rm));
  new_Rn = address;
  set_reg(proc,d,slv6_read_byte(proc->mmu_ptr,address));
  set_reg(proc,n,new_Rn);
}

/* A4.1.24--A5.2.7
 * LDRB -- Load and Store Word or Unsigned Byte - Scaled register pre indexed */
void slv6_X_LDRB_M2_ScReg_preInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t index;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  switch (shift) {
  case 0:
    index = (old_Rm << shift_imm);
    break;
  case 1:
    index = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
    break;
  case 2:
    index = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 1)? 0xFFFFFFFF: 0): asr(old_Rm, shift_imm));
    break;
  case 3:
    index = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
    break;
    default: abort();
  }
  address = ((U == 1)? (old_Rn + index): (old_Rn - index));
  new_Rn = address;
  set_reg(proc,d,slv6_read_byte(proc->mmu_ptr,address));
  set_reg(proc,n,new_Rn);
}

/* A4.1.24--A5.2.8
 * LDRB -- Load and Store Word or Unsigned Byte - Immediate post indexed */
void slv6_X_LDRB_M2_Imm_postInd(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  new_Rn = (old_Rn + signed_offset_12);
  set_reg(proc,d,slv6_read_byte(proc->mmu_ptr,address));
  set_reg(proc,n,new_Rn);
}

/* A4.1.24--A5.2.9
 * LDRB -- Load and Store Word or Unsigned Byte - Register post indexed */
void slv6_X_LDRB_M2_Reg_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  if ((U == 1))
    new_Rn = (old_Rn + old_Rm);
  else
    new_Rn = (old_Rn - old_Rm);
  set_reg(proc,d,slv6_read_byte(proc->mmu_ptr,address));
  set_reg(proc,n,new_Rn);
}

/* A4.1.24--A5.2.10
 * LDRB -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
void slv6_X_LDRB_M2_ScReg_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t index;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  switch (shift) {
  case 0:
    index = (old_Rm << shift_imm);
    break;
  case 1:
    index = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
    break;
  case 2:
    index = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 1)? 0xFFFFFFFF: 0): asr(old_Rm, shift_imm));
    break;
  case 3:
    index = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
    break;
    default: abort();
  }
  if ((U == 1))
    new_Rn = (old_Rn + index);
  else
    new_Rn = (old_Rn - index);
  set_reg(proc,d,slv6_read_byte(proc->mmu_ptr,address));
  set_reg(proc,n,new_Rn);
}

/* A4.1.25--A5.2.8
 * LDRBT -- Load and Store Word or Unsigned Byte - Immediate post indexed */
void slv6_X_LDRBT_M2_Imm_postInd(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  new_Rn = (old_Rn + signed_offset_12);
  set_reg(proc,d,slv6_read_byte_as_user(proc->mmu_ptr,address));
  set_reg(proc,n,new_Rn);
}

/* A4.1.25--A5.2.9
 * LDRBT -- Load and Store Word or Unsigned Byte - Register post indexed */
void slv6_X_LDRBT_M2_Reg_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  if ((U == 1))
    new_Rn = (old_Rn + old_Rm);
  else
    new_Rn = (old_Rn - old_Rm);
  set_reg(proc,d,slv6_read_byte_as_user(proc->mmu_ptr,address));
  set_reg(proc,n,new_Rn);
}

/* A4.1.25--A5.2.10
 * LDRBT -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
void slv6_X_LDRBT_M2_ScReg_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t index;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  switch (shift) {
  case 0:
    index = (old_Rm << shift_imm);
    break;
  case 1:
    index = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
    break;
  case 2:
    index = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 1)? 0xFFFFFFFF: 0): asr(old_Rm, shift_imm));
    break;
  case 3:
    index = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
    break;
    default: abort();
  }
  if ((U == 1))
    new_Rn = (old_Rn + index);
  else
    new_Rn = (old_Rn - index);
  set_reg(proc,d,slv6_read_byte_as_user(proc->mmu_ptr,address));
  set_reg(proc,n,new_Rn);
}

/* A4.1.26--A5.3.2
 * LDRD -- Miscellaneous Loads and Stores - Immediate offset */
void slv6_X_LDRD_M3_ImmOff(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint8_t offset_8;
  offset_8 = immedHL;
  address = ((U == 1)? (old_Rn + offset_8): (old_Rn - offset_8));
  if ((((is_even(d) && (d != 14)) && (get_bits(address,1,0) == 0)) && ((CP15_reg1_Ubit(proc->cp15_ptr) == 1) || (get_bit(address,2) == 0)))) {
    set_reg(proc,d,slv6_read_word(proc->mmu_ptr,address));
    set_reg(proc,(d + 1),slv6_read_word(proc->mmu_ptr,(address + 4)));
  } else
    unpredictable("LDRD_M3_ImmOff");
}

/* A4.1.26--A5.3.3
 * LDRD -- Miscellaneous Loads and Stores - Register offset */
void slv6_X_LDRD_M3_RegOff(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  address = ((U == 1)? (old_Rn + old_Rm): (old_Rn - old_Rm));
  if ((((is_even(d) && (d != 14)) && (get_bits(address,1,0) == 0)) && ((CP15_reg1_Ubit(proc->cp15_ptr) == 1) || (get_bit(address,2) == 0)))) {
    set_reg(proc,d,slv6_read_word(proc->mmu_ptr,address));
    set_reg(proc,(d + 1),slv6_read_word(proc->mmu_ptr,(address + 4)));
  } else
    unpredictable("LDRD_M3_RegOff");
}

/* A4.1.26--A5.3.4
 * LDRD -- Miscellaneous Loads and Stores - Immediate pre indexed */
void slv6_X_LDRD_M3_Imm_preInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t new_Rn;
  uint8_t offset_8;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  offset_8 = immedHL;
  address = ((U == 1)? (old_Rn + offset_8): (old_Rn - offset_8));
  new_Rn = address;
  if ((((is_even(d) && (d != 14)) && (get_bits(address,1,0) == 0)) && ((CP15_reg1_Ubit(proc->cp15_ptr) == 1) || (get_bit(address,2) == 0)))) {
    set_reg(proc,d,slv6_read_word(proc->mmu_ptr,address));
    set_reg(proc,(d + 1),slv6_read_word(proc->mmu_ptr,(address + 4)));
  } else
    unpredictable("LDRD_M3_Imm_preInd");
  set_reg(proc,n,new_Rn);
}

/* A4.1.26--A5.3.5
 * LDRD -- Miscellaneous Loads and Stores - Register pre indexed */
void slv6_X_LDRD_M3_Reg_preInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = ((U == 1)? (old_Rn + old_Rm): (old_Rn - old_Rm));
  new_Rn = address;
  if ((((is_even(d) && (d != 14)) && (get_bits(address,1,0) == 0)) && ((CP15_reg1_Ubit(proc->cp15_ptr) == 1) || (get_bit(address,2) == 0)))) {
    set_reg(proc,d,slv6_read_word(proc->mmu_ptr,address));
    set_reg(proc,(d + 1),slv6_read_word(proc->mmu_ptr,(address + 4)));
  } else
    unpredictable("LDRD_M3_Reg_preInd");
  set_reg(proc,n,new_Rn);
}

/* A4.1.26--A5.3.6
 * LDRD -- Miscellaneous Loads and Stores - Immediate post indexed */
void slv6_X_LDRD_M3_Imm_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t new_Rn;
  uint8_t offset_8;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  offset_8 = immedHL;
  if ((U == 1))
    new_Rn = (old_Rn + offset_8);
  else
    new_Rn = (old_Rn - offset_8);
  if ((((is_even(d) && (d != 14)) && (get_bits(address,1,0) == 0)) && ((CP15_reg1_Ubit(proc->cp15_ptr) == 1) || (get_bit(address,2) == 0)))) {
    set_reg(proc,d,slv6_read_word(proc->mmu_ptr,address));
    set_reg(proc,(d + 1),slv6_read_word(proc->mmu_ptr,(address + 4)));
  } else
    unpredictable("LDRD_M3_Imm_postInd");
  set_reg_or_pc_ws(proc,n,new_Rn,4);
}

/* A4.1.26--A5.3.7
 * LDRD -- Miscellaneous Loads and Stores - Register post indexed */
void slv6_X_LDRD_M3_Reg_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  if ((U == 1))
    new_Rn = (old_Rn + old_Rm);
  else
    new_Rn = (old_Rn - old_Rm);
  if ((((is_even(d) && (d != 14)) && (get_bits(address,1,0) == 0)) && ((CP15_reg1_Ubit(proc->cp15_ptr) == 1) || (get_bit(address,2) == 0)))) {
    set_reg(proc,d,slv6_read_word(proc->mmu_ptr,address));
    set_reg(proc,(d + 1),slv6_read_word(proc->mmu_ptr,(address + 4)));
  } else
    unpredictable("LDRD_M3_Reg_postInd");
  set_reg_or_pc_ws(proc,n,new_Rn,4);
}

/* A4.1.27
 * LDREX */
void slv6_X_LDREX(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t physical_address;
  uint32_t processor_id;
  processor_id = ExecutingProcessor();
  set_reg(proc,d,slv6_read_word(proc->mmu_ptr,old_Rn));
  physical_address = slv6_TLB(old_Rn);
  if ((Shared(old_Rn) == 1))
    MarkExclusiveGlobal(physical_address, processor_id, 4);
  MarkExclusiveLocal(physical_address, processor_id, 4);
}

/* A4.1.28--A5.3.3
 * LDRH -- Miscellaneous Loads and Stores - Register offset */
void slv6_X_LDRH_M3_RegOff(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint16_t data;
  address = ((U == 1)? (old_Rn + old_Rm): (old_Rn - old_Rm));
  if ((!((get_bit(address,0) == 0)) && (CP15_reg1_Ubit(proc->cp15_ptr) == 0)))
    unpredictable("LDRH_M3_RegOff");
  data = slv6_read_half(proc->mmu_ptr,address);
  set_reg(proc,d,ZeroExtend(get_half_0(data)));
}

/* A4.1.28--A5.3.4
 * LDRH -- Miscellaneous Loads and Stores - Immediate pre indexed */
void slv6_X_LDRH_M3_Imm_preInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint16_t data;
  uint32_t new_Rn;
  uint8_t offset_8;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  offset_8 = immedHL;
  address = ((U == 1)? (old_Rn + offset_8): (old_Rn - offset_8));
  new_Rn = address;
  if ((!((get_bit(address,0) == 0)) && (CP15_reg1_Ubit(proc->cp15_ptr) == 0)))
    unpredictable("LDRH_M3_Imm_preInd");
  data = slv6_read_half(proc->mmu_ptr,address);
  set_reg(proc,d,ZeroExtend(get_half_0(data)));
  set_reg(proc,n,new_Rn);
}

/* A4.1.28--A5.3.5
 * LDRH -- Miscellaneous Loads and Stores - Register pre indexed */
void slv6_X_LDRH_M3_Reg_preInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint16_t data;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = ((U == 1)? (old_Rn + old_Rm): (old_Rn - old_Rm));
  new_Rn = address;
  if ((!((get_bit(address,0) == 0)) && (CP15_reg1_Ubit(proc->cp15_ptr) == 0)))
    unpredictable("LDRH_M3_Reg_preInd");
  data = slv6_read_half(proc->mmu_ptr,address);
  set_reg(proc,d,ZeroExtend(get_half_0(data)));
  set_reg(proc,n,new_Rn);
}

/* A4.1.28--A5.3.6
 * LDRH -- Miscellaneous Loads and Stores - Immediate post indexed */
void slv6_X_LDRH_M3_Imm_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint16_t data;
  uint32_t new_Rn;
  uint8_t offset_8;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  offset_8 = immedHL;
  if ((U == 1))
    new_Rn = (old_Rn + offset_8);
  else
    new_Rn = (old_Rn - offset_8);
  if ((!((get_bit(address,0) == 0)) && (CP15_reg1_Ubit(proc->cp15_ptr) == 0)))
    unpredictable("LDRH_M3_Imm_postInd");
  data = slv6_read_half(proc->mmu_ptr,address);
  set_reg(proc,d,ZeroExtend(get_half_0(data)));
  set_reg_or_pc_ws(proc,n,new_Rn,4);
}

/* A4.1.28--A5.3.7
 * LDRH -- Miscellaneous Loads and Stores - Register post indexed */
void slv6_X_LDRH_M3_Reg_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint16_t data;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  if ((U == 1))
    new_Rn = (old_Rn + old_Rm);
  else
    new_Rn = (old_Rn - old_Rm);
  if ((!((get_bit(address,0) == 0)) && (CP15_reg1_Ubit(proc->cp15_ptr) == 0)))
    unpredictable("LDRH_M3_Reg_postInd");
  data = slv6_read_half(proc->mmu_ptr,address);
  set_reg(proc,d,ZeroExtend(get_half_0(data)));
  set_reg_or_pc_ws(proc,n,new_Rn,4);
}

/* A4.1.29--A5.3.2
 * LDRSB -- Miscellaneous Loads and Stores - Immediate offset */
void slv6_X_LDRSB_M3_ImmOff(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint8_t data;
  uint8_t offset_8;
  offset_8 = immedHL;
  address = ((U == 1)? (old_Rn + offset_8): (old_Rn - offset_8));
  data = slv6_read_byte(proc->mmu_ptr,address);
  set_reg(proc,d,SignExtend8(data));
}

/* A4.1.29--A5.3.3
 * LDRSB -- Miscellaneous Loads and Stores - Register offset */
void slv6_X_LDRSB_M3_RegOff(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint8_t data;
  address = ((U == 1)? (old_Rn + old_Rm): (old_Rn - old_Rm));
  data = slv6_read_byte(proc->mmu_ptr,address);
  set_reg(proc,d,SignExtend8(data));
}

/* A4.1.29--A5.3.4
 * LDRSB -- Miscellaneous Loads and Stores - Immediate pre indexed */
void slv6_X_LDRSB_M3_Imm_preInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint8_t data;
  uint32_t new_Rn;
  uint8_t offset_8;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  offset_8 = immedHL;
  address = ((U == 1)? (old_Rn + offset_8): (old_Rn - offset_8));
  new_Rn = address;
  data = slv6_read_byte(proc->mmu_ptr,address);
  set_reg(proc,d,SignExtend8(data));
  set_reg(proc,n,new_Rn);
}

/* A4.1.29--A5.3.5
 * LDRSB -- Miscellaneous Loads and Stores - Register pre indexed */
void slv6_X_LDRSB_M3_Reg_preInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint8_t data;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = ((U == 1)? (old_Rn + old_Rm): (old_Rn - old_Rm));
  new_Rn = address;
  data = slv6_read_byte(proc->mmu_ptr,address);
  set_reg(proc,d,SignExtend8(data));
  set_reg(proc,n,new_Rn);
}

/* A4.1.29--A5.3.6
 * LDRSB -- Miscellaneous Loads and Stores - Immediate post indexed */
void slv6_X_LDRSB_M3_Imm_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint8_t data;
  uint32_t new_Rn;
  uint8_t offset_8;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  offset_8 = immedHL;
  if ((U == 1))
    new_Rn = (old_Rn + offset_8);
  else
    new_Rn = (old_Rn - offset_8);
  data = slv6_read_byte(proc->mmu_ptr,address);
  set_reg(proc,d,SignExtend8(data));
  set_reg_or_pc_ws(proc,n,new_Rn,4);
}

/* A4.1.29--A5.3.7
 * LDRSB -- Miscellaneous Loads and Stores - Register post indexed */
void slv6_X_LDRSB_M3_Reg_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint8_t data;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  if ((U == 1))
    new_Rn = (old_Rn + old_Rm);
  else
    new_Rn = (old_Rn - old_Rm);
  data = slv6_read_byte(proc->mmu_ptr,address);
  set_reg(proc,d,SignExtend8(data));
  set_reg_or_pc_ws(proc,n,new_Rn,4);
}

/* A4.1.30--A5.3.2
 * LDRSH -- Miscellaneous Loads and Stores - Immediate offset */
void slv6_X_LDRSH_M3_ImmOff(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint16_t data;
  uint8_t offset_8;
  offset_8 = immedHL;
  address = ((U == 1)? (old_Rn + offset_8): (old_Rn - offset_8));
  if ((!((get_bit(address,0) == 0)) && (CP15_reg1_Ubit(proc->cp15_ptr) == 0)))
    unpredictable("LDRSH_M3_ImmOff");
  data = slv6_read_half(proc->mmu_ptr,address);
  set_reg(proc,d,SignExtend16(get_half_0(data)));
}

/* A4.1.30--A5.3.3
 * LDRSH -- Miscellaneous Loads and Stores - Register offset */
void slv6_X_LDRSH_M3_RegOff(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint16_t data;
  address = ((U == 1)? (old_Rn + old_Rm): (old_Rn - old_Rm));
  if ((!((get_bit(address,0) == 0)) && (CP15_reg1_Ubit(proc->cp15_ptr) == 0)))
    unpredictable("LDRSH_M3_RegOff");
  data = slv6_read_half(proc->mmu_ptr,address);
  set_reg(proc,d,SignExtend16(get_half_0(data)));
}

/* A4.1.30--A5.3.4
 * LDRSH -- Miscellaneous Loads and Stores - Immediate pre indexed */
void slv6_X_LDRSH_M3_Imm_preInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint16_t data;
  uint32_t new_Rn;
  uint8_t offset_8;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  offset_8 = immedHL;
  address = ((U == 1)? (old_Rn + offset_8): (old_Rn - offset_8));
  new_Rn = address;
  if ((!((get_bit(address,0) == 0)) && (CP15_reg1_Ubit(proc->cp15_ptr) == 0)))
    unpredictable("LDRSH_M3_Imm_preInd");
  data = slv6_read_half(proc->mmu_ptr,address);
  set_reg(proc,d,SignExtend16(get_half_0(data)));
  set_reg(proc,n,new_Rn);
}

/* A4.1.30--A5.3.5
 * LDRSH -- Miscellaneous Loads and Stores - Register pre indexed */
void slv6_X_LDRSH_M3_Reg_preInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint16_t data;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = ((U == 1)? (old_Rn + old_Rm): (old_Rn - old_Rm));
  new_Rn = address;
  if ((!((get_bit(address,0) == 0)) && (CP15_reg1_Ubit(proc->cp15_ptr) == 0)))
    unpredictable("LDRSH_M3_Reg_preInd");
  data = slv6_read_half(proc->mmu_ptr,address);
  set_reg(proc,d,SignExtend16(get_half_0(data)));
  set_reg(proc,n,new_Rn);
}

/* A4.1.30--A5.3.6
 * LDRSH -- Miscellaneous Loads and Stores - Immediate post indexed */
void slv6_X_LDRSH_M3_Imm_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint16_t data;
  uint32_t new_Rn;
  uint8_t offset_8;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  offset_8 = immedHL;
  if ((U == 1))
    new_Rn = (old_Rn + offset_8);
  else
    new_Rn = (old_Rn - offset_8);
  if ((!((get_bit(address,0) == 0)) && (CP15_reg1_Ubit(proc->cp15_ptr) == 0)))
    unpredictable("LDRSH_M3_Imm_postInd");
  data = slv6_read_half(proc->mmu_ptr,address);
  set_reg(proc,d,SignExtend16(get_half_0(data)));
  set_reg_or_pc_ws(proc,n,new_Rn,4);
}

/* A4.1.30--A5.3.7
 * LDRSH -- Miscellaneous Loads and Stores - Register post indexed */
void slv6_X_LDRSH_M3_Reg_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint16_t data;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  if ((U == 1))
    new_Rn = (old_Rn + old_Rm);
  else
    new_Rn = (old_Rn - old_Rm);
  if ((!((get_bit(address,0) == 0)) && (CP15_reg1_Ubit(proc->cp15_ptr) == 0)))
    unpredictable("LDRSH_M3_Reg_postInd");
  data = slv6_read_half(proc->mmu_ptr,address);
  set_reg(proc,d,SignExtend16(get_half_0(data)));
  set_reg_or_pc_ws(proc,n,new_Rn,4);
}

/* A4.1.31--A5.2.8
 * LDRT -- Load and Store Word or Unsigned Byte - Immediate post indexed */
void slv6_X_LDRT_M2_Imm_postInd(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  new_Rn = (old_Rn + signed_offset_12);
  if ((CP15_reg1_Ubit(proc->cp15_ptr) == 0))
    set_reg(proc,d,rotate_right(slv6_read_word_as_user(proc->mmu_ptr,address), (get_bits(address,1,0) * 8)));
  else
    set_reg(proc,d,slv6_read_word_as_user(proc->mmu_ptr,address));
  set_reg(proc,n,new_Rn);
}

/* A4.1.31--A5.2.9
 * LDRT -- Load and Store Word or Unsigned Byte - Register post indexed */
void slv6_X_LDRT_M2_Reg_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  if ((U == 1))
    new_Rn = (old_Rn + old_Rm);
  else
    new_Rn = (old_Rn - old_Rm);
  if ((CP15_reg1_Ubit(proc->cp15_ptr) == 0))
    set_reg(proc,d,rotate_right(slv6_read_word_as_user(proc->mmu_ptr,address), (get_bits(address,1,0) * 8)));
  else
    set_reg(proc,d,slv6_read_word_as_user(proc->mmu_ptr,address));
  set_reg(proc,n,new_Rn);
}

/* A4.1.31--A5.2.10
 * LDRT -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
void slv6_X_LDRT_M2_ScReg_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t index;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  switch (shift) {
  case 0:
    index = (old_Rm << shift_imm);
    break;
  case 1:
    index = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
    break;
  case 2:
    index = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 1)? 0xFFFFFFFF: 0): asr(old_Rm, shift_imm));
    break;
  case 3:
    index = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
    break;
    default: abort();
  }
  if ((U == 1))
    new_Rn = (old_Rn + index);
  else
    new_Rn = (old_Rn - index);
  if ((CP15_reg1_Ubit(proc->cp15_ptr) == 0))
    set_reg(proc,d,rotate_right(slv6_read_word_as_user(proc->mmu_ptr,address), (get_bits(address,1,0) * 8)));
  else
    set_reg(proc,d,slv6_read_word_as_user(proc->mmu_ptr,address));
  set_reg(proc,n,new_Rn);
}

/* A4.1.32
 * MCR */
void slv6_X_MCR(struct SLv6_Processor *proc,
    const uint8_t CRm,
    const uint8_t CRn,
    const uint8_t cp_num,
    const uint8_t d,
    const uint8_t opcode_1,
    const uint8_t opcode_2,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  if (!slv6_MCR_send(proc,cp_num,opcode_1,opcode_2,CRn,CRm,reg(proc,d))) return;
}

/* A4.1.33
 * MCRR */
void slv6_X_MCRR(struct SLv6_Processor *proc,
    const uint8_t cp_num,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  if (!slv6_MCRR_send(proc,cp_num,reg(proc,d))) return;
  if (!slv6_MCRR_send(proc,cp_num,old_Rn)) return;
}

/* A4.1.34
 * MLA */
void slv6_X_MLA(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,get_bits(((to_u64(old_Rm) * to_u64(old_Rs)) + old_Rn),31,0));
  if ((S == 1)) {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
  }
}

/* A4.1.35--A5.1.4
 * MOV -- Data processing operands - Register */
void slv6_X_MOV_M1_Reg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = old_Rm;
  shifter_carry_out = proc->cpsr.C_flag;
  set_reg_or_pc_ws(proc,d,shifter_operand,4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MOV_M1_Reg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.35--A5.1.10
 * MOV -- Data processing operands - Arithmetic shift right by register */
void slv6_X_MOV_M1_ASRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? asr(old_Rm, get_byte_0(old_Rs)): ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF)));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): get_bit(old_Rm,31)));
  set_reg(proc,d,shifter_operand);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MOV_M1_ASRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.35--A5.1.12
 * MOV -- Data processing operands - Rotate right by register */
void slv6_X_MOV_M1_RRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_bits(old_Rs,4,0) == 0)? old_Rm: rotate_right(old_Rm, get_bits(old_Rs,4,0))));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_bits(old_Rs,4,0) == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(get_bits(old_Rs,4,0) - 1))));
  set_reg(proc,d,shifter_operand);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MOV_M1_RRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.35--A5.1.13
 * MOV -- Data processing operands - Rotate right with extend */
void slv6_X_MOV_M1_RRE(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((proc->cpsr.C_flag << 31) | (old_Rm >> 1));
  shifter_carry_out = get_bit(old_Rm,0);
  set_reg_or_pc_ws(proc,d,shifter_operand,4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MOV_M1_RRE");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.36
 * MRC */
void slv6_X_MRC(struct SLv6_Processor *proc,
    const uint8_t CRm,
    const uint8_t CRn,
    const uint8_t cp_num,
    const uint8_t d,
    const uint8_t opcode_1,
    const uint8_t opcode_2,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  uint32_t data;
  if (!slv6_MRC_value(proc,&data,cp_num,opcode_1,opcode_2,CRn,CRm)) return;
  if ((d == 15)) {
    proc->cpsr.N_flag = get_bit(data,31);
    proc->cpsr.Z_flag = get_bit(data,30);
    proc->cpsr.C_flag = get_bit(data,29);
    proc->cpsr.V_flag = get_bit(data,28);
  } else
    set_reg_or_pc_ws(proc,d,data,4);
}

/* A4.1.37
 * MRRC */
void slv6_X_MRRC(struct SLv6_Processor *proc,
    const uint8_t cp_num,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  if (!slv6_MRRC_first_value(proc,addr_of_reg(proc,d),cp_num)) return;
  if (!slv6_MRRC_second_value(proc,addr_of_reg(proc,n),cp_num)) return;
}

/* A4.1.38
 * MRS */
void slv6_X_MRS(struct SLv6_Processor *proc,
    const bool R,
    const uint8_t d,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  if ((R == 1))
    set_reg(proc,d,StatusRegister_to_uint32(spsr(proc)));
  else
    set_reg(proc,d,StatusRegister_to_uint32(&proc->cpsr));
}

/* A4.1.39
 * MSRimm */
void slv6_X_MSRimm(struct SLv6_Processor *proc,
    const bool R,
    const uint8_t field_mask,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  uint32_t byte_mask;
  uint32_t mask;
  uint32_t operand;
  operand = immed_rotated;
  if (((operand & UnallocMask()) != 0))
    unpredictable("MSRimm");
  byte_mask = (((((get_bit(field_mask,0) == 1)? 0x000000FF: 0x00000000) | ((get_bit(field_mask,1) == 1)? 0x0000FF00: 0x00000000)) | ((get_bit(field_mask,2) == 1)? 0x00FF0000: 0x00000000)) | ((get_bit(field_mask,3) == 1)? 0xFF000000: 0x00000000));
  if ((R == 0)) {
    if ((InAPrivilegedMode(proc) && ((operand & StateMask()) != 0)))
      unpredictable("MSRimm");
    mask = (!(InAPrivilegedMode(proc))? (byte_mask & UserMask()): (byte_mask & (UserMask() | PrivMask())));
    set_cpsr_bin(proc, ((StatusRegister_to_uint32(&proc->cpsr) & ~(mask)) | (operand & mask)));
  } else {
    if (CurrentModeHasSPSR(proc)) {
      mask = (byte_mask & ((UserMask() | PrivMask()) | StateMask()));
      set_StatusRegister(spsr(proc),((StatusRegister_to_uint32(spsr(proc)) & ~(mask)) | (operand & mask)));
    } else
      unpredictable("MSRimm");
  }
}

/* A4.1.39
 * MSRreg */
void slv6_X_MSRreg(struct SLv6_Processor *proc,
    const bool R,
    const uint8_t field_mask,
    const uint8_t m,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  uint32_t byte_mask;
  uint32_t mask;
  uint32_t operand;
  operand = old_Rm;
  if (((operand & UnallocMask()) != 0))
    unpredictable("MSRreg");
  byte_mask = (((((get_bit(field_mask,0) == 1)? 0x000000FF: 0x00000000) | ((get_bit(field_mask,1) == 1)? 0x0000FF00: 0x00000000)) | ((get_bit(field_mask,2) == 1)? 0x00FF0000: 0x00000000)) | ((get_bit(field_mask,3) == 1)? 0xFF000000: 0x00000000));
  if ((R == 0)) {
    if ((InAPrivilegedMode(proc) && ((operand & StateMask()) != 0)))
      unpredictable("MSRreg");
    mask = (!(InAPrivilegedMode(proc))? (byte_mask & UserMask()): (byte_mask & (UserMask() | PrivMask())));
    set_cpsr_bin(proc, ((StatusRegister_to_uint32(&proc->cpsr) & ~(mask)) | (operand & mask)));
  } else {
    if (CurrentModeHasSPSR(proc)) {
      mask = (byte_mask & ((UserMask() | PrivMask()) | StateMask()));
      set_StatusRegister(spsr(proc),((StatusRegister_to_uint32(spsr(proc)) & ~(mask)) | (operand & mask)));
    } else
      unpredictable("MSRreg");
  }
}

/* A4.1.41--A5.1.5
 * MVN -- Data processing operands - Logical shift left by immediate */
void slv6_X_MVN_M1_LSLImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? old_Rm: (old_Rm << shift_imm));
  shifter_carry_out = ((shift_imm == 0)? proc->cpsr.C_flag: get_bit(old_Rm,(32 - shift_imm)));
  set_reg_or_pc_ws(proc,d,~(shifter_operand),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MVN_M1_LSLImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.41--A5.1.6
 * MVN -- Data processing operands - Logical shift left by register */
void slv6_X_MVN_M1_LSLReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm << get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(32 - get_byte_0(old_Rs))): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,0): 0)));
  set_reg(proc,d,~(shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MVN_M1_LSLReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.41--A5.1.7
 * MVN -- Data processing operands - Logical shift right by immediate */
void slv6_X_MVN_M1_LSRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,~(shifter_operand),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MVN_M1_LSRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.41--A5.1.8
 * MVN -- Data processing operands - Logical shift right by register */
void slv6_X_MVN_M1_LSRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm >> get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,31): 0)));
  set_reg(proc,d,~(shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MVN_M1_LSRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.41--A5.1.9
 * MVN -- Data processing operands - Arithmetic shift right by immediate */
void slv6_X_MVN_M1_ASRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF): asr(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,~(shifter_operand),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MVN_M1_ASRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.41--A5.1.10
 * MVN -- Data processing operands - Arithmetic shift right by register */
void slv6_X_MVN_M1_ASRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? asr(old_Rm, get_byte_0(old_Rs)): ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF)));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): get_bit(old_Rm,31)));
  set_reg(proc,d,~(shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MVN_M1_ASRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.41--A5.1.11
 * MVN -- Data processing operands - Rotate right by immediate */
void slv6_X_MVN_M1_RRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,0): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,~(shifter_operand),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MVN_M1_RRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.41--A5.1.12
 * MVN -- Data processing operands - Rotate right by register */
void slv6_X_MVN_M1_RRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_bits(old_Rs,4,0) == 0)? old_Rm: rotate_right(old_Rm, get_bits(old_Rs,4,0))));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_bits(old_Rs,4,0) == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(get_bits(old_Rs,4,0) - 1))));
  set_reg(proc,d,~(shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MVN_M1_RRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.41--A5.1.13
 * MVN -- Data processing operands - Rotate right with extend */
void slv6_X_MVN_M1_RRE(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((proc->cpsr.C_flag << 31) | (old_Rm >> 1));
  shifter_carry_out = get_bit(old_Rm,0);
  set_reg_or_pc_ws(proc,d,~(shifter_operand),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MVN_M1_RRE");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.42--A5.1.6
 * ORR -- Data processing operands - Logical shift left by register */
void slv6_X_ORR_M1_LSLReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm << get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(32 - get_byte_0(old_Rs))): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,0): 0)));
  set_reg(proc,d,(old_Rn | shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ORR_M1_LSLReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.42--A5.1.8
 * ORR -- Data processing operands - Logical shift right by register */
void slv6_X_ORR_M1_LSRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm >> get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,31): 0)));
  set_reg(proc,d,(old_Rn | shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ORR_M1_LSRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.42--A5.1.10
 * ORR -- Data processing operands - Arithmetic shift right by register */
void slv6_X_ORR_M1_ASRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? asr(old_Rm, get_byte_0(old_Rs)): ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF)));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): get_bit(old_Rm,31)));
  set_reg(proc,d,(old_Rn | shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ORR_M1_ASRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.42--A5.1.11
 * ORR -- Data processing operands - Rotate right by immediate */
void slv6_X_ORR_M1_RRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,0): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn | shifter_operand),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ORR_M1_RRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.42--A5.1.12
 * ORR -- Data processing operands - Rotate right by register */
void slv6_X_ORR_M1_RRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_bits(old_Rs,4,0) == 0)? old_Rm: rotate_right(old_Rm, get_bits(old_Rs,4,0))));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_bits(old_Rs,4,0) == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(get_bits(old_Rs,4,0) - 1))));
  set_reg(proc,d,(old_Rn | shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ORR_M1_RRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.42--A5.1.13
 * ORR -- Data processing operands - Rotate right with extend */
void slv6_X_ORR_M1_RRE(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((proc->cpsr.C_flag << 31) | (old_Rm >> 1));
  shifter_carry_out = get_bit(old_Rm,0);
  set_reg_or_pc_ws(proc,d,(old_Rn | shifter_operand),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ORR_M1_RRE");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = shifter_carry_out;
    }
  }
}

/* A4.1.43
 * PKHBT */
void slv6_X_PKHBT(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 15, 0, get_half_0(old_Rn));
  set_field(addr_of_reg(proc,d), 31, 16, get_half_1((old_Rm << shift_imm)));
}

/* A4.1.44
 * PKHTB */
void slv6_X_PKHTB(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  if ((shift_imm == 0)) {
    if ((get_bit(old_Rm,31) == 0))
      set_field(addr_of_reg(proc,d), 15, 0, 0x0000);
    else
      set_field(addr_of_reg(proc,d), 15, 0, 0xFFFF);
  } else
    set_field(addr_of_reg(proc,d), 15, 0, get_half_0(asr(old_Rm, shift_imm)));
  set_field(addr_of_reg(proc,d), 31, 16, get_half_1(old_Rn));
}

/* A4.1.45--A5.2.2
 * PLD -- Load and Store Word or Unsigned Byte - Immediate offset */
void slv6_X_PLD_M2_ImmOff(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint32_t signed_offset_12)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  address = (old_Rn + signed_offset_12);

}

/* A4.1.45--A5.2.3
 * PLD -- Load and Store Word or Unsigned Byte - Register offset */
void slv6_X_PLD_M2_RegOff(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  address = ((U == 1)? (old_Rn + old_Rm): (old_Rn - old_Rm));

}

/* A4.1.45--A5.2.4
 * PLD -- Load and Store Word or Unsigned Byte - Scaled register offset */
void slv6_X_PLD_M2_ScRegOff(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t index;
  switch (shift) {
  case 0:
    index = (old_Rm << shift_imm);
    break;
  case 1:
    index = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
    break;
  case 2:
    index = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 1)? 0xFFFFFFFF: 0): asr(old_Rm, shift_imm));
    break;
  case 3:
    index = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
    break;
    default: abort();
  }
  address = ((U == 1)? (old_Rn + index): (old_Rn - index));
}

/* A4.1.46
 * QADD */
void slv6_X_QADD(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,SignedSat32_add(old_Rm, old_Rn));
  if (SignedDoesSat32_add(old_Rm, old_Rn))
    proc->cpsr.Q_flag = 1;
}

/* A4.1.47
 * QADD16 */
void slv6_X_QADD16(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 15, 0, SignedSat((get_half_0(old_Rn) + get_half_0(old_Rm)), 16));
  set_field(addr_of_reg(proc,d), 31, 16, SignedSat((get_half_1(old_Rn) + get_half_1(old_Rm)), 16));
}

/* A4.1.48
 * QADD8 */
void slv6_X_QADD8(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 7, 0, SignedSat((get_byte_0(old_Rn) + get_byte_0(old_Rm)), 8));
  set_field(addr_of_reg(proc,d), 15, 8, SignedSat((get_byte_1(old_Rn) + get_byte_1(old_Rm)), 8));
  set_field(addr_of_reg(proc,d), 23, 16, SignedSat((get_byte_2(old_Rn) + get_byte_2(old_Rm)), 8));
  set_field(addr_of_reg(proc,d), 31, 24, SignedSat((get_byte_3(old_Rn) + get_byte_3(old_Rm)), 8));
}

/* A4.1.49
 * QADDSUBX */
void slv6_X_QADDSUBX(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 31, 16, SignedSat((get_half_1(old_Rn) + get_half_0(old_Rm)), 16));
  set_field(addr_of_reg(proc,d), 15, 0, SignedSat((get_half_0(old_Rn) - get_half_1(old_Rm)), 16));
}

/* A4.1.50
 * QDADD */
void slv6_X_QDADD(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,SignedSat32_add(old_Rm, SignedSat32_double(old_Rn)));
  if ((SignedDoesSat32_add(old_Rm, SignedSat32_double(old_Rn)) || SignedDoesSat32_double(old_Rn)))
    proc->cpsr.Q_flag = 1;
}

/* A4.1.51
 * QDSUB */
void slv6_X_QDSUB(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,SignedSat32_sub(old_Rm, SignedSat32_double(old_Rn)));
  if ((SignedDoesSat32_sub(old_Rm, SignedSat32_double(old_Rn)) || SignedDoesSat32_double(old_Rn)))
    proc->cpsr.Q_flag = 1;
}

/* A4.1.52
 * QSUB */
void slv6_X_QSUB(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,SignedSat32_sub(old_Rm, old_Rn));
  if (SignedDoesSat32_sub(old_Rm, old_Rn))
    proc->cpsr.Q_flag = 1;
}

/* A4.1.53
 * QSUB16 */
void slv6_X_QSUB16(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 15, 0, SignedSat((get_half_0(old_Rn) - get_half_0(old_Rm)), 16));
  set_field(addr_of_reg(proc,d), 31, 16, SignedSat((get_half_1(old_Rn) - get_half_1(old_Rm)), 16));
}

/* A4.1.54
 * QSUB8 */
void slv6_X_QSUB8(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 7, 0, SignedSat((get_byte_0(old_Rn) - get_byte_0(old_Rm)), 8));
  set_field(addr_of_reg(proc,d), 15, 8, SignedSat((get_byte_1(old_Rn) - get_byte_1(old_Rm)), 8));
  set_field(addr_of_reg(proc,d), 23, 16, SignedSat((get_byte_2(old_Rn) - get_byte_2(old_Rm)), 8));
  set_field(addr_of_reg(proc,d), 31, 24, SignedSat((get_byte_3(old_Rn) - get_byte_3(old_Rm)), 8));
}

/* A4.1.55
 * QSUBADDX */
void slv6_X_QSUBADDX(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 31, 16, SignedSat((get_half_1(old_Rn) - get_half_0(old_Rm)), 16));
  set_field(addr_of_reg(proc,d), 15, 0, SignedSat((get_half_0(old_Rn) + get_half_1(old_Rm)), 16));
}

/* A4.1.56
 * REV */
void slv6_X_REV(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 31, 24, get_byte_0(old_Rm));
  set_field(addr_of_reg(proc,d), 23, 16, get_byte_1(old_Rm));
  set_field(addr_of_reg(proc,d), 15, 8, get_byte_2(old_Rm));
  set_field(addr_of_reg(proc,d), 7, 0, get_byte_3(old_Rm));
}

/* A4.1.57
 * REV16 */
void slv6_X_REV16(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 15, 8, get_byte_0(old_Rm));
  set_field(addr_of_reg(proc,d), 7, 0, get_byte_1(old_Rm));
  set_field(addr_of_reg(proc,d), 31, 24, get_byte_2(old_Rm));
  set_field(addr_of_reg(proc,d), 23, 16, get_byte_3(old_Rm));
}

/* A4.1.58
 * REVSH */
void slv6_X_REVSH(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 15, 8, get_byte_0(old_Rm));
  set_field(addr_of_reg(proc,d), 7, 0, get_byte_1(old_Rm));
  if ((get_bit(old_Rm,7) == 1))
    set_field(addr_of_reg(proc,d), 31, 16, 0xFFFF);
  else
    set_field(addr_of_reg(proc,d), 31, 16, 0x0000);
}

/* A4.1.59--A5.4.2
 * RFE -- Load and Store Multiple - Increment after */
void slv6_X_RFE_M4_IA(struct SLv6_Processor *proc,
    const bool W,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t end_address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t start_address;
  uint32_t value;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  start_address = old_Rn;
  end_address = ((old_Rn + (4 * 2)) - 4);
  if ((W == 1))
    new_Rn = (old_Rn + (4 * 2));
  address = start_address;
  value = slv6_read_word(proc->mmu_ptr,address);
  if (InAPrivilegedMode(proc))
    set_cpsr_bin(proc, slv6_read_word(proc->mmu_ptr,(address + 4)));
  else
    unpredictable("RFE_M4_IA");
  set_pc_raw_ws(proc,value,4);
  if ((W == 1))
    set_reg(proc,n,new_Rn);
}

/* A4.1.59--A5.4.3
 * RFE -- Load and Store Multiple - Increment before */
void slv6_X_RFE_M4_IB(struct SLv6_Processor *proc,
    const bool W,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t end_address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t start_address;
  uint32_t value;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  start_address = (old_Rn + 4);
  end_address = (old_Rn + (4 * 2));
  if ((W == 1))
    new_Rn = (old_Rn + (4 * 2));
  address = start_address;
  value = slv6_read_word(proc->mmu_ptr,address);
  if (InAPrivilegedMode(proc))
    set_cpsr_bin(proc, slv6_read_word(proc->mmu_ptr,(address + 4)));
  else
    unpredictable("RFE_M4_IB");
  set_pc_raw_ws(proc,value,4);
  if ((W == 1))
    set_reg(proc,n,new_Rn);
}

/* A4.1.59--A5.4.4
 * RFE -- Load and Store Multiple - Decrement after */
void slv6_X_RFE_M4_DA(struct SLv6_Processor *proc,
    const bool W,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t end_address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t start_address;
  uint32_t value;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  start_address = ((old_Rn - (4 * 2)) + 4);
  end_address = old_Rn;
  if ((W == 1))
    new_Rn = (old_Rn - (4 * 2));
  address = start_address;
  value = slv6_read_word(proc->mmu_ptr,address);
  if (InAPrivilegedMode(proc))
    set_cpsr_bin(proc, slv6_read_word(proc->mmu_ptr,(address + 4)));
  else
    unpredictable("RFE_M4_DA");
  set_pc_raw_ws(proc,value,4);
  if ((W == 1))
    set_reg(proc,n,new_Rn);
}

/* A4.1.59--A5.4.5
 * RFE -- Load and Store Multiple - Decrement before */
void slv6_X_RFE_M4_DB(struct SLv6_Processor *proc,
    const bool W,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t end_address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t start_address;
  uint32_t value;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  start_address = (old_Rn - (4 * 2));
  end_address = (old_Rn - 4);
  if ((W == 1))
    new_Rn = (old_Rn - (4 * 2));
  address = start_address;
  value = slv6_read_word(proc->mmu_ptr,address);
  if (InAPrivilegedMode(proc))
    set_cpsr_bin(proc, slv6_read_word(proc->mmu_ptr,(address + 4)));
  else
    unpredictable("RFE_M4_DB");
  set_pc_raw_ws(proc,value,4);
  if ((W == 1))
    set_reg(proc,n,new_Rn);
}

/* A4.1.60--A5.1.6
 * RSB -- Data processing operands - Logical shift left by register */
void slv6_X_RSB_M1_LSLReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm << get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(32 - get_byte_0(old_Rs))): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,0): 0)));
  set_reg(proc,d,(shifter_operand - old_Rn));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSB_M1_LSLReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub2(shifter_operand, old_Rn));
      proc->cpsr.V_flag = OverflowFrom_sub2(shifter_operand, old_Rn);
    }
  }
}

/* A4.1.60--A5.1.7
 * RSB -- Data processing operands - Logical shift right by immediate */
void slv6_X_RSB_M1_LSRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(shifter_operand - old_Rn),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSB_M1_LSRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub2(shifter_operand, old_Rn));
      proc->cpsr.V_flag = OverflowFrom_sub2(shifter_operand, old_Rn);
    }
  }
}

/* A4.1.60--A5.1.8
 * RSB -- Data processing operands - Logical shift right by register */
void slv6_X_RSB_M1_LSRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm >> get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,31): 0)));
  set_reg(proc,d,(shifter_operand - old_Rn));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSB_M1_LSRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub2(shifter_operand, old_Rn));
      proc->cpsr.V_flag = OverflowFrom_sub2(shifter_operand, old_Rn);
    }
  }
}

/* A4.1.60--A5.1.10
 * RSB -- Data processing operands - Arithmetic shift right by register */
void slv6_X_RSB_M1_ASRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? asr(old_Rm, get_byte_0(old_Rs)): ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF)));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): get_bit(old_Rm,31)));
  set_reg(proc,d,(shifter_operand - old_Rn));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSB_M1_ASRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub2(shifter_operand, old_Rn));
      proc->cpsr.V_flag = OverflowFrom_sub2(shifter_operand, old_Rn);
    }
  }
}

/* A4.1.60--A5.1.11
 * RSB -- Data processing operands - Rotate right by immediate */
void slv6_X_RSB_M1_RRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,0): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(shifter_operand - old_Rn),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSB_M1_RRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub2(shifter_operand, old_Rn));
      proc->cpsr.V_flag = OverflowFrom_sub2(shifter_operand, old_Rn);
    }
  }
}

/* A4.1.60--A5.1.12
 * RSB -- Data processing operands - Rotate right by register */
void slv6_X_RSB_M1_RRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_bits(old_Rs,4,0) == 0)? old_Rm: rotate_right(old_Rm, get_bits(old_Rs,4,0))));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_bits(old_Rs,4,0) == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(get_bits(old_Rs,4,0) - 1))));
  set_reg(proc,d,(shifter_operand - old_Rn));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSB_M1_RRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub2(shifter_operand, old_Rn));
      proc->cpsr.V_flag = OverflowFrom_sub2(shifter_operand, old_Rn);
    }
  }
}

/* A4.1.60--A5.1.13
 * RSB -- Data processing operands - Rotate right with extend */
void slv6_X_RSB_M1_RRE(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((proc->cpsr.C_flag << 31) | (old_Rm >> 1));
  shifter_carry_out = get_bit(old_Rm,0);
  set_reg_or_pc_ws(proc,d,(shifter_operand - old_Rn),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSB_M1_RRE");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub2(shifter_operand, old_Rn));
      proc->cpsr.V_flag = OverflowFrom_sub2(shifter_operand, old_Rn);
    }
  }
}

/* A4.1.61--A5.1.3
 * RSC -- Data processing operands - Immediate */
void slv6_X_RSC_M1_Imm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,((shifter_operand - old_Rn) - !(proc->cpsr.C_flag)),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSC_M1_Imm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub3(shifter_operand, old_Rn, !(proc->cpsr.C_flag)));
      proc->cpsr.V_flag = OverflowFrom_sub3(shifter_operand, old_Rn, !(proc->cpsr.C_flag));
    }
  }
}

/* A4.1.61--A5.1.4
 * RSC -- Data processing operands - Register */
void slv6_X_RSC_M1_Reg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = old_Rm;
  shifter_carry_out = proc->cpsr.C_flag;
  set_reg_or_pc_ws(proc,d,((shifter_operand - old_Rn) - !(proc->cpsr.C_flag)),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSC_M1_Reg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub3(shifter_operand, old_Rn, !(proc->cpsr.C_flag)));
      proc->cpsr.V_flag = OverflowFrom_sub3(shifter_operand, old_Rn, !(proc->cpsr.C_flag));
    }
  }
}

/* A4.1.61--A5.1.5
 * RSC -- Data processing operands - Logical shift left by immediate */
void slv6_X_RSC_M1_LSLImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? old_Rm: (old_Rm << shift_imm));
  shifter_carry_out = ((shift_imm == 0)? proc->cpsr.C_flag: get_bit(old_Rm,(32 - shift_imm)));
  set_reg_or_pc_ws(proc,d,((shifter_operand - old_Rn) - !(proc->cpsr.C_flag)),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSC_M1_LSLImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub3(shifter_operand, old_Rn, !(proc->cpsr.C_flag)));
      proc->cpsr.V_flag = OverflowFrom_sub3(shifter_operand, old_Rn, !(proc->cpsr.C_flag));
    }
  }
}

/* A4.1.61--A5.1.6
 * RSC -- Data processing operands - Logical shift left by register */
void slv6_X_RSC_M1_LSLReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm << get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(32 - get_byte_0(old_Rs))): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,0): 0)));
  set_reg(proc,d,((shifter_operand - old_Rn) - !(proc->cpsr.C_flag)));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSC_M1_LSLReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub3(shifter_operand, old_Rn, !(proc->cpsr.C_flag)));
      proc->cpsr.V_flag = OverflowFrom_sub3(shifter_operand, old_Rn, !(proc->cpsr.C_flag));
    }
  }
}

/* A4.1.61--A5.1.7
 * RSC -- Data processing operands - Logical shift right by immediate */
void slv6_X_RSC_M1_LSRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,((shifter_operand - old_Rn) - !(proc->cpsr.C_flag)),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSC_M1_LSRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub3(shifter_operand, old_Rn, !(proc->cpsr.C_flag)));
      proc->cpsr.V_flag = OverflowFrom_sub3(shifter_operand, old_Rn, !(proc->cpsr.C_flag));
    }
  }
}

/* A4.1.61--A5.1.8
 * RSC -- Data processing operands - Logical shift right by register */
void slv6_X_RSC_M1_LSRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm >> get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,31): 0)));
  set_reg(proc,d,((shifter_operand - old_Rn) - !(proc->cpsr.C_flag)));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSC_M1_LSRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub3(shifter_operand, old_Rn, !(proc->cpsr.C_flag)));
      proc->cpsr.V_flag = OverflowFrom_sub3(shifter_operand, old_Rn, !(proc->cpsr.C_flag));
    }
  }
}

/* A4.1.61--A5.1.9
 * RSC -- Data processing operands - Arithmetic shift right by immediate */
void slv6_X_RSC_M1_ASRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF): asr(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,((shifter_operand - old_Rn) - !(proc->cpsr.C_flag)),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSC_M1_ASRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub3(shifter_operand, old_Rn, !(proc->cpsr.C_flag)));
      proc->cpsr.V_flag = OverflowFrom_sub3(shifter_operand, old_Rn, !(proc->cpsr.C_flag));
    }
  }
}

/* A4.1.61--A5.1.10
 * RSC -- Data processing operands - Arithmetic shift right by register */
void slv6_X_RSC_M1_ASRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? asr(old_Rm, get_byte_0(old_Rs)): ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF)));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): get_bit(old_Rm,31)));
  set_reg(proc,d,((shifter_operand - old_Rn) - !(proc->cpsr.C_flag)));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSC_M1_ASRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub3(shifter_operand, old_Rn, !(proc->cpsr.C_flag)));
      proc->cpsr.V_flag = OverflowFrom_sub3(shifter_operand, old_Rn, !(proc->cpsr.C_flag));
    }
  }
}

/* A4.1.61--A5.1.11
 * RSC -- Data processing operands - Rotate right by immediate */
void slv6_X_RSC_M1_RRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,0): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,((shifter_operand - old_Rn) - !(proc->cpsr.C_flag)),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSC_M1_RRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub3(shifter_operand, old_Rn, !(proc->cpsr.C_flag)));
      proc->cpsr.V_flag = OverflowFrom_sub3(shifter_operand, old_Rn, !(proc->cpsr.C_flag));
    }
  }
}

/* A4.1.61--A5.1.12
 * RSC -- Data processing operands - Rotate right by register */
void slv6_X_RSC_M1_RRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_bits(old_Rs,4,0) == 0)? old_Rm: rotate_right(old_Rm, get_bits(old_Rs,4,0))));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_bits(old_Rs,4,0) == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(get_bits(old_Rs,4,0) - 1))));
  set_reg(proc,d,((shifter_operand - old_Rn) - !(proc->cpsr.C_flag)));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSC_M1_RRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub3(shifter_operand, old_Rn, !(proc->cpsr.C_flag)));
      proc->cpsr.V_flag = OverflowFrom_sub3(shifter_operand, old_Rn, !(proc->cpsr.C_flag));
    }
  }
}

/* A4.1.61--A5.1.13
 * RSC -- Data processing operands - Rotate right with extend */
void slv6_X_RSC_M1_RRE(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((proc->cpsr.C_flag << 31) | (old_Rm >> 1));
  shifter_carry_out = get_bit(old_Rm,0);
  set_reg_or_pc_ws(proc,d,((shifter_operand - old_Rn) - !(proc->cpsr.C_flag)),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSC_M1_RRE");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub3(shifter_operand, old_Rn, !(proc->cpsr.C_flag)));
      proc->cpsr.V_flag = OverflowFrom_sub3(shifter_operand, old_Rn, !(proc->cpsr.C_flag));
    }
  }
}

/* A4.1.62
 * SADD16 */
void slv6_X_SADD16(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t sum;
  sum = (get_half_0(old_Rn) + get_half_0(old_Rm));
  set_field(addr_of_reg(proc,d), 15, 0, get_half_0(sum));
  set_GE_10(&proc->cpsr,((to_int32(sum) >= 0)? 3: 0));
  sum = (get_half_1(old_Rn) + get_half_1(old_Rm));
  set_field(addr_of_reg(proc,d), 31, 16, get_half_0(sum));
  set_GE_32(&proc->cpsr,((to_int32(sum) >= 0)? 3: 0));
}

/* A4.1.63
 * SADD8 */
void slv6_X_SADD8(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t sum;
  sum = (get_byte_0(old_Rn) + get_byte_0(old_Rm));
  set_field(addr_of_reg(proc,d), 7, 0, get_byte_0(sum));
  proc->cpsr.GE0 = ((to_int32(sum) >= 0)? 1: 0);
  sum = (get_byte_1(old_Rn) + get_byte_1(old_Rm));
  set_field(addr_of_reg(proc,d), 15, 8, get_byte_0(sum));
  proc->cpsr.GE1 = ((to_int32(sum) >= 0)? 1: 0);
  sum = (get_byte_2(old_Rn) + get_byte_2(old_Rm));
  set_field(addr_of_reg(proc,d), 23, 16, get_byte_0(sum));
  proc->cpsr.GE2 = ((to_int32(sum) >= 0)? 1: 0);
  sum = (get_byte_3(old_Rn) + get_byte_3(old_Rm));
  set_field(addr_of_reg(proc,d), 31, 24, get_byte_0(sum));
  proc->cpsr.GE3 = ((to_int32(sum) >= 0)? 1: 0);
}

/* A4.1.64
 * SADDSUBX */
void slv6_X_SADDSUBX(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t diff;
  uint32_t sum;
  sum = (get_half_1(old_Rn) + get_half_0(old_Rm));
  set_field(addr_of_reg(proc,d), 31, 16, get_half_0(sum));
  set_GE_32(&proc->cpsr,((to_int32(sum) >= 0)? 3: 0));
  diff = (get_half_0(old_Rn) - get_half_1(old_Rm));
  set_field(addr_of_reg(proc,d), 15, 0, get_half_0(diff));
  set_GE_10(&proc->cpsr,((to_int32(diff) >= 0)? 3: 0));
}

/* A4.1.65--A5.1.3
 * SBC -- Data processing operands - Immediate */
void slv6_X_SBC_M1_Imm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,((old_Rn - shifter_operand) - !(proc->cpsr.C_flag)),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SBC_M1_Imm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub3(old_Rn, shifter_operand, !(proc->cpsr.C_flag)));
      proc->cpsr.V_flag = OverflowFrom_sub3(old_Rn, shifter_operand, !(proc->cpsr.C_flag));
    }
  }
}

/* A4.1.65--A5.1.4
 * SBC -- Data processing operands - Register */
void slv6_X_SBC_M1_Reg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = old_Rm;
  shifter_carry_out = proc->cpsr.C_flag;
  set_reg_or_pc_ws(proc,d,((old_Rn - shifter_operand) - !(proc->cpsr.C_flag)),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SBC_M1_Reg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub3(old_Rn, shifter_operand, !(proc->cpsr.C_flag)));
      proc->cpsr.V_flag = OverflowFrom_sub3(old_Rn, shifter_operand, !(proc->cpsr.C_flag));
    }
  }
}

/* A4.1.65--A5.1.5
 * SBC -- Data processing operands - Logical shift left by immediate */
void slv6_X_SBC_M1_LSLImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? old_Rm: (old_Rm << shift_imm));
  shifter_carry_out = ((shift_imm == 0)? proc->cpsr.C_flag: get_bit(old_Rm,(32 - shift_imm)));
  set_reg_or_pc_ws(proc,d,((old_Rn - shifter_operand) - !(proc->cpsr.C_flag)),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SBC_M1_LSLImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub3(old_Rn, shifter_operand, !(proc->cpsr.C_flag)));
      proc->cpsr.V_flag = OverflowFrom_sub3(old_Rn, shifter_operand, !(proc->cpsr.C_flag));
    }
  }
}

/* A4.1.65--A5.1.6
 * SBC -- Data processing operands - Logical shift left by register */
void slv6_X_SBC_M1_LSLReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm << get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(32 - get_byte_0(old_Rs))): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,0): 0)));
  set_reg(proc,d,((old_Rn - shifter_operand) - !(proc->cpsr.C_flag)));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SBC_M1_LSLReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub3(old_Rn, shifter_operand, !(proc->cpsr.C_flag)));
      proc->cpsr.V_flag = OverflowFrom_sub3(old_Rn, shifter_operand, !(proc->cpsr.C_flag));
    }
  }
}

/* A4.1.65--A5.1.7
 * SBC -- Data processing operands - Logical shift right by immediate */
void slv6_X_SBC_M1_LSRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,((old_Rn - shifter_operand) - !(proc->cpsr.C_flag)),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SBC_M1_LSRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub3(old_Rn, shifter_operand, !(proc->cpsr.C_flag)));
      proc->cpsr.V_flag = OverflowFrom_sub3(old_Rn, shifter_operand, !(proc->cpsr.C_flag));
    }
  }
}

/* A4.1.65--A5.1.8
 * SBC -- Data processing operands - Logical shift right by register */
void slv6_X_SBC_M1_LSRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm >> get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,31): 0)));
  set_reg(proc,d,((old_Rn - shifter_operand) - !(proc->cpsr.C_flag)));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SBC_M1_LSRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub3(old_Rn, shifter_operand, !(proc->cpsr.C_flag)));
      proc->cpsr.V_flag = OverflowFrom_sub3(old_Rn, shifter_operand, !(proc->cpsr.C_flag));
    }
  }
}

/* A4.1.65--A5.1.9
 * SBC -- Data processing operands - Arithmetic shift right by immediate */
void slv6_X_SBC_M1_ASRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF): asr(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,((old_Rn - shifter_operand) - !(proc->cpsr.C_flag)),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SBC_M1_ASRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub3(old_Rn, shifter_operand, !(proc->cpsr.C_flag)));
      proc->cpsr.V_flag = OverflowFrom_sub3(old_Rn, shifter_operand, !(proc->cpsr.C_flag));
    }
  }
}

/* A4.1.65--A5.1.10
 * SBC -- Data processing operands - Arithmetic shift right by register */
void slv6_X_SBC_M1_ASRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? asr(old_Rm, get_byte_0(old_Rs)): ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF)));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): get_bit(old_Rm,31)));
  set_reg(proc,d,((old_Rn - shifter_operand) - !(proc->cpsr.C_flag)));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SBC_M1_ASRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub3(old_Rn, shifter_operand, !(proc->cpsr.C_flag)));
      proc->cpsr.V_flag = OverflowFrom_sub3(old_Rn, shifter_operand, !(proc->cpsr.C_flag));
    }
  }
}

/* A4.1.65--A5.1.11
 * SBC -- Data processing operands - Rotate right by immediate */
void slv6_X_SBC_M1_RRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,0): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,((old_Rn - shifter_operand) - !(proc->cpsr.C_flag)),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SBC_M1_RRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub3(old_Rn, shifter_operand, !(proc->cpsr.C_flag)));
      proc->cpsr.V_flag = OverflowFrom_sub3(old_Rn, shifter_operand, !(proc->cpsr.C_flag));
    }
  }
}

/* A4.1.65--A5.1.12
 * SBC -- Data processing operands - Rotate right by register */
void slv6_X_SBC_M1_RRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_bits(old_Rs,4,0) == 0)? old_Rm: rotate_right(old_Rm, get_bits(old_Rs,4,0))));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_bits(old_Rs,4,0) == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(get_bits(old_Rs,4,0) - 1))));
  set_reg(proc,d,((old_Rn - shifter_operand) - !(proc->cpsr.C_flag)));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SBC_M1_RRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub3(old_Rn, shifter_operand, !(proc->cpsr.C_flag)));
      proc->cpsr.V_flag = OverflowFrom_sub3(old_Rn, shifter_operand, !(proc->cpsr.C_flag));
    }
  }
}

/* A4.1.65--A5.1.13
 * SBC -- Data processing operands - Rotate right with extend */
void slv6_X_SBC_M1_RRE(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((proc->cpsr.C_flag << 31) | (old_Rm >> 1));
  shifter_carry_out = get_bit(old_Rm,0);
  set_reg_or_pc_ws(proc,d,((old_Rn - shifter_operand) - !(proc->cpsr.C_flag)),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SBC_M1_RRE");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub3(old_Rn, shifter_operand, !(proc->cpsr.C_flag)));
      proc->cpsr.V_flag = OverflowFrom_sub3(old_Rn, shifter_operand, !(proc->cpsr.C_flag));
    }
  }
}

/* A4.1.66
 * SEL */
void slv6_X_SEL(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 7, 0, ((proc->cpsr.GE0 == 1)? get_byte_0(old_Rn): get_byte_0(old_Rm)));
  set_field(addr_of_reg(proc,d), 15, 8, ((proc->cpsr.GE1 == 1)? get_byte_1(old_Rn): get_byte_1(old_Rm)));
  set_field(addr_of_reg(proc,d), 23, 16, ((proc->cpsr.GE2 == 1)? get_byte_2(old_Rn): get_byte_2(old_Rm)));
  set_field(addr_of_reg(proc,d), 31, 24, ((proc->cpsr.GE3 == 1)? get_byte_3(old_Rn): get_byte_3(old_Rm)));
}

/* A4.1.67
 * SETEND */
void slv6_X_SETEND(struct SLv6_Processor *proc,
    const bool E)
{
  proc->cpsr.E_flag = E;
}

/* A4.1.68
 * SHADD16 */
void slv6_X_SHADD16(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t sum;
  sum = (get_half_0(old_Rn) + get_half_0(old_Rm));
  set_field(addr_of_reg(proc,d), 15, 0, get_bits(sum,16,1));
  sum = (get_half_1(old_Rn) + get_half_1(old_Rm));
  set_field(addr_of_reg(proc,d), 31, 16, get_bits(sum,16,1));
}

/* A4.1.69
 * SHADD8 */
void slv6_X_SHADD8(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t sum;
  sum = (get_byte_0(old_Rn) + get_byte_0(old_Rm));
  set_field(addr_of_reg(proc,d), 7, 0, get_bits(sum,8,1));
  sum = (get_byte_1(old_Rn) + get_byte_1(old_Rm));
  set_field(addr_of_reg(proc,d), 15, 8, get_bits(sum,8,1));
  sum = (get_byte_2(old_Rn) + get_byte_2(old_Rm));
  set_field(addr_of_reg(proc,d), 23, 16, get_bits(sum,8,1));
  sum = (get_byte_3(old_Rn) + get_byte_3(old_Rm));
  set_field(addr_of_reg(proc,d), 31, 24, get_bits(sum,8,1));
}

/* A4.1.70
 * SHADDSUBX */
void slv6_X_SHADDSUBX(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t diff;
  uint32_t sum;
  sum = (get_half_1(old_Rn) + get_half_0(old_Rm));
  set_field(addr_of_reg(proc,d), 31, 16, get_bits(sum,16,1));
  diff = (get_half_0(old_Rn) - get_half_1(old_Rm));
  set_field(addr_of_reg(proc,d), 15, 0, get_bits(diff,16,1));
}

/* A4.1.71
 * SHSUB16 */
void slv6_X_SHSUB16(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t diff;
  diff = (get_half_0(old_Rn) - get_half_0(old_Rm));
  set_field(addr_of_reg(proc,d), 15, 0, get_bits(diff,16,1));
  diff = (get_half_1(old_Rn) - get_half_1(old_Rm));
  set_field(addr_of_reg(proc,d), 31, 16, get_bits(diff,16,1));
}

/* A4.1.72
 * SHSUB8 */
void slv6_X_SHSUB8(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t diff;
  diff = (get_byte_0(old_Rn) - get_byte_0(old_Rm));
  set_field(addr_of_reg(proc,d), 7, 0, get_bits(diff,8,1));
  diff = (get_byte_1(old_Rn) - get_byte_1(old_Rm));
  set_field(addr_of_reg(proc,d), 15, 8, get_bits(diff,8,1));
  diff = (get_byte_2(old_Rn) - get_byte_2(old_Rm));
  set_field(addr_of_reg(proc,d), 23, 16, get_bits(diff,8,1));
  diff = (get_byte_3(old_Rn) - get_byte_3(old_Rm));
  set_field(addr_of_reg(proc,d), 31, 24, get_bits(diff,8,1));
}

/* A4.1.73
 * SHSUBADDX */
void slv6_X_SHSUBADDX(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t diff;
  uint32_t sum;
  diff = (get_half_1(old_Rn) - get_half_0(old_Rm));
  set_field(addr_of_reg(proc,d), 31, 16, get_bits(diff,16,1));
  sum = (get_half_0(old_Rn) + get_half_1(old_Rm));
  set_field(addr_of_reg(proc,d), 15, 0, get_bits(sum,16,1));
}

/* A4.1.74
 * SMLA<x><y> */
void slv6_X_SMLAxy(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const bool x,
    const bool y,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t operand1;
  uint32_t operand2;
  operand1 = ((x == 0)? SignExtend16(get_half_0(old_Rm)): SignExtend16(get_half_1(old_Rm)));
  operand2 = ((y == 0)? SignExtend16(get_half_0(old_Rs)): SignExtend16(get_half_1(old_Rs)));
  set_reg(proc,d,((to_i64(operand1) * to_i64(operand2)) + old_Rn));
  if (OverflowFrom_add2((to_i64(operand1) * to_i64(operand2)), old_Rn))
    proc->cpsr.Q_flag = 1;
}

/* A4.1.75
 * SMLAD */
void slv6_X_SMLAD(struct SLv6_Processor *proc,
    const bool X,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t operand2;
  uint32_t product1;
  uint32_t product2;
  operand2 = ((X == 1)? rotate_right(old_Rs, 16): old_Rs);
  product1 = (to_i64(get_half_0(old_Rm)) * to_i64(get_half_0(operand2)));
  product2 = (to_i64(get_half_1(old_Rm)) * to_i64(get_half_1(operand2)));
  set_reg(proc,d,((old_Rn + product1) + product2));
  if (OverflowFrom_add3(old_Rn, product1, product2))
    proc->cpsr.Q_flag = 1;
}

/* A4.1.76
 * SMLAL */
void slv6_X_SMLAL(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t dHi,
    const uint8_t dLo,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  const uint32_t old_RdLo = reg(proc,dLo);
  set_reg(proc,dLo,(get_bits((to_i64(old_Rm) * to_i64(old_Rs)),31,0) + old_RdLo));
  set_reg(proc,dHi,((get_bits((to_i64(old_Rm) * to_i64(old_Rs)),63,32) + reg(proc,dHi)) + CarryFrom_add2(get_bits((to_i64(old_Rm) * to_i64(old_Rs)),31,0), old_RdLo)));
  if ((S == 1)) {
    proc->cpsr.N_flag = get_bit(reg(proc,dHi),31);
    proc->cpsr.Z_flag = (((reg(proc,dHi) == 0) && (old_RdLo == 0))? 1: 0);
  }
}

/* A4.1.77
 * SMLAL<x><y> */
void slv6_X_SMLALxy(struct SLv6_Processor *proc,
    const uint8_t dHi,
    const uint8_t dLo,
    const uint8_t m,
    const uint8_t s,
    const bool x,
    const bool y,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  const uint32_t old_RdLo = reg(proc,dLo);
  uint32_t operand1;
  uint32_t operand2;
  operand1 = ((x == 0)? SignExtend16(get_half_0(old_Rm)): SignExtend16(get_half_1(old_Rm)));
  operand2 = ((y == 0)? SignExtend16(get_half_0(old_Rs)): SignExtend16(get_half_1(old_Rs)));
  set_reg(proc,dLo,(old_RdLo + (to_i64(operand1) * to_i64(operand2))));
  set_reg(proc,dHi,((reg(proc,dHi) + ((to_int64((to_i64(operand1) * to_i64(operand2))) < 0)? 0xFFFFFFFF: 0)) + CarryFrom_add2(old_RdLo, (to_i64(operand1) * to_i64(operand2)))));
}

/* A4.1.78
 * SMLALD */
void slv6_X_SMLALD(struct SLv6_Processor *proc,
    const bool X,
    const uint8_t dHi,
    const uint8_t dLo,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  const uint32_t old_RdLo = reg(proc,dLo);
  uint64_t accvalue;
  uint32_t operand2;
  uint32_t product1;
  uint32_t product2;
  uint64_t result;
  operand2 = ((X == 1)? rotate_right(old_Rs, 16): old_Rs);
  accvalue = ((to_u64(ZeroExtend(reg(proc,dHi))) << 32) | ZeroExtend(old_RdLo));
  product1 = (to_i64(get_half_0(old_Rm)) * to_i64(get_half_0(operand2)));
  product2 = (to_i64(get_half_1(old_Rm)) * to_i64(get_half_1(operand2)));
  result = ((accvalue + product1) + product2);
  set_reg(proc,dLo,get_bits(result,31,0));
  set_reg(proc,dHi,get_bits(result,63,32));
}

/* A4.1.79
 * SMLAW<y> */
void slv6_X_SMLAWy(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const bool y,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t operand2;
  operand2 = ((y == 0)? SignExtend16(get_half_0(old_Rs)): SignExtend16(get_half_1(old_Rs)));
  set_reg(proc,d,(get_bits((to_i64(old_Rm) * to_i64(operand2)),47,16) + old_Rn));
  if (OverflowFrom_add2(get_bits((to_i64(old_Rm) * to_i64(operand2)),47,16), old_Rn))
    proc->cpsr.Q_flag = 1;
}

/* A4.1.80
 * SMLSD */
void slv6_X_SMLSD(struct SLv6_Processor *proc,
    const bool X,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t diffofproducts;
  uint32_t operand2;
  uint32_t product1;
  uint32_t product2;
  operand2 = ((X == 1)? rotate_right(old_Rs, 16): old_Rs);
  product1 = (to_i64(get_half_0(old_Rm)) * to_i64(get_half_0(operand2)));
  product2 = (to_i64(get_half_1(old_Rm)) * to_i64(get_half_1(operand2)));
  diffofproducts = (product1 - product2);
  set_reg(proc,d,(old_Rn + diffofproducts));
  if (OverflowFrom_add2(old_Rn, diffofproducts))
    proc->cpsr.Q_flag = 1;
}

/* A4.1.81
 * SMLSLD */
void slv6_X_SMLSLD(struct SLv6_Processor *proc,
    const bool X,
    const uint8_t dHi,
    const uint8_t dLo,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  const uint32_t old_RdLo = reg(proc,dLo);
  uint64_t accvalue;
  uint32_t operand2;
  uint32_t product1;
  uint32_t product2;
  uint64_t result;
  operand2 = ((X == 1)? rotate_right(old_Rs, 16): old_Rs);
  accvalue = ((to_u64(ZeroExtend(reg(proc,dHi))) << 32) | ZeroExtend(old_RdLo));
  product1 = (to_i64(get_half_0(old_Rm)) * to_i64(get_half_0(operand2)));
  product2 = (to_i64(get_half_1(old_Rm)) * to_i64(get_half_1(operand2)));
  result = ((accvalue + product1) - product2);
  set_reg(proc,dLo,get_bits(result,31,0));
  set_reg(proc,dHi,get_bits(result,63,32));
}

/* A4.1.82
 * SMMLA */
void slv6_X_SMMLA(struct SLv6_Processor *proc,
    const bool R,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t value;
  value = (to_i64(old_Rm) * to_i64(old_Rs));
  if ((R == 1))
    set_reg(proc,d,get_bits((((to_u64(old_Rn) << 32) + value) + 0x80000000),63,32));
  else
    set_reg(proc,d,get_bits(((to_u64(old_Rn) << 32) + value),63,32));
}

/* A4.1.83
 * SMMLS */
void slv6_X_SMMLS(struct SLv6_Processor *proc,
    const bool R,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t value;
  value = (to_i64(old_Rm) * to_i64(old_Rs));
  if ((R == 1))
    set_reg(proc,d,get_bits((((to_u64(old_Rn) << 32) - value) + 0x80000000),63,32));
  else
    set_reg(proc,d,get_bits(((to_u64(old_Rn) << 32) - value),63,32));
}

/* A4.1.84
 * SMMUL */
void slv6_X_SMMUL(struct SLv6_Processor *proc,
    const bool R,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t value;
  value = ((R == 1)? ((to_i64(old_Rm) * to_i64(old_Rs)) + 0x80000000): (to_i64(old_Rm) * to_i64(old_Rs)));
  set_reg(proc,d,get_bits(value,63,32));
}

/* A4.1.85
 * SMUAD */
void slv6_X_SMUAD(struct SLv6_Processor *proc,
    const bool X,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t operand2;
  uint32_t product1;
  uint32_t product2;
  operand2 = ((X == 1)? rotate_right(old_Rs, 16): old_Rs);
  product1 = (to_i64(get_half_0(old_Rm)) * to_i64(get_half_0(operand2)));
  product2 = (to_i64(get_half_1(old_Rm)) * to_i64(get_half_1(operand2)));
  set_reg(proc,d,(product1 + product2));
  if (OverflowFrom_add2(product1, product2))
    proc->cpsr.Q_flag = 1;
}

/* A4.1.86
 * SMUL<x><y> */
void slv6_X_SMULxy(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const bool x,
    const bool y,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t operand1;
  uint32_t operand2;
  operand1 = ((x == 0)? SignExtend16(get_half_0(old_Rm)): SignExtend16(get_half_1(old_Rm)));
  operand2 = ((y == 0)? SignExtend16(get_half_0(old_Rs)): SignExtend16(get_half_1(old_Rs)));
  set_reg(proc,d,(to_i64(operand1) * to_i64(operand2)));
}

/* A4.1.88
 * SMULW<y> */
void slv6_X_SMULWy(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const bool y,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t operand2;
  operand2 = ((y == 0)? SignExtend16(get_half_0(old_Rs)): SignExtend16(get_half_1(old_Rs)));
  set_reg(proc,d,get_bits((to_i64(old_Rm) * to_i64(operand2)),47,16));
}

/* A4.1.89
 * SMUSD */
void slv6_X_SMUSD(struct SLv6_Processor *proc,
    const bool X,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t operand2;
  uint32_t product1;
  uint32_t product2;
  operand2 = ((X == 1)? rotate_right(old_Rs, 16): old_Rs);
  product1 = (to_i64(get_half_0(old_Rm)) * to_i64(get_half_0(operand2)));
  product2 = (to_i64(get_half_1(old_Rm)) * to_i64(get_half_1(operand2)));
  set_reg(proc,d,(product1 - product2));
}

/* A4.1.90--A5.4.2
 * SRS -- Load and Store Multiple - Increment after */
void slv6_X_SRS_M4_IA(struct SLv6_Processor *proc,
    const bool W,
    const SLv6_Mode mode)
{
  uint32_t address;
  uint32_t end_address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  uint32_t start_address;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  start_address = reg_m(proc, 13, mode);
  end_address = ((reg_m(proc, 13, mode) + (4 * 2)) - 4);
  if ((W == 1))
    new_Rn = (reg_m(proc, 13, mode) + (4 * 2));
  processor_id = ExecutingProcessor();
  address = start_address;
  slv6_write_word(proc->mmu_ptr, address, reg(proc,14));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  if (CurrentModeHasSPSR(proc)) {
    slv6_write_word(proc->mmu_ptr, (address + 4), StatusRegister_to_uint32(spsr(proc)));
    if (Shared((address + 4))) {
      physical_address = slv6_TLB((address + 4));
      ClearExclusiveByAddress3(physical_address, processor_id, 4);
    }
  } else
    unpredictable("SRS_M4_IA");
  if ((W == 1))
    set_reg_m(proc, 13, mode, new_Rn);
}

/* A4.1.90--A5.4.3
 * SRS -- Load and Store Multiple - Increment before */
void slv6_X_SRS_M4_IB(struct SLv6_Processor *proc,
    const bool W,
    const SLv6_Mode mode)
{
  uint32_t address;
  uint32_t end_address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  uint32_t start_address;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  start_address = (reg_m(proc, 13, mode) + 4);
  end_address = (reg_m(proc, 13, mode) + (4 * 2));
  if ((W == 1))
    new_Rn = (reg_m(proc, 13, mode) + (4 * 2));
  processor_id = ExecutingProcessor();
  address = start_address;
  slv6_write_word(proc->mmu_ptr, address, reg(proc,14));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  if (CurrentModeHasSPSR(proc)) {
    slv6_write_word(proc->mmu_ptr, (address + 4), StatusRegister_to_uint32(spsr(proc)));
    if (Shared((address + 4))) {
      physical_address = slv6_TLB((address + 4));
      ClearExclusiveByAddress3(physical_address, processor_id, 4);
    }
  } else
    unpredictable("SRS_M4_IB");
  if ((W == 1))
    set_reg_m(proc, 13, mode, new_Rn);
}

/* A4.1.90--A5.4.4
 * SRS -- Load and Store Multiple - Decrement after */
void slv6_X_SRS_M4_DA(struct SLv6_Processor *proc,
    const bool W,
    const SLv6_Mode mode)
{
  uint32_t address;
  uint32_t end_address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  uint32_t start_address;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  start_address = ((reg_m(proc, 13, mode) - (4 * 2)) + 4);
  end_address = reg_m(proc, 13, mode);
  if ((W == 1))
    new_Rn = (reg_m(proc, 13, mode) - (4 * 2));
  processor_id = ExecutingProcessor();
  address = start_address;
  slv6_write_word(proc->mmu_ptr, address, reg(proc,14));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  if (CurrentModeHasSPSR(proc)) {
    slv6_write_word(proc->mmu_ptr, (address + 4), StatusRegister_to_uint32(spsr(proc)));
    if (Shared((address + 4))) {
      physical_address = slv6_TLB((address + 4));
      ClearExclusiveByAddress3(physical_address, processor_id, 4);
    }
  } else
    unpredictable("SRS_M4_DA");
  if ((W == 1))
    set_reg_m(proc, 13, mode, new_Rn);
}

/* A4.1.90--A5.4.5
 * SRS -- Load and Store Multiple - Decrement before */
void slv6_X_SRS_M4_DB(struct SLv6_Processor *proc,
    const bool W,
    const SLv6_Mode mode)
{
  uint32_t address;
  uint32_t end_address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  uint32_t start_address;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  start_address = (reg_m(proc, 13, mode) - (4 * 2));
  end_address = (reg_m(proc, 13, mode) - 4);
  if ((W == 1))
    new_Rn = (reg_m(proc, 13, mode) - (4 * 2));
  processor_id = ExecutingProcessor();
  address = start_address;
  slv6_write_word(proc->mmu_ptr, address, reg(proc,14));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  if (CurrentModeHasSPSR(proc)) {
    slv6_write_word(proc->mmu_ptr, (address + 4), StatusRegister_to_uint32(spsr(proc)));
    if (Shared((address + 4))) {
      physical_address = slv6_TLB((address + 4));
      ClearExclusiveByAddress3(physical_address, processor_id, 4);
    }
  } else
    unpredictable("SRS_M4_DB");
  if ((W == 1))
    set_reg_m(proc, 13, mode, new_Rn);
}

/* A4.1.91
 * SSAT */
void slv6_X_SSAT(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t sat_imm,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  uint32_t operand;
  operand = ((shift == 1)? ((shift_imm == 0)? get_bits(asr(old_Rm, 32),31,0): get_bits(asr(old_Rm, shift_imm),31,0)): get_bits((old_Rm << shift_imm),31,0));
  set_reg(proc,d,SignedSat(operand, (sat_imm + 1)));
  if (SignedDoesSat(operand, (sat_imm + 1)))
    proc->cpsr.Q_flag = 1;
}

/* A4.1.92
 * SSAT16 */
void slv6_X_SSAT16(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t sat_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 15, 0, SignedSat(get_half_0(old_Rm), (sat_imm + 1)));
  set_field(addr_of_reg(proc,d), 31, 16, SignedSat(get_half_1(old_Rm), (sat_imm + 1)));
  if ((SignedDoesSat(get_half_0(old_Rm), (sat_imm + 1)) || SignedDoesSat(get_half_1(old_Rm), (sat_imm + 1))))
    proc->cpsr.Q_flag = 1;
}

/* A4.1.93
 * SSUB16 */
void slv6_X_SSUB16(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t diff;
  diff = (get_half_0(old_Rn) - get_half_0(old_Rm));
  set_field(addr_of_reg(proc,d), 15, 0, get_half_0(diff));
  set_GE_10(&proc->cpsr,((to_int32(diff) >= 0)? 3: 0));
  diff = (get_half_1(old_Rn) - get_half_1(old_Rm));
  set_field(addr_of_reg(proc,d), 31, 16, get_half_0(diff));
  set_GE_32(&proc->cpsr,((to_int32(diff) >= 0)? 3: 0));
}

/* A4.1.94
 * SSUB8 */
void slv6_X_SSUB8(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t diff;
  diff = (get_byte_0(old_Rn) - get_byte_0(old_Rm));
  set_field(addr_of_reg(proc,d), 7, 0, get_byte_0(diff));
  proc->cpsr.GE0 = ((to_int32(diff) >= 0)? 1: 0);
  diff = (get_byte_1(old_Rn) - get_byte_1(old_Rm));
  set_field(addr_of_reg(proc,d), 15, 8, get_byte_0(diff));
  proc->cpsr.GE1 = ((to_int32(diff) >= 0)? 1: 0);
  diff = (get_byte_2(old_Rn) - get_byte_2(old_Rm));
  set_field(addr_of_reg(proc,d), 23, 16, get_byte_0(diff));
  proc->cpsr.GE2 = ((to_int32(diff) >= 0)? 1: 0);
  diff = (get_byte_3(old_Rn) - get_byte_3(old_Rm));
  set_field(addr_of_reg(proc,d), 31, 24, get_byte_0(diff));
  proc->cpsr.GE3 = ((to_int32(diff) >= 0)? 1: 0);
}

/* A4.1.95
 * SSUBADDX */
void slv6_X_SSUBADDX(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t diff;
  uint32_t sum;
  diff = (get_half_1(old_Rn) - get_half_0(old_Rm));
  set_field(addr_of_reg(proc,d), 31, 16, get_half_0(diff));
  set_GE_32(&proc->cpsr,((to_int32(diff) >= 0)? 3: 0));
  sum = (get_half_0(old_Rn) + get_half_1(old_Rm));
  set_field(addr_of_reg(proc,d), 15, 0, get_half_0(sum));
  set_GE_10(&proc->cpsr,((to_int32(sum) >= 0)? 3: 0));
}

/* A4.1.96--A5.5.2
 * STC -- Load and Store Coprocessor - Immediate offset */
void slv6_X_STC_M5_ImmOff(struct SLv6_Processor *proc)
{
  exec_undefined_instruction(proc, NULL);
}

/* A4.1.96--A5.5.3
 * STC -- Load and Store Coprocessor - Immediate pre indexed */
void slv6_X_STC_M5_Imm_preInd(struct SLv6_Processor *proc)
{
  exec_undefined_instruction(proc, NULL);
}

/* A4.1.96--A5.5.4
 * STC -- Load and Store Coprocessor - Immediate post indexed */
void slv6_X_STC_M5_Imm_postInd(struct SLv6_Processor *proc)
{
  exec_undefined_instruction(proc, NULL);
}

/* A4.1.96--A5.5.5
 * STC -- Load and Store Coprocessor - Unindexed */
void slv6_X_STC_M5_U(struct SLv6_Processor *proc)
{
  exec_undefined_instruction(proc, NULL);
}

/* A4.1.97--A5.4.4
 * STM (1) -- Load and Store Multiple - Decrement after */
void slv6_X_STM1_M4_DA(struct SLv6_Processor *proc,
    const bool W,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t end_address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  uint32_t start_address;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  start_address = ((old_Rn - nb_reg_x4) + 4);
  end_address = old_Rn;
  if ((W == 1))
    new_Rn = (old_Rn - nb_reg_x4);
  processor_id = ExecutingProcessor();
  address = start_address;
  size_t i; for (i = 0; i<=15; ++i) {
    if ((get_bit(register_list,i) == 1)) {
      slv6_write_word(proc->mmu_ptr, address, reg(proc,i));
      address = (address + 4);
      if (Shared(address)) {
        physical_address = slv6_TLB(address);
        ClearExclusiveByAddress3(physical_address, processor_id, 4);
      }
    }
}
  if ((W == 1))
    set_reg(proc,n,new_Rn);
}

/* A4.1.98--A5.4.2
 * STM (2) -- Load and Store Multiple - Increment after */
void slv6_X_STM2_M4_IA(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t end_address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  uint32_t start_address;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  start_address = old_Rn;
  end_address = ((old_Rn + (Number_Of_Set_Bits_In(register_list) * 4)) - 4);
  if ((0 == 1))
    new_Rn = (old_Rn + (Number_Of_Set_Bits_In(register_list) * 4));
  processor_id = ExecutingProcessor();
  address = start_address;
  size_t i; for (i = 0; i<=15; ++i) {
    if ((get_bit(register_list,i) == 1)) {
      slv6_write_word(proc->mmu_ptr, address, reg_m(proc,i,usr));
      address = (address + 4);
      if (Shared(address)) {
        physical_address = slv6_TLB(address);
        ClearExclusiveByAddress3(physical_address, processor_id, 4);
      }
    }
}
}

/* A4.1.98--A5.4.3
 * STM (2) -- Load and Store Multiple - Increment before */
void slv6_X_STM2_M4_IB(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t end_address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  uint32_t start_address;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  start_address = (old_Rn + 4);
  end_address = (old_Rn + (Number_Of_Set_Bits_In(register_list) * 4));
  if ((0 == 1))
    new_Rn = (old_Rn + (Number_Of_Set_Bits_In(register_list) * 4));
  processor_id = ExecutingProcessor();
  address = start_address;
  size_t i; for (i = 0; i<=15; ++i) {
    if ((get_bit(register_list,i) == 1)) {
      slv6_write_word(proc->mmu_ptr, address, reg_m(proc,i,usr));
      address = (address + 4);
      if (Shared(address)) {
        physical_address = slv6_TLB(address);
        ClearExclusiveByAddress3(physical_address, processor_id, 4);
      }
    }
}
}

/* A4.1.98--A5.4.4
 * STM (2) -- Load and Store Multiple - Decrement after */
void slv6_X_STM2_M4_DA(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t end_address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  uint32_t start_address;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  start_address = ((old_Rn - (Number_Of_Set_Bits_In(register_list) * 4)) + 4);
  end_address = old_Rn;
  if ((0 == 1))
    new_Rn = (old_Rn - (Number_Of_Set_Bits_In(register_list) * 4));
  processor_id = ExecutingProcessor();
  address = start_address;
  size_t i; for (i = 0; i<=15; ++i) {
    if ((get_bit(register_list,i) == 1)) {
      slv6_write_word(proc->mmu_ptr, address, reg_m(proc,i,usr));
      address = (address + 4);
      if (Shared(address)) {
        physical_address = slv6_TLB(address);
        ClearExclusiveByAddress3(physical_address, processor_id, 4);
      }
    }
}
}

/* A4.1.98--A5.4.5
 * STM (2) -- Load and Store Multiple - Decrement before */
void slv6_X_STM2_M4_DB(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const SLv6_Condition cond,
    const uint32_t register_list)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t end_address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  uint32_t start_address;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  start_address = (old_Rn - (Number_Of_Set_Bits_In(register_list) * 4));
  end_address = (old_Rn - 4);
  if ((0 == 1))
    new_Rn = (old_Rn - (Number_Of_Set_Bits_In(register_list) * 4));
  processor_id = ExecutingProcessor();
  address = start_address;
  size_t i; for (i = 0; i<=15; ++i) {
    if ((get_bit(register_list,i) == 1)) {
      slv6_write_word(proc->mmu_ptr, address, reg_m(proc,i,usr));
      address = (address + 4);
      if (Shared(address)) {
        physical_address = slv6_TLB(address);
        ClearExclusiveByAddress3(physical_address, processor_id, 4);
      }
    }
}
}

/* A4.1.99--A5.2.6
 * STR -- Load and Store Word or Unsigned Byte - Register pre indexed */
void slv6_X_STR_M2_Reg_preInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = ((U == 1)? (old_Rn + old_Rm): (old_Rn - old_Rm));
  new_Rn = address;
  processor_id = ExecutingProcessor();
  slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.99--A5.2.7
 * STR -- Load and Store Word or Unsigned Byte - Scaled register pre indexed */
void slv6_X_STR_M2_ScReg_preInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t index;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  switch (shift) {
  case 0:
    index = (old_Rm << shift_imm);
    break;
  case 1:
    index = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
    break;
  case 2:
    index = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 1)? 0xFFFFFFFF: 0): asr(old_Rm, shift_imm));
    break;
  case 3:
    index = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
    break;
    default: abort();
  }
  address = ((U == 1)? (old_Rn + index): (old_Rn - index));
  new_Rn = address;
  processor_id = ExecutingProcessor();
  slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.99--A5.2.10
 * STR -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
void slv6_X_STR_M2_ScReg_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t index;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  switch (shift) {
  case 0:
    index = (old_Rm << shift_imm);
    break;
  case 1:
    index = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
    break;
  case 2:
    index = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 1)? 0xFFFFFFFF: 0): asr(old_Rm, shift_imm));
    break;
  case 3:
    index = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
    break;
    default: abort();
  }
  if ((U == 1))
    new_Rn = (old_Rn + index);
  else
    new_Rn = (old_Rn - index);
  processor_id = ExecutingProcessor();
  slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.100--A5.2.4
 * STRB -- Load and Store Word or Unsigned Byte - Scaled register offset */
void slv6_X_STRB_M2_ScRegOff(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t index;
  uint32_t physical_address;
  uint32_t processor_id;
  switch (shift) {
  case 0:
    index = (old_Rm << shift_imm);
    break;
  case 1:
    index = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
    break;
  case 2:
    index = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 1)? 0xFFFFFFFF: 0): asr(old_Rm, shift_imm));
    break;
  case 3:
    index = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
    break;
    default: abort();
  }
  address = ((U == 1)? (old_Rn + index): (old_Rn - index));
  processor_id = ExecutingProcessor();
  slv6_write_byte(proc->mmu_ptr, address, get_byte_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 1);
  }
}

/* A4.1.100--A5.2.5
 * STRB -- Load and Store Word or Unsigned Byte - Immediate pre indexed */
void slv6_X_STRB_M2_Imm_preInd(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = (old_Rn + signed_offset_12);
  new_Rn = address;
  processor_id = ExecutingProcessor();
  slv6_write_byte(proc->mmu_ptr, address, get_byte_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 1);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.100--A5.2.6
 * STRB -- Load and Store Word or Unsigned Byte - Register pre indexed */
void slv6_X_STRB_M2_Reg_preInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = ((U == 1)? (old_Rn + old_Rm): (old_Rn - old_Rm));
  new_Rn = address;
  processor_id = ExecutingProcessor();
  slv6_write_byte(proc->mmu_ptr, address, get_byte_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 1);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.100--A5.2.7
 * STRB -- Load and Store Word or Unsigned Byte - Scaled register pre indexed */
void slv6_X_STRB_M2_ScReg_preInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t index;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  switch (shift) {
  case 0:
    index = (old_Rm << shift_imm);
    break;
  case 1:
    index = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
    break;
  case 2:
    index = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 1)? 0xFFFFFFFF: 0): asr(old_Rm, shift_imm));
    break;
  case 3:
    index = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
    break;
    default: abort();
  }
  address = ((U == 1)? (old_Rn + index): (old_Rn - index));
  new_Rn = address;
  processor_id = ExecutingProcessor();
  slv6_write_byte(proc->mmu_ptr, address, get_byte_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 1);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.100--A5.2.9
 * STRB -- Load and Store Word or Unsigned Byte - Register post indexed */
void slv6_X_STRB_M2_Reg_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  if ((U == 1))
    new_Rn = (old_Rn + old_Rm);
  else
    new_Rn = (old_Rn - old_Rm);
  processor_id = ExecutingProcessor();
  slv6_write_byte(proc->mmu_ptr, address, get_byte_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 1);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.100--A5.2.10
 * STRB -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
void slv6_X_STRB_M2_ScReg_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t index;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  switch (shift) {
  case 0:
    index = (old_Rm << shift_imm);
    break;
  case 1:
    index = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
    break;
  case 2:
    index = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 1)? 0xFFFFFFFF: 0): asr(old_Rm, shift_imm));
    break;
  case 3:
    index = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
    break;
    default: abort();
  }
  if ((U == 1))
    new_Rn = (old_Rn + index);
  else
    new_Rn = (old_Rn - index);
  processor_id = ExecutingProcessor();
  slv6_write_byte(proc->mmu_ptr, address, get_byte_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 1);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.101--A5.2.8
 * STRBT -- Load and Store Word or Unsigned Byte - Immediate post indexed */
void slv6_X_STRBT_M2_Imm_postInd(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  new_Rn = (old_Rn + signed_offset_12);
  processor_id = ExecutingProcessor();
  slv6_write_byte_as_user(proc->mmu_ptr, address, get_byte_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 1);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.101--A5.2.9
 * STRBT -- Load and Store Word or Unsigned Byte - Register post indexed */
void slv6_X_STRBT_M2_Reg_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  if ((U == 1))
    new_Rn = (old_Rn + old_Rm);
  else
    new_Rn = (old_Rn - old_Rm);
  processor_id = ExecutingProcessor();
  slv6_write_byte_as_user(proc->mmu_ptr, address, get_byte_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 1);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.101--A5.2.10
 * STRBT -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
void slv6_X_STRBT_M2_ScReg_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t index;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  switch (shift) {
  case 0:
    index = (old_Rm << shift_imm);
    break;
  case 1:
    index = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
    break;
  case 2:
    index = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 1)? 0xFFFFFFFF: 0): asr(old_Rm, shift_imm));
    break;
  case 3:
    index = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
    break;
    default: abort();
  }
  if ((U == 1))
    new_Rn = (old_Rn + index);
  else
    new_Rn = (old_Rn - index);
  processor_id = ExecutingProcessor();
  slv6_write_byte_as_user(proc->mmu_ptr, address, get_byte_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 1);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.102--A5.3.2
 * STRD -- Miscellaneous Loads and Stores - Immediate offset */
void slv6_X_STRD_M3_ImmOff(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint8_t offset_8;
  uint32_t physical_address;
  uint32_t processor_id;
  offset_8 = immedHL;
  address = ((U == 1)? (old_Rn + offset_8): (old_Rn - offset_8));
  processor_id = ExecutingProcessor();
  if ((((is_even(d) && (d != 14)) && (get_bits(address,1,0) == 0)) && ((CP15_reg1_Ubit(proc->cp15_ptr) == 1) || (get_bit(address,2) == 0)))) {
    slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
    slv6_write_word(proc->mmu_ptr, (address + 4), reg(proc,(d + 1)));
  } else
    unpredictable("STRD_M3_ImmOff");
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  if (Shared((address + 4))) {
    physical_address = slv6_TLB((address + 4));
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
}

/* A4.1.102--A5.3.3
 * STRD -- Miscellaneous Loads and Stores - Register offset */
void slv6_X_STRD_M3_RegOff(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t physical_address;
  uint32_t processor_id;
  address = ((U == 1)? (old_Rn + old_Rm): (old_Rn - old_Rm));
  processor_id = ExecutingProcessor();
  if ((((is_even(d) && (d != 14)) && (get_bits(address,1,0) == 0)) && ((CP15_reg1_Ubit(proc->cp15_ptr) == 1) || (get_bit(address,2) == 0)))) {
    slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
    slv6_write_word(proc->mmu_ptr, (address + 4), reg(proc,(d + 1)));
  } else
    unpredictable("STRD_M3_RegOff");
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  if (Shared((address + 4))) {
    physical_address = slv6_TLB((address + 4));
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
}

/* A4.1.102--A5.3.4
 * STRD -- Miscellaneous Loads and Stores - Immediate pre indexed */
void slv6_X_STRD_M3_Imm_preInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t new_Rn;
  uint8_t offset_8;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  offset_8 = immedHL;
  address = ((U == 1)? (old_Rn + offset_8): (old_Rn - offset_8));
  new_Rn = address;
  processor_id = ExecutingProcessor();
  if ((((is_even(d) && (d != 14)) && (get_bits(address,1,0) == 0)) && ((CP15_reg1_Ubit(proc->cp15_ptr) == 1) || (get_bit(address,2) == 0)))) {
    slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
    slv6_write_word(proc->mmu_ptr, (address + 4), reg(proc,(d + 1)));
  } else
    unpredictable("STRD_M3_Imm_preInd");
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  if (Shared((address + 4))) {
    physical_address = slv6_TLB((address + 4));
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.102--A5.3.5
 * STRD -- Miscellaneous Loads and Stores - Register pre indexed */
void slv6_X_STRD_M3_Reg_preInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = ((U == 1)? (old_Rn + old_Rm): (old_Rn - old_Rm));
  new_Rn = address;
  processor_id = ExecutingProcessor();
  if ((((is_even(d) && (d != 14)) && (get_bits(address,1,0) == 0)) && ((CP15_reg1_Ubit(proc->cp15_ptr) == 1) || (get_bit(address,2) == 0)))) {
    slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
    slv6_write_word(proc->mmu_ptr, (address + 4), reg(proc,(d + 1)));
  } else
    unpredictable("STRD_M3_Reg_preInd");
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  if (Shared((address + 4))) {
    physical_address = slv6_TLB((address + 4));
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.102--A5.3.6
 * STRD -- Miscellaneous Loads and Stores - Immediate post indexed */
void slv6_X_STRD_M3_Imm_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t new_Rn;
  uint8_t offset_8;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  offset_8 = immedHL;
  if ((U == 1))
    new_Rn = (old_Rn + offset_8);
  else
    new_Rn = (old_Rn - offset_8);
  processor_id = ExecutingProcessor();
  if ((((is_even(d) && (d != 14)) && (get_bits(address,1,0) == 0)) && ((CP15_reg1_Ubit(proc->cp15_ptr) == 1) || (get_bit(address,2) == 0)))) {
    slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
    slv6_write_word(proc->mmu_ptr, (address + 4), reg(proc,(d + 1)));
  } else
    unpredictable("STRD_M3_Imm_postInd");
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  if (Shared((address + 4))) {
    physical_address = slv6_TLB((address + 4));
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  set_reg_or_pc_ws(proc,n,new_Rn,4);
}

/* A4.1.102--A5.3.7
 * STRD -- Miscellaneous Loads and Stores - Register post indexed */
void slv6_X_STRD_M3_Reg_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  if ((U == 1))
    new_Rn = (old_Rn + old_Rm);
  else
    new_Rn = (old_Rn - old_Rm);
  processor_id = ExecutingProcessor();
  if ((((is_even(d) && (d != 14)) && (get_bits(address,1,0) == 0)) && ((CP15_reg1_Ubit(proc->cp15_ptr) == 1) || (get_bit(address,2) == 0)))) {
    slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
    slv6_write_word(proc->mmu_ptr, (address + 4), reg(proc,(d + 1)));
  } else
    unpredictable("STRD_M3_Reg_postInd");
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  if (Shared((address + 4))) {
    physical_address = slv6_TLB((address + 4));
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  set_reg_or_pc_ws(proc,n,new_Rn,4);
}

/* A4.1.103
 * STREX */
void slv6_X_STREX(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t physical_address;
  uint32_t processor_id;
  processor_id = ExecutingProcessor();
  physical_address = slv6_TLB(old_Rn);
  if (IsExclusiveLocal(physical_address, processor_id, 4)) {
    if ((Shared(old_Rn) == 1)) {
      if (IsExclusiveGlobal(physical_address, processor_id, 4)) {
        slv6_write_word(proc->mmu_ptr, old_Rn, old_Rm);
        set_reg(proc,d,0);
        ClearExclusiveByAddress3(physical_address, processor_id, 4);
      } else
        set_reg(proc,d,1);
    } else {
      slv6_write_word(proc->mmu_ptr, old_Rn, old_Rm);
      set_reg(proc,d,0);
    }
  } else
    set_reg(proc,d,1);
  ClearExclusiveLocal(processor_id);
}

/* A4.1.104--A5.3.2
 * STRH -- Miscellaneous Loads and Stores - Immediate offset */
void slv6_X_STRH_M3_ImmOff(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint8_t offset_8;
  uint32_t physical_address;
  uint32_t processor_id;
  offset_8 = immedHL;
  address = ((U == 1)? (old_Rn + offset_8): (old_Rn - offset_8));
  processor_id = ExecutingProcessor();
  if ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)) {
    if ((get_bit(address,0) == 0))
      slv6_write_half(proc->mmu_ptr, address, get_half_0(reg(proc,d)));
    else
      unpredictable("STRH_M3_ImmOff");
  } else
    slv6_write_half(proc->mmu_ptr, address, get_half_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 2);
  }
}

/* A4.1.104--A5.3.3
 * STRH -- Miscellaneous Loads and Stores - Register offset */
void slv6_X_STRH_M3_RegOff(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t physical_address;
  uint32_t processor_id;
  address = ((U == 1)? (old_Rn + old_Rm): (old_Rn - old_Rm));
  processor_id = ExecutingProcessor();
  if ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)) {
    if ((get_bit(address,0) == 0))
      slv6_write_half(proc->mmu_ptr, address, get_half_0(reg(proc,d)));
    else
      unpredictable("STRH_M3_RegOff");
  } else
    slv6_write_half(proc->mmu_ptr, address, get_half_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 2);
  }
}

/* A4.1.104--A5.3.4
 * STRH -- Miscellaneous Loads and Stores - Immediate pre indexed */
void slv6_X_STRH_M3_Imm_preInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t new_Rn;
  uint8_t offset_8;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  offset_8 = immedHL;
  address = ((U == 1)? (old_Rn + offset_8): (old_Rn - offset_8));
  new_Rn = address;
  processor_id = ExecutingProcessor();
  if ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)) {
    if ((get_bit(address,0) == 0))
      slv6_write_half(proc->mmu_ptr, address, get_half_0(reg(proc,d)));
    else
      unpredictable("STRH_M3_Imm_preInd");
  } else
    slv6_write_half(proc->mmu_ptr, address, get_half_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 2);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.104--A5.3.5
 * STRH -- Miscellaneous Loads and Stores - Register pre indexed */
void slv6_X_STRH_M3_Reg_preInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = ((U == 1)? (old_Rn + old_Rm): (old_Rn - old_Rm));
  new_Rn = address;
  processor_id = ExecutingProcessor();
  if ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)) {
    if ((get_bit(address,0) == 0))
      slv6_write_half(proc->mmu_ptr, address, get_half_0(reg(proc,d)));
    else
      unpredictable("STRH_M3_Reg_preInd");
  } else
    slv6_write_half(proc->mmu_ptr, address, get_half_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 2);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.104--A5.3.6
 * STRH -- Miscellaneous Loads and Stores - Immediate post indexed */
void slv6_X_STRH_M3_Imm_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t new_Rn;
  uint8_t offset_8;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  offset_8 = immedHL;
  if ((U == 1))
    new_Rn = (old_Rn + offset_8);
  else
    new_Rn = (old_Rn - offset_8);
  processor_id = ExecutingProcessor();
  if ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)) {
    if ((get_bit(address,0) == 0))
      slv6_write_half(proc->mmu_ptr, address, get_half_0(reg(proc,d)));
    else
      unpredictable("STRH_M3_Imm_postInd");
  } else
    slv6_write_half(proc->mmu_ptr, address, get_half_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 2);
  }
  set_reg_or_pc_ws(proc,n,new_Rn,4);
}

/* A4.1.104--A5.3.7
 * STRH -- Miscellaneous Loads and Stores - Register post indexed */
void slv6_X_STRH_M3_Reg_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  if ((U == 1))
    new_Rn = (old_Rn + old_Rm);
  else
    new_Rn = (old_Rn - old_Rm);
  processor_id = ExecutingProcessor();
  if ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)) {
    if ((get_bit(address,0) == 0))
      slv6_write_half(proc->mmu_ptr, address, get_half_0(reg(proc,d)));
    else
      unpredictable("STRH_M3_Reg_postInd");
  } else
    slv6_write_half(proc->mmu_ptr, address, get_half_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 2);
  }
  set_reg_or_pc_ws(proc,n,new_Rn,4);
}

/* A4.1.105--A5.2.8
 * STRT -- Load and Store Word or Unsigned Byte - Immediate post indexed */
void slv6_X_STRT_M2_Imm_postInd(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  new_Rn = (old_Rn + signed_offset_12);
  processor_id = ExecutingProcessor();
  slv6_write_word_as_user(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.105--A5.2.9
 * STRT -- Load and Store Word or Unsigned Byte - Register post indexed */
void slv6_X_STRT_M2_Reg_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  if ((U == 1))
    new_Rn = (old_Rn + old_Rm);
  else
    new_Rn = (old_Rn - old_Rm);
  processor_id = ExecutingProcessor();
  slv6_write_word_as_user(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.105--A5.2.10
 * STRT -- Load and Store Word or Unsigned Byte - Scaled register post indexed */
void slv6_X_STRT_M2_ScReg_postInd(struct SLv6_Processor *proc,
    const bool U,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t index;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  uint32_t physical_address;
  uint32_t processor_id;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  switch (shift) {
  case 0:
    index = (old_Rm << shift_imm);
    break;
  case 1:
    index = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
    break;
  case 2:
    index = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 1)? 0xFFFFFFFF: 0): asr(old_Rm, shift_imm));
    break;
  case 3:
    index = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
    break;
    default: abort();
  }
  if ((U == 1))
    new_Rn = (old_Rn + index);
  else
    new_Rn = (old_Rn - index);
  processor_id = ExecutingProcessor();
  slv6_write_word_as_user(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.106--A5.1.4
 * SUB -- Data processing operands - Register */
void slv6_X_SUB_M1_Reg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = old_Rm;
  shifter_carry_out = proc->cpsr.C_flag;
  set_reg_or_pc_ws(proc,d,(old_Rn - shifter_operand),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SUB_M1_Reg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
      proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
    }
  }
}

/* A4.1.106--A5.1.6
 * SUB -- Data processing operands - Logical shift left by register */
void slv6_X_SUB_M1_LSLReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm << get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(32 - get_byte_0(old_Rs))): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,0): 0)));
  set_reg(proc,d,(old_Rn - shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SUB_M1_LSLReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
      proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
    }
  }
}

/* A4.1.106--A5.1.7
 * SUB -- Data processing operands - Logical shift right by immediate */
void slv6_X_SUB_M1_LSRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn - shifter_operand),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SUB_M1_LSRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
      proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
    }
  }
}

/* A4.1.106--A5.1.8
 * SUB -- Data processing operands - Logical shift right by register */
void slv6_X_SUB_M1_LSRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm >> get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,31): 0)));
  set_reg(proc,d,(old_Rn - shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SUB_M1_LSRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
      proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
    }
  }
}

/* A4.1.106--A5.1.10
 * SUB -- Data processing operands - Arithmetic shift right by register */
void slv6_X_SUB_M1_ASRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? asr(old_Rm, get_byte_0(old_Rs)): ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF)));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): get_bit(old_Rm,31)));
  set_reg(proc,d,(old_Rn - shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SUB_M1_ASRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
      proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
    }
  }
}

/* A4.1.106--A5.1.11
 * SUB -- Data processing operands - Rotate right by immediate */
void slv6_X_SUB_M1_RRImm(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,0): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn - shifter_operand),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SUB_M1_RRImm");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
      proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
    }
  }
}

/* A4.1.106--A5.1.12
 * SUB -- Data processing operands - Rotate right by register */
void slv6_X_SUB_M1_RRReg(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_bits(old_Rs,4,0) == 0)? old_Rm: rotate_right(old_Rm, get_bits(old_Rs,4,0))));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_bits(old_Rs,4,0) == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(get_bits(old_Rs,4,0) - 1))));
  set_reg(proc,d,(old_Rn - shifter_operand));
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SUB_M1_RRReg");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
      proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
    }
  }
}

/* A4.1.106--A5.1.13
 * SUB -- Data processing operands - Rotate right with extend */
void slv6_X_SUB_M1_RRE(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((proc->cpsr.C_flag << 31) | (old_Rm >> 1));
  shifter_carry_out = get_bit(old_Rm,0);
  set_reg_or_pc_ws(proc,d,(old_Rn - shifter_operand),4);
  if (((S == 1) && (d == 15))) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SUB_M1_RRE");
  } else {
    if ((S == 1)) {
      proc->cpsr.N_flag = get_bit(reg(proc,d),31);
      proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
      proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
      proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
    }
  }
}

/* A4.1.107
 * SWI */
void slv6_X_SWI(struct SLv6_Processor *proc,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  uint32_t addr_of_next_instr;
  addr_of_next_instr = (reg(proc,15) - 4);
  set_reg_m(proc,14,svc,addr_of_next_instr);
  *spsr_m(proc,svc) = proc->cpsr;
  set_cpsr_mode(proc, svc);
  proc->cpsr.T_flag = 0;
  set_cpsr_I_flag(proc,1);
  proc->cpsr.E_flag = CP15_reg1_EEbit(proc->cp15_ptr);
  if (high_vectors_configured(proc))
    set_pc_raw_ws(proc,0xFFFF0008,inst_size(proc));
  else
    set_pc_raw_ws(proc,0x00000008,inst_size(proc));
}

/* A4.1.108
 * SWP */
void slv6_X_SWP(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t physical_address;
  uint32_t processor_id;
  uint32_t temp;
  processor_id = ExecutingProcessor();
  address = old_Rn;
  if ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)) {
    temp = rotate_right(slv6_read_word(proc->mmu_ptr,address), (get_bits(address,1,0) * 8));
    slv6_write_word(proc->mmu_ptr, address, old_Rm);
    set_reg(proc,d,temp);
  } else {
    temp = slv6_read_word(proc->mmu_ptr,address);
    slv6_write_word(proc->mmu_ptr, address, old_Rm);
    set_reg(proc,d,temp);
  }
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
}

/* A4.1.109
 * SWPB */
void slv6_X_SWPB(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t physical_address;
  uint32_t processor_id;
  uint8_t temp;
  processor_id = ExecutingProcessor();
  address = old_Rn;
  temp = slv6_read_byte(proc->mmu_ptr,address);
  slv6_write_byte(proc->mmu_ptr, address, get_byte_0(old_Rm));
  set_reg(proc,d,temp);
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 1);
  }
}

/* A4.1.110
 * SXTAB */
void slv6_X_SXTAB(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t rotate,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t operand2;
  operand2 = rotate_right(old_Rm, (rotate * 8));
  set_reg(proc,d,(old_Rn + SignExtend8(get_byte_0(operand2))));
}

/* A4.1.111
 * SXTAB16 */
void slv6_X_SXTAB16(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t rotate,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t operand2;
  operand2 = rotate_right(old_Rm, (rotate * 8));
  set_field(addr_of_reg(proc,d), 15, 0, (get_half_0(old_Rn) + SignExtend8(get_byte_0(operand2))));
  set_field(addr_of_reg(proc,d), 31, 16, (get_half_1(old_Rn) + SignExtend8(get_byte_2(operand2))));
}

/* A4.1.112
 * SXTAH */
void slv6_X_SXTAH(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t rotate,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t operand2;
  operand2 = rotate_right(old_Rm, (rotate * 8));
  set_reg(proc,d,(old_Rn + SignExtend16(get_half_0(operand2))));
}

/* A4.1.113
 * SXTB */
void slv6_X_SXTB(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t rotate,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  uint32_t operand2;
  operand2 = rotate_right(old_Rm, (rotate * 8));
  set_field(addr_of_reg(proc,d), 31, 0, SignExtend8(get_byte_0(operand2)));
}

/* A4.1.114
 * SXTB16 */
void slv6_X_SXTB16(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t rotate,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  uint32_t operand2;
  operand2 = rotate_right(old_Rm, (rotate * 8));
  set_field(addr_of_reg(proc,d), 15, 0, SignExtend8(get_byte_0(operand2)));
  set_field(addr_of_reg(proc,d), 31, 16, SignExtend8(get_byte_2(operand2)));
}

/* A4.1.115
 * SXTH */
void slv6_X_SXTH(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t rotate,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  uint32_t operand2;
  operand2 = rotate_right(old_Rm, (rotate * 8));
  set_field(addr_of_reg(proc,d), 31, 0, SignExtend16(get_half_0(operand2)));
}

/* A4.1.116--A5.1.3
 * TEQ -- Data processing operands - Immediate */
void slv6_X_TEQ_M1_Imm(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  alu_out = (old_Rn ^ shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.116--A5.1.4
 * TEQ -- Data processing operands - Register */
void slv6_X_TEQ_M1_Reg(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = old_Rm;
  shifter_carry_out = proc->cpsr.C_flag;
  alu_out = (old_Rn ^ shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.116--A5.1.5
 * TEQ -- Data processing operands - Logical shift left by immediate */
void slv6_X_TEQ_M1_LSLImm(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? old_Rm: (old_Rm << shift_imm));
  shifter_carry_out = ((shift_imm == 0)? proc->cpsr.C_flag: get_bit(old_Rm,(32 - shift_imm)));
  alu_out = (old_Rn ^ shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.116--A5.1.6
 * TEQ -- Data processing operands - Logical shift left by register */
void slv6_X_TEQ_M1_LSLReg(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm << get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(32 - get_byte_0(old_Rs))): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,0): 0)));
  alu_out = (old_Rn ^ shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.116--A5.1.7
 * TEQ -- Data processing operands - Logical shift right by immediate */
void slv6_X_TEQ_M1_LSRImm(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  alu_out = (old_Rn ^ shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.116--A5.1.8
 * TEQ -- Data processing operands - Logical shift right by register */
void slv6_X_TEQ_M1_LSRReg(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm >> get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,31): 0)));
  alu_out = (old_Rn ^ shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.116--A5.1.9
 * TEQ -- Data processing operands - Arithmetic shift right by immediate */
void slv6_X_TEQ_M1_ASRImm(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF): asr(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  alu_out = (old_Rn ^ shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.116--A5.1.10
 * TEQ -- Data processing operands - Arithmetic shift right by register */
void slv6_X_TEQ_M1_ASRReg(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? asr(old_Rm, get_byte_0(old_Rs)): ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF)));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): get_bit(old_Rm,31)));
  alu_out = (old_Rn ^ shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.116--A5.1.11
 * TEQ -- Data processing operands - Rotate right by immediate */
void slv6_X_TEQ_M1_RRImm(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,0): get_bit(old_Rm,(shift_imm - 1)));
  alu_out = (old_Rn ^ shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.116--A5.1.12
 * TEQ -- Data processing operands - Rotate right by register */
void slv6_X_TEQ_M1_RRReg(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_bits(old_Rs,4,0) == 0)? old_Rm: rotate_right(old_Rm, get_bits(old_Rs,4,0))));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_bits(old_Rs,4,0) == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(get_bits(old_Rs,4,0) - 1))));
  alu_out = (old_Rn ^ shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.116--A5.1.13
 * TEQ -- Data processing operands - Rotate right with extend */
void slv6_X_TEQ_M1_RRE(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((proc->cpsr.C_flag << 31) | (old_Rm >> 1));
  shifter_carry_out = get_bit(old_Rm,0);
  alu_out = (old_Rn ^ shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.117--A5.1.5
 * TST -- Data processing operands - Logical shift left by immediate */
void slv6_X_TST_M1_LSLImm(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? old_Rm: (old_Rm << shift_imm));
  shifter_carry_out = ((shift_imm == 0)? proc->cpsr.C_flag: get_bit(old_Rm,(32 - shift_imm)));
  alu_out = (old_Rn & shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.117--A5.1.6
 * TST -- Data processing operands - Logical shift left by register */
void slv6_X_TST_M1_LSLReg(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm << get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(32 - get_byte_0(old_Rs))): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,0): 0)));
  alu_out = (old_Rn & shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.117--A5.1.7
 * TST -- Data processing operands - Logical shift right by immediate */
void slv6_X_TST_M1_LSRImm(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  alu_out = (old_Rn & shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.117--A5.1.8
 * TST -- Data processing operands - Logical shift right by register */
void slv6_X_TST_M1_LSRReg(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm >> get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,31): 0)));
  alu_out = (old_Rn & shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.117--A5.1.9
 * TST -- Data processing operands - Arithmetic shift right by immediate */
void slv6_X_TST_M1_ASRImm(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF): asr(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  alu_out = (old_Rn & shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.117--A5.1.10
 * TST -- Data processing operands - Arithmetic shift right by register */
void slv6_X_TST_M1_ASRReg(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? asr(old_Rm, get_byte_0(old_Rs)): ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF)));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): get_bit(old_Rm,31)));
  alu_out = (old_Rn & shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.117--A5.1.11
 * TST -- Data processing operands - Rotate right by immediate */
void slv6_X_TST_M1_RRImm(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,0): get_bit(old_Rm,(shift_imm - 1)));
  alu_out = (old_Rn & shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.117--A5.1.12
 * TST -- Data processing operands - Rotate right by register */
void slv6_X_TST_M1_RRReg(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_bits(old_Rs,4,0) == 0)? old_Rm: rotate_right(old_Rm, get_bits(old_Rs,4,0))));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_bits(old_Rs,4,0) == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(get_bits(old_Rs,4,0) - 1))));
  alu_out = (old_Rn & shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.117--A5.1.13
 * TST -- Data processing operands - Rotate right with extend */
void slv6_X_TST_M1_RRE(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((proc->cpsr.C_flag << 31) | (old_Rm >> 1));
  shifter_carry_out = get_bit(old_Rm,0);
  alu_out = (old_Rn & shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.118
 * UADD16 */
void slv6_X_UADD16(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 15, 0, (get_half_0(old_Rn) + get_half_0(old_Rm)));
  set_GE_10(&proc->cpsr,((CarryFrom16_add2(get_half_0(old_Rn), get_half_0(old_Rm)) == 1)? 3: 0));
  set_field(addr_of_reg(proc,d), 31, 16, (get_half_1(old_Rn) + get_half_1(old_Rm)));
  set_GE_32(&proc->cpsr,((CarryFrom16_add2(get_half_1(old_Rn), get_half_1(old_Rm)) == 1)? 3: 0));
}

/* A4.1.119
 * UADD8 */
void slv6_X_UADD8(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 7, 0, (get_byte_0(old_Rn) + get_byte_0(old_Rm)));
  proc->cpsr.GE0 = CarryFrom8_add2(get_byte_0(old_Rn), get_byte_0(old_Rm));
  set_field(addr_of_reg(proc,d), 15, 8, (get_byte_1(old_Rn) + get_byte_1(old_Rm)));
  proc->cpsr.GE1 = CarryFrom8_add2(get_byte_1(old_Rn), get_byte_1(old_Rm));
  set_field(addr_of_reg(proc,d), 23, 16, (get_byte_2(old_Rn) + get_byte_2(old_Rm)));
  proc->cpsr.GE2 = CarryFrom8_add2(get_byte_2(old_Rn), get_byte_2(old_Rm));
  set_field(addr_of_reg(proc,d), 31, 24, (get_byte_3(old_Rn) + get_byte_3(old_Rm)));
  proc->cpsr.GE3 = CarryFrom8_add2(get_byte_3(old_Rn), get_byte_3(old_Rm));
}

/* A4.1.120
 * UADDSUBX */
void slv6_X_UADDSUBX(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t diff;
  uint32_t sum;
  sum = (get_half_1(old_Rn) + get_half_0(old_Rm));
  set_field(addr_of_reg(proc,d), 31, 16, get_half_0(sum));
  set_GE_32(&proc->cpsr,(CarryFrom16_add2(get_half_1(old_Rn), get_half_0(old_Rm))? 3: 0));
  diff = (get_half_0(old_Rn) - get_half_1(old_Rm));
  set_field(addr_of_reg(proc,d), 15, 0, get_half_0(diff));
  set_GE_10(&proc->cpsr,(BorrowFrom_sub2(get_half_0(old_Rn), get_half_1(old_Rm))? 3: 0));
}

/* A4.1.121
 * UHADD16 */
void slv6_X_UHADD16(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t sum;
  sum = (get_half_0(old_Rn) + get_half_0(old_Rm));
  set_field(addr_of_reg(proc,d), 15, 0, get_bits(sum,16,1));
  sum = (get_half_1(old_Rn) + get_half_1(old_Rm));
  set_field(addr_of_reg(proc,d), 31, 16, get_bits(sum,16,1));
}

/* A4.1.122
 * UHADD8 */
void slv6_X_UHADD8(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t sum;
  sum = (get_byte_0(old_Rn) + get_byte_0(old_Rm));
  set_field(addr_of_reg(proc,d), 7, 0, get_bits(sum,8,1));
  sum = (get_byte_1(old_Rn) + get_byte_1(old_Rm));
  set_field(addr_of_reg(proc,d), 15, 8, get_bits(sum,8,1));
  sum = (get_byte_2(old_Rn) + get_byte_2(old_Rm));
  set_field(addr_of_reg(proc,d), 23, 16, get_bits(sum,8,1));
  sum = (get_byte_3(old_Rn) + get_byte_3(old_Rm));
  set_field(addr_of_reg(proc,d), 31, 24, get_bits(sum,8,1));
}

/* A4.1.123
 * UHADDSUBX */
void slv6_X_UHADDSUBX(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t diff;
  uint32_t sum;
  sum = (get_half_1(old_Rn) + get_half_0(old_Rm));
  set_field(addr_of_reg(proc,d), 31, 16, get_bits(sum,16,1));
  diff = (get_half_0(old_Rn) - get_half_1(old_Rm));
  set_field(addr_of_reg(proc,d), 15, 0, get_bits(diff,16,1));
}

/* A4.1.124
 * UHSUB16 */
void slv6_X_UHSUB16(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t diff;
  diff = (get_half_0(old_Rn) - get_half_0(old_Rm));
  set_field(addr_of_reg(proc,d), 15, 0, get_bits(diff,16,1));
  diff = (get_half_1(old_Rn) - get_half_1(old_Rm));
  set_field(addr_of_reg(proc,d), 31, 16, get_bits(diff,16,1));
}

/* A4.1.125
 * UHSUB8 */
void slv6_X_UHSUB8(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t diff;
  diff = (get_byte_0(old_Rn) - get_byte_0(old_Rm));
  set_field(addr_of_reg(proc,d), 7, 0, get_bits(diff,8,1));
  diff = (get_byte_1(old_Rn) - get_byte_1(old_Rm));
  set_field(addr_of_reg(proc,d), 15, 8, get_bits(diff,8,1));
  diff = (get_byte_2(old_Rn) - get_byte_2(old_Rm));
  set_field(addr_of_reg(proc,d), 23, 16, get_bits(diff,8,1));
  diff = (get_byte_3(old_Rn) - get_byte_3(old_Rm));
  set_field(addr_of_reg(proc,d), 31, 24, get_bits(diff,8,1));
}

/* A4.1.126
 * UHSUBADDX */
void slv6_X_UHSUBADDX(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t diff;
  uint32_t sum;
  diff = (get_half_1(old_Rn) - get_half_0(old_Rm));
  set_field(addr_of_reg(proc,d), 31, 16, get_bits(diff,16,1));
  sum = (get_half_0(old_Rn) + get_half_1(old_Rm));
  set_field(addr_of_reg(proc,d), 15, 0, get_bits(sum,16,1));
}

/* A4.1.127
 * UMAAL */
void slv6_X_UMAAL(struct SLv6_Processor *proc,
    const uint8_t dHi,
    const uint8_t dLo,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  const uint32_t old_RdLo = reg(proc,dLo);
  uint64_t result;
  result = (((to_u64(old_Rm) * to_u64(old_Rs)) + old_RdLo) + reg(proc,dHi));
  set_reg(proc,dLo,get_bits(result,31,0));
  set_reg(proc,dHi,get_bits(result,63,32));
}

/* A4.1.128
 * UMLAL */
void slv6_X_UMLAL(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t dHi,
    const uint8_t dLo,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  const uint32_t old_RdLo = reg(proc,dLo);
  set_reg(proc,dLo,(get_bits((to_u64(old_Rm) * to_u64(old_Rs)),31,0) + old_RdLo));
  set_reg(proc,dHi,((get_bits((to_u64(old_Rm) * to_u64(old_Rs)),63,32) + reg(proc,dHi)) + CarryFrom_add2(get_bits((to_u64(old_Rm) * to_u64(old_Rs)),31,0), old_RdLo)));
  if ((S == 1)) {
    proc->cpsr.N_flag = get_bit(reg(proc,dHi),31);
    proc->cpsr.Z_flag = (((reg(proc,dHi) == 0) && (old_RdLo == 0))? 1: 0);
  }
}

/* A4.1.129
 * UMULL */
void slv6_X_UMULL(struct SLv6_Processor *proc,
    const bool S,
    const uint8_t dHi,
    const uint8_t dLo,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  const uint32_t old_RdLo = reg(proc,dLo);
  set_reg(proc,dHi,get_bits((to_u64(old_Rm) * to_u64(old_Rs)),63,32));
  set_reg(proc,dLo,get_bits((to_u64(old_Rm) * to_u64(old_Rs)),31,0));
  if ((S == 1)) {
    proc->cpsr.N_flag = get_bit(reg(proc,dHi),31);
    proc->cpsr.Z_flag = (((reg(proc,dHi) == 0) && (old_RdLo == 0))? 1: 0);
  }
}

/* A4.1.130
 * UQADD16 */
void slv6_X_UQADD16(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 15, 0, UnsignedSat((get_half_0(old_Rn) + get_half_0(old_Rm)), 16));
  set_field(addr_of_reg(proc,d), 31, 16, UnsignedSat((get_half_1(old_Rn) + get_half_1(old_Rm)), 16));
}

/* A4.1.131
 * UQADD8 */
void slv6_X_UQADD8(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 7, 0, UnsignedSat((get_byte_0(old_Rn) + get_byte_0(old_Rm)), 8));
  set_field(addr_of_reg(proc,d), 15, 8, UnsignedSat((get_byte_1(old_Rn) + get_byte_1(old_Rm)), 8));
  set_field(addr_of_reg(proc,d), 23, 16, UnsignedSat((get_byte_2(old_Rn) + get_byte_2(old_Rm)), 8));
  set_field(addr_of_reg(proc,d), 31, 24, UnsignedSat((get_byte_3(old_Rn) + get_byte_3(old_Rm)), 8));
}

/* A4.1.132
 * UQADDSUBX */
void slv6_X_UQADDSUBX(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 15, 0, UnsignedSat((get_half_0(old_Rn) - get_half_1(old_Rm)), 16));
  set_field(addr_of_reg(proc,d), 31, 16, UnsignedSat((get_half_1(old_Rn) + get_half_0(old_Rm)), 16));
}

/* A4.1.133
 * UQSUB16 */
void slv6_X_UQSUB16(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 15, 0, UnsignedSat((get_half_0(old_Rn) - get_half_0(old_Rm)), 16));
  set_field(addr_of_reg(proc,d), 31, 16, UnsignedSat((get_half_1(old_Rn) - get_half_1(old_Rm)), 16));
}

/* A4.1.134
 * UQSUB8 */
void slv6_X_UQSUB8(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 7, 0, UnsignedSat((get_byte_0(old_Rn) - get_byte_0(old_Rm)), 8));
  set_field(addr_of_reg(proc,d), 15, 8, UnsignedSat((get_byte_1(old_Rn) - get_byte_1(old_Rm)), 8));
  set_field(addr_of_reg(proc,d), 23, 16, UnsignedSat((get_byte_2(old_Rn) - get_byte_2(old_Rm)), 8));
  set_field(addr_of_reg(proc,d), 31, 24, UnsignedSat((get_byte_3(old_Rn) - get_byte_3(old_Rm)), 8));
}

/* A4.1.135
 * UQSUBADDX */
void slv6_X_UQSUBADDX(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 31, 16, UnsignedSat((get_half_1(old_Rn) - get_half_0(old_Rm)), 16));
  set_field(addr_of_reg(proc,d), 15, 0, UnsignedSat((get_half_0(old_Rn) + get_half_1(old_Rm)), 16));
}

/* A4.1.136
 * USAD8 */
void slv6_X_USAD8(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t diff1;
  uint32_t diff2;
  uint32_t diff3;
  uint32_t diff4;
  diff1 = ((get_byte_0(old_Rm) < get_byte_0(old_Rs))? (get_byte_0(old_Rs) - get_byte_0(old_Rm)): (get_byte_0(old_Rm) - get_byte_0(old_Rs)));
  diff2 = ((get_byte_1(old_Rm) < get_byte_1(old_Rs))? (get_byte_1(old_Rs) - get_byte_1(old_Rm)): (get_byte_1(old_Rm) - get_byte_1(old_Rs)));
  diff3 = ((get_byte_2(old_Rm) < get_byte_2(old_Rs))? (get_byte_2(old_Rs) - get_byte_2(old_Rm)): (get_byte_2(old_Rm) - get_byte_2(old_Rs)));
  diff4 = ((get_byte_3(old_Rm) < get_byte_3(old_Rs))? (get_byte_3(old_Rs) - get_byte_3(old_Rm)): (get_byte_3(old_Rm) - get_byte_3(old_Rs)));
  set_reg(proc,d,(((ZeroExtend(diff1) + ZeroExtend(diff2)) + ZeroExtend(diff3)) + ZeroExtend(diff4)));
}

/* A4.1.137
 * USADA8 */
void slv6_X_USADA8(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t diff1;
  uint32_t diff2;
  uint32_t diff3;
  uint32_t diff4;
  diff1 = ((get_byte_0(old_Rm) < get_byte_0(old_Rs))? (get_byte_0(old_Rs) - get_byte_0(old_Rm)): (get_byte_0(old_Rm) - get_byte_0(old_Rs)));
  diff2 = ((get_byte_1(old_Rm) < get_byte_1(old_Rs))? (get_byte_1(old_Rs) - get_byte_1(old_Rm)): (get_byte_1(old_Rm) - get_byte_1(old_Rs)));
  diff3 = ((get_byte_2(old_Rm) < get_byte_2(old_Rs))? (get_byte_2(old_Rs) - get_byte_2(old_Rm)): (get_byte_2(old_Rm) - get_byte_2(old_Rs)));
  diff4 = ((get_byte_3(old_Rm) < get_byte_3(old_Rs))? (get_byte_3(old_Rs) - get_byte_3(old_Rm)): (get_byte_3(old_Rm) - get_byte_3(old_Rs)));
  set_reg(proc,d,((((old_Rn + ZeroExtend(diff1)) + ZeroExtend(diff2)) + ZeroExtend(diff3)) + ZeroExtend(diff4)));
}

/* A4.1.138
 * USAT */
void slv6_X_USAT(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t sat_imm,
    const uint8_t shift,
    const uint8_t shift_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  uint32_t operand;
  operand = ((shift == 1)? ((shift_imm == 0)? get_bits(asr(old_Rm, 32),31,0): get_bits(asr(old_Rm, shift_imm),31,0)): get_bits((old_Rm << shift_imm),31,0));
  set_reg(proc,d,UnsignedSat(operand, sat_imm));
  if (UnsignedDoesSat(operand, sat_imm))
    proc->cpsr.Q_flag = 1;
}

/* A4.1.139
 * USAT16 */
void slv6_X_USAT16(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t sat_imm,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 15, 0, UnsignedSat(get_half_0(old_Rm), sat_imm));
  set_field(addr_of_reg(proc,d), 31, 16, UnsignedSat(get_half_1(old_Rm), sat_imm));
  if ((UnsignedDoesSat(get_half_0(old_Rm), sat_imm) || UnsignedDoesSat(get_half_1(old_Rm), sat_imm)))
    proc->cpsr.Q_flag = 1;
}

/* A4.1.140
 * USUB16 */
void slv6_X_USUB16(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 15, 0, (get_half_0(old_Rn) - get_half_0(old_Rm)));
  set_GE_10(&proc->cpsr,(BorrowFrom_sub2(get_half_0(old_Rn), get_half_0(old_Rm))? 0: 3));
  set_field(addr_of_reg(proc,d), 31, 16, (get_half_1(old_Rn) - get_half_1(old_Rm)));
  set_GE_32(&proc->cpsr,(BorrowFrom_sub2(get_half_1(old_Rn), get_half_1(old_Rm))? 0: 3));
}

/* A4.1.141
 * USUB8 */
void slv6_X_USUB8(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 7, 0, (get_byte_0(old_Rn) - get_byte_0(old_Rm)));
  proc->cpsr.GE0 = !(BorrowFrom_sub2(get_byte_0(old_Rn), get_byte_0(old_Rm)));
  set_field(addr_of_reg(proc,d), 15, 8, (get_byte_1(old_Rn) - get_byte_1(old_Rm)));
  proc->cpsr.GE1 = !(BorrowFrom_sub2(get_byte_1(old_Rn), get_byte_1(old_Rm)));
  set_field(addr_of_reg(proc,d), 23, 16, (get_byte_2(old_Rn) - get_byte_2(old_Rm)));
  proc->cpsr.GE2 = !(BorrowFrom_sub2(get_byte_2(old_Rn), get_byte_2(old_Rm)));
  set_field(addr_of_reg(proc,d), 31, 24, (get_byte_3(old_Rn) - get_byte_3(old_Rm)));
  proc->cpsr.GE3 = !(BorrowFrom_sub2(get_byte_3(old_Rn), get_byte_3(old_Rm)));
}

/* A4.1.142
 * USUBADDX */
void slv6_X_USUBADDX(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t diff;
  uint32_t sum;
  diff = (get_half_1(old_Rn) - get_half_0(old_Rm));
  set_field(addr_of_reg(proc,d), 31, 16, get_half_0(diff));
  set_GE_32(&proc->cpsr,(BorrowFrom_sub2(get_half_1(old_Rn), get_half_0(old_Rm))? 3: 0));
  sum = (get_half_0(old_Rn) + get_half_1(old_Rm));
  set_field(addr_of_reg(proc,d), 15, 0, get_half_0(sum));
  set_GE_10(&proc->cpsr,(CarryFrom16_add2(get_half_0(old_Rn), get_half_1(old_Rm))? 3: 0));
}

/* A4.1.143
 * UXTAB */
void slv6_X_UXTAB(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t rotate,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t operand2;
  operand2 = (rotate_right(old_Rm, (rotate * 8)) & 0x000000ff);
  set_reg(proc,d,(old_Rn + operand2));
}

/* A4.1.144
 * UXTAB16 */
void slv6_X_UXTAB16(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t rotate,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t operand2;
  operand2 = (rotate_right(old_Rm, (rotate * 8)) & 0x00ff00ff);
  set_field(addr_of_reg(proc,d), 15, 0, (get_half_0(old_Rn) + get_half_0(operand2)));
  set_field(addr_of_reg(proc,d), 31, 16, (get_half_1(old_Rn) + get_byte_2(operand2)));
}

/* A4.1.145
 * UXTAH */
void slv6_X_UXTAH(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t rotate,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t operand2;
  operand2 = (rotate_right(old_Rm, (rotate * 8)) & 0x0000ffff);
  set_reg(proc,d,(old_Rn + operand2));
}

/* A4.1.146
 * UXTB */
void slv6_X_UXTB(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t rotate,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 31, 0, (rotate_right(old_Rm, (rotate * 8)) & 0x000000ff));
}

/* A4.1.147
 * UXTB16 */
void slv6_X_UXTB16(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t rotate,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 31, 0, (rotate_right(old_Rm, (rotate * 8)) & 0x00ff00ff));
}

/* A4.1.148
 * UXTH */
void slv6_X_UXTH(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t rotate,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  set_field(addr_of_reg(proc,d), 31, 0, (rotate_right(old_Rm, (rotate * 8)) & 0x0000ffff));
}

/* A7.1.7
 * ADD (5) */
void slv6_X_Tb_ADD5(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t immed_8)
{
  set_reg(proc,d,((reg(proc,15) & 0xFFFFFFFC) + (immed_8 * 4)));
}

/* A7.1.12
 * ASR (2) */
void slv6_X_Tb_ASR2(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t s)
{
  const uint32_t old_Rs = reg(proc,s);
  if (!((get_byte_0(old_Rs) == 0))) {
    if ((get_byte_0(old_Rs) < 32)) {
      proc->cpsr.C_flag = get_bit(reg(proc,d),(get_byte_0(old_Rs) - 1));
      set_reg(proc,d,asr(reg(proc,d), get_byte_0(old_Rs)));
    } else {
      proc->cpsr.C_flag = get_bit(reg(proc,d),31);
      if ((get_bit(reg(proc,d),31) == 0))
        set_reg(proc,d,0);
      else
        set_reg(proc,d,0xFFFFFFFF);
    }
  }
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
}

/* A7.1.16
 * BKPT */
void slv6_X_Tb_BKPT(struct SLv6_Processor *proc)
{
  if (not_overridden_by_debug_hardware()) {
    set_reg_m(proc,14,abt,(address_of_current_instruction(proc) + 4));
    *spsr_m(proc,abt) = proc->cpsr;
    set_cpsr_mode(proc, abt);
    proc->cpsr.T_flag = 0;
    set_cpsr_I_flag(proc,1);
    set_cpsr_A_flag(proc,1);
    proc->cpsr.E_flag = CP15_reg1_EEbit(proc->cp15_ptr);
    if (high_vectors_configured(proc))
      set_pc_raw_ws(proc,0xFFFF000C,inst_size(proc));
    else
      set_pc_raw_ws(proc,0x0000000C,inst_size(proc));
  }
}

/* A7.1.18
 * BLX (2) */
void slv6_X_Tb_BLX2(struct SLv6_Processor *proc,
    const uint8_t m)
{
  const uint32_t old_Rm = reg(proc,m);
  uint32_t addr_of_next_instr;
  uint32_t target;
  addr_of_next_instr = (reg(proc,15) - 2);
  target = old_Rm;
  set_reg(proc,14,(addr_of_next_instr | 1));
  proc->cpsr.T_flag = get_bit(target,0);
  set_pc_raw_ws(proc,(target & 0xFFFFFFFE),inst_size(proc));
}

/* A7.1.20
 * CMN */
void slv6_X_Tb_CMN(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  alu_out = (old_Rn + old_Rm);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = CarryFrom_add2(old_Rn, old_Rm);
  proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, old_Rm);
}

/* A7.1.24
 * CPS */
void slv6_X_Tb_CPS(struct SLv6_Processor *proc,
    const bool A,
    const bool F,
    const bool I,
    const uint8_t imod)
{
  if (InAPrivilegedMode(proc)) {
    if ((A == 1))
      set_cpsr_A_flag(proc,imod);
    if ((I == 1))
      set_cpsr_I_flag(proc,imod);
    if ((F == 1))
      set_cpsr_F_flag(proc,imod);
  }
}

/* A7.1.35
 * LDRH (2) */
void slv6_X_Tb_LDRH2(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint16_t data;
  address = (old_Rn + old_Rm);
  if ((!((get_bit(address,0) == 0)) && (CP15_reg1_Ubit(proc->cp15_ptr) == 0)))
    unpredictable("Tb_LDRH2");
  data = slv6_read_half(proc->mmu_ptr,address);
  set_reg(proc,d,ZeroExtend(get_half_0(data)));
}

/* A7.1.36
 * LDRSB */
void slv6_X_Tb_LDRSB(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  address = (old_Rn + old_Rm);
  set_reg(proc,d,SignExtend8(slv6_read_byte(proc->mmu_ptr,address)));
}

/* A7.1.37
 * LDRSH */
void slv6_X_Tb_LDRSH(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint16_t data;
  address = (old_Rn + old_Rm);
  if ((!((get_bit(address,0) == 0)) && (CP15_reg1_Ubit(proc->cp15_ptr) == 0)))
    unpredictable("Tb_LDRSH");
  data = slv6_read_half(proc->mmu_ptr,address);
  set_reg(proc,d,SignExtend16(get_half_0(data)));
}

/* A7.1.51
 * REV */
void slv6_X_Tb_REV(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  set_field(addr_of_reg(proc,d), 31, 24, get_byte_0(old_Rn));
  set_field(addr_of_reg(proc,d), 23, 16, get_byte_1(old_Rn));
  set_field(addr_of_reg(proc,d), 15, 8, get_byte_2(old_Rn));
  set_field(addr_of_reg(proc,d), 7, 0, get_byte_3(old_Rn));
}

/* A7.1.52
 * REV16 */
void slv6_X_Tb_REV16(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  set_field(addr_of_reg(proc,d), 15, 8, get_byte_0(old_Rn));
  set_field(addr_of_reg(proc,d), 7, 0, get_byte_1(old_Rn));
  set_field(addr_of_reg(proc,d), 31, 24, get_byte_2(old_Rn));
  set_field(addr_of_reg(proc,d), 23, 16, get_byte_3(old_Rn));
}

/* A7.1.53
 * REVSH */
void slv6_X_Tb_REVSH(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  set_field(addr_of_reg(proc,d), 15, 8, get_byte_0(old_Rn));
  set_field(addr_of_reg(proc,d), 7, 0, get_byte_1(old_Rn));
  if ((get_bit(old_Rn,7) == 1))
    set_field(addr_of_reg(proc,d), 31, 16, 0xFFFF);
  else
    set_field(addr_of_reg(proc,d), 31, 16, 0x0000);
}

/* A7.1.55
 * SBC */
void slv6_X_Tb_SBC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m)
{
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,((reg(proc,d) - old_Rm) - !(proc->cpsr.C_flag)));
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
  proc->cpsr.C_flag = !(BorrowFrom_sub3(reg(proc,d), old_Rm, !(proc->cpsr.C_flag)));
  proc->cpsr.V_flag = OverflowFrom_sub3(reg(proc,d), old_Rm, !(proc->cpsr.C_flag));
}

/* A7.1.56
 * SETEND */
void slv6_X_Tb_SETEND(struct SLv6_Processor *proc,
    const bool E)
{
  proc->cpsr.E_flag = E;
}

/* A7.1.63
 * STRH (1) */
void slv6_X_Tb_STRH1(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint32_t immed_5)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t physical_address;
  uint32_t processor_id;
  processor_id = ExecutingProcessor();
  address = (old_Rn + (immed_5 * 2));
  if ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)) {
    if ((get_bit(address,0) == 0))
      slv6_write_half(proc->mmu_ptr, address, get_half_0(reg(proc,d)));
    else
      unpredictable("Tb_STRH1");
  } else
    slv6_write_half(proc->mmu_ptr, address, get_half_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress2(physical_address, 2);
  }
}

/* A7.1.64
 * STRH (2) */
void slv6_X_Tb_STRH2(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t physical_address;
  uint32_t processor_id;
  processor_id = ExecutingProcessor();
  address = (old_Rn + old_Rm);
  if ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)) {
    if ((get_bit(address,0) == 0))
      slv6_write_half(proc->mmu_ptr, address, get_half_0(reg(proc,d)));
    else
      unpredictable("Tb_STRH2");
  } else
    slv6_write_half(proc->mmu_ptr, address, get_half_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress2(physical_address, 2);
  }
}

/* A7.1.69
 * SWI */
void slv6_X_Tb_SWI(struct SLv6_Processor *proc)
{
  uint32_t addr_of_next_instr;
  addr_of_next_instr = (reg(proc,15) - 2);
  set_reg_m(proc,14,svc,addr_of_next_instr);
  *spsr_m(proc,svc) = proc->cpsr;
  set_cpsr_mode(proc, svc);
  proc->cpsr.T_flag = 0;
  set_cpsr_I_flag(proc,1);
  proc->cpsr.E_flag = CP15_reg1_EEbit(proc->cp15_ptr);
  if (high_vectors_configured(proc))
    set_pc_raw_ws(proc,0xFFFF0008,inst_size(proc));
  else
    set_pc_raw_ws(proc,0x00000008,inst_size(proc));
}

/* A7.1.70
 * SXTB */
void slv6_X_Tb_SXTB(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m)
{
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,SignExtend8(get_byte_0(old_Rm)));
}

/* A7.1.71
 * SXTH */
void slv6_X_Tb_SXTH(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m)
{
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,SignExtend16(get_half_0(old_Rm)));
}

/* A7.1.73
 * UXTB */
void slv6_X_Tb_UXTB(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m)
{
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,(old_Rm & 0x000000ff));
}

/* A7.1.74
 * UXTH */
void slv6_X_Tb_UXTH(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m)
{
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,(old_Rm & 0x0000ffff));
}

END_SIMSOC_NAMESPACE
