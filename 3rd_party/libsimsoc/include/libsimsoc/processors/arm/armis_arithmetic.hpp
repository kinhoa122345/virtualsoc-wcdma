//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARMIS_ARITHMETIC_HPP
#define ARMIS_ARITHMETIC_HPP

#include "libsimsoc/processors/arm/armis.hpp"
#include "libsimsoc/processors/arm/arm_condition.hpp"
#include "libsimsoc/processors/arm/arm_shift.hpp"
#include "libsimsoc/processors/arm/arm_dpi.hpp"
#include "libsimsoc/processors/arm/arm_cpu.hpp"
#include "libsimsoc/processors/arm/armpi.hpp"

namespace simsoc {

/******************************************************************************/

struct ARM_DPI_ShiftImm: public ARM32_Instruction {
  ARM_Condition cond;
  uint8_t shift_amount;
  ARM_Shift shift;
  uint8_t Rm;
  ARM_DPI_ShiftImm(ARM_Condition c, uint8_t sa, uint8_t z, uint8_t m);
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

struct ARM_DPI_ShiftReg: public ARM32_Instruction {
  ARM_Condition cond;
  uint8_t Rs;
  ARM_Shift shift;
  uint8_t Rm;
  ARM_DPI_ShiftReg(ARM_Condition c, uint8_t sa, uint8_t z, uint8_t m);
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

struct ARM_DPI_Imm: public ARM32_Instruction {
  ARM_Condition cond;
  uint8_t rotate_amount;
  uint8_t immed;
  ARM_DPI_Imm(ARM_Condition c, uint8_t ra, uint8_t i);
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

/******************************************************************************/

template <class op>
struct ARM_NumericIS: public ARM_DPI_ShiftImm {
  bool s;
  uint8_t Rd;
  uint8_t Rn;
  ARM_NumericIS(ARM_Condition c, bool s_, uint8_t d, uint8_t n,
                uint8_t sa, uint8_t z, uint8_t m);
  uint32_t computeShift(ARM_Processor &proc, uint32_t m);
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const {return false;}
  bool may_branch() const {return Rd==ARM_CPU::PC;};
};

template <class op>
struct ARM_NumericRS: public ARM_DPI_ShiftReg {
  bool s;
  uint8_t Rd;
  uint8_t Rn;
  ARM_NumericRS(ARM_Condition c, bool s_, uint8_t d, uint8_t n,
                uint8_t sa, uint8_t z, uint8_t m);
  uint32_t computeShift(ARM_Processor &proc, uint32_t m);
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const {return false;}
  bool may_branch() const {return Rd==ARM_CPU::PC;};
};

template <class op>
struct ARM_NumericImm: public ARM_DPI_Imm {
  bool s;
  uint8_t Rd;
  uint8_t Rn;
  ARM_NumericImm(ARM_Condition c, bool s_, uint8_t d, uint8_t n,
                 uint8_t ra, uint8_t i);
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const {return false;}
  bool may_branch() const {return Rd==ARM_CPU::PC;};
};

/******************************************************************************/

struct ARM_adc {
  static const unsigned char id = 1;
  static const DPI_Opcode opcode = ADC;
  static uint32_t result(uint32_t a, uint32_t b, bool c) {return a+b+(c?1:0);}
  static void updateCV(ARM_StatusRegister& sr, uint32_t a, uint32_t b, uint32_t r) {
    const uint32_t c = static_cast<uint32_t>(sr.c);
    sr.c = r<a+c || a+c<c;
    sr.v = ((a^~b)&(a^r))>>31;
  }
};

struct ARM_add {
  static const unsigned char id = 0;
  static const DPI_Opcode opcode = ADD;
  static uint32_t result(uint32_t a, uint32_t b, bool c) {return a+b;}
  static void updateCV(ARM_StatusRegister& sr, uint32_t a, uint32_t b, uint32_t r) {
    sr.c = r<a;
    sr.v = ((a^~b)&(a^r))>>31;
  }
};

struct ARM_rsb {
  static const unsigned char id = 4;
  static const DPI_Opcode opcode = RSB;
  static uint32_t result(uint32_t a, uint32_t b, bool c) {return b-a;}
  static void updateCV(ARM_StatusRegister& sr, uint32_t a, uint32_t b, uint32_t r) {
    sr.c = b>=a;
    sr.v = ((b^a)&(b^r))>>31;
  }
};

struct ARM_rsc {
  static const unsigned char id = 5;
  static const DPI_Opcode opcode = RSC;
  static uint32_t result(uint32_t a, uint32_t b, bool c) {return b-a-(c?0:1);}
  static void updateCV(ARM_StatusRegister& sr, uint32_t a, uint32_t b, uint32_t r) {
    const uint32_t not_c = static_cast<uint32_t>(!sr.c);
    sr.c = b>=a && (b-a)>=not_c;
    sr.v = ((b^a)&(b^r))>>31;
  }
};

struct ARM_sbc {
  static const unsigned char id = 3;
  static const DPI_Opcode opcode = SBC;
  static uint32_t result(uint32_t a, uint32_t b, bool c) {return a-b-(c?0:1);}
  static void updateCV(ARM_StatusRegister& sr, uint32_t a, uint32_t b, uint32_t r) {
    const uint32_t not_c = static_cast<uint32_t>(!sr.c);
    sr.c = a>=b && (a-b)>=not_c;
    sr.v = ((a^b)&(a^r))>>31;
  }
};

struct ARM_sub {
  static const unsigned char id = 2;
  static const DPI_Opcode opcode = SUB;
  static uint32_t result(uint32_t a, uint32_t b, bool c) {return a-b;}
  static void updateCV(ARM_StatusRegister& sr, uint32_t a, uint32_t b, uint32_t r) {
    sr.c = a>=b;
    sr.v = ((a^b)&(a^r))>>31;
  }
};

/******************************************************************************/

template <class op>
struct ARM_BooleanIS: public ARM_DPI_ShiftImm {
  bool s;
  uint8_t Rd;
  uint8_t Rn;
  ARM_BooleanIS(ARM_Condition c, bool s_, uint8_t d, uint8_t n,
                uint8_t sa, uint8_t z, uint8_t m);
  uint32_t computeShift(ARM_Processor &proc, uint32_t m);
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const {return false;}
  bool may_branch() const {return Rd==ARM_CPU::PC;};
};

template <class op>
struct ARM_BooleanRS: public ARM_DPI_ShiftReg {
  bool s;
  uint8_t Rd;
  uint8_t Rn;
  ARM_BooleanRS(ARM_Condition c, bool s_, uint8_t d, uint8_t n,
                uint8_t sa, uint8_t z, uint8_t m);
  uint32_t computeShift(ARM_Processor &proc, uint32_t m);
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const {return false;}
  bool may_branch() const {return Rd==ARM_CPU::PC;};
};

template <class op>
struct ARM_BooleanImm: public ARM_DPI_Imm {
  bool s;
  uint8_t Rd;
  uint8_t Rn;
  ARM_BooleanImm(ARM_Condition c, bool s_, uint8_t d, uint8_t n,
                 uint8_t ra, uint8_t i);
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const {return false;}
  bool may_branch() const {return Rd==ARM_CPU::PC;};
};

/********************************************************************************/

struct ARM_and {
  static const DPI_Opcode opcode = AND;
  static uint32_t result(uint32_t a, uint32_t b, bool c) {return a&b;}
};

struct ARM_bic {
  static const DPI_Opcode opcode = BIC;
  static uint32_t result(uint32_t a, uint32_t b, bool c) {return a&~b;}
};

struct ARM_eor {
  static const DPI_Opcode opcode = EOR;
  static uint32_t result(uint32_t a, uint32_t b, bool c) {return a^b;}
};

struct ARM_orr {
  static const DPI_Opcode opcode = ORR;
  static uint32_t result(uint32_t a, uint32_t b, bool c) {return a|b;}
};

/******************************************************************************/

template <class op>
struct ARM_CompareIS: public ARM_DPI_ShiftImm {
  uint8_t Rn;
  ARM_CompareIS(ARM_Condition c, uint8_t n, uint8_t sa, uint8_t z, uint8_t m);
  uint32_t computeShift(ARM_Processor &proc, uint32_t m);
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const {return false;}
  bool may_branch() const {return false;};
};

template <class op>
struct ARM_CompareRS: public ARM_DPI_ShiftReg {
  uint8_t Rn;
  ARM_CompareRS(ARM_Condition c, uint8_t n, uint8_t sa, uint8_t z, uint8_t m);
  uint32_t computeShift(ARM_Processor &proc, uint32_t m);
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const {return false;}
  bool may_branch() const {return false;};
};

template <class op>
struct ARM_CompareImm: public ARM_DPI_Imm {
  uint8_t Rn;
  ARM_CompareImm(ARM_Condition c, uint8_t n, uint8_t ra, uint8_t i);
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const {return false;}
  bool may_branch() const {return false;};
};

/******************************************************************************/

struct ARM_cmn {
  static const DPI_Opcode opcode = CMN;
  static uint32_t result(uint32_t a, uint32_t b) {return a+b;}
  static void updateCV(ARM_StatusRegister& sr, uint32_t a, uint32_t b, uint32_t r) {
    sr.c = r<a;
    sr.v = ((a^~b)&(a^r))>>31;
  }
};

struct ARM_cmp {
  static const DPI_Opcode opcode = CMP;
  static uint32_t result(uint32_t a, uint32_t b) {return a-b;}
  static void updateCV(ARM_StatusRegister& sr, uint32_t a, uint32_t b, uint32_t r) {
    sr.c = a>=b;
    sr.v = ((a^b)&(a^r))>>31;
  }
};

/******************************************************************************/

template <class op>
struct ARM_TestIS: public ARM_DPI_ShiftImm {
  uint8_t Rn;
  ARM_TestIS(ARM_Condition c, uint8_t n, uint8_t sa, uint8_t z, uint8_t m);
  uint32_t computeShift(ARM_Processor &proc, uint32_t m);
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const {return false;}
  bool may_branch() const {return false;};
};

template <class op>
struct ARM_TestRS: public ARM_DPI_ShiftReg {
  uint8_t Rn;
  ARM_TestRS(ARM_Condition c, uint8_t n, uint8_t sa, uint8_t z, uint8_t m);
  uint32_t computeShift(ARM_Processor &proc, uint32_t m);
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const {return false;}
  bool may_branch() const {return false;};
};

template <class op>
struct ARM_TestImm: public ARM_DPI_Imm {
  uint8_t Rn;
  ARM_TestImm(ARM_Condition c, uint8_t n, uint8_t ra, uint8_t i);
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const {return false;}
  bool may_branch() const {return false;};
};

/******************************************************************************/

struct ARM_teq {
  static const DPI_Opcode opcode = TEQ;
  static uint32_t result(uint32_t a, uint32_t b) {return a^b;}
};

struct ARM_tst {
  static const DPI_Opcode opcode = TST;
  static uint32_t result(uint32_t a, uint32_t b) {return a&b;}
};

/******************************************************************************/

template<class op>
struct ARM_MoveIS: public ARM_DPI_ShiftImm {
  bool s;
  uint8_t Rd;
  ARM_MoveIS(ARM_Condition c, bool s_, uint8_t d, uint8_t sa, uint8_t z, uint8_t m);
  uint32_t computeShift(ARM_Processor &proc, uint32_t m);
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const {return false;}
  bool may_branch() const {return Rd==ARM_CPU::PC;};
};

template<class op>
struct ARM_MoveRS: public ARM_DPI_ShiftReg {
  bool s;
  uint8_t Rd;
  ARM_MoveRS(ARM_Condition c, bool s_, uint8_t d, uint8_t sa, uint8_t z, uint8_t m);
  uint32_t computeShift(ARM_Processor &proc, uint32_t m);
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const {return false;}
  bool may_branch() const {return Rd==ARM_CPU::PC;};
};

template<class op>
struct ARM_MoveImm: public ARM_DPI_Imm {
  bool s;
  uint8_t Rd;
  ARM_MoveImm(ARM_Condition c, bool s_, uint8_t d, uint8_t ra, uint8_t i);
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const {return false;}
  bool may_branch() const {return Rd==ARM_CPU::PC;};
};

/******************************************************************************/

struct ARM_mov {
  static const DPI_Opcode opcode = MOV;
  static uint32_t result(uint32_t b) {return b;}
};

struct ARM_mvn {
  static const DPI_Opcode opcode = MVN;
  static uint32_t result(uint32_t b) {return ~b;}
};

/******************************************************************************/

struct ARM_clz: public ARM32_Instruction {
  ARM_Condition cond;
  uint8_t Rd;
  uint8_t Rm;
  ARM_clz(ARM_Condition c, uint8_t d, uint8_t m):
    ARM32_Instruction(), cond(c), Rd(d), Rm(m) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const {return false;}
  bool may_branch() const {return false;};
};

/******************************************************************************/

struct ARM_mla: public ARM32_Instruction {
  ARM_Condition cond;
  bool s;
  uint8_t Rd;
  uint8_t Rm;
  uint8_t Rs;
  uint8_t Rn;
  ARM_mla(ARM_Condition c, bool s_, uint8_t d, uint8_t m, uint8_t rs, uint8_t n);
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const {return false;}
  bool may_branch() const {return false;};
};

struct ARM_mul: public ARM32_Instruction {
  ARM_Condition cond;
  bool s;
  uint8_t Rd;
  uint8_t Rm;
  uint8_t Rs;
  ARM_mul(ARM_Condition c, bool s_, uint8_t d, uint8_t m, uint8_t rs);
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const {return false;}
  bool may_branch() const {return false;};
};

template <class op>
struct ARM_longmult: public ARM32_Instruction {
  ARM_Condition cond;
  bool s;
  uint8_t RdLo;  // != PC
  uint8_t RdHi; // != PC
  uint8_t Rm;  // != PC
  uint8_t Rs; // != PC
  ARM_longmult(ARM_Condition c, bool s_, uint8_t d, uint8_t D, uint8_t m, uint8_t rs):
    ARM32_Instruction(), cond(c), s(s_), RdLo(d), RdHi(D), Rm(m), Rs(rs) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const {return false;}
  bool may_branch() const {return false;};
};

struct ARM_smlal {
  static const uint8_t opcode = 3;
  static const char * name() {return "SMLAL";}
  static void compute(uint32_t & RdHi, uint32_t & RdLo, uint32_t Rm, uint32_t Rs);
};

struct ARM_smull {
  static const uint8_t opcode = 2;
  static const char * name() {return "SMULL";}
  static void compute(uint32_t & RdHi, uint32_t & RdLo, uint32_t Rm, uint32_t Rs);
};

struct ARM_umlal {
  static const uint8_t opcode = 5;
  static const char * name() {return "UMLAL";}
  static void compute(uint32_t & RdHi, uint32_t & RdLo, uint32_t Rm, uint32_t Rs);
};

struct ARM_umull {
  static const uint8_t opcode = 4;
  static const char * name() {return "UMULL";}
  static void compute(uint32_t & RdHi, uint32_t & RdLo, uint32_t Rm, uint32_t Rs);
};

} // namespace simsoc

#include "armis_arithmetic.tpp"

#endif //ARMIS_ARITHMETIC_HPP
