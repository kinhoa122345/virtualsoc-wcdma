//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// Interrupt controller
// Specification: http://www.gavare.se/gxemul/gxemul-stable/doc/experiments.html#expdevices

#ifndef IRQC_HPP
#define IRQC_HPP

#include <vector>

#include "libsimsoc/interfaces/tlm.hpp"
#include "libsimsoc/interfaces/tlm_signal.hpp"
#include "libsimsoc/module.hpp"

namespace simsoc {

class Irqc: public Module,
            public RW_Target,
            public SignalMultiTarget<bool> {
public:
  static const size_t SIZE = 0x10;

  static const uint32_t IRQ = 0x0;
  static const uint32_t MASK = 0x4;
  static const uint32_t UNMASK = 0x8;

protected:
  uint32_t status;
  uint32_t enabled;

public:
  std::vector<SignalMultiTargetPort<bool> > in_signals;

  SignalInitiatorPort<bool> out_signal;
  RW_TargetPort rw_port;

  Irqc(sc_core::sc_module_name name);
  ~Irqc();

  void signal(bool b, size_t n);

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
        error() <<": write data  method is not implemented for data_length = "
        <<pl.get_data_length() <<std::endl;
        exit(1);
      }
  };
};

} // namespace simsoc

#endif //IRQC_HPP
