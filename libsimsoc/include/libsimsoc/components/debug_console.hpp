//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef DEBUG_CONSOLE_HPP
#define DEBUG_CONSOLE_HPP

#include "libsimsoc/interfaces/tlm_helper.hpp"
#include "libsimsoc/components/stop_box.hpp"
#include "libsimsoc/module.hpp"
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

namespace simsoc {

class DebugConsole: public Module {
public:
  static const size_t SIZE = 0x100;

  static const uint32_t PUT_CHAR = 0x0; // WO (byte)
  static const uint32_t PUT_DEC_INT = 0x4; //WO (word, half or byte)
  static const uint32_t PUT_DEC_UINT = 0x8; //WO (word, half or byte)
  static const uint32_t PUT_HEX_UINT = 0xC; //WO (word, half or byte)

  static const uint32_t STR_PUT_ADDR = 0x10; // WO (word)
  static const uint32_t STR_GET_ADDR = 0x14; // WO (word) !SYSTEM BLOCKING ACCESS!
  static const uint32_t STR_GET_SIZE = 0x18; // RW (word)

  static const uint32_t HALT = 0x20; // WO (word) !PROCESS BLOCKING ACCESS!
  static const uint32_t DTMODE = 0x28; // WO (word)

  static const uint32_t SET_ERROR_LEVEL = 0x30; // WO (word)
  static const uint32_t SET_WARNING_LEVEL = 0x34; // WO (word)
  static const uint32_t SET_INFO_LEVEL = 0x38; // WO (word)
  static const uint32_t SET_DEBUG_LEVEL = 0x3c; // WO (word)

  static const uint32_t PUT_DEC_INT_LOW = 0x40; //WO (32-bits word)
  static const uint32_t PUT_DEC_INT_HIGH = 0x44; //WO (32-bits word)
  static const uint32_t PUT_DEC_UINT_LOW = 0x48; //WO (32-bits word)
  static const uint32_t PUT_DEC_UINT_HIGH = 0x4c; //WO (32-bits word)
  static const uint32_t PUT_HEX_UINT_LOW = 0x50; //WO (32-bits word)
  static const uint32_t PUT_HEX_UINT_HIGH = 0x54; //WO (32-bits word)

public:
  tlm_utils::simple_target_socket<DebugConsole> target_socket;
  tlm_utils::simple_initiator_socket<DebugConsole> initiator_socket;

  DebugConsole(sc_core::sc_module_name name,
               StopBox *sb = NULL,uint32_t _wait_num=1, bool big_endian=false);

  ~DebugConsole();

  void set_big_endian(bool value) {big_endian = value;}

protected:
  void b_transport(tlm::tlm_generic_payload &payload, sc_core::sc_time &delay_time);
  uint32_t read_word(uint32_t addr);
  void write_word(uint32_t addr, uint32_t data);
  void write_half(uint32_t addr, uint16_t data);
  void write_byte(uint32_t addr, uint8_t data);

  // registers
  uint32_t str_get_size;

  // halt requests are forwarded to the stop box, if not null
  // else sc_stop() is called directly.
  StopBox *stop_box;
  uint32_t wait_num;
  bool half_of_64_loaded;
  uint32_t half_of_64;
  bool big_endian;
  sc_core::sc_event never_notified;

  void set_trace_level(TraceLevel tl, uint32_t data);
  bool do_print(uint32_t);
  uint64_t merge_halves(uint32_t, uint32_t);

  bool same_endianness() const {return !big_endian;}
  // TODO: must return false is the target and the host do not use the same endianness

};

} // namespace simsoc

#endif //DEBUG_CONSOLE_HPP
