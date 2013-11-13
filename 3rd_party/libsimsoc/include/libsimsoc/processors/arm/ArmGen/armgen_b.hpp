//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARMGEN_B_HPP
#define ARMGEN_B_HPP

#include "armgen.hpp"
// ARM V5 Branch Instructions

typedef enum {B,    //0
              BL,   //1
              BLX_1,//2
              BLX_2,//3
              BX,    //4
}B_Opcode;


const std::string B_OPCODE_SUFFIX[5] = {"_b","_bl","_blx1",
                                   "_blx2","_bx"};


B_Opcode &operator ++ (B_Opcode &op);


const B_Opcode FIRST_B = B;
const B_Opcode LAST_B = BX;

const B_Opcode FIRST_L_B = B;
const B_Opcode LAST_L_B = BL;

const B_Opcode OPCODE_H_B = BLX_1;

const B_Opcode FIRST_Reg_B = BLX_2;
const B_Opcode LAST_Reg_B = BX;

const std::string SP_SUFFIX[2] = {"_noSP", "_SP"};
//class to generate Branch instructions

class B_Generator: public ARM_Generator{

public:
  void generate();
protected:


  //generate function table for BLX_2 and BX instructions
  void generate_b_func_table(const std::string table_name,
                             const std::string prefix,
                             const B_Opcode opcode_from,
                             const B_Opcode opcode_to);
 //generate instruction  for BLX_2 and BX instructions

  void generate_b_instruction(const std::string func_name,
                              const ConditionCode cond,
                              const B_Opcode opcode);
//generate function table for B ,BL and BLX_1 instructions
  void generate_b_sp_func_table(const std::string table_name,
                                const std::string prefix,
                                const B_Opcode opcode_from,
                                const B_Opcode opcode_to);

//generate instruction  for B ,BL and BLX_1 instructions
  void generate_b_sp_instruction(const std::string func_name,
                                 const ConditionCode cond,
                                 const int  sp,
                                 const B_Opcode opcode);
};

#endif // ARMGEN_B_HPP
