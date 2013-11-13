//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "armgen_clz.hpp"

using namespace std;

void CLZ_Generator::generate_clz_func_table(const string table_name,
                                            const string prefix)

{ string func_name = prefix;
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
    generate_clz_instruction(func_name,cond);
    if (cond < LAST_COND_CODE)
      header_file << ", "; // debug << " /* cond */ " ;
  } // end condition code loop
  closeArrayDecl(header_file);
}

void CLZ_Generator::generate_clz_instruction(const string func_name,
                                             const ConditionCode cond)
{
  ostringstream body  ;

  // print function name
  code_file << "// Semantic function " << endl;
  code_file << PSEUDO_TYPE <<func_name <<  ARGS <<endl;
  // generate function body
  body <<'{' <<endl;
  body <<"  proc.debug() <<\"" <<func_name <<"\" <<endl;" <<endl;
  generate_condition_code(body, cond);
  body << "   const uint32_t m = proc.cpu.regs[p.args.any_reg.Rm]; "<<endl;
  body << "   proc.cpu.regs[p.args.any_reg.Rd] = 32-fls(m);"<<endl;
  code_file << body.str() << "  return OK;" << endl << "}" << endl;
  header_file << func_name << " " ;
}

void CLZ_Generator::generate()
{
  // one file for all move instructions
  openFileSet("armpi_clz");
  generate_clz_func_table("arm_clz_table", "arm_clz");
  closeFileSet();
}
