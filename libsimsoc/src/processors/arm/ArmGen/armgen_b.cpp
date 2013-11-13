//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "armgen_b.hpp"

using namespace std;

B_Opcode & operator++ (B_Opcode &op){
  return (B_Opcode &) ++ ((int &) op );
}

//in this function ,will generate 15*3*2 = 90 functions
// 15 condition code ,3 opcodes, 2 sp bit
// in B,BL,BX_1,we need to judge whether next instruction is in the same page.
void B_Generator:: generate_b_sp_func_table(const string table_name,
                                            const string prefix,
                                            const B_Opcode opcode_from,
                                            const B_Opcode opcode_to)
{ string func_name = prefix;
  int dim;
  int *func_array_struct;
  ConditionCode cond;
  func_array_struct = new int [5];
  func_array_struct[0] = LAST_COND_CODE + 1; // N conditions codes
  func_array_struct[1] = opcode_to - opcode_from + 1 ; // N operation types
  func_array_struct[2] = 2 ;// branch in the same page or not
  dim = 3;
  // create table declaration in header file
  openArrayDecl(header_file, table_name, func_array_struct, dim);
  // now loop on all specialized functions
  // print ',' after each element of an array
  // but do not print ',' after last element of an array
  for (cond=FIRST_COND_CODE ; cond <= LAST_COND_CODE ; ++cond) {
    newArrayRow(header_file); // generate curly bracket
    for (int opcode=opcode_from; opcode <= opcode_to; ++opcode) {
      newArrayRow(header_file); // generate curly bracket
      for (int sp = 0; sp <= 1; ++sp) {
        func_name = prefix + COND_CODE_SUFFIX[cond]
          +B_OPCODE_SUFFIX[opcode]+SP_SUFFIX[sp];
        generate_b_sp_instruction(func_name,cond,sp,(B_Opcode) opcode);
        if (sp< 1)
          header_file << ", "; // debug << " /* sp */" ;
      } // end sp loop
      closeArrayRow(header_file);
      if (opcode < opcode_to)
        header_file << ", "; // debug << " /* opcode */" ;
    } // end opcode loop
    closeArrayRow(header_file);
    if (cond < LAST_COND_CODE)
      header_file << ", "; // debug << " /* cond */ " ;
  } // end condition code loop
  closeArrayDecl(header_file);
}

//in this function ,will generate 15*2 = 30 functions
// 15 condition code , 2 opcodes
void B_Generator::generate_b_func_table(const string table_name,
                                        const string prefix,
                                        const B_Opcode opcode_from,
                                        const B_Opcode opcode_to)
{ string func_name = prefix;
  int dim;
  int *func_array_struct;
  ConditionCode cond;
  func_array_struct = new int [5];
  func_array_struct[0] = LAST_COND_CODE + 1; // N conditions codes
  func_array_struct[1] = opcode_to - opcode_from + 1 ; // N operation types
  dim = 2;
  // create table declaration in header file
  openArrayDecl(header_file, table_name, func_array_struct, dim);
  // now loop on all specialized functions
  // print ',' after each element of an array
  // but do not print ',' after last element of an array
  for (cond=FIRST_COND_CODE ; cond <= LAST_COND_CODE ; ++cond) {
    newArrayRow(header_file); // generate curly bracket
    for (int opcode=opcode_from; opcode <= opcode_to; ++opcode) {
      func_name = prefix + COND_CODE_SUFFIX[cond]
        +B_OPCODE_SUFFIX[opcode];;
      generate_b_instruction(func_name,cond,(B_Opcode) opcode);
      if (opcode < opcode_to)
        header_file << ", "; // debug << " /* opcode */" ;
    } // end opcode loop
    closeArrayRow(header_file);
    if (cond < LAST_COND_CODE)
      header_file << ", "; // debug << " /* cond */ " ;
  } // end condition code loop
  closeArrayDecl(header_file);

}

// generate instruction about BLX_2 and BX
void B_Generator:: generate_b_instruction(const string func_name,
                                          const ConditionCode cond,
                                          const B_Opcode opcode)
{
  ostringstream body  ;

  // print function name
  code_file << "// Semantic function " << endl;
  code_file << PSEUDO_TYPE <<func_name <<  ARGS <<endl;
  // generate function body
  body <<'{' <<endl;
  body <<"  proc.debug() <<\"" <<func_name <<"\" <<endl;" <<endl;
  generate_condition_code(body, cond);
  switch (opcode) {
  case BLX_2:
    body << "  proc.cpu.regs[ARM_CPU::LR] = proc.cpu.regs[ARM_CPU::PC]-4;" <<endl;
    body << "  uint32_t addr = proc.cpu.regs[p.args.any_reg.Rm];"<<endl;
    body << "  switch (addr&0x3) {" <<endl;
    body << "  case 0:"<<endl;
    body << "    proc.cpu.regs[ARM_CPU::PC] = addr+8; break;"<< endl;
    body << "  case 2: "<<endl;
    body  <<"    proc.error() <<\" the result is unpredictable (why?)\" <<endl;" <<endl;
    body  <<"     exit(1); break;" <<endl;
    body << "  case 1:"<<endl;
    body << "  case 3:"<<endl;
    body << "    proc.cpu.regs[ARM_CPU::PC] = (addr&0xFFFFFFFE)+4;" <<endl;
    body << "    proc.cpu.set_thumb_mode();\n    break;" <<endl;
    body << "  }"<<endl;
    break;

  case BX:
    body << "  uint32_t addr = proc.cpu.regs[p.args.any_reg.Rm];"<<endl;
     body << "  switch (addr&0x3) {" <<endl;
    body << "  case 0:"<<endl;
    body << "    proc.cpu.regs[ARM_CPU::PC] = addr+8; break;"<< endl;
    body << "  case 2: "<<endl;
    body  <<"    proc.error() <<\" the result is unpredictable\" <<endl;" <<endl;
    body  <<"     exit(1); break;" <<endl;
    body << "  case 1:"<<endl;
    body << "  case 3:"<<endl;
    body << "    proc.cpu.regs[ARM_CPU::PC] = (addr&0xFFFFFFFE)+4;" <<endl;
    body << "    proc.cpu.set_thumb_mode();\n    break;" <<endl;
    body << "  }"<<endl;
    break;

  default:
    Fatal("illegal BRANCH operation");
  }
  code_file << body.str() << "  return BRANCH;" << endl << "}" << endl;
  header_file << func_name << " " ;
}

// generate instructin for B , BL and BLX_1
void B_Generator:: generate_b_sp_instruction(const string func_name,
                                             const ConditionCode cond,
                                             const int  sp,
                                             const B_Opcode opcode)
{
  ostringstream body  ;

  // print function name
  code_file << "// Semantic function " << endl;
  code_file << PSEUDO_TYPE <<func_name <<  ARGS <<endl;
  // generate function body
  body <<'{' <<endl;
  body <<"  proc.debug() <<\"" <<func_name <<"\" <<endl;" <<endl;
  generate_condition_code(body, cond);
  switch (opcode) {
  case B:
    body << "  proc.cpu.regs[ARM_CPU::PC] += p.args.b_imm.offset;" << endl;
    break;
  case BL:
    body << "  proc.cpu.regs[ARM_CPU::LR] = proc.cpu.regs[ARM_CPU::PC]-4;" <<endl;
    body << "  proc.cpu.regs[ARM_CPU::PC] += p.args.b_imm.offset;"  << endl;
    break;
  case BLX_1:
    body << "  proc.cpu.regs[ARM_CPU::LR] = proc.cpu.regs[ARM_CPU::PC]-4;" <<endl;
    body << "  proc.cpu.regs[ARM_CPU::PC] += p.args.b_imm.offset;" << endl;
    body << "  proc.cpu.set_thumb_mode();" <<endl;
    break;
  default:
    Fatal("illegal BRANCH operation");
  }
  if (sp && opcode!=BLX_1)
    code_file << body.str() << "  return BRANCH_SAME_PAGE;" << endl << "}" << endl;
  else
    code_file << body.str() << "  return BRANCH;" << endl << "}" << endl;
  header_file << func_name << " " ;
}

void B_Generator::generate()
{
  // one file for  B and BL  instructions
  openFileSet("armpi_b_l");
  generate_b_sp_func_table("arm_b_l_table", "arm_b_l",
                           FIRST_L_B , LAST_L_B);
  closeFileSet();

  // one file for  BLX(1)  instruction
  openFileSet("armpi_b_h");
  generate_b_sp_func_table("arm_b_h_table", "arm_b_h",
                           OPCODE_H_B ,  OPCODE_H_B);
  closeFileSet();

  // one file for  BLX(2) and BX  instructions
  openFileSet("armpi_b_reg");
  generate_b_func_table("arm_b_reg_table", "arm_reg_h",
                        FIRST_Reg_B , LAST_Reg_B );
  closeFileSet();
}
