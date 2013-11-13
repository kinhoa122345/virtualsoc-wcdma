//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "armgen_swp.hpp"

using namespace std;

SWP_Opcode & operator++ (SWP_Opcode &op){
  return (SWP_Opcode &) ++ ((int &) op );
}


void SWP_Generator::generate_swp_instruction (const string func_name,
                                              const ConditionCode cond,
                                              const SWP_Opcode op,
                                              const bool specialize_Rd,
                                              const int reg_d,
                                              const bool specialize_Rn,
                                              const int reg_n,
                                              const bool specialize_Rm,
                                              const int reg_m)
{
  ostringstream body  ;

  // print function name
  code_file << "// Semantic function " << endl;
  code_file << PSEUDO_TYPE <<func_name <<  ARGS <<endl;
  // generate function body
  body <<'{' <<endl;
  body <<"  proc.debug() <<\"" <<func_name <<"\" <<std::endl;" <<endl;
  generate_condition_code(body, cond);

  // body <<"  YIELD();\n"; // DO NOT COMMIT
  if (specialize_Rn)
    body << "  uint32_t addr= proc.cpu.regs[" <<reg_n << "] ; " <<endl;
  else
    body << "  uint32_t addr= proc.cpu.regs[p.args.any_reg.Rn] ; " << endl;
  if (specialize_Rm)
    body << "  uint32_t tmpm= proc.cpu.regs[" <<reg_m << "] ; "<<endl;
  else
    body << "  uint32_t tmpm= proc.cpu.regs[p.args.any_reg.Rm] ; " <<endl;
  if (op == SWP)
    {
      body << "  uint32_t data = proc.mmu.read_word(addr) ;" <<endl;
      if (specialize_Rd)
        body << "  proc.cpu.regs[" <<reg_d << "] = data ; " <<endl;
      else
        body << "   proc.cpu.regs[p.args.any_reg.Rd] = data ; " <<endl;
      body << "  proc.mmu.write_word(addr,tmpm) ;" <<endl;
    }
  else
    {
      body << "  uint32_t data =proc.mmu.read_byte(addr) ;" <<endl;
      if (specialize_Rd)
        body << "  proc.cpu.regs[" <<reg_d << "] = data ; " <<endl;
      else
        body << "   proc.cpu.regs[p.args.any_reg.Rd] = data ; " <<endl;
      body << "  proc.mmu.write_byte(addr,tmpm) ;" <<endl;
    }

  code_file << body.str() << "  return OK;" << endl << "}" << endl;
  header_file << func_name << " " ;
}

void SWP_Generator:: generate_swp_func_table(const string table_name,
                                             const string prefix,
                                             const SWP_Opcode opcode_from,
                                             const SWP_Opcode opcode_to,
                                             bool specialize_Rd,
                                             bool specialize_Rn,
                                             bool specialize_Rm)
{ string func_name = prefix;
  int dim;
  int *func_array_struct;
  int cond;
  func_array_struct = new int [5];
  func_array_struct[0] = (int) LAST_COND_CODE + 1; // N conditions codes
  func_array_struct[1] = opcode_to - opcode_from + 1 ; // N operation types
  dim = 2;
  // create table declaration in header file
  openArrayDecl(header_file, table_name, func_array_struct, dim);
  // now loop on all specialized functions
  // print ',' after each element of an array
  // but do not print ',' after last element of an array
  for (cond=(int) FIRST_COND_CODE ; cond <= (int) LAST_COND_CODE ; ++cond) {
    int opcode;
    newArrayRow(header_file); // generate curly bracket
    for (opcode=(int) opcode_from; opcode <= (int) opcode_to; ++opcode) {
      func_name = prefix + COND_CODE_SUFFIX[cond]
            +SWP_OPCODE_SUFFIX[opcode];
          generate_swp_instruction(func_name,(ConditionCode) cond, (SWP_Opcode) opcode,
                                  specialize_Rd,0,specialize_Rn,0,
                                  specialize_Rm,0);

          if (opcode < (int) opcode_to)
            header_file << ", "; // debug << " /* opcode */" ;
      } // end opcode loop
      closeArrayRow(header_file);
      if (cond < (int) LAST_COND_CODE)
      header_file << ", "; // debug << " /* cond */ " ;
  } // end condition code loop
  closeArrayDecl(header_file);
}

void SWP_Generator::generate()
{
  // one file for all swp and swpb instructions
  openFileSet("armpi_swp");
  generate_swp_func_table("arm_swp_table", "arm_swp",
                          FIRST_SWP , LAST_SWP ,
                          false, false,false);
  closeFileSet();
}
