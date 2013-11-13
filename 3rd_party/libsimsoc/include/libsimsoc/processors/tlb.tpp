//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// Implementation of "tlb.hpp"
// This file is included only by "tlb.cpp"
#include "tlb.hpp"
#include <libsimsoc/translation_page.hpp>
#include <cassert>

using namespace std;

namespace simsoc {

  template <typename word_t>
  TLB<word_t>::TLB(const char* tlb_name, uint32_t tlb_size)
    : name(tlb_name), size(tlb_size),
      curpos(0), search_pos(0){
    entries = new TLBEntry<word_t>*[size];
    if(!entries) {
      error() <<"allocation of TLB failed!\n";
      exit(1);
    }
    memset(entries,0,size*sizeof(TLBEntry<word_t>*));
  }

  template <typename word_t>
  TLB<word_t>::~TLB() {
    for(uint32_t i=0;i!=size;i++) {
      delete entries[i];
    }
    delete[] entries;
  }

  /*
   * default implementation of TLB member functions
   */
  template <typename word_t>
  TLBEntry<word_t> **TLB<word_t>::search_entry(word_t virt_addr)
  {
    const uint32_t index = virt_addr/TranslationPage::TR_PAGE_SIZE;
    assert(index<size);
    TLBEntry<word_t> *entry = entries[index];
    if (entry && (virt_addr & ~(entry->mask))==entry->virt_addr) {
      search_pos=index;
      return &entries[index];
    }
    return NULL;
  }

  template <typename word_t>
  TLBEntry<word_t> **TLB<word_t>::get_entry(uint32_t index)
  {
    assert(index<size);
    return &entries[index];
  }

  template <typename word_t>
  void TLB<word_t>::add_entry(TLBEntry<word_t> *entry, word_t va)
  {
    const uint32_t index = va/TranslationPage::TR_PAGE_SIZE;
    assert(index<size);
    if(entries[index]) {
      delete entries[index];
      entries[index] = NULL;
    }
    entries[index] = entry;
    curpos=index;
  }

  template <typename word_t>
  void TLB<word_t>::invalidate_all_entries()
  {
    for (uint32_t i=0;i!=size;i++) {
      if(entries[i]) {
        delete entries[i];
        entries[i] = NULL;
      }
    }
    curpos=0;
  }

  template <typename word_t>
  void TLB<word_t>::invalidate_single_entry(word_t virt_addr)
  {
    TLBEntry<word_t> **tlb_entry = search_entry(virt_addr);
    if (tlb_entry!=NULL) {
      delete *tlb_entry;
      *tlb_entry = NULL;
    }
  }

} // namespace simsoc
