//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/interfaces/dmi.hpp"

#ifndef HOST_MEMORY_HPP
#define HOST_MEMORY_HPP

namespace simsoc {

  template < typename word_t >
  class HostMemory {

    class DMI_Descriptor {
    public:
      DMI_Descriptor()
      {
        this->set(0, 0, 0, NULL);
      }

      DMI_Descriptor(uint8_t *memory,
                     word_t   size  ,
                     word_t   offset,
                     TranslationTable *code_table)
      {
        this->set(memory, size, offset, code_table);
      }

      inline word_t get_size  () const { return m_size  ; }
      inline word_t get_offset() const { return m_offset; }
      inline word_t get_end   () const { return m_end   ; }
      inline uint8_t* get_memory() const { return m_memory; }
      inline TranslationTable *get_code_table() const {return m_code_table;}

      void set(uint8_t *memory, word_t size, word_t offset,
               TranslationTable *code_table) {
        m_memory     = memory;
        m_size       = size;
        m_offset     = offset;
        m_end        = offset+size;
        m_code_table = code_table;
      }

      inline bool dmi_address(word_t address) const {
        return m_offset<=address && address <m_end;
      }

    protected:
      uint8_t *m_memory;
      word_t   m_size;
      word_t   m_offset;
      word_t   m_end;
      TranslationTable *m_code_table; // for dynamic translation
    }; // class DMI_Descriptor

  public:
    HostMemory():
      dmi_descriptors(),
      m_memory(NULL), m_code_table(NULL), m_offset(~0), m_end(0)
    {}

    inline void reset() {
      dmi_descriptors.clear();
      m_memory = NULL; m_code_table = NULL; m_offset = ~0; m_end = 0;
    }

    inline void add_dmi(uint8_t *memory,
                        word_t   size  ,
                        word_t   offset,
                        TranslationTable *code_table) {
      info() <<"add_dmi: " <<std::hex <<(intptr_t) memory <<", " <<size <<", "
             <<offset <<", " <<(intptr_t) code_table <<".\n";
      dmi_descriptors.push_back(DMI_Descriptor(memory,size,offset,code_table));
    }

    inline bool dmi_address(word_t address) {
#ifndef NDEBUG
      last_addr = address;
#endif
      if (m_end>address && address>=m_offset)
        return true;
      for (size_t i = 0, ei = dmi_descriptors.size(); i!=ei; ++i) {
        if (dmi_descriptors[i].dmi_address(address)) {
          m_code_table = dmi_descriptors[i].get_code_table();
          m_memory = dmi_descriptors[i].get_memory();
          m_offset = dmi_descriptors[i].get_offset();
          m_end = dmi_descriptors[i].get_end();
          return true;
        }
      }
      return false;
    }

    inline bool has_instruction_cache(word_t address) {
#ifndef NDEBUG
      last_addr = address; // FOR DEBUG
#endif
      if (m_end>address && address>=m_offset)
        return m_code_table!=NULL;
      return dmi_address(address) && m_code_table!=NULL;
    }

    inline /*-*/ uint8_t* raw(word_t a) /*-*/ { assert(a==last_addr); return m_memory + (a - m_offset); }
    inline const uint8_t* raw(word_t a) const { assert(a==last_addr); return m_memory + (a - m_offset); }

    inline /*-*/ uint16_t* raw16(word_t a) /*-*/ { assert(a==last_addr); return (uint16_t*) raw(a); }
    inline const uint16_t* raw16(word_t a) const { assert(a==last_addr); return (uint16_t*) raw(a); }

    inline /*-*/ uint32_t* raw32(word_t a) /*-*/ { assert(a==last_addr); return (uint32_t*) raw(a); }
    inline const uint32_t* raw32(word_t a) const { assert(a==last_addr); return (uint32_t*) raw(a); }

    inline /*-*/ uint64_t* raw64(word_t a) /*-*/ { assert(a==last_addr); return (uint64_t*) raw(a); }
    inline const uint64_t* raw64(word_t a) const { assert(a==last_addr); return (uint64_t*) raw(a); }

    inline uint8_t& operator[](word_t a) /*-*/ { assert(a==last_addr); return m_memory[a-m_offset]; }
    inline uint8_t  operator[](word_t a) const { assert(a==last_addr); return m_memory[a-m_offset]; }

    inline word_t relative(word_t address) const {
      assert(address==last_addr);
      return address - m_offset;
    }

    inline word_t get_offset(word_t a) const { assert(a==last_addr); return m_offset; }

    inline TranslationTable *get_code_table(word_t a) const { assert(a==last_addr); return m_code_table; }

  protected:
    std::vector<DMI_Descriptor> dmi_descriptors;
    uint8_t *m_memory;
    TranslationTable *m_code_table; // for dynamic translation
    word_t   m_offset;
    word_t   m_end;
    word_t last_addr;
  }; // class host_memory

} // namespace simsoc

#endif // HOST_MEMORY_HPP
