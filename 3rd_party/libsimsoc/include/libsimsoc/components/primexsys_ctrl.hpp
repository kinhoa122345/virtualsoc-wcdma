//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PRIMECELL_SYSCTRL_HPP
#define PRIMECELL_SYSCTRL_HPP
/*
 * TLM Model for ARM 926  System Controller
 *
 */

#include "libsimsoc/interfaces/tlm.hpp"
#include "libsimsoc/module.hpp"

namespace simsoc {

/*
 * The controller  manages system global variables
 */

class PrimeXsysCtrl: public Module,
                     public RW_Target {

public:
  static const uint32_t  SYSCTRL_WORD_LOWER_BOUND  = 0x00;
  static const uint32_t  SYSCTRL_WORD_UPPER_BOUND  = 0x30;

  static const uint32_t  SYSCTRL_CONTROL_OFFSET = 0x00;
  static const uint32_t  SYSCTRL_STATUS_OFFSET = 0x04;
  static const uint32_t  SYSCTRL_ITMODE_CTRL_OFFSET = 0x08;
  static const uint32_t  SYSCTRL_ITMODE_STAT_OFFSET = 0x0C;
  static const uint32_t  SYSCTRL_CRYSTAL_OFFSET = 0x10;
  static const uint32_t  SYSCTRL_PLL_OFFSET = 0x14;
  static const uint32_t  SYSCTRL_PLLFREQ_OFFSET = 0x18;
  static const uint32_t  SYSCTRL_PERIPH0_OFFSET= 0x1C;
  static const uint32_t  SYSCTRL_PERIPH1_OFFSET= 0x20;
  static const uint32_t  SYSCTRL_PERCLK_ENABLE_OFFSET= 0x24;
  static const uint32_t  SYSCTRL_PERCLK_DISABLE_OFFSET= 0x28;
  static const uint32_t  SYSCTRL_PERCLK_ENABLE_STAT_OFFSET= 0x2C;
  static const uint32_t  SYSCTRL_PERCLK_STATUS_OFFSET= 0x30;

  static const uint32_t SLEEP_MODE  = 0x00;
  static const uint32_t D0ZE_MODE   = 0x08;
  static const uint32_t SLOW_MODE   = 0x10;
  static const uint32_t NORMAL_MODE = 0x20;

  static const uint32_t SLEEP_MODE_CTRL  = 0x0;
  static const uint32_t DOZE_MODE_CTRL   = 0x1;
  static const uint32_t SLOW_MODE_CTRL   = 0x2;
  static const uint32_t NORMAL_MODE_CTRL = 0x4;

  RW_TargetPort rw_port;
  uint32_t control; // control register
  uint32_t status; // status register
  uint32_t it_mode_ctrl; // interrupt control register
  uint32_t it_mode_status; // it mode status
  uint32_t crystal; // it status
  uint32_t pll_ctrl; //  PLL control register
  uint32_t pll_freq; //  PLL frequency control register
  uint32_t per_clock0; // periph clock control register
  uint32_t per_clock1; // periph clock control register
  uint32_t per_clock_enable; // write only register
  uint32_t per_clock_disable; //  write only register
  uint32_t per_clock_enable_status; // read-only register
  uint32_t per_clock_status; // read only register

  PrimeXsysCtrl(sc_core::sc_module_name name);
  ~PrimeXsysCtrl();

  // TLM read writes
  uint32_t read_word(uint32_t addr);
  void write_word(uint32_t addr, uint32_t data);

 void trans_read_data(PayLoad &pl)
  {
      switch (pl.get_data_length()) {
      case 4: {
        uint32_t addr = pl.get_address();
          uint32_t data = read_word(addr);
          *(uint32_t*)(pl.get_data_ptr()) = data;
      } break;
      default:
        error() <<": read data method is not implemented for data_length = "
        <<pl.get_data_length() <<std::endl;
        exit(1);
      }
  };

  void trans_write_data(PayLoad &pl)
  {
      switch (pl.get_data_length()) {
      case 4: {
        uint32_t addr = pl.get_address();
          uint32_t data = *(uint32_t*)(pl.get_data_ptr());
          write_word(addr,data);
        } break;
      default:
        error() <<": write data method is not implemented for data_length = "
        <<pl.get_data_length() <<std::endl;
        exit(1);
      }
  };

protected:
  // void Reset();
};

} // namespace simsoc

#endif //SYSCTRL
