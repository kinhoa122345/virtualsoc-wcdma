//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/processors/arm/armis_edsp.hpp"
#include "libsimsoc/processors/arm/arm_cpu.hpp"
#include "libsimsoc/processors/arm/arm_processor.hpp"

#include <limits>
#include <iostream>

using std::ostream;

// --------------------------------------------------------------------
#ifndef INT32_MIN
# define INT32_MIN std::numeric_limits<int32_t>::min()
#endif
#ifndef INT32_MAX
# define INT32_MAX std::numeric_limits<int32_t>::max()
#endif

// --------------------------------------------------------------------
namespace simsoc {

  namespace internal {
    static int32_t saturate_s64_s32(int64_t value, bool &qflag) {
      if (value > INT32_MAX) { qflag = true; return INT32_MAX; }
      if (value < INT32_MIN) { qflag = true; return INT32_MIN; }
      return value;
    }

    static int16_t s16_of_u32(uint32_t value, bool hipart) {
      return hipart
        ? (value >> 16) & 0xFFFF
        : (value >>  0) & 0xFFFF;
    }
  }

  // ------------------------------------------------------------------
  template < class Compute >
  ostream& ARM_EDSP_qarith<Compute>::display(ostream &output) const {
    return output
      << Compute::name() << "["
      << "Rd=" << (ARM_AsmId) Rd << ","
      << "Rm=" << (ARM_AsmId) Rm << ","
      << "Rn=" << (ARM_AsmId) Rn << "]"
      << std::endl;
  }

  template < class Compute >
  void ARM_EDSP_qarith<Compute>::exec(ARM_Processor &proc) {
    proc.cpu.regs[Rd] =
      Compute::compute(proc.cpu.regs[Rm],
                       proc.cpu.regs[Rn],
                       /* out */ proc.cpu.cpsr.q);
    proc.cpu.regs[ARM_CPU::PC] += 4;
  }

  // ------------------------------------------------------------------
  struct ARM_EDSP_qadd_traits {
    static const char* name() { return "QADD"; }

    static int32_t compute(int32_t left, int32_t right, bool &qflag) {
      int64_t result = (int64_t) left + (int64_t) right;
      return internal::saturate_s64_s32(result, qflag);
    }
  };

  struct ARM_EDSP_qdadd_traits {
    static const char* name() { return "QDADD"; }

    static int32_t compute(int32_t left, int32_t right, bool &qflag) {
      return ARM_EDSP_qadd_traits::compute
        (left, ARM_EDSP_qadd_traits::compute(right, right, qflag), qflag);
    }
  };

  struct ARM_EDSP_qsub_traits {
    static const char* name() { return "QSUB"; }

    static int32_t compute(int32_t left, int32_t right, bool &qflag) {
      int64_t result = (int64_t) left - (int64_t) right;
      return internal::saturate_s64_s32(result, qflag);
    }
  };

  struct ARM_EDSP_qdsub_traits {
    static const char* name() { return "QDSUB"; }

    static int32_t compute(int32_t left, int32_t right, bool &qflag) {
      return ARM_EDSP_qsub_traits::compute
        (ARM_EDSP_qadd_traits::compute(left, left, qflag), right, qflag);
    }
  };

  // ------------------------------------------------------------------
  template class ARM_EDSP_qarith< ARM_EDSP_qadd_traits  >;
  template class ARM_EDSP_qarith< ARM_EDSP_qdadd_traits >;
  template class ARM_EDSP_qarith< ARM_EDSP_qsub_traits  >;
  template class ARM_EDSP_qarith< ARM_EDSP_qdsub_traits >;

  // ------------------------------------------------------------------
  ostream& ARM_EDSP_smla::display(ostream &output) const {
    return output
      << "SMLA" << "["
      << "Rd=" << (ARM_AsmId) Rd << ","
      << "Rn=" << (ARM_AsmId) Rn << ","
      << "Rs=" << (ARM_AsmId) Rs << "/" << Rs_hipart << ","
      << "Rm=" << (ARM_AsmId) Rm << "/" << Rm_hipart << "]"
      << std::endl;
  }

  void ARM_EDSP_smla::exec(ARM_Processor &proc) {
    int32_t Rm_part = internal::s16_of_u32(proc.cpu.regs[Rm], Rm_hipart);
    int32_t Rs_part = internal::s16_of_u32(proc.cpu.regs[Rs], Rs_hipart);

    int32_t product = Rm_part * Rs_part;
    proc.cpu.regs[Rd] = product + proc.cpu.regs[Rn];
    ARM_EDSP_qadd_traits::compute(product, proc.cpu.regs[Rn], proc.cpu.cpsr.q);
    proc.cpu.regs[ARM_CPU::PC] += 4;
  }

  // --------------------------------------------------------------------
  ostream& ARM_EDSP_smlal::display(ostream &output) const {
    return output
      << "SMLAL" << "["
      << "Rd=" << (ARM_AsmId) Rd_hi << "/" << (ARM_AsmId) Rd_lo << ","
      << "Rs=" << (ARM_AsmId) Rs << "/" << Rs_hipart << ","
      << "Rm=" << (ARM_AsmId) Rm << "/" << Rm_hipart << "]"
      << std::endl;
  }

  void ARM_EDSP_smlal::exec(ARM_Processor &proc) {
    int64_t Rm_part = internal::s16_of_u32(proc.cpu.regs[Rm], Rm_hipart);
    int64_t Rs_part = internal::s16_of_u32(proc.cpu.regs[Rs], Rs_hipart);

    uint64_t result
      = ((uint64_t) proc.cpu.regs[Rd_hi]) << 32
      | ((uint64_t) proc.cpu.regs[Rd_lo]) <<  0;
    result += Rm_part * Rs_part;

    proc.cpu.regs[Rd_lo] = (result >>  0) & 0xFFFFFFFF;
    proc.cpu.regs[Rd_hi] = (result >> 32) & 0xFFFFFFFF;
    proc.cpu.regs[ARM_CPU::PC] += 4;
  }

  // ------------------------------------------------------------------
  ostream& ARM_EDSP_smlaw::display(ostream &output) const {
    return output
      << "SMLA>" << "["
      << "Rd=" << (ARM_AsmId) Rd << ","
      << "Rn=" << (ARM_AsmId) Rn << ","
      << "Rs=" << (ARM_AsmId) Rs << "/" << Rs_hipart << ","
      << "Rm=" << (ARM_AsmId) Rm << "]"
      << std::endl;
  }

  void ARM_EDSP_smlaw::exec(ARM_Processor &proc) {
    int32_t Rs_part = internal::s16_of_u32(proc.cpu.regs[Rs], Rs_hipart);

    uint64_t product64    = ((int64_t) proc.cpu.regs[Rm]) * ((int64_t) Rs_part);
    uint32_t product32_hi = (product64 >> 16) & 0xFFFFFFFF;

    proc.cpu.regs[Rd] = product32_hi + proc.cpu.regs[Rn];
    ARM_EDSP_qadd_traits::compute(product32_hi, proc.cpu.regs[Rn], proc.cpu.cpsr.q);
    proc.cpu.regs[ARM_CPU::PC] += 4;
  }

  // ------------------------------------------------------------------
  ostream& ARM_EDSP_smul::display(ostream &output) const {
    return output
      << "SMUL" << "["
      << "Rd=" << (ARM_AsmId) Rd << ","
      << "Rs=" << (ARM_AsmId) Rs << "/" << Rs_hipart << ","
      << "Rm=" << (ARM_AsmId) Rm << "/" << Rm_hipart << "]"
      << std::endl;
    }

  void ARM_EDSP_smul::exec(ARM_Processor &proc) {
    int32_t Rm_part = internal::s16_of_u32(proc.cpu.regs[Rm], Rm_hipart);
    int32_t Rs_part = internal::s16_of_u32(proc.cpu.regs[Rs], Rs_hipart);
    proc.cpu.regs[Rd] = Rm_part * Rs_part;
    proc.cpu.regs[ARM_CPU::PC] += 4;
  }

  // ------------------------------------------------------------------
  ostream& ARM_EDSP_smulw::display(ostream &output) const {
    return output
      << "SMULW" << "["
      << "Rd=" << (ARM_AsmId) Rd << ","
      << "Rs=" << (ARM_AsmId) Rs << "/" << Rs_hipart << ","
      << "Rm=" << (ARM_AsmId) Rm << "]"
      << std::endl;
  }

  void ARM_EDSP_smulw::exec(ARM_Processor &proc) {
    int32_t Rs_part = internal::s16_of_u32(proc.cpu.regs[Rs], Rs_hipart);
    uint64_t product64 = ((int64_t) proc.cpu.regs[Rm]) * (int64_t) Rs_part;

    proc.cpu.regs[Rd] = (product64 >> 16) & 0xFFFFFFFF;
    proc.cpu.regs[ARM_CPU::PC] += 4;
  }

}
