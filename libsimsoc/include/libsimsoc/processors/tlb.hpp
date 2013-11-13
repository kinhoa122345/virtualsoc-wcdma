//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef TLB_HPP
#define TLB_HPP

#include <libsimsoc/display.hpp>
#include "common.hpp"
#include <cstring>

namespace simsoc {

  /*
   * definition of TLB Entry
   */
  template <typename word_t>
  class TLBEntry
  {
  public:

    word_t virt_addr;
    word_t mask;

    TLBEntry(): virt_addr(0), mask(0) {}

    // virtual word_t getPA(word_t va)=0; -> not used
  };

  /*
   * definition of TLB
   */
  template <typename word_t>
  class TLB {
  public:
    const char* name;
    uint32_t size;
    TLBEntry<word_t> **entries;
    uint32_t curpos;
    uint32_t search_pos;

    TLB(const char* tlb_name, uint32_t tlb_size);
    virtual ~TLB();

    virtual TLBEntry<word_t> **search_entry(word_t virt_addr);
    TLBEntry<word_t> **get_entry(uint32_t index);
    void add_entry(TLBEntry<word_t> * entry, word_t index);
    virtual void invalidate_all_entries();
    void invalidate_single_entry(word_t virt_addr);
  };

} // namespace simsoc

// We do not include "tlb.tpp" here,
// because we only use a restricted number of parameter values.
// Code for these parameter values is created in "tlb.cpp".

#endif // TLB_HPP
