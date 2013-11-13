//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARMGEN_MLI_HPP
#define ARMGEN_MLI_HPP

#include "armgen.hpp"

// ARM V5 Multiply Instructions

typedef enum {MUL=0,
              MLA=1,
              SMULL=2,
              SMLAL=3,
              UMULL=4,
              UMLAL=5,
              WRONG_MLI=6
} MLI_Opcode;


const std::string MLI_OPCODE_SUFFIX[6] = {"_mul","_mla",
                                     "_smull","_smlal",
                                     "_umull","_umlal"};


MLI_Opcode &operator ++ (MLI_Opcode &op);

const MLI_Opcode FIRST_MLI=MUL;
const MLI_Opcode LAST_MLI=UMLAL;

const MLI_Opcode FIRST_32_MLI=MUL;
const MLI_Opcode LAST_32_MLI=MLA;

const MLI_Opcode FIRST_64_Int_MLI=SMULL;
const MLI_Opcode LAST_64_Int_MLI=SMLAL;

const MLI_Opcode FIRST_64_Uint_MLI=UMULL;
const MLI_Opcode LAST_64_Uint_MLI=UMLAL;


//class to generate Multiply instructions
class MLI_Generator: public ARM_Generator{

public:
  void generate();
  // MLI Generator();
protected:
  //generic function generates an array of functions of type ARM_PseudoFunction
  //it always generates at least 180 functions corresponding to the 15 condition codes,over the target operand modes and 2 S bit
  //therefore it can generate a table of
  //[15 cond]*[6 opcodes]*[2 sbit]=180 generated functions
  void generate_func_table(const std::string table_name,
                           const std::string prefix,
                           const MLI_Opcode opcode_from,
                           const MLI_Opcode opcode_to);
  //code gernerate function
  //that adds the specific generated code to the output stream
  //This function is called from within generate_func_table
  void generate_operation(std::ostringstream &body,
                  const int s_bit,  const MLI_Opcode opcode/*,
                          const bool specialize_Rd_reg, const int reg_d,
                          const bool specialize_RdHi_reg, const int reg_dh,
                  const bool specialize_RdLo_reg, const int reg_dl,
                  const bool specialize_Rn_reg, const int reg_n,
                  const bool specialize_Rs_reg, const int reg_s,
                  const bool specialize_Rm_reg, const int reg_m*/);

  // function to print MLI instruction code
  void generate_instruction(const std::string func_name,
                            const ConditionCode cond,
                            const int s_bit,
                            const MLI_Opcode opcode/*,
                            const bool specialize_Rd_reg,
                            const int reg_d,
                            const bool specialize_RdHi_reg,
                            const int reg_dh,
                            const bool specialize_RdLo_reg,
                            const int reg_dl,
                            const bool specialize_Rn_reg,
                            const int reg_n,
                            const bool specialize_Rs_reg,
                            const int reg_s,
                            const bool specialize_Rm_reg,
                            const int reg_m */);
  std::string generate_operand_suffix( const bool use_reg_Rn,
                                       const int reg_Rs,
                                       const int reg_Rm,
                                       const int reg_Rn);

};

#endif //ARMGEN_MLI_HPP


