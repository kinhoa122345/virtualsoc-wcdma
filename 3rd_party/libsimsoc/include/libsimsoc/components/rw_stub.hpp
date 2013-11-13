//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef RW_STUB_HPP
#define RW_STUB_HPP

#include "libsimsoc/interfaces/tlm.hpp"
#include "libsimsoc/module.hpp"

namespace simsoc {

class RW_Stub: public Module,
               public RW_Target {
public:
  RW_TargetPort rw_port;
  RW_Stub(sc_core::sc_module_name name, bool big_endian=false);
  RW_Stub(sc_core::sc_module_name name, const char *message, bool big_endian=false);
  RW_Stub(sc_core::sc_module_name name, const char *message,
          int error_number, bool big_endian=false);

  uint32_t read_word(uint32_t addr);
  void write_word(uint32_t addr, uint32_t data);

  uint16_t read_half(uint32_t addr);
  void write_half(uint32_t addr, uint16_t data);

  uint8_t read_byte(uint32_t addr);
  void write_byte(uint32_t addr, uint8_t data);

 void trans_read_data(PayLoad &pl)
  {
      switch (pl.get_data_length()) {
      case 1: {
        const uint32_t addr = big_endian? pl.get_address()^3: pl.get_address();
        const uint8_t data = read_byte(addr);
        *(pl.get_data_ptr()) = data;
      } break;
      case 2: {
        const uint32_t addr = big_endian? pl.get_address()^2: pl.get_address();
        const uint16_t data = read_half(addr);
        *(uint16_t*)(pl.get_data_ptr()) = data;
      } break;
      case 4: {
        const uint32_t addr = pl.get_address();
        const uint32_t data = read_word(addr);
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
      case 1: {
        const uint32_t addr = big_endian? pl.get_address()^3: pl.get_address();
        const uint8_t data = *(pl.get_data_ptr());
        write_byte(addr,data);
      } break;
      case 2: {
        const uint32_t addr = big_endian? pl.get_address()^2: pl.get_address();
        const uint16_t data = *(uint16_t*)(pl.get_data_ptr());
        write_half(addr,data);
      } break;
      case 4: {
        const uint32_t addr = pl.get_address();
        const uint32_t data = *(uint32_t*)(pl.get_data_ptr());
        write_word(addr,data);
        } break;
      default:
        error() <<": write data method is not implemented for data_length = "
        <<pl.get_data_length() <<std::endl;
        exit(1);
      }
   };

  bool in_addr_arrange(uint32_t address);

//   void get_direct_access(uint32_t address /* in */,
//                          uint32_t *&host_address /* out */,
//                          uint32_t &size /* out */,
//                          ARM_TranslationTable *&table /* out */);

protected:
  const char* msg;
  int errnum;
  bool quiet;
  bool big_endian; // if used in a word-invariant big-endian system, then the addresses must be fixed.
};

} // namespace simsoc

#endif //RW_STUB_HPP
