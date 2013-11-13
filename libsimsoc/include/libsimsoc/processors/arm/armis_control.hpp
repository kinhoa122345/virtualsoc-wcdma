//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARMIS_CONTROL_HPP
#define ARMIS_CONTROL_HPP

#include "libsimsoc/processors/arm/armis.hpp"
#include "libsimsoc/processors/arm/arm_condition.hpp"

namespace simsoc {

struct ARM_InstrWithTargetAddr: public ARM32_Instruction {
  int32_t offset;
  bool thumb_mode;
  ARM_InstrWithTargetAddr(int32_t offset_, bool tm):
    ARM32_Instruction(), offset(offset_), thumb_mode(tm) {}
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

struct ARM_b: public ARM_InstrWithTargetAddr {
  ARM_Condition cond;
  ARM_b(ARM_Condition c, int32_t offset):
    ARM_InstrWithTargetAddr(offset,false), cond(c) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const {return false;}
};

struct ARM_Idle: public ARM_InstrWithTargetAddr {
  ARM_Idle():
    ARM_InstrWithTargetAddr(-8,false) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const {return true;}
};

struct ARM_bl: public ARM_InstrWithTargetAddr {
  ARM_Condition cond;
  ARM_bl(ARM_Condition c, int32_t offset):
    ARM_InstrWithTargetAddr(offset,false), cond(c) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const  {return false;}
};

struct ARM_bx: public ARM32_Instruction {
  ARM_Condition cond;
  uint8_t Rm;
  ARM_bx(ARM_Condition c, uint8_t m):
    ARM32_Instruction(), cond(c), Rm(m) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const  {return false;}
};

struct ARM_blx: public ARM_InstrWithTargetAddr {
  ARM_blx(int32_t offset):
    ARM_InstrWithTargetAddr(offset,true) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() {return false;}
};

struct ARM_blx2: public ARM32_Instruction {
  ARM_Condition cond;
  uint8_t Rm;
  ARM_blx2(ARM_Condition c, uint8_t m):
    ARM32_Instruction(), cond(c), Rm(m) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const  {return false;}
};

struct ARM_bkpt: public ARM32_Instruction {
  uint16_t immed;
  ARM_bkpt(uint16_t i):
    ARM32_Instruction(), immed(i) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const  {return true;}
};

struct ARM_mrs: public ARM32_Instruction {
  ARM_Condition cond;
  uint8_t Rd;
  bool R;
  ARM_mrs(ARM_Condition c, uint8_t d, bool r):
    ARM32_Instruction(), cond(c), Rd(d), R(r) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const  {return false;}
  bool may_branch() const {return false;}
};

struct ARM_msr_imm: public ARM32_Instruction {
  ARM_Condition cond;
  bool R;
  uint8_t fields;
  uint32_t immed;
  ARM_msr_imm(ARM_Condition c, bool r, uint8_t f, uint32_t i):
    ARM32_Instruction(), cond(c), R(r), fields(f), immed(i) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const {return true;}
  bool may_branch() const {return fields&1;}
};

struct ARM_msr_reg: public ARM32_Instruction {
  ARM_Condition cond;
  bool R;
  uint8_t fields;
  uint8_t Rm;
  ARM_msr_reg(ARM_Condition c, bool r, uint8_t f, uint8_t m):
    ARM32_Instruction(), cond(c), R(r), fields(f), Rm(m) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const  {return true;}
  bool may_branch() const {return fields&1;}
};

struct ARM_swi: public ARM32_Instruction {
  ARM_Condition cond;
  uint32_t immed;
  bool m;
  ARM_swi(ARM_Condition c, uint32_t i, bool user_level):
    ARM32_Instruction(), cond(c), immed(i), m(user_level) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

  bool may_raise_something() const  {return true;}
};

} // namespace simsoc

#endif //ARMIS_CONTROL_HPP
