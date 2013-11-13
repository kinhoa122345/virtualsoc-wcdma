//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "armgen_swi.hpp"

using namespace std;

void SWI_Generator :: generate_swi_func_table(const string table_name,
                                              const string prefix)
{
  string func_name = prefix;
  int dim;
  int *func_array_struct;
  ConditionCode cond;
  func_array_struct = new int [5];
  func_array_struct[0] = LAST_COND_CODE + 1; // N conditions codes
  dim = 1;
  // create table declaration in header file
  openArrayDecl(header_file, table_name, func_array_struct, dim);
  for (cond=FIRST_COND_CODE ; cond <= LAST_COND_CODE ; ++cond) {
    func_name = prefix + COND_CODE_SUFFIX[cond];
    generate_swi_instruction(func_name,cond);
    if (cond < LAST_COND_CODE)
      header_file << ", "; // debug << " /* cond */ " ;
  } // end condition code loop
  closeArrayDecl(header_file);
}

void SWI_Generator::generate_swi_instruction(const string func_name,
                                             const ConditionCode cond)
{
  ostringstream body;

  // print function name
  code_file << "// Semantic function " << endl;
  code_file << PSEUDO_TYPE <<func_name <<  ARGS <<endl;
  // generate function body
  body <<'{' <<endl;
  body <<"  proc.debug() <<\"" <<func_name <<"\" <<std::endl;" <<endl;
  generate_condition_code(body, cond);
  body << "   proc.software_interrupt();" <<endl;
  code_file << body.str() << "  return BRANCH;" << endl << "}" << endl;
  header_file << func_name << " " ;
}

void SWI_Generator::generate()
{
  // one file for all swi instruction
  openFileSet("armpi_swi");
  generate_swi_func_table("arm_swi_table", "arm_swi");
  closeFileSet();
}
