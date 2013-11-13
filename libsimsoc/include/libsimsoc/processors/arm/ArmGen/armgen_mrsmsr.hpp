//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARMGEN_MRSMSR_HPP
#define ARMGEN_MRSMSR_HPP

#include "armgen.hpp"

typedef enum{_8_bit_immediate,
             m_registers
} M_OperandMode;


M_OperandMode &operator++ (M_OperandMode &m);

const M_OperandMode FIRST_MODE = _8_bit_immediate;
const M_OperandMode LAST_MODE = m_registers;

const std::string M_OP_MODE_SUFFIX[2] = {"_imm","_reg"};

const std::string M_OPCODE_SUFFIX[2] = {"_mrs","_msr"};

const std::string R_SUFFIX[2] = {"_R","_noR"};

class MRSMSR_Generator : public ARM_Generator{
public:
  void generate();
protected:

  // Function  table for MRS
  void generate_mrs_func_table(const std::string table_name,
                               const std::string prefix);

  //Function table for MSR

  void generate_msr_func_table(const std::string table_name,
                               const std::string prefix,
                               const M_OperandMode opm_from,
                               const M_OperandMode opm_to);

  //MRS instruction
  void generate_mrs_instruction(const std::string func_name,
                                const ConditionCode cond,
                                const int r_bit);

  //MSR instruction
  void generate_msr_instruction(const std::string func_name,
                                const ConditionCode cond,
                                const int r_bit,
                                const M_OperandMode opm);

  //Generate operand code for msr instruction
  void generate_operand_code(std::ostringstream &oss,
                             const M_OperandMode opm);
};

#endif //ARMGEN_MRSMSR_HPP


