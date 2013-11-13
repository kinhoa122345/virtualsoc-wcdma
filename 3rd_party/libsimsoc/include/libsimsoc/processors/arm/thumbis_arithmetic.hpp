//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef THUMBIS_ARITHMETIC_HPP
#define THUMBIS_ARITHMETIC_HPP

#include "armis.hpp"

namespace simsoc {

  struct THUMB_adc: public THUMB_Instruction {
    uint8_t Rd;
    uint8_t Rm;
    THUMB_adc(uint8_t d, uint8_t m);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_mov2: public THUMB_Instruction {
    uint8_t Rd;
    uint8_t Rn;
    THUMB_mov2(uint8_t d,uint8_t n);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_add1: public THUMB_Instruction {
    uint8_t immed;
    uint8_t Rd;
    uint8_t Rn;
    THUMB_add1(uint8_t i,uint8_t d,uint8_t n);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_add2: public THUMB_Instruction {
    uint8_t immed;
    uint8_t Rd;
    THUMB_add2(uint8_t i,uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_add3: public THUMB_Instruction {
    uint8_t Rm;
    uint8_t Rd;
    uint8_t Rn;
    THUMB_add3(uint8_t m,uint8_t d,uint8_t n);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_add4: public THUMB_Instruction {
    uint8_t Rd;
    uint8_t Rm;
    THUMB_add4(uint8_t d, uint8_t m);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return Rd==15;};
  };

  struct THUMB_add5: public THUMB_Instruction {
    uint8_t immed;
    uint8_t Rd;
    THUMB_add5(uint8_t i,uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_add6: public THUMB_Instruction {
    uint8_t immed;
    uint8_t Rd;
    THUMB_add6(uint8_t i,uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_add7: public THUMB_Instruction {
    uint8_t immed;
    THUMB_add7(uint8_t i);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_and: public THUMB_Instruction {
    uint8_t Rd;
    uint8_t Rm;
    THUMB_and(uint8_t d,uint8_t m);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_asr1: public THUMB_Instruction {
    uint8_t immed;
    uint8_t Rd;
    uint8_t Rm;
    THUMB_asr1(uint8_t d, uint8_t i, uint8_t m);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_asr2: public THUMB_Instruction {
    uint8_t Rs;
    uint8_t Rd;
    THUMB_asr2(uint8_t s, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_bic: public THUMB_Instruction {
    uint8_t Rm;
    uint8_t Rd;
    THUMB_bic(uint8_t m, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_cmn: public THUMB_Instruction {
    uint8_t Rm;
    uint8_t Rn;
    THUMB_cmn(uint8_t m, uint8_t n);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_cmp1: public THUMB_Instruction {
    uint8_t immed;
    uint8_t Rn;
    THUMB_cmp1(uint8_t i, uint8_t n);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_cmp2: public THUMB_Instruction {
    uint8_t Rm;
    uint8_t Rn;
    THUMB_cmp2(uint8_t m, uint8_t n);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_cmp3: public THUMB_Instruction {
    uint8_t Rm;
    uint8_t Rn;
    THUMB_cmp3(uint8_t m, uint8_t n);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_eor: public THUMB_Instruction {
    uint8_t Rm;
    uint8_t Rd;
    THUMB_eor(uint8_t m, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_lsl1: public THUMB_Instruction {
    uint8_t immed;
    uint8_t Rm;
    uint8_t Rd;
    THUMB_lsl1(uint8_t i, uint8_t m, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_lsl2: public THUMB_Instruction {
    uint8_t Rs;
    uint8_t Rd;
    THUMB_lsl2(uint8_t d, uint8_t s);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_lsr1: public THUMB_Instruction {
    uint8_t immed;
    uint8_t Rm;
    uint8_t Rd;
    THUMB_lsr1(uint8_t i, uint8_t m, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_lsr2: public THUMB_Instruction {
    uint8_t Rs;
    uint8_t Rd;
    THUMB_lsr2(uint8_t s, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_mov1: public THUMB_Instruction {
    uint8_t Rd;
    uint8_t immed;
    THUMB_mov1(uint8_t d, uint8_t i);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_mov3: public THUMB_Instruction {
    uint8_t Rm;
    uint8_t Rd;
    THUMB_mov3(uint8_t m, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return Rd==15;};
  };

  struct THUMB_mul: public THUMB_Instruction {
    uint8_t Rm;
    uint8_t Rd;
    THUMB_mul(uint8_t m, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_mvn: public THUMB_Instruction {
    uint8_t Rm;
    uint8_t Rd;
    THUMB_mvn(uint8_t m, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_neg: public THUMB_Instruction {
    uint8_t Rm;
    uint8_t Rd;
    THUMB_neg(uint8_t m, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_orr: public THUMB_Instruction {
    uint8_t Rm;
    uint8_t Rd;
    THUMB_orr(uint8_t m, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_sbc: public THUMB_Instruction {
    uint8_t Rm;
    uint8_t Rd;
    THUMB_sbc(uint8_t m, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_ror: public THUMB_Instruction {
    uint8_t Rs;
    uint8_t Rd;
    THUMB_ror(uint8_t s, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_sub1: public THUMB_Instruction {
    uint8_t immed;
    uint8_t Rd;
    uint8_t Rn;
    THUMB_sub1(uint8_t i,uint8_t d,uint8_t n);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_sub2: public THUMB_Instruction {
    uint8_t immed;
    uint8_t Rd;
    THUMB_sub2(uint8_t i, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_sub3: public THUMB_Instruction {
    uint8_t Rm;
    uint8_t Rd;
    uint8_t Rn;
    THUMB_sub3(uint8_t m, uint8_t d, uint8_t n);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_sub4: public THUMB_Instruction {
    uint8_t immed;
    THUMB_sub4(uint8_t i);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_tst: public THUMB_Instruction {
    uint8_t Rm;
    uint8_t Rn;
    THUMB_tst(uint8_t m, uint8_t n);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

} // namespace simsoc

#endif  //THUMBIS_ARITHMETIC_HPP
