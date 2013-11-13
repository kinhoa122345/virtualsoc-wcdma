//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARMGEN_SWP_HPP
#define ARMGEN_SWP_HPP


#include "armgen.hpp"


// ARM V5 Swp and Swpb instructions


typedef enum {SWP,
              SWPB
} SWP_Opcode;

const std::string SWP_OPCODE_SUFFIX[2] = {"_swp","_swpb"};


SWP_Opcode &operator++ (SWP_Opcode &op);


const SWP_Opcode FIRST_SWP = SWP;
const SWP_Opcode LAST_SWP = SWPB;


// class to generate Swp instructions

class SWP_Generator: public ARM_Generator{
public:
  void generate();

protected:

  void generate_swp_func_table(const std::string table_name,
                               const std::string prefix,
                               const SWP_Opcode opcode_from,
                               const SWP_Opcode opcode_to,
                               bool specialize_Rd,
                               bool specialize_Rn,
                               bool specialize_Rm);

  void specialize_swp_register(const std::string prefix,
                               const ConditionCode cond,
                               const SWP_Opcode opcode,
                               const bool specialize_Rd,
                               const bool specialize_Rn,
                               const bool specialize_Rm);

 void generate_swp_instruction(const std::string func_name,
                               const ConditionCode cond,
                               const SWP_Opcode op,
                               const bool specialize_Rd,
                               const int reg_d,
                               const bool specialize_Rn,
                               const int reg_n,
                               const bool specialize_Rm,
                               const int reg_m);
};

#endif //ARMGEN_SWP_HPP
