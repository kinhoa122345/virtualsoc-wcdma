//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "arm_systemcontrol_coproc.hpp"
#include <cassert>
#include "libsimsoc/processors/arm/arm_mmu.hpp"

using namespace std;
using namespace sc_core;

namespace simsoc {

ARM_SystemControl_Coprocessor::ARM_SystemControl_Coprocessor(sc_module_name name,
                                                             ARM_Processor *proc,
                                                             ARM_MMU *mmu_):
  ARM_Coprocessor(name,proc)
  ,main_id(0x41069265),cache_type(0x1D112152),v6_tlb_type(0x204001)
  ,control(0x00050078)
  ,ttb(0)
  ,domain(0)
  ,fsr(0)
  ,far(0)
  ,pid(0)
  ,mmu(mmu_)
{
  assert(mmu);

}

void ARM_SystemControl_Coprocessor::mcr(uint8_t opcode1, uint8_t opcode2,
                                        uint32_t Rd_value, uint8_t CRn, uint8_t CRm)
{
 switch (CRn) {
  case ID:
    error()<<"write to read only ID register"<<endl;
    break;

  case CONTROL:
    control=Rd_value;
    break;

  case TTB:
    ttb=Rd_value;
    break;

  case CP15_DOMAIN:
    domain=Rd_value;
    break;

  case FSR:
    fsr =Rd_value;
    break;

  case FAR:
    far=Rd_value;
    break;

 case TLBLOCK:
   lock=Rd_value;
   break;

  case TLBFUN:
    tlb_fun(Rd_value,CRm,opcode2);
    break;

  case PID:
    pid=Rd_value;
    break;

 default:
    break;
  }

}

uint32_t ARM_SystemControl_Coprocessor::mrc(uint8_t opcode1, uint8_t opcode2,
                                            uint8_t CRn, uint8_t CRm)
{
  switch (CRn) {
  case ID:
    switch(opcode2)
      {
      case MAIN_ID_OP:
        return main_id;
      case CACHE_TYPE_OP:
        return cache_type;
      default:
        warning()<<"read unimplemented register CRn = "<<CRn<<" opcode2 = "<<opcode2<<endl;
        return 0;
      }

  case CONTROL:
    return control;

  case TTB:
    return ttb;

  case CP15_DOMAIN:
    return domain;

  case FSR:
    return fsr;

  case FAR:
    return far;

  case CACHE_WRITE_CONTROL:
   if(opcode2==3)
     return 0x40000000;
   break;

  case TLBFUN:
    error()<<"read write only tlb option register"<<endl;
    break;

  case PID:
    return pid;
  default:
    return 0;
  }
  return 0;
}

void ARM_SystemControl_Coprocessor::tlb_fun(uint32_t Rd_value,uint8_t CRm,uint8_t opcode2)
{
  ARM_TLB* dTLBs=static_cast<ARM_TLB*>(mmu->dTLBs);
  ARM_TLB* iTLBs=static_cast<ARM_TLB*>(mmu->iTLBs);
  bool isUnified =mmu->isUnified;

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
      static_cast<ARM_TLB*>(dTLBs)->invalidate_single_entry(Rd_value);
      if (!isUnified) {
        static_cast<ARM_TLB*>(iTLBs)->invalidate_single_entry(Rd_value);
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
      static_cast<ARM_TLB*>(iTLBs)->invalidate_single_entry(Rd_value);
      return;
    }
    return;
  case TLBFUN_CRM_DTLB:
    switch (opcode2) {
    case TLBFUN_OP2_ENTIRE:
      dTLBs->invalidate_all_entries();
      return;
    case TLBFUN_OP2_SINGLE:
      static_cast<ARM_TLB*>(dTLBs)->invalidate_single_entry(Rd_value);
      return;
    }
    return;
  }
}

} // namespace simsoc
