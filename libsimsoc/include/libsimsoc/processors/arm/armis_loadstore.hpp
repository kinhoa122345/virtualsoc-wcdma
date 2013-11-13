//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARMIS_LOADSTORE_HPP
#define ARMIS_LOADSTORE_HPP

#include "libsimsoc/processors/arm/arm_condition.hpp"
#include "libsimsoc/processors/arm/arm_shift.hpp"
#include "libsimsoc/bitwise_operator.hpp"
#include "libsimsoc/processors/arm/armis.hpp"
#include "libsimsoc/processors/arm/armpi.hpp"
#include "libsimsoc/processors/arm/arm_processor.hpp"
#include "libsimsoc/processors/arm/arm_loadstore.hpp"
#include "libsimsoc/display.hpp"

namespace simsoc {

struct ARM_LoadStoreImmBase: public ARM32_Instruction {
  ARM_Condition cond;
  uint8_t Rd;
  bool p;
  bool u;
  bool w;
  uint8_t Rn;
  uint16_t immed;
  ARM_LoadStoreImmBase(ARM_Condition c, uint8_t d,
                       bool p_, bool u_, bool w_,  uint8_t n, uint16_t i):
    ARM32_Instruction(), cond(c), Rd(d), p(p_), u(u_), w(w_), Rn(n), immed(i) {}
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

template <class op>
struct ARM_LoadStoreImm: public ARM_LoadStoreImmBase {
  ARM_LoadStoreImm(ARM_Condition c, uint8_t d, bool p, bool u, bool w,  uint8_t n, uint16_t i):
    ARM_LoadStoreImmBase(c,d,p,u,w,n,i) {}
  virtual void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;

  bool may_raise_something() const;
  bool may_branch() const;
  bool is_load_local_data() const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

struct ARM_LoadStoreRegBase: public ARM32_Instruction {
  ARM_Condition cond;
  uint8_t Rd;
  bool p;
  bool u;
  bool w;
  uint8_t Rn;
  uint8_t Rm;
  ARM_LoadStoreRegBase(ARM_Condition c, uint8_t d, bool p_, bool u_, bool w_,
                       uint8_t n, uint8_t m):
    ARM32_Instruction(), cond(c), Rd(d), p(p_), u(u_), w(w_), Rn(n), Rm(m) {}
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

template <class op>
struct ARM_LoadStoreReg: public ARM_LoadStoreRegBase {
  ARM_LoadStoreReg(ARM_Condition c, uint8_t d, bool p, bool u, bool w,
                   uint8_t n, uint8_t m):
    ARM_LoadStoreRegBase(c,d,p,u,w,n,m) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;

  bool may_raise_something() {return true;}
  bool may_branch() const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

struct ARM_LoadStoreScRgBase: public ARM32_Instruction {
  ARM_Condition cond;
  uint8_t Rd;
  bool p;
  bool u;
  bool w;
  uint8_t Rn;
  uint8_t shift_imm;
  ARM_Shift shift;
  uint8_t Rm;
  ARM_LoadStoreScRgBase(ARM_Condition c, uint8_t d, bool p_, bool u_, bool w_, uint8_t n,
                        uint8_t si, ARM_Shift s, uint8_t m):
    ARM32_Instruction(), cond(c), Rd(d), p(p_), u(u_), w(w_), Rn(n),
    shift_imm((!si && (s==LSR||s==ASR))? 32: si),
    shift((s==ROR && si==0)? RRX: s),
    Rm(m) {}
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

template <class op>
struct ARM_LoadStoreScRg: public ARM_LoadStoreScRgBase {
  ARM_LoadStoreScRg(ARM_Condition c, uint8_t d, bool p, bool u, bool w, uint8_t n,
                    uint8_t si, ARM_Shift s, uint8_t m):
    ARM_LoadStoreScRgBase(c,d,p,u,w,n,si,s,m) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;

  bool may_raise_something() {return true;}
  bool may_branch() const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

/******************************************************************************/

struct ARM_ldr {
  static const unsigned char id = 0;
  static const LoadStoreOpcode opcode = LDR;
  static const char * name() {return "LDR";}
  static const char * suffix() {return "";}
  static void doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr);
};

struct ARM_ldrb {
  static const unsigned char id = 1;
  static const LoadStoreOpcode opcode = LDRB;
  static const char * name() {return "LDR";}
  static const char * suffix() {return "B";}
  static void doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr);
};

struct ARM_str {
  static const unsigned char id = 4;
  static const LoadStoreOpcode opcode = STR;
  static const char * name() {return "STR";}
  static const char * suffix() {return "";}
  static void doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr);
};

struct ARM_strb {
  static const unsigned char id = 5;
 static const LoadStoreOpcode opcode = STRB;
  static const char * name() {return "STR";}
  static const char * suffix() {return "B";}
  static void doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr);
};

struct ARM_ldrt {
  static const unsigned char id = 2;
  static const LoadStoreOpcode opcode = LDRT;
  static const char * name() {return "LDR";}
  static const char * suffix() {return "T";}
  static void doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr);
};

struct ARM_ldrbt {
  static const unsigned char id = 3;
  static const LoadStoreOpcode opcode = LDRBT;
  static const char * name() {return "LDR";}
  static const char * suffix() {return "BT";}
  static void doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr);
};

struct ARM_strt {
  static const unsigned char id = 6;
  static const LoadStoreOpcode opcode = STRT;
  static const char * name() {return "STR";}
  static const char * suffix() {return "T";}
  static void doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr);
};

struct ARM_strbt {
  static const unsigned char id = 7;
  static const LoadStoreOpcode opcode = STRBT;
  static const char * name() {return "STR";}
  static const char * suffix() {return "BT";}
  static void doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr);
};

/******************************************************************************/

struct ARM_ldrh {
  static const unsigned char id = 8;
  static const LoadStoreOpcode opcode = LDRH;
  static const char * name() {return "LDR";}
  static const char * suffix() {return "H";}
  static void doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr);
};

struct ARM_ldrsb {
  static const unsigned char id = 9;
  static const LoadStoreOpcode opcode = LDRSB;
  static const char * name() {return "LDR";}
  static const char * suffix() {return "SB";}
  static void doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr);
};

struct ARM_ldrsh {
  static const unsigned char id = 10;
  static const LoadStoreOpcode opcode = LDRSH;
  static const char * name() {return "LDR";}
  static const char * suffix() {return "SH";}
  static void doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr);
};

struct ARM_strh {
  static const unsigned char id = 11;
  static const LoadStoreOpcode opcode = STRH;
  static const char * name() {return "STR";}
  static const char * suffix() {return "H";}
  static void doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr);
};

struct ARM_ldrd {
  static const unsigned char id = 12;
  static const LoadStoreOpcode opcode = LDRD;
  static const char * name() {return "LDR";}
  static const char * suffix() {return "D";}
  static void doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr);
};

struct ARM_strd {
  static const unsigned char id = 13;
  static const LoadStoreOpcode opcode = STRD;
  static const char * name() {return "STR";}
  static const char * suffix() {return "D";}
  static void doAccess(ARM_Processor &proc, uint8_t Rd, uint32_t addr);
};

/******************************************************************************/

// Load Store Multiple
struct ARM_lsm: public ARM32_Instruction {
  typedef enum {DA,IA,DB,IB} mode;
  ARM_Condition cond;
  mode am;
  bool w;
  uint8_t Rn;
  uint16_t registers;
  uint8_t nb_reg; // Number of Registers
  ARM_lsm(ARM_Condition c, uint8_t a, bool w_, uint8_t n, uint16_t regs):
    ARM32_Instruction(),
    cond(c), am((mode) a), w(w_), Rn(n), registers(regs),
    nb_reg(numberOfSetBitsIn(regs)) {}
  std::ostream& display(std::ostream& os) const;

  void compute_addresses(ARM_Processor &proc,
                         uint32_t& start, uint32_t& end, uint32_t& new_Rn);
  void update_Rn_offset(ARM_Processor &proc);
  virtual const char * opname() const =0;
  virtual const char * suffix() const =0;
  virtual bool special() const {return false;}
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

struct ARM_ldm: public ARM_lsm {
  ARM_ldm(ARM_Condition c, uint8_t a, bool w, uint8_t n, uint16_t regs):
    ARM_lsm(c,a,w,n,regs) {}
  const char * opname() const {return "LDM";}
  const char * suffix() const;
  virtual void exec(ARM_Processor &proc);
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
  virtual bool may_branch() const {return registers&(1<<ARM_CPU::PC);}
};

struct ARM_ldm_2: public ARM_ldm {
  ARM_ldm_2(ARM_Condition c, uint8_t a, uint8_t n, uint16_t regs):
    ARM_ldm(c,a,false,n,regs) {}
  void exec(ARM_Processor &proc);

  bool special() const {return true;}
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

struct ARM_ldm_3: public ARM_ldm {
  ARM_ldm_3(ARM_Condition c, uint8_t a, bool w, uint8_t n, uint16_t regs):
    ARM_ldm(c,a,w,n,regs) {}
  void exec(ARM_Processor &proc);

  bool special() const {return true;}
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

struct ARM_stm: public ARM_lsm {
  ARM_stm(ARM_Condition c, uint8_t a, bool w, uint8_t n, uint16_t regs):
    ARM_lsm(c,a,w,n,regs) {}
  const char * opname() const {return "STM";}
  const char * suffix() const;
  virtual void exec(ARM_Processor &proc);
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
  virtual bool may_branch() const {return false;}
};

struct ARM_stm_2: public ARM_stm {
  ARM_stm_2(ARM_Condition c, uint8_t a, uint8_t n, uint16_t regs):
    ARM_stm(c,a,false,n,regs) {}
  void exec(ARM_Processor &proc);

  bool special() const {return true;}
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

/******************************************************************************/

struct ARM_swp: public ARM32_Instruction {
  ARM_Condition cond;
  uint8_t Rd;
  uint8_t Rm;
  uint8_t Rn;
  ARM_swp(ARM_Condition c, uint8_t d, uint8_t m, uint8_t n):
    ARM32_Instruction(), cond(c), Rd(d), Rm(m), Rn(n) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
  bool may_branch() const {return false;}
};

struct ARM_swpb: public ARM32_Instruction {
  ARM_Condition cond;
  uint8_t Rd;
  uint8_t Rm;
  uint8_t Rn;
  ARM_swpb(ARM_Condition c, uint8_t d, uint8_t m, uint8_t n):
    ARM32_Instruction(), cond(c), Rd(d), Rm(m), Rn(n) {}
  void exec(ARM_Processor &proc);
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
  bool may_branch() const {return false;}
};

/******************************************************************************/

struct ARM_pld_imm: public ARM_Nop {
  uint8_t Rn;
  bool u;
  uint16_t immed;
  ARM_pld_imm(uint8_t n, bool u_, uint16_t i):
    ARM_Nop(), Rn(n), u(u_), immed(i) {}
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

struct ARM_pld_reg: public ARM_Nop {
  uint8_t Rn;
  bool u;
  uint8_t Rm;
  ARM_pld_reg(uint8_t n, bool u_, uint8_t m):
    ARM_Nop(), Rn(n), u(u_), Rm(m) {}
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

struct ARM_pld_scrg: public ARM_Nop {
  uint8_t Rn;
  bool u;
  uint8_t shift_imm;
  ARM_Shift shift;
  uint8_t Rm;
  ARM_pld_scrg(uint8_t n, bool u_, uint8_t si, ARM_Shift s, uint8_t m):
    ARM_Nop(), Rn(n), u(u_),
    shift_imm((!si && (s==LSR||s==ASR))? 32: si),
    shift((s==ROR && si==0)? RRX: s),
    Rm(m) {}
  std::ostream& display(std::ostream& os) const;
  virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
};

} // namespace simsoc

#include "armis_loadstore.tpp"

#endif //ARMIS_LOADSTORE_HPP
