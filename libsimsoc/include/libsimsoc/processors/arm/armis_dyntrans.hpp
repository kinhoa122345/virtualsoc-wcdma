//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARMIS_DYNTRANS_HPP
#define ARMIS_DYNTRANS_HPP

#include "armis.hpp"
#include "armpi.hpp"
#include <vector>

namespace simsoc {

  class ARM32_ExecuteBlock: public ARM32_Instruction {
  public:
    ARM32_ExecuteBlock();
    ~ARM32_ExecuteBlock();
    void push_back(ARM_Processor &proc, ARM_Instruction *i, bool &is_generic_pi);
    std::ostream& display(std::ostream& os) const;
    void exec(ARM_Processor& proc);
    size_t size() const {return pis.size();}
  private:
    std::vector<ARM_PseudoInstruction> pis;
    size_t count;
  };

  class ARM32_TranslateBlock: public ARM32_Instruction {
    ARM32_TranslateBlock(): ARM32_Instruction() {}
    static ARM32_TranslateBlock singleton;
  public:
    static ARM32_TranslateBlock *get() {
      return &singleton;
    }
    std::ostream& display(std::ostream& os) const;
    void exec(ARM_Processor& proc);
    bool delete_me() const {return false;}
  };

  /****************************************************************************/

  class THUMB_ExecuteBlock: public THUMB_Instruction {
  public:
    THUMB_ExecuteBlock();
    ~THUMB_ExecuteBlock();
    void push_back(ARM_Processor &proc, ARM_Instruction *i, bool &is_generic_pi);
    std::ostream& display(std::ostream& os) const;
    void exec(ARM_Processor& proc);
    size_t size() const {return pis.size();}
  private:
    std::vector<ARM_PseudoInstruction> pis;
    size_t count;
  };

  class THUMB_TranslateBlock: public THUMB_Instruction {
    THUMB_TranslateBlock(): THUMB_Instruction() {}
    static THUMB_TranslateBlock singleton;
  public:
    static THUMB_TranslateBlock *get() {
      return &singleton;
    }
    std::ostream& display(std::ostream& os) const;
    void exec(ARM_Processor& proc);
    bool delete_me() const {return false;}
  };

} // namespace simsoc

#endif // ARMIS_DYNTRANS_HPP
