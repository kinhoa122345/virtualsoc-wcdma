//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "armgen_ldmstm.hpp"

using namespace std;

LdmStmOpcode & operator++ (LdmStmOpcode &op){
  return (LdmStmOpcode &) ++ ((int &) op);
}

AddressMode &operator++ (AddressMode &am) {
  return (AddressMode &) ++((int &) am);
}

void LdmStmGenerator::generate_address(ostringstream &oss,
                                       const AddressMode am,
                                       const int w_bit)
{
  switch(am){
  case IA:
    oss <<"  uint8_t Rn = p.args.load_store_mult.Rn;"<<endl;
    oss <<"  uint16_t registers = p.args.load_store_mult.registers; "<<endl;
    oss <<"  uint32_t start_address = proc.cpu.regs[Rn];"<<endl;
//    if(w_bit == 1)
//      oss <<"  proc.cpu.regs[Rn]=proc.cpu.regs[Rn]+(p.args.load_store_mult.nb_reg*4); "<<endl;
    break;
  case IB:
    oss <<"  uint8_t Rn = p.args.load_store_mult.Rn;"<<endl;
    oss <<"  uint16_t registers = p.args.load_store_mult.registers; "<<endl;
    oss <<"  uint32_t start_address = proc.cpu.regs[Rn]+4;"<<endl;
//    if(w_bit == 1)
//      oss <<"  proc.cpu.regs[Rn]=proc.cpu.regs[Rn]+(p.args.load_store_mult.nb_reg*4); "<<endl;
    break;
  case DA:
    oss <<"  uint8_t Rn = p.args.load_store_mult.Rn;"<<endl;
    oss <<"  uint8_t number_of_registers = p.args.load_store_mult.nb_reg;"<<endl;
    oss <<"  uint16_t registers = p.args.load_store_mult.registers; "<<endl;
    oss <<"  uint32_t start_address = proc.cpu.regs[Rn] - number_of_registers*4 +4;"<<endl;
//    if(w_bit == 1)
//      oss <<"  proc.cpu.regs[Rn]=proc.cpu.regs[Rn]-(number_of_registers*4); "<<endl;
    break;
  case DB:
    oss <<"  uint8_t Rn = p.args.load_store_mult.Rn;"<<endl;
    oss <<"  uint8_t number_of_registers = p.args.load_store_mult.nb_reg;"<<endl;
    oss <<"  uint16_t registers = p.args.load_store_mult.registers; "<<endl;
    oss <<"  uint32_t start_address = proc.cpu.regs[Rn] - number_of_registers*4;"<<endl;
 //   if(w_bit == 1)
 //     oss <<"  proc.cpu.regs[Rn]=proc.cpu.regs[Rn]-(number_of_registers*4); "<<endl;
    break;
  default: Fatal("illegal address mode");
  }
}

void LdmStmGenerator::generate_Rn_address_offset(ostringstream &oss,
                                       const AddressMode am)
{
  switch(am){
  case IA:
      oss <<"  proc.cpu.regs[Rn]=proc.cpu.regs[Rn]+(p.args.load_store_mult.nb_reg*4); "<<endl;
    break;
  case IB:
      oss <<"  proc.cpu.regs[Rn]=proc.cpu.regs[Rn]+(p.args.load_store_mult.nb_reg*4); "<<endl;
    break;
  case DA:
      oss <<"  proc.cpu.regs[Rn]=proc.cpu.regs[Rn]-(p.args.load_store_mult.nb_reg*4); "<<endl;
    break;
  case DB:
      oss <<"  proc.cpu.regs[Rn]=proc.cpu.regs[Rn]-(p.args.load_store_mult.nb_reg*4); "<<endl;
    break;
  default: ;
  }
}

void LdmStmGenerator::generate_stm_func_table(const string table_name,
                                              const string prefix,
                                              const LdmStmOpcode opcode_from,
                                              const LdmStmOpcode opcode_to,
                                              const AddressMode addrm_from,
                                              const AddressMode addrm_to)
{
  string func_name = prefix;
  ConditionCode cond;
  int dim;
  int *func_array_struct;
  //   int level; // indentation level inside array
  // Compute number of dimensions for the array of functions, maximum is 8
  func_array_struct = new int [8];
  func_array_struct[0] = LAST_COND_CODE + 1; // N conditions codes
  func_array_struct[1] = 2 ; // bit W is 0 or 1
  func_array_struct[2] = opcode_to - opcode_from + 1 ; // N operation types
  func_array_struct[3] = addrm_to - addrm_from + 1 ; // N addressing mode
  dim = 4;
  // create table declaration in header file
  openArrayDecl(header_file, table_name, func_array_struct, dim);
  // now loop on all specialized functions
  // print ',' after each element of an array
  // but do not print ',' after last element of an array
  for (cond=FIRST_COND_CODE ; cond <= LAST_COND_CODE ; ++cond) {
    newArrayRow(header_file); // generate curly bracket
    for (int w_bit=0; w_bit <= 1; ++w_bit) {
      newArrayRow(header_file);
      for (int opcode=opcode_from; opcode <= opcode_to; ++opcode) {
        newArrayRow(header_file);
        for (int adm=addrm_from;adm <=addrm_to ; ++adm) {
          func_name = prefix + COND_CODE_SUFFIX[cond]
            + W_SUFFIX[w_bit] + LDM_STM_SUFFIX[opcode]
            + ADDRESSING_MODE_SUFFIX[adm];
          generate_stm_instruction(func_name, cond, w_bit,
                                   (LdmStmOpcode) opcode,
                                   (AddressMode) adm);
          if (adm < addrm_to)
            header_file << ", " ; // debug << "/* mode */" ;
        } //end addressing mode loop
        closeArrayRow(header_file);
        if (opcode < opcode_to)
          header_file << ", "; // debug << " /* opcode */" ;
      } // end opcode loop
      closeArrayRow(header_file);
      if (w_bit < 1)
        header_file << ", "; // debug << " /* s bit */" ;
    } // end w_bit loop
    closeArrayRow(header_file);
    if (cond < LAST_COND_CODE)
      header_file << ", "; // debug << " /* cond */ " ;
  } // end condition code loop
  closeArrayDecl(header_file);
}


void LdmStmGenerator::generate_ldm_func_table(const string table_name,
                                              const string prefix,
                                              const LdmStmOpcode opcode_from,
                                              const LdmStmOpcode opcode_to,
                                              const AddressMode addrm_from,
                                              const AddressMode addrm_to)
{
  string func_name = prefix;
  ConditionCode cond;
  int dim;
  int *func_array_struct;
  //   int level; // indentation level inside array
  // Compute number of dimensions for the array of functions, maximum is 8
  func_array_struct = new int [8];
  func_array_struct[0] = LAST_COND_CODE + 1; // N conditions codes
  func_array_struct[1] = 2 ; // bit W is 0 or 1
  func_array_struct[2] = 2 ; // register is PC or not
  func_array_struct[3] = opcode_to - opcode_from + 1 ; // N operation types
  func_array_struct[4] = addrm_to - addrm_from + 1 ; // N addressing mode
  dim = 5;
  // create table declaration in header file
  openArrayDecl(header_file, table_name, func_array_struct, dim);
  // now loop on all specialized functions
  // print ',' after each element of an array
  // but do not print ',' after last element of an array
  for (cond=FIRST_COND_CODE ; cond <= LAST_COND_CODE ; ++cond) {
    newArrayRow(header_file); // generate curly bracket
    for (int w_bit=0; w_bit <= 1; ++w_bit) {
      newArrayRow(header_file);
      for (int reg_pc=0;reg_pc<=1 ; ++reg_pc) {
        newArrayRow(header_file);
        for (int opcode=opcode_from; opcode <= opcode_to; ++opcode) {
          newArrayRow(header_file);
          for (int adm=addrm_from;adm <=addrm_to ; ++adm) {
            func_name = prefix + COND_CODE_SUFFIX[cond]
              + W_SUFFIX[w_bit]+PC_SUFFIX[reg_pc]
              + LDM_STM_SUFFIX[opcode]+ ADDRESSING_MODE_SUFFIX[adm];
            generate_ldm_instruction(func_name, cond, w_bit,reg_pc,
                                     (LdmStmOpcode) opcode,
                                     (AddressMode) adm);

            if (adm < addrm_to)
              header_file << ", " ; // debug << "/* mode */" ;
          } //end addressing mode loop
          closeArrayRow(header_file);
          if (opcode < opcode_to)
            header_file << ", "; // debug << " /* opcode */" ;
        } // end opcode loop
        closeArrayRow(header_file);
        if (reg_pc < 1)
          header_file << ", " ; // debug << "/* reg_pc */" ;
      } //end register PC loop
      closeArrayRow(header_file);
      if (w_bit < 1)
        header_file << ", "; // debug << " /* s bit */" ;
    } // end w_bit loop
    closeArrayRow(header_file);
    if (cond < LAST_COND_CODE)
      header_file << ", "; // debug << " /* cond */ " ;
  } // end condition code loop
  closeArrayDecl(header_file);
}

void LdmStmGenerator::generate_ldm_instruction(const string func_name,
                                               const ConditionCode cond,
                                               const int w_bit,
                                               const int reg_pc,

                                               const LdmStmOpcode opcode,
                                               const AddressMode addr_m)
{
  ostringstream body ;
  // print to files the generated  strings
  // print function name
  code_file << "// Semantic function " << endl;
  code_file << PSEUDO_TYPE << func_name << ARGS << endl;
  // generate function body
  body <<  "{" << endl;
  body <<"  proc.debug() <<\"" <<func_name <<"\" <<std::endl;" <<endl;
  generate_condition_code(body, cond);
  generate_address(body,addr_m,w_bit);
  body <<"  uint32_t address = start_address;"<<endl;
  switch(opcode)
    {

    case LDM_1:
      body <<"  for (int i=0 ;i<=14;i++) {"<<endl;
      body <<"    if (registers&(1<<i)) {"<<endl;
      body <<"      proc.cpu.regs[i]=proc.mmu.read_word(address); "<<endl;
      body <<"      address += 4;"<<endl;
      body <<"    }"<<endl;
      body <<"  }"<<endl;
      if(reg_pc == 1)
        { body <<"  uint32_t value = proc.mmu.read_word(address);"<<endl;
          body <<"  address += 4; "<<endl;
          //body <<"  if (proc.cpu.cpsr.t == 1) {"<<endl;
          //body <<"    value = value&0xFFFFFFFE ;"<<endl;
          //body <<"    proc.cpu.set_thumb_mode(); "<<endl;
          //body <<"  }else"<<endl;
          //body<<"     value = value&0xFFFFFFFC; "<<endl;
          //body <<" proc.cpu.regs[ARM_CPU::PC] = value+8;"<<endl;
          body <<"  switch(value&3){"<<endl;
          body <<"  case 0: // 00"<<endl;
          body <<"    proc.cpu.regs[ARM_CPU::PC]=value+8;break;"<<endl;
          body <<"  case 2: // 10"<<endl;
          body <<"    proc.error()<<\"unpredictable branching to a non-aligned address.\"<<endl;"<<endl;
          body <<"  case 1: // 01"<<endl;
          body <<"  case 3: // 11"<<endl;
          body <<"    proc.cpu.regs[ARM_CPU::PC] = value & ~1+4;"<<endl;
          body <<"    proc.cpu.set_thumb_mode();"<<endl;
          body <<"  }"<<endl;
        }
      break;

    case LDM_3:
      body <<"  for (int i=0 ;i<=14;i++) {"<<endl;
      body <<"    if (registers&(1<<i)) {"<<endl;
      body <<"      proc.cpu.regs[i]=proc.mmu.read_word(address); "<<endl;
      body <<"      address += 4;"<<endl;
      body <<"    }"<<endl;
      body <<"  }"<<endl;
      break;


    default: Fatal("illegal LDMSTM instructions");
    }
    if(w_bit==1)
      		generate_Rn_address_offset(body,addr_m);
	if(opcode==LDM_3)
	{
		body <<"proc.spsr_to_cpsr();"<<endl;
      if(reg_pc == 1)
        { body <<"  uint32_t value = proc.mmu.read_word(address);"<<endl;
          body <<"  address += 4; "<<endl;
          body <<"  if (proc.cpu.cpsr.t == 1) {"<<endl;
          body <<"    value = value&0xFFFFFFFE ;"<<endl;
          body <<"    proc.cpu.set_thumb_mode(); "<<endl;
          body <<"    proc.cpu.regs[ARM_CPU::PC] =value+4;"<<endl;
          body <<"  }else{"<<endl;
          body <<"  if(value & 2){"<<endl;
          body <<"    proc.error()<<\"unpredictable branching to a non-aligned address\"<<endl;"<<endl;
          body <<"    exit(5);}"<<endl;
          body <<"     value = value&0xFFFFFFFC; "<<endl;
          body <<"     proc.cpu.regs[ARM_CPU::PC] = value+8;}"<<endl;
          //body <<" proc.cpu.regs[ARM_CPU::PC] = value+8;"<<endl;
         }
	}
  if(reg_pc == 1)
    code_file << body.str() << "  return BRANCH ;" << endl << "}" << endl;
  else
    code_file << body.str() << "  return OK ;" << endl << "}" << endl;
  header_file << func_name << " " ;
}


void LdmStmGenerator::generate_stm_instruction(const string func_name,
                                               const ConditionCode cond,
                                               const int w_bit,

                                               const LdmStmOpcode opcode,
                                               const AddressMode addr_m)
{
  ostringstream body ;
  // print to files the generated  strings
  // print function name
  code_file << "// Semantic function " << endl;
  code_file << PSEUDO_TYPE << func_name << ARGS << endl;
  // generate function body
  body <<  "{" << endl;
  body <<"  proc.debug() <<\"" <<func_name <<"\" <<std::endl;" <<endl;

  generate_condition_code(body, cond);
  generate_address(body,addr_m,w_bit);
  body <<"  uint32_t address = start_address;"<<endl;
  switch(opcode)
    {
    case STM_1:
      body <<"  for (int i=0 ;i<=15;i++) {"<<endl;
      body <<"    if (registers&(1<<i)) {"<<endl;
      body <<"      proc.mmu.write_word(address,proc.cpu.regs[i]); "<<endl;
      body <<"      address += 4;"<<endl;
      body <<"    }"<<endl;
      body <<"  }"<<endl;
      break;
    case STM_2:
      body <<"  for (int i=0 ;i<=15;i++) {"<<endl;
      body <<"    if (registers&(1<<i)) {"<<endl;
      body <<"      proc.mmu.write_word(address,proc.cpu.user_regs(i)); "<<endl;
      body <<"      address += 4;"<<endl;
      body <<"    }"<<endl;
      body <<"  }"<<endl;
      break;
    case LDM_2:
      body <<"  for (int i=0 ;i<=14;i++) {"<<endl;
      body <<"    if (registers&(1<<i)) {"<<endl;
      body <<"      proc.cpu.user_regs(i)=proc.mmu.read_word(address); "<<endl;
      body <<"      address += 4;"<<endl;
      body <<"    }"<<endl;
      body <<"  }"<<endl;
      break;

    default: Fatal("illegal LDMSTM instructions");
    }
    if(w_bit==1)
      		generate_Rn_address_offset(body,addr_m);

  code_file << body.str() << "  return OK ;" << endl << "}" << endl;
  header_file << func_name << " " ;
}


void LdmStmGenerator::generate()
{
  openFileSet("armpi_ldmstm_pc");
  generate_ldm_func_table("arm_ldmstm_pc_table","arm_ldmstm_pc",
                          FIRST_LDMOP,LAST_LDMOP,
                          FIRST_ADDRESSING_MODE, LAST_ADDRESSING_MODE);
  closeFileSet();

  openFileSet("armpi_ldmstm_nopc");
  generate_stm_func_table("arm_ldmstm_nopc_table",
                          "arm_ldmstm_nopc",
                          FIRST_STMOP,LAST_STMOP,
                          FIRST_ADDRESSING_MODE, LAST_ADDRESSING_MODE);
  closeFileSet();
}


