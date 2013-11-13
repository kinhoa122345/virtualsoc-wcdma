//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "mmu.tpp"

namespace simsoc {

template class MMU_Faults<BUS32>;
template class MMU_Faults<BUS64>;

template class MMU<BUS32>;
template class MMU<BUS64>;

} // namespace simsoc
