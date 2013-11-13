//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "libsimsoc/interfaces/dmi.hpp"
#include "libsimsoc/translation_table.hpp"
#include "libsimsoc/module.hpp"
#include <tlm.h>
#include <tlm_utils/simple_target_socket.h>
#include <list>
#include <set>
#include <signal.h>
#include <map>
#include <algorithm>

namespace simsoc {

class Memory: public Module {
  // On some systems, a write access to read-only memory raises a SIGSEGV,
  // in some others, it raises a SIGBUS, so we redefine both.
  static struct sigaction act,old_segv_act,old_bus_act;
  static bool sigsegv_handler_set;

public:
  // host addresses to Memory modules mapping (used by the sigsev handler)
  static std::map<uint8_t*, Memory*, std::greater<void*> > host_addresses;

  static void set_sigsegv_handler();
  static void reset_sigsegv_handler();

  unsigned size; // number of bytes
  tlm_utils::simple_target_socket<Memory> rw_socket;

  // Size and uint32_tes are given in byte.
  Memory(sc_core::sc_module_name name,
         unsigned size_);
  ~Memory();

  // RW_Target methods
  void b_transport(tlm::tlm_generic_payload &payload,
                          sc_core::sc_time &delay_time);
  unsigned int transport_dbg(tlm::tlm_generic_payload& pl);
  bool get_direct_mem_ptr(tlm::tlm_generic_payload &payload,
                          tlm::tlm_dmi &dmi_data);

  inline void trans_read_data(tlm::tlm_generic_payload &pl);
  inline void trans_write_data(tlm::tlm_generic_payload &pl);

  uint8_t *get_host_address();
  void load_image(const char *file_name, uint32_t address);

  void dump(uint32_t start,
            uint32_t length = 4,
            std::ostream& os = std::cout);

  void invalidate_translated_codepage(uint32_t addr);

protected:
  void clean_invalidated_pages();
  uint8_t * mem;
  TranslationTable translation_table;
  std::list<TranslationPage*> invalidated_pages;
  std::list<Processor*> translation_code_users;
};

} // namespace simsoc

#endif //MEMORY_HPP
