//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "armgen_mrsmsr.hpp"

using namespace std;

M_OperandMode &operator++ (M_OperandMode &m){
  return (M_OperandMode &) ++ ((int &) m);
}

void MRSMSR_Generator:: generate_operand_code(ostringstream &oss,
                                              const M_OperandMode opm)
{
  switch (opm){
  case _8_bit_immediate:
    oss << "  uint32_t opv = p.args.msr_imm_reg.immed;"  << endl;
    break;

  case m_registers:
    oss << "  uint32_t opv = proc.cpu.regs[p.args.msr_imm_reg.Rm];" << endl;
    break;
  default: Fatal("illegal data processing operand" );
  }
}


void MRSMSR_Generator::generate_mrs_func_table(const string table_name,
                                               const string prefix)
{
  string func_name = prefix;
  ConditionCode cond;
  int dim;
  int *func_array_struct;
  //   int level; // indentation level inside array

  // Compute number of dimensions for the array of functions, maximum is 8
  func_array_struct = new int [8];
  func_array_struct[0] = LAST_COND_CODE + 1; // N conditions codes
  func_array_struct[1] = 2 ; // bit R is 0 or 1
  dim = 2;
  // create table declaration in header file
  openArrayDecl(header_file, table_name, func_array_struct, dim);
  // now loop on all specialized functions
  // print ',' after each element of an array
  // but do not print ',' after last element of an array
  for (cond=FIRST_COND_CODE ; cond <= LAST_COND_CODE ; ++cond) {
    newArrayRow(header_file); // generate curly bracket
    for (int r_bit=0; r_bit <= 1; ++r_bit) {
      func_name = prefix + COND_CODE_SUFFIX[cond]
        + R_SUFFIX[r_bit] + M_OPCODE_SUFFIX[0];
      generate_mrs_instruction(func_name,cond,r_bit);
      if (r_bit < 1)
        header_file << ", "; // debug << " /* r bit */" ;
    } // end s_bit loop
    closeArrayRow(header_file);
    if (cond < LAST_COND_CODE)
      header_file << ", "; // debug << " /* cond */ " ;
  } // end condition code loop
  closeArrayDecl(header_file);
}

void MRSMSR_Generator::generate_msr_func_table(const string table_name,
                                               const string prefix,
                                               const M_OperandMode opm_from,
                                               const M_OperandMode opm_to)
{
  string func_name = prefix;
  ConditionCode cond;
  int dim;
  int *func_array_struct;
  //   int level; // indentation level inside array

  // Compute number of dimensions for the array of functions, maximum is 8
  func_array_struct = new int [8];
  func_array_struct[0] = LAST_COND_CODE + 1; // N conditions codes
  func_array_struct[1] = 2 ; // bit R is 0 or 1
  func_array_struct[2] = 2 ; // operand mode
  dim = 3;
  // create table declaration in header file
  openArrayDecl(header_file, table_name, func_array_struct, dim);
  // now loop on all specialized functions
  // print ',' after each element of an array
  // but do not print ',' after last element of an array
  for (cond=FIRST_COND_CODE ; cond <= LAST_COND_CODE ; ++cond) {
    int r_bit;
    newArrayRow(header_file); // generate curly bracket
    for (r_bit=0; r_bit <= 1; ++r_bit) {
      newArrayRow(header_file);
      for (int opm= opm_from; opm <= opm_to ; ++opm) {
        func_name = prefix + COND_CODE_SUFFIX[cond]
          + R_SUFFIX[r_bit] + M_OP_MODE_SUFFIX[opm];
        generate_msr_instruction(func_name,cond,r_bit,(M_OperandMode) opm);
        if (opm < opm_to)
          header_file << ", " ; // debug << "/* mode */" ;
      } //end operand loop
      closeArrayRow(header_file);
      if (r_bit < 1)
        header_file << ", "; // debug << " /* r bit */" ;
    } // end s_bit loop
    closeArrayRow(header_file);
    if (cond < LAST_COND_CODE)
      header_file << ", "; // debug << " /* cond */ " ;
  } // end condition code loop
  closeArrayDecl(header_file);
}

void MRSMSR_Generator::generate_mrs_instruction(const string func_name,
                                                const ConditionCode cond,
                                                const int r_bit)
{ ostringstream body  ;

  // print function name
  code_file << "// Semantic function " << endl;
  code_file << PSEUDO_TYPE <<func_name <<  ARGS <<endl;
  // generate function body
  body <<'{' <<endl;
  body <<"  proc.debug() <<\"" <<func_name <<"\" <<std::endl;" <<endl;

  generate_condition_code(body, cond);

  if(r_bit == 1) {
    body <<"  uint32_t x = 0;" <<endl;
    body <<"  if (proc.cpu.spsr().n) " <<endl;
    body <<"    x |= 1<<31;" <<endl;
    body <<"  if (proc.cpu.spsr().z) " <<endl;
    body <<"    x |= 1<<30;" <<endl;
    body <<"  if (proc.cpu.spsr().c) " <<endl;
    body <<"    x |= 1<<29;" <<endl;
    body <<"  if (proc.cpu.spsr().v) " <<endl;
    body <<"    x |= 1<<28;" <<endl;
    body <<"  if (proc.cpu.spsr().q) " <<endl;
    body <<"    x |= 1<<27;" <<endl;
    body <<"  if (proc.cpu.spsr().i) " <<endl;
    body <<"    x |= 1<<7;" <<endl;
    body <<"  if (proc.cpu.spsr().f) " <<endl;
    body <<"    x |= 1<<6;" <<endl;
    body <<"  if (proc.cpu.spsr().t) " <<endl;
    body <<"    x |= 1<<5;" <<endl;
    body <<" x |= ARM_StatusRegister::MODE_BITS[proc.cpu.spsr().mode];" <<endl;
    body <<" proc.cpu.regs[p.args.any_reg.Rd] = x;" <<endl;
  } else {
    body <<"  uint32_t x = 0;" <<endl;
    body <<"  if (proc.cpu.cpsr.n) " <<endl;
    body <<"    x |= 1<<31;" <<endl;
    body <<"  if (proc.cpu.cpsr.z) " <<endl;
    body <<"    x |= 1<<30;" <<endl;
    body <<"  if (proc.cpu.cpsr.c) " <<endl;
    body <<"    x |= 1<<29;" <<endl;
    body <<"  if (proc.cpu.cpsr.v) " <<endl;
    body <<"    x |= 1<<28;" <<endl;
    body <<"  if (proc.cpu.cpsr.q) " <<endl;
    body <<"    x |= 1<<27;" <<endl;
    body <<"  if (proc.cpu.cpsr.i) " <<endl;
    body <<"    x |= 1<<7;" <<endl;
    body <<"  if (proc.cpu.cpsr.f) " <<endl;
    body <<"    x |= 1<<6;" <<endl;
    body <<"  if (proc.cpu.cpsr.t) " <<endl;
    body <<"    x |= 1<<5;" <<endl;
    body <<"  x |= ARM_StatusRegister::MODE_BITS[proc.cpu.cpsr.mode];" <<endl;
    body <<"  proc.cpu.regs[p.args.any_reg.Rd] = x;" <<endl;
  }
  code_file <<body.str()
            <<"  return OK;" <<endl
            <<'}' <<endl;
  header_file <<func_name <<" " ;
}

void MRSMSR_Generator::generate_msr_instruction(const string func_name,
                                                const ConditionCode cond,
                                                const int r_bit,
                                                const M_OperandMode opm)
{
  ostringstream body;
  //  string  func_name = prefix;

  // print function name
  code_file <<"// Semantic function " <<endl;
  code_file <<PSEUDO_TYPE <<func_name <<ARGS <<endl;
  // generate function body
  body <<'{' <<endl;
  body <<"  proc.debug() <<\"" <<func_name <<"\" <<std::endl;" <<endl;
  generate_condition_code(body, cond);
  generate_operand_code(body,opm);
  body <<"  uint8_t field_mask = p.args.msr_imm_reg.field;" <<endl;
  if(r_bit == 0) {
    body <<"  if (proc.cpu.cpsr.mode==ARM_USER)\n"
         <<"    field_mask &= ~1;\n";
    body <<"  if (field_mask&1 && (proc.cpu.cpsr.t!=opv&(1<<5))) {\n"
         <<"    proc.error() <<\"attempt to alter the T bit using MSR\" <<std::endl;\n"
         <<"    exit(1);\n"
         <<"  }" <<endl;
    body <<"  proc.set_cpsr(opv,field_mask);" <<endl;
  } else {
    body <<"  if (field_mask&(1<<0)) {" <<endl;
    body <<"    proc.cpu.spsr().mode = arm_mode(opv&0x1F);" <<endl;
    body <<"    proc.cpu.spsr().t = opv&(1<<5);" <<endl;
    body <<"    proc.cpu.spsr().f = opv&(1<<6);" <<endl;
    body <<"    proc.cpu.spsr().i = opv&(1<<7);" <<endl;
    body <<"  }" <<endl;
    body <<"  if(field_mask&(1<<3)){" <<endl;
    body <<"    proc.cpu.spsr().q = opv&(1<<27);" <<endl;
    body <<"    proc.cpu.spsr().v = opv&(1<<28);" <<endl;
    body <<"    proc.cpu.spsr().c = opv&(1<<29);" <<endl;
    body <<"    proc.cpu.spsr().z = opv&(1<<30);" <<endl;
    body <<"    proc.cpu.spsr().n = opv&(1<<31);" <<endl;
    body <<"  }" <<endl;
  }
  code_file <<body.str()
            <<"  return OK;" <<endl
            <<'}' <<endl;
  header_file << func_name << " " ;
}


void MRSMSR_Generator::generate()
{
  //one file for mrs instruction
  openFileSet("armpi_mrs");
  generate_mrs_func_table("arm_mrs_table","arm_mrs");
  closeFileSet();
  //one file for msr instruction
  openFileSet("armpi_msr");
  generate_msr_func_table("arm_msr_table","arm_msr",
                          FIRST_MODE,LAST_MODE);
  closeFileSet();
}

