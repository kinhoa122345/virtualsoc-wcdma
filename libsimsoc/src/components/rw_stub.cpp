//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "rw_stub.hpp"
#include "libsimsoc/display.hpp"
using namespace std;
using namespace sc_core;

namespace simsoc {

  RW_Stub::RW_Stub(sc_module_name name, bool be):
  Module(name), msg(NULL), errnum(0), quiet(true), big_endian(be)
{
  rw_port(*this);
}

RW_Stub::RW_Stub(sc_core::sc_module_name name, const char *message, bool be):
  Module(name), msg(message), errnum(0), quiet(false), big_endian(be)
{
  rw_port(*this);
}

RW_Stub::RW_Stub(sc_core::sc_module_name name, const char *message,
                 int error_number, bool be):
  Module(name), msg(message), errnum(error_number), quiet(false), big_endian(be)
{
  rw_port(*this);
}

uint32_t RW_Stub::read_word(uint32_t addr) {
  if (msg)
    if (errnum) {
      error() <<msg <<'\n';
      error() <<"read word at address " <<hex <<addr <<'\n';
      exit(errnum);
    } else {
      if (!quiet) {
        warning() <<msg <<'\n';
        warning() <<"read word at address " <<hex <<addr <<'\n';
        warning() <<"next accesses to this component will be ignored." <<endl;
        quiet = true;
      }
    }
  else
    info() <<"read word at address " <<hex <<addr <<'\n';
  return 0;
}

void RW_Stub::write_word(uint32_t addr, uint32_t d) {
  if (msg)
    if (errnum) {
      error() <<msg <<'\n';
      error() <<"write word " <<hex <<d <<"\tat address " <<addr <<'\n';
      exit(errnum);
    } else {
      if (!quiet) {
        warning() <<msg <<'\n';
        warning()  <<"write word " <<hex <<d <<"\tat address " <<addr <<'\n';
        warning() <<"next accesses to this component will be ignored." <<endl;
        quiet = true;
      }
    }
  else
    info() <<"write word " <<hex <<d <<"\tat address " <<addr <<'\n';
}

uint16_t RW_Stub::read_half(uint32_t addr) {
  if (msg)
    if (errnum) {
      error() <<msg <<'\n';
      error() <<"read half at address " <<hex <<addr <<'\n';
      exit(errnum);
    } else {
      if (!quiet) {
        warning() <<msg <<'\n';
        warning() <<"read half at address " <<hex <<addr <<'\n';
        warning() <<"next accesses to this component will be ignored." <<endl;
        quiet = true;
      }
    }
  else
    info() <<"read half at address " <<hex <<addr <<'\n';
  return 0;
}

void RW_Stub::write_half(uint32_t addr, uint16_t d) {
  if (msg)
    if (errnum) {
      error() <<msg <<'\n';
      error() <<"write half " <<hex <<d <<"\tat address " <<addr <<'\n';
      exit(errnum);
    } else {
      if (!quiet) {
        warning() <<msg <<'\n';
        warning() <<"write half " <<hex <<d <<"\tat address " <<addr <<'\n';
        warning() <<"next accesses to this component will be ignored." <<endl;
        quiet = true;
      }
    }
  else
    info() <<"write half " <<hex <<d <<"\tat address " <<addr <<'\n';
}

uint8_t RW_Stub::read_byte(uint32_t addr) {
  if (msg)
    if (errnum) {
      error() <<msg <<'\n';
      error() <<"read byte at address " <<hex <<addr <<'\n';
      exit(errnum);
    } else {
      if (!quiet) {
        warning() <<msg <<'\n';
        warning() <<"read byte at address " <<hex <<addr <<'\n';
        warning() <<"next accesses to this component will be ignored." <<endl;
        quiet = true;
      }
    }
  else
    info() <<"read byte at address " <<hex <<addr <<'\n';
  return 0;
}

void RW_Stub::write_byte(uint32_t addr, uint8_t d) {
  if (msg)
    if (errnum) {
      error() <<msg <<'\n';
      error() <<"write byte " <<hex <<(int)d <<"\tat address " <<addr <<'\n';
      exit(errnum);
    } else {
      if (!quiet) {
        warning() <<msg <<'\n';
        warning() <<"write byte " <<hex <<(int)d <<"\tat address " <<addr <<'\n';
        warning() <<"next accesses to this component will be ignored." <<endl;
        quiet = true;
      }
    }
  else
    info() <<"write byte " <<hex <<(int)d <<"\tat address " <<addr <<'\n';
}

bool RW_Stub::in_addr_arrange(uint32_t address){
  return false;
}

} // namespace simsoc
