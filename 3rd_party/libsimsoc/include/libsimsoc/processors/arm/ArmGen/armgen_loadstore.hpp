//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARMGEN_LOADSTORE_HPP
#define ARMGEN_LOADSTORE_HPP

#include "armgen.hpp"

// load store operand mode

typedef enum {immediate_ls,
              register_source_ls,
              logical_shift_left_reg_ls,
              logical_shift_right_reg_ls,
              arithmetic_shift_reg_ls,
              rotate_shift_reg_ls,
              rotate_shift_extend_ls
} LSOperandMode;

LSOperandMode &operator++ (LSOperandMode &m);

// values of first and last
const LSOperandMode FIRST_OP_MODE_LS = immediate_ls;
const LSOperandMode LAST_OP_MODE_NSH_LS = register_source_ls;
const LSOperandMode LAST_OP_MODE_LS = rotate_shift_extend_ls;


const std::string OPERAND_LS_SUFFIX[7] = {"_imm", "_reg",
                                     "_lsl","_lsr",
                                     "_asr", "_ror",
                                     "_rrx"};


// except LDR,specialize reg
// const int REG_FIRST_LS = 0;
// const int REG_LAST_LS = 14;
// const int ARM_NUM_REG_LS = 15;
// const std::string REGISTER_LS_SUFFIX[15] = {"_r0", "_r1", "_r2", "_r3",
//                                     "_r4","_r5", "_r6", "_r7",
//                                     "_r8", "_r9","_sl", "_fp",
//                                     "_ip", "_sp", "_lr"};

//  load store operations


typedef enum {LDR,    // 0
              LDRB,   // 1
              STR,    // 2
              STRB,   // 3
              LDRT,   // 4
              LDRBT,  // 5
              STRT,   // 6
              STRBT,  // 7
              LDRH,   // 8
              LDRSB,  // 9
              LDRSH,  // 10
              STRH,   // 11
              LDRD,   // 12
              STRD    // 13
} LoadStoreOpcode;


const LoadStoreOpcode FIRST_LSOP=LDR;
const LoadStoreOpcode LAST_LSOP=STRD;

const LoadStoreOpcode FIRST_LSOP_ADMODE2_9=LDR;
const LoadStoreOpcode LAST_LSOP_ADMODE2_9=STRB;

const LoadStoreOpcode FIRST_LSOP_ADMODE2_3=LDRT;
const LoadStoreOpcode LAST_LSOP_ADMODE2_3=STRBT;

const LoadStoreOpcode FIRST_LSOP_ADMODE3_6=LDRH;
const LoadStoreOpcode LAST_LSOP_ADMODE3_6=STRD;

const std::string LOAD_STORE_SUFFIX[14] = {"_ldr", "_ldrb", "_str",
                                           "_strb","_ldrt", "_ldrbt",
                                           "_strt", "_strbt","_ldrh",
                                           "_ldrsb","_ldrsh","_strh","_ldrd","_strd"};

LoadStoreOpcode &operator++ (LoadStoreOpcode &opc);
// B bit
// typedef enum {data_signed, data_unsigned} LoadStoreSign;
// LoadStoreSign &operator++ (LoadStoreSign &am);
// const std::string SIGN_SUFFIX[2] = {"_s", "_u"};
// U bit
const std::string U_SUFFIX[2] = {"_U0", "_U1"};

typedef enum {arm32_offset, // 0 index not added/sub to base
              arm32_pre_index, // 1 index added/sub to base before
              arm32_post_index, // 2 index added/sub to base after
} AddressingMode;

AddressingMode &operator++ (AddressingMode &am);

const std::string ADDRESS_MODE_SUFFIX[3] = {"_off", "_pre", "_post"};

const AddressingMode FIRST_ADDRESS_MODE = arm32_offset;
const AddressingMode LAST_ADDRESS_MODE = arm32_post_index;

// class to generate Data Processing instructions
class LoadStoreGenerator: public ARM_Generator {
public:
  void generate();
protected:
  // generic function generates an array of functions of type ARM_PseudoFunction

  void generate_ls_func_table(const std::string table_name,
                              const std::string prefix,
                              const LoadStoreOpcode opcode_from,
                              const LoadStoreOpcode opcode_to,
                              const LSOperandMode opm_from,
                              const LSOperandMode opm_to,
                              const AddressingMode addrm_from,
                              const AddressingMode addrm_to// ,
//                           bool specialize_Rd_reg,
//                           bool specialize_Rn_reg
                              );
  void generate_LDR_PC_func_table(const std::string table_name,
                                  const std::string prefix,
                                  const LoadStoreOpcode opcode,
                                  const LSOperandMode opm_from,
                                  const LSOperandMode opm_to,
                                  const AddressingMode addrm_from,
                                  const AddressingMode addrm_to);

  void generate_ls_zero_func_table(const std::string table_name,
                                   const std::string prefix,
                                   const LoadStoreOpcode opcode_from,
                                   const LoadStoreOpcode opcode_to);

  // function to print load store instruction code
  void generate_ls_instruction(const std::string prefix,
                               const ConditionCode cond,
                               const LoadStoreOpcode opcode,
                               const LSOperandMode opm,
                               const AddressingMode addr_m,
                               const int u_bit);

 void generate_ls_ldr_pc_instruction(const std::string prefix,
                                     const ConditionCode cond,
                                     const LoadStoreOpcode opcode,
                                     const LSOperandMode opm,
                                     const AddressingMode addr_m,
                                     const int u_bit);

  void generate_ls_zero_instruction(const std::string prefix,
                                    const ConditionCode cond,
                                    const LoadStoreOpcode opcode);

  void generate_ls_address(std::ostringstream &oss,
                           const AddressingMode am,
                           const int u_bit);

  void generate_Rn_address_offset(std::ostringstream &oss,
                           const AddressingMode am,
                           const int u_bit);

  void generate_ls_operand(std::ostringstream &oss, const LSOperandMode opm);

};

#endif //ARMGEN_LOADSTORE_HPP
