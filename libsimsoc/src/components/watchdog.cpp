//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "watchdog.hpp"
#include "libsimsoc/display.hpp"
using namespace std;
using namespace sc_core;

namespace simsoc {

  static bool wdog_valid_word_address(uint32_t a) {
    return (WatchDog::WDOG_WORD_LOWER_BOUND <= a) &&
      (a <= WatchDog::WDOG_WORD_UPPER_BOUND);
  }

/*
 * Constructor and destructor
 */

WatchDog::WatchDog(sc_module_name name):
  Module(name)
{
  rw_port(*this);              // bind the target port
  debug() <<"WatchDog constructor" <<endl;
  load = 0;
  control = 0;
  value = 0;
  raw_it_status = 0;
  masked_it_status = 0;
  lock = 0;
}

WatchDog::~WatchDog()
{
  debug() <<"WatchDog destructed" << endl;
}

/*
 * The addresses for
 *
 */


uint32_t WatchDog::read_word(uint32_t addr) {
  if (! wdog_valid_word_address(addr)) {
    error() << "Invalid read watchdog register" << endl;
    exit(1);
  }
  // read register
  info() << "WatchDog read word" << addr << endl;
  switch(addr) {
  case WDOG_LOAD_OFFSET :
    return load;

  case WDOG_VALUE_OFFSET :
    return value;

  case WDOG_CONTROL_OFFSET :
    return control;

  case WDOG_RIS_OFFSET :
    return raw_it_status;

  case WDOG_MIS_OFFSET :
    return masked_it_status;

  case WDOG_LOCK_OFFSET :
    return masked_it_status;

  case WDOG_IT_CLEAR_OFFSET:
    error() << "Invalid read on WO clear interrupt register " << endl;
    exit(1);
  }
  // should not happen
  error() << "Try to read non existent WDOG register " << endl;
  exit(1);
}

void WatchDog::write_word(uint32_t addr, uint32_t d) {
  info() << "WDOG write word" << endl;
  if (! wdog_valid_word_address(addr)) {
    error() << "Invalid write watchdog address" << endl;
    exit(1);
  }
  //
  info() << "Write watchdog register " << addr << endl;
  switch (addr) {
  case WDOG_LOAD_OFFSET :
    load = d;
    return;

  case WDOG_CONTROL_OFFSET :
    control = d;
    return;

  case WDOG_IT_CLEAR_OFFSET :
    it_clear = d; // TODO clear Interrupt on VIC
    return;

  case WDOG_LOCK_OFFSET :
    lock = d;
    return;

  case WDOG_VALUE_OFFSET:
    error() << "Write RO raw it status register" << endl;
    exit(1);

  case WDOG_RIS_OFFSET:
    error() << "Write RO raw it status register" << endl;
    exit(1);

  case WDOG_MIS_OFFSET:
    error() << "Write RO masked it status register" << endl;
    exit(1);

  }
  // should not happen
  error() << "Invalid write WDOG register" << endl;
  exit(1);
}

} // namespace simsoc
