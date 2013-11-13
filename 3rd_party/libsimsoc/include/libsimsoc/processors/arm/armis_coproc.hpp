//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARMIS_COPROC_HPP
#define ARMIS_COPROC_HPP

#include "libsimsoc/processors/arm/armis.hpp"
#include "libsimsoc/processors/arm/arm_condition.hpp"

namespace simsoc {

struct ARM_cdp: public ARM32_Instruction {
  ARM_Condition cond;
  uint8_t coproc;
  uint8_t opcode1;
  uint8_t CRd;
  uint8_t CRn;
  uint8_t CRm;
  uint8_t opcode2;
  ARM_cdp(ARM_Condition c, uint8_t cp, uint8_t o1,
          uint8_t d, uint8_t n, uint8_t m, uint8_t o2):
    ARM32_Instruction(), cond(c), coproc(cp), opcode1(o1),
    CRd(d), CRn(n), CRm(m), opcode2(o2) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

struct ARM_cdp2: public ARM32_Instruction {
  uint8_t coproc;
  uint8_t opcode1;
  uint8_t CRd;
  uint8_t CRn;
  uint8_t CRm;
  uint8_t opcode2;
  ARM_cdp2(uint8_t cp, uint8_t o1,
          uint8_t d, uint8_t n, uint8_t m, uint8_t o2):
    ARM32_Instruction(), coproc(cp), opcode1(o1),
    CRd(d), CRn(n), CRm(m), opcode2(o2) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

struct ARM_ldc: public ARM32_Instruction {
  ARM_Condition cond;
  bool l;
  uint8_t coproc;
  uint8_t CRd;
  bool p;
  bool u;
  uint8_t Rn;
  bool w;
  uint8_t offset;
  ARM_ldc(ARM_Condition c, bool l_, uint8_t cp, uint8_t d,
          bool p_, bool u_, uint8_t n, bool w_, uint8_t o):
    ARM32_Instruction(), cond(c), l(l_), coproc(cp), CRd(d), p(p_), u(u_),
    Rn(n), w(w_), offset(o) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

struct ARM_ldc2: public ARM32_Instruction {
  bool l;
  uint8_t coproc;
  uint8_t CRd;
  bool p;
  bool u;
  uint8_t Rn;
  bool w;
  uint8_t offset;
  ARM_ldc2(bool l_, uint8_t cp, uint8_t d,
          bool p_, bool u_, uint8_t n, bool w_, uint8_t o):
    ARM32_Instruction(), l(l_), coproc(cp), CRd(d), p(p_), u(u_),
    Rn(n), w(w_), offset(o) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

struct ARM_stc: public ARM32_Instruction {
  ARM_Condition cond;
  bool l;
  uint8_t coproc;
  uint8_t CRd;
  bool p;
  bool u;
  uint8_t Rn;
  bool w;
  uint8_t offset;
  ARM_stc(ARM_Condition c, bool l_, uint8_t cp, uint8_t d,
          bool p_, bool u_, uint8_t n, bool w_, uint8_t o):
    ARM32_Instruction(), cond(c), l(l_), coproc(cp), CRd(d), p(p_), u(u_),
    Rn(n), w(w_), offset(o) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

struct ARM_stc2: public ARM32_Instruction {
  bool l;
  uint8_t coproc;
  uint8_t CRd;
  bool p;
  bool u;
  uint8_t Rn;
  bool w;
  uint8_t offset;
  ARM_stc2(bool l_, uint8_t cp, uint8_t d,
          bool p_, bool u_, uint8_t n, bool w_, uint8_t o):
    ARM32_Instruction(), l(l_), coproc(cp), CRd(d), p(p_), u(u_),
    Rn(n), w(w_), offset(o) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

struct ARM_mcr: public ARM32_Instruction {
  ARM_Condition cond;
  uint8_t coproc;
  uint8_t opcode1;
  uint8_t Rd;
  uint8_t CRn;
  uint8_t CRm;
  uint8_t opcode2;
  ARM_mcr(ARM_Condition c, uint8_t cp, uint8_t o1,
          uint8_t d, uint8_t n, uint8_t m, uint8_t o2):
    ARM32_Instruction(), cond(c), coproc(cp), opcode1(o1),
    Rd(d), CRn(n), CRm(m), opcode2(o2) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

struct ARM_mcr2: public ARM32_Instruction {
  uint8_t coproc;
  uint8_t opcode1;
  uint8_t Rd;
  uint8_t CRn;
  uint8_t CRm;
  uint8_t opcode2;
  ARM_mcr2(uint8_t cp, uint8_t o1,
          uint8_t d, uint8_t n, uint8_t m, uint8_t o2):
    ARM32_Instruction(), coproc(cp), opcode1(o1),
    Rd(d), CRn(n), CRm(m), opcode2(o2) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

struct ARM_mrc: public ARM32_Instruction {
  ARM_Condition cond;
  uint8_t coproc;
  uint8_t opcode1;
  uint8_t Rd;
  uint8_t CRn;
  uint8_t CRm;
  uint8_t opcode2;
  ARM_mrc(ARM_Condition c, uint8_t cp, uint8_t o1,
          uint8_t d, uint8_t n, uint8_t m, uint8_t o2):
    ARM32_Instruction(), cond(c), coproc(cp), opcode1(o1),
    Rd(d), CRn(n), CRm(m), opcode2(o2) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
  bool may_branch() const {return false;}
};

struct ARM_mrc2: public ARM32_Instruction {
  uint8_t coproc;
  uint8_t opcode1;
  uint8_t Rd;
  uint8_t CRn;
  uint8_t CRm;
  uint8_t opcode2;
  ARM_mrc2(uint8_t cp, uint8_t o1,
           uint8_t d, uint8_t n, uint8_t m, uint8_t o2):
    ARM32_Instruction(), coproc(cp), opcode1(o1),
    Rd(d), CRn(n), CRm(m), opcode2(o2) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
  bool may_branch() const {return false;}
};

} // namespace simsoc

#endif //ARMIS_COPROC_HPP
