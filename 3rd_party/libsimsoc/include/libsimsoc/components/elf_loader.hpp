//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ELF_LOADER_HPP
#define ELF_LOADER_HPP

#include <libsimsoc/simsoc-config.h>

#include <libsimsoc/module.hpp>
#include <libsimsoc/processors/common.hpp>

#include <tlm_utils/multi_passthrough_initiator_socket.h>

#include <fstream>
#include <vector>
#include <map>
#include <inttypes.h>

#ifdef SIMSOC_HAVE_ELF_H
# include <elf.h>
#else
# include "libsimsoc/interfaces/elf.h"
#endif

namespace simsoc {

  struct ProcessorBase;

  struct Elf32_SectionHeader;

struct Elf32_Header: public Elf32_Ehdr {
  std::vector<Elf32_SectionHeader*> sections;
  char * strings;
  Elf32_SectionHeader* text;
  Elf32_SectionHeader* reginfo;
  Elf32_Header();
  ~Elf32_Header();
  bool is_elf();
  bool is_elf32();
  bool is_big_endian();
  void unencode();
  bool is_exec();
  void load_sections(std::ifstream &ifs);
  uint32_t get_gp_value(std::ifstream &ifs);
  size_t start_brk;
  uint32_t get_start_brk();
};

class ElfFile{
public:

  const char* file_name;

  ElfFile(const char* elf_file);

  ~ElfFile();

  Architecture get_architecture();

  MIPS_SpecFlag get_mips_spec();

  bool is_big_endian();

  bool is_elf32() {return header.is_elf32();}

  uint32_t get_start_address();

  uint32_t get_text_start();

  uint32_t get_text_size();

  uint32_t get_mips_gp();

  void load_sections(char *mem, const size_t max);

  uint32_t get_elf_brk();

  std::ifstream ifs;

  Elf32_Header header;

  bool loaded;

  size_t start_brk;
};

class ElfLoader: public Module {
public:

  tlm_utils::multi_passthrough_initiator_socket<ElfLoader, 32> initiator_sockets;

  ElfLoader(sc_core::sc_module_name name);
  void set_file(ProcessorBase *proc, const char* elf_file);
  void end_of_elaboration();

protected:
  void load_sections(ElfFile &elf_file, int id);

  struct Job {
    ProcessorBase *proc;
    const char *filename;
    int socket_id;
    Job(ProcessorBase *p, const char *f, int s): proc(p), filename(f), socket_id(s) {}
  };
  std::vector<Job> jobs;
};

} // namespace simsoc

#endif //ELF_LOADER_HPP
