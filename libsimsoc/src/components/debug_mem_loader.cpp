//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "debug_mem_loader.hpp"
#include "libsimsoc/display.hpp"
using namespace std;
using namespace sc_core;

#ifndef ABS_TOP_SRCDIR
#error "ABS_TOP_SRCDIR not defined"
#endif

namespace simsoc {

DebugMemLoader::DebugMemLoader(sc_module_name name,
                               uint8_t *mem, size_t mem_start, size_t mem_size
                               ):
  Module(name),
  dmi_mem(mem), dmi_mem_start(mem_start), dmi_mem_size(mem_size),
  load_base(0)
{
  rw_port(*this); //bind slave port
  debug() <<"constructor called" <<endl;
}

DebugMemLoader::~DebugMemLoader() {
  debug() <<"destructor called" <<endl;
}

uint32_t DebugMemLoader::read_word(uint32_t addr) {
  switch (addr) {
  case IFS_GET_SIZE:
    debug()<<"get size: "<<get_size<<endl;
    return get_size;
  default:
    error() <<"invalid read word access at offset " <<hex <<addr <<".\n";
    exit(1);
  }
  return 0;
}

void DebugMemLoader::write_word(uint32_t addr, uint32_t data) {
  switch (addr) {
  case IFS_OPEN:
    {
      uint32_t i = data - dmi_mem_start;
      if (i>dmi_mem_size) {
        error() <<"OPEN_FILE source is outside memory (addr="
                <<hex <<data <<")\n";
        exit(1);
      }
      filename = string((char*) dmi_mem+i);
      ifs.open(filename.c_str(),ios::in|ios::binary);
      if (!ifs) {
        info() <<"failed to open " <<filename <<'\n';
        filename.insert(0,"/");
        filename.insert(0,ABS_TOP_SRCDIR);
        ifs.open(filename.c_str(),ios::in|ios::binary);
        info() <<"try to open " <<filename <<'\n';
        if (!ifs) {
          error() <<"failed to open file " <<filename <<endl;
          exit(1);
        }
      }
      debug()<<"Open file "<<filename<<" success"<<endl;
    }
    return;
  case IFS_CLOSE:
    {
      ifs.close();
      debug()<<"file "<<filename<<" closed"<<endl;
    }
    return;
  case IFS_SEEKG:
    {
      ifs.seekg(data);
      debug()<<hex<<  "ifs seekg "<<data<<endl;
    }
    return;
  case PUT_ADDR:			//load_section
    {
      if (is_bigendian) {
        uint32_t addr=(get_start_addr+load_base-dmi_mem_start)^3;
        if(addr>dmi_mem_size){
          error() <<"LOAD_SECTION source is outside memory (addr="
                  <<hex <<data <<")\n";
        }
        *((char*)dmi_mem+addr) = (char)data;
        debug()<<"load section bit endian"<<(char)data<<" at "<<addr<<endl;
      } else { // little endian (i.e. host endian)
        uint32_t i = get_start_addr+load_base - dmi_mem_start;
        if (i>dmi_mem_size) {
          error() <<"LOAD_SECTION source is outside memory (addr="
                  <<hex <<data <<")\n";
          exit(1);
        }
        ifs.read((char*) dmi_mem+i, get_size);
        debug()<<hex <<"load section at "<<load_base<<"from "<< get_start_addr-dmi_mem_start<< " for size of "<<get_size<<endl;
      }
      return;
    case IFS_GET_ADDR:			//read
      {
        uint32_t i = data - dmi_mem_start;
        if (i+get_size>dmi_mem_size) {
          error() <<"GET_ADDR destination is outside memory (start="
                  <<hex <<data <<"; size=" <<get_size <<")\n";
          exit(1);
        }
        ifs.read((char*) dmi_mem+i, get_size);
        debug()<<hex<<"ifs read from "<<i<<" for size of "<<get_size<<endl;
      }
      return;
    case IFS_GET_SIZE:
      get_size = data;
      debug()<<"set get_size "<<data<<endl;
      return;
    case SET_START_ADDR:
      get_start_addr=data;
      debug()<<"set start addresss "<<data<<endl;
      return;
    case SET_ENDIAN:
      is_bigendian=(bool)data;
      debug()<< "set big endian "<<data<<endl;
      return;
    case SET_DMI_MEM:
      load_base=data;
      debug()<<"set dmi mem at "<<data<<endl;
      return;
    case SET_DMI_START:
      dmi_mem_start=data;
      debug()<<"set dmi size: "<<data<<endl;
      return;
    case SET_DMI_SIZE:
      dmi_mem_size=data;
      debug()<<"set dmi size: "<<data<<endl;
      return;
    default:
      error() <<"invalid write word access at offset " <<hex <<addr <<".\n";
      exit(1);
    }
  }
}

} // namespace simsoc
