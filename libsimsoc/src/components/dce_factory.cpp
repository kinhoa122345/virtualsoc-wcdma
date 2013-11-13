//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "dce_factory.hpp"
#include <libsimsoc/context.hpp>
#include "dce_xterm.hpp"
#include "dce_xterm_pthread.hpp"
#include "dce_host_uart.hpp"
#include "dce_host_uart_pthread.hpp"
#include "dce_stub.hpp"

using namespace sc_core;

namespace simsoc {

  static const char *dce_class_names[5] =
    {"stub", "xterm", "pxterm", "host", "phost"};

  ParameterEnumQueue dce_classes("UART","-uart",
                                 "select the DCE class to connect to the UART",
                                 dce_class_names,5,0);

  AbstractRS232_DCE *create_dce(AbstractRS232_DTE *dte, const char *name) {
    AbstractRS232_DCE *dce = NULL;
    switch (dce_classes.front()) {
    case 0:
      dce = new DCE_Stub(name? name: sc_gen_unique_name("STUB"));
      break;
    case 1:
      dce = new DCE_Xterm(name? name: sc_gen_unique_name("XTERM"));
      break;
    case 2:
      dce = new DCE_Xterm_PTHREAD(name? name: sc_gen_unique_name("P_XTERM"));
      break;
    case 3:
      dce = new DCE_HostUART(name? name: sc_gen_unique_name("HOST_UART"));
      break;
    case 4:
      dce = new DCE_HostUART_PTHREAD(name? name: sc_gen_unique_name("P_HOST_UART"));
      break;
    default: UNREACHABLE;
    }
    dce_classes.pop_front();
    assert(dce);
    dce->bind(dte);
    return dce;
  }

} // namespace simsoc
