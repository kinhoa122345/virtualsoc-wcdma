//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "armpi.hpp"
#include <cassert>
#include "libsimsoc/processors/arm/armis.hpp"
#include "libsimsoc/bitwise_operator.hpp"
#include "libsimsoc/processors/arm/armpi.hpp"
#include "libsimsoc/processors/arm/arm_processor.hpp"
#include "libsimsoc/display.hpp"

using namespace std;

namespace simsoc {

/******************************************************************************/

PseudoStatus armPseudoNextPage(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  proc.debug() <<"armPseudonext_page" <<endl;
  return NEXT_PAGE;
}

void armTranslateNextPage(ARM_PseudoInstruction& pi) {
  pi.f = armPseudoNextPage;
}

PseudoStatus armPseudoGeneric(ARM_Processor &proc, const ARM_PseudoInstruction& pi) {
  proc.debug() <<"pif_generic: " <<*pi.args.generic.instr <<endl;
  pi.args.generic.instr->exec(proc);
  if (pi.args.generic.instr->may_branch())
    return BRANCH;
  else {
    proc.cpu.regs[ARM_CPU::PC] -= proc.instr_size;
    return OK;
  }
}

void armTranslateGeneric(ARM_PseudoInstruction& pi, ARM_Instruction* instr) {
  pi.f = armPseudoGeneric;
  pi.args.generic.instr = instr;
}

  bool isPseudoGeneric(const ARM_PseudoInstruction& pi) {
    return pi.f==armPseudoGeneric;
  }

  void destructPseudo(ARM_PseudoInstruction& pi) {
    if (isPseudoGeneric(pi))
      delete pi.args.generic.instr;
  }

PseudoStatus arm_pi_nop(ARM_Processor &proc, const ARM_PseudoInstruction& p) {
  return OK;
}

/******************************************************************************/

extern ARM_PseudoFunction arm_dpi_int_table[2][2][8][13][2];
extern ARM_PseudoFunction arm_dpi_bool_table[2][2][6][13][2];
extern ARM_PseudoFunction arm_dpi_move_table[2][2][2][13][2];
//condition,bit S,opcode
extern ARM_PseudoFunction arm_mli_32_table[2][2][2];
extern ARM_PseudoFunction arm_mli_64_int_table[2][2][2];
extern ARM_PseudoFunction arm_mli_64_uint_table[2][2][2];
// condtion,opcode,oprand mode,addressing mode,bit U
extern ARM_PseudoFunction arm_loadstore_admode2_9_table[2][4][7][3][2];
extern ARM_PseudoFunction arm_loadstore_admode2_9_zero_table[2][4];
extern ARM_PseudoFunction arm_loadstore_admode2_3_table[2][4][7][3][2];
extern ARM_PseudoFunction arm_loadstore_admode3_6_table[2][6][2][3][2];
// condition,opcode,oprand mode,addressing mode,bit U
extern ARM_PseudoFunction arm_ldr_pc_admode2_9_table[2][7][3][2];
// codition,opcode
extern ARM_PseudoFunction arm_swp_table[2][2];
// condition,opcode,sp(the next instruction in the same page or not)
extern ARM_PseudoFunction arm_b_l_table[2][2][2];
extern ARM_PseudoFunction arm_b_h_table[2][1][2];
// condition,opcode
extern ARM_PseudoFunction arm_b_reg_table[2][2];
//condtion
extern ARM_PseudoFunction arm_clz_table[2];
//condtion m(in user mode of not)
extern ARM_PseudoFunction arm_swi_table[2][2];
//condition,w bit,opcode,address mode
extern ARM_PseudoFunction arm_ldmstm_nopc_table[2][2][3][4];
//condition,w bit,register pc include or not,opcode,address mode
extern ARM_PseudoFunction arm_ldmstm_pc_table[2][2][2][2][4];
//condition,r bit
extern ARM_PseudoFunction arm_mrs_table[2][2];
//condition,r bit,operand mode
extern ARM_PseudoFunction arm_msr_table[2][2][2];

void armTranslateDPI_IntImm(ARM_PseudoInstruction& pi,
                            DPI_Opcode op, bool s,bool a, ARM_Condition cond,
                            uint8_t Rd, uint8_t Rn,
                            uint8_t immed, uint8_t rotate_amount) {
  pi.f = arm_dpi_int_table[a][s][op-FIRST_INT][0][Rd==ARM_CPU::PC];
  pi.args.dpi_imm.Rd = Rd;
  pi.args.dpi_imm.Rn = Rn;
  pi.args.dpi_imm.set_carry = rotate_amount;
  pi.args.dpi_imm.immed = rotateRight(immed,rotate_amount);
 pi.args.any.cond = cond;
}

void armTranslateDPI_IntIS(ARM_PseudoInstruction& pi,
                           DPI_Opcode op, bool s,bool a, ARM_Condition cond,
                           uint8_t Rd, uint8_t Rn,
                           uint8_t Rm, ARM_Shift shift, uint8_t immed) {
  size_t m;
  if (immed)
    m = 4+(size_t) shift;
  else if (shift==LSL)
    m = 1; // reg
  else
    m = 8; // rrx
  pi.f = arm_dpi_int_table[a][s][op-FIRST_INT][m][Rd==ARM_CPU::PC];
  pi.args.dpi_shift_imm.Rd = Rd;
  pi.args.dpi_shift_imm.Rn = Rn;
  pi.args.dpi_shift_imm.Rm = Rm;
  pi.args.dpi_shift_imm.imm_s = immed;
 pi.args.any.cond = cond;

}

void armTranslateDPI_IntIS_lsr_32(ARM_PseudoInstruction& pi,
                                  DPI_Opcode op, bool s, bool a,ARM_Condition cond,
                                  uint8_t Rd, uint8_t Rn,
                                  uint8_t Rm) {
  pi.f = arm_dpi_int_table[a][s][op-FIRST_INT][2][Rd==ARM_CPU::PC];
  pi.args.dpi_shift_imm.Rd = Rd;
  pi.args.dpi_shift_imm.Rn = Rn;
  pi.args.dpi_shift_imm.Rm = Rm;
  pi.args.any.cond = cond;
}

void armTranslateDPI_IntIS_asr_32(ARM_PseudoInstruction& pi,
                                  DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                                  uint8_t Rd, uint8_t Rn,
                                  uint8_t Rm) {
  pi.f = arm_dpi_int_table[a][s][op-FIRST_INT][3][Rd==ARM_CPU::PC];
  pi.args.dpi_shift_imm.Rd = Rd;
  pi.args.dpi_shift_imm.Rn = Rn;
  pi.args.dpi_shift_imm.Rm = Rm;
  pi.args.any.cond = cond;
}

void armTranslateDPI_IntRS(ARM_PseudoInstruction& pi,
                           DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                           uint8_t Rd, uint8_t Rn,
                           uint8_t Rm, ARM_Shift shift, uint8_t Rs) {
  unsigned int m = 9+(unsigned int) shift;
  pi.f = arm_dpi_int_table[a][s][op-FIRST_INT][m][Rd==ARM_CPU::PC];
  pi.args.dpi_shift_reg.Rd = Rd;
  pi.args.dpi_shift_reg.Rn = Rn;
  pi.args.dpi_shift_reg.Rm = Rm;
  pi.args.dpi_shift_reg.Rs = Rs;
  pi.args.any.cond = cond;
}

void armTranslateDPI_BoolImm(ARM_PseudoInstruction& pi,
                             DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                             uint8_t Rd, uint8_t Rn,
                             uint8_t immed, uint8_t rotate_amount) {
  pi.f = arm_dpi_bool_table[a][s][op-FIRST_BOOL][0][Rd==ARM_CPU::PC];
  pi.args.dpi_imm.Rd = Rd;
  pi.args.dpi_imm.Rn = Rn;
  pi.args.dpi_imm.set_carry = rotate_amount;
  pi.args.dpi_imm.immed = rotateRight(immed,rotate_amount);
  pi.args.any.cond = cond;
}

void armTranslateDPI_BoolIS(ARM_PseudoInstruction& pi,
                            DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                            uint8_t Rd, uint8_t Rn,
                            uint8_t Rm, ARM_Shift shift, uint8_t immed) {
  size_t m;
  if (immed)
    m = 4+(size_t) shift;
  else if (shift==LSL)
    m = 1; // reg
  else
    m = 8; // rrx
  pi.f = arm_dpi_bool_table[a][s][op-FIRST_BOOL][m][Rd==ARM_CPU::PC];
  pi.args.dpi_shift_imm.Rd = Rd;
  pi.args.dpi_shift_imm.Rn = Rn;
  pi.args.dpi_shift_imm.Rm = Rm;
  pi.args.dpi_shift_imm.imm_s = immed;
  pi.args.any.cond = cond;
}

void armTranslateDPI_BoolIS_lsr_32(ARM_PseudoInstruction& pi,
                                   DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                                   uint8_t Rd, uint8_t Rn,
                                   uint8_t Rm) {
  pi.f = arm_dpi_move_table[a][s][op-FIRST_MOVE][2][Rd==ARM_CPU::PC];
  pi.args.dpi_shift_imm.Rd = Rd;
  pi.args.dpi_shift_imm.Rm = Rm;
  pi.args.any.cond = cond;
}

void armTranslateDPI_BoolIS_asr_32(ARM_PseudoInstruction& pi,
                           DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                           uint8_t Rd, uint8_t Rn,
                           uint8_t Rm) {
  pi.f = arm_dpi_bool_table[a][s][op-FIRST_BOOL][3][Rd==ARM_CPU::PC];
  pi.args.dpi_shift_imm.Rd = Rd;
  pi.args.dpi_shift_imm.Rn = Rn;
  pi.args.dpi_shift_imm.Rm = Rm;
  pi.args.any.cond = cond;

}

void armTranslateDPI_BoolRS(ARM_PseudoInstruction& pi,
                            DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                            uint8_t Rd, uint8_t Rn,
                            uint8_t Rm, ARM_Shift shift, uint8_t Rs) {
  unsigned int m = 9+(unsigned int) shift;
  pi.f = arm_dpi_bool_table[a][s][op-FIRST_BOOL][m][Rd==ARM_CPU::PC];
  pi.args.dpi_shift_reg.Rd = Rd;
  pi.args.dpi_shift_reg.Rn = Rn;
  pi.args.dpi_shift_reg.Rm = Rm;
  pi.args.dpi_shift_reg.Rs = Rs;
  pi.args.any.cond = cond;
}

void armTranslateDPI_MoveImm(ARM_PseudoInstruction& pi,
                             DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                             uint8_t Rd,
                             uint8_t immed, uint8_t rotate_amount) {
  pi.f = arm_dpi_move_table[a][s][op-FIRST_MOVE][0][Rd==ARM_CPU::PC];
  pi.args.dpi_imm.Rd = Rd;
  pi.args.dpi_imm.set_carry = rotate_amount;
  pi.args.dpi_imm.immed = rotateRight(immed,rotate_amount);
  pi.args.any.cond = cond;
}

void armTranslateDPI_MoveIS(ARM_PseudoInstruction& pi,
                            DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                            uint8_t Rd,
                            uint8_t Rm, ARM_Shift shift, uint8_t immed) {
  size_t m;
  if (immed)
    m = 4+(size_t) shift;
  else if (shift==LSL)
    m = 1; // reg
  else
    m = 8; // rrx
  pi.f = arm_dpi_move_table[a][s][op-FIRST_MOVE][m][Rd==ARM_CPU::PC];
  pi.args.dpi_shift_imm.Rd = Rd;
  pi.args.dpi_shift_imm.Rm = Rm;
  pi.args.dpi_shift_imm.imm_s = immed;
  pi.args.any.cond = cond;
}

void armTranslateDPI_MoveIS_lsr_32(ARM_PseudoInstruction& pi,
                                   DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                                   uint8_t Rd,uint8_t Rm) {
  pi.f = arm_dpi_move_table[a][s][op-FIRST_MOVE][2][Rd==ARM_CPU::PC];
  pi.args.dpi_shift_imm.Rd = Rd;
  pi.args.dpi_shift_imm.Rm = Rm;
  pi.args.any.cond = cond;
}

void armTranslateDPI_MoveIS_asr_32(ARM_PseudoInstruction& pi,
                                   DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                                   uint8_t Rd,
                                   uint8_t Rm) {
  pi.f = arm_dpi_move_table[a][s][op-FIRST_MOVE][3][Rd==ARM_CPU::PC];
  pi.args.dpi_shift_imm.Rd = Rd;
  pi.args.dpi_shift_imm.Rm = Rm;
  pi.args.any.cond = cond;
}

void armTranslateDPI_MoveRS(ARM_PseudoInstruction& pi,
                            DPI_Opcode op, bool s, bool a, ARM_Condition cond,
                            uint8_t Rd,
                            uint8_t Rm, ARM_Shift shift, uint8_t Rs) {
  unsigned int m = 9+(unsigned int) shift;

  pi.f = arm_dpi_move_table[a][s][op-FIRST_MOVE][m][Rd==ARM_CPU::PC];
  pi.args.dpi_shift_reg.Rd = Rd;
  pi.args.dpi_shift_reg.Rm = Rm;
  pi.args.dpi_shift_reg.Rs = Rs;
  pi.args.any.cond = cond;
}

void armTranslateMLI_32(ARM_PseudoInstruction& pi,
                        uint8_t op,
                        bool s, ARM_Condition cond, bool a,
                        uint8_t Rd,uint8_t Rm,
                        uint8_t Rs,uint8_t Rn)
{
  pi.f = arm_mli_32_table[a][s][op];
  pi.args.mli_32.Rd = Rd;
  pi.args.mli_32.Rm = Rm;
  pi.args.mli_32.Rs = Rs;
  pi.args.mli_32.Rn = Rn;
  pi.args.any.cond = cond;
}

void armTranslateMLI_64(ARM_PseudoInstruction& pi,
                        uint8_t op,
                        bool s, ARM_Condition cond, bool a,
                        uint8_t RdHi,uint8_t RdLo,
                        uint8_t Rm,uint8_t Rs)
{
  if (op<=3)
    pi.f = arm_mli_64_int_table[a][s][op-2];
  else
    pi.f = arm_mli_64_uint_table[a][s][op-4];
  pi.args.mli_64.RdHi=RdHi;
  pi.args.mli_64.RdLo=RdLo;
  pi.args.mli_64.Rs=Rs;
  pi.args.mli_64.Rm=Rm;
  pi.args.any.cond = cond;
}

void armTranslateLS_Imm(ARM_PseudoInstruction& pi,
                        LoadStoreOpcode op,
                        bool u,ARM_Condition cond, bool a,
                        AddressingMode adm,
                        uint8_t Rd,uint8_t Rn,
                        uint16_t immed)
{
  if(op<=3)
    if (op==LDR & Rd==ARM_CPU::PC)
      pi.f =arm_ldr_pc_admode2_9_table[a][immediate_ls][adm][u] ;
    else if (immed==0)
      pi.f = arm_loadstore_admode2_9_zero_table[a][op-FIRST_LSOP_ADMODE2_9];
    else
      pi.f = arm_loadstore_admode2_9_table[a][op-FIRST_LSOP_ADMODE2_9][immediate_ls][adm][u];
  else if (op >3 & op <=7)
    pi.f = arm_loadstore_admode2_3_table[a][op-FIRST_LSOP_ADMODE2_3][immediate_ls][2][u];
  else
    pi.f = arm_loadstore_admode3_6_table[a][op-FIRST_LSOP_ADMODE3_6][immediate_ls][adm][u];
  pi.args.ls_offset.Rd = Rd;
  pi.args.ls_offset.Rn = Rn;
  pi.args.ls_offset.offset = immed;
  pi.args.any.cond = cond;
}

void armTranslateLS_Reg(ARM_PseudoInstruction& pi,
                         LoadStoreOpcode op,
                        bool u,ARM_Condition cond, bool a,
                        AddressingMode adm,
                        uint8_t Rd,uint8_t Rn,
                        uint8_t Rm)
{ if(op<=3)
    if (op==LDR & Rd==ARM_CPU::PC)
      pi.f =arm_ldr_pc_admode2_9_table[a][register_source_ls][adm][u] ;
    else
      pi.f = arm_loadstore_admode2_9_table[a][op- FIRST_LSOP_ADMODE2_9][register_source_ls][adm][u];
  else if (op >3 & op <=7)
    pi.f = arm_loadstore_admode2_3_table[a][op-FIRST_LSOP_ADMODE2_3][register_source_ls][2][u];
  else
    pi.f = arm_loadstore_admode3_6_table[a][op-FIRST_LSOP_ADMODE3_6][register_source_ls][adm][u];
  pi.args.ls_immed.Rd = Rd;
  pi.args.ls_immed.Rn = Rn;
  pi.args.ls_immed.Rm = Rm;
  pi.args.any.cond = cond;
}

void armTranslateLS_RS(ARM_PseudoInstruction& pi,
                        LoadStoreOpcode op,
                       bool u,ARM_Condition cond, bool a,
                       AddressingMode adm, LSOperandMode opm,
                       uint8_t Rd, uint8_t Rn,
                       uint8_t Rm, uint8_t immed)
{ if(op<=3)
    if (op==LDR & Rd==ARM_CPU::PC)
      pi.f =arm_ldr_pc_admode2_9_table[a][opm][adm][u] ;
    else
      pi.f = arm_loadstore_admode2_9_table[a][op- FIRST_LSOP_ADMODE2_9][opm][adm][u];
  else if (op >STRB & op <=STRBT)
    pi.f = arm_loadstore_admode2_3_table[a][op-FIRST_LSOP_ADMODE2_3][opm][arm32_post_index][u];
  else
    pi.f = arm_loadstore_admode3_6_table[a][op-FIRST_LSOP_ADMODE3_6][opm][adm][u];
  pi.args.ls_immed.Rd = Rd;
  pi.args.ls_immed.Rn = Rn;
  pi.args.ls_immed.Rm = Rm;
  pi.args.ls_immed.immed = immed;
  pi.args.any.cond = cond;
}

void armTranslateSWP(ARM_PseudoInstruction& pi,
                      uint8_t op,
                     ARM_Condition cond, bool a,
                     uint8_t Rd, uint8_t Rm,
                     uint8_t Rn)
{
  pi.f = arm_swp_table[a][op];
  pi.args.swp_2.Rd = Rd;
  pi.args.swp_2.Rn = Rn;
  pi.args.swp_2.Rm = Rm;
  pi.args.any.cond = cond;
}

void armTranslateBImm(ARM_PseudoInstruction& pi,
                       uint8_t op,
                      bool same_page,
                      ARM_Condition cond, bool a,
                      int32_t branch_offset)
{
  if (op==2)
    pi.f = arm_b_h_table[a][0][same_page];
  else
    pi.f = arm_b_l_table[a][op][same_page];
  pi.args.b_imm.offset = branch_offset;
 pi.args.any.cond = cond;
}


void armTranslateBReg(ARM_PseudoInstruction& pi,
                       uint8_t op,
                      ARM_Condition cond, bool a,
                      uint8_t Rm)
{
  pi.f = arm_b_reg_table[a][op-3];
  pi.args.b_reg.Rm = Rm;
 pi.args.any.cond = cond;
}

void armTranslateCLZ(ARM_PseudoInstruction& pi,
                     ARM_Condition cond, bool a,
                     uint8_t Rd,uint8_t Rm)
{
  pi.f = arm_clz_table[a];
  pi.args.clz_reg.Rd = Rd;
  pi.args.clz_reg.Rm = Rm;
 pi.args.any.cond = cond;
}


void armTranslateSWI(ARM_PseudoInstruction& pi,
                     ARM_Condition cond, bool a,
                     bool m,uint32_t immed)
{
  pi.f = arm_swi_table[a][m];
  pi.args.swi_imm.immed = immed;
  pi.args.any.cond = cond;
}

void armTranslateSTM(ARM_PseudoInstruction& pi,
                     ARM_Condition cond, bool a,
                     uint8_t op,bool w,uint8_t addr_m,
                     uint8_t Rn, uint8_t nb_reg,uint16_t registers)
{
  pi.f = arm_ldmstm_nopc_table[a][w][op][addr_m];
  pi.args.load_store_mult.Rn = Rn;
  pi.args.load_store_mult.nb_reg = nb_reg;
  pi.args.load_store_mult.registers = registers;
  pi.args.any.cond = cond;
}

void armTranslateLDM(ARM_PseudoInstruction& pi,
                     ARM_Condition cond, bool a,
                     uint8_t op,bool w,bool reg_pc,uint8_t addr_m,
                     uint8_t Rn, uint8_t nb_reg,uint16_t registers)
{
  pi.f = arm_ldmstm_pc_table[a][w][reg_pc][op][addr_m];
  pi.args.load_store_mult.Rn = Rn;
  pi.args.load_store_mult.nb_reg = nb_reg;
  pi.args.load_store_mult.registers = registers;
  pi.args.any.cond = cond;
}

void armTranslateMRS(ARM_PseudoInstruction& pi,
                    ARM_Condition cond, bool a,
                     bool r,uint8_t Rd)
{
  pi.f = arm_mrs_table[a][r];
  pi.args.mrs_no.Rd = Rd;
 pi.args.any.cond = cond;
}

void armTranslateMSRReg(ARM_PseudoInstruction& pi,
                       ARM_Condition cond, bool a,
                        bool r,uint8_t field,uint8_t Rm)
{
  pi.f = arm_msr_table[a][r][1];
  pi.args.msr_imm_reg.Rm = Rm;
  pi.args.msr_imm_reg.field = field;
  pi.args.any.cond = cond;
}

void armTranslateMSRImm(ARM_PseudoInstruction& pi,
                        ARM_Condition cond, bool a,
                        bool r, uint8_t field, uint32_t immed)
{
  pi.f = arm_msr_table[a][r][0];
  pi.args.msr_imm_reg.field = field;
  pi.args.msr_imm_reg.immed = immed;
  pi.args.any.cond = cond;
}

static PseudoStatus arm_set_register_always(ARM_Processor &proc,
                                            const ARM_PseudoInstruction &p) {
  proc.debug() <<"arm_set_register_always" <<std::endl;
  proc.cpu.regs[p.args.any_reg.Rd] = p.args.dpi_imm.immed;
  return OK;
}

static PseudoStatus arm_set_register(ARM_Processor &proc,
                                     const ARM_PseudoInstruction &p) {
  proc.debug() <<"arm_set_register" <<std::endl;
  if (not_arm_cond[p.args.any.cond][proc.cpu.cpsr.n]
      [proc.cpu.cpsr.z][proc.cpu.cpsr.c][proc.cpu.cpsr.v])
    return OK;
  proc.cpu.regs[p.args.any_reg.Rd] = p.args.dpi_imm.immed;
  return OK;
}

void armTranslateSetRegister(ARM_PseudoInstruction& pi,
                             ARM_Condition cond, uint8_t Rd, uint32_t data) {
  pi.f = (cond==AL? arm_set_register_always: arm_set_register);
  pi.args.any.cond = cond;
  pi.args.any_reg.Rd = Rd;
  pi.args.dpi_imm.immed = data;
}

} // namespace simsoc
