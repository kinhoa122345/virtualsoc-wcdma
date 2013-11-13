//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "stop_box.hpp"
#include "libsimsoc/display.hpp"

using namespace std;
using namespace sc_core;

namespace simsoc {

StopBox::StopBox(sc_core::sc_module_name name, size_t n_):
  Module(name),
  n(n_) {}

void StopBox::stop() {
  if (--n)
    return;
  info() <<"sc_stop called." <<endl;
  sc_core::sc_stop();
}

} // namespace simsoc
