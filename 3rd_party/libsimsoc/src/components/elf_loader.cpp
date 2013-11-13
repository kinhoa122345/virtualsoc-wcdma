//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifdef HAVE_CONFIG_H
# include "libsimsoc/config.h"
#endif

#include "libsimsoc/components/elf_loader.hpp"

#include <libsimsoc/display.hpp>
#include <libsimsoc/processors/processor_base.hpp>
//#include <libsimsoc/processors/mips/mips_processor.hpp>

#if defined(HAVE_BYTESWAP_H)
# include <byteswap.h>
#elif defined(HAVE_COREFOUNDATION_COREFOUNDATION_H)
# include "CoreFoundation/CoreFoundation.h"
static inline uint32_t bswap_32(uint32_t n) {return CFSwapInt32(n);}
static inline uint16_t bswap_16(uint16_t n) {return CFSwapInt16(n);}
#else
# error "No bswap_32 and bswap_16 functions are available."
#endif

using namespace std;
using namespace sc_core;

namespace simsoc {

/******************************************************************************/
struct Elf32_Mips_reginfo: public Elf32_RegInfo {

  void unencode() {
    ri_gprmask = bswap_32(ri_gprmask);
    for (size_t i = 0; i<4; ++i)
      ri_cprmask[i] = bswap_32(ri_cprmask[i]);
    ri_gp_value = bswap_32(ri_gp_value);
  }

  uint32_t get_gp_value() {
    return ri_gp_value;
  }
};

/******************************************************************************/
struct Elf32_SectionHeader: public Elf32_Shdr {

  const char *name;

  void unencode() {
    sh_name = bswap_32(sh_name);
    sh_type = bswap_32(sh_type);
    sh_flags = bswap_32(sh_flags);
    sh_addr = bswap_32(sh_addr);
    sh_offset = bswap_32(sh_offset);
    sh_size = bswap_32(sh_size);
    sh_link = bswap_32(sh_link);
    sh_info = bswap_32(sh_info);
    sh_addralign = bswap_32(sh_addralign);
    sh_entsize = bswap_32(sh_entsize);
  }

  size_t start() {
    return sh_addr;
  }

  size_t size() {
    return sh_size;
  }

  size_t file_offset() {
    return sh_offset;
  }

  const char *str_type(Elf32_Half machine) {
    switch (sh_type) {
    case SHT_NULL: return "NULL";
    case SHT_PROGBITS: return "PROGBITS";
    case SHT_SYMTAB: return "SYMTAB";
    case SHT_STRTAB: return "STRTAB";
    case SHT_NOBITS: return "NOBITS";
    case SHT_MIPS_REGINFO:
      if (machine==EM_MIPS)
        return "REGINFO";
      else {
        debug() <<HERE <<"sh_type = " <<hex <<sh_type <<endl;
        return "other";
      }
    default:
      debug() <<HERE <<"sh_type = " <<hex <<sh_type <<endl;
      return "other";
    }
  }

  bool is_load() {
    return (sh_flags&SHF_ALLOC) && sh_type==SHT_PROGBITS;
  }

  bool is_alloc(){
    return (sh_flags&SHF_ALLOC);
  }

  bool is_reginfo(Elf32_Half machine) {
    return machine==EM_MIPS && sh_type==SHT_MIPS_REGINFO;
  }
};

/******************************************************************************/
Elf32_Header::Elf32_Header() {
  strings = NULL;
  text = NULL;
  reginfo = NULL;
  start_brk = 0;
}

Elf32_Header::~Elf32_Header() {
  for (size_t i = 0; i<sections.size(); ++i)
    delete sections[i];
  delete[] strings;
}

bool Elf32_Header::is_elf() {
  return
    e_ident[EI_MAG0]==ELFMAG0 &&
    e_ident[EI_MAG1]==ELFMAG1 &&
    e_ident[EI_MAG2]==ELFMAG2 &&
    e_ident[EI_MAG3]==ELFMAG3;
}

bool Elf32_Header::is_elf32() {
  return e_ident[EI_CLASS]==ELFCLASS32;
}

bool Elf32_Header::is_big_endian() {
  return e_ident[EI_DATA]==ELFDATA2MSB;
}

void Elf32_Header::unencode() {
  if (!is_big_endian())
    return;
  e_type = bswap_16(e_type);
  e_machine = bswap_16(e_machine);
  e_version = bswap_32(e_version);
  e_entry = bswap_32(e_entry);
  e_phoff = bswap_32(e_phoff);
  e_shoff = bswap_32(e_shoff);
  e_flags = bswap_32(e_flags);
  e_ehsize = bswap_16(e_ehsize);
  e_phentsize = bswap_16(e_phentsize);
  e_phnum = bswap_16(e_phnum);
  e_shentsize = bswap_16(e_shentsize);
  e_shnum = bswap_16(e_shnum);
  e_shstrndx = bswap_16(e_shstrndx);
}

bool Elf32_Header::is_exec() {
  return e_type==ET_EXEC;
}

  uint32_t Elf32_Header::get_start_brk(){
    for (size_t i = 0; i<sections.size(); ++i) {
      if (sections[i]->is_alloc()) {
        uint32_t mem_start = sections[i]->start();
        uint32_t mem_size = sections[i]->size();
        uint32_t mem_end = mem_start+mem_size;
        if(start_brk < mem_end)
          start_brk = mem_end;
      }
    }
    return start_brk;
  }

void Elf32_Header::load_sections(ifstream &ifs) {
  if (e_shentsize!=sizeof(Elf32_Shdr))
    UNREACHABLE;
  ifs.seekg(e_shoff);
  if (!ifs)
    UNREACHABLE;
  for (size_t i = 0; i<e_shnum; ++i) {
    sections.push_back(new Elf32_SectionHeader());
    ifs.read((char*) sections[i], sizeof(Elf32_Shdr));
    if (!ifs)
      UNREACHABLE;
    if (is_big_endian())
      sections[i]->unencode();
  }
  if (e_shstrndx>=sections.size())
    UNREACHABLE;
  strings = new char[sections[e_shstrndx]->size()];
  ifs.seekg(sections[e_shstrndx]->file_offset());
  if (!ifs)
    UNREACHABLE;
  ifs.read(strings,sections[e_shstrndx]->size());
  if (!ifs)
    UNREACHABLE;
  for (size_t i = 0; i<e_shnum; ++i) {
    sections[i]->name = strings+sections[i]->sh_name;
    debug() <<HERE <<"section " <<dec <<i <<": " <<sections[i]->name
           <<'\t' <<sections[i]->str_type(e_machine)
           <<(sections[i]->is_load()? " (load)": "")
           <<endl;
    if (!strcmp(".text",sections[i]->name))
      text = sections[i];
    if (sections[i]->is_reginfo(e_machine))
      reginfo = sections[i];
  }
  if (!text)
    UNREACHABLE;
}

uint32_t Elf32_Header::get_gp_value(ifstream &ifs) {
  Elf32_Mips_reginfo ri;
  ifs.seekg(reginfo->file_offset());
  if (!ifs)
    UNREACHABLE;
  if (sizeof(Elf32_RegInfo)!=reginfo->size())
    UNREACHABLE;
  ifs.read((char*)&ri,sizeof(Elf32_RegInfo));
  if (!ifs)
    UNREACHABLE;
  if (is_big_endian())
    ri.unencode();
  return ri.get_gp_value();
}

/******************************************************************************/
ElfFile::ElfFile(const char *elf_file):
  file_name(elf_file),
  ifs(file_name,ios::in|ios::binary),
  loaded(false),
  start_brk(0)
{
  if (!ifs) {
    error() <<"failed to open file " <<file_name <<endl;
    exit(1);
  }
  ifs.read((char*) &header, sizeof(Elf32_Ehdr));
  if (!ifs)
    UNREACHABLE;
  if (!header.is_elf()) {
    error() <<file_name <<" is not an ELF file\n";
    exit(1);
  }
  if (!header.is_elf32()) {
    TODO("64-bit ELF file");
  }
  header.unencode();
  if (!header.is_exec()) {
    error() <<file_name <<" is not an executable ELF file\n";
    exit(1);
  }
  header.load_sections(ifs);

}

ElfFile::~ElfFile() {
  ifs.close();
  debug() <<"ElfFile destructor called" <<endl;
}

Architecture ElfFile::get_architecture() {
  switch (header.e_machine) {
  case EM_MIPS:
    return MIPS;
  case EM_ARM:
    return ARM;
  case EM_PPC:
    return POWERPC;
  default:
    info() <<"e_machine = " <<header.e_machine <<endl;
    return LAST_ARCH;
  }
}

MIPS_SpecFlag ElfFile::get_mips_spec(){
  if((header.e_flags & EF_MIPS_ARCH)<=0x50000000)
    return MIPS32;
  else if((header.e_flags & EF_MIPS_ARCH)==0x60000000)
    return MIPS64;
  else{ info()<<"MIPS 32 and 64 Revision 2  or newer instruction set are not supported yet. " \
                          "e_flag= "<<(header.e_flags & EF_MIPS_ARCH)<<endl;
  exit(1);
  }
}

bool ElfFile::is_big_endian() {
  return header.is_big_endian();
}

uint32_t ElfFile::get_start_address() {
  return header.e_entry;
}

uint32_t ElfFile::get_text_start() {
  return header.text->sh_addr;
}

uint32_t ElfFile::get_text_size() {
  return header.text->size();
}

uint32_t ElfFile::get_mips_gp() {
  return header.get_gp_value(ifs);
}

  void ElfFile::load_sections(char *dst, const size_t max) {
    for (size_t i = 0; i<header.sections.size(); ++i) {
      uint32_t mem_start = header.sections[i]->start();
      uint32_t mem_size = header.sections[i]->size();
      uint32_t mem_end = mem_start+mem_size;
      if (header.sections[i]->is_load()) {
        ifs.seekg(header.sections[i]->file_offset());
        if (!ifs)
          UNREACHABLE;
        info() <<hex <<"write from " <<mem_start <<" to "
               <<mem_end <<endl;
        char * tmp = new char[mem_size];
        ifs.read(tmp, mem_size);
        if (!ifs)
          UNREACHABLE;
        for (uint32_t j = 0; j<mem_size; ++j) {
          uint64_t addr;
          if (get_architecture()==MIPS && get_mips_spec()==MIPS64)
            addr = sign_ext<uint64_t>(mem_start+j);
          else
            addr = mem_start+j;
          assert(addr<max);
          dst[addr] = tmp[j];
        }
        delete[] tmp;
      }
      if(header.sections[i]->is_alloc()){
        if(start_brk < mem_end)
          start_brk = mem_end;
      }
    }
    loaded=true;
  }

  uint32_t ElfFile::get_elf_brk(){
    if(loaded)
      return start_brk;
    else{
      //header sections already been loaded in ElfFile Constructor
      start_brk=header.get_start_brk();
      return start_brk;
    }
  }


/*****************************************************************************/
  void ElfLoader::load_sections(ElfFile &elf_file, int socket_id) {
    tlm::tlm_generic_payload trans;
    trans.set_streaming_width(1);
    trans.set_command(tlm::TLM_WRITE_COMMAND);
    if (elf_file.loaded)
      return;
    for (size_t i = 0; i<elf_file.header.sections.size(); ++i) {
      uint32_t mem_start = elf_file.header.sections[i]->start();
      uint32_t mem_size = elf_file.header.sections[i]->size();
      uint32_t mem_end = mem_start+mem_size;
      if (elf_file.header.sections[i]->is_load()) {
        elf_file.ifs.seekg(elf_file.header.sections[i]->file_offset());
        if (!elf_file.ifs)
          UNREACHABLE;
        info() <<hex <<"write from " <<mem_start <<" to "
               <<mem_end <<endl;
        char * tmp = new char[mem_size];
        elf_file.ifs.read(tmp, mem_size);
        if (!elf_file.ifs)
          UNREACHABLE;
        trans.set_data_length(mem_size);
        trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
        if (elf_file.get_architecture()==MIPS && elf_file.get_mips_spec()==MIPS64)
          trans.set_address(sign_ext<uint64_t>(mem_start));
        else
          trans.set_address(mem_start);
        trans.set_data_ptr(reinterpret_cast<uint8_t*>(tmp));
        const unsigned int n = initiator_sockets[socket_id]->transport_dbg(trans);
        assert(n==mem_size && "transaction failed");
        delete[] tmp;
      }
      if(elf_file.header.sections[i]->is_alloc()){
        if(elf_file.start_brk < mem_end)
          elf_file.start_brk = mem_end;
      }
    }
    elf_file.loaded = true;
  }

  ElfLoader::ElfLoader(sc_core::sc_module_name name):
    Module(name,WARNING_LEVEL),
    jobs()
  {}

  void ElfLoader::set_file(ProcessorBase *proc, const char* elf_file) {
    assert(proc && elf_file && "invalid parameters");
    int sid = jobs.size();
    #ifndef NO_MMU
    initiator_sockets(proc->debug_port);
    #endif
    if (strcmp(elf_file,"NoELF"))
      jobs.push_back(Job(proc,elf_file,sid));
  }

  void ElfLoader::end_of_elaboration() {
    for (size_t i=0, ei=jobs.size(); i!=ei; ++i) {
      ProcessorBase *proc = jobs[i].proc;
      ElfFile elf_file(jobs[i].filename);
      if (elf_file.is_big_endian())
        proc->set_endian_big();
      else
        proc->set_endian_little();
      load_sections(elf_file,jobs[i].socket_id);
      if (elf_file.get_architecture()==MIPS) {
        if (elf_file.get_mips_spec()==MIPS32) {
          if(elf_file.header.reginfo){
            const uint32_t gp = elf_file.get_mips_gp();
            info() <<"initialize register gp of the MIPS processor with value: "
                 <<hex <<gp <<endl;
                 //static_cast<MIPS_Processor<BUS32>*>(proc)->set_GP_register(gp);
          }
          proc->set_pc(elf_file.get_start_address());
        } else {
          const uint64_t gp = sign_ext<uint64_t>(elf_file.get_mips_gp());
          info() <<"initialize register gp of the MIPS processor with value: "
                 <<hex <<gp <<endl;
          //static_cast<MIPS_Processor<BUS64>*>(proc)->set_GP_register(gp);
          proc->set_pc(sign_ext<uint64_t>(elf_file.get_start_address()));
        }
      } else {//other architecture
        proc->set_pc(elf_file.get_start_address());
      }
    }
  }

} // namespace simsoc
