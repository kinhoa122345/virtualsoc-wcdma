//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "armgen_dpi.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

DPI_Opcode & operator++ (DPI_Opcode &op) {
  return (DPI_Opcode &) ++((int &) op);
}


OperandMode & operator++ (OperandMode &m) {
  return (OperandMode &) ++((int &) m);
}

/*
 * DPI_Generator Class to generate Data Processing Instructions
 */

// generate suffix string for names of functions
string DPI_Generator::generate_operand_suffix(const OperandMode opm,
                                              const bool use_reg_Rn,
                                              const int reg)
{
  if (opm > LAST_OP_MODE) {
    Fatal("illegal operand mcode");
    return "";
  }
  else return (use_reg_Rn)?
         OPERAND_SUFFIX[opm] + REGISTER_SUFFIX[reg]:
         OPERAND_SUFFIX[opm] ;
}

/*
 * Generate code doing the ARM operand shifter operations.
 * The result of shifter operand is stored in variable opv
 * Uses 64 bits intermediate variables to compute rotated shift
 * Will be faster on 64 bits machines...
 * if the S bit is set, it generates a variable shift_c
 * which contains the value of the shifter carry out
 */

void DPI_Generator::generate_operand_code(ostringstream &oss,
                                          const OperandMode op,
                                          const int set_carry)
{
  switch (op) {
  case immediate:
    oss << "  uint32_t opv = p.args.dpi_imm.immed;"  << endl;
    if (set_carry)
      oss << "  uint32_t shift_c = p.args.dpi_imm.set_carry? opv&0x80000000: proc.cpu.cpsr.c;"
          <<endl;
    break;
  case register_source:
    oss << "  uint32_t opv = proc.cpu.regs[p.args.any_reg.Rm];" << endl;
    if (set_carry)
      oss << "  uint32_t shift_c = proc.cpu.cpsr.c;" <<endl;
    break;
  case logical_shift_left_imm:
    oss << "  uint32_t opv = proc.cpu.regs[p.args.any_reg.Rm];" <<endl ;
    oss << "  uint32_t shift = p.args.dpi_shift_imm.imm_s;" << endl;
    if (set_carry) {
      oss << "  uint32_t shift_c = (shift==0)? proc.cpu.cpsr.c:";
      oss <<" (opv>>(32-shift))&0x1;";
    }
    oss << endl << "  opv = opv << shift;" << endl;
    break;
  case logical_shift_left_reg:
    oss << "  uint32_t opv = proc.cpu.regs[p.args.dpi_shift_imm.Rm];" <<endl ;
    oss << "  uint8_t shift = proc.cpu.regs[p.args.dpi_shift_reg.Rs];" << endl;
    if (set_carry) {
      oss << "  uint32_t shift_c=(shift==0)? proc.cpu.cpsr.c:";
      oss << " (shift>32)? 0: opv &(0x1<<(32-shift));" << endl;
    }
    oss << "  opv = valueLSL(opv,shift);" << endl;
    break;
  case logical_shift_right_imm:
    oss << "  uint32_t opv = proc.cpu.regs[p.args.any_reg.Rm];" <<endl ;
    oss << "  uint32_t shift = p.args.dpi_shift_imm.imm_s ;" << endl;
    if (set_carry)
      oss << "  uint32_t shift_c = opv&(1<<(shift-1));"<<endl;
    oss << "  opv = opv >> shift;" << endl;
    break;
  case logical_shift_right_imm_32:
    oss << "  uint32_t opv = 0;" <<endl ;
    if (set_carry)
      oss << "  uint32_t shift_c = proc.cpu.regs[p.args.any_reg.Rm] >>31;"<< endl;
    break;
  case logical_shift_right_reg:
    oss << "  uint32_t opv = proc.cpu.regs[p.args.dpi_shift_imm.Rm];" <<endl ;
    oss << "  uint8_t shift = proc.cpu.regs[p.args.any_reg.Rs];" << endl;
    if (set_carry) {
      oss << "  uint32_t shift_c = (shift==0)? proc.cpu.cpsr.c:";
      oss << " ((shift>32)? 0: opv&(0x1<<(shift-1)));";
    }
    oss << endl << "  opv = valueLSR(opv,shift);" << endl;
    break;
  case arithmetic_shift_imm:
    oss << "  int32_t val = proc.cpu.regs[p.args.dpi_shift_imm.Rm];" <<endl ;
    oss << "  uint32_t shift = p.args.dpi_shift_imm.imm_s ;" << endl;
    if (set_carry) {
      oss << "  uint32_t shift_c =val&(1<<(shift-1));"<< endl;
    }
    oss << "  val = val >> shift;" << endl;
    oss << "  uint32_t opv = (uint32_t) val;" <<endl;
    break;
  case arithmetic_shift_imm_32:
    oss << "  int32_t val = proc.cpu.regs[p.args.dpi_shift_imm.Rm];" <<endl ;
    if (set_carry) {
      oss << "  uint32_t shift_c = val>>31;"<<endl;
    }
    oss << "  val = (val<0)?-1:0;" << endl;
    oss << "  uint32_t opv = (uint32_t) val;" <<endl;
    break;

  case arithmetic_shift_reg:
    oss << "  int32_t val = proc.cpu.regs[p.args.dpi_shift_imm.Rm];" <<endl ;
    oss << "  uint8_t shift = proc.cpu.regs[p.args.dpi_shift_reg.Rs];" << endl;
    if (set_carry) {
      oss << "  uint32_t shift_c=(shift==0)? proc.cpu.cpsr.c:";
      oss << " val & (0x1<<(shift>32)?31:shift-1);";
    }
    oss << "  uint32_t opv = (shift==0)? (uint32_t)val: valueASR(val,shift);" <<endl;
    break;
  case rotate_shift_imm:
    oss << "  uint64_t val = proc.cpu.regs[p.args.dpi_shift_imm.Rm]; " << endl;
    oss << "  uint8_t shift = p.args.dpi_shift_imm.imm_s ;" << endl;
    oss << "  val = ((val<<32) | val) >> shift ;" << endl;
    if (set_carry) {
      oss << "  uint32_t shift_c = val << shift-1;";
    }
    oss << "  uint32_t opv = (uint32_t) val ; " << endl ;
    break;
  case rotate_shift_reg:
    oss << "  uint8_t shift = proc.cpu.regs[p.args.dpi_shift_reg.Rs];\n";
    oss << "  uint32_t val = proc.cpu.regs[p.args.dpi_shift_reg.Rm];\n";
    if (set_carry)
      oss << "  uint32_t shift_c;\n";
    oss << "  uint32_t opv;\n";
    oss << "  if (shift==0) {\n";
    if (set_carry)
      oss << "    shift_c = proc.cpu.cpsr.c;\n";
    oss << "    opv = val;\n";
    oss << "  } else {\n";
    oss << "    shift = shift%32;\n";
    oss << "    if (shift==0) {\n";
    if (set_carry)
      oss << "      shift_c = val&(1<<31);\n";
    oss << "      opv = val;\n";
    oss << "    } else {\n";
    if (set_carry)
      oss << "      shift_c = val&(1<<(shift-1));\n";
    oss << "      opv = rotateRight(val,shift);\n";
    oss << "    }\n";
    oss << "  }\n";
    break;
  case rotate_shift_extend:
    oss << "  uint32_t opv = (proc.cpu.regs[p.args.any_reg.Rm]>>1)|(proc.cpu.cpsr.c? 0x80000000: 0);"
        << endl;
    if (set_carry) {
       oss << "  uint32_t shift_c = (uint32_t)0x1&p.args.any_reg.Rm;" <<endl;

    }

    break;
  default: Fatal("illegal data processing operand" );
  }
}

#ifdef SPRD

/*
 * Generate code for one semantic function
 * Print to files the generated  strings
 */
void DPI_Generator::generate_instruction(const string prefix,
                                         const ConditionCode cond,
                                         const int s_bit,
                                         const DPI_Opcode opcode,
                                         const OperandMode opm,

                                         const int reg_d
                                         // const bool specialize_Rn_reg,
//                                          const int reg_n
                                         )
{
  ostringstream body  ;
  string func_name = prefix;
  string opm_suffix =  OPERAND_SUFFIX[opm];

 //  if (specialize_Rn_reg) opm_suffix.append(REGISTER_SUFFIX[reg_n]);
  // print function name
  code_file << "// Semantic function " << endl;
  code_file << PSEUDO_TYPE << func_name.append(opm_suffix) << ARGS <<endl;
  // generate function body
  body <<'{' <<endl;
  body <<"  proc.debug() <<\"" <<func_name <<"\" <<std::endl;" <<endl;
  switch (opm) {
  case immediate:
    generate_condition_code(body, cond, "p.args.dpi_imm.cond");
    break;
  case register_source:
  case logical_shift_right_imm_32:
  case arithmetic_shift_imm_32:
  case logical_shift_left_imm:
  case logical_shift_right_imm:
  case arithmetic_shift_imm:
  case rotate_shift_imm:
    generate_condition_code(body, cond, "p.args.dpi_shift_imm.cond");
    break;
  case rotate_shift_extend:
  case logical_shift_left_reg:
  case logical_shift_right_reg:
  case arithmetic_shift_reg:
  case rotate_shift_reg:
    generate_condition_code(body, cond, "p.args.dpi_shift_reg.cond");
    break;
  }
  // invoke the operation method for this operator
  generate_operation(body, s_bit, opcode, opm,
                    reg_d
                    );
  if (reg_d==15)
    code_file << body.str() << "  return BRANCH;" << endl << "}" << endl;
  else
    code_file << body.str() << "  return OK;" << endl << "}" << endl;

  // print function name to include file for declaration
  //   func_list_file << FUNC_TYPE << func_name << " ;" << endl;
  // print function name to table file for static array  initialization
 header_file << func_name << " " ;

}

/*
 * the generic function to generate an array of functions and their code
 * for all DPI with possibly shifted operand
 */

void DPI_Generator::generate_func_table(const string table_name,
                                        const string prefix,
                                        const DPI_Opcode opcode_from,
                                        const DPI_Opcode opcode_to,
                                        const OperandMode opm_from,
                                        const OperandMode opm_to
                                        )
{
  string func_name = prefix;
  ConditionCode cond;
  OperandMode opm;
  int dim;
  int *func_array_struct;
//   int level; // indentation level inside array

  // Compute number of dimensions for the array of functions, maximum is 8
  func_array_struct = new int [8];
  func_array_struct[0] = LAST_COND_CODE + 1; // N conditions codes
  func_array_struct[1] = 2 ; // bit S is 0 or 1
  func_array_struct[2] = opcode_to - opcode_from + 1 ; // N operation types
  func_array_struct[3] = opm_to - opm_from + 1 ; // M operand types
  // if specialize Rd then 16 functions, otherwise two for r15 and others
//   func_array_struct[4] = ((specialize_Rd_reg) ? ARM_NUM_REG : 2);
//   dim = 5;
  func_array_struct[4] = ARM_NUM_REG ;
  dim = 5;

 //  if (specialize_Rn_reg){
//     dim += 1;
//     func_array_struct[dim] = ARM_NUM_REG;
//   }
  // create table declaration in header file
  openArrayDecl(header_file, table_name, func_array_struct, dim);
  // now loop on all specialized functions
  // print ',' after each element of an array
  // but do not print ',' after last element of an array
  for (cond=FIRST_COND_CODE ; cond <= LAST_COND_CODE ; ++cond) {
    DPI_Opcode opcode;
    int s_bit;
    newArrayRow(header_file); // generate curly bracket
    for (s_bit=0; s_bit <= 1; ++s_bit) {
      newArrayRow(header_file);
      for (opcode=opcode_from; opcode <= opcode_to; ++opcode) {
        newArrayRow(header_file);
        for (opm= opm_from; opm <= opm_to ; ++opm) {
          newArrayRow(header_file);
          for (int reg_d= 0; reg_d <= ARM_NUM_REG-1 ; ++reg_d) {
            func_name = prefix + COND_CODE_SUFFIX[cond]
              + FLAGS_SUFFIX[s_bit] + OPCODE_SUFFIX[opcode] + REGISTER_SUFFIX[reg_d];
            //   specialize_register(func_name, cond, s_bit, opcode, opm,
            // 			      specialize_Rd_reg, specialize_Rn_reg);
            generate_instruction(func_name, cond, s_bit, opcode, opm,
                                 reg_d);
            if (reg_d < ARM_NUM_REG)
              header_file << ", " ; // debug << "/* Rd */" ;
          } //end Rd loop
          closeArrayRow(header_file);
          if (opm < opm_to)
            header_file << ", " ; // debug << "/* mode */" ;
        } //end operand loop
        closeArrayRow(header_file);
        if (opcode < opcode_to)
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
 * ARM operations take first operand in Rn and the second operand
 * is possibly shifted with all combinations
 * The two operands are stored in variables tmp and opv
 * tmp contains register Rn and opv the result of shifter operand
 * The operation result is stored in variable r
 * then r is stored in destination register Rd
 * except for operations TST and TEQ that do not modiy Rd
 * r, tmp and opv are needed for computing the C,V,Z,N flags
 * Hopefully the C++ compiler will optimize.
 * Separate boolean operations from integer operations
 */

void DPI_Generator::generate_operation(ostringstream &body,
                                       const int s_bit,
                                       const DPI_Opcode opcode,
                                       const OperandMode opm,
                                       const int reg_d
                                      //  const bool specialize_Rn_reg,
//                                        const int reg_n
                                       )
{
  if (FIRST_BOOL<=opcode && opcode<=LAST_BOOL) {
    if ((opcode == TST || opcode == TEQ) & (s_bit == 0))
      return ;
    // for TST and TEQ instruction the S bit must be set
    // we generate empty function for this impossible case...
    // generate code for operand.
    generate_operand_code(body, opm,
                          s_bit == 1
                          && ((reg_d != ARM_PC)
                              || (reg_d == ARM_PC &&
                                  (opcode == TEQ || opcode == TST)
                                  )
                              ));
    //   if (specialize_Rn_reg)
    //       body << "  uint32_t tmp = proc.cpu.regs[" << reg_n << "] ";
    //     else
    body << "  uint32_t tmp = proc.cpu.regs[p.args.any_reg.Rn] ";
    switch (opcode) {

    case AND:
    case TST:
      body << " & opv;" << endl;
      break;

    case EOR:
    case TEQ:
      body << " ^ opv;" << endl;
      break;

    case ORR:
      body << " | opv;" << endl;
      break;

    case BIC:
      body << " &~ opv;" << endl;
      break;
    default:
      Fatal(string("internal error in file ")+__FILE__);
    }
    if (opcode != TST && opcode != TEQ) {
      if (reg_d == ARM_PC)
        body << "  proc.cpu.regs[15] = tmp+8;" << endl;
      else
        body << "  proc.cpu.regs["<<reg_d<<"] = tmp;" << endl;
    }
    if (s_bit) {
      if ((reg_d == ARM_PC)
          && (opcode == AND || opcode == ORR || opcode == EOR || opcode == BIC))
        body << "  proc.spsr_to_cpsr();" << endl;
      else {
        body << "  proc.cpu.cpsr.n = tmp&0x80000000;" << endl;
        body << "  proc.cpu.cpsr.z = !tmp;"  <<endl;
        body << "  proc.cpu.cpsr.c = shift_c;" << endl;
      }
    }

  } else if (FIRST_DATA<=opcode && opcode<=LAST_DATA) { // integer instructions
    if ((opcode == CMP || opcode == CMN) & (s_bit == 0))
      return ;
    // for CMP and CMN instruction the S bit must be set
    // we generate empty function for this impossible case...
    // generate code for operand.
  //   if (specialize_Rn_reg)
//       body << "  uint32_t tmp = proc.cpu.regs[" << reg_n << "];" << endl;
//     else
      body << "  uint32_t tmp = proc.cpu.regs[p.args.any_reg.Rn];" << endl;
    generate_operand_code(body, opm, 0);
    switch (opcode) {
    case ADD:
      body << "  uint32_t r = tmp + opv";
      body << ((reg_d == ARM_PC) ? "+ 8;" : ";") << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  proc.cpu.cpsr.c = r<tmp;" << endl;
          body << "  proc.cpu.cpsr.v = ((tmp^~opv)&(tmp^r))>>31;" << endl;
        }
      }
      break;
    case ADC:
      body << "  const uint32_t r = tmp + opv + proc.cpu.cpsr.c;" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  const uint32_t c = proc.cpu.cpsr.c;" << endl;
          body << "  proc.cpu.cpsr.c = r<tmp+c || tmp+c<c;" << endl;
          body << "  proc.cpu.cpsr.v = ((tmp^~opv)&(tmp^r))>>31;" << endl;
        }
      }
      break;
    case SUB:
      body << "  uint32_t r = tmp - opv ;" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  proc.cpu.cpsr.c = tmp>=opv;" << endl;
          body << "  proc.cpu.cpsr.v = ((tmp^opv)&(tmp^r))>>31;" << endl;
        }
      }
      break;
    case SBC:
      body << "  const uint32_t r = tmp - opv - (! proc.cpu.cpsr.c);" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  proc.cpu.cpsr.c = tmp>=opv && tmp-opv>=(proc.cpu.cpsr.c?0:1);\n";
          body << "  proc.cpu.cpsr.v = ((tmp^opv)&(tmp^r))>>31;" << endl;
        }
      }
      break;
    case RSB:
      body << "  uint32_t r = opv - tmp;" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  proc.cpu.cpsr.c = opv>=tmp;" << endl;
          body << "  proc.cpu.cpsr.v = ((opv^tmp)&(opv^r))>>31;" << endl;
        }
      }
      break;
    case RSC:
      body << "  uint32_t r = opv - tmp - !proc.cpu.cpsr.c;" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  proc.cpu.cpsr.c = opv>=tmp && opv-tmp>=(proc.cpu.cpsr.c?0:1);\n";
          body << "  proc.cpu.cpsr.v = ((opv^tmp)&(opv^r))>>31;" << endl;
        }
      }
      break;
    case CMP:
      body << "  uint32_t r = tmp - opv ;" << endl;
      //if ((tmp - opv)==0)
      // body << "  proc.cpu.cpsr.z = 1;" << endl;
      // else
      // body << "  proc.cpu.cpsr.z = 0;" << endl;
      // body << "  proc.cpu.cpsr.n = r&0x80000000;" << endl;
      body << "  proc.cpu.cpsr.c = tmp>=opv;" << endl;
      body << "  proc.cpu.cpsr.v = ((tmp^opv)&(tmp^r))>>31;" << endl;
      break;
    case CMN:
      body << "  uint32_t r = tmp + opv ;" << endl;
      body << "  proc.cpu.cpsr.c = r<tmp;" << endl;
      body << "  proc.cpu.cpsr.v = ((tmp^~opv)&(tmp^r))>>31;" << endl;
      break;
    default:
      Fatal("illegal DPI operation");
    }
    if (s_bit && reg_d != ARM_PC) {
      body << "  proc.cpu.cpsr.z = !r;" << endl;
      body << "  proc.cpu.cpsr.n = r&0x80000000;"  <<endl;
    }
    if (opcode!=CMP && opcode!=CMN)
      if (reg_d == ARM_PC )
        body << "  proc.cpu.regs[15] = r+8;"<<endl;
      else
        body << "  proc.cpu.regs[" << reg_d << "] = r;"<<endl;


  }
 else { // move instructions
    generate_operand_code(body, opm, (s_bit==1 && reg_d!=ARM_PC));
    switch (opcode) {
    case MOV:
      body <<  "  uint32_t r = opv; " << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else
          body << "  proc.cpu.cpsr.c = shift_c;" << endl;
      }
      break;
    case MVN:
      body <<  "  uint32_t r = ~opv;" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else
          body << "  proc.cpu.cpsr.c = shift_c;" << endl;
      }
      break;
    default:
      Fatal(string("internal error in file ")+__FILE__);
    }
    if (s_bit && reg_d != ARM_PC) {
      body << "  proc.cpu.cpsr.z = !r;" << endl;
      body << "  proc.cpu.cpsr.n = r&0x80000000;"  <<endl;
    }
    if (reg_d == ARM_PC)
      body << "  proc.cpu.regs[15] = r+8;" <<endl;
    else
      body << "  proc.cpu.regs[" << reg_d << "] = r;" <<endl;
  }
}

void DPI_Generator::generate()
{
  // one file for all move instructions
  openFileSet("armpi_dpi_mov");
  generate_func_table("arm_dpi_move_table", "arm",
                      FIRST_MOVE, LAST_MOVE,
                      FIRST_OP_MODE, LAST_OP_MODE);
  closeFileSet();
  // one file for all boolean operation instructions
  openFileSet("armpi_dpi_bool");
  generate_func_table("arm_dpi_bool_table", "arm_dpi",
                      FIRST_BOOL, LAST_BOOL,
                      FIRST_OP_MODE, LAST_OP_MODE);
  closeFileSet();
  openFileSet("armpi_dpi_int");
  // one file for all boolean operation instructions
  generate_func_table("arm_dpi_int_table", "arm_dpi",
                      FIRST_DATA, LAST_DATA,
                      FIRST_OP_MODE, LAST_OP_MODE);
  closeFileSet();
}

#else
#ifdef NCOND


/*
 * Generate code for one semantic function
 * Print to files the generated  strings
 */
void DPI_Generator::generate_instruction(const string prefix,
                                         const ConditionCode cond,
                                         const int s_bit,
                                         const DPI_Opcode opcode,
                                         const OperandMode opm,

                                         const int reg_d
                                         // const bool specialize_Rn_reg,
//                                          const int reg_n
                                         )
{
  ostringstream body  ;
  string func_name = prefix;
  string opm_suffix =  OPERAND_SUFFIX[opm];

 //  if (specialize_Rn_reg) opm_suffix.append(REGISTER_SUFFIX[reg_n]);
  // print function name
  code_file << "// Semantic function " << endl;
  code_file << PSEUDO_TYPE << func_name.append(opm_suffix) << ARGS <<endl;
  // generate function body
  body <<'{' <<endl;
  body <<"  proc.debug() <<\"" <<func_name <<"\" <<std::endl;" <<endl;
  generate_condition_code(body, cond, "p.args.dpi_imm.cond");
  // invoke the operation method for this operator
  generate_operation(body, s_bit, opcode, opm,
                    reg_d
                    );
  if (reg_d==15)
    code_file << body.str() << "  return BRANCH;" << endl << "}" << endl;
  else
    code_file << body.str() << "  return OK;" << endl << "}" << endl;

  // print function name to include file for declaration
  //   func_list_file << FUNC_TYPE << func_name << " ;" << endl;
  // print function name to table file for static array  initialization
 header_file << func_name << " " ;

}

/*
 * the generic function to generate an array of functions and their code
 * for all DPI with possibly shifted operand
 */

void DPI_Generator::generate_func_table(const string table_name,
                                        const string prefix,
                                        const DPI_Opcode opcode_from,
                                        const DPI_Opcode opcode_to,
                                        const OperandMode opm_from,
                                        const OperandMode opm_to
                                        )
{
  string func_name = prefix;
  ConditionCode cond;
  OperandMode opm;
  int dim;
  int *func_array_struct;
//   int level; // indentation level inside array

  // Compute number of dimensions for the array of functions, maximum is 8
  func_array_struct = new int [8];
  func_array_struct[0] = LAST_COND_CODE + 1; // N conditions codes
  func_array_struct[1] = 2 ; // bit S is 0 or 1
  func_array_struct[2] = opcode_to - opcode_from + 1 ; // N operation types
  func_array_struct[3] = opm_to - opm_from + 1 ; // M operand types
  // if specialize Rd then 16 functions, otherwise two for r15 and others
//   func_array_struct[4] = ((specialize_Rd_reg) ? ARM_NUM_REG : 2);
//   dim = 5;
  func_array_struct[4] = ARM_NUM_REG ;
  dim = 5;

 //  if (specialize_Rn_reg){
//     dim += 1;
//     func_array_struct[dim] = ARM_NUM_REG;
//   }
  // create table declaration in header file
  openArrayDecl(header_file, table_name, func_array_struct, dim);
  // now loop on all specialized functions
  // print ',' after each element of an array
  // but do not print ',' after last element of an array
  for (cond=FIRST_COND_CODE ; cond <= LAST_COND_CODE ; ++cond) {
    DPI_Opcode opcode;
    int s_bit;
    newArrayRow(header_file); // generate curly bracket
    for (s_bit=0; s_bit <= 1; ++s_bit) {
      newArrayRow(header_file);
      for (opcode=opcode_from; opcode <= opcode_to; ++opcode) {
        newArrayRow(header_file);
        for (opm= opm_from; opm <= opm_to ; ++opm) {
          newArrayRow(header_file);
          for (int reg_d= 0; reg_d <= ARM_NUM_REG-1 ; ++reg_d) {
            func_name = prefix + COND_CODE_SUFFIX[cond]
              + FLAGS_SUFFIX[s_bit] + OPCODE_SUFFIX[opcode] + REGISTER_SUFFIX[reg_d];
            //   specialize_register(func_name, cond, s_bit, opcode, opm,
            // 			      specialize_Rd_reg, specialize_Rn_reg);
            generate_instruction(func_name, cond, s_bit, opcode, opm,
                                 reg_d);
            if (reg_d < ARM_NUM_REG)
              header_file << ", " ; // debug << "/* Rd */" ;
          } //end Rd loop
          closeArrayRow(header_file);
          if (opm < opm_to)
            header_file << ", " ; // debug << "/* mode */" ;
        } //end operand loop
        closeArrayRow(header_file);
        if (opcode < opcode_to)
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
 * ARM operations take first operand in Rn and the second operand
 * is possibly shifted with all combinations
 * The two operands are stored in variables tmp and opv
 * tmp contains register Rn and opv the result of shifter operand
 * The operation result is stored in variable r
 * then r is stored in destination register Rd
 * except for operations TST and TEQ that do not modiy Rd
 * r, tmp and opv are needed for computing the C,V,Z,N flags
 * Hopefully the C++ compiler will optimize.
 * Separate boolean operations from integer operations
 */

void DPI_Generator::generate_operation(ostringstream &body,
                                       const int s_bit,
                                       const DPI_Opcode opcode,
                                       const OperandMode opm,
                                       const int reg_d
                                      //  const bool specialize_Rn_reg,
//                                        const int reg_n
                                       )
{
  if (FIRST_BOOL<=opcode && opcode<=LAST_BOOL) {
    if ((opcode == TST || opcode == TEQ) & (s_bit == 0))
      return ;
    // for TST and TEQ instruction the S bit must be set
    // we generate empty function for this impossible case...
    // generate code for operand.
    generate_operand_code(body, opm,
                          s_bit == 1
                          && ((reg_d != ARM_PC)
                              || (reg_d == ARM_PC &&
                                  (opcode == TEQ || opcode == TST)
                                  )
                              ));
  //   if (specialize_Rn_reg)
//       body << "  uint32_t tmp = proc.cpu.regs[" << reg_n << "] ";
//     else
      body << "  uint32_t tmp = proc.cpu.regs[p.args.any_reg.Rn] ";
    switch (opcode) {

    case AND:
    case TST:
      body << " & opv;" << endl;
      break;

    case EOR:
    case TEQ:
      body << " ^ opv;" << endl;
      break;

    case ORR:
      body << " | opv;" << endl;
      break;

    case BIC:
      body << " &~ opv;" << endl;
      break;
    default:
      Fatal(string("internal error in file ")+__FILE__);
    }
    if (opcode != TST && opcode != TEQ) {
      if (reg_d == ARM_PC)
        body << "  proc.cpu.regs[15] = tmp+8;" << endl;
      else
        body << "  proc.cpu.regs["<<reg_d<<"] = tmp;" << endl;
    }
    if (s_bit) {
      if ((reg_d == ARM_PC)
          && (opcode == AND || opcode == ORR || opcode == EOR || opcode == BIC))
        body << "  proc.spsr_to_cpsr();" << endl;
      else {
        body << "  proc.cpu.cpsr.n = tmp&0x80000000;" << endl;
        body << "  proc.cpu.cpsr.z = !tmp;"  <<endl;
        body << "  proc.cpu.cpsr.c = shift_c;" << endl;
      }
    }

  } else if (FIRST_DATA<=opcode && opcode<=LAST_DATA) { // integer instructions
    if ((opcode == CMP || opcode == CMN) & (s_bit == 0))
      return ;
    // for CMP and CMN instruction the S bit must be set
    // we generate empty function for this impossible case...
    // generate code for operand.
  //   if (specialize_Rn_reg)
//       body << "  uint32_t tmp = proc.cpu.regs[" << reg_n << "];" << endl;
//     else
      body << "  uint32_t tmp = proc.cpu.regs[p.args.any_reg.Rn];" << endl;
    generate_operand_code(body, opm, 0);
    switch (opcode) {
    case ADD:
      body << "  uint32_t r = tmp + opv";
      body << ((reg_d == ARM_PC) ? "+ 8;" : ";") << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  proc.cpu.cpsr.c = r<tmp;" << endl;
          body << "  proc.cpu.cpsr.v = ((tmp^~opv)&(tmp^r))>>31;" << endl;
        }
      }
      break;
    case ADC:
      body << "  uint32_t r = tmp + opv + proc.cpu.cpsr.c;" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  const uint32_t c = proc.cpu.cpsr.c;" << endl;
          body << "  proc.cpu.cpsr.c = r<tmp+c || tmp+c<c;" << endl;
          body << "  proc.cpu.cpsr.v = ((tmp^~opv)&(tmp^r))>>31;" << endl;
        }
      }
      break;
    case SUB:
      body << "  uint32_t r = tmp - opv ;" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  proc.cpu.cpsr.c = tmp>=opv;" << endl;
          body << "  proc.cpu.cpsr.v = ((tmp^opv)&(tmp^r))>>31;" << endl;
        }
      }
      break;
    case SBC:
      body << "  uint32_t r = tmp - opv - (! proc.cpu.cpsr.c);" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  proc.cpu.cpsr.c = tmp>=opv && tmp-opv>=(proc.cpu.cpsr.c?0:1);\n";
          body << "  proc.cpu.cpsr.v = ((tmp^opv)&(tmp^r))>>31;" << endl;
        }
      }
      break;
    case RSB:
      body << "  uint32_t r = opv - tmp;" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  proc.cpu.cpsr.c = opv>=tmp;" << endl;
          body << "  proc.cpu.cpsr.v = ((opv^tmp)&(opv^r))>>31;" << endl;
        }
      }
      break;
    case RSC:
      body << "  uint32_t r = opv - tmp - !proc.cpu.cpsr.c;" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  proc.cpu.cpsr.c = opv>=tmp && opv-tmp>=(proc.cpu.cpsr.c?0:1);\n";
          body << "  proc.cpu.cpsr.v = ((opv^tmp)&(opv^r))>>31;" << endl;
        }
      }
      break;
    case CMP:
      body << "  uint32_t r = tmp - opv ;" << endl;
      //if ((tmp - opv)==0)
      // body << "  proc.cpu.cpsr.z = 1;" << endl;
      // else
      // body << "  proc.cpu.cpsr.z = 0;" << endl;
      // body << "  proc.cpu.cpsr.n = r&0x80000000;" << endl;
      body << "  proc.cpu.cpsr.c = tmp>=opv;" << endl;
      body << "  proc.cpu.cpsr.v = ((tmp^opv)&(tmp^r))>>31;" << endl;
      break;
    case CMN:
      body << "  uint32_t r = tmp + opv ;" << endl;
      body << "  proc.cpu.cpsr.c = r<tmp;" << endl;
      body << "  proc.cpu.cpsr.v = ((tmp^~opv)&(tmp^r))>>31;" << endl;
      break;
    default:
      Fatal("illegal DPI operation");
    }
    if (s_bit && reg_d != ARM_PC) {
      body << "  proc.cpu.cpsr.z = !r;" << endl;
      body << "  proc.cpu.cpsr.n = r&0x80000000;"  <<endl;
    }
    if (opcode!=CMP && opcode!=CMN)
      if (reg_d == ARM_PC )
        body << "  proc.cpu.regs[15] = r+8;"<<endl;
      else
        body << "  proc.cpu.regs[" << reg_d << "] = r;"<<endl;


  }
 else { // move instructions
    generate_operand_code(body, opm, (s_bit==1 && reg_d!=ARM_PC));
    switch (opcode) {
    case MOV:
      body <<  "  uint32_t r = opv; " << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else
          body << "  proc.cpu.cpsr.c = shift_c;" << endl;
      }
      break;
    case MVN:
      body <<  "  uint32_t r = ~opv;" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else
          body << "  proc.cpu.cpsr.c = shift_c;" << endl;
      }
      break;
    default:
      Fatal(string("internal error in file ")+__FILE__);
    }
    if (s_bit && reg_d != ARM_PC) {
      body << "  proc.cpu.cpsr.z = !r;" << endl;
      body << "  proc.cpu.cpsr.n = r&0x80000000;"  <<endl;
    }
    if (reg_d == ARM_PC)
      body << "  proc.cpu.regs[15] = r+8;" <<endl;
    else
      body << "  proc.cpu.regs[" << reg_d << "] = r;" <<endl;
  }
}

void DPI_Generator::generate()
{
  // one file for all move instructions
  openFileSet("armpi_dpi_mov");
  generate_func_table("arm_dpi_move_table", "arm",
                      FIRST_MOVE, LAST_MOVE,
                      FIRST_OP_MODE, LAST_OP_MODE);
  closeFileSet();
  // one file for all boolean operation instructions
  openFileSet("armpi_dpi_bool");
  generate_func_table("arm_dpi_bool_table", "arm_dpi",
                      FIRST_BOOL, LAST_BOOL,
                      FIRST_OP_MODE, LAST_OP_MODE);
  closeFileSet();
  openFileSet("armpi_dpi_int");
  // one file for all boolean operation instructions
  generate_func_table("arm_dpi_int_table", "arm_dpi",
                      FIRST_DATA, LAST_DATA,
                      FIRST_OP_MODE, LAST_OP_MODE);
  closeFileSet();
}
#else
#ifdef SPCOND
/*
 * Generate code in the case the destination and/or source registers
 * are specialized.
 * Generate immediate constant values instead of memory access
 * TRICK: if specialize_Rd is true we generate 15 functions
 * but if specialize_Rd is false, we still generate only two functions
 * one to handle the general case and one for special case of pc=r15
 */

void DPI_Generator::specialize_register(const string prefix,
                                        const ConditionCode cond,
                                        const int s_bit,
                                        const DPI_Opcode opcode,
                                        const OperandMode opm,
                                        const bool specialize_Rd_reg,
                                        const bool specialize_Rn_reg)
{
  string func_name = prefix;
  int reg_d, reg_n;
  int reg_start;

  if (specialize_Rd_reg)
    reg_start = 0;
  else
    reg_start = 14;
  newArrayRow(header_file);
  for (reg_d= reg_start; reg_d < ARM_NUM_REG ; ++reg_d) {
    if (!(reg_d==14 && !(specialize_Rd_reg)))
      func_name.append(REGISTER_SUFFIX[reg_d]);
//     else
//       func_name.append("_reg");
    if (specialize_Rn_reg) {
      newArrayRow(header_file);
      for (reg_n= 0; reg_n < ARM_NUM_REG ; ++reg_n) {
        func_name.append( REGISTER_SUFFIX[reg_n]);
        generate_instruction(func_name, cond, s_bit, opcode, opm,
                             specialize_Rd_reg, reg_d, true, reg_n);
        if (reg_n < ARM_NUM_REG-1)
          header_file << ", /* Rn */ " ;
      }
      closeArrayRow(header_file);
    }
    else {
      generate_instruction(func_name, cond, s_bit, opcode, opm,
                           false, reg_d, false, 0);
    }
    if (reg_d < ARM_NUM_REG-1)
      header_file << ", /* Rd */ " ;
  }; // end loop on register Rd
  closeArrayRow(header_file);
}

/*
 * Generate code for one semantic function
 * Print to files the generated  strings
 */
void DPI_Generator::generate_instruction(const string prefix,
                                         const ConditionCode cond,
                                         const int s_bit,
                                         const DPI_Opcode opcode,
                                         const OperandMode opm,
                                         const bool specialize_Rd_reg,
                                         const int reg_d,
                                         const bool specialize_Rn_reg,
                                         const int reg_n)
{
  ostringstream body  ;
  string func_name = prefix;
  string opm_suffix =  OPERAND_SUFFIX[opm];

  if (specialize_Rn_reg) opm_suffix.append(REGISTER_SUFFIX[reg_n]);
  // print function name
  code_file << "// Semantic function " << endl;
  code_file << PSEUDO_TYPE << func_name.append(opm_suffix) << ARGS <<endl;
  // generate function body
  body <<'{' <<endl;
  body <<"  proc.debug() <<\"" <<func_name <<"\" <<std::endl;" <<endl;
  generate_condition_code(body, cond);
  // invoke the operation method for this operator
  generate_operation(body, s_bit, opcode, opm,
                     specialize_Rd_reg, reg_d,
                     specialize_Rn_reg, reg_n);
  if (reg_d==15)
    code_file << body.str() << "  return BRANCH;" << endl << "}" << endl;
  else
    code_file << body.str() << "  return OK;" << endl << "}" << endl;

  // print function name to include file for declaration
  //   func_list_file << FUNC_TYPE << func_name << " ;" << endl;
  // print function name to table file for static array  initialization
 header_file << func_name << " " ;

}

/*
 * the generic function to generate an array of functions and their code
 * for all DPI with possibly shifted operand
 */

void DPI_Generator::generate_func_table(const string table_name,
                                        const string prefix,
                                        const DPI_Opcode opcode_from,
                                        const DPI_Opcode opcode_to,
                                        const OperandMode opm_from,
                                        const OperandMode opm_to,
                                        bool specialize_Rd_reg,
                                        bool specialize_Rn_reg)
{
  string func_name = prefix;
  ConditionCode cond;
  OperandMode opm;
  int dim;
  int *func_array_struct;
//   int level; // indentation level inside array

  // Compute number of dimensions for the array of functions, maximum is 8
  func_array_struct = new int [8];
  func_array_struct[0] = LAST_COND_CODE + 1; // N conditions codes
  func_array_struct[1] = 2 ; // bit S is 0 or 1
  func_array_struct[2] = opcode_to - opcode_from + 1 ; // N operation types
  func_array_struct[3] = opm_to - opm_from + 1 ; // M operand types
  // if specialize Rd then 16 functions, otherwise two for r15 and others
  func_array_struct[4] = ((specialize_Rd_reg) ? ARM_NUM_REG : 2);
  dim = 5;
  if (specialize_Rn_reg){
    dim += 1;
    func_array_struct[dim] = ARM_NUM_REG;
  }
  // create table declaration in header file
  openArrayDecl(header_file, table_name, func_array_struct, dim);
  // now loop on all specialized functions
  // print ',' after each element of an array
  // but do not print ',' after last element of an array
  for (cond=FIRST_COND_CODE ; cond <= LAST_COND_CODE ; ++cond) {
    DPI_Opcode opcode;
    int s_bit;
    newArrayRow(header_file); // generate curly bracket
    for (s_bit=0; s_bit <= 1; ++s_bit) {
      newArrayRow(header_file);
      for (opcode=opcode_from; opcode <= opcode_to; ++opcode) {
        newArrayRow(header_file);
        for (opm= opm_from; opm <= opm_to ; ++opm) {
          func_name = prefix + COND_CODE_SUFFIX[cond]
            + FLAGS_SUFFIX[s_bit] + OPCODE_SUFFIX[opcode];
          specialize_register(func_name, cond, s_bit, opcode, opm,
                              specialize_Rd_reg, specialize_Rn_reg);
          if (opm < opm_to)
            header_file << ", " ; // debug << "/* mode */" ;
        } //end operand loop
        closeArrayRow(header_file);
        if (opcode < opcode_to)
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
 * ARM operations take first operand in Rn and the second operand
 * is possibly shifted with all combinations
 * The two operands are stored in variables tmp and opv
 * tmp contains register Rn and opv the result of shifter operand
 * The operation result is stored in variable r
 * then r is stored in destination register Rd
 * except for operations TST and TEQ that do not modiy Rd
 * r, tmp and opv are needed for computing the C,V,Z,N flags
 * Hopefully the C++ compiler will optimize.
 * Separate boolean operations from integer operations
 */

void DPI_Generator::generate_operation(ostringstream &body,
                                       const int s_bit,
                                       const DPI_Opcode opcode,
                                       const OperandMode opm,
                                       const bool specialize_Rd_reg,
                                       const int reg_d,
                                       const bool specialize_Rn_reg,
                                       const int reg_n)
{
  if (FIRST_BOOL<=opcode && opcode<=LAST_BOOL) {
    if ((opcode == TST || opcode == TEQ) & (s_bit == 0))
      return ;
    // for TST and TEQ instruction the S bit must be set
    // we generate empty function for this impossible case...
    // generate code for operand.
    generate_operand_code(body, opm,
                          s_bit == 1
                          && ((reg_d != ARM_PC)
                              || (reg_d == ARM_PC &&
                                  (opcode == TEQ || opcode == TST)
                                  )
                              ));
    if (specialize_Rn_reg)
      body << "  uint32_t tmp = proc.cpu.regs[" << reg_n << "] ";
    else
      body << "  uint32_t tmp = proc.cpu.regs[p.args.any_reg.Rn] ";
    switch (opcode) {

    case AND:
    case TST:
      body << " & opv;" << endl;
      break;

    case EOR:
    case TEQ:
      body << " ^ opv;" << endl;
      break;

    case ORR:
      body << " | opv;" << endl;
      break;

    case BIC:
      body << " &~ opv;" << endl;
      break;
    default:
      Fatal(string("internal error in file ")+__FILE__);
    }
    if (opcode != TST && opcode != TEQ) {
      if (reg_d == ARM_PC)
        body << "  proc.cpu.regs[15] = tmp+8;" << endl;
      else if (specialize_Rd_reg)
        body << "  proc.cpu.regs["<<reg_d<<"] = tmp;" << endl;
      else
        body << "  proc.cpu.regs[p.args.any_reg.Rd] = tmp;" << endl;
    }
    if (s_bit) {
      if ((reg_d == ARM_PC)
          && (opcode == AND || opcode == ORR || opcode == EOR || opcode == BIC))
        body << "  proc.spsr_to_cpsr();" << endl;
      else {
        body << "  proc.cpu.cpsr.n = tmp&0x80000000;" << endl;
        body << "  proc.cpu.cpsr.z = !tmp;"  <<endl;
        body << "  proc.cpu.cpsr.c = shift_c;" << endl;
      }
    }

  } else if (FIRST_DATA<=opcode && opcode<=LAST_DATA) { // integer instructions
    if ((opcode == CMP || opcode == CMN) & (s_bit == 0))
      return ;
    // for CMP and CMN instruction the S bit must be set
    // we generate empty function for this impossible case...
    // generate code for operand.
    if (specialize_Rn_reg)
      body << "  uint32_t tmp = proc.cpu.regs[" << reg_n << "];" << endl;
    else
      body << "  uint32_t tmp = proc.cpu.regs[p.args.any_reg.Rn];" << endl;
    generate_operand_code(body, opm, 0);
    switch (opcode) {
    case ADD:
      body << "  uint32_t r = tmp + opv";
      body << ((reg_d == ARM_PC) ? "+ 8;" : ";") << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  proc.cpu.cpsr.c = r<tmp;" << endl;
          body << "  proc.cpu.cpsr.v = ((tmp^~opv)&(tmp^r))>>31;" << endl;
        }
      }
      break;
    case ADC:
      body << "  uint32_t r = tmp + opv + proc.cpu.cpsr.c;" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  const uint32_t c = proc.cpu.cpsr.c;" << endl;
          body << "  proc.cpu.cpsr.c = r<tmp+c || tmp+c<c;" << endl;
          body << "  proc.cpu.cpsr.v = ((tmp^~opv)&(tmp^r))>>31;" << endl;
        }
      }
      break;
    case SUB:
      body << "  uint32_t r = tmp - opv ;" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  proc.cpu.cpsr.c = tmp>=opv;" << endl;
          body << "  proc.cpu.cpsr.v = ((tmp^opv)&(tmp^r))>>31;" << endl;
        }
      }
      break;
    case SBC:
      body << "  uint32_t r = tmp - opv - (! proc.cpu.cpsr.c);" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  proc.cpu.cpsr.c = tmp>=opv && tmp-opv>=(proc.cpu.cpsr.c?0:1);\n";
          body << "  proc.cpu.cpsr.v = ((tmp^opv)&(tmp^r))>>31;" << endl;
        }
      }
      break;
    case RSB:
      body << "  uint32_t r = opv - tmp;" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  proc.cpu.cpsr.c = opv>=tmp;" << endl;
          body << "  proc.cpu.cpsr.v = ((opv^tmp)&(opv^r))>>31;" << endl;
        }
      }
      break;
    case RSC:
      body << "  uint32_t r = opv - tmp - !proc.cpu.cpsr.c;" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  proc.cpu.cpsr.c = opv>=tmp && opv-tmp>=(proc.cpu.cpsr.c?0:1);\n";
          body << "  proc.cpu.cpsr.v = ((opv^tmp)&(opv^r))>>31;" << endl;
        }
      }
      break;
    case CMP:
      body << "  uint32_t r = tmp - opv ;" << endl;
      //if ((tmp - opv)==0)
      // body << "  proc.cpu.cpsr.z = 1;" << endl;
      // else
      // body << "  proc.cpu.cpsr.z = 0;" << endl;
      // body << "  proc.cpu.cpsr.n = r&0x80000000;" << endl;
      body << "  proc.cpu.cpsr.c = tmp>=opv;" << endl;
      body << "  proc.cpu.cpsr.v = ((tmp^opv)&(tmp^r))>>31;" << endl;
      break;
    case CMN:
      body << "  uint32_t r = tmp + opv ;" << endl;
      body << "  proc.cpu.cpsr.c = r<tmp;" << endl;
      body << "  proc.cpu.cpsr.v = ((tmp^~opv)&(tmp^r))>>31;" << endl;
      break;
    default:
      Fatal("illegal DPI operation");
    }
    if (s_bit && reg_d != ARM_PC) {
      body << "  proc.cpu.cpsr.z = !r;" << endl;
      body << "  proc.cpu.cpsr.n = r&0x80000000;"  <<endl;
    }
    if (opcode!=CMP && opcode!=CMN)
      if (reg_d == ARM_PC )
        body << "  proc.cpu.regs[15] = r+8;"<<endl;
      else if ( specialize_Rd_reg)
        body << "  proc.cpu.regs[" << reg_d << "] = r;"<<endl;
      else
        body << "  proc.cpu.regs[p.args.any_reg.Rd] = r;"<<endl;

  }
 else { // move instructions
    generate_operand_code(body, opm, (s_bit==1 && reg_d!=ARM_PC));
    switch (opcode) {
    case MOV:
      body <<  "  uint32_t r = opv; " << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else
          body << "  proc.cpu.cpsr.c = shift_c;" << endl;
      }
      break;
    case MVN:
      body <<  "  uint32_t r = ~opv;" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else
          body << "  proc.cpu.cpsr.c = shift_c;" << endl;
      }
      break;
    default:
      Fatal(string("internal error in file ")+__FILE__);
    }
    if (s_bit && reg_d != ARM_PC) {
      body << "  proc.cpu.cpsr.z = !r;" << endl;
      body << "  proc.cpu.cpsr.n = r&0x80000000;"  <<endl;
    }
    if (reg_d == ARM_PC)
      body << "  proc.cpu.regs[15] = r+8;" <<endl;
    else if (reg_d == specialize_Rd_reg)
      body << "  proc.cpu.regs[" << reg_d << "] = r;" <<endl;
    else
      body << "  proc.cpu.regs[p.args.any_reg.Rd] = r;" <<endl;
  }
}

void DPI_Generator::generate()
{
  // one file for all move instructions
  openFileSet("armpi_dpi_mov");
  generate_func_table("arm_dpi_move_table", "arm",
                      FIRST_MOVE, LAST_MOVE,
                      FIRST_OP_MODE, LAST_OP_MODE, false, false);
  closeFileSet();
  // one file for all boolean operation instructions
  openFileSet("armpi_dpi_bool");
  generate_func_table("arm_dpi_bool_table", "arm_dpi",
                      FIRST_BOOL, LAST_BOOL,
                      FIRST_OP_MODE, LAST_OP_MODE, false, false);
  closeFileSet();
  openFileSet("armpi_dpi_int");
  // one file for all boolean operation instructions
  generate_func_table("arm_dpi_int_table", "arm_dpi",
                      FIRST_DATA, LAST_DATA,
                      FIRST_OP_MODE, LAST_OP_MODE, false, false);
  closeFileSet();
}
#else
/*
 * Generate code in the case the destination and/or source registers
 * are specialized.
 * Generate immediate constant values instead of memory access
 * TRICK: if specialize_Rd is true we generate 15 functions
 * but if specialize_Rd is false, we still generate only two functions
 * one to handle the general case and one for special case of pc=r15
 */

void DPI_Generator::specialize_register(const string prefix,
                                        const ConditionCode cond,
                                        const int s_bit,
                                        const DPI_Opcode opcode,
                                        const OperandMode opm,
                                        const bool specialize_Rd_reg,
                                        const bool specialize_Rn_reg)
{
  string func_name = prefix;
  int reg_d, reg_n;
  int reg_start;

  if (specialize_Rd_reg)
    reg_start = 0;
  else
    reg_start = 14;
  newArrayRow(header_file);
  for (reg_d= reg_start; reg_d < ARM_NUM_REG ; ++reg_d) {
    if (!(reg_d==14 && !(specialize_Rd_reg)))
      func_name.append(REGISTER_SUFFIX[reg_d]);
//     else
//       func_name.append("_reg");
    if (specialize_Rn_reg) {
      newArrayRow(header_file);
      for (reg_n= 0; reg_n < ARM_NUM_REG ; ++reg_n) {
        func_name.append( REGISTER_SUFFIX[reg_n]);
        generate_instruction(func_name, cond, s_bit, opcode, opm,
                             specialize_Rd_reg, reg_d, true, reg_n);
        if (reg_n < ARM_NUM_REG-1)
          header_file << ", /* Rn */ " ;
      }
      closeArrayRow(header_file);
    }
    else {
      generate_instruction(func_name, cond, s_bit, opcode, opm,
                           false, reg_d, false, 0);
    }
    if (reg_d < ARM_NUM_REG-1)
      header_file << ", /* Rd */ " ;
  }; // end loop on register Rd
  closeArrayRow(header_file);
}

/*
 * Generate code for one semantic function
 * Print to files the generated  strings
 */
void DPI_Generator::generate_instruction(const string prefix,
                                         const ConditionCode cond,
                                         const int s_bit,
                                         const DPI_Opcode opcode,
                                         const OperandMode opm,
                                         const bool specialize_Rd_reg,
                                         const int reg_d,
                                         const bool specialize_Rn_reg,
                                         const int reg_n)
{
  ostringstream body  ;
  string func_name = prefix;
  string opm_suffix =  OPERAND_SUFFIX[opm];

  if (specialize_Rn_reg) opm_suffix.append(REGISTER_SUFFIX[reg_n]);
  // print function name
  code_file << "// Semantic function " << endl;
  code_file << PSEUDO_TYPE << func_name.append(opm_suffix) << ARGS <<endl;
  // generate function body
  body <<'{' <<endl;
  body <<"  proc.debug() <<\"" <<func_name <<"\" <<std::endl;" <<endl;
  generate_condition_code(body, cond);
  // invoke the operation method for this operator
  generate_operation(body, s_bit, opcode, opm,
                     specialize_Rd_reg, reg_d,
                     specialize_Rn_reg, reg_n);
  if (reg_d==15)
    code_file << body.str() << "  return BRANCH;" << endl << "}" << endl;
  else
    code_file << body.str() << "  return OK;" << endl << "}" << endl;

  // print function name to include file for declaration
  //   func_list_file << FUNC_TYPE << func_name << " ;" << endl;
  // print function name to table file for static array  initialization
 header_file << func_name << " " ;

}

/*
 * the generic function to generate an array of functions and their code
 * for all DPI with possibly shifted operand
 */

void DPI_Generator::generate_func_table(const string table_name,
                                        const string prefix,
                                        const DPI_Opcode opcode_from,
                                        const DPI_Opcode opcode_to,
                                        const OperandMode opm_from,
                                        const OperandMode opm_to,
                                        bool specialize_Rd_reg,
                                        bool specialize_Rn_reg)
{
  string func_name = prefix;
  ConditionCode cond;
  OperandMode opm;
  int dim;
  int *func_array_struct;
//   int level; // indentation level inside array

  // Compute number of dimensions for the array of functions, maximum is 8
  func_array_struct = new int [8];
  func_array_struct[0] = LAST_COND_CODE + 1; // N conditions codes
  func_array_struct[1] = 2 ; // bit S is 0 or 1
  func_array_struct[2] = opcode_to - opcode_from + 1 ; // N operation types
  func_array_struct[3] = opm_to - opm_from + 1 ; // M operand types
  // if specialize Rd then 16 functions, otherwise two for r15 and others
  func_array_struct[4] = ((specialize_Rd_reg) ? ARM_NUM_REG : 2);
  dim = 5;
  if (specialize_Rn_reg){
    dim += 1;
    func_array_struct[dim] = ARM_NUM_REG;
  }
  // create table declaration in header file
  openArrayDecl(header_file, table_name, func_array_struct, dim);
  // now loop on all specialized functions
  // print ',' after each element of an array
  // but do not print ',' after last element of an array
  for (cond=FIRST_COND_CODE ; cond <= LAST_COND_CODE ; ++cond) {
    DPI_Opcode opcode;
    int s_bit;
    newArrayRow(header_file); // generate curly bracket
    for (s_bit=0; s_bit <= 1; ++s_bit) {
      newArrayRow(header_file);
      for (opcode=opcode_from; opcode <= opcode_to; ++opcode) {
        newArrayRow(header_file);
        for (opm= opm_from; opm <= opm_to ; ++opm) {
          func_name = prefix + COND_CODE_SUFFIX[cond]
            + FLAGS_SUFFIX[s_bit] + OPCODE_SUFFIX[opcode];
          specialize_register(func_name, cond, s_bit, opcode, opm,
                              specialize_Rd_reg, specialize_Rn_reg);
          if (opm < opm_to)
            header_file << ", " ; // debug << "/* mode */" ;
	  close(open("/dev/null", 0));
        } //end operand loop
        closeArrayRow(header_file);
        if (opcode < opcode_to)
          header_file << ", "; // debug << " /* opcode */" ;
	close(open("/dev/null", 0));
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
 * ARM operations take first operand in Rn and the second operand
 * is possibly shifted with all combinations
 * The two operands are stored in variables tmp and opv
 * tmp contains register Rn and opv the result of shifter operand
 * The operation result is stored in variable r
 * then r is stored in destination register Rd
 * except for operations TST and TEQ that do not modiy Rd
 * r, tmp and opv are needed for computing the C,V,Z,N flags
 * Hopefully the C++ compiler will optimize.
 * Separate boolean operations from integer operations
 */

void DPI_Generator::generate_operation(ostringstream &body,
                                       const int s_bit,
                                       const DPI_Opcode opcode,
                                       const OperandMode opm,
                                       const bool specialize_Rd_reg,
                                       const int reg_d,
                                       const bool specialize_Rn_reg,
                                       const int reg_n)
{
  if (FIRST_BOOL<=opcode && opcode<=LAST_BOOL) {
    if ((opcode == TST || opcode == TEQ) & (s_bit == 0))
      return ;
    // for TST and TEQ instruction the S bit must be set
    // we generate empty function for this impossible case...
    // generate code for operand.
    generate_operand_code(body, opm,
                          s_bit == 1
                          && ((reg_d != ARM_PC)
                              || (reg_d == ARM_PC &&
                                  (opcode == TEQ || opcode == TST)
                                  )
                              ));
    if (specialize_Rn_reg)
      body << "  uint32_t tmp = proc.cpu.regs[" << reg_n << "] ";
    else
      body << "  uint32_t tmp = proc.cpu.regs[p.args.any_reg.Rn] ";
    switch (opcode) {

    case AND:
    case TST:
      body << " & opv;" << endl;
      break;

    case EOR:
    case TEQ:
      body << " ^ opv;" << endl;
      break;

    case ORR:
      body << " | opv;" << endl;
      break;

    case BIC:
      body << " &~ opv;" << endl;
      break;
    default:
      Fatal(string("internal error in file ")+__FILE__);
    }
    if (opcode != TST && opcode != TEQ) {
      if (reg_d == ARM_PC)
        body << "  proc.cpu.regs[15] = tmp+8;" << endl;
      else if (specialize_Rd_reg)
        body << "  proc.cpu.regs["<<reg_d<<"] = tmp;" << endl;
      else
        body << "  proc.cpu.regs[p.args.any_reg.Rd] = tmp;" << endl;
    }
    if (s_bit) {
      if ((reg_d == ARM_PC)
          && (opcode == AND || opcode == ORR || opcode == EOR || opcode == BIC))
        body << "  proc.spsr_to_cpsr();" << endl;
      else {
        body << "  proc.cpu.cpsr.n = tmp&0x80000000;" << endl;
        body << "  proc.cpu.cpsr.z = !tmp;"  <<endl;
        body << "  proc.cpu.cpsr.c = shift_c;" << endl;
      }
    }

  } else if (FIRST_DATA<=opcode && opcode<=LAST_DATA) { // integer instructions
    if ((opcode == CMP || opcode == CMN) & (s_bit == 0))
      return ;
    // for CMP and CMN instruction the S bit must be set
    // we generate empty function for this impossible case...
    // generate code for operand.
    if (specialize_Rn_reg)
      body << "  uint32_t tmp = proc.cpu.regs[" << reg_n << "];" << endl;
    else
      body << "  uint32_t tmp = proc.cpu.regs[p.args.any_reg.Rn];" << endl;
    generate_operand_code(body, opm, 0);
    switch (opcode) {
    case ADD:
      body << "  uint32_t r = tmp + opv;"<<endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  proc.cpu.cpsr.c = r<tmp;" << endl;
          body << "  proc.cpu.cpsr.v = ((tmp^~opv)&(tmp^r))>>31;" << endl;
        }
      }
      break;
    case ADC:
      body << "  uint32_t r = tmp + opv + proc.cpu.cpsr.c;" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  const uint32_t c = proc.cpu.cpsr.c;" << endl;
          body << "  proc.cpu.cpsr.c = r<tmp+c || tmp+c<c;" << endl;
          body << "  proc.cpu.cpsr.v = ((tmp^~opv)&(tmp^r))>>31;" << endl;
        }
      }
      break;
    case SUB:
      body << "  uint32_t r = tmp - opv ;" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  proc.cpu.cpsr.c = tmp>=opv;" << endl;
          body << "  proc.cpu.cpsr.v = ((tmp^opv)&(tmp^r))>>31;" << endl;
        }
      }
      break;
    case SBC:
      body << "  uint32_t r = tmp - opv - (! proc.cpu.cpsr.c);" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  proc.cpu.cpsr.c = tmp>=opv && tmp-opv>=(proc.cpu.cpsr.c?0:1);\n";
          body << "  proc.cpu.cpsr.v = ((tmp^opv)&(tmp^r))>>31;" << endl;
        }
      }
      break;
    case RSB:
      body << "  uint32_t r = opv - tmp;" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  proc.cpu.cpsr.c = opv>=tmp;" << endl;
          body << "  proc.cpu.cpsr.v = ((opv^tmp)&(opv^r))>>31;" << endl;
        }
      }
      break;
    case RSC:
      body << "  uint32_t r = opv - tmp - !proc.cpu.cpsr.c;" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else {
          body << "  proc.cpu.cpsr.c = opv>=tmp && opv-tmp>=(proc.cpu.cpsr.c?0:1);\n";
          body << "  proc.cpu.cpsr.v = ((opv^tmp)&(opv^r))>>31;" << endl;
        }
      }
      break;
    case CMP:
      body << "  uint32_t r = tmp - opv ;" << endl;
      //if ((tmp - opv)==0)
      // body << "  proc.cpu.cpsr.z = 1;" << endl;
      // else
      // body << "  proc.cpu.cpsr.z = 0;" << endl;
      // body << "  proc.cpu.cpsr.n = r&0x80000000;" << endl;
      body << "  proc.cpu.cpsr.c = tmp>=opv;" << endl;
      body << "  proc.cpu.cpsr.v = ((tmp^opv)&(tmp^r))>>31;" << endl;
      break;
    case CMN:
      body << "  uint32_t r = tmp + opv ;" << endl;
      body << "  proc.cpu.cpsr.c = r<tmp;" << endl;
      body << "  proc.cpu.cpsr.v = ((tmp^~opv)&(tmp^r))>>31;" << endl;
      break;
    default:
      Fatal("illegal DPI operation");
    }
    if (s_bit && reg_d != ARM_PC) {
      body << "  proc.cpu.cpsr.z = !r;" << endl;
      body << "  proc.cpu.cpsr.n = r&0x80000000;"  <<endl;
    }
    if (opcode!=CMP && opcode!=CMN) {
      if (reg_d == ARM_PC )
        body << "  proc.cpu.regs[15] = r+8;"<<endl;
      else if ( specialize_Rd_reg)
        body << "  proc.cpu.regs[" << reg_d << "] = r;"<<endl;
      else
        body << "  proc.cpu.regs[p.args.any_reg.Rd] = r;"<<endl;
    }
  }
 else { // move instructions
    generate_operand_code(body, opm, (s_bit==1 && reg_d!=ARM_PC));
    switch (opcode) {
    case MOV:
      body <<  "  uint32_t r = opv; " << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else
          body << "  proc.cpu.cpsr.c = shift_c;" << endl;
      }
      break;
    case MVN:
      body <<  "  uint32_t r = ~opv;" << endl;
      if (s_bit) {
        if (reg_d == ARM_PC)
          body << "  proc.spsr_to_cpsr();" << endl;
        else
          body << "  proc.cpu.cpsr.c = shift_c;" << endl;
      }
      break;
    default:
      Fatal(string("internal error in file ")+__FILE__);
    }
    if (s_bit && reg_d != ARM_PC) {
      body << "  proc.cpu.cpsr.z = !r;" << endl;
      body << "  proc.cpu.cpsr.n = r&0x80000000;"  <<endl;
    }
    if (reg_d == ARM_PC)
      body << "  proc.cpu.regs[15] = r+8;" <<endl;
    else if (reg_d == specialize_Rd_reg)
      body << "  proc.cpu.regs[" << reg_d << "] = r;" <<endl;
    else
      body << "  proc.cpu.regs[p.args.any_reg.Rd] = r;" <<endl;
  }
}

void DPI_Generator::generate()
{
  // one file for all move instructions
  openFileSet("armpi_dpi_mov");
  generate_func_table("arm_dpi_move_table", "arm",
                      FIRST_MOVE, LAST_MOVE,
                      FIRST_OP_MODE, LAST_OP_MODE, false, false);
  closeFileSet();
  // one file for all boolean operation instructions
  openFileSet("armpi_dpi_bool");
  generate_func_table("arm_dpi_bool_table", "arm_dpi",
                      FIRST_BOOL, LAST_BOOL,
                      FIRST_OP_MODE, LAST_OP_MODE, false, false);
  closeFileSet();
  openFileSet("armpi_dpi_int");
  // one file for all boolean operation instructions
  generate_func_table("arm_dpi_int_table", "arm_dpi",
                      FIRST_DATA, LAST_DATA,
                      FIRST_OP_MODE, LAST_OP_MODE, false, false);
  closeFileSet();
}

#endif
#endif
#endif
