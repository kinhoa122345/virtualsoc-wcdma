//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "arm_mmu.hpp"
#include "libsimsoc/display.hpp"
#include "libsimsoc/processors/arm/arm_processor.hpp"
#include "libsimsoc/processors/arm/arm_systemcontrol_coproc.hpp"

using namespace sc_core;
using namespace std;

namespace simsoc {

const char* get_v5_fault_msg(uint32_t fault)
{
  switch(fault)
    {
    case ALIGNMENT_FAULT:
      return "alignment fault";
    case SECTION_TRANSLATION_FAULT:
      return "section translation fault";
    case PAGE_TRANSLATION_FAULT:
      return "page translation fault";
    case SECTION_DOMAIN_FAULT:
      return "section domain fault";
    case PAGE_DOMAIN_FAULT:
      return "page domain fault";
    case SECTION_PERMISSION_FAULT:
      return "section permission fault";
    case SUBPAGE_PERMISSION_FAULT:
      return "subpage permission fault";
    default:
      return "unhandled fault";
    }
}


ARM_MMU::ARM_MMU(sc_core::sc_module_name name, ARM_Processor *proc_):
  MMU<BUS32>(name,proc_,0,0),
  cp15(proc_->cp15),
  saved_entry(NULL)
{
  assert(proc);
  isUnified = getTLBs();
}

ARM_MMU::~ARM_MMU() {}

bool ARM_MMU::getTLBs()
{
#ifdef USE_TLBCache
  static const uint64_t VIRT_MEMORY_SIZE= 0x100000000ULL;
  static const uint32_t VIRT_PAGE_SIZE= 0x1000;
  TLB_Cache* main_tlb=new TLB<BUS32>("tlb_cache",VIRT_MEMORY_SIZE/VIRT_PAGE_SIZE);
#else
  ARM_TLB* lockdown_tlb=new ARM_TLB("lock down tlb",8,true);
  ARM_TLB* main_tlb=new ARM_TLB("main tlb",64);
  lockdown_tlb->next=main_tlb;
#endif
  dTLBs=iTLBs=main_tlb;
  return true;
};

void ARM_MMU::check_access(uint32_t va, TLBEntry<word_t> *tlbEntry, mem_op_type op_type)
{
  typedef enum {
    NO_ACCESS=0,
    CLIENT=1,
    RESERVED=2,
    MANAGER=3
  } access_type;

  assert(tlbEntry!=NULL);
  ARM_TLBEntry *tlb_entry = static_cast<ARM_TLBEntry*>(tlbEntry);
  const uint32_t domain = tlb_entry->domain;
  switch (cp15.get_domain(domain)) {
  case CLIENT: //client access-check permissions
    if (!check_perms(tlb_entry->getAP(va),op_type)) {
      if (tlb_entry->mapping_type==TLB_SECTION )
        throw MMU_Faults<BUS32>(va,SECTION_PERMISSION_FAULT,domain);
      else
        throw MMU_Faults<BUS32>(va,SUBPAGE_PERMISSION_FAULT,domain);
    } else
      return;
  case NO_ACCESS:
    if (tlb_entry->mapping_type==TLB_SECTION)
      throw MMU_Faults<BUS32>(va,SECTION_DOMAIN_FAULT,domain);
    else
      throw MMU_Faults<BUS32>(va,PAGE_DOMAIN_FAULT,domain);
  case MANAGER: //manager access-don't check permissions
    return;
  case RESERVED:
  default:
    throw MMU_Faults<BUS32>(va,SECTION_DOMAIN_FAULT,domain);
  }
};

int ARM_MMU::check_perms(int ap, int write) {
  const int s = cp15.get_S();
  const int r = cp15.get_R();
  const int user = (int)user_mode;
  switch (ap) {
  case 0:
    return !write && ((s && !user) || r);
  case 1:
    return !user;
  case 2:
    return !write || !user;
  case 3:
    return 1;
  }
  return 0;
}

void ARM_MMU::check_alignment(uint32_t va, mmu_data_type data_type)
{
  if((cp15.check_align() && (data_type==MMU_WORD_TYPE) && (va&3))
     || (cp15.check_align() && (data_type==MMU_HALF_TYPE) &&(va&1)))
    {
      throw MMU_Faults<BUS32>(va,ALIGNMENT_FAULT);
    }
  return;
};


  TLBEntry<ARM_MMU::word_t> *ARM_MMU::translation_table_walk(uint32_t virt_addr,
                                                             mmu_data_type data_type)
{
  const uint32_t l1table_addr = (cp15.get_ttb()| bits<uint32_t>(virt_addr,31,18)) & ~3;
  const uint32_t descriptor = memory_read_word(l1table_addr);

  uint32_t l2table_addr;
  uint32_t l2table_desc;

  switch (bits<uint32_t>(descriptor, 1, 0)) {
  case 0: //fault
    throw MMU_Faults<BUS32>(virt_addr,SECTION_TRANSLATION_FAULT);
  case 1:
    {
      CoarsePage coarsePage(virt_addr,descriptor);
      l2table_addr=coarsePage.get_page_table_addr();
      l2table_desc=memory_read_word(l2table_addr);
      return coarsePage.parse_page_entry(l2table_desc);
    }
  case 2:
    return new Section(virt_addr,descriptor);
  case 3:
    {
      FinePage finePage(virt_addr,descriptor);
      l2table_addr=finePage.get_page_table_addr();
      l2table_desc=memory_read_word(l2table_addr);
      return finePage.parse_page_entry(l2table_desc);
    }
  default:
    assert(false);
    return NULL;
  }
}

  void ARM_MMU::handle_data_faults(uint32_t virt_addr, uint32_t fault,
                                   uint32_t domain, mem_op_type op_type)
  {
    info()<<"MMU data exception at address "<<hex<<virt_addr
          <<" for "<<get_v5_fault_msg(fault)<<endl;
    cp15.set_fsr(fault,domain);
    cp15.set_far(virt_addr);
    static_cast<ARM_Processor*>(proc)->data_abort();
  }

  void ARM_MMU::handle_instruction_faults(uint32_t virt_addr, uint32_t fault,
                                          uint32_t domain, mem_op_type op_type) {
    info()<<"MMU instruction prefetch exception at address "
          <<hex<<virt_addr<<" for "<<get_v5_fault_msg(fault)<<endl;
    cp15.set_fsr(fault,domain);
    cp15.set_far(virt_addr);
    static_cast<ARM_Processor*>(proc)->prefetch_abort();
  }

  uint32_t ARM_MMU::virt_to_phy(uint32_t va,
                                mmu_data_type data_type/*used to check alignment*/,
                                mem_op_type op_type/*used to check permission*/,
                                TLB<word_t> *tlbs){
    uint32_t pa = 0;
    //va = fast_context_switch(va);
    check_alignment(va,data_type);
    ARM_TLBEntry *entry;
    if (saved_entry && (*saved_entry) &&
        ( (va & ~((*saved_entry)->mask))==(*saved_entry)->virt_addr)) {
      entry = static_cast<ARM_TLBEntry*>(*saved_entry);
      pa = entry->getPA(va);
    } else {
      TLBEntry<word_t> **entry_ptr = tlbs->search_entry(va);
      entry = static_cast<ARM_TLBEntry*>(entry_ptr? *entry_ptr: NULL);
      if (entry) {
        pa = entry->getPA(va);
        //debug()<<"Find in TLb! get physical addr["<<pa<<"]"<<endl;
      } else {
        //debug()<<"TLB miss! translation table walk!"<<endl;
        entry = static_cast<ARM_TLBEntry*>(translation_table_walk(va,data_type));
        static_cast<ARM_TLB*>(tlbs)->add_entry(entry,va);
        pa = entry->getPA(va);
      }
      saved_entry = static_cast<ARM_TLB*>(tlbs)->get_entry(tlbs->curpos);
    }
    check_access(va,entry,op_type);
    return pa;
  }

} // namespace simsoc
