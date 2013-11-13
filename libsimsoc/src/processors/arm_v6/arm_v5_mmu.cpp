//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// FIXME: this file describes the MMU of the ARM architecture version 5
// it should be replaced by a description of the MMU corresponding to version 6

#include "libsimsoc/display.hpp"

#include "libsimsoc/processors/arm_v6/arm_v5_mmu.hpp"
#include "libsimsoc/processors/arm_v6/arm_v6_processor.hpp"
#include "libsimsoc/processors/arm_v6/arm_v5_systemcontrol_coproc.hpp"

using namespace sc_core;
using namespace std;

namespace simsoc {

  static const char* get_v5_fault_msg(uint32_t fault) {
    switch(fault) {
    case ARMv6_ALIGNMENT_FAULT:
      return "alignment fault";
    case ARMv6_SECTION_TRANSLATION_FAULT:
      return "section translation fault";
    case ARMv6_PAGE_TRANSLATION_FAULT:
      return "page translation fault";
    case ARMv6_SECTION_DOMAIN_FAULT:
      return "section domain fault";
    case ARMv6_PAGE_DOMAIN_FAULT:
      return "page domain fault";
    case ARMv6_SECTION_PERMISSION_FAULT:
      return "section permission fault";
    case ARMv6_SUBPAGE_PERMISSION_FAULT:
      return "subpage permission fault";
    default:
      return "unhandled fault";
    }
  }

  ARMv6_MMU::ARMv6_MMU(sc_core::sc_module_name name, ARMv6_Processor *proc_,int ID, int TILE_ID):
    MMU<BUS32>(name,proc_,ID,TILE_ID),
    cp15(proc_->cp15),
    saved_entry(NULL)
  {
    assert(proc);
    isUnified = getTLBs();
  }

  ARMv6_MMU::~ARMv6_MMU() {}

  bool ARMv6_MMU::getTLBs()
  {
#ifdef USE_TLBCache
    static const uint64_t VIRT_MEMORY_SIZE= 0x100000000ULL;
    static const uint32_t VIRT_PAGE_SIZE= 0x1000;
    TLB_Cache* main_tlb=new TLB<BUS32>("tlb_cache",VIRT_MEMORY_SIZE/VIRT_PAGE_SIZE);
#else
    ARMv6_TLB* lockdown_tlb = new ARMv6_TLB("lock down tlb",8,true);
    ARMv6_TLB* main_tlb = new ARMv6_TLB("main tlb",64);
    lockdown_tlb->next=main_tlb;
#endif
    dTLBs=iTLBs=main_tlb;
    return true;
  }

  void ARMv6_MMU::check_access(uint32_t va, TLBEntry<uint32_t> *tlbEntry,
                               mem_op_type op_type)
  {
    typedef enum {
      NO_ACCESS=0,
      CLIENT=1,
      RESERVED=2,
      MANAGER=3
    } access_type;

    assert(tlbEntry!=NULL);
    ARMv6_TLBEntry *tlb_entry = static_cast<ARMv6_TLBEntry*>(tlbEntry);
    const uint32_t domain = tlb_entry->domain;
    switch (cp15.get_domain(domain)) {
    case CLIENT: //client access-check permissions
      if (!check_perms(tlb_entry->getAP(va),op_type)) {
        if (tlb_entry->mapping_type==ARMv6_TLB_SECTION )
          throw MMU_Faults<BUS32>(va,ARMv6_SECTION_PERMISSION_FAULT,domain);
        else
          throw MMU_Faults<BUS32>(va,ARMv6_SUBPAGE_PERMISSION_FAULT,domain);
      } else
        return;
    case NO_ACCESS:
      if (tlb_entry->mapping_type==ARMv6_TLB_SECTION)
        throw MMU_Faults<BUS32>(va,ARMv6_SECTION_DOMAIN_FAULT,domain);
      else
        throw MMU_Faults<BUS32>(va,ARMv6_PAGE_DOMAIN_FAULT,domain);
    case MANAGER: //manager access-don't check permissions
      return;
    case RESERVED:
    default:
      throw MMU_Faults<BUS32>(va,ARMv6_SECTION_DOMAIN_FAULT,domain);
    }
  };

  int ARMv6_MMU::check_perms(int ap, int write) {
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

  void ARMv6_MMU::check_alignment(uint32_t va, mmu_data_type data_type)
  {
    if((cp15.check_align() && (data_type==MMU_WORD_TYPE) && (va&3))
       || (cp15.check_align() && (data_type==MMU_HALF_TYPE) &&(va&1)))
      {
        throw MMU_Faults<BUS32>(va,ARMv6_ALIGNMENT_FAULT);
      }
    return;
  };


  TLBEntry<uint32_t> *ARMv6_MMU::translation_table_walk(uint32_t virt_addr,
                                                        mmu_data_type data_type)
  {
    const uint32_t l1table_addr = (cp15.get_ttb()| bits<uint32_t>(virt_addr,31,18)) & ~3;
    const uint32_t descriptor = memory_read_word(l1table_addr);

    uint32_t l2table_addr;
    uint32_t l2table_desc;

    switch (bits<uint32_t>(descriptor, 1, 0)) {
    case 0: //fault
      throw MMU_Faults<BUS32>(virt_addr,ARMv6_SECTION_TRANSLATION_FAULT);
    case 1:
      {
        ARMv6_CoarsePage coarsePage(virt_addr,descriptor);
        l2table_addr=coarsePage.get_page_table_addr();
        l2table_desc=memory_read_word(l2table_addr);
        return coarsePage.parse_page_entry(l2table_desc);
      }
    case 2:
      return new ARMv6_Section(virt_addr,descriptor);
    case 3:
      {
        ARMv6_FinePage finePage(virt_addr,descriptor);
        l2table_addr=finePage.get_page_table_addr();
        l2table_desc=memory_read_word(l2table_addr);
        return finePage.parse_page_entry(l2table_desc);
      }
    default:
      assert(false);
      return NULL;
    }
  }

  void ARMv6_MMU::handle_data_faults(uint32_t virt_addr, uint32_t fault,
                                     uint32_t domain, mem_op_type op_type)
  {
    info()<<"MMU data exception at address "<<hex<<virt_addr
          <<" for "<<get_v5_fault_msg(fault)<<endl;
    cp15.set_fsr(fault,domain);
    cp15.set_far(virt_addr);
    static_cast<ARMv6_Processor*>(proc)->data_abort();
  }

  void ARMv6_MMU::handle_instruction_faults(uint32_t virt_addr, uint32_t fault,
                                          uint32_t domain, mem_op_type op_type) {
    info()<<"MMU instruction prefetch exception at address "
          <<hex<<virt_addr<<" for "<<get_v5_fault_msg(fault)<<endl;
    cp15.set_fsr(fault,domain);
    cp15.set_far(virt_addr);
    static_cast<ARMv6_Processor*>(proc)->prefetch_abort();
  }

  uint32_t ARMv6_MMU::virt_to_phy(uint32_t va,
                                  mmu_data_type data_type/*used to check alignment*/,
                                  mem_op_type op_type/*used to check permission*/,
                                  TLB<uint32_t> *tlbs){
    uint32_t pa = 0;
    //va = fast_context_switch(va);
    check_alignment(va,data_type);
    ARMv6_TLBEntry *entry;
    if (saved_entry && (*saved_entry) &&
        ( (va & ~((*saved_entry)->mask))==(*saved_entry)->virt_addr)) {
      entry = static_cast<ARMv6_TLBEntry*>(*saved_entry);
      pa = entry->getPA(va);
    } else {
      TLBEntry<uint32_t> **entry_ptr = tlbs->search_entry(va);
      entry = static_cast<ARMv6_TLBEntry*>(entry_ptr? *entry_ptr: NULL);
      if (entry) {
        pa = entry->getPA(va);
        //debug()<<"Find in TLb! get physical addr["<<pa<<"]"<<endl;
      } else {
        //debug()<<"TLB miss! translation table walk!"<<endl;
        entry = static_cast<ARMv6_TLBEntry*>(translation_table_walk(va,data_type));
        static_cast<ARMv6_TLB*>(tlbs)->add_entry(entry,va);
        pa = entry->getPA(va);
      }
      saved_entry = static_cast<ARMv6_TLB*>(tlbs)->get_entry(tlbs->curpos);
    }
    check_access(va,entry,op_type);
    return pa;
  }

  uint32_t ARMv6_MMU::read_word__mmu(word_t va) {
    try {
      word_t pa = virt_to_phy(va,MMU_WORD_TYPE,MMU_READ,dTLBs);
      uint32_t data=memory_read_word(pa);
      debug() <<hex<<"read word at ["<<va<<"]->["<<pa<<"] return "<<data<<endl;
      return data;
    } catch(MMU_Faults<word_t>& faults) {
      handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_READ);
      return 0;
    }
  }

  void ARMv6_MMU::write_word__mmu(word_t va, uint32_t data) {
    try {
      word_t pa = virt_to_phy(va,MMU_WORD_TYPE,MMU_WRITE,dTLBs);
      debug() <<hex<<"write word "<<data<<" at ["<<va<<"]->["<<pa<<"]"<<endl;
      memory_write_word(pa,data);
    } catch(MMU_Faults<word_t>& faults) {
      handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_WRITE);
    }
  }

} // namespace simsoc
