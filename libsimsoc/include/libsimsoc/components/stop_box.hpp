//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef STOP_BOX_HPP
#define STOP_BOX_HPP

#include <sys/types.h>
#include "libsimsoc/module.hpp"

namespace simsoc {

class StopBox: public Module {
public:
  StopBox(sc_core::sc_module_name name, size_t n_);
  void stop();
protected:
  size_t n;
};

} // namespace simsoc

#endif //STOP_BOX_HPP
