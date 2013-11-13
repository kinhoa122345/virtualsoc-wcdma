//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "primexsys_ctrl.hpp"
#include "libsimsoc/display.hpp"
using namespace std;
using namespace sc_core;

namespace simsoc {

  static bool sysctrl_valid_word_address(uint32_t a) {
    return (PrimeXsysCtrl::SYSCTRL_WORD_LOWER_BOUND <= a) &&
      (a <=  PrimeXsysCtrl::SYSCTRL_WORD_UPPER_BOUND);
  }

  // Constructor
  PrimeXsysCtrl::PrimeXsysCtrl(sc_module_name name):
    Module(name)
  {
    rw_port(*this);              // bind the target port
    debug() <<"PrimeXsysCtrl constructor" <<endl;
  }

  // Destructor
  PrimeXsysCtrl::~PrimeXsysCtrl()
  {
    debug() <<"PrimeXsysCtrl destructed" << endl;
  }

  uint32_t PrimeXsysCtrl::read_word(uint32_t addr) {
    info() << "PrimeXsysCtrl read word" << endl;
    if (! sysctrl_valid_word_address(addr)) {
      error() << "Invalid read word" << endl;
      exit(1);
    }
    // read register
    switch(addr) {
    case SYSCTRL_CONTROL_OFFSET: return control;
    case SYSCTRL_STATUS_OFFSET: return status;
    case SYSCTRL_ITMODE_CTRL_OFFSET: return it_mode_ctrl;
    case SYSCTRL_ITMODE_STAT_OFFSET: return it_mode_status;
    case SYSCTRL_CRYSTAL_OFFSET: return crystal;
    case SYSCTRL_PLL_OFFSET: return pll_ctrl;
    case SYSCTRL_PLLFREQ_OFFSET: return pll_freq;
    case SYSCTRL_PERIPH0_OFFSET: return per_clock0;
    case SYSCTRL_PERIPH1_OFFSET: return per_clock1;
    case SYSCTRL_PERCLK_ENABLE_OFFSET:
      error() << "Try to read write only clock enable register " << endl;
      exit(1);
    case SYSCTRL_PERCLK_DISABLE_OFFSET:
      error() << "Try to read write only clock disable register " << endl;
      exit(1);
    case SYSCTRL_PERCLK_ENABLE_STAT_OFFSET: return per_clock_enable_status;
    case SYSCTRL_PERCLK_STATUS_OFFSET: return per_clock_status;
    }
    // should not happen
    error() << "Try to read non existent SYSCTRL register " << endl;
    exit(1);
  }

  void PrimeXsysCtrl::write_word(uint32_t addr, uint32_t d) {
    info() << "SYSCTRL write word" << endl;
    if (! sysctrl_valid_word_address(addr)) {
      error() << "Invalid write word address" << endl;
      exit(1);
    }
    switch (addr) {
    case SYSCTRL_CONTROL_OFFSET :
      if (d & NORMAL_MODE_CTRL) {
        control |= NORMAL_MODE;
        debug() << "Set NORMAL MODE control register " << endl;
      }
      debug() << "Write control register " << endl;
      return;

    case SYSCTRL_STATUS_OFFSET :
      status = d;
      debug() << "Write status register " << endl;
      return;

    case SYSCTRL_ITMODE_CTRL_OFFSET :
      it_mode_ctrl = d;
      debug() << "Write it_mode_ctrl register " << endl;
      return;

    case SYSCTRL_ITMODE_STAT_OFFSET :
      it_mode_status = d;
      debug() << "Write it_mode_status register " << endl;
      return;

    case SYSCTRL_CRYSTAL_OFFSET :
      crystal = d;
      debug() << "Write crystal register " << endl;
      return;

    case SYSCTRL_PLL_OFFSET :
      pll_ctrl = d;
      debug() << "Write pll_ctrl register " << endl;
      return;

    case SYSCTRL_PLLFREQ_OFFSET :
      pll_freq = d;
      debug() << "Write pll_freq register " << endl;
      return;

    case SYSCTRL_PERIPH0_OFFSET:
      per_clock0 = d;
      debug() << "Write per_clock0 register " << endl;
      return;

    case SYSCTRL_PERIPH1_OFFSET:
      per_clock1 = d;
      debug() << "Write per_clock1 register " << endl;
      return;

    case SYSCTRL_PERCLK_ENABLE_OFFSET:
      per_clock_enable = d;
      debug() << "Write per_clock_enable register " << endl;
      return;

    case SYSCTRL_PERCLK_DISABLE_OFFSET:
      per_clock_disable = d;
      debug() << "Write per_clock_disable register " << endl;
      return;

    case SYSCTRL_PERCLK_ENABLE_STAT_OFFSET:
      error() << "Write read only clock enable register" << endl;
      exit(1);

    case SYSCTRL_PERCLK_STATUS_OFFSET:
      error() << "Write read only clock status register" << endl;
      exit(1);

    }
    // should not happen
    error() << "Invalid write SYSCTRL register" << endl;
    exit(1);
  }

} // namespace simsoc
