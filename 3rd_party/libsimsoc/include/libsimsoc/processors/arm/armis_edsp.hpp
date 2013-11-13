//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined(ARMIS_EDSP_HPP)
# define ARMIS_EDSP_HPP

# include "libsimsoc/processors/arm/armis.hpp"
# include <iostream>

namespace simsoc {
  class ARM_Processor;

  // ------------------------------------------------------------------
  template < class Compute >
  class ARM_EDSP_qarith: public ARM32_Instruction {
  public:
    ARM_EDSP_qarith(uint8_t a_Rd, uint8_t a_Rm, uint8_t a_Rn)
      :Rd(a_Rd), Rm(a_Rm), Rn(a_Rn)
    {}

    virtual std::ostream& display(std::ostream &output) const;
    virtual void exec(ARM_Processor &proc);
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

    const uint8_t Rd;
    const uint8_t Rm;
    const uint8_t Rn;
  };

  // ------------------------------------------------------------------
  struct ARM_EDSP_qadd_traits ;
  struct ARM_EDSP_qdadd_traits;
  struct ARM_EDSP_qsub_traits ;
  struct ARM_EDSP_qdsub_traits;

  typedef ARM_EDSP_qarith< ARM_EDSP_qadd_traits  > ARM_EDSP_qadd ;
  typedef ARM_EDSP_qarith< ARM_EDSP_qdadd_traits > ARM_EDSP_qdadd;
  typedef ARM_EDSP_qarith< ARM_EDSP_qsub_traits  > ARM_EDSP_qsub ;
  typedef ARM_EDSP_qarith< ARM_EDSP_qdsub_traits > ARM_EDSP_qdsub;

  // ------------------------------------------------------------------
  class ARM_EDSP_smla: public ARM32_Instruction {
  public:
    ARM_EDSP_smla(uint8_t a_Rd, uint8_t a_Rn,
                  uint8_t a_Rs, bool a_Rs_hipart,
                  uint8_t a_Rm, bool a_Rm_hipart)
      :Rd(a_Rd), Rn(a_Rn), Rs(a_Rs), Rm(a_Rm)
      ,Rs_hipart(a_Rs_hipart)
      ,Rm_hipart(a_Rm_hipart)
    {}

    virtual std::ostream& display(std::ostream &output) const;
    virtual void exec(ARM_Processor &proc);
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

    const uint8_t Rd;
    const uint8_t Rn;
    const uint8_t Rs;
    const uint8_t Rm;
    const bool    Rs_hipart;
    const bool    Rm_hipart;
  };

  // ------------------------------------------------------------------
  class ARM_EDSP_smlal: public ARM32_Instruction {
  public:
    ARM_EDSP_smlal(uint8_t a_Rd_hi, uint8_t a_Rd_lo,
                   uint8_t a_Rs, bool a_Rs_hipart,
                   uint8_t a_Rm, bool a_Rm_hipart)
      :Rd_hi(a_Rd_hi), Rd_lo(a_Rd_lo)
      ,Rs(a_Rs), Rm(a_Rm)
      ,Rs_hipart(a_Rs_hipart)
      ,Rm_hipart(a_Rm_hipart)
    {}

    virtual std::ostream& display(std::ostream &output) const;
    virtual void exec(ARM_Processor &proc);
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

    const uint8_t Rd_hi;
    const uint8_t Rd_lo;
    const uint8_t Rs;
    const uint8_t Rm;
    const bool    Rs_hipart;
    const bool    Rm_hipart;

  };

  // ------------------------------------------------------------------
  class ARM_EDSP_smlaw: public ARM32_Instruction {
  public:
    ARM_EDSP_smlaw(uint8_t a_Rd, uint8_t a_Rn,
                   uint8_t a_Rs, bool a_Rs_hipart,
                   uint8_t a_Rm)
      :Rd(a_Rd), Rn(a_Rn), Rs(a_Rs), Rm(a_Rm)
      ,Rs_hipart(a_Rs_hipart)
    {}

    virtual std::ostream& display(std::ostream &output) const;
    virtual void exec(ARM_Processor &proc);
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

    const uint8_t Rd;
    const uint8_t Rn;
    const uint8_t Rs;
    const uint8_t Rm;
    const bool    Rs_hipart;
  };

  // ------------------------------------------------------------------
  class ARM_EDSP_smul: public ARM32_Instruction {
  public:
    ARM_EDSP_smul(uint8_t a_Rd,
                  uint8_t a_Rs, bool a_Rs_hipart,
                  uint8_t a_Rm, bool a_Rm_hipart)
      :Rd(a_Rd), Rs(a_Rs), Rm(a_Rm)
      ,Rs_hipart(a_Rs_hipart)
      ,Rm_hipart(a_Rm_hipart)
    {}

    virtual std::ostream& display(std::ostream &output) const;
    virtual void exec(ARM_Processor &proc);
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

    const uint8_t Rd;
    const uint8_t Rs;
    const uint8_t Rm;
    const bool    Rs_hipart;
    const bool    Rm_hipart;
  };

  // ------------------------------------------------------------------
  class ARM_EDSP_smulw: public ARM32_Instruction {
  public:
    ARM_EDSP_smulw(uint8_t a_Rd,
                   uint8_t a_Rs, bool a_Rs_hipart,
                   uint8_t a_Rm)
      :Rd(a_Rd), Rs(a_Rs), Rm(a_Rm)
      ,Rs_hipart(a_Rs_hipart)
    {}

    virtual std::ostream& display(std::ostream &output) const;
    virtual void exec(ARM_Processor &proc);
    virtual void accept(ARM_InstructionVisitor &visitor) {visitor.visit(*this);}

    const uint8_t Rd;
    const uint8_t Rs;
    const uint8_t Rm;
    const bool    Rs_hipart;
  };

}

#endif // !ARMIS_EDSP_HPP
