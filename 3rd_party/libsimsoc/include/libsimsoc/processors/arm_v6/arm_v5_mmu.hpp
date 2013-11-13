//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// FIXME: this file describes the MMU of the ARM architecture version 5
// it should be replaced by a description of the MMU corresponding to version 6

#ifndef ARM_V5_MMU_HPP
#define ARM_V5_MMU_HPP

#include "arm_v6_coproc.hpp"
#include "arm_v5_tlb.hpp"
#include "libsimsoc/interfaces/dmi.hpp"

namespace simsoc {

  class ARMv6_MMU: public MMU<BUS32>
  {
    int ID,TILE_ID;
  public:
    typedef uint32_t word_t;

    ARMv6_SystemCoproc &cp15;

    TLBEntry<word_t> **saved_entry;

    // initilization
    ARMv6_MMU(sc_core::sc_module_name name, ARMv6_Processor *proc_,int ID,int TILE_ID);
    ~ARMv6_MMU();

    uint32_t virt_to_phy(uint32_t va,
                         mmu_data_type data_type /*used to check alignment*/,
                         mem_op_type op_type /*used to check permission*/,
                         TLB<word_t> *tlbs);

    // all check information from cp15
    inline bool data_preprocess_and_is_enabled(uint32_t& va) const {
      if (topbits<uint32_t>(va,25)==0)
        va |= cp15.get_pid();
      return cp15.is_mmu_enabled();
    }

    inline bool is_bigendian() const {
      return cp15.is_big_endian();
    }

    void check_access(uint32_t va,
                      TLBEntry<word_t> *tlbEntry,
                      mem_op_type op_type);

    int check_perms (int ap, int write);

    void check_alignment(uint32_t va, mmu_data_type data_type);

  public:

    bool getTLBs();


    TLBEntry<word_t> *translation_table_walk(uint32_t va,
                                             mmu_data_type data_type);

    void handle_data_faults(uint32_t virt_addr,
                            uint32_t fault,
                            uint32_t domain,
                            mem_op_type op_type=MMU_READ);

    void handle_instruction_faults(uint32_t virt_addr,
                                   uint32_t fault,
                                   uint32_t domain,
                                   mem_op_type op_type=MMU_READ);

    // code partly inlined
    inline uint32_t read_word(uint32_t va);
    uint32_t read_word__mmu(uint32_t va); // this part is not inlined
    inline void write_word(uint32_t va, uint32_t data);
    void write_word__mmu(uint32_t va, uint32_t data);

    inline void fetch_page(word_t virtual_page_id, //input
                           uint32_t *&target_code, //output
                           TranslationTableItem *&translated_page); //output

  }; // class ARMv6_MMU

  // code duplicated to check if it improves performances
  void ARMv6_MMU::fetch_page(word_t virtual_page_id, //input
                             uint32_t *&target_code, //output
                             TranslationTableItem *&translated_page) //output
  {
    word_t va = virtual_page_id * TranslationPage::TR_PAGE_SIZE;
    word_t pa;
    if (topbits<uint32_t>(va,25)==0)
      va |= cp15.get_pid();
    if (cp15.is_mmu_enabled()) {
      try {
        pa = virt_to_phy(va,MMU_WORD_TYPE,MMU_READ,iTLBs);
      } catch(MMU_Faults<word_t>& faults) {
        target_code = NULL;
        translated_page = NULL;
        // Take care: it is forbidden to raise an interrupt in fetch page!
        // Do not do that: handle_instruction_faults(faults.virt_addr,faults.fault,faults.domain);
        return;
      }
      debug() <<std::hex <<"fetch page [" <<virtual_page_id <<"]->["
              <<pa/TranslationPage::TR_PAGE_SIZE <<"]\n";
    } else {
      debug() <<std::hex <<"fetch page [" <<virtual_page_id <<"]\n";
      pa = va;
    }
    if (!hmemory.has_instruction_cache(pa))
      get_dmi_at_address(pa);
    if (hmemory.has_instruction_cache(pa)) {
      target_code = hmemory.raw32(pa);//todo:just for 32bit instruction now
      translated_page =
        &(*hmemory.get_code_table(pa))
        [hmemory.relative(pa)/TranslationPage::TR_PAGE_SIZE];
    } else {
      target_code = NULL;
      translated_page = NULL;
    }
  }
  
  // code duplicated to check if it improves performances (edit: it looks so)
  uint32_t ARMv6_MMU::read_word(word_t va) {
    if (topbits<uint32_t>(va,25)==0)
      va |= cp15.get_pid();
    if (!cp15.is_mmu_enabled()) {
      uint32_t data=memory_read_word(va);
      debug() <<std::hex <<"read word at [" <<va <<"] return " <<data <<std::endl;
      return data;
    } else {
      return read_word__mmu(va);
    }
  }

  // code duplicated to check if it improves performances (edit: it looks so)
  void ARMv6_MMU::write_word(word_t va,uint32_t data) {
    if (topbits<uint32_t>(va,25)==0)
      va |= cp15.get_pid();
    if (!cp15.is_mmu_enabled()) {
      debug() <<std::hex <<"write word " <<data <<" at [" <<va <<"]" <<std::endl;
      memory_write_word(va,data);
    } else {
      write_word__mmu(va,data);
    }
  }

} // namespace simsoc

#endif //ARM_V5_MMU_HPP
