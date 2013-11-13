#include "slv6_iss_c_prelude.h"

/* A4.1.23--A5.2.2
 * LDR -- Load and Store Word or Unsigned Byte - Immediate offset */
void slv6_X_LDR_M2_ImmOff(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t data;
  address = (old_Rn + signed_offset_12);
  data = ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)? rotate_right(slv6_read_word(proc->mmu_ptr,address), (get_bits(address,1,0) * 8)): slv6_read_word(proc->mmu_ptr,address));
  if ((d == 15)) {
    set_pc_raw_ws(proc,(data & 0xFFFFFFFE),inst_size(proc));
    proc->cpsr.T_flag = get_bit(data,0);
  } else
    set_reg_or_pc_ws(proc,d,data,inst_size(proc));
}

/* A4.1.99--A5.2.2
 * STR -- Load and Store Word or Unsigned Byte - Immediate offset */
void slv6_X_STR_M2_ImmOff(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t physical_address;
  uint32_t processor_id;
  address = (old_Rn + signed_offset_12);
  processor_id = ExecutingProcessor();
  slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
}

/* A4.1.5
 * B, BL (L=1) */
void slv6_X_B_L1(struct SLv6_Processor *proc,
    const SLv6_Condition cond,
    const uint32_t pc_offset)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  uint32_t addr_of_next_instr;
  addr_of_next_instr = (reg(proc,15) - 4);
  set_reg(proc,14,addr_of_next_instr);
  set_pc_raw_ws(proc,(reg(proc,15) + pc_offset),4);
}

/* A4.1.5
 * B, BL (L=0) */
void slv6_X_B_L0(struct SLv6_Processor *proc,
    const SLv6_Condition cond,
    const uint32_t pc_offset)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  uint32_t addr_of_next_instr;
  addr_of_next_instr = (reg(proc,15) - 4);
  set_pc_raw_ws(proc,(reg(proc,15) + pc_offset),4);
}

/* A4.1.106--A5.1.3
 * SUB -- Data processing operands - Immediate (S=1) */
void slv6_X_SUB_M1_Imm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn - shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SUB_M1_Imm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
    proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
  }
}

/* A4.1.106--A5.1.3
 * SUB -- Data processing operands - Immediate (S=0) */
void slv6_X_SUB_M1_Imm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn - shifter_operand),4);
}

/* A4.1.15--A5.1.4
 * CMP -- Data processing operands - Register */
void slv6_X_CMP_M1_Reg(struct SLv6_Processor *proc,
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
  alu_out = (old_Rn - shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
  proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
}

/* A4.1.3--A5.1.3
 * ADD -- Data processing operands - Immediate (S=1) */
void slv6_X_ADD_M1_Imm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn + shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADD_M1_Imm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
    proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
  }
}

/* A4.1.3--A5.1.3
 * ADD -- Data processing operands - Immediate (S=0) */
void slv6_X_ADD_M1_Imm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn + shifter_operand),4);
}

/* A4.1.3--A5.1.4
 * ADD -- Data processing operands - Register (S=1) */
void slv6_X_ADD_M1_Reg_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn + shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADD_M1_Reg_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
    proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
  }
}

/* A4.1.3--A5.1.4
 * ADD -- Data processing operands - Register (S=0) */
void slv6_X_ADD_M1_Reg_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn + shifter_operand),4);
}

/* A4.1.18--A5.1.4
 * EOR -- Data processing operands - Register (S=1) */
void slv6_X_EOR_M1_Reg_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn ^ shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("EOR_M1_Reg_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.18--A5.1.4
 * EOR -- Data processing operands - Register (S=0) */
void slv6_X_EOR_M1_Reg_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn ^ shifter_operand),4);
}

/* A4.1.4--A5.1.3
 * AND -- Data processing operands - Immediate (S=1) */
void slv6_X_AND_M1_Imm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn & shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("AND_M1_Imm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.4--A5.1.3
 * AND -- Data processing operands - Immediate (S=0) */
void slv6_X_AND_M1_Imm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn & shifter_operand),4);
}

/* A4.1.35--A5.1.7
 * MOV -- Data processing operands - Logical shift right by immediate (S=1) */
void slv6_X_MOV_M1_LSRImm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,shifter_operand,4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MOV_M1_LSRImm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.35--A5.1.7
 * MOV -- Data processing operands - Logical shift right by immediate (S=0) */
void slv6_X_MOV_M1_LSRImm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,shifter_operand,4);
}

/* A4.1.17
 * CPY */
void slv6_X_CPY(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  set_reg_or_pc_ws(proc,d,old_Rm,4);
}

/* A4.1.35--A5.1.5
 * MOV -- Data processing operands - Logical shift left by immediate (S=1) */
void slv6_X_MOV_M1_LSLImm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,shifter_operand,4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MOV_M1_LSLImm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.35--A5.1.5
 * MOV -- Data processing operands - Logical shift left by immediate (S=0) */
void slv6_X_MOV_M1_LSLImm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,shifter_operand,4);
}

/* A4.1.35--A5.1.3
 * MOV -- Data processing operands - Immediate (S=1) */
void slv6_X_MOV_M1_Imm_S1(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,shifter_operand,4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MOV_M1_Imm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.35--A5.1.3
 * MOV -- Data processing operands - Immediate (S=0) */
void slv6_X_MOV_M1_Imm_S0(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,shifter_operand,4);
}

/* A4.1.20--A5.4.2
 * LDM (1) -- Load and Store Multiple - Increment after (W=1) */
void slv6_X_LDM1_M4_IA_W1(struct SLv6_Processor *proc,
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
  new_Rn = (old_Rn + nb_reg_x4);
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
  set_reg(proc,n,new_Rn);
}

/* A4.1.20--A5.4.2
 * LDM (1) -- Load and Store Multiple - Increment after (W=0) */
void slv6_X_LDM1_M4_IA_W0(struct SLv6_Processor *proc,
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
}

/* A4.1.15--A5.1.3
 * CMP -- Data processing operands - Immediate */
void slv6_X_CMP_M1_Imm(struct SLv6_Processor *proc,
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
  alu_out = (old_Rn - shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
  proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
}

/* A4.1.23--A5.2.4
 * LDR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) */
void slv6_X_LDR_M2_ScRegOff_U1(struct SLv6_Processor *proc,
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
  address = (old_Rn + index);
  data = ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)? rotate_right(slv6_read_word(proc->mmu_ptr,address), (get_bits(address,1,0) * 8)): slv6_read_word(proc->mmu_ptr,address));
  if ((d == 15)) {
    set_pc_raw_ws(proc,(data & 0xFFFFFFFE),inst_size(proc));
    proc->cpsr.T_flag = get_bit(data,0);
  } else
    set_reg_or_pc_ws(proc,d,data,inst_size(proc));
}

/* A4.1.23--A5.2.4
 * LDR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) */
void slv6_X_LDR_M2_ScRegOff_U0(struct SLv6_Processor *proc,
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
  address = (old_Rn - index);
  data = ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)? rotate_right(slv6_read_word(proc->mmu_ptr,address), (get_bits(address,1,0) * 8)): slv6_read_word(proc->mmu_ptr,address));
  if ((d == 15)) {
    set_pc_raw_ws(proc,(data & 0xFFFFFFFE),inst_size(proc));
    proc->cpsr.T_flag = get_bit(data,0);
  } else
    set_reg_or_pc_ws(proc,d,data,inst_size(proc));
}

/* A4.1.10
 * BX */
void slv6_X_BX(struct SLv6_Processor *proc,
    const uint8_t m,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rm = reg(proc,m);
  proc->cpsr.T_flag = get_bit(old_Rm,0);
  set_pc_raw_ws(proc,(old_Rm & 0xFFFFFFFE),inst_size(proc));
}

/* A4.1.3--A5.1.5
 * ADD -- Data processing operands - Logical shift left by immediate (S=1) */
void slv6_X_ADD_M1_LSLImm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn + shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADD_M1_LSLImm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
    proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
  }
}

/* A4.1.3--A5.1.5
 * ADD -- Data processing operands - Logical shift left by immediate (S=0) */
void slv6_X_ADD_M1_LSLImm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn + shifter_operand),4);
}

/* A4.1.24--A5.2.2
 * LDRB -- Load and Store Word or Unsigned Byte - Immediate offset */
void slv6_X_LDRB_M2_ImmOff(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  address = (old_Rn + signed_offset_12);
  set_reg(proc,d,slv6_read_byte(proc->mmu_ptr,address));
}

/* A4.1.42--A5.1.4
 * ORR -- Data processing operands - Register (S=1) */
void slv6_X_ORR_M1_Reg_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn | shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ORR_M1_Reg_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.42--A5.1.4
 * ORR -- Data processing operands - Register (S=0) */
void slv6_X_ORR_M1_Reg_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn | shifter_operand),4);
}

/* A4.1.35--A5.1.11
 * MOV -- Data processing operands - Rotate right by immediate (S=1) */
void slv6_X_MOV_M1_RRImm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,shifter_operand,4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MOV_M1_RRImm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.35--A5.1.11
 * MOV -- Data processing operands - Rotate right by immediate (S=0) */
void slv6_X_MOV_M1_RRImm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,shifter_operand,4);
}

/* A4.1.23--A5.2.8
 * LDR -- Load and Store Word or Unsigned Byte - Immediate post indexed */
void slv6_X_LDR_M2_Imm_postInd(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t data;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  new_Rn = (old_Rn + signed_offset_12);
  data = ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)? rotate_right(slv6_read_word(proc->mmu_ptr,address), (get_bits(address,1,0) * 8)): slv6_read_word(proc->mmu_ptr,address));
  if ((d == 15)) {
    set_pc_raw_ws(proc,(data & 0xFFFFFFFE),inst_size(proc));
    proc->cpsr.T_flag = get_bit(data,0);
  } else
    set_reg_or_pc_ws(proc,d,data,inst_size(proc));
  set_reg(proc,n,new_Rn);
}

/* A4.1.18--A5.1.11
 * EOR -- Data processing operands - Rotate right by immediate (S=1) */
void slv6_X_EOR_M1_RRImm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn ^ shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("EOR_M1_RRImm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.18--A5.1.11
 * EOR -- Data processing operands - Rotate right by immediate (S=0) */
void slv6_X_EOR_M1_RRImm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn ^ shifter_operand),4);
}

/* A4.1.4--A5.1.4
 * AND -- Data processing operands - Register (S=1) */
void slv6_X_AND_M1_Reg_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn & shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("AND_M1_Reg_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.4--A5.1.4
 * AND -- Data processing operands - Register (S=0) */
void slv6_X_AND_M1_Reg_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn & shifter_operand),4);
}

/* A4.1.99--A5.2.5
 * STR -- Load and Store Word or Unsigned Byte - Immediate pre indexed */
void slv6_X_STR_M2_Imm_preInd(struct SLv6_Processor *proc,
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
  slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.100--A5.2.2
 * STRB -- Load and Store Word or Unsigned Byte - Immediate offset */
void slv6_X_STRB_M2_ImmOff(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t physical_address;
  uint32_t processor_id;
  address = (old_Rn + signed_offset_12);
  processor_id = ExecutingProcessor();
  slv6_write_byte(proc->mmu_ptr, address, get_byte_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 1);
  }
}

/* A4.1.42--A5.1.5
 * ORR -- Data processing operands - Logical shift left by immediate (S=1) */
void slv6_X_ORR_M1_LSLImm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn | shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ORR_M1_LSLImm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.42--A5.1.5
 * ORR -- Data processing operands - Logical shift left by immediate (S=0) */
void slv6_X_ORR_M1_LSLImm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn | shifter_operand),4);
}

/* A4.1.2--A5.1.4
 * ADC -- Data processing operands - Register (S=1) */
void slv6_X_ADC_M1_Reg_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,((old_Rn + shifter_operand) + proc->cpsr.C_flag),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADC_M1_Reg_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = CarryFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
    proc->cpsr.V_flag = OverflowFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
  }
}

/* A4.1.2--A5.1.4
 * ADC -- Data processing operands - Register (S=0) */
void slv6_X_ADC_M1_Reg_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,((old_Rn + shifter_operand) + proc->cpsr.C_flag),4);
}

/* A4.1.24--A5.2.3
 * LDRB -- Load and Store Word or Unsigned Byte - Register offset (U=1) */
void slv6_X_LDRB_M2_RegOff_U1(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  address = (old_Rn + old_Rm);
  set_reg(proc,d,slv6_read_byte(proc->mmu_ptr,address));
}

/* A4.1.24--A5.2.3
 * LDRB -- Load and Store Word or Unsigned Byte - Register offset (U=0) */
void slv6_X_LDRB_M2_RegOff_U0(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  address = (old_Rn - old_Rm);
  set_reg(proc,d,slv6_read_byte(proc->mmu_ptr,address));
}

/* A4.1.60--A5.1.4
 * RSB -- Data processing operands - Register (S=1) */
void slv6_X_RSB_M1_Reg_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(shifter_operand - old_Rn),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSB_M1_Reg_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = !(BorrowFrom_sub2(shifter_operand, old_Rn));
    proc->cpsr.V_flag = OverflowFrom_sub2(shifter_operand, old_Rn);
  }
}

/* A4.1.60--A5.1.4
 * RSB -- Data processing operands - Register (S=0) */
void slv6_X_RSB_M1_Reg_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(shifter_operand - old_Rn),4);
}

/* A4.1.6--A5.1.3
 * BIC -- Data processing operands - Immediate (S=1) */
void slv6_X_BIC_M1_Imm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn & ~(shifter_operand)),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("BIC_M1_Imm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.6--A5.1.3
 * BIC -- Data processing operands - Immediate (S=0) */
void slv6_X_BIC_M1_Imm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn & ~(shifter_operand)),4);
}

/* A4.1.41--A5.1.3
 * MVN -- Data processing operands - Immediate (S=1) */
void slv6_X_MVN_M1_Imm_S1(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,~(shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MVN_M1_Imm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.41--A5.1.3
 * MVN -- Data processing operands - Immediate (S=0) */
void slv6_X_MVN_M1_Imm_S0(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t rotate_imm,
    const SLv6_Condition cond,
    const uint32_t immed_rotated)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,~(shifter_operand),4);
}

/* A4.1.42--A5.1.7
 * ORR -- Data processing operands - Logical shift right by immediate (S=1) */
void slv6_X_ORR_M1_LSRImm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn | shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ORR_M1_LSRImm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.42--A5.1.7
 * ORR -- Data processing operands - Logical shift right by immediate (S=0) */
void slv6_X_ORR_M1_LSRImm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn | shifter_operand),4);
}

/* A4.1.18--A5.1.7
 * EOR -- Data processing operands - Logical shift right by immediate (S=1) */
void slv6_X_EOR_M1_LSRImm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn ^ shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("EOR_M1_LSRImm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.18--A5.1.7
 * EOR -- Data processing operands - Logical shift right by immediate (S=0) */
void slv6_X_EOR_M1_LSRImm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn ^ shifter_operand),4);
}

/* A4.1.23--A5.2.3
 * LDR -- Load and Store Word or Unsigned Byte - Register offset (U=1) */
void slv6_X_LDR_M2_RegOff_U1(struct SLv6_Processor *proc,
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
  address = (old_Rn + old_Rm);
  data = ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)? rotate_right(slv6_read_word(proc->mmu_ptr,address), (get_bits(address,1,0) * 8)): slv6_read_word(proc->mmu_ptr,address));
  if ((d == 15)) {
    set_pc_raw_ws(proc,(data & 0xFFFFFFFE),inst_size(proc));
    proc->cpsr.T_flag = get_bit(data,0);
  } else
    set_reg_or_pc_ws(proc,d,data,inst_size(proc));
}

/* A4.1.23--A5.2.3
 * LDR -- Load and Store Word or Unsigned Byte - Register offset (U=0) */
void slv6_X_LDR_M2_RegOff_U0(struct SLv6_Processor *proc,
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
  address = (old_Rn - old_Rm);
  data = ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)? rotate_right(slv6_read_word(proc->mmu_ptr,address), (get_bits(address,1,0) * 8)): slv6_read_word(proc->mmu_ptr,address));
  if ((d == 15)) {
    set_pc_raw_ws(proc,(data & 0xFFFFFFFE),inst_size(proc));
    proc->cpsr.T_flag = get_bit(data,0);
  } else
    set_reg_or_pc_ws(proc,d,data,inst_size(proc));
}

/* A4.1.35--A5.1.8
 * MOV -- Data processing operands - Logical shift right by register (S=1) */
void slv6_X_MOV_M1_LSRReg_S1(struct SLv6_Processor *proc,
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
  set_reg(proc,d,shifter_operand);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MOV_M1_LSRReg_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.35--A5.1.8
 * MOV -- Data processing operands - Logical shift right by register (S=0) */
void slv6_X_MOV_M1_LSRReg_S0(struct SLv6_Processor *proc,
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
  set_reg(proc,d,shifter_operand);
}

/* A4.1.100--A5.2.3
 * STRB -- Load and Store Word or Unsigned Byte - Register offset (U=1) */
void slv6_X_STRB_M2_RegOff_U1(struct SLv6_Processor *proc,
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
  address = (old_Rn + old_Rm);
  processor_id = ExecutingProcessor();
  slv6_write_byte(proc->mmu_ptr, address, get_byte_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 1);
  }
}

/* A4.1.100--A5.2.3
 * STRB -- Load and Store Word or Unsigned Byte - Register offset (U=0) */
void slv6_X_STRB_M2_RegOff_U0(struct SLv6_Processor *proc,
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
  address = (old_Rn - old_Rm);
  processor_id = ExecutingProcessor();
  slv6_write_byte(proc->mmu_ptr, address, get_byte_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 1);
  }
}

/* A4.1.99--A5.2.4
 * STR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) */
void slv6_X_STR_M2_ScRegOff_U1(struct SLv6_Processor *proc,
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
  address = (old_Rn + index);
  processor_id = ExecutingProcessor();
  slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
}

/* A4.1.99--A5.2.4
 * STR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) */
void slv6_X_STR_M2_ScRegOff_U0(struct SLv6_Processor *proc,
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
  address = (old_Rn - index);
  processor_id = ExecutingProcessor();
  slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
}

/* A4.1.14--A5.1.4
 * CMN -- Data processing operands - Register */
void slv6_X_CMN_M1_Reg(struct SLv6_Processor *proc,
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
  alu_out = (old_Rn + shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
  proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
}

/* A4.1.99--A5.2.9
 * STR -- Load and Store Word or Unsigned Byte - Register post indexed (U=1) */
void slv6_X_STR_M2_Reg_postInd_U1(struct SLv6_Processor *proc,
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
  new_Rn = (old_Rn + old_Rm);
  processor_id = ExecutingProcessor();
  slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.99--A5.2.9
 * STR -- Load and Store Word or Unsigned Byte - Register post indexed (U=0) */
void slv6_X_STR_M2_Reg_postInd_U0(struct SLv6_Processor *proc,
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
  new_Rn = (old_Rn - old_Rm);
  processor_id = ExecutingProcessor();
  slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.99--A5.2.3
 * STR -- Load and Store Word or Unsigned Byte - Register offset (U=1) */
void slv6_X_STR_M2_RegOff_U1(struct SLv6_Processor *proc,
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
  address = (old_Rn + old_Rm);
  processor_id = ExecutingProcessor();
  slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
}

/* A4.1.99--A5.2.3
 * STR -- Load and Store Word or Unsigned Byte - Register offset (U=0) */
void slv6_X_STR_M2_RegOff_U0(struct SLv6_Processor *proc,
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
  address = (old_Rn - old_Rm);
  processor_id = ExecutingProcessor();
  slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
}

/* A4.1.18--A5.1.5
 * EOR -- Data processing operands - Logical shift left by immediate (S=1) */
void slv6_X_EOR_M1_LSLImm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn ^ shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("EOR_M1_LSLImm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.18--A5.1.5
 * EOR -- Data processing operands - Logical shift left by immediate (S=0) */
void slv6_X_EOR_M1_LSLImm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn ^ shifter_operand),4);
}

/* A4.1.60--A5.1.3
 * RSB -- Data processing operands - Immediate (S=1) */
void slv6_X_RSB_M1_Imm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(shifter_operand - old_Rn),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSB_M1_Imm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = !(BorrowFrom_sub2(shifter_operand, old_Rn));
    proc->cpsr.V_flag = OverflowFrom_sub2(shifter_operand, old_Rn);
  }
}

/* A4.1.60--A5.1.3
 * RSB -- Data processing operands - Immediate (S=0) */
void slv6_X_RSB_M1_Imm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(shifter_operand - old_Rn),4);
}

/* A4.1.35--A5.1.9
 * MOV -- Data processing operands - Arithmetic shift right by immediate (S=1) */
void slv6_X_MOV_M1_ASRImm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,shifter_operand,4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MOV_M1_ASRImm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.35--A5.1.9
 * MOV -- Data processing operands - Arithmetic shift right by immediate (S=0) */
void slv6_X_MOV_M1_ASRImm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,shifter_operand,4);
}

/* A4.1.3--A5.1.11
 * ADD -- Data processing operands - Rotate right by immediate (S=1) */
void slv6_X_ADD_M1_RRImm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn + shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADD_M1_RRImm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
    proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
  }
}

/* A4.1.3--A5.1.11
 * ADD -- Data processing operands - Rotate right by immediate (S=0) */
void slv6_X_ADD_M1_RRImm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn + shifter_operand),4);
}

/* A4.1.60--A5.1.5
 * RSB -- Data processing operands - Logical shift left by immediate (S=1) */
void slv6_X_RSB_M1_LSLImm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(shifter_operand - old_Rn),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSB_M1_LSLImm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = !(BorrowFrom_sub2(shifter_operand, old_Rn));
    proc->cpsr.V_flag = OverflowFrom_sub2(shifter_operand, old_Rn);
  }
}

/* A4.1.60--A5.1.5
 * RSB -- Data processing operands - Logical shift left by immediate (S=0) */
void slv6_X_RSB_M1_LSLImm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(shifter_operand - old_Rn),4);
}

/* A4.1.100--A5.2.8
 * STRB -- Load and Store Word or Unsigned Byte - Immediate post indexed */
void slv6_X_STRB_M2_Imm_postInd(struct SLv6_Processor *proc,
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
  slv6_write_byte(proc->mmu_ptr, address, get_byte_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 1);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.97--A5.4.2
 * STM (1) -- Load and Store Multiple - Increment after (W=1) */
void slv6_X_STM1_M4_IA_W1(struct SLv6_Processor *proc,
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
  end_address = ((old_Rn + nb_reg_x4) - 4);
  new_Rn = (old_Rn + nb_reg_x4);
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
  set_reg(proc,n,new_Rn);
}

/* A4.1.97--A5.4.2
 * STM (1) -- Load and Store Multiple - Increment after (W=0) */
void slv6_X_STM1_M4_IA_W0(struct SLv6_Processor *proc,
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
  end_address = ((old_Rn + nb_reg_x4) - 4);
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
}

/* A4.1.117--A5.1.3
 * TST -- Data processing operands - Immediate */
void slv6_X_TST_M1_Imm(struct SLv6_Processor *proc,
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
  alu_out = (old_Rn & shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.97--A5.4.5
 * STM (1) -- Load and Store Multiple - Decrement before (W=1) */
void slv6_X_STM1_M4_DB_W1(struct SLv6_Processor *proc,
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
  start_address = (old_Rn - nb_reg_x4);
  end_address = (old_Rn - 4);
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
  set_reg(proc,n,new_Rn);
}

/* A4.1.97--A5.4.5
 * STM (1) -- Load and Store Multiple - Decrement before (W=0) */
void slv6_X_STM1_M4_DB_W0(struct SLv6_Processor *proc,
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
  start_address = (old_Rn - nb_reg_x4);
  end_address = (old_Rn - 4);
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
}

/* A4.1.41--A5.1.4
 * MVN -- Data processing operands - Register (S=1) */
void slv6_X_MVN_M1_Reg_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,~(shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MVN_M1_Reg_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.41--A5.1.4
 * MVN -- Data processing operands - Register (S=0) */
void slv6_X_MVN_M1_Reg_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,~(shifter_operand),4);
}

/* A4.1.97--A5.4.3
 * STM (1) -- Load and Store Multiple - Increment before (W=1) */
void slv6_X_STM1_M4_IB_W1(struct SLv6_Processor *proc,
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
  end_address = (old_Rn + nb_reg_x4);
  new_Rn = (old_Rn + nb_reg_x4);
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
  set_reg(proc,n,new_Rn);
}

/* A4.1.97--A5.4.3
 * STM (1) -- Load and Store Multiple - Increment before (W=0) */
void slv6_X_STM1_M4_IB_W0(struct SLv6_Processor *proc,
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
  end_address = (old_Rn + nb_reg_x4);
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
}

/* A4.1.3--A5.1.7
 * ADD -- Data processing operands - Logical shift right by immediate (S=1) */
void slv6_X_ADD_M1_LSRImm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn + shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADD_M1_LSRImm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
    proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
  }
}

/* A4.1.3--A5.1.7
 * ADD -- Data processing operands - Logical shift right by immediate (S=0) */
void slv6_X_ADD_M1_LSRImm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn + shifter_operand),4);
}

/* A4.1.99--A5.2.8
 * STR -- Load and Store Word or Unsigned Byte - Immediate post indexed */
void slv6_X_STR_M2_Imm_postInd(struct SLv6_Processor *proc,
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
  slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.24--A5.2.4
 * LDRB -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) */
void slv6_X_LDRB_M2_ScRegOff_U1(struct SLv6_Processor *proc,
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
  address = (old_Rn + index);
  set_reg(proc,d,slv6_read_byte(proc->mmu_ptr,address));
}

/* A4.1.24--A5.2.4
 * LDRB -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) */
void slv6_X_LDRB_M2_ScRegOff_U0(struct SLv6_Processor *proc,
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
  address = (old_Rn - index);
  set_reg(proc,d,slv6_read_byte(proc->mmu_ptr,address));
}

/* A4.1.106--A5.1.5
 * SUB -- Data processing operands - Logical shift left by immediate (S=1) */
void slv6_X_SUB_M1_LSLImm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn - shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SUB_M1_LSLImm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
    proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
  }
}

/* A4.1.106--A5.1.5
 * SUB -- Data processing operands - Logical shift left by immediate (S=0) */
void slv6_X_SUB_M1_LSLImm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn - shifter_operand),4);
}

/* A4.1.20--A5.4.3
 * LDM (1) -- Load and Store Multiple - Increment before (W=1) */
void slv6_X_LDM1_M4_IB_W1(struct SLv6_Processor *proc,
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
  new_Rn = (old_Rn + nb_reg_x4);
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
  set_reg(proc,n,new_Rn);
}

/* A4.1.20--A5.4.3
 * LDM (1) -- Load and Store Multiple - Increment before (W=0) */
void slv6_X_LDM1_M4_IB_W0(struct SLv6_Processor *proc,
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
}

/* A4.1.28--A5.3.2
 * LDRH -- Miscellaneous Loads and Stores - Immediate offset (U=1) */
void slv6_X_LDRH_M3_ImmOff_U1(struct SLv6_Processor *proc,
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
  address = (old_Rn + offset_8);
  if ((!((get_bit(address,0) == 0)) && (CP15_reg1_Ubit(proc->cp15_ptr) == 0)))
    unpredictable("LDRH_M3_ImmOff_U1");
  data = slv6_read_half(proc->mmu_ptr,address);
  set_reg(proc,d,ZeroExtend(get_half_0(data)));
}

/* A4.1.28--A5.3.2
 * LDRH -- Miscellaneous Loads and Stores - Immediate offset (U=0) */
void slv6_X_LDRH_M3_ImmOff_U0(struct SLv6_Processor *proc,
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
  address = (old_Rn - offset_8);
  if ((!((get_bit(address,0) == 0)) && (CP15_reg1_Ubit(proc->cp15_ptr) == 0)))
    unpredictable("LDRH_M3_ImmOff_U0");
  data = slv6_read_half(proc->mmu_ptr,address);
  set_reg(proc,d,ZeroExtend(get_half_0(data)));
}

/* A4.1.23--A5.2.5
 * LDR -- Load and Store Word or Unsigned Byte - Immediate pre indexed */
void slv6_X_LDR_M2_Imm_preInd(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const SLv6_Condition cond,
    const uint32_t signed_offset_12)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t data;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = (old_Rn + signed_offset_12);
  new_Rn = address;
  data = ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)? rotate_right(slv6_read_word(proc->mmu_ptr,address), (get_bits(address,1,0) * 8)): slv6_read_word(proc->mmu_ptr,address));
  if ((d == 15)) {
    set_pc_raw_ws(proc,(data & 0xFFFFFFFE),inst_size(proc));
    proc->cpsr.T_flag = get_bit(data,0);
  } else
    set_reg_or_pc_ws(proc,d,data,inst_size(proc));
  set_reg(proc,n,new_Rn);
}

/* A4.1.87
 * SMULL (S=1) */
void slv6_X_SMULL_S1(struct SLv6_Processor *proc,
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
  set_reg(proc,dHi,get_bits((to_i64(old_Rm) * to_i64(old_Rs)),63,32));
  set_reg(proc,dLo,get_bits((to_i64(old_Rm) * to_i64(old_Rs)),31,0));
  proc->cpsr.N_flag = get_bit(reg(proc,dHi),31);
  proc->cpsr.Z_flag = (((reg(proc,dHi) == 0) && (old_RdLo == 0))? 1: 0);
}

/* A4.1.87
 * SMULL (S=0) */
void slv6_X_SMULL_S0(struct SLv6_Processor *proc,
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
  set_reg(proc,dHi,get_bits((to_i64(old_Rm) * to_i64(old_Rs)),63,32));
  set_reg(proc,dLo,get_bits((to_i64(old_Rm) * to_i64(old_Rs)),31,0));
}

/* A4.1.60--A5.1.9
 * RSB -- Data processing operands - Arithmetic shift right by immediate (S=1) */
void slv6_X_RSB_M1_ASRImm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(shifter_operand - old_Rn),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSB_M1_ASRImm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = !(BorrowFrom_sub2(shifter_operand, old_Rn));
    proc->cpsr.V_flag = OverflowFrom_sub2(shifter_operand, old_Rn);
  }
}

/* A4.1.60--A5.1.9
 * RSB -- Data processing operands - Arithmetic shift right by immediate (S=0) */
void slv6_X_RSB_M1_ASRImm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(shifter_operand - old_Rn),4);
}

/* A4.1.117--A5.1.4
 * TST -- Data processing operands - Register */
void slv6_X_TST_M1_Reg(struct SLv6_Processor *proc,
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
  alu_out = (old_Rn & shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.18--A5.1.3
 * EOR -- Data processing operands - Immediate (S=1) */
void slv6_X_EOR_M1_Imm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn ^ shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("EOR_M1_Imm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.18--A5.1.3
 * EOR -- Data processing operands - Immediate (S=0) */
void slv6_X_EOR_M1_Imm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn ^ shifter_operand),4);
}

/* A4.1.42--A5.1.9
 * ORR -- Data processing operands - Arithmetic shift right by immediate (S=1) */
void slv6_X_ORR_M1_ASRImm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn | shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ORR_M1_ASRImm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.42--A5.1.9
 * ORR -- Data processing operands - Arithmetic shift right by immediate (S=0) */
void slv6_X_ORR_M1_ASRImm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn | shifter_operand),4);
}

/* A4.1.42--A5.1.3
 * ORR -- Data processing operands - Immediate (S=1) */
void slv6_X_ORR_M1_Imm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn | shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ORR_M1_Imm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.42--A5.1.3
 * ORR -- Data processing operands - Immediate (S=0) */
void slv6_X_ORR_M1_Imm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn | shifter_operand),4);
}

/* A4.1.106--A5.1.9
 * SUB -- Data processing operands - Arithmetic shift right by immediate (S=1) */
void slv6_X_SUB_M1_ASRImm_S1(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn - shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SUB_M1_ASRImm_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
    proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
  }
}

/* A4.1.106--A5.1.9
 * SUB -- Data processing operands - Arithmetic shift right by immediate (S=0) */
void slv6_X_SUB_M1_ASRImm_S0(struct SLv6_Processor *proc,
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
  set_reg_or_pc_ws(proc,d,(old_Rn - shifter_operand),4);
}

/* A4.1.35--A5.1.6
 * MOV -- Data processing operands - Logical shift left by register (S=1) */
void slv6_X_MOV_M1_LSLReg_S1(struct SLv6_Processor *proc,
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
  set_reg(proc,d,shifter_operand);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MOV_M1_LSLReg_S1");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.35--A5.1.6
 * MOV -- Data processing operands - Logical shift left by register (S=0) */
void slv6_X_MOV_M1_LSLReg_S0(struct SLv6_Processor *proc,
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
  set_reg(proc,d,shifter_operand);
}

/* A4.1.40
 * MUL (S=1) */
void slv6_X_MUL_S1(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,get_bits((to_u64(old_Rm) * to_u64(old_Rs)),31,0));
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
}

/* A4.1.40
 * MUL (S=0) */
void slv6_X_MUL_S0(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s,
    const SLv6_Condition cond)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,get_bits((to_u64(old_Rm) * to_u64(old_Rs)),31,0));

}

/* A4.1.14--A5.1.3
 * CMN -- Data processing operands - Immediate */
void slv6_X_CMN_M1_Imm(struct SLv6_Processor *proc,
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
  alu_out = (old_Rn + shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
  proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
}

/* A7.1.28
 * LDR (1) */
void slv6_X_Tb_LDR1(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint32_t immed_5)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t data;
  address = (old_Rn + (immed_5 * 4));
  if ((!((get_bits(address,1,0) == 0)) && (CP15_reg1_Ubit(proc->cp15_ptr) == 0)))
    unpredictable("Tb_LDR1");
  data = slv6_read_word(proc->mmu_ptr,address);
  set_reg(proc,d,data);
}

/* A7.1.25
 * CPY */
void slv6_X_Tb_CPY(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m)
{
  const uint32_t old_Rm = reg(proc,m);
  set_reg_or_pc_ws(proc,d,old_Rm,2);
}

/* A7.1.58
 * STR (1) */
void slv6_X_Tb_STR1(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint32_t immed_5)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t physical_address;
  uint32_t processor_id;
  processor_id = ExecutingProcessor();
  address = (old_Rn + (immed_5 * 4));
  if ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)) {
    if ((get_bits(address,1,0) == 0))
      slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
    else
      unpredictable("Tb_STR1");
  } else
    slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address))
    physical_address = slv6_TLB(address);
  ClearExclusiveByAddress2(physical_address, 4);
}

/* A7.1.13
 * B (1) */
void slv6_X_Tb_B1(struct SLv6_Processor *proc,
    const SLv6_Condition cond,
    const uint32_t simmed_8_ext)
{
  if (!ConditionPassed(&proc->cpsr, cond)) return;
  set_pc_raw_ws(proc,(reg(proc,15) + simmed_8_ext),2);
}

/* A7.1.38
 * LSL (1) */
void slv6_X_Tb_LSL1(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint32_t immed_5)
{
  const uint32_t old_Rm = reg(proc,m);
  if ((immed_5 == 0))
    set_reg(proc,d,old_Rm);
  else {
    proc->cpsr.C_flag = get_bit(old_Rm,(32 - immed_5));
    set_reg(proc,d,(old_Rm << immed_5));
  }
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
}

/* A7.1.5
 * ADD (3) */
void slv6_X_Tb_ADD3(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,(old_Rn + old_Rm));
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
  proc->cpsr.C_flag = CarryFrom_add2(old_Rn, old_Rm);
  proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, old_Rm);
}

/* A7.1.42
 * MOV (1) */
void slv6_X_Tb_MOV1(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t immed_8)
{
  set_reg(proc,d,immed_8);
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
}

/* A7.1.22
 * CMP (2) */
void slv6_X_Tb_CMP2(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  alu_out = (old_Rn - old_Rm);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, old_Rm));
  proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, old_Rm);
}

/* A7.1.30
 * LDR (3) */
void slv6_X_Tb_LDR3(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t immed_8)
{
  uint32_t address;
  address = ((reg(proc,15) & 0xFFFFFFFC) + (immed_8 * 4));
  set_reg(proc,d,slv6_read_word(proc->mmu_ptr,address));
}

/* A7.1.26
 * EOR */
void slv6_X_Tb_EOR(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m)
{
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,(reg(proc,d) ^ old_Rm));
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
}

/* A7.1.66
 * SUB (2) */
void slv6_X_Tb_SUB2(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t immed_8)
{
  set_reg(proc,d,(reg(proc,d) - immed_8));
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
  proc->cpsr.C_flag = !(BorrowFrom_sub2(reg(proc,d), immed_8));
  proc->cpsr.V_flag = OverflowFrom_sub2(reg(proc,d), immed_8);
}

/* A7.1.43
 * MOV (2) */
void slv6_X_Tb_MOV2(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  set_reg(proc,d,old_Rn);
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
  proc->cpsr.C_flag = 0;
  proc->cpsr.V_flag = 0;
}

/* A7.1.4
 * ADD (2) */
void slv6_X_Tb_ADD2(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t immed_8)
{
  set_reg(proc,d,(reg(proc,d) + immed_8));
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
  proc->cpsr.C_flag = CarryFrom_add2(reg(proc,d), immed_8);
  proc->cpsr.V_flag = OverflowFrom_add2(reg(proc,d), immed_8);
}

/* A7.1.31
 * LDR (4) */
void slv6_X_Tb_LDR4(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t immed_8)
{
  uint32_t address;
  uint32_t data;
  address = (reg(proc,13) + (immed_8 * 4));
  if ((!((get_bits(address,1,0) == 0)) && (CP15_reg1_Ubit(proc->cp15_ptr) == 0)))
    unpredictable("Tb_LDR4");
  data = slv6_read_word(proc->mmu_ptr,address);
  set_reg(proc,d,data);
}

/* A7.1.10
 * AND */
void slv6_X_Tb_AND(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m)
{
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,(reg(proc,d) & old_Rm));
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
}

/* A7.1.40
 * LSR (1) */
void slv6_X_Tb_LSR1(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint32_t immed_5)
{
  const uint32_t old_Rm = reg(proc,m);
  if ((immed_5 == 0)) {
    proc->cpsr.C_flag = get_bit(old_Rm,31);
    set_reg(proc,d,0);
  } else {
    proc->cpsr.C_flag = get_bit(old_Rm,(immed_5 - 1));
    set_reg(proc,d,(old_Rm >> immed_5));
  }
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
}

/* A7.1.29
 * LDR (2) */
void slv6_X_Tb_LDR2(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t data;
  address = (old_Rn + old_Rm);
  if ((!((get_bits(address,1,0) == 0)) && (CP15_reg1_Ubit(proc->cp15_ptr) == 0)))
    unpredictable("Tb_LDR2");
  data = slv6_read_word(proc->mmu_ptr,address);
  set_reg(proc,d,data);
}

/* A7.1.6
 * ADD (4) */
void slv6_X_Tb_ADD4(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m)
{
  const uint32_t old_Rm = reg(proc,m);
  set_reg_or_pc_ws(proc,d,(reg(proc,d) + old_Rm),2);
}

/* A7.1.21
 * CMP (1) */
void slv6_X_Tb_CMP1(struct SLv6_Processor *proc,
    const uint8_t immed_8,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t alu_out;
  alu_out = (old_Rn - immed_8);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, immed_8));
  proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, immed_8);
}

/* A7.1.48
 * ORR */
void slv6_X_Tb_ORR(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m)
{
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,(reg(proc,d) | old_Rm));
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
}

/* A7.1.60
 * STR (3) */
void slv6_X_Tb_STR3(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t immed_8)
{
  uint32_t address;
  uint32_t physical_address;
  uint32_t processor_id;
  processor_id = ExecutingProcessor();
  address = (reg(proc,13) + (immed_8 * 4));
  if ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)) {
    if ((get_bits(address,1,0) == 0))
      slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
    else
      unpredictable("Tb_STR3");
  } else
    slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress2(physical_address, 4);
  }
}

/* A7.1.54
 * ROR */
void slv6_X_Tb_ROR(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t s)
{
  const uint32_t old_Rs = reg(proc,s);
  if (!((get_byte_0(old_Rs) == 0))) {
    if ((get_bits(old_Rs,4,0) == 0))
      proc->cpsr.C_flag = get_bit(reg(proc,d),31);
    else {
      proc->cpsr.C_flag = get_bit(reg(proc,d),(get_bits(old_Rs,4,0) - 1));
      set_reg(proc,d,rotate_right(reg(proc,d), get_bits(old_Rs,4,0)));
    }
  }
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
}

/* A7.1.17
 * BL, BLX (1) */
void slv6_X_Tb_BL(struct SLv6_Processor *proc,
    const uint32_t H,
    const uint32_t offset_11)
{
  uint32_t addr_of_next_instr;
  addr_of_next_instr = (reg(proc,15) - 2);
  if ((H == 2))
    set_reg(proc,14,(reg(proc,15) + (SignExtend11(offset_11) << 12)));
  else {
    if ((H == 3)) {
      set_pc_raw_ws(proc,(reg(proc,14) + (offset_11 << 1)),inst_size(proc));
      set_reg(proc,14,(addr_of_next_instr | 1));
    } else {
      if ((H == 1)) {
        set_pc_raw_ws(proc,((reg(proc,14) + (offset_11 << 1)) & 0xFFFFFFFC),inst_size(proc));
        set_reg(proc,14,(addr_of_next_instr | 1));
        proc->cpsr.T_flag = 0;
      }
    }
  }
}

/* A7.1.14
 * B (2) */
void slv6_X_Tb_B2(struct SLv6_Processor *proc,
    const uint32_t simmed_11_ext)
{
  set_pc_raw_ws(proc,(reg(proc,15) + simmed_11_ext),2);
}

/* A7.1.47
 * NEG */
void slv6_X_Tb_NEG(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m)
{
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,(0 - old_Rm));
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
  proc->cpsr.C_flag = !(BorrowFrom_sub2(0, old_Rm));
  proc->cpsr.V_flag = OverflowFrom_sub2(0, old_Rm);
}

/* A7.1.32
 * LDRB (1) */
void slv6_X_Tb_LDRB1(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint32_t immed_5)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  address = (old_Rn + immed_5);
  set_reg(proc,d,slv6_read_byte(proc->mmu_ptr,address));
}

/* A7.1.50
 * PUSH */
void slv6_X_Tb_PUSH(struct SLv6_Processor *proc,
    const bool R,
    const uint32_t register_list)
{
  uint32_t address;
  uint32_t end_address;
  uint32_t physical_address;
  uint32_t start_address;
  start_address = (reg(proc,13) - ((R + Number_Of_Set_Bits_In(register_list)) * 4));
  end_address = (reg(proc,13) - 4);
  address = start_address;
  size_t i; for (i = 0; i<=7; ++i) {
    if ((get_bit(register_list,i) == 1)) {
      slv6_write_word(proc->mmu_ptr, address, reg(proc,i));
      address = (address + 4);
    }
}
  if ((R == 1)) {
    slv6_write_word(proc->mmu_ptr, address, reg(proc,14));
    address = (address + 4);
  }
  set_reg(proc,13,(reg(proc,13) - ((R + Number_Of_Set_Bits_In(register_list)) * 4)));
  if ((CP15_reg1_Ubit(proc->cp15_ptr) == 1)) {
    if (Shared(address)) {
      physical_address = slv6_TLB(address);
      ClearExclusiveByAddress2(physical_address, 4);
    }
  }
}

/* A7.1.49
 * POP */
void slv6_X_Tb_POP(struct SLv6_Processor *proc,
    const bool R,
    const uint32_t register_list)
{
  uint32_t address;
  uint32_t end_address;
  uint32_t start_address;
  uint32_t value;
  start_address = reg(proc,13);
  end_address = (reg(proc,13) + ((R + Number_Of_Set_Bits_In(register_list)) * 4));
  address = start_address;
  size_t i; for (i = 0; i<=7; ++i) {
    if ((get_bit(register_list,i) == 1)) {
      set_reg(proc,i,slv6_read_word(proc->mmu_ptr,address));
      address = (address + 4);
    }
}
  if ((R == 1)) {
    value = slv6_read_word(proc->mmu_ptr,address);
    set_pc_raw_ws(proc,(value & 0xFFFFFFFE),inst_size(proc));
    proc->cpsr.T_flag = get_bit(value,0);
    address = (address + 4);
  }
  set_reg(proc,13,end_address);
}

/* A7.1.23
 * CMP (3) */
void slv6_X_Tb_CMP3(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  alu_out = (old_Rn - old_Rm);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, old_Rm));
  proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, old_Rm);
}

/* A7.1.68
 * SUB (4) */
void slv6_X_Tb_SUB4(struct SLv6_Processor *proc,
    const uint32_t immed_7)
{
  set_reg(proc,13,(reg(proc,13) - (immed_7 << 2)));
}

/* A7.1.9
 * ADD (7) */
void slv6_X_Tb_ADD7(struct SLv6_Processor *proc,
    const uint32_t immed_7)
{
  set_reg(proc,13,(reg(proc,13) + (immed_7 << 2)));
}

/* A7.1.8
 * ADD (6) */
void slv6_X_Tb_ADD6(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t immed_8)
{
  set_reg(proc,d,(reg(proc,13) + (immed_8 << 2)));
}

/* A7.1.19
 * BX */
void slv6_X_Tb_BX(struct SLv6_Processor *proc,
    const uint8_t m)
{
  const uint32_t old_Rm = reg(proc,m);
  proc->cpsr.T_flag = get_bit(old_Rm,0);
  set_pc_raw_ws(proc,(get_bits(old_Rm,31,1) << 1),inst_size(proc));
}

/* A7.1.61
 * STRB (1) */
void slv6_X_Tb_STRB1(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint32_t immed_5)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t physical_address;
  uint32_t processor_id;
  processor_id = ExecutingProcessor();
  address = (old_Rn + immed_5);
  slv6_write_byte(proc->mmu_ptr, address, get_byte_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress2(physical_address, 1);
  }
}

/* A7.1.33
 * LDRB (2) */
void slv6_X_Tb_LDRB2(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  address = (old_Rn + old_Rm);
  set_reg(proc,d,slv6_read_byte(proc->mmu_ptr,address));
}

/* A7.1.2
 * ADC */
void slv6_X_Tb_ADC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m)
{
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,((reg(proc,d) + old_Rm) + proc->cpsr.C_flag));
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
  proc->cpsr.C_flag = CarryFrom_add3(reg(proc,d), old_Rm, proc->cpsr.C_flag);
  proc->cpsr.V_flag = OverflowFrom_add3(reg(proc,d), old_Rm, proc->cpsr.C_flag);
}

/* A7.1.67
 * SUB (3) */
void slv6_X_Tb_SUB3(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,(old_Rn - old_Rm));
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
  proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, old_Rm));
  proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, old_Rm);
}

/* A7.1.65
 * SUB (1) */
void slv6_X_Tb_SUB1(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint32_t immed_3)
{
  const uint32_t old_Rn = reg(proc,n);
  set_reg(proc,d,(old_Rn - immed_3));
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
  proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, immed_3));
  proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, immed_3);
}

/* A7.1.41
 * LSR (2) */
void slv6_X_Tb_LSR2(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t s)
{
  const uint32_t old_Rs = reg(proc,s);
  if (!((get_byte_0(old_Rs) == 0))) {
    if ((get_byte_0(old_Rs) < 32)) {
      proc->cpsr.C_flag = get_bit(reg(proc,d),(get_byte_0(old_Rs) - 1));
      set_reg(proc,d,(reg(proc,d) >> get_byte_0(old_Rs)));
    } else {
      if ((get_byte_0(old_Rs) == 32)) {
        proc->cpsr.C_flag = get_bit(reg(proc,d),31);
        set_reg(proc,d,0);
      } else {
        proc->cpsr.C_flag = 0;
        set_reg(proc,d,0);
      }
    }
  }
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
}

/* A7.1.59
 * STR (2) */
void slv6_X_Tb_STR2(struct SLv6_Processor *proc,
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
    if ((get_bits(address,1,0) == 0))
      slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
    else
      unpredictable("Tb_STR2");
  } else
    slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress2(physical_address, 4);
  }
}

/* A7.1.62
 * STRB (2) */
void slv6_X_Tb_STRB2(struct SLv6_Processor *proc,
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
  slv6_write_byte(proc->mmu_ptr, address, get_byte_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress2(physical_address, 1);
  }
}

/* A7.1.27
 * LDMIA */
void slv6_X_Tb_LDMIA(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t end_address;
  uint32_t start_address;
  start_address = old_Rn;
  end_address = ((old_Rn + nb_reg_x4) - 4);
  address = start_address;
  set_reg(proc,n,(old_Rn + nb_reg_x4));
  size_t i; for (i = 0; i<=7; ++i) {
    if ((get_bit(register_list,i) == 1)) {
      set_reg(proc,i,slv6_read_word(proc->mmu_ptr,address));
      address = (address + 4);
    }
}
}

/* A7.1.57
 * STMIA */
void slv6_X_Tb_STMIA(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t end_address;
  uint32_t physical_address;
  uint32_t processor_id;
  uint32_t start_address;
  processor_id = ExecutingProcessor();
  start_address = old_Rn;
  end_address = ((old_Rn + nb_reg_x4) - 4);
  address = start_address;
  size_t i; for (i = 0; i<=7; ++i) {
    if ((get_bit(register_list,i) == 1)) {
      slv6_write_word(proc->mmu_ptr, address, reg(proc,i));
      if (Shared(address)) {
        physical_address = slv6_TLB(address);
        ClearExclusiveByAddress2(physical_address, 4);
      }
      address = (address + 4);
    }
}
  set_reg(proc,n,(old_Rn + nb_reg_x4));
}

/* A7.1.3
 * ADD (1) */
void slv6_X_Tb_ADD1(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint32_t immed_3)
{
  const uint32_t old_Rn = reg(proc,n);
  set_reg(proc,d,(old_Rn + immed_3));
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
  proc->cpsr.C_flag = CarryFrom_add2(old_Rn, immed_3);
  proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, immed_3);
}

/* A7.1.45
 * MUL */
void slv6_X_Tb_MUL(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m)
{
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,get_bits((to_u64(old_Rm) * to_u64(reg(proc,d))),31,0));
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
}

/* A7.1.11
 * ASR (1) */
void slv6_X_Tb_ASR1(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint32_t immed_5)
{
  const uint32_t old_Rm = reg(proc,m);
  if ((immed_5 == 0)) {
    proc->cpsr.C_flag = get_bit(old_Rm,31);
    if ((get_bit(old_Rm,31) == 0))
      set_reg(proc,d,0);
    else
      set_reg(proc,d,0xFFFFFFFF);
  } else {
    proc->cpsr.C_flag = get_bit(old_Rm,(immed_5 - 1));
    set_reg(proc,d,asr(old_Rm, immed_5));
  }
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
}

/* A7.1.46
 * MVN */
void slv6_X_Tb_MVN(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m)
{
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,~(old_Rm));
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
}

/* A7.1.34
 * LDRH (1) */
void slv6_X_Tb_LDRH1(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint32_t immed_5)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint16_t data;
  address = (old_Rn + (immed_5 * 2));
  if ((!((get_bit(address,0) == 0)) && (CP15_reg1_Ubit(proc->cp15_ptr) == 0)))
    unpredictable("Tb_LDRH1");
  data = slv6_read_half(proc->mmu_ptr,address);
  set_reg(proc,d,ZeroExtend(get_half_0(data)));
}

/* A7.1.72
 * TST */
void slv6_X_Tb_TST(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  alu_out = (old_Rn & old_Rm);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
}

/* A7.1.15
 * BIC */
void slv6_X_Tb_BIC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m)
{
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,(reg(proc,d) & ~(old_Rm)));
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
}

/* A7.1.39
 * LSL (2) */
void slv6_X_Tb_LSL2(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t s)
{
  const uint32_t old_Rs = reg(proc,s);
  if (!((get_byte_0(old_Rs) == 0))) {
    if ((get_byte_0(old_Rs) < 32)) {
      proc->cpsr.C_flag = get_bit(reg(proc,d),(32 - get_byte_0(old_Rs)));
      set_reg(proc,d,(reg(proc,d) << get_byte_0(old_Rs)));
    } else {
      if ((get_byte_0(old_Rs) == 32)) {
        proc->cpsr.C_flag = get_bit(reg(proc,d),0);
        set_reg(proc,d,0);
      } else {
        proc->cpsr.C_flag = 0;
        set_reg(proc,d,0);
      }
    }
  }
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
}

/* A4.1.23--A5.2.2--NC
 * LDR -- Load and Store Word or Unsigned Byte - Immediate offset (no cond) */
void slv6_X_LDR_M2_ImmOff_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint32_t signed_offset_12)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t data;
  address = (old_Rn + signed_offset_12);
  data = ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)? rotate_right(slv6_read_word(proc->mmu_ptr,address), (get_bits(address,1,0) * 8)): slv6_read_word(proc->mmu_ptr,address));
  if ((d == 15)) {
    set_pc_raw_ws(proc,(data & 0xFFFFFFFE),inst_size(proc));
    proc->cpsr.T_flag = get_bit(data,0);
  } else
    set_reg_or_pc_ws(proc,d,data,inst_size(proc));
}

/* A4.1.99--A5.2.2--NC
 * STR -- Load and Store Word or Unsigned Byte - Immediate offset (no cond) */
void slv6_X_STR_M2_ImmOff_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint32_t signed_offset_12)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t physical_address;
  uint32_t processor_id;
  address = (old_Rn + signed_offset_12);
  processor_id = ExecutingProcessor();
  slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
}

/* A4.1.5--NC
 * B, BL (L=1) (no cond) */
void slv6_X_B_L1_NC(struct SLv6_Processor *proc,
    const uint32_t pc_offset)
{
  uint32_t addr_of_next_instr;
  addr_of_next_instr = (reg(proc,15) - 4);
  set_reg(proc,14,addr_of_next_instr);
  set_pc_raw_ws(proc,(reg(proc,15) + pc_offset),4);
}

/* A4.1.5--NC
 * B, BL (L=0) (no cond) */
void slv6_X_B_L0_NC(struct SLv6_Processor *proc,
    const uint32_t pc_offset)
{
  uint32_t addr_of_next_instr;
  addr_of_next_instr = (reg(proc,15) - 4);
  set_pc_raw_ws(proc,(reg(proc,15) + pc_offset),4);
}

/* A4.1.106--A5.1.3--NC
 * SUB -- Data processing operands - Immediate (S=1) (no cond) */
void slv6_X_SUB_M1_Imm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated)
{
  const uint32_t old_Rn = reg(proc,n);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,(old_Rn - shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SUB_M1_Imm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
    proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
  }
}

/* A4.1.106--A5.1.3--NC
 * SUB -- Data processing operands - Immediate (S=0) (no cond) */
void slv6_X_SUB_M1_Imm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated)
{
  const uint32_t old_Rn = reg(proc,n);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,(old_Rn - shifter_operand),4);
}

/* A4.1.15--A5.1.4--NC
 * CMP -- Data processing operands - Register (no cond) */
void slv6_X_CMP_M1_Reg_NC(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = old_Rm;
  shifter_carry_out = proc->cpsr.C_flag;
  alu_out = (old_Rn - shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
  proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
}

/* A4.1.3--A5.1.3--NC
 * ADD -- Data processing operands - Immediate (S=1) (no cond) */
void slv6_X_ADD_M1_Imm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated)
{
  const uint32_t old_Rn = reg(proc,n);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,(old_Rn + shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADD_M1_Imm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
    proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
  }
}

/* A4.1.3--A5.1.3--NC
 * ADD -- Data processing operands - Immediate (S=0) (no cond) */
void slv6_X_ADD_M1_Imm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated)
{
  const uint32_t old_Rn = reg(proc,n);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,(old_Rn + shifter_operand),4);
}

/* A4.1.3--A5.1.4--NC
 * ADD -- Data processing operands - Register (S=1) (no cond) */
void slv6_X_ADD_M1_Reg_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = old_Rm;
  shifter_carry_out = proc->cpsr.C_flag;
  set_reg_or_pc_ws(proc,d,(old_Rn + shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADD_M1_Reg_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
    proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
  }
}

/* A4.1.3--A5.1.4--NC
 * ADD -- Data processing operands - Register (S=0) (no cond) */
void slv6_X_ADD_M1_Reg_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = old_Rm;
  shifter_carry_out = proc->cpsr.C_flag;
  set_reg_or_pc_ws(proc,d,(old_Rn + shifter_operand),4);
}

/* A4.1.18--A5.1.4--NC
 * EOR -- Data processing operands - Register (S=1) (no cond) */
void slv6_X_EOR_M1_Reg_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = old_Rm;
  shifter_carry_out = proc->cpsr.C_flag;
  set_reg_or_pc_ws(proc,d,(old_Rn ^ shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("EOR_M1_Reg_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.18--A5.1.4--NC
 * EOR -- Data processing operands - Register (S=0) (no cond) */
void slv6_X_EOR_M1_Reg_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = old_Rm;
  shifter_carry_out = proc->cpsr.C_flag;
  set_reg_or_pc_ws(proc,d,(old_Rn ^ shifter_operand),4);
}

/* A4.1.4--A5.1.3--NC
 * AND -- Data processing operands - Immediate (S=1) (no cond) */
void slv6_X_AND_M1_Imm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated)
{
  const uint32_t old_Rn = reg(proc,n);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,(old_Rn & shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("AND_M1_Imm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.4--A5.1.3--NC
 * AND -- Data processing operands - Immediate (S=0) (no cond) */
void slv6_X_AND_M1_Imm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated)
{
  const uint32_t old_Rn = reg(proc,n);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,(old_Rn & shifter_operand),4);
}

/* A4.1.35--A5.1.7--NC
 * MOV -- Data processing operands - Logical shift right by immediate (S=1) (no cond) */
void slv6_X_MOV_M1_LSRImm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm)
{
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,shifter_operand,4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MOV_M1_LSRImm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.35--A5.1.7--NC
 * MOV -- Data processing operands - Logical shift right by immediate (S=0) (no cond) */
void slv6_X_MOV_M1_LSRImm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm)
{
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,shifter_operand,4);
}

/* A4.1.17--NC
 * CPY (no cond) */
void slv6_X_CPY_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m)
{
  const uint32_t old_Rm = reg(proc,m);
  set_reg_or_pc_ws(proc,d,old_Rm,4);
}

/* A4.1.35--A5.1.5--NC
 * MOV -- Data processing operands - Logical shift left by immediate (S=1) (no cond) */
void slv6_X_MOV_M1_LSLImm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm)
{
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? old_Rm: (old_Rm << shift_imm));
  shifter_carry_out = ((shift_imm == 0)? proc->cpsr.C_flag: get_bit(old_Rm,(32 - shift_imm)));
  set_reg_or_pc_ws(proc,d,shifter_operand,4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MOV_M1_LSLImm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.35--A5.1.5--NC
 * MOV -- Data processing operands - Logical shift left by immediate (S=0) (no cond) */
void slv6_X_MOV_M1_LSLImm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm)
{
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? old_Rm: (old_Rm << shift_imm));
  shifter_carry_out = ((shift_imm == 0)? proc->cpsr.C_flag: get_bit(old_Rm,(32 - shift_imm)));
  set_reg_or_pc_ws(proc,d,shifter_operand,4);
}

/* A4.1.35--A5.1.3--NC
 * MOV -- Data processing operands - Immediate (S=1) (no cond) */
void slv6_X_MOV_M1_Imm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated)
{
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,shifter_operand,4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MOV_M1_Imm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.35--A5.1.3--NC
 * MOV -- Data processing operands - Immediate (S=0) (no cond) */
void slv6_X_MOV_M1_Imm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated)
{
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,shifter_operand,4);
}

/* A4.1.20--A5.4.2--NC
 * LDM (1) -- Load and Store Multiple - Increment after (W=1) (no cond) */
void slv6_X_LDM1_M4_IA_W1_NC(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list)
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
  end_address = ((old_Rn + nb_reg_x4) - 4);
  new_Rn = (old_Rn + nb_reg_x4);
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
  set_reg(proc,n,new_Rn);
}

/* A4.1.20--A5.4.2--NC
 * LDM (1) -- Load and Store Multiple - Increment after (W=0) (no cond) */
void slv6_X_LDM1_M4_IA_W0_NC(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list)
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
  end_address = ((old_Rn + nb_reg_x4) - 4);
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
}

/* A4.1.15--A5.1.3--NC
 * CMP -- Data processing operands - Immediate (no cond) */
void slv6_X_CMP_M1_Imm_NC(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  alu_out = (old_Rn - shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
  proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
}

/* A4.1.23--A5.2.4--NC
 * LDR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) (no cond) */
void slv6_X_LDR_M2_ScRegOff_U1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t data;
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
  address = (old_Rn + index);
  data = ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)? rotate_right(slv6_read_word(proc->mmu_ptr,address), (get_bits(address,1,0) * 8)): slv6_read_word(proc->mmu_ptr,address));
  if ((d == 15)) {
    set_pc_raw_ws(proc,(data & 0xFFFFFFFE),inst_size(proc));
    proc->cpsr.T_flag = get_bit(data,0);
  } else
    set_reg_or_pc_ws(proc,d,data,inst_size(proc));
}

/* A4.1.23--A5.2.4--NC
 * LDR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) (no cond) */
void slv6_X_LDR_M2_ScRegOff_U0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t data;
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
  address = (old_Rn - index);
  data = ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)? rotate_right(slv6_read_word(proc->mmu_ptr,address), (get_bits(address,1,0) * 8)): slv6_read_word(proc->mmu_ptr,address));
  if ((d == 15)) {
    set_pc_raw_ws(proc,(data & 0xFFFFFFFE),inst_size(proc));
    proc->cpsr.T_flag = get_bit(data,0);
  } else
    set_reg_or_pc_ws(proc,d,data,inst_size(proc));
}

/* A4.1.10--NC
 * BX (no cond) */
void slv6_X_BX_NC(struct SLv6_Processor *proc,
    const uint8_t m)
{
  const uint32_t old_Rm = reg(proc,m);
  proc->cpsr.T_flag = get_bit(old_Rm,0);
  set_pc_raw_ws(proc,(old_Rm & 0xFFFFFFFE),inst_size(proc));
}

/* A4.1.3--A5.1.5--NC
 * ADD -- Data processing operands - Logical shift left by immediate (S=1) (no cond) */
void slv6_X_ADD_M1_LSLImm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? old_Rm: (old_Rm << shift_imm));
  shifter_carry_out = ((shift_imm == 0)? proc->cpsr.C_flag: get_bit(old_Rm,(32 - shift_imm)));
  set_reg_or_pc_ws(proc,d,(old_Rn + shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADD_M1_LSLImm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
    proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
  }
}

/* A4.1.3--A5.1.5--NC
 * ADD -- Data processing operands - Logical shift left by immediate (S=0) (no cond) */
void slv6_X_ADD_M1_LSLImm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? old_Rm: (old_Rm << shift_imm));
  shifter_carry_out = ((shift_imm == 0)? proc->cpsr.C_flag: get_bit(old_Rm,(32 - shift_imm)));
  set_reg_or_pc_ws(proc,d,(old_Rn + shifter_operand),4);
}

/* A4.1.24--A5.2.2--NC
 * LDRB -- Load and Store Word or Unsigned Byte - Immediate offset (no cond) */
void slv6_X_LDRB_M2_ImmOff_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint32_t signed_offset_12)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  address = (old_Rn + signed_offset_12);
  set_reg(proc,d,slv6_read_byte(proc->mmu_ptr,address));
}

/* A4.1.42--A5.1.4--NC
 * ORR -- Data processing operands - Register (S=1) (no cond) */
void slv6_X_ORR_M1_Reg_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = old_Rm;
  shifter_carry_out = proc->cpsr.C_flag;
  set_reg_or_pc_ws(proc,d,(old_Rn | shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ORR_M1_Reg_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.42--A5.1.4--NC
 * ORR -- Data processing operands - Register (S=0) (no cond) */
void slv6_X_ORR_M1_Reg_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = old_Rm;
  shifter_carry_out = proc->cpsr.C_flag;
  set_reg_or_pc_ws(proc,d,(old_Rn | shifter_operand),4);
}

/* A4.1.35--A5.1.11--NC
 * MOV -- Data processing operands - Rotate right by immediate (S=1) (no cond) */
void slv6_X_MOV_M1_RRImm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm)
{
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,0): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,shifter_operand,4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MOV_M1_RRImm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.35--A5.1.11--NC
 * MOV -- Data processing operands - Rotate right by immediate (S=0) (no cond) */
void slv6_X_MOV_M1_RRImm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm)
{
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,0): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,shifter_operand,4);
}

/* A4.1.23--A5.2.8--NC
 * LDR -- Load and Store Word or Unsigned Byte - Immediate post indexed (no cond) */
void slv6_X_LDR_M2_Imm_postInd_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint32_t signed_offset_12)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t data;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = old_Rn;
  new_Rn = (old_Rn + signed_offset_12);
  data = ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)? rotate_right(slv6_read_word(proc->mmu_ptr,address), (get_bits(address,1,0) * 8)): slv6_read_word(proc->mmu_ptr,address));
  if ((d == 15)) {
    set_pc_raw_ws(proc,(data & 0xFFFFFFFE),inst_size(proc));
    proc->cpsr.T_flag = get_bit(data,0);
  } else
    set_reg_or_pc_ws(proc,d,data,inst_size(proc));
  set_reg(proc,n,new_Rn);
}

/* A4.1.18--A5.1.11--NC
 * EOR -- Data processing operands - Rotate right by immediate (S=1) (no cond) */
void slv6_X_EOR_M1_RRImm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,0): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn ^ shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("EOR_M1_RRImm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.18--A5.1.11--NC
 * EOR -- Data processing operands - Rotate right by immediate (S=0) (no cond) */
void slv6_X_EOR_M1_RRImm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,0): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn ^ shifter_operand),4);
}

/* A4.1.4--A5.1.4--NC
 * AND -- Data processing operands - Register (S=1) (no cond) */
void slv6_X_AND_M1_Reg_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = old_Rm;
  shifter_carry_out = proc->cpsr.C_flag;
  set_reg_or_pc_ws(proc,d,(old_Rn & shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("AND_M1_Reg_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.4--A5.1.4--NC
 * AND -- Data processing operands - Register (S=0) (no cond) */
void slv6_X_AND_M1_Reg_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = old_Rm;
  shifter_carry_out = proc->cpsr.C_flag;
  set_reg_or_pc_ws(proc,d,(old_Rn & shifter_operand),4);
}

/* A4.1.99--A5.2.5--NC
 * STR -- Load and Store Word or Unsigned Byte - Immediate pre indexed (no cond) */
void slv6_X_STR_M2_Imm_preInd_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint32_t signed_offset_12)
{
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
  slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.100--A5.2.2--NC
 * STRB -- Load and Store Word or Unsigned Byte - Immediate offset (no cond) */
void slv6_X_STRB_M2_ImmOff_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint32_t signed_offset_12)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t physical_address;
  uint32_t processor_id;
  address = (old_Rn + signed_offset_12);
  processor_id = ExecutingProcessor();
  slv6_write_byte(proc->mmu_ptr, address, get_byte_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 1);
  }
}

/* A4.1.42--A5.1.5--NC
 * ORR -- Data processing operands - Logical shift left by immediate (S=1) (no cond) */
void slv6_X_ORR_M1_LSLImm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? old_Rm: (old_Rm << shift_imm));
  shifter_carry_out = ((shift_imm == 0)? proc->cpsr.C_flag: get_bit(old_Rm,(32 - shift_imm)));
  set_reg_or_pc_ws(proc,d,(old_Rn | shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ORR_M1_LSLImm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.42--A5.1.5--NC
 * ORR -- Data processing operands - Logical shift left by immediate (S=0) (no cond) */
void slv6_X_ORR_M1_LSLImm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? old_Rm: (old_Rm << shift_imm));
  shifter_carry_out = ((shift_imm == 0)? proc->cpsr.C_flag: get_bit(old_Rm,(32 - shift_imm)));
  set_reg_or_pc_ws(proc,d,(old_Rn | shifter_operand),4);
}

/* A4.1.2--A5.1.4--NC
 * ADC -- Data processing operands - Register (S=1) (no cond) */
void slv6_X_ADC_M1_Reg_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = old_Rm;
  shifter_carry_out = proc->cpsr.C_flag;
  set_reg_or_pc_ws(proc,d,((old_Rn + shifter_operand) + proc->cpsr.C_flag),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADC_M1_Reg_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = CarryFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
    proc->cpsr.V_flag = OverflowFrom_add3(old_Rn, shifter_operand, proc->cpsr.C_flag);
  }
}

/* A4.1.2--A5.1.4--NC
 * ADC -- Data processing operands - Register (S=0) (no cond) */
void slv6_X_ADC_M1_Reg_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = old_Rm;
  shifter_carry_out = proc->cpsr.C_flag;
  set_reg_or_pc_ws(proc,d,((old_Rn + shifter_operand) + proc->cpsr.C_flag),4);
}

/* A4.1.24--A5.2.3--NC
 * LDRB -- Load and Store Word or Unsigned Byte - Register offset (U=1) (no cond) */
void slv6_X_LDRB_M2_RegOff_U1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  address = (old_Rn + old_Rm);
  set_reg(proc,d,slv6_read_byte(proc->mmu_ptr,address));
}

/* A4.1.24--A5.2.3--NC
 * LDRB -- Load and Store Word or Unsigned Byte - Register offset (U=0) (no cond) */
void slv6_X_LDRB_M2_RegOff_U0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  address = (old_Rn - old_Rm);
  set_reg(proc,d,slv6_read_byte(proc->mmu_ptr,address));
}

/* A4.1.60--A5.1.4--NC
 * RSB -- Data processing operands - Register (S=1) (no cond) */
void slv6_X_RSB_M1_Reg_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = old_Rm;
  shifter_carry_out = proc->cpsr.C_flag;
  set_reg_or_pc_ws(proc,d,(shifter_operand - old_Rn),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSB_M1_Reg_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = !(BorrowFrom_sub2(shifter_operand, old_Rn));
    proc->cpsr.V_flag = OverflowFrom_sub2(shifter_operand, old_Rn);
  }
}

/* A4.1.60--A5.1.4--NC
 * RSB -- Data processing operands - Register (S=0) (no cond) */
void slv6_X_RSB_M1_Reg_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = old_Rm;
  shifter_carry_out = proc->cpsr.C_flag;
  set_reg_or_pc_ws(proc,d,(shifter_operand - old_Rn),4);
}

/* A4.1.6--A5.1.3--NC
 * BIC -- Data processing operands - Immediate (S=1) (no cond) */
void slv6_X_BIC_M1_Imm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated)
{
  const uint32_t old_Rn = reg(proc,n);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,(old_Rn & ~(shifter_operand)),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("BIC_M1_Imm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.6--A5.1.3--NC
 * BIC -- Data processing operands - Immediate (S=0) (no cond) */
void slv6_X_BIC_M1_Imm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated)
{
  const uint32_t old_Rn = reg(proc,n);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,(old_Rn & ~(shifter_operand)),4);
}

/* A4.1.41--A5.1.3--NC
 * MVN -- Data processing operands - Immediate (S=1) (no cond) */
void slv6_X_MVN_M1_Imm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated)
{
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,~(shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MVN_M1_Imm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.41--A5.1.3--NC
 * MVN -- Data processing operands - Immediate (S=0) (no cond) */
void slv6_X_MVN_M1_Imm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated)
{
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,~(shifter_operand),4);
}

/* A4.1.42--A5.1.7--NC
 * ORR -- Data processing operands - Logical shift right by immediate (S=1) (no cond) */
void slv6_X_ORR_M1_LSRImm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn | shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ORR_M1_LSRImm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.42--A5.1.7--NC
 * ORR -- Data processing operands - Logical shift right by immediate (S=0) (no cond) */
void slv6_X_ORR_M1_LSRImm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn | shifter_operand),4);
}

/* A4.1.18--A5.1.7--NC
 * EOR -- Data processing operands - Logical shift right by immediate (S=1) (no cond) */
void slv6_X_EOR_M1_LSRImm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn ^ shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("EOR_M1_LSRImm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.18--A5.1.7--NC
 * EOR -- Data processing operands - Logical shift right by immediate (S=0) (no cond) */
void slv6_X_EOR_M1_LSRImm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn ^ shifter_operand),4);
}

/* A4.1.23--A5.2.3--NC
 * LDR -- Load and Store Word or Unsigned Byte - Register offset (U=1) (no cond) */
void slv6_X_LDR_M2_RegOff_U1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t data;
  address = (old_Rn + old_Rm);
  data = ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)? rotate_right(slv6_read_word(proc->mmu_ptr,address), (get_bits(address,1,0) * 8)): slv6_read_word(proc->mmu_ptr,address));
  if ((d == 15)) {
    set_pc_raw_ws(proc,(data & 0xFFFFFFFE),inst_size(proc));
    proc->cpsr.T_flag = get_bit(data,0);
  } else
    set_reg_or_pc_ws(proc,d,data,inst_size(proc));
}

/* A4.1.23--A5.2.3--NC
 * LDR -- Load and Store Word or Unsigned Byte - Register offset (U=0) (no cond) */
void slv6_X_LDR_M2_RegOff_U0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t data;
  address = (old_Rn - old_Rm);
  data = ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)? rotate_right(slv6_read_word(proc->mmu_ptr,address), (get_bits(address,1,0) * 8)): slv6_read_word(proc->mmu_ptr,address));
  if ((d == 15)) {
    set_pc_raw_ws(proc,(data & 0xFFFFFFFE),inst_size(proc));
    proc->cpsr.T_flag = get_bit(data,0);
  } else
    set_reg_or_pc_ws(proc,d,data,inst_size(proc));
}

/* A4.1.35--A5.1.8--NC
 * MOV -- Data processing operands - Logical shift right by register (S=1) (no cond) */
void slv6_X_MOV_M1_LSRReg_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s)
{
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm >> get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,31): 0)));
  set_reg(proc,d,shifter_operand);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MOV_M1_LSRReg_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.35--A5.1.8--NC
 * MOV -- Data processing operands - Logical shift right by register (S=0) (no cond) */
void slv6_X_MOV_M1_LSRReg_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s)
{
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm >> get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(get_byte_0(old_Rs) - 1)): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,31): 0)));
  set_reg(proc,d,shifter_operand);
}

/* A4.1.100--A5.2.3--NC
 * STRB -- Load and Store Word or Unsigned Byte - Register offset (U=1) (no cond) */
void slv6_X_STRB_M2_RegOff_U1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t physical_address;
  uint32_t processor_id;
  address = (old_Rn + old_Rm);
  processor_id = ExecutingProcessor();
  slv6_write_byte(proc->mmu_ptr, address, get_byte_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 1);
  }
}

/* A4.1.100--A5.2.3--NC
 * STRB -- Load and Store Word or Unsigned Byte - Register offset (U=0) (no cond) */
void slv6_X_STRB_M2_RegOff_U0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t physical_address;
  uint32_t processor_id;
  address = (old_Rn - old_Rm);
  processor_id = ExecutingProcessor();
  slv6_write_byte(proc->mmu_ptr, address, get_byte_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 1);
  }
}

/* A4.1.99--A5.2.4--NC
 * STR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) (no cond) */
void slv6_X_STR_M2_ScRegOff_U1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm)
{
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
  address = (old_Rn + index);
  processor_id = ExecutingProcessor();
  slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
}

/* A4.1.99--A5.2.4--NC
 * STR -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) (no cond) */
void slv6_X_STR_M2_ScRegOff_U0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift,
    const uint8_t shift_imm)
{
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
  address = (old_Rn - index);
  processor_id = ExecutingProcessor();
  slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
}

/* A4.1.14--A5.1.4--NC
 * CMN -- Data processing operands - Register (no cond) */
void slv6_X_CMN_M1_Reg_NC(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = old_Rm;
  shifter_carry_out = proc->cpsr.C_flag;
  alu_out = (old_Rn + shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
  proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
}

/* A4.1.99--A5.2.9--NC
 * STR -- Load and Store Word or Unsigned Byte - Register post indexed (U=1) (no cond) */
void slv6_X_STR_M2_Reg_postInd_U1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
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
  new_Rn = (old_Rn + old_Rm);
  processor_id = ExecutingProcessor();
  slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.99--A5.2.9--NC
 * STR -- Load and Store Word or Unsigned Byte - Register post indexed (U=0) (no cond) */
void slv6_X_STR_M2_Reg_postInd_U0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
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
  new_Rn = (old_Rn - old_Rm);
  processor_id = ExecutingProcessor();
  slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.99--A5.2.3--NC
 * STR -- Load and Store Word or Unsigned Byte - Register offset (U=1) (no cond) */
void slv6_X_STR_M2_RegOff_U1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t physical_address;
  uint32_t processor_id;
  address = (old_Rn + old_Rm);
  processor_id = ExecutingProcessor();
  slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
}

/* A4.1.99--A5.2.3--NC
 * STR -- Load and Store Word or Unsigned Byte - Register offset (U=0) (no cond) */
void slv6_X_STR_M2_RegOff_U0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t address;
  uint32_t physical_address;
  uint32_t processor_id;
  address = (old_Rn - old_Rm);
  processor_id = ExecutingProcessor();
  slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
}

/* A4.1.18--A5.1.5--NC
 * EOR -- Data processing operands - Logical shift left by immediate (S=1) (no cond) */
void slv6_X_EOR_M1_LSLImm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? old_Rm: (old_Rm << shift_imm));
  shifter_carry_out = ((shift_imm == 0)? proc->cpsr.C_flag: get_bit(old_Rm,(32 - shift_imm)));
  set_reg_or_pc_ws(proc,d,(old_Rn ^ shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("EOR_M1_LSLImm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.18--A5.1.5--NC
 * EOR -- Data processing operands - Logical shift left by immediate (S=0) (no cond) */
void slv6_X_EOR_M1_LSLImm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? old_Rm: (old_Rm << shift_imm));
  shifter_carry_out = ((shift_imm == 0)? proc->cpsr.C_flag: get_bit(old_Rm,(32 - shift_imm)));
  set_reg_or_pc_ws(proc,d,(old_Rn ^ shifter_operand),4);
}

/* A4.1.60--A5.1.3--NC
 * RSB -- Data processing operands - Immediate (S=1) (no cond) */
void slv6_X_RSB_M1_Imm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated)
{
  const uint32_t old_Rn = reg(proc,n);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,(shifter_operand - old_Rn),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSB_M1_Imm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = !(BorrowFrom_sub2(shifter_operand, old_Rn));
    proc->cpsr.V_flag = OverflowFrom_sub2(shifter_operand, old_Rn);
  }
}

/* A4.1.60--A5.1.3--NC
 * RSB -- Data processing operands - Immediate (S=0) (no cond) */
void slv6_X_RSB_M1_Imm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated)
{
  const uint32_t old_Rn = reg(proc,n);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,(shifter_operand - old_Rn),4);
}

/* A4.1.35--A5.1.9--NC
 * MOV -- Data processing operands - Arithmetic shift right by immediate (S=1) (no cond) */
void slv6_X_MOV_M1_ASRImm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm)
{
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF): asr(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,shifter_operand,4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MOV_M1_ASRImm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.35--A5.1.9--NC
 * MOV -- Data processing operands - Arithmetic shift right by immediate (S=0) (no cond) */
void slv6_X_MOV_M1_ASRImm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t shift_imm)
{
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF): asr(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,shifter_operand,4);
}

/* A4.1.3--A5.1.11--NC
 * ADD -- Data processing operands - Rotate right by immediate (S=1) (no cond) */
void slv6_X_ADD_M1_RRImm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,0): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn + shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADD_M1_RRImm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
    proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
  }
}

/* A4.1.3--A5.1.11--NC
 * ADD -- Data processing operands - Rotate right by immediate (S=0) (no cond) */
void slv6_X_ADD_M1_RRImm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((proc->cpsr.C_flag << 31) | (old_Rm >> 1)): rotate_right(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,0): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn + shifter_operand),4);
}

/* A4.1.60--A5.1.5--NC
 * RSB -- Data processing operands - Logical shift left by immediate (S=1) (no cond) */
void slv6_X_RSB_M1_LSLImm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? old_Rm: (old_Rm << shift_imm));
  shifter_carry_out = ((shift_imm == 0)? proc->cpsr.C_flag: get_bit(old_Rm,(32 - shift_imm)));
  set_reg_or_pc_ws(proc,d,(shifter_operand - old_Rn),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSB_M1_LSLImm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = !(BorrowFrom_sub2(shifter_operand, old_Rn));
    proc->cpsr.V_flag = OverflowFrom_sub2(shifter_operand, old_Rn);
  }
}

/* A4.1.60--A5.1.5--NC
 * RSB -- Data processing operands - Logical shift left by immediate (S=0) (no cond) */
void slv6_X_RSB_M1_LSLImm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? old_Rm: (old_Rm << shift_imm));
  shifter_carry_out = ((shift_imm == 0)? proc->cpsr.C_flag: get_bit(old_Rm,(32 - shift_imm)));
  set_reg_or_pc_ws(proc,d,(shifter_operand - old_Rn),4);
}

/* A4.1.100--A5.2.8--NC
 * STRB -- Load and Store Word or Unsigned Byte - Immediate post indexed (no cond) */
void slv6_X_STRB_M2_Imm_postInd_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint32_t signed_offset_12)
{
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
  slv6_write_byte(proc->mmu_ptr, address, get_byte_0(reg(proc,d)));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 1);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.97--A5.4.2--NC
 * STM (1) -- Load and Store Multiple - Increment after (W=1) (no cond) */
void slv6_X_STM1_M4_IA_W1_NC(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list)
{
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
  end_address = ((old_Rn + nb_reg_x4) - 4);
  new_Rn = (old_Rn + nb_reg_x4);
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
  set_reg(proc,n,new_Rn);
}

/* A4.1.97--A5.4.2--NC
 * STM (1) -- Load and Store Multiple - Increment after (W=0) (no cond) */
void slv6_X_STM1_M4_IA_W0_NC(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list)
{
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
  end_address = ((old_Rn + nb_reg_x4) - 4);
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
}

/* A4.1.117--A5.1.3--NC
 * TST -- Data processing operands - Immediate (no cond) */
void slv6_X_TST_M1_Imm_NC(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  alu_out = (old_Rn & shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.97--A5.4.5--NC
 * STM (1) -- Load and Store Multiple - Decrement before (W=1) (no cond) */
void slv6_X_STM1_M4_DB_W1_NC(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list)
{
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
  start_address = (old_Rn - nb_reg_x4);
  end_address = (old_Rn - 4);
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
  set_reg(proc,n,new_Rn);
}

/* A4.1.97--A5.4.5--NC
 * STM (1) -- Load and Store Multiple - Decrement before (W=0) (no cond) */
void slv6_X_STM1_M4_DB_W0_NC(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list)
{
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
  start_address = (old_Rn - nb_reg_x4);
  end_address = (old_Rn - 4);
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
}

/* A4.1.41--A5.1.4--NC
 * MVN -- Data processing operands - Register (S=1) (no cond) */
void slv6_X_MVN_M1_Reg_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m)
{
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = old_Rm;
  shifter_carry_out = proc->cpsr.C_flag;
  set_reg_or_pc_ws(proc,d,~(shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MVN_M1_Reg_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.41--A5.1.4--NC
 * MVN -- Data processing operands - Register (S=0) (no cond) */
void slv6_X_MVN_M1_Reg_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m)
{
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = old_Rm;
  shifter_carry_out = proc->cpsr.C_flag;
  set_reg_or_pc_ws(proc,d,~(shifter_operand),4);
}

/* A4.1.97--A5.4.3--NC
 * STM (1) -- Load and Store Multiple - Increment before (W=1) (no cond) */
void slv6_X_STM1_M4_IB_W1_NC(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list)
{
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
  end_address = (old_Rn + nb_reg_x4);
  new_Rn = (old_Rn + nb_reg_x4);
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
  set_reg(proc,n,new_Rn);
}

/* A4.1.97--A5.4.3--NC
 * STM (1) -- Load and Store Multiple - Increment before (W=0) (no cond) */
void slv6_X_STM1_M4_IB_W0_NC(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list)
{
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
  end_address = (old_Rn + nb_reg_x4);
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
}

/* A4.1.3--A5.1.7--NC
 * ADD -- Data processing operands - Logical shift right by immediate (S=1) (no cond) */
void slv6_X_ADD_M1_LSRImm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn + shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ADD_M1_LSRImm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
    proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
  }
}

/* A4.1.3--A5.1.7--NC
 * ADD -- Data processing operands - Logical shift right by immediate (S=0) (no cond) */
void slv6_X_ADD_M1_LSRImm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? 0: (old_Rm >> shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn + shifter_operand),4);
}

/* A4.1.99--A5.2.8--NC
 * STR -- Load and Store Word or Unsigned Byte - Immediate post indexed (no cond) */
void slv6_X_STR_M2_Imm_postInd_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint32_t signed_offset_12)
{
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
  slv6_write_word(proc->mmu_ptr, address, reg(proc,d));
  if (Shared(address)) {
    physical_address = slv6_TLB(address);
    ClearExclusiveByAddress3(physical_address, processor_id, 4);
  }
  set_reg(proc,n,new_Rn);
}

/* A4.1.24--A5.2.4--NC
 * LDRB -- Load and Store Word or Unsigned Byte - Scaled register offset (U=1) (no cond) */
void slv6_X_LDRB_M2_ScRegOff_U1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
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
  address = (old_Rn + index);
  set_reg(proc,d,slv6_read_byte(proc->mmu_ptr,address));
}

/* A4.1.24--A5.2.4--NC
 * LDRB -- Load and Store Word or Unsigned Byte - Scaled register offset (U=0) (no cond) */
void slv6_X_LDRB_M2_ScRegOff_U0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
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
  address = (old_Rn - index);
  set_reg(proc,d,slv6_read_byte(proc->mmu_ptr,address));
}

/* A4.1.106--A5.1.5--NC
 * SUB -- Data processing operands - Logical shift left by immediate (S=1) (no cond) */
void slv6_X_SUB_M1_LSLImm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? old_Rm: (old_Rm << shift_imm));
  shifter_carry_out = ((shift_imm == 0)? proc->cpsr.C_flag: get_bit(old_Rm,(32 - shift_imm)));
  set_reg_or_pc_ws(proc,d,(old_Rn - shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SUB_M1_LSLImm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
    proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
  }
}

/* A4.1.106--A5.1.5--NC
 * SUB -- Data processing operands - Logical shift left by immediate (S=0) (no cond) */
void slv6_X_SUB_M1_LSLImm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? old_Rm: (old_Rm << shift_imm));
  shifter_carry_out = ((shift_imm == 0)? proc->cpsr.C_flag: get_bit(old_Rm,(32 - shift_imm)));
  set_reg_or_pc_ws(proc,d,(old_Rn - shifter_operand),4);
}

/* A4.1.20--A5.4.3--NC
 * LDM (1) -- Load and Store Multiple - Increment before (W=1) (no cond) */
void slv6_X_LDM1_M4_IB_W1_NC(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list)
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
  end_address = (old_Rn + nb_reg_x4);
  new_Rn = (old_Rn + nb_reg_x4);
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
  set_reg(proc,n,new_Rn);
}

/* A4.1.20--A5.4.3--NC
 * LDM (1) -- Load and Store Multiple - Increment before (W=0) (no cond) */
void slv6_X_LDM1_M4_IB_W0_NC(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t nb_reg_x4,
    const uint32_t register_list)
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
  end_address = (old_Rn + nb_reg_x4);
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
}

/* A4.1.28--A5.3.2--NC
 * LDRH -- Miscellaneous Loads and Stores - Immediate offset (U=1) (no cond) */
void slv6_X_LDRH_M3_ImmOff_U1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint16_t data;
  uint8_t offset_8;
  offset_8 = immedHL;
  address = (old_Rn + offset_8);
  if ((!((get_bit(address,0) == 0)) && (CP15_reg1_Ubit(proc->cp15_ptr) == 0)))
    unpredictable("LDRH_M3_ImmOff_U1_NC");
  data = slv6_read_half(proc->mmu_ptr,address);
  set_reg(proc,d,ZeroExtend(get_half_0(data)));
}

/* A4.1.28--A5.3.2--NC
 * LDRH -- Miscellaneous Loads and Stores - Immediate offset (U=0) (no cond) */
void slv6_X_LDRH_M3_ImmOff_U0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint8_t immedHL)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint16_t data;
  uint8_t offset_8;
  offset_8 = immedHL;
  address = (old_Rn - offset_8);
  if ((!((get_bit(address,0) == 0)) && (CP15_reg1_Ubit(proc->cp15_ptr) == 0)))
    unpredictable("LDRH_M3_ImmOff_U0_NC");
  data = slv6_read_half(proc->mmu_ptr,address);
  set_reg(proc,d,ZeroExtend(get_half_0(data)));
}

/* A4.1.23--A5.2.5--NC
 * LDR -- Load and Store Word or Unsigned Byte - Immediate pre indexed (no cond) */
void slv6_X_LDR_M2_Imm_preInd_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint32_t signed_offset_12)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t data;
  uint32_t new_Rn;
  SLv6_Mode old_mode;
  new_Rn = 0xBAD;
  old_mode = get_current_mode(proc);
  address = (old_Rn + signed_offset_12);
  new_Rn = address;
  data = ((CP15_reg1_Ubit(proc->cp15_ptr) == 0)? rotate_right(slv6_read_word(proc->mmu_ptr,address), (get_bits(address,1,0) * 8)): slv6_read_word(proc->mmu_ptr,address));
  if ((d == 15)) {
    set_pc_raw_ws(proc,(data & 0xFFFFFFFE),inst_size(proc));
    proc->cpsr.T_flag = get_bit(data,0);
  } else
    set_reg_or_pc_ws(proc,d,data,inst_size(proc));
  set_reg(proc,n,new_Rn);
}

/* A4.1.87--NC
 * SMULL (S=1) (no cond) */
void slv6_X_SMULL_S1_NC(struct SLv6_Processor *proc,
    const uint8_t dHi,
    const uint8_t dLo,
    const uint8_t m,
    const uint8_t s)
{
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  const uint32_t old_RdLo = reg(proc,dLo);
  set_reg(proc,dHi,get_bits((to_i64(old_Rm) * to_i64(old_Rs)),63,32));
  set_reg(proc,dLo,get_bits((to_i64(old_Rm) * to_i64(old_Rs)),31,0));
  proc->cpsr.N_flag = get_bit(reg(proc,dHi),31);
  proc->cpsr.Z_flag = (((reg(proc,dHi) == 0) && (old_RdLo == 0))? 1: 0);
}

/* A4.1.87--NC
 * SMULL (S=0) (no cond) */
void slv6_X_SMULL_S0_NC(struct SLv6_Processor *proc,
    const uint8_t dHi,
    const uint8_t dLo,
    const uint8_t m,
    const uint8_t s)
{
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  const uint32_t old_RdLo = reg(proc,dLo);
  set_reg(proc,dHi,get_bits((to_i64(old_Rm) * to_i64(old_Rs)),63,32));
  set_reg(proc,dLo,get_bits((to_i64(old_Rm) * to_i64(old_Rs)),31,0));
}

/* A4.1.60--A5.1.9--NC
 * RSB -- Data processing operands - Arithmetic shift right by immediate (S=1) (no cond) */
void slv6_X_RSB_M1_ASRImm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF): asr(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(shifter_operand - old_Rn),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("RSB_M1_ASRImm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = !(BorrowFrom_sub2(shifter_operand, old_Rn));
    proc->cpsr.V_flag = OverflowFrom_sub2(shifter_operand, old_Rn);
  }
}

/* A4.1.60--A5.1.9--NC
 * RSB -- Data processing operands - Arithmetic shift right by immediate (S=0) (no cond) */
void slv6_X_RSB_M1_ASRImm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF): asr(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(shifter_operand - old_Rn),4);
}

/* A4.1.117--A5.1.4--NC
 * TST -- Data processing operands - Register (no cond) */
void slv6_X_TST_M1_Reg_NC(struct SLv6_Processor *proc,
    const uint8_t m,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = old_Rm;
  shifter_carry_out = proc->cpsr.C_flag;
  alu_out = (old_Rn & shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = shifter_carry_out;
}

/* A4.1.18--A5.1.3--NC
 * EOR -- Data processing operands - Immediate (S=1) (no cond) */
void slv6_X_EOR_M1_Imm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated)
{
  const uint32_t old_Rn = reg(proc,n);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,(old_Rn ^ shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("EOR_M1_Imm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.18--A5.1.3--NC
 * EOR -- Data processing operands - Immediate (S=0) (no cond) */
void slv6_X_EOR_M1_Imm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated)
{
  const uint32_t old_Rn = reg(proc,n);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,(old_Rn ^ shifter_operand),4);
}

/* A4.1.42--A5.1.9--NC
 * ORR -- Data processing operands - Arithmetic shift right by immediate (S=1) (no cond) */
void slv6_X_ORR_M1_ASRImm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF): asr(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn | shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ORR_M1_ASRImm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.42--A5.1.9--NC
 * ORR -- Data processing operands - Arithmetic shift right by immediate (S=0) (no cond) */
void slv6_X_ORR_M1_ASRImm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF): asr(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn | shifter_operand),4);
}

/* A4.1.42--A5.1.3--NC
 * ORR -- Data processing operands - Immediate (S=1) (no cond) */
void slv6_X_ORR_M1_Imm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated)
{
  const uint32_t old_Rn = reg(proc,n);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,(old_Rn | shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("ORR_M1_Imm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.42--A5.1.3--NC
 * ORR -- Data processing operands - Immediate (S=0) (no cond) */
void slv6_X_ORR_M1_Imm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated)
{
  const uint32_t old_Rn = reg(proc,n);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  set_reg_or_pc_ws(proc,d,(old_Rn | shifter_operand),4);
}

/* A4.1.106--A5.1.9--NC
 * SUB -- Data processing operands - Arithmetic shift right by immediate (S=1) (no cond) */
void slv6_X_SUB_M1_ASRImm_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF): asr(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn - shifter_operand),4);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("SUB_M1_ASRImm_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = !(BorrowFrom_sub2(old_Rn, shifter_operand));
    proc->cpsr.V_flag = OverflowFrom_sub2(old_Rn, shifter_operand);
  }
}

/* A4.1.106--A5.1.9--NC
 * SUB -- Data processing operands - Arithmetic shift right by immediate (S=0) (no cond) */
void slv6_X_SUB_M1_ASRImm_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t n,
    const uint8_t shift_imm)
{
  const uint32_t old_Rn = reg(proc,n);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((shift_imm == 0)? ((get_bit(old_Rm,31) == 0)? 0: 0xFFFFFFFF): asr(old_Rm, shift_imm));
  shifter_carry_out = ((shift_imm == 0)? get_bit(old_Rm,31): get_bit(old_Rm,(shift_imm - 1)));
  set_reg_or_pc_ws(proc,d,(old_Rn - shifter_operand),4);
}

/* A4.1.35--A5.1.6--NC
 * MOV -- Data processing operands - Logical shift left by register (S=1) (no cond) */
void slv6_X_MOV_M1_LSLReg_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s)
{
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm << get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(32 - get_byte_0(old_Rs))): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,0): 0)));
  set_reg(proc,d,shifter_operand);
  if ((d == 15)) {
    if (CurrentModeHasSPSR(proc))
      set_cpsr_sr(proc, *spsr(proc));
    else
      unpredictable("MOV_M1_LSLReg_S1_NC");
  } else {
    proc->cpsr.N_flag = get_bit(reg(proc,d),31);
    proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
    proc->cpsr.C_flag = shifter_carry_out;
  }
}

/* A4.1.35--A5.1.6--NC
 * MOV -- Data processing operands - Logical shift left by register (S=0) (no cond) */
void slv6_X_MOV_M1_LSLReg_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s)
{
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = ((get_byte_0(old_Rs) == 0)? old_Rm: ((get_byte_0(old_Rs) < 32)? (old_Rm << get_byte_0(old_Rs)): 0));
  shifter_carry_out = ((get_byte_0(old_Rs) == 0)? proc->cpsr.C_flag: ((get_byte_0(old_Rs) < 32)? get_bit(old_Rm,(32 - get_byte_0(old_Rs))): ((get_byte_0(old_Rs) == 32)? get_bit(old_Rm,0): 0)));
  set_reg(proc,d,shifter_operand);
}

/* A4.1.40--NC
 * MUL (S=1) (no cond) */
void slv6_X_MUL_S1_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s)
{
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,get_bits((to_u64(old_Rm) * to_u64(old_Rs)),31,0));
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
}

/* A4.1.40--NC
 * MUL (S=0) (no cond) */
void slv6_X_MUL_S0_NC(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m,
    const uint8_t s)
{
  const uint32_t old_Rs = reg(proc,s);
  const uint32_t old_Rm = reg(proc,m);
  set_reg(proc,d,get_bits((to_u64(old_Rm) * to_u64(old_Rs)),31,0));

}

/* A4.1.14--A5.1.3--NC
 * CMN -- Data processing operands - Immediate (no cond) */
void slv6_X_CMN_M1_Imm_NC(struct SLv6_Processor *proc,
    const uint8_t n,
    const uint8_t rotate_imm,
    const uint32_t immed_rotated)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t alu_out;
  bool shifter_carry_out;
  uint32_t shifter_operand;
  shifter_operand = immed_rotated;
  shifter_carry_out = ((rotate_imm == 0)? proc->cpsr.C_flag: get_bit(shifter_operand,31));
  alu_out = (old_Rn + shifter_operand);
  proc->cpsr.N_flag = get_bit(alu_out,31);
  proc->cpsr.Z_flag = ((alu_out == 0)? 1: 0);
  proc->cpsr.C_flag = CarryFrom_add2(old_Rn, shifter_operand);
  proc->cpsr.V_flag = OverflowFrom_add2(old_Rn, shifter_operand);
}

/* A7.1.28--NI
 * LDR (1) (no immed) */
void slv6_X_Tb_LDR1_NI(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t n)
{
  const uint32_t old_Rn = reg(proc,n);
  uint32_t address;
  uint32_t data;
  address = (old_Rn + (4 * 0));
  if ((!((get_bits(address,1,0) == 0)) && (CP15_reg1_Ubit(proc->cp15_ptr) == 0)))
    unpredictable("Tb_LDR1_NI");
  data = slv6_read_word(proc->mmu_ptr,address);
  set_reg(proc,d,data);
}

/* A7.1.38--NI
 * LSL (1) (no immed) */
void slv6_X_Tb_LSL1_NI(struct SLv6_Processor *proc,
    const uint8_t d,
    const uint8_t m)
{
  const uint32_t old_Rm = reg(proc,m);
  if ((0 == 0))
    set_reg(proc,d,old_Rm);
  else {
    proc->cpsr.C_flag = get_bit(old_Rm,(32 - 0));
    set_reg(proc,d,(old_Rm << 0));
  }
  proc->cpsr.N_flag = get_bit(reg(proc,d),31);
  proc->cpsr.Z_flag = ((reg(proc,d) == 0)? 1: 0);
}

END_SIMSOC_NAMESPACE
