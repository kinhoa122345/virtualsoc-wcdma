//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef DCE_FACTORY_HPP
#define DCE_FACTORY_HPP

#include "libsimsoc/interfaces/RS232.hpp"

namespace simsoc {

  extern AbstractRS232_DCE *create_dce(AbstractRS232_DTE *dte,
                                       const char *name = NULL);

} // namespace simsoc

#endif //DCE_FACTORY_HPP
