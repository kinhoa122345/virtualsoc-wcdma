//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "tlb.tpp"

namespace simsoc {

  template class TLBEntry<BUS32>;
  template class TLBEntry<BUS64>;

  template class TLB<BUS32>;
  template class TLB<BUS64>;

} // namespace simsoc
