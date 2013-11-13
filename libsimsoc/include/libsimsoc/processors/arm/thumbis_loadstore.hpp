//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef THUMBIS_LOADSTORE_HPP
#define THUMBIS_LOADSTORE_HPP

#include "armis.hpp"

namespace simsoc {

  struct THUMB_ldr1: public THUMB_Instruction {
    uint8_t immed;
    uint8_t Rn;
    uint8_t Rd;
    THUMB_ldr1(uint8_t i, uint8_t n, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_ldr2: public THUMB_Instruction {
    uint8_t Rm;
    uint8_t Rn;
    uint8_t Rd;
    THUMB_ldr2(uint8_t m, uint8_t n, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_ldr3: public THUMB_Instruction {
    uint8_t Rd;
    uint8_t immed;
    THUMB_ldr3(uint8_t d, uint8_t i);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_ldr4: public THUMB_Instruction {
    uint8_t Rd;
    uint8_t immed;
    THUMB_ldr4(uint8_t d, uint8_t i);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_ldrb1: public THUMB_Instruction {
    uint8_t immed;
    uint8_t Rn;
    uint8_t Rd;
    THUMB_ldrb1(uint8_t i, uint8_t n, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_ldrb2: public THUMB_Instruction {
    uint8_t Rm;
    uint8_t Rn;
    uint8_t Rd;
    THUMB_ldrb2(uint8_t m, uint8_t n, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_ldrh1: public THUMB_Instruction {
    uint8_t immed;
    uint8_t Rn;
    uint8_t Rd;
    THUMB_ldrh1(uint8_t i, uint8_t n, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_ldrh2: public THUMB_Instruction {
    uint8_t Rm;
    uint8_t Rn;
    uint8_t Rd;
    THUMB_ldrh2(uint8_t m, uint8_t n, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_ldrsb: public THUMB_Instruction {
    uint8_t Rm;
    uint8_t Rn;
    uint8_t Rd;
    THUMB_ldrsb(uint8_t m, uint8_t n, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_ldrsh: public THUMB_Instruction {
    uint8_t Rm;
    uint8_t Rn;
    uint8_t Rd;
    THUMB_ldrsh(uint8_t m, uint8_t n, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_str1: public THUMB_Instruction {
    uint8_t immed;
    uint8_t Rn;
    uint8_t Rd;
    THUMB_str1(uint8_t i, uint8_t n, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_str2: public THUMB_Instruction {
    uint8_t Rm;
    uint8_t Rn;
    uint8_t Rd;
    THUMB_str2(uint8_t m, uint8_t n, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_str3: public THUMB_Instruction {
    uint8_t Rd;
    uint8_t immed;
    THUMB_str3(uint8_t d, uint8_t i);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_strb1: public THUMB_Instruction {
    uint8_t immed;
    uint8_t Rn;
    uint8_t Rd;
    THUMB_strb1(uint8_t i, uint8_t n, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_strb2: public THUMB_Instruction {
    uint8_t Rm;
    uint8_t Rn;
    uint8_t Rd;
    THUMB_strb2(uint8_t m, uint8_t n, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_strh1: public THUMB_Instruction {
    uint8_t immed;
    uint8_t Rn;
    uint8_t Rd;
    THUMB_strh1(uint8_t i, uint8_t n, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_strh2: public THUMB_Instruction {
    uint8_t Rm;
    uint8_t Rn;
    uint8_t Rd;
    THUMB_strh2(uint8_t m, uint8_t n, uint8_t d);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_ldmia: public THUMB_Instruction {
    uint8_t Rn;
    uint8_t registers;
    uint8_t nb_reg;
    THUMB_ldmia(uint8_t n, uint8_t regs);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_stmia: public THUMB_Instruction {
    uint8_t Rn;
    uint8_t registers;
    uint8_t nb_reg;
    THUMB_stmia(uint8_t n, uint8_t regs);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

  struct THUMB_pop: public THUMB_Instruction {
    bool R;
    uint8_t registers;
    uint8_t nb_reg;
    THUMB_pop(bool r, uint8_t regs);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return R;};
  };

  struct THUMB_push: public THUMB_Instruction {
    bool R;
    uint8_t registers;
    uint8_t nb_reg;
    THUMB_push(bool r, uint8_t regs);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;};
  };

} // namespace simsoc

#endif //THUMBIS_LOADSTORE_HPP
