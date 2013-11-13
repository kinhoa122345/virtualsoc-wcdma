//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// FIXME: this file describes the TLB of the ARM architecture version 5
// it should be replaced by a description of the TLB corresponding to version 6

#ifndef ARM_V5_TLB_HPP
#define ARM_V5_TLB_HPP

#include "arm_v5_systemcontrol_coproc.hpp"
#include <libsimsoc/processors/mmu.hpp>

namespace simsoc {

  typedef enum {
    ARMv6_NO_FAULT = 0x0,
    ARMv6_ALIGNMENT_FAULT = 0x1,
    ARMv6_SECTION_TRANSLATION_FAULT = 0x5,
    ARMv6_PAGE_TRANSLATION_FAULT = 0x7, 		//domain valide
    ARMv6_SECTION_DOMAIN_FAULT = 0x9,			//domain valide
    ARMv6_PAGE_DOMAIN_FAULT = 0xB, 			//domain valide
    ARMv6_SECTION_PERMISSION_FAULT = 0xD, 		//domain valide
    ARMv6_SUBPAGE_PERMISSION_FAULT = 0xF 		//domain valide
  } arm_v6_mmu_fault_t;

  //specify the mapping type. For different entries may have same page size
  typedef enum {
    ARMv6_TLB_INVALID =0,
    ARMv6_TLB_SECTION =1,
    ARMv6_TLB_LARGEPAGE =2,
    ARMv6_TLB_SMALLPAGE =3,
    ARMv6_TLB_TINYPAGE =4,
  } arm_v6_tlb_mapping_t;

  const uint32_t ARMv6_SECTION_MASK=  0x000FFFFF;
  const uint32_t ARMv6_LARGEPAGE_MASK=0x0000FFFF;
  const uint32_t ARMv6_SMALLPAGE_MASK=0x00000FFF;
  const uint32_t ARMv6_TINYPAGE_MASK= 0x000003FF;

  class ARMv6_TLBEntry: public TLBEntry<BUS32> {
  public:
    uint32_t phy_addr;
    uint32_t ap[4];
    uint32_t domain;
    uint32_t C;
    uint32_t B;

    arm_v6_tlb_mapping_t mapping_type;

    ARMv6_TLBEntry():
      TLBEntry<BUS32>(),
      phy_addr(0), ap(), domain(0), C(0), B(0),
      mapping_type(ARMv6_TLB_INVALID)
    {}

    uint32_t getPA(uint32_t va) {
      return phy_addr | (va & mask);
    }

    int getAP(uint32_t virt_addr) {
      return ap[0];
    }
  };

  class ARMv6_Section: public ARMv6_TLBEntry {
  public:
    ARMv6_Section(uint32_t va, uint32_t desc):
      ARMv6_TLBEntry()
    {
      mask = ARMv6_SECTION_MASK;
      mapping_type = ARMv6_TLB_SECTION;
      virt_addr = va & ~ARMv6_SECTION_MASK;
      phy_addr = desc & ~ARMv6_SECTION_MASK;
      ap[0] = bits<uint32_t>(desc,11,10);
      domain = bits<uint32_t>(desc,8,5);
      C = bit<uint32_t>(desc,3);
      B = bit<uint32_t>(desc,2);
    }
  };

  class ARMv6_LargePage: public ARMv6_TLBEntry {
  public:
    ARMv6_LargePage(uint32_t va, uint32_t desc, uint32_t _domain):
      ARMv6_TLBEntry()
    {
      mask = ARMv6_LARGEPAGE_MASK;
      mapping_type = ARMv6_TLB_LARGEPAGE;
      virt_addr = va & ~ARMv6_LARGEPAGE_MASK;
      phy_addr = desc & ~ARMv6_LARGEPAGE_MASK;
      domain = _domain;
      C = bit<uint32_t>(desc,3);
      B = bit<uint32_t>(desc,2);

      ap[0] = bits<uint32_t>(desc,5,4);
      ap[3] = bits<uint32_t>(desc,11,10);
      ap[2] = bits<uint32_t>(desc,9,8);
      ap[1] = bits<uint32_t>(desc,7,6);
    }

    int getAP(uint32_t va) {
      //page index[15:0],take bit[15:14] to decide the subpage
      uint32_t subpage = (va >> 14) & 3;
      return ap[subpage];
    }
  };

  class ARMv6_SmallPage: public ARMv6_TLBEntry{
  public:
    ARMv6_SmallPage(uint32_t va, uint32_t desc, uint32_t _domain):
      ARMv6_TLBEntry()
    {
      mask = ARMv6_SMALLPAGE_MASK;
      mapping_type = ARMv6_TLB_SMALLPAGE;
      virt_addr = va & ~ARMv6_SMALLPAGE_MASK;
      phy_addr = desc & ~ARMv6_SMALLPAGE_MASK;
      ap[3] = bits<uint32_t>(desc,11,10);
      ap[2] = bits<uint32_t>(desc,9,8);
      ap[1] = bits<uint32_t>(desc,7,6);
      ap[0] = bits<uint32_t>(desc,5,4);
      domain = _domain;
      C = bit<uint32_t>(desc,3);
      B = bit<uint32_t>(desc,2);
    }

    int getAP(uint32_t va) {
      //page index[11:0],take bit[11:10] to decide the subpage
      uint32_t subpage = (va>> 10) & 3;
      return ap[subpage];
    }
  };

  class ARMv6_TinyPage: public ARMv6_TLBEntry {
  public:
    ARMv6_TinyPage(uint32_t va, uint32_t desc, uint32_t _domain):
      ARMv6_TLBEntry()
    {
      mask = ARMv6_TINYPAGE_MASK;
      mapping_type = ARMv6_TLB_TINYPAGE;
      virt_addr = va & ~ARMv6_TINYPAGE_MASK;
      phy_addr = desc & ARMv6_TINYPAGE_MASK;
      ap[0] = bits<uint32_t>(desc,5,4);
      domain = _domain;
      C = bit<uint32_t>(desc,3);
      B = bit<uint32_t>(desc,2);
    }
  };

  class ARMv6_PageTable {
  public:
    uint32_t va;
    uint32_t base;
    uint32_t domain;
    ARMv6_PageTable(): va(0), base(0), domain(0) {}
    virtual uint32_t get_page_table_addr()=0;
    virtual ARMv6_TLBEntry* parse_page_entry(uint32_t desc)=0;
    virtual ~ARMv6_PageTable(){};
  };

  class ARMv6_CoarsePage: public ARMv6_PageTable {
  public:
    ARMv6_CoarsePage(uint32_t _va,uint32_t _desc):
      ARMv6_PageTable()
    {
      va = _va;
      base = topbits<uint32_t>(_desc,10);
      domain = bits<uint32_t>(_desc,8,5);
    }

    uint32_t get_page_table_addr() {
      return (base | bits<uint32_t>(va,19,10)) & ~3; //va[19:12] and 00 so get va[19:10]
    }

    ARMv6_TLBEntry* parse_page_entry(uint32_t desc) {
      switch(bits<uint32_t>(desc,1,0)) {
      case 0:
        throw MMU_Faults<BUS32>(va,ARMv6_PAGE_TRANSLATION_FAULT,domain);
      case 1:
        return new ARMv6_LargePage(va,desc,domain);
        break;
      case 2:
        return new ARMv6_SmallPage(va,desc,domain);
        break;
      case 3:
        return new ARMv6_TinyPage(va,desc,domain);
        break;
      default:
        assert(false);
        return NULL;
      }
    }
  };

  class ARMv6_FinePage: public ARMv6_PageTable {
  public:
    ARMv6_FinePage(uint32_t _va, uint32_t _desc):
      ARMv6_PageTable()
    {
      va = _va;
      base = topbits<uint32_t>(_desc,12);
      domain = bits<uint32_t>(_desc,8,5);
    }

    uint32_t get_page_table_addr() {
      return (base | bits<uint32_t>(va,19,8)) & ~3; //va[19:10] and 00 so get va[19:8]
    }

    ARMv6_TLBEntry* parse_page_entry(uint32_t desc) {
      switch(bits<uint32_t>(desc,1,0)) {
      case 0:
        throw MMU_Faults<BUS32>(va,ARMv6_PAGE_TRANSLATION_FAULT,domain);
      case 1:
        return new ARMv6_LargePage(va,desc,domain);
        break;
      case 2:
        return new ARMv6_SmallPage(va,desc,domain);
        break;
      case 3:
        return new ARMv6_TinyPage(va,desc,domain);
        break;
      default:
        assert(false);
        return NULL;
      }
    }
  };

  class ARMv6_TLB: public TLB<BUS32> {
  public:
    bool isLock;
    ARMv6_TLB* next;

    ARMv6_TLB(const char* tlb_name, uint32_t tlb_size, bool lockable_=false);
    ~ARMv6_TLB(){};
    TLBEntry<uint32_t> **search_entry(uint32_t virt_addr);
    void add_entry(TLBEntry<uint32_t> *entry, uint32_t index);
    void invalidate_all_entries();
    void invalidate_single_entry(uint32_t virt_addr);
  };

} // namespace simsoc

#endif // ARM_V5_TLB_HPP
