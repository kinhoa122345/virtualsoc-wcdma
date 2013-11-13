//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARMGEN_HPP
#define ARMGEN_HPP

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

// utilities functions
void Fatal(const std::string s);

// arguments of semantic functions
const std::string ARGS = "(ARM_Processor &proc, const ARM_PseudoInstruction &p) ";
const std::string FUNC_TYPE = "ARM_PseudoFunction ";
const std::string FUNC_ARRAY_TYPE = "ARM_PseudoFunction ";
const std::string REGS = "proc.cpu.regs";
const std::string PSEUDO_TYPE = "PseudoStatus ";

// 16 ARM V5 registers
const int REG_FIRST = 0;
const int REG_LAST = 15;
const int ARM_PC = 15;
const int ARM_NUM_REG = 16;
const std::string REGISTER_SUFFIX[16] = {"_r0", "_r1", "_r2", "_r3",
                                    "_r4","_r5", "_r6", "_r7",
                                    "_r8", "_r9","_sl", "_fp",
                                    "_ip", "_sp", "_lr","_pc"};

const std::string FLAGS_SUFFIX[2] = { "_nfl", "_sfl" }; /* no flag, set flag */



// 15 ARM condition code
#ifdef NCOND

typedef enum { always,  // always , unconditional
               any
} ConditionCode;
ConditionCode &operator++ (ConditionCode &cc);

 const ConditionCode FIRST_COND_CODE = always;
const ConditionCode LAST_COND_CODE = any;

const std::string COND_CODE_SUFFIX[2] = { "_Cal","_Cany"};

class ARM_Generator {
public:
  // each subclass must implement a code generation function for its subclass
  // covering all instructions grouped by the subclass
  virtual void generate() = 0;
  virtual ~ARM_Generator() {}

  //  ARM_Generator();
  void openFileSet(const std::string file_id); // create output files
  void closeFileSet(); // close output files
  // generate a table declaration
  void openArrayDecl(std::ostream &stream, std::string name,
                     int array_struct[], const int length);
  void closeArrayDecl(std::ostream &stream); // generate end of table
  void newArrayRow(std::ostream &stream); // append '{' to file
  void closeArrayRow(std::ostream &stream); // append '}' to file
  // generate code testing cond code
  void generate_condition_code(ostringstream &body,
                               const ConditionCode cond);

protected:
  std::string hfname;
  std:: ofstream code_file; // the files for code generation
  std::ofstream header_file;
//   ofstream func_list_file;
  int bracket_level; // level for table initialization
};
#else
#ifdef SPCOND
typedef enum {eq=0, //Z=1
              ne=1, //Z=0
              cshs, // carry set or higher or same C=1
              cclo,  // carry clear or lower  C=0
              mi,  // minus or negative    N=1
              pl, // plus or positive or zero  N=0
              vs, // overflow   V=1
              vc, // no overflow  V=0
              hi,  // unsigned higher C=1 and Z=0
              ls,  // unsigned lower or same  C=0 or Z=1
              ge,  // signed greater than or equal (N=1 and V=1) or (N=0 and V=0)
              lt, // signed less than  (N=1 and V=0) or (N=0 and V=1)
              gt, // signed greater than (Z=0 and N=V)
              le, // signed less or equal(Z=1 or N!=V)
              always  // always , unconditional
} ConditionCode;

ConditionCode &operator++ (ConditionCode &cc);

const ConditionCode FIRST_COND_CODE = eq;
const ConditionCode LAST_COND_CODE = always;

const std::string COND_CODE_SUFFIX[15] = { "_Ceq", "_Cne", "_Ccshs", "_Ccclo",
                                      "_Cmi", "_Cpl", "_Vvs", "_Cvc",
                                      "_Chi", "_Cls", "_Cge", "_Clt",
                                      "_Cgt", "_Cle", "_Cal"};

class ARM_Generator {
public:
  // each subclass must implement a code generation function for its subclass
  // covering all instructions grouped by the subclass
  virtual void generate() = 0;
  virtual ~ARM_Generator() {}

  //  ARM_Generator();
  void openFileSet(const std::string file_id); // create output files
  void closeFileSet(); // close output files
  // generate a table declaration
  void openArrayDecl(std::ostream &stream, std::string name,
                     int array_struct[], const int length);
  void closeArrayDecl(std::ostream &stream); // generate end of table
  void newArrayRow(std::ostream &stream); // append '{' to file
  void closeArrayRow(std::ostream &stream); // append '}' to file
  // generate code testing cond code
void generate_condition_code(std::ostringstream &body,
                             const ConditionCode cond);


protected:
  std::string hfname;
  std:: ofstream code_file; // the files for code generation
  std::ofstream header_file;
//   ofstream func_list_file;
  int bracket_level; // level for table initialization
};
#else
typedef enum { always,  // always , unconditional
               any
} ConditionCode;
ConditionCode &operator++ (ConditionCode &cc);

const ConditionCode FIRST_COND_CODE = always;
const ConditionCode LAST_COND_CODE = any;

const std::string COND_CODE_SUFFIX[2] = { "_Cal","_Cany"};
class ARM_Generator {
public:
  // each subclass must implement a code generation function for its subclass
  // covering all instructions grouped by the subclass
  virtual void generate() = 0;
  virtual ~ARM_Generator() {}

  //  ARM_Generator();
  void openFileSet(const std::string file_id); // create output files
  void closeFileSet(); // close output files
  // generate a table declaration
  void openArrayDecl(std::ostream &stream, std::string name,
                     int array_struct[], const int length);
  void closeArrayDecl(std::ostream &stream); // generate end of table
  void newArrayRow(std::ostream &stream); // append '{' to file
  void closeArrayRow(std::ostream &stream); // append '}' to file
  // generate code testing cond code
  void generate_condition_code(std::ostringstream &body,
                               const ConditionCode cond);

protected:
  std::string hfname;
  std::ofstream code_file; // the files for code generation
  std::ofstream header_file;
//   ofstream func_list_file;
  int bracket_level; // level for table initialization
};

#endif
#endif
// 11 ARM operands mode

// typedef enum {immediate,
//               register_source,
// 	      logical_shift_left_imm,
//               logical_shift_right_imm,
// 	      arithmetic_shift_imm,
//               rotate_shift_imm,
// 	      rotate_shift_extend,
// 	      logical_shift_left_reg,
//               logical_shift_right_reg,
// 	      arithmetic_shift_reg,
//               rotate_shift_reg} OperandMode;

// OperandMode &operator++ (OperandMode &m);

// // values of first and last
// const OperandMode FIRST_OP_MODE = immediate;
// const OperandMode LAST_OP_MODE = rotate_shift_reg;
// const OperandMode LAST_SHIFT_IMM = rotate_shift_extend;

// const std::string OPERAND_SUFFIX[11] = {"_imm", "_reg", "_lsli", "_lsri",
//                                    "_asri", "_rori", "_rrx", "_lslr",
//                                    "_lsrr", "_asrr", "_rorr"};


// Parent Class for ARM V5 code generation of instruction execution
// class to generate the various ARM types of operands


#endif //ARMGEN_HPP

