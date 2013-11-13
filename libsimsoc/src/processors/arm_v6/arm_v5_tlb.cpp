//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// FIXME: this file describes the TLB of the ARM architecture version 5
// it should be replaced by a description of the TLB corresponding to version 6

#include "arm_v5_tlb.hpp"
#include "arm_v5_mmu.hpp"
#include <cassert>

namespace simsoc {

  ARMv6_TLB::ARMv6_TLB(const char* tlb_name,
                       uint32_t tlb_size,
                       bool lockable_):
    TLB<BUS32>(tlb_name, tlb_size), isLock(lockable_), next(NULL)
  {}

  TLBEntry<uint32_t> **ARMv6_TLB::search_entry(uint32_t virt_addr)
  {
    for (uint32_t i = 0; i!=size; i++) {
      ARMv6_TLBEntry *entry = static_cast<ARMv6_TLBEntry*>(entries[i]);
      if (!entry) {
        continue;
      }
      if ((virt_addr & ~(entry->mask)) == entry->virt_addr) {
        search_pos=i;
        return &entries[i];
      }
    }
    if (next)
      return next->search_entry(virt_addr);
    return NULL;
  }

  void ARMv6_TLB::add_entry(TLBEntry<uint32_t> *entry, uint32_t va)
  {
    uint32_t index = (curpos+1)%size;
    if (!isLock) {
      assert(index<size);
      delete entries[index];
      entries[index] = entry;
      curpos=index;
    } else {
      if (next)
        next->add_entry(entry,index);
    }
  }

  void ARMv6_TLB::invalidate_all_entries()
  {
    for (uint32_t i=0; i!=size; i++) {
      if (entries[i]) {
        delete entries[i];
        entries[i]=NULL;
      }
    }
    curpos=0;
    if (next)
      next->invalidate_all_entries();
  }

  void ARMv6_TLB::invalidate_single_entry(uint32_t virt_addr)
  {
    TLBEntry<uint32_t> **tlb_entry;
    tlb_entry = search_entry(virt_addr);
    if (tlb_entry!=NULL) {
      delete *tlb_entry;
      *tlb_entry = NULL;
    }
    if (next)
      next->invalidate_single_entry(virt_addr);
  }

} // namespace simsoc
