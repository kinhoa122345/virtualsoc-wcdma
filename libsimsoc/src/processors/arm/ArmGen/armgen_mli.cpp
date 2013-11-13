//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "armgen_mli.hpp"

using namespace std;

MLI_Opcode & operator++ (MLI_Opcode &op) {
  return (MLI_Opcode &) ++((int &) op);
}

/*
 * MLI_Generator Class to generate Multiply Instructions
 */

/*
 * Generate code for one semantic function
 * Print to files the generated  strings
 */
void MLI_Generator::generate_instruction(const string prefix,
                                         const ConditionCode cond,
                                         const int s_bit,
                                         const MLI_Opcode opcode)
{
  ostringstream body  ;
  string func_name = prefix;
  // print function name
  code_file << "// Semantic function " << endl;
  code_file << PSEUDO_TYPE << func_name << ARGS <<endl;
  // generate function body
  body <<'{' <<endl;
  body <<"  proc.debug() <<\"" <<func_name <<"\" <<std::endl;" <<endl;
  generate_condition_code(body, cond);
  // invoke the operation method for this operator
  generate_operation(body, s_bit, opcode);
  code_file << body.str() << "  return OK;" << endl << "}" << endl;

  // print function name to include file for declaration
  //   func_list_file << FUNC_TYPE << func_name << " ;" << endl;
  // print function name to table file for static array  initialization
  header_file << func_name << " " ;
}

/*
 * the generic function to generate an array of functions and their code
 */

void MLI_Generator::generate_func_table(const string table_name,
                                        const string prefix,
                                        const MLI_Opcode opcode_from,
                                        const MLI_Opcode opcode_to)
{
  string func_name = prefix;
  int dim;
  int *func_array_struct;
  //   int level; // indentation level inside array

  // Compute number of dimensions for the array of functions, maximum is 8
  func_array_struct = new int [8];
  func_array_struct[0] = LAST_COND_CODE + 1; // N conditions codes
  func_array_struct[1] = 2 ; // bit S is 0 or 1
  func_array_struct[2] = opcode_to - opcode_from + 1 ; // N operation types
  dim = 3;
  // create table declaration in header file
  openArrayDecl(header_file, table_name, func_array_struct, dim);
  // now loop on all specialized functions
  // print ',' after each element of an array
  // but do not print ',' after last element of an array
  for (ConditionCode cond=FIRST_COND_CODE ; cond <= LAST_COND_CODE ; ++cond) {
    newArrayRow(header_file); // generate curly bracket
    for (int s_bit=0; s_bit <= 1; ++s_bit) {
      newArrayRow(header_file);
      for (int opcode = opcode_from; opcode<=opcode_to; ++opcode) {
        func_name = prefix +COND_CODE_SUFFIX[cond]
          + FLAGS_SUFFIX[s_bit] + MLI_OPCODE_SUFFIX[opcode];
        generate_instruction(func_name,cond,s_bit, (MLI_Opcode) opcode);
        if (opcode!=opcode_to)
          header_file << ", "; // debug << " /* opcode */" ;
      } // end opcode loop
      closeArrayRow(header_file);
      if (s_bit < 1)
        header_file << ", "; // debug << " /* s bit */" ;
    } // end s_bit loop
    closeArrayRow(header_file);
    if (cond < LAST_COND_CODE)
      header_file << ", "; // debug << " /* cond */ " ;
  } // end condition code loop
  closeArrayDecl(header_file);
}
/*
 * Generate code corresponding to one specific operation
 * ARM Multiply operations take operand in Rs and Rm ,only in the M   LA,register Rn is used.
 * The value of Rs is stored in variable tmp,the value of Rm is sto   red in variable opv,the value of Rn is stored in variable val
 * if the operation is 32 bit, the operation result is stored in va   riable r , then r is stored in destination register Rd.
 * if the operation is 64 bit,the operation is stored in variable r   l and rh,then rl is stored in destionation register RdLo,rh is s   tored in destionation register RdHi
 */

void MLI_Generator::generate_operation(ostringstream &body,
                                       const int s_bit,
                                       const MLI_Opcode opcode) {
  if (MUL==opcode||opcode==MLA) {
    body << "  uint32_t tmp = proc.cpu.regs[p.args.any_reg.Rs]; "<<endl;
    body << "  uint32_t opv = proc.cpu.regs[p.args.any_reg.Rm];"<<endl;

    switch (opcode) {
    case MUL:
      body << "  uint32_t r = tmp * opv;"<<endl;
      break;
    case MLA:
      body << "  uint32_t val = proc.cpu.regs[p.args.any_reg.Rn]; "<<endl;
      body << "  uint32_t r = tmp*opv+val;" << endl;
      break;
    default:
      Fatal("illegal MLI operation (a)");
    }

    body << "  proc.cpu.regs[p.args.any_reg.Rd] = r;" <<endl;
    if (s_bit) {
      body << "  proc.cpu.cpsr.n = r&0x80000000;" << endl;
      body << "  proc.cpu.cpsr.z =! r;" << endl;
    }
  } else if (SMULL==opcode||opcode==SMLAL) { // SMULL and SMLAL instructions
    body << "  int64_t tmp = (int32_t) proc.cpu.regs[p.args.mli_64.Rs];" << endl;
    body << "  int64_t opv = (int32_t) proc.cpu.regs[p.args.mli_64.Rm];" << endl;
    switch (opcode) {
    case SMULL:
      body << "  int64_t r = tmp * opv;"<<endl;
      body << "  int32_t rl =r; "<<endl;
      body << "  int32_t rh =r>>32; "<<endl;
      break;
    case SMLAL:
      body << "  int32_t vdh = proc.cpu.regs[p.args.mli_64.RdHi];" << endl;
      body << "  int32_t vdl = proc.cpu.regs[p.args.mli_64.RdLo];" << endl;
      body << "  int64_t r = vdh ;" << endl;
      body << "          r = r<<32 ;" << endl;
      body << "          r = tmp*opv+r+vdl;" << endl;
      body << "  int32_t rl = r;" << endl;
      body << "  int32_t rh = r>>32 ;" << endl;
      break;
    default:
      Fatal("illegal MLI operation (b)");
    }
    body << "  proc.cpu.regs[p.args.mli_64.RdHi] = rh;" <<endl;
    body << "  proc.cpu.regs[p.args.mli_64.RdLo] = rl;" <<endl;
    if (s_bit) {
      body << "  proc.cpu.cpsr.n = rh&0x80000000;" << endl;
      body << "  proc.cpu.cpsr.z =! r;" << endl;
    }
  } else if (UMULL==opcode||opcode==UMLAL) { //UMULL and UMLAL
    body << "  uint64_t tmp = proc.cpu.regs[p.args.mli_64.Rs];" << endl;
    body << "  uint64_t opv = proc.cpu.regs[p.args.mli_64.Rm];" << endl;
    switch (opcode) {
    case UMULL:
      body << "  uint64_t r = tmp * opv;"<<endl;
      body << "  uint32_t rl =r; "<<endl;
      body << "  uint32_t rh =r>>32; "<<endl;
      break;
    case UMLAL:
      body << "  uint32_t vdh = proc.cpu.regs[p.args.mli_64.RdHi];" << endl;
      body << "  uint32_t vdl = proc.cpu.regs[p.args.mli_64.RdLo];" << endl;
      body << "  uint64_t r = vdh;" << endl;
      body << "           r = r<<32;" << endl;
      body << "           r = tmp*opv+r+vdl;" << endl;
      body << "  uint32_t rl = r;" << endl;
      body << "  uint32_t rh = r>>32;" << endl;
      break;
    default:
      Fatal("illegal MLI operation (c)");
    }
    body << "  proc.cpu.regs[p.args.mli_64.RdHi] = rh;" <<endl;
    body << "  proc.cpu.regs[p.args.mli_64.RdLo] = rl;" <<endl;
    if (s_bit) {
      body << "  proc.cpu.cpsr.n = rh&0x80000000;" << endl;
      body << "  proc.cpu.cpsr.z = !r;" << endl;
    }
  } else
    Fatal("illegal MLI operation");
}
void MLI_Generator::generate()
{  // one file for all 32 bit multiply instructions
  openFileSet("armpi_mli_32");
  generate_func_table("arm_mli_32_table", "arm_mli",
                      FIRST_32_MLI , LAST_32_MLI);
  closeFileSet();
  // one file for all 64 bit int multiply  operation instructions
  openFileSet("armpi_mli_64_int");
  generate_func_table("arm_mli_64_int_table", "arm_mli",
                      FIRST_64_Int_MLI, LAST_64_Int_MLI );
  closeFileSet();
  openFileSet("armpi_mli_64_uint");
  // one file for all boolean operation instructions
  generate_func_table("arm_mli_64_uint_table", "arm_mli",
                      FIRST_64_Uint_MLI, LAST_64_Uint_MLI );
  closeFileSet();
}
