//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARMGEN_DPI_HPP
#define ARMGEN_DPI_HPP

#include "armgen.hpp"




typedef enum {immediate,//0
              register_source,//1
              logical_shift_right_imm_32,//2
              arithmetic_shift_imm_32,//3
              logical_shift_left_imm,//4
              logical_shift_right_imm,//5
              arithmetic_shift_imm,//6
              rotate_shift_imm,//7
              rotate_shift_extend,//8
              logical_shift_left_reg,//9
              logical_shift_right_reg,//10
              arithmetic_shift_reg,//11
              rotate_shift_reg//12
             } OperandMode;

OperandMode &operator++ (OperandMode &m);

// values of first and last
const OperandMode FIRST_OP_MODE = immediate;
const OperandMode LAST_OP_MODE = rotate_shift_reg;
const OperandMode LAST_SHIFT_IMM = rotate_shift_extend;

const std::string OPERAND_SUFFIX[13] = {"_imm", "_reg","_lsri32","_asri32",
                                   "_lsli", "_lsri", "_asri", "_rori","_rrx","_lslr",
                                    "_lsrr", "_asrr","_rorr"};





// ARM V5 Data Processing Instructions

typedef enum {AND = 0,
              EOR, // 1
              ORR, // 2
              BIC, // 3 clear bit I
              TST, // 4
              TEQ, // 5
              ADD, // 6
              ADC, // 7
              SUB, // 8 substract a - b
              SBC, // 9
              RSB, // 10 substract b - a
              RSC, // 11
              CMP, // 12
              CMN, // 13
              MOV, // 14
              MVN, // 15
} DPI_Opcode;


const std::string OPCODE_SUFFIX[16] = { "_and", "_eor", "_orr", "_bic",
                                   "_tst", "_teq",
                                   "_add", "_adc", "_sub", "_sbc",
                                   "_rsb", "_rsc",
                                   "_cmp", "_cmn",
                                   "_mov", "_mvn" };

DPI_Opcode &operator++ (DPI_Opcode &op);

const DPI_Opcode FIRST_DPI = AND;
const DPI_Opcode LAST_DPI = MVN;

const DPI_Opcode FIRST_BOOL = AND;
const DPI_Opcode LAST_BOOL = TEQ;

const DPI_Opcode FIRST_DATA = ADD;
const DPI_Opcode LAST_DATA = CMN;

const DPI_Opcode FIRST_MOVE = MOV;
const DPI_Opcode LAST_MOVE = MVN;

#ifdef SPRD


// class to generate Data Processing instructions
class DPI_Generator: public ARM_Generator {
public:
  void generate();
  // DPIGenerator();

protected:
  // generic function generates an array of functions of type ARM_PseudoFunction
  // it always generate at least 15 functions corresponding
  // to the 15 condition codes
  // For each condition code, it loops over the target opcode types,
  // over the target operand modes
  // and optionnally over the destination register and the source register
  // Therefore it can generate a table of
  // [15 cond]*[N opcodes]*[M modes]*[16 regs]*[16 regs] elements
  void generate_func_table(const std::string table_name,
                           const std::string prefix,
                           const DPI_Opcode opcode_from,
                           const DPI_Opcode opcode_to,
                           const OperandMode opm_from,
                           const OperandMode opm_to
                           );

  // code generation function
  // that adds the specific generated code to the output stream
  // This function is called from within generate_func_table
  void generate_operation(ostringstream &body,
                          const int s_bit,
                          const DPI_Opcode opcode, const OperandMode opm,
                          const int reg_d
                          );

  // function to print DPI instruction code
  void generate_instruction(const std::string func_name,
                            const ConditionCode cond,
                            const int s_bit,
                            const DPI_Opcode op, const OperandMode opm,
                            const int reg_d
                            );


  std::string generate_operand_suffix(const OperandMode op,
                                      const bool specialize_Rn_reg,
                                      const int r);

  void generate_operand_code(ostringstream &oss,
                             const OperandMode op,
                             const int set_carry);

};

#else
#ifdef NCOND
class DPI_Generator: public ARM_Generator {
public:
  void generate();
  // DPIGenerator();

protected:
  // generic function generates an array of functions of type ARM_PseudoFunction
  // it always generate at least 15 functions corresponding
  // to the 15 condition codes
  // For each condition code, it loops over the target opcode types,
  // over the target operand modes
  // and optionnally over the destination register and the source register
  // Therefore it can generate a table of
  // [15 cond]*[N opcodes]*[M modes]*[16 regs]*[16 regs] elements
  void generate_func_table(const std::string table_name,
                           const std::string prefix,
                           const DPI_Opcode opcode_from,
                           const DPI_Opcode opcode_to,
                           const OperandMode opm_from,
                           const OperandMode opm_to
                           );

  // code generation function
  // that adds the specific generated code to the output stream
  // This function is called from within generate_func_table
  void generate_operation(ostringstream &body,
                          const int s_bit,
                          const DPI_Opcode opcode, const OperandMode opm,
                          const int reg_d
                          );

  // function to print DPI instruction code
  void generate_instruction(const std::string func_name,
                            const ConditionCode cond,
                            const int s_bit,
                            const DPI_Opcode op, const OperandMode opm,
                            const int reg_d
                            );


  std::string generate_operand_suffix(const OperandMode op,
                                      const bool specialize_Rn_reg,
                                      const int r);

  void generate_operand_code(std::ostringstream &oss,
                             const OperandMode op,
                             const int set_carry);

};
#else
#ifdef SPCOND
// class to generate Data Processing instructions
class DPI_Generator: public ARM_Generator {
public:
  void generate();
  // DPIGenerator();

protected:
  // generic function generates an array of functions of type ARM_PseudoFunction
  // it always generate at least 15 functions corresponding
  // to the 15 condition codes
  // For each condition code, it loops over the target opcode types,
  // over the target operand modes
  // and optionnally over the destination register and the source register
  // Therefore it can generate a table of
  // [15 cond]*[N opcodes]*[M modes]*[16 regs]*[16 regs] elements
  void generate_func_table(const std::string table_name,
                           const std::string prefix,
                           const DPI_Opcode opcode_from,
                           const DPI_Opcode opcode_to,
                           const OperandMode opm_from,
                           const OperandMode opm_to,
                           bool specialize_Rd_reg,
                           bool specialize_Rn_reg);

  // code generation function
  // that adds the specific generated code to the output stream
  // This function is called from within generate_func_table
  void generate_operation(std::ostringstream &body,
                          const int s_bit,
                          const DPI_Opcode opcode, const OperandMode opm,
                          const bool specialize_Rd_reg, const int reg_d,
                          const bool specialize_Rn_reg, const int reg_n);

  // function to print DPI instruction code
  void generate_instruction(const std::string func_name,
                            const ConditionCode cond,
                            const int s_bit,
                            const DPI_Opcode op, const OperandMode opm,
                            const bool specialize_Rd_reg,
                            const int reg_d,
                            const bool specialize_Rn_reg,
                            const int reg_n);

  // function to loop over registers to specialize register with constants
  void specialize_register(const std::string prefix,
                           const ConditionCode cond,
                           const int s_bit,
                           const DPI_Opcode opcode,
                           const OperandMode opm,
                           const bool specialize_Rd_reg,
                           const bool specialize_Rn_reg);

  std::string generate_operand_suffix(const OperandMode op,
                                      const bool specialize_Rn_reg,
                                      const int r);

  void generate_operand_code(std::ostringstream &oss,
                             const OperandMode op,
                             const int set_carry);

};
#else
class DPI_Generator: public ARM_Generator {
public:
  void generate();
  // DPIGenerator();

protected:
  // generic function generates an array of functions of type ARM_PseudoFunction
  // it always generate at least 15 functions corresponding
  // to the 15 condition codes
  // For each condition code, it loops over the target opcode types,
  // over the target operand modes
  // and optionnally over the destination register and the source register
  // Therefore it can generate a table of
  // [15 cond]*[N opcodes]*[M modes]*[16 regs]*[16 regs] elements
  void generate_func_table(const std::string table_name,
                           const std::string prefix,
                           const DPI_Opcode opcode_from,
                           const DPI_Opcode opcode_to,
                           const OperandMode opm_from,
                           const OperandMode opm_to,
                           bool specialize_Rd_reg,
                           bool specialize_Rn_reg);

  // code generation function
  // that adds the specific generated code to the output stream
  // This function is called from within generate_func_table
  void generate_operation(std::ostringstream &body,
                          const int s_bit,
                          const DPI_Opcode opcode, const OperandMode opm,
                          const bool specialize_Rd_reg, const int reg_d,
                          const bool specialize_Rn_reg, const int reg_n);

  // function to print DPI instruction code
  void generate_instruction(const std::string func_name,
                            const ConditionCode cond,
                            const int s_bit,
                            const DPI_Opcode op, const OperandMode opm,
                            const bool specialize_Rd_reg,
                            const int reg_d,
                            const bool specialize_Rn_reg,
                            const int reg_n);

  // function to loop over registers to specialize register with constants
  void specialize_register(const std::string prefix,
                           const ConditionCode cond,
                           const int s_bit,
                           const DPI_Opcode opcode,
                           const OperandMode opm,
                           const bool specialize_Rd_reg,
                           const bool specialize_Rn_reg);

  std::string generate_operand_suffix(const OperandMode op,
                                      const bool specialize_Rn_reg,
                                      const int r);

  void generate_operand_code(std::ostringstream &oss,
                             const OperandMode op,
                             const int set_carry);

};

#endif
#endif
#endif
#endif //ARMGEN_DPI_HPP
