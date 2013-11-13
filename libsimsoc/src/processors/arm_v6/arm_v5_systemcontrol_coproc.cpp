//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// FIXME: this file describes the cp15 of the ARM architecture version 5
// it should be replaced by a description of the cp15 corresponding to version 6

#include "arm_v5_systemcontrol_coproc.hpp"
#include "arm_v5_mmu.hpp"
#include <cassert>

using namespace std;
using namespace sc_core;

namespace simsoc {

  ARMv6_SystemCoproc::ARMv6_SystemCoproc(sc_module_name name,
                                         ARMv6_Processor *proc,
                                         ARMv6_MMU *mmu_):
    ARMv6_Coprocessor(name,proc),
    main_id(0x41069265), cache_type(0x1D112152), v6_tlb_type(0x204001),
    control(0x00050078),
    ttb(0), domain(0), fsr(0), far(0), pid(0),
    mmu(mmu_)
  {
    assert(mmu);
  }

  bool ARMv6_SystemCoproc::mcr(uint8_t opcode1, uint8_t opcode2,
                               uint32_t Rd_value, uint8_t CRn, uint8_t CRm)
  {
    switch (CRn) {
    case ID:
      warning() <<"write to read only ID register"<<endl;
      break;
    case CONTROL: control = Rd_value; break;
    case TTB: ttb = Rd_value; break;
    case CP15_DOMAIN: domain = Rd_value; break;
    case FSR: fsr = Rd_value; break;
    case FAR: far = Rd_value; break;
    case TLBLOCK: lock = Rd_value; break;
    case TLBFUN: tlb_fun(Rd_value,CRm,opcode2); break;
    case PID: pid = Rd_value; break;
    default: break;
    }
    return true;
  }

  bool ARMv6_SystemCoproc::mrc(uint32_t &result,
                               uint8_t opcode1, uint8_t opcode2,
                               uint8_t CRn, uint8_t CRm)
  {
    switch (CRn) {
    case ID:
      switch(opcode2) {
      case MAIN_ID_OP: result = main_id; break;
      case CACHE_TYPE_OP: result = cache_type; break;
      default:
        warning() <<"read unimplemented register CRn = " <<CRn
                  <<" opcode2 = " <<opcode2 <<endl;
        result = 0;
        break;
      }
      break;
    case CONTROL: result = control; break;
    case TTB: result = ttb; break;
    case CP15_DOMAIN: result = domain; break;
    case FSR: result = fsr; break;
    case FAR: result = far; break;
    case CACHE_WRITE_CONTROL:
      if (opcode2==3) result = 0x40000000;
      else result = 0;
      break;
    case TLBFUN:
      warning() <<"read write only tlb option register" <<endl;
      break;
    case PID: result = pid; break;
    default: result = 0; break;
    }
    return true;
  }

  void ARMv6_SystemCoproc::tlb_fun(uint32_t Rd_value, uint8_t CRm,
                                   uint8_t opcode2)
  {
    ARMv6_TLB* dTLBs = static_cast<ARMv6_TLB*>(mmu->dTLBs);
    ARMv6_TLB* iTLBs = static_cast<ARMv6_TLB*>(mmu->iTLBs);
    bool isUnified = mmu->isUnified;

    switch (CRm) {
    case TLBFUN_CRM_UNIFIED:
      switch (opcode2) {
      case TLBFUN_OP2_ENTIRE:
        dTLBs->invalidate_all_entries();
        if (!isUnified) {
          iTLBs->invalidate_all_entries();
        }
        return;
      case TLBFUN_OP2_SINGLE:
        static_cast<ARMv6_TLB*>(dTLBs)->invalidate_single_entry(Rd_value);
        if (!isUnified) {
          static_cast<ARMv6_TLB*>(iTLBs)->invalidate_single_entry(Rd_value);
        }
        return;
      }
      return;
    case TLBFUN_CRM_ITLB:
      switch (opcode2) {
      case TLBFUN_OP2_ENTIRE:
        iTLBs->invalidate_all_entries();
        return;
      case TLBFUN_OP2_SINGLE:
        static_cast<ARMv6_TLB*>(iTLBs)->invalidate_single_entry(Rd_value);
        return;
      }
      return;
    case TLBFUN_CRM_DTLB:
      switch (opcode2) {
      case TLBFUN_OP2_ENTIRE:
        dTLBs->invalidate_all_entries();
        return;
      case TLBFUN_OP2_SINGLE:
        static_cast<ARMv6_TLB*>(dTLBs)->invalidate_single_entry(Rd_value);
        return;
      }
      return;
    }
  }

} // namespace simsoc
