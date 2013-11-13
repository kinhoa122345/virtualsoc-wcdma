//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include <cassert>
#include "libsimsoc/processors/arm/arm_tlb.hpp"
#include "libsimsoc/processors/arm/arm_mmu.hpp"

namespace simsoc {

  ARM_TLB::ARM_TLB(const char* tlb_name,
                   uint32_t tlb_size,
                   bool lockable_):
    TLB<BUS32>(tlb_name, tlb_size), isLock(lockable_), next(NULL)
  {}

  TLBEntry<ARM_TLB::word_t> **ARM_TLB::search_entry(word_t virt_addr)
  {
    for (uint32_t i = 0; i!=size; i++) {
      ARM_TLBEntry *entry = static_cast<ARM_TLBEntry*>(entries[i]);
      if (!entry) {
        continue;
      }
      if ((virt_addr & ~(entry->mask)) == entry->virt_addr) {
        search_pos=i;
        return &entries[i];
      }
    }
    if(next)
      return next->search_entry(virt_addr);
    return NULL;
  }

  void ARM_TLB::add_entry(TLBEntry<ARM_TLB::word_t> *entry, word_t va)
  {
    uint32_t index=(curpos+1)%size;
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

  void ARM_TLB::invalidate_all_entries()
  {
    for (uint32_t i=0;i!=size;i++) {
      if(entries[i]) {
        delete entries[i];
        entries[i]=NULL;
      }
    }
    curpos=0;
    if(next)
      next->invalidate_all_entries();
  }

  void ARM_TLB::invalidate_single_entry(word_t virt_addr)
  {
    TLBEntry<word_t> **tlb_entry;
    tlb_entry = search_entry(virt_addr);
    if (tlb_entry!=NULL) {
      delete *tlb_entry;
      *tlb_entry = NULL;
    }
    if(next)
      next->invalidate_single_entry(virt_addr);
  }

} // namespace simsoc
