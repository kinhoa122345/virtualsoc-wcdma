//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef SPEAR_CTRL_HPP
#define SPEAR_CTRL_HPP
/*
 * TLM Model for SPEAR Plus 600 SoC contoller
 * This module is incomplete. Many TODO's
 *
 */

#include "libsimsoc/interfaces/tlm.hpp"
#include "libsimsoc/module.hpp"

namespace simsoc {
/*
 * The controller  manages watchdog timer
 */

class WatchDog: public Module,
                public RW_Target {

public:
  static const uint32_t  WDOG_WORD_LOWER_BOUND  = 0x00;
  static const uint32_t  WDOG_WORD_UPPER_BOUND  = 0xC00;

  static const uint32_t  WDOG_LOAD_OFFSET = 0x00;
  static const uint32_t  WDOG_VALUE_OFFSET = 0x04;
  static const uint32_t  WDOG_CONTROL_OFFSET = 0x08;
  static const uint32_t  WDOG_IT_CLEAR_OFFSET = 0x0C;
  static const uint32_t  WDOG_RIS_OFFSET = 0x10;
  static const uint32_t  WDOG_MIS_OFFSET = 0x14;
  static const uint32_t  WDOG_LOCK_OFFSET= 0xC00;

  RW_TargetPort rw_port;
  uint32_t load; // interrupt control register
  uint32_t value; // it status
  uint32_t control; // control register
  uint32_t it_clear; //  clear interrupt
  uint32_t raw_it_status; // status register
  uint32_t masked_it_status; //  PLL control register
  uint32_t lock; // read only register

  WatchDog(sc_core::sc_module_name name);
  ~WatchDog();

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

#endif //WDOG
