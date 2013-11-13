//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARMIS_HPP
#define ARMIS_HPP

#include "arm_shift.hpp"
#include "armis_visitor.hpp"
#include <libsimsoc/processors/common.hpp>

namespace simsoc {

  class ARM_Processor;

  struct ARM_Instruction: Printable {
    bool is_branch_target;

    ARM_Instruction():
      is_branch_target(false) {}

    virtual void exec(ARM_Processor& proc) = 0;
    virtual std::ostream& display(std::ostream& os) const = 0;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
    virtual bool may_raise_something() const;
    virtual bool may_branch() const;
    virtual bool delete_me() const {return true;}
  };

  struct ARM_Undefined: public ARM_Instruction {
    const char * msg;
    ARM_Undefined(const char * message):
      ARM_Instruction(), msg(message) {}
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  struct ARM_Unpredictable: public ARM_Instruction {
    const char * msg;
    ARM_Unpredictable(const char * message):
      ARM_Instruction(), msg(message) {}
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  struct ARM_Nop: public ARM_Instruction {
    ARM_Nop(): ARM_Instruction() {}
    void exec(ARM_Processor &proc);
    std::ostream& display(std::ostream &os) const;

    bool may_raise_something() const;
    bool may_branch() const;
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  class ARM32_Instruction: public ARM_Instruction {
  public:
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  class THUMB_Instruction: public ARM_Instruction {
  public:
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

} // namespace simsoc

#endif //ARMIS_HPP
