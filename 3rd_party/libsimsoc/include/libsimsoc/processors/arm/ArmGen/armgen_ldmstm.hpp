//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARMGEN_LDMSTM_HPP
#define ARMGEN_LDMSTM_HPP

#include "armgen.hpp"

typedef enum {LDM_1,
              LDM_3,
              STM_1,
              STM_2,
              LDM_2
}LdmStmOpcode;

const LdmStmOpcode FIRST_LDMOP=LDM_1;
const LdmStmOpcode LAST_LDMOP=LDM_3;

const LdmStmOpcode FIRST_STMOP=STM_1;
const LdmStmOpcode LAST_STMOP=LDM_2;

const std::string W_SUFFIX[2] = {"_noW", "_W"};

const std::string PC_SUFFIX[2] = {"_noPC", "_PC"};

const std::string LDM_STM_SUFFIX[5] = {"_ldm_1","_ldm_3",
                                  "_stm_1","_stm_2","_ldm_2"};

LdmStmOpcode &operator++ (LdmStmOpcode  &opc);

typedef enum {DA,
              IA,
              DB,
              IB
}AddressMode;

AddressMode &operator++ (AddressMode &am);
const std::string ADDRESSING_MODE_SUFFIX[4] = {"_DA", "_IA", "_DB","_IB"};

const AddressMode FIRST_ADDRESSING_MODE = DA;
const AddressMode LAST_ADDRESSING_MODE = IB;

class LdmStmGenerator: public ARM_Generator {
public:
  void generate();
protected:
  void generate_ldm_func_table(const std::string table_name,
                               const std::string prefix,
                               const LdmStmOpcode opcode_from,
                               const LdmStmOpcode opcode_to,
                               const AddressMode addrm_from,
                               const AddressMode addrm_to);

 void generate_stm_func_table(const std::string table_name,
                              const std::string prefix,
                              const LdmStmOpcode opcode_from,
                              const LdmStmOpcode opcode_to,
                              const AddressMode addrm_from,
                              const AddressMode addrm_to);

  void generate_ldm_instruction(const std::string func_neme,
                                const ConditionCode cond,
                                const int w_bit,
                                const int reg_pc,
                                const LdmStmOpcode opcode,
                                const AddressMode addr_m);

  void generate_stm_instruction(const std::string func_neme,
                                const ConditionCode cond,
                                const int w_bit,
                                const LdmStmOpcode opcode,
                                const AddressMode addr_m);

  void generate_address(std::ostringstream &oss,
                        const AddressMode am,
                        const int w_bit);
                        
  void generate_Rn_address_offset(std::ostringstream &oss,
                                       const AddressMode am);
};
#endif //ARMGEN_LDMSTM_HPP
