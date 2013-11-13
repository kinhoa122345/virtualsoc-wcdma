//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "armgen.hpp"

using namespace std;

// utilities functions

void Fatal(const string s) {
  cerr << " Fatal error: " << s << endl;
  exit(1);
}

// define ++ operator on enums

ConditionCode &operator++ (ConditionCode &cc) {
  return (ConditionCode &) ++((int &) cc);
}

// OperandMode & operator++ (OperandMode &m) {
//   return (OperandMode &) ++((int &) m);
// }

/*
 * ARM Generation Base Class
 */

// open and initialize header and code files with includes

void ARM_Generator::openFileSet(const string file_id) {
//   string flfname = file_id + "_func.hpp";
  hfname = file_id + ".hpp";
  string cfname = file_id + ".cpp";

  code_file.open(cfname.data(), ios::trunc );
  header_file.open(hfname.data(), ios::trunc );
//   func_list_file.open(flfname.data(), ios::trunc );

  if (code_file.fail()) {
    Fatal( "Fail opening code file: " + cfname);
  }
  else if (header_file.fail()) {
    Fatal( "Fail opening header file: " + hfname);
  }
//   else if (func_list_file.fail()) {
//     Fatal( "Fail opening functions list file: " + flfname);
//   }
  else {
    cout << "Generating file set for " << file_id << endl;
  }
//   func_list_file << "// Automatically generated. Do not modify" << endl;
//   func_list_file << "#include \"armpi.hpp\"" << endl;

  header_file << "// Automatically generated. Do not modify\n"
              << "namespace simsoc {" << endl;

  code_file << "// Automatically generated. Do not modify\n"
            << "#include \"libsimsoc/processors/arm/armpi.hpp\"\n"
            << "#include \"libsimsoc/processors/arm/arm_processor.hpp\"\n"
            << "#include \"libsimsoc/interfaces/yield.hpp\"\n"
            << "#include \"libsimsoc/display.hpp\"\n"
            << "#include \"libsimsoc/bitwise_operator.hpp\"\n"
            << "#include \"libsimsoc/processors/arm/arm_condition.hpp\"\n"
            << "#include \"libsimsoc/processors/arm/arm_shift.hpp\"\n"
            << "using namespace std;\n"
            << "namespace simsoc {" <<endl;
}


void ARM_Generator::closeFileSet() {
  code_file <<"} // namespace simsoc\n"
            << "#include \"" << hfname << "\"" << endl;
  header_file <<"} // namespace simsoc" <<endl;
  code_file.close();
  header_file.close( );
//   func_list_file.close();
}

/* generate declaration of a new array of functions.
 * length indicates the number of dimensions and each dimension size
 * is in corresponding array_struct
 */
void ARM_Generator::openArrayDecl(ostream &stream, string name,
                                  int array_struct[], const int length)
{
  int i;
  // bracket level is only useful for debugging the generated code...
  bracket_level = length;
  stream << FUNC_ARRAY_TYPE << name ;
  // debug  cout << "create array of dim " << length << " size= " ;
  for (i=0; i<length; i++) {
    stream << "[" << array_struct[i] << "]";
  }
  stream << " = { " << endl ;
}

// generate end of array declaration
void  ARM_Generator::closeArrayDecl(ostream &stream) {
  stream << "};" << endl ;
}

// generate transition from array row to a new row
void ARM_Generator::newArrayRow(ostream &stream) {
  stream << endl << "{ /* " << --bracket_level << " */ ";
  if (bracket_level > 1)
    stream << endl  ;
}

// generate end of array row
void ARM_Generator::closeArrayRow(ostream &stream){
  if (bracket_level > 1 )
    stream << endl;
  stream << " /* " << bracket_level++ << " */ } " ;
}
// Generate code to test actual condition code
#ifdef NCOND
void ARM_Generator::generate_condition_code(ostringstream &body,
                                            nconst ConditionCode cond) {
  switch (cond) {
  case always:
    // no test for always
    break;
  case any:
    body << " if  (conditionPassed(proc.cpu.cpsr, p.any.cond) )  return OK;\n";
    break;
  default: Fatal("error condition code");
  }
}

#else
#ifdef SPCOND
void ARM_Generator::generate_condition_code(ostringstream &body,
                                            const ConditionCode cond) {
  switch (cond) {
  case eq:
    body << "  if (!proc.cpu.cpsr.z) return OK;\n";
    break;
  case ne:
    body << "  if (proc.cpu.cpsr.z) return OK;\n";
    break;
  case cshs:
    body << "  if (!proc.cpu.cpsr.c) return OK;\n";
    break;
  case cclo:
    body << "  if (proc.cpu.cpsr.c) return OK;\n";
    break;
  case mi:
    body << "  if (!proc.cpu.cpsr.n) return OK;\n";
    break;
  case pl:
    body << "  if (proc.cpu.cpsr.n) return OK;\n";
    break;
  case vs:
    body << "  if (!proc.cpu.cpsr.v) return OK;\n";
    break;
  case vc:
    body << "  if (proc.cpu.cpsr.v) return OK;\n";
    break;
  case hi:
    body << "  if (!proc.cpu.cpsr.c || proc.cpu.cpsr.z) return OK;\n";
    break;
  case ls:
    body << "  if (proc.cpu.cpsr.c && !proc.cpu.cpsr.z) return OK;\n";
    break;
  case ge:
    body << "  if (proc.cpu.cpsr.n!=proc.cpu.cpsr.v) return OK;\n";
    break;
  case lt:
    body << "  if (proc.cpu.cpsr.n==proc.cpu.cpsr.v) return OK;\n";
    break;
  case gt:
    body << "  if (proc.cpu.cpsr.z || (proc.cpu.cpsr.n!=proc.cpu.cpsr.v)) return OK;\n";
    break;
  case le:
    body << "  if (!proc.cpu.cpsr.z && (proc.cpu.cpsr.n==proc.cpu.cpsr.v)) return OK;\n";
    break;
  case always:
    // no test for always
    break;
  default: Fatal("error condition code");
  }
}

#else

void ARM_Generator::generate_condition_code(ostringstream &body,
                                            const ConditionCode cond) {
  switch (cond) {
  case always:
    // no test for always
     break;
  case any:

    body << "  if (not_arm_cond[p.args.any.cond][proc.cpu.cpsr.n][proc.cpu.cpsr.z][proc.cpu.cpsr.c][proc.cpu.cpsr.v])  return OK;\n";
//     body << " if  (!conditionPassed(proc.cpu.cpsr, p.args.any.cond) )  return OK;\n";
    break;
  default: Fatal("error condition code");
   }
}

#endif
#endif
