//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// Real time controller
// Specification: http://www.gavare.se/gxemul/gxemul-stable/doc/experiments.html#expdevices
//                (only register 0x100 and 0x110)

#ifndef RTC_HPP
#define RTC_HPP

#include "libsimsoc/interfaces/tlm_signal.hpp"
#include "libsimsoc/module.hpp"

#include <tlm.h>
#include <tlm_utils/simple_target_socket.h>

#include <inttypes.h>

namespace simsoc {

class Rtc: public Module {
public:
  static const size_t SIZE = 0x200;

  static const uint32_t HZ = 0x100;
  static const uint32_t INTERRUPT_ACK = 0x110;

protected:
  uint32_t it;
  uint32_t hz;
  sc_core::sc_event tic;

public:

  tlm_utils::simple_target_socket<Rtc> rw_socket;
  SignalInitiatorPort<bool> it_signal;

  SC_HAS_PROCESS(Rtc);
  Rtc(sc_core::sc_module_name name);
  ~Rtc();

protected:

  void compute();

  void custom_b_transport(tlm::tlm_generic_payload &payload,
                          sc_core::sc_time &delay_time);

  uint32_t read_word(uint32_t addr);
  void write_word(uint32_t addr, uint32_t data);

  void ack();
  void prog_tic();
};

} // namespace simsoc

#endif //RTC_HPP
