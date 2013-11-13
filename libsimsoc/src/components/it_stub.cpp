//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "it_stub.hpp"
#include "libsimsoc/display.hpp"
using namespace sc_core;
using namespace std;

namespace simsoc {

IT_Stub::IT_Stub(sc_module_name name):
  Module(name), it_port(false)
{
  it_port(*this);
}

void IT_Stub::signal(bool b) {
  if (b)
    info() <<"interrupt raised." <<endl;
  else
    info() <<"interrupt cleared." <<endl;
}

} // namespace simsoc
