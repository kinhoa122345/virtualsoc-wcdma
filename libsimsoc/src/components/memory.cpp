//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifdef HAVE_CONFIG_H
# include "libsimsoc/config.h"
#endif

#include "libsimsoc/components/memory.hpp"
#include "libsimsoc/processors/processor.hpp"

#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fstream>

using namespace std;
using namespace sc_core;

namespace simsoc {

Memory::Memory(sc_module_name name,
               unsigned size_):
  Module(name),
  size(size_),
  mem(NULL),
  translation_table(size_/TranslationPage::TR_PAGE_SIZE),
  invalidated_pages(), translation_code_users()
{
  debug() <<"constructor called\n";
  rw_socket.register_b_transport(this, &Memory::b_transport);
  rw_socket.register_transport_dbg(this, &Memory::transport_dbg);
  rw_socket.register_get_direct_mem_ptr(this, &Memory::get_direct_mem_ptr);

#if defined(HAVE_MAP_ANONYMOUS)
  mem = (uint8_t*) mmap(0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
#elif defined(HAVE_MAP_ANON)
  mem = (uint8_t*) mmap(0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANON, -1, 0);
#else
#error "Neither MAP_ANONYMOUS nor MAP_ANON are available."
#endif

  if (mem==MAP_FAILED) {
    error() <<"mmap simulated memory failed! errmsg=[" <<strerror(errno) <<"]" <<endl;
    exit(1);
  }

  host_addresses[mem] = this;

  set_sigsegv_handler();
}

Memory::~Memory() {
  if (munmap(mem,size)) {
    error() <<"munmap memory failed! errmsg=[" <<strerror(errno) <<"]" <<endl;
    exit(1);
  }

  for (list<TranslationPage*>::iterator i = invalidated_pages.begin();
       i!= invalidated_pages.end(); ++i)
    if (*i) {
      delete *i;
      *i = NULL;
    }

  reset_sigsegv_handler();

  debug() <<"Destructor called." <<endl;
}

  void Memory::b_transport(tlm::tlm_generic_payload &payload,
                           sc_core::sc_time &delay_time) {
    assert(payload.get_response_status()==tlm::TLM_INCOMPLETE_RESPONSE);
    if (payload.get_byte_enable_ptr()) {
      warning() <<"byte enable not supported.\n";
      payload.set_response_status(tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE);
    } else {
      switch (payload.get_command()) {
      default:
        info() <<"command not supported.\n";
        payload.set_response_status(tlm::TLM_COMMAND_ERROR_RESPONSE);
        return;
      case tlm::TLM_WRITE_COMMAND:
        trans_write_data(payload);
        break;
      case tlm::TLM_READ_COMMAND:
        trans_read_data(payload);
        break;
      }
      payload.set_response_status(tlm::TLM_OK_RESPONSE);
      payload.set_dmi_allowed(true);
    }
  }

  unsigned int Memory::transport_dbg(tlm::tlm_generic_payload &payload) {
    assert(payload.get_response_status()==tlm::TLM_INCOMPLETE_RESPONSE);
    if (payload.get_byte_enable_ptr()) {
      warning() <<"byte enable not supported.\n";
      payload.set_response_status(tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE);
      return 0;
    } else {
      switch (payload.get_command()) {
      default:
        info() <<"command not supported.\n";
        payload.set_response_status(tlm::TLM_COMMAND_ERROR_RESPONSE);
        return 0;
      case tlm::TLM_WRITE_COMMAND:
        trans_write_data(payload);
        break;
      case tlm::TLM_READ_COMMAND:
        trans_read_data(payload);
        break;
      }
      payload.set_response_status(tlm::TLM_OK_RESPONSE);
      return payload.get_data_length();
    }
  }

  bool Memory::get_direct_mem_ptr(tlm::tlm_generic_payload &payload,
                          tlm::tlm_dmi&  dmi_data) {
    uint32_t address = payload.get_address();
    if (address<size) {
      dmi_data.allow_read_write();
      dmi_data.set_start_address(0);
      dmi_data.set_end_address(size-1);
      dmi_data.set_dmi_ptr(mem);
      dmi_data.set_read_latency(sc_core::sc_time(10, sc_core::SC_NS));
      dmi_data.set_write_latency(sc_core::sc_time(10, sc_core::SC_NS));

      // Fill extension for instruction cache:
      DirectInstrCacheExtension *ext = NULL;
      payload.get_extension(ext);
      if (ext) {
        assert(ext->user);
        debug() <<"add " <<ext->user->name() <<" as a user of the translation table" <<endl;
        translation_code_users.push_front(ext->user);
        ext->table = &translation_table;
      }

      return true;
    } else {
      dmi_data.set_start_address(address);
      dmi_data.set_end_address(address);
      return false;
    }
  }

  void Memory::trans_read_data(tlm::tlm_generic_payload &pl)
  {
    uint32_t addr = pl.get_address();
    assert(addr+pl.get_data_length()<=size);
    memcpy(pl.get_data_ptr(),(char*)(mem+addr),pl.get_data_length());
  }

  void Memory::trans_write_data(tlm::tlm_generic_payload &pl)
  {
    uint32_t addr = pl.get_address();
    assert(addr+pl.get_data_length()<=size);
    memcpy((char*)mem+addr,pl.get_data_ptr(),pl.get_data_length());
  }

uint8_t *Memory::get_host_address() {
  return mem;
}

void Memory::load_image(const char *file_name, uint32_t address) {
  assert(address<size);
  struct stat file_stat;
  if (!stat(file_name, &file_stat) == 0) {
    error() <<"failed to \"stat\" file " <<file_name <<endl;
    exit(1);
  }
  if (address+file_stat.st_size>size) {
    error() <<"not enough space in target memory ("
          <<address+file_stat.st_size-size <<" exceeding bytes)" <<endl;
    exit(1);
  }
  ifstream file_stream(file_name,ios::in|ios::binary);
  file_stream.read((char*)mem+address,file_stat.st_size);
  if (!file_stream) {
    error() <<"failed to load file" <<endl;
    exit(1);
  }
  file_stream.close();
}


void Memory::dump(uint32_t start, uint32_t length, ostream& os) {
  uint32_t s = start;
  uint32_t e = s + length;
  assert(e<=size);
  os <<"MEMORY DUMP: " <<hex;
  for (uint32_t a = s; a<e; ++a)
    os <<mem[a] <<' ';
  os <<dec <<endl;
}

void Memory::invalidate_translated_codepage(uint32_t addr) {
  TranslationTableItem *translated_page = &translation_table[addr/TranslationPage::TR_PAGE_SIZE];
  if (!translated_page)
    UNREACHABLE;
  info() <<"invalidate translated pages corresponding to address " <<hex <<addr <<endl;
  translated_page->clear(invalidated_pages);
  if (invalidated_pages.size()>42)
    clean_invalidated_pages();
}

// subfunction for clean_invalidated_pages method
static void add_current_page(set<const TranslationPage*> *current_pages, Processor *p) {
  current_pages->insert(p->get_current_page());
}

// subfunction for clean_invalidated_pages method
static bool can_free_page(set<const TranslationPage*> *current_pages, TranslationPage* p) {
  bool b = current_pages->find(p)==current_pages->end();
  if (b)
    delete p;
  return b;
}

void Memory::clean_invalidated_pages() {
  set<const TranslationPage*> current_pages;
  for_each(translation_code_users.begin(),translation_code_users.end(),
          bind1st(ptr_fun(add_current_page),&current_pages));
  invalidated_pages.erase(remove_if(invalidated_pages.begin(),invalidated_pages.end(),
                                    bind1st(ptr_fun(can_free_page),&current_pages)),
                          invalidated_pages.end());
}

/******************************************************************************/
// static functions

  void sigsegv_handler(int signo, siginfo_t *siginfo, void *ucontext);

  bool Memory::sigsegv_handler_set = false;

  // On some systems, a write access to read-only memory raises a SIGSEGV,
  // in some others, it raises a SIGBUS, so we redefine both.

  struct sigaction Memory::act, Memory::old_segv_act, Memory::old_bus_act;

  map<uint8_t*, Memory*, greater<void*> > Memory::host_addresses;

  void Memory::set_sigsegv_handler() {
    if (sigsegv_handler_set)
      return;
    ::simsoc::debug() <<"[class Memory] " <<"set SIGSEGV handler" <<endl;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = sigsegv_handler;
    if (sigaction(SIGSEGV, &act, &old_segv_act)<0) {
      ::simsoc::error() <<"[class Memory] " <<"Set SIGSEGV handler Failed! errMsg=["
                        <<strerror(errno) <<"]" <<endl;
      exit(1);
    }
    if (sigaction(SIGBUS, &act, &old_bus_act)<0) {
      ::simsoc::error() <<"[class Memory] " <<"Set SIGBUS handler Failed! errMsg=["
                        <<strerror(errno) <<"]" <<endl;
      exit(1);
    }
    sigsegv_handler_set = true;
  }

  void Memory::reset_sigsegv_handler() {
    if (!sigsegv_handler_set)
      return;
    ::simsoc::debug() <<"[class Memory] " <<"restore previous SIGSEGV handler" <<endl;
    if (sigaction(SIGSEGV, &old_segv_act, NULL)<0) {
      ::simsoc::error() <<"[class Memory] " <<"Reset SIGSEGV handler Failed! errMsg=["
                        <<strerror(errno) <<"]" <<endl;
      exit(1);
    }
    if (sigaction(SIGBUS, &old_bus_act, NULL)<0) {
      ::simsoc::error() <<"[class Memory] " <<"Reset SIGBUS handler Failed! errMsg=["
                        <<strerror(errno) <<"]" <<endl;
      exit(1);
    }
    sigsegv_handler_set = false;
  }

/******************************************************************************/
// SIGSEGV handler

void sigsegv_handler(int signo, siginfo_t *siginfo, void *ucontext) {
  //get the host address where signal raised
  uint8_t *sig_addr = (uint8_t*) siginfo->si_addr;
  map<uint8_t*, Memory*, greater<void*> >::iterator i = Memory::host_addresses.lower_bound(sig_addr);

  if (i==Memory::host_addresses.end()) {
    Memory::reset_sigsegv_handler();
    return;
  }

  uint32_t target_addr = sig_addr-i->first;

  if (target_addr >= i->second->size) {
    Memory::reset_sigsegv_handler();
    return;
  }

  i->second->invalidate_translated_codepage(target_addr);

  if (mprotect((void*)((size_t)sig_addr&~(size_t)(getpagesize()-1)),
               TranslationPage::TR_PAGE_SIZE,
               PROT_READ|PROT_WRITE)) {
    error() <<"[sigsegv_handler] "
            <<"mprotect error in sigsegv handler! errMsg=["<<strerror(errno)
            <<"]"<<endl;
    exit(2);
  }
}

} // namespace simsoc
