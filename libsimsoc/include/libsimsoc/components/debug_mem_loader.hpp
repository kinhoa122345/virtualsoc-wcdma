//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef DEBUG_MEM_LOADER_HPP_
#define DEBUG_MEM_LOADER_HPP_

#include <fstream>
#include "libsimsoc/interfaces/tlm.hpp"
#include "libsimsoc/module.hpp"

namespace simsoc {

class DebugMemLoader: public Module,
                      public RW_Target {
public:
  static const size_t SIZE = 0x40;

  static const uint32_t IFS_OPEN = 0x0;
  static const uint32_t PUT_ADDR= 0x4;
  static const uint32_t IFS_GET_ADDR = 0x8;
  static const uint32_t IFS_GET_SIZE = 0xC;
  static const uint32_t IFS_CLOSE = 0x10;
  static const uint32_t IFS_SEEKG=0x14;
  static const uint32_t SET_START_ADDR =0x18;
  static const uint32_t SET_ENDIAN=0x1C;
  static const uint32_t SET_DMI_MEM=0x20;
  static const uint32_t SET_DMI_START=0x24;
  static const uint32_t SET_DMI_SIZE=0x28;

  RW_TargetPort rw_port;
  std::string filename;
  uint32_t get_size;
  uint32_t get_start_addr;
  bool is_bigendian;

  DebugMemLoader(sc_core::sc_module_name name,
               uint8_t *mem, size_t mem_start, size_t mem_size);

  ~DebugMemLoader();

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

protected:
  // Direct Memory Interface
  uint8_t *dmi_mem;
  size_t dmi_mem_start;
  size_t dmi_mem_size;

  uint32_t load_base;
  std::ifstream ifs;
};

} // namespace simsoc

#endif /*DEBUG_MEM_LOADER_HPP_*/
