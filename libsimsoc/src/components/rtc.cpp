//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "rtc.hpp"
#include "libsimsoc/display.hpp"

using namespace std;
using namespace sc_core;

namespace simsoc {

  Rtc::Rtc(sc_module_name name):
    Module(name),
    it(0), hz(0),
    rw_socket("rw_socket")
  {
    rw_socket.register_b_transport(this, &Rtc::custom_b_transport);
    SC_METHOD(compute);
    dont_initialize();
    sensitive <<tic;
  }

  Rtc::~Rtc() {}

  void Rtc::compute() {
    info() <<"TIC at time " <<sc_time_stamp() <<endl;
    ++it;
    if (it==1)
      it_signal = true;
    prog_tic();
  }

  void Rtc::custom_b_transport(tlm::tlm_generic_payload &payload,
                          sc_core::sc_time &delay_time) {
    assert(payload.get_response_status()==tlm::TLM_INCOMPLETE_RESPONSE);
    if (payload.get_data_length()!=4) {
      warning() <<"received transaction with invalid data length (should be 4).\n";
      payload.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
    } else if (payload.get_streaming_width()<payload.get_data_length()) {
      warning() <<"received transaction with invalid streaming width.\n";
      payload.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
    } else if (payload.get_byte_enable_ptr()) {
      warning() <<"byte enable not supported.\n";
      payload.set_response_status(tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE);
    } else {
      switch (payload.get_command()) {
      default:
        warning() <<"command not supported.\n";
        payload.set_response_status(tlm::TLM_COMMAND_ERROR_RESPONSE);
        break;
      case tlm::TLM_WRITE_COMMAND:
        write_word(static_cast<uint32_t>(payload.get_address()),
                   *reinterpret_cast<uint32_t*>(payload.get_data_ptr()));
        payload.set_response_status(tlm::TLM_OK_RESPONSE);
        break;
      case tlm::TLM_READ_COMMAND:
        *reinterpret_cast<uint32_t*>(payload.get_data_ptr()) =
          read_word(static_cast<uint32_t>(payload.get_address()));
        payload.set_response_status(tlm::TLM_OK_RESPONSE);
        break;
      }
    }
  }

  uint32_t Rtc::read_word(uint32_t a) {
    switch (a) {
    case HZ:
      return hz;
    case INTERRUPT_ACK:
      ack();
      return 0;
    default:
      assert(false);
      return 0;
    }
  }

  void Rtc::write_word(uint32_t a, uint32_t d) {
    switch (a) {
    case HZ:
      info() <<"set HZ: " <<dec <<d <<endl;
      hz = d;
      prog_tic();
      return;
    case INTERRUPT_ACK:
      ack();
      return;
    default:
      assert(false);
    }
  }

  void Rtc::ack() {
    info() <<"ACK at time " <<sc_time_stamp() <<endl;
    if (it) {
      --it;
      if (it==0)
        it_signal = false;
    }
  }

  void Rtc::prog_tic() {
    tic.cancel();
    if (hz)
      tic.notify(1.0/hz, SC_SEC);
  }

} // namespace simsoc
