//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "armgen_loadstore.hpp"

using namespace std;

/*
 * Load Store generation
 */

// define ++ operator on enums

LoadStoreOpcode &operator++ (LoadStoreOpcode &opc) {
  return (LoadStoreOpcode &) ++((int &) opc);
}

// LoadStoreSign &operator++ (LoadStoreSign &s) {
//   return (LoadStoreSign &) ++((int &) s);
// }

AddressingMode &operator++ (AddressingMode &am) {
  return (AddressingMode &) ++((int &) am);
}


LSOperandMode & operator++ (LSOperandMode &m) {
  return (LSOperandMode &) ++((int &) m);
}

void LoadStoreGenerator::generate_ls_operand(ostringstream &oss, const LSOperandMode om)
{
  switch (om) {
  case immediate_ls:
    oss << "  const uint32_t index = p.args.ls_offset.offset;"  << endl;
    break;
  case register_source_ls:
    oss << "  const uint32_t index = proc.cpu.regs[p.args.any_reg.Rm];" << endl;
    break;
  case logical_shift_left_reg_ls:
    oss << "  uint32_t index = proc.cpu.regs[p.args.any_reg.Rm];" <<endl;
    oss << "  const uint32_t shift = p.args.ls_immed.immed;" << endl;
    oss << "  index = index << shift;" << endl;
    break;
  case logical_shift_right_reg_ls:
    oss << "  uint32_t index = proc.cpu.regs[p.args.any_reg.Rm];" <<endl;
    oss << "  const uint32_t shift = p.args.ls_immed.immed;" << endl;
    oss << "  index = index >> shift;" << endl;
    break;
  case arithmetic_shift_reg_ls:
    oss << "  int32_t index = proc.cpu.regs[p.args.any_reg.Rm];" <<endl;
    oss << "  const uint32_t shift = p.args.ls_immed.immed;" << endl;
    oss << "  index = (uint32_t)((int32_t)index >> shift);" <<endl;
    break;
  case rotate_shift_reg_ls:
    oss << "  uint64_t val = proc.cpu.regs[p.args.any_reg.Rm]; " << endl;
    oss << "  const uint32_t shift = p.args.ls_immed.immed;" << endl;
    oss << "  val = ((val<<32) | val) >> shift;" << endl;
    oss << "  const uint32_t index = (uint32_t) val; " << endl;
    break;
  case rotate_shift_extend_ls:
    oss << "  uint64_t val = proc.cpu.regs[p.args.any_reg.Rm];" << endl;
    oss << "  val = (val | ((uint64_t)(proc.cpu.cpsr.c)<<32))>>1;"<< endl;
    oss << "  const uint32_t index = (uint32_t)val;"<<endl;
    break;

  default: Fatal("illegal load store operand");
  }
}


void LoadStoreGenerator::generate_ls_address(ostringstream &oss,
                                             const AddressingMode addr_m,
                                             const int u_bit// ,
//                                              const bool specialize_Rn_reg,
//                                              const int reg_n
                                             )
{
  char addsub = u_bit? '+': '-';
  oss << "  uint32_t addr = ";
  //  if (specialize_Rn_reg)
  //     oss << "proc.cpu.regs[" << reg_n << "];" << endl;
  //   else
  oss << "proc.cpu.regs[p.args.any_reg.Rn];" << endl;

  switch(addr_m) {
  case arm32_offset:
    oss << "  addr = addr" << addsub << "index;" << endl;
    break;
  case arm32_pre_index:
    oss << "  addr = addr" << addsub << "index;" << endl;
    //  if (specialize_Rn_reg)
    //       oss << "proc.cpu.regs[" << reg_n << "]";
    //     else
//    oss << "  proc.cpu.regs[p.args.any_reg.Rn]";
//   oss << " = addr;" << endl;
    break;
  case arm32_post_index:
    //  if (specialize_Rn_reg)
    //       oss << "proc.cpu.regs[" << reg_n << "] = addr";
    //     else
//    oss << "  proc.cpu.regs[p.args.any_reg.Rn] = addr";
//    oss << addsub << "index;" << endl;
    break;
  default: Fatal("illegal address mode");
  }
}

void LoadStoreGenerator::generate_Rn_address_offset(ostringstream &oss,
                                             const AddressingMode addr_m,
                                             const int u_bit// ,
//                                              const bool specialize_Rn_reg,
//                                              const int reg_n
                                             )
{
  char addsub = u_bit? '+': '-';
  switch(addr_m) {
  case arm32_offset:
   break;
  case arm32_pre_index:
    oss << "  proc.cpu.regs[p.args.any_reg.Rn]";
    oss << " = addr;" << endl;
    break;
  case arm32_post_index:
   oss << "  proc.cpu.regs[p.args.any_reg.Rn] = addr";
    oss << addsub << "index;" << endl;
    break;
  default: Fatal("illegal address mode");
  }
}

void LoadStoreGenerator::generate_ls_instruction(const string func_name,
                                                 const ConditionCode cond,
                                                 const LoadStoreOpcode opcode,
                                                 const LSOperandMode opm,
                                                 const AddressingMode addr_m,
                                                 const int u_bit)
{
  ostringstream body;

  // print to files the generated  strings
  // print function name
  code_file << "// Semantic function " << endl;
  code_file << PSEUDO_TYPE << func_name << ARGS << endl;
  // generate function body
  body <<  "{" << endl;
  body <<"  proc.debug() <<\"" <<func_name <<"\" <<std::endl;" <<endl;

  generate_condition_code(body, cond);
  generate_ls_operand(body, opm);
  generate_ls_address(body, addr_m, u_bit// , specialize_Rn_reg, reg_n
                      );

  // implement all store instructions
  if (opcode == STR || opcode == STRB || opcode == STRT ||
      opcode == STRBT || opcode == STRH || opcode == STRD) {


    body << "  uint32_t data = proc.cpu.regs[p.args.any_reg.Rd];" << endl;
    switch(opcode) {
    case STR:
      body << "  proc.mmu.write_word(addr&~3,data);" <<endl;
      break;

    case STRB:
      body << "  proc.mmu.write_byte(addr,data);"  <<endl;
      break;

    case STRT:
      body << "  if(!proc.mmu.user_mode){"<<endl;
      body << "    proc.mmu.user_mode = true;"<<endl;
      body << "    proc.mmu.write_word(addr&~3,data);"  <<endl;
      body << "    proc.mmu.user_mode = false;"<<endl;
      body << "  }else"<<endl;
      body << "    proc.mmu.write_word(addr,data);"  <<endl;
      break;

    case STRBT:
      body << "  if(!proc.mmu.user_mode){"<<endl;
      body << "    proc.mmu.user_mode = true;"<<endl;
      body << "    proc.mmu.write_byte(addr,data);"  <<endl;
      body << "    proc.mmu.user_mode = false;"<<endl;
      body << "  }else"<<endl;
      body << "    proc.mmu.write_byte(addr,data);"  <<endl;
      break;

    case STRH:
      body << "  proc.mmu.write_half(addr,data);"  <<endl;
      break;

    case STRD:
      body << "  proc.mmu.write_word(addr,data);" <<endl;
      body << "  data = proc.cpu.regs[p.args.any_reg.Rd+1];" << endl;
      body << "  proc.mmu.write_word(addr+4,data);" <<endl;
      break;

    default: Fatal("instruction not coded yet");
    }
  }
  // implement all load instructions
  else  {
    switch(opcode){
   case LDR:
     body << "  if (!(addr&3))" <<endl;
     body << "    proc.cpu.regs[p.args.any_reg.Rd] = proc.mmu.read_word(addr);" << endl;
     body << "  else"<<endl;
     body << "    proc.cpu.regs[p.args.any_reg.Rd] = rotateRight(proc.mmu.read_word(addr), 8*(addr&3));" <<endl;
      break;

    case LDRB:
      body << "  uint32_t data = proc.mmu.read_byte(addr);" <<endl;
      body << "  proc.cpu.regs[p.args.any_reg.Rd] = data;" << endl;
      break;

    case LDRT:
      body << "  if(!proc.mmu.user_mode){"<<endl;
      body << "    proc.mmu.user_mode = true;"<<endl;
      body << "    uint32_t data1 = proc.mmu.read_word(addr);"<<endl;
      body << "    proc.mmu.user_mode = false;"<<endl;
      body << "    proc.cpu.regs[p.args.any_reg.Rd] = data1;" << endl;
      body << "  }else{"<<endl;
      body << "    uint32_t data = proc.mmu.read_word(addr);" <<endl;
      body << "    proc.cpu.regs[p.args.any_reg.Rd] = data;}" << endl;
      break;

    case LDRBT:
      body << "  if(!proc.mmu.user_mode){"<<endl;
      body << "    proc.mmu.user_mode = true;"<<endl;
      body << "    uint32_t data1 = proc.mmu.read_byte(addr);"<<endl;
      body << "    proc.mmu.user_mode = false;"<<endl;
      body << "    proc.cpu.regs[p.args.any_reg.Rd] = data1;" << endl;
      body << "  }else{"<<endl;
      body << "    uint32_t data = proc.mmu.read_byte(addr);" <<endl;
      body << "    proc.cpu.regs[p.args.any_reg.Rd] = data;}" << endl;
      break;

    case LDRSB:
      body << "  int32_t data = (int8_t)proc.mmu.read_byte(addr);"  <<endl;
      body << "  proc.cpu.regs[p.args.any_reg.Rd] = data;" << endl;
      break;

    case LDRSH:
      body << "  int32_t data = (int16_t)proc.mmu.read_half(addr);"  <<endl;
      body << "  proc.cpu.regs[p.args.any_reg.Rd] = data;" << endl;
     break;

    case LDRH:
      body << "  uint32_t data = proc.mmu.read_half(addr);"  <<endl;
      body << "  proc.cpu.regs[p.args.any_reg.Rd] = data;" << endl;
      break;

    case LDRD:
      body << "  uint32_t data = proc.mmu.read_word(addr);"  <<endl;
      body << "  proc.cpu.regs[p.args.any_reg.Rd] = data;" << endl;
      body << "  data = proc.mmu.read_word(addr+4);"  <<endl;
      body << "  proc.cpu.regs[p.args.any_reg.Rd+1] = data;" << endl;
      break;

    default: Fatal("instruction not coded yet");

    }

  }

	generate_Rn_address_offset(body, addr_m, u_bit);
    code_file << body.str() << "  return OK;" << endl << "}" << endl;
    header_file << func_name << " ";
  // print function name to include file for declaration
  //   func_list_file << FUNC_TYPE << func_name << ";" << endl;
  // print function name to table file for static array  initialization
 //  header_file << func_name << " ";
}

void LoadStoreGenerator::generate_ls_zero_instruction(const string func_name,
                                                      const ConditionCode cond,
                                                      const LoadStoreOpcode opcode)
{
  ostringstream body;
  code_file << "// Semantic function " << endl;
  code_file << PSEUDO_TYPE << func_name << ARGS << endl;
  body <<  "{" << endl;
  body <<"  proc.debug() <<\"" <<func_name <<"\" <<std::endl;" <<endl;
  generate_condition_code(body, cond);
  body <<"  uint32_t addr = proc.cpu.regs[p.args.ls_offset.Rn];" <<endl;

  // implement all store instructions
  if (opcode == STR || opcode == STRB || opcode == STRT ||
      opcode == STRBT || opcode == STRH) {
    body << "  uint32_t data = proc.cpu.regs[p.args.any_reg.Rd];" << endl;
    switch(opcode) {
    case STR:
      body << "  proc.mmu.write_word(addr,data);" <<endl;
      break;
    case STRB:
      body << "  proc.mmu.write_byte(addr,data);"  <<endl;
      break;
    case STRT:
      body << "  if(!proc.mmu.user_mode){"<<endl;
      body << "    proc.mmu.user_mode = true;"<<endl;
      body << "    proc.mmu.write_word(addr,data);"  <<endl;
      body << "    proc.mmu.user_mode = false;"<<endl;
      body << "  }else"<<endl;
      body << "    proc.mmu.write_word(addr,data);"  <<endl;
      break;
    case STRBT:
      body << "  if(!proc.mmu.user_mode){"<<endl;
      body << "    proc.mmu.user_mode = true;"<<endl;
      body << "    proc.mmu.write_byte(addr,data);"  <<endl;
      body << "    proc.mmu.user_mode = false;"<<endl;
      body << "  }else"<<endl;
      body << "    proc.mmu.write_byte(addr,data);"  <<endl;
      break;
    case STRH:
      body << "  proc.mmu.write_half(addr,data);"  <<endl;
      break;
    default: Fatal("instruction not coded yet");
    }
  }
  // implement all load instructions
  else  {
    switch(opcode){
    case LDR:
      body << " if (!(addr&3))" <<endl;
      body << "  proc.cpu.regs[p.args.any_reg.Rd] = proc.mmu.read_word(addr);" << endl;
      body << " else"<<endl;
      body << "   proc.cpu.regs[p.args.any_reg.Rd] = rotateRight(proc.mmu.read_word(addr), 8*(addr&3));" <<endl;
      break;

    case LDRB:
      body << "  uint32_t data = proc.mmu.read_byte(addr);" <<endl;
      body << "  proc.cpu.regs[p.args.any_reg.Rd] = data;" << endl;
      break;

    case LDRT:
      body << "  if(!proc.mmu.user_mode){"<<endl;
      body << "    proc.mmu.user_mode = true;"<<endl;
      body << "    uint32_t data1 = proc.mmu.read_word(addr);"<<endl;
      body << "    proc.mmu.user_mode = false;"<<endl;
      body << "    proc.cpu.regs[p.args.any_reg.Rd] = data1;" << endl;
      body << "  }else{"<<endl;
      body << "    uint32_t data = proc.mmu.read_word(addr);" <<endl;
      body << "    proc.cpu.regs[p.args.any_reg.Rd] = data;}" << endl;
      break;

    case LDRBT:
      body << "  if(!proc.mmu.user_mode){"<<endl;
      body << "    proc.mmu.user_mode = true;"<<endl;
      body << "    uint32_t data1 = proc.mmu.read_byte(addr);"<<endl;
      body << "    proc.mmu.user_mode = false;"<<endl;
      body << "    proc.cpu.regs[p.args.any_reg.Rd] = data1;" << endl;
      body << "  }else{"<<endl;
      body << "    uint32_t data = proc.mmu.read_byte(addr);" <<endl;
      body << "    proc.cpu.regs[p.args.any_reg.Rd] = data;}" << endl;
      break;

    case LDRSB:
      body << "  int32_t data = (int8_t)proc.mmu.read_byte(addr);"  <<endl;
      body << "  proc.cpu.regs[p.args.any_reg.Rd] = data;" << endl;
      break;

    case LDRSH:
      body << "  int32_t data = (int16_t)proc.mmu.read_half(addr);"  <<endl;
      body << "  proc.cpu.regs[p.args.any_reg.Rd] = data;" << endl;
     break;

    case LDRH:
      body << "  uint32_t data = proc.mmu.read_half(addr);"  <<endl;
      body << "  proc.cpu.regs[p.args.any_reg.Rd] = data;" << endl;
      break;

    default: Fatal("instruction not coded yet");
    }
  }
  code_file << body.str() << "  return OK;" << endl << "}" << endl;
  header_file << func_name << " ";
  // print function name to include file for declaration
  //   func_list_file << FUNC_TYPE << func_name << ";" << endl;
  // print function name to table file for static array  initialization
  //  header_file << func_name << " ";
}

void LoadStoreGenerator::
generate_ls_func_table(const string table_name,
                       const string prefix,
                       const LoadStoreOpcode opcode_from,
                       const LoadStoreOpcode opcode_to,
                       const LSOperandMode opm_from,
                       const LSOperandMode opm_to,
                       const AddressingMode addrm_from,
                       const AddressingMode addrm_to// ,
// 		       bool specialize_Rd_reg,
// 		       bool specialize_Rn_reg
                       )
{
  string func_name;
  int dim;
  int func_array_struct[10];
  int u_bit;
  ConditionCode cond;

  // Compute number of dimensions for the array of functions, maximum is 8
  // 15 conditions codes
  func_array_struct[0] = LAST_COND_CODE + 1;
  // opcodes LDR/STR/LDRB/STRB =>4
  //      or LDRT/STRT/LDRBT/STRBT =>4
  //      or LDRH/LDRSH/LDRSB/STRH =>4
  func_array_struct[1] = opcode_to - opcode_from +1;
  // shift mode / immediate => imm or reg or 5 shifts => 7
  func_array_struct[2] = opm_to - opm_from + 1;
  // indexing mode: offset, pre-indexed, post-indexed => 3
  func_array_struct[3] = addrm_to - addrm_from + 1;
  // bit U is + or -
  func_array_struct[4] = 2;
  dim = 5;
  //  if (specialize_Rd_reg) {
  //     dim += 1;
  //     func_array_struct[dim] = ARM_NUM_REG;
  //   }
  //   if (specialize_Rn_reg){
  //     dim += 1;
  //     func_array_struct[dim] = ARM_NUM_REG;
  //   }
  // create table declaration in header file
  openArrayDecl(header_file, table_name, func_array_struct, dim);
  // now loop on all specialized functions
  // print ',' after each element of an array
  // but do not print ',' after last element of an array
  for (cond=FIRST_COND_CODE; cond <= LAST_COND_CODE; ++cond) {
    newArrayRow(header_file);
    for (int opcode=opcode_from;opcode<=opcode_to;++opcode){
      newArrayRow(header_file);
      for (int opm=opm_from; opm <= opm_to; ++opm) {
        newArrayRow(header_file); // generate curly bracket
        for (int addr_m=addrm_from; addr_m <= addrm_to; ++addr_m) {
          newArrayRow(header_file);
          for (u_bit=0; u_bit <= 1; ++u_bit) {
            func_name = prefix + COND_CODE_SUFFIX[cond]
              + LOAD_STORE_SUFFIX[opcode]
              + OPERAND_LS_SUFFIX[opm]
              + ADDRESS_MODE_SUFFIX[addr_m]
              + U_SUFFIX[u_bit];
            generate_ls_instruction(func_name,cond,
                                    (LoadStoreOpcode) opcode,
                                    (LSOperandMode) opm,
                                    (AddressingMode) addr_m,
                                    u_bit);
            if (u_bit == 0)  header_file << ", ";
          } // end u loop
          closeArrayRow(header_file);
          if (addr_m < addrm_to) header_file << ", ";
        } // end address mode loop
        closeArrayRow(header_file);
        if (opm < opm_to)  header_file << ", ";
      }//end oprand mode loop
      closeArrayRow(header_file);
      if (opcode < opcode_to) header_file << ", ";
    }//end operation loop
    closeArrayRow(header_file);
    if (cond < LAST_COND_CODE)  header_file << ", ";
  } // end of condition code loop
  closeArrayDecl(header_file);
}

void LoadStoreGenerator::
generate_ls_zero_func_table(const string table_name,
                            const string prefix,
                            const LoadStoreOpcode opcode_from,
                            const LoadStoreOpcode opcode_to)
{
  string func_name;
  const int dim = 2;
  int func_array_struct[dim];
  ConditionCode cond;
  // 15 conditions codes
  func_array_struct[0] = LAST_COND_CODE + 1;
  func_array_struct[1] = opcode_to - opcode_from +1;
  // create table declaration in header file
  openArrayDecl(header_file, table_name, func_array_struct, dim);
  // now loop on all specialized functions
  // print ',' after each element of an array
  // but do not print ',' after last element of an array
  for (cond=FIRST_COND_CODE; cond <= LAST_COND_CODE; ++cond) {
    newArrayRow(header_file);
    for (int opcode=opcode_from;opcode<=opcode_to;++opcode){
      func_name = prefix + COND_CODE_SUFFIX[cond] + LOAD_STORE_SUFFIX[opcode];
      generate_ls_zero_instruction(func_name,cond,
                                   (LoadStoreOpcode) opcode);
      if (opcode < opcode_to) header_file << ", ";
    }//end operation loop
    closeArrayRow(header_file);
    if (cond < LAST_COND_CODE)  header_file << ", ";
  } // end of condition code loop
  closeArrayDecl(header_file);
}

void LoadStoreGenerator::generate_ls_ldr_pc_instruction(const string func_name,
                                                        const ConditionCode cond,
                                                        const LoadStoreOpcode opcode,
                                                        const LSOperandMode opm,
                                                        const AddressingMode addr_m,
                                                        const int u_bit) {
  ostringstream body;

  // print to files the generated  strings
  // print function name
  code_file << "// Semantic function " << endl;
  code_file << PSEUDO_TYPE << func_name << ARGS << endl;
  // generate function body
  body <<  "{" << endl;
  body <<"  proc.debug() <<\"" <<func_name <<"\" <<std::endl;" <<endl;
  generate_condition_code(body, cond);

  generate_ls_operand(body, opm);
  generate_ls_address(body, addr_m, u_bit);
  body << " if (addr&3){" <<endl;
  body << "   uint32_t data1 = rotateRight(proc.mmu.read_word(addr), 8*(addr&3))+8;" <<endl;
  body << "   proc.cpu.regs[15] = data1&0xFFFFFFE;"<<endl;
  body << "   proc.cpu.cpsr.t = data1&1;"<<endl;
  body << "} else{"<<endl;
  body << "   uint32_t data = proc.mmu.read_word(addr);" <<endl;
  body << "   proc.cpu.regs[15] = (data&0xFFFFFFFE)+8;" << endl;
  body << "   proc.cpu.cpsr.t = data&1;}"<<endl;
  generate_Rn_address_offset(body, addr_m, u_bit);
  code_file << body.str() << "  return BRANCH;" << endl << "}" << endl;
  header_file << func_name << " ";

}

void LoadStoreGenerator::
generate_LDR_PC_func_table(const string table_name,
                           const string prefix,
                           const LoadStoreOpcode opcode,
                           const LSOperandMode opm_from,
                           const LSOperandMode opm_to,
                           const AddressingMode addrm_from,
                           const AddressingMode addrm_to)
{ string func_name;
  int dim;
  int func_array_struct[10];
  int u_bit;
  ConditionCode cond;

  // Compute number of dimensions for the array of functions, maximum is 8
  // 15 conditions codes
  func_array_struct[0] = LAST_COND_CODE + 1;
  // opcode = ldr
  //   func_array_struct[1] =1;
  // shift mode / immediate => imm or reg or 5 shifts => 7
  func_array_struct[1] = opm_to - opm_from + 1;
  // indexing mode: offset, pre-indexed, post-indexed => 3
  func_array_struct[2] = addrm_to - addrm_from + 1;
  // bit U is + or -
  func_array_struct[3] = 2;
  dim = 4;
  // create table declaration in header file
  openArrayDecl(header_file, table_name, func_array_struct, dim);
  // now loop on all specialized functions
  // print ',' after each element of an array
  // but do not print ',' after last element of an array
  for (cond=FIRST_COND_CODE; cond <= LAST_COND_CODE; ++cond) {
    newArrayRow(header_file);
    for (int opm=opm_from; opm <= opm_to; ++opm) {
        newArrayRow(header_file); // generate curly bracket
        for (int addr_m=addrm_from; addr_m <= addrm_to; ++addr_m) {
          newArrayRow(header_file);
          for (u_bit=0; u_bit <= 1; ++u_bit) {
            func_name = prefix + COND_CODE_SUFFIX[cond]
              + LOAD_STORE_SUFFIX[0]
              + OPERAND_LS_SUFFIX[opm]
              + ADDRESS_MODE_SUFFIX[addr_m]
              + U_SUFFIX[u_bit];
            generate_ls_ldr_pc_instruction(func_name,cond,opcode,
                                           (LSOperandMode) opm,
                                           (AddressingMode) addr_m,
                                           u_bit);
            if (u_bit == 0)  header_file << ", ";
          } // end u loop
          closeArrayRow(header_file);
          if (addr_m < addrm_to) header_file << ", ";
        } // end address mode loop
        closeArrayRow(header_file);
        if (opm < opm_to)  header_file << ", ";
    }//end oprand mode loop
    closeArrayRow(header_file);
    if (cond < LAST_COND_CODE)  header_file << ", ";
  } // end of condition code loop
  closeArrayDecl(header_file);
}




void LoadStoreGenerator::generate()
{
  openFileSet("armpi_loadstore_admode2_9");
  generate_ls_func_table("arm_loadstore_admode2_9_table",
                         "arm_loadstore_admode2_9",
                         FIRST_LSOP_ADMODE2_9, LAST_LSOP_ADMODE2_9,
                         FIRST_OP_MODE_LS,LAST_OP_MODE_LS,
                         FIRST_ADDRESS_MODE, LAST_ADDRESS_MODE);
  closeFileSet();
  openFileSet("armpi_loadstore_admode2_9_zero");
  generate_ls_zero_func_table("arm_loadstore_admode2_9_zero_table",
                              "arm_loadstore_admode2_9_zero",
                              FIRST_LSOP_ADMODE2_9, LAST_LSOP_ADMODE2_9);
  closeFileSet();
  openFileSet("armpi_loadstore_admode2_3");
  generate_ls_func_table("arm_loadstore_admode2_3_table",
                         "arm_loadstore_admode2_3",
                         FIRST_LSOP_ADMODE2_3, LAST_LSOP_ADMODE2_3,
                         FIRST_OP_MODE_LS, LAST_OP_MODE_LS,
                         FIRST_ADDRESS_MODE, LAST_ADDRESS_MODE// ,
                         // 			 false, false
                         );
  closeFileSet();
  openFileSet("armpi_loadstore_admode3_6");
  generate_ls_func_table("arm_loadstore_admode3_6_table",
                         "arm_loadstore_admode3_6",
                         FIRST_LSOP_ADMODE3_6, LAST_LSOP_ADMODE3_6,
                         FIRST_OP_MODE_LS,LAST_OP_MODE_NSH_LS,
                         FIRST_ADDRESS_MODE, LAST_ADDRESS_MODE// ,
                         // 			 false, false
                         );
  closeFileSet();

  openFileSet("armpi_ldr_pc_admode2_9");
  generate_LDR_PC_func_table("arm_ldr_pc_admode2_9_table",
                             "arm_ldr_pc_admode2_9",LDR,
                             FIRST_OP_MODE_LS,LAST_OP_MODE_LS,
                             FIRST_ADDRESS_MODE, LAST_ADDRESS_MODE);
  closeFileSet();
}

