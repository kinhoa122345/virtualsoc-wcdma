//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef THUMBIS_CONTROL_HPP
#define THUMBIS_CONTROL_HPP

#include "armis.hpp"
#include "arm_condition.hpp"

namespace simsoc {

  struct THUMB_b: public THUMB_Instruction {
    ARM_Condition cond;
    int32_t offset;
    THUMB_b(ARM_Condition c, int32_t o);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  struct THUMB_bl_blx1: public THUMB_Instruction {
    bool exchange;
    int32_t offset;
    THUMB_bl_blx1(bool x, int32_t o);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  struct THUMB_bx_blx2: public THUMB_Instruction {
    bool set_lr;
    uint8_t Rm;
    THUMB_bx_blx2(bool l, uint8_t m);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  struct THUMB_swi: public THUMB_Instruction {
    uint32_t immed;
    THUMB_swi(uint8_t i);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  struct THUMB_bkpt: public THUMB_Instruction {
    uint32_t immed;
    THUMB_bkpt(uint8_t i);
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

} // namespace simsoc

#endif //THUMBIS_CONTROL_HPP
