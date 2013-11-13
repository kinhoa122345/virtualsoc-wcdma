//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARM_TLB_HPP
#define ARM_TLB_HPP

#include "libsimsoc/processors/mmu.hpp"
#include "libsimsoc/processors/arm/arm_systemcontrol_coproc.hpp"

namespace simsoc {

  typedef enum arm_mmu_fault_t
    {
      NO_FAULT = 0x0,
      ALIGNMENT_FAULT = 0x1,
      SECTION_TRANSLATION_FAULT = 0x5,
      PAGE_TRANSLATION_FAULT = 0x7, 		//domain valide
      SECTION_DOMAIN_FAULT = 0x9,			//domain valide
      PAGE_DOMAIN_FAULT = 0xB, 			//domain valide
      SECTION_PERMISSION_FAULT = 0xD, 		//domain valide
      SUBPAGE_PERMISSION_FAULT = 0xF 		//domain valide
    } arm_mmu_fault_t;

  //specify the mapping type. For different entries may have same page size
  typedef enum tlb_mapping_t
    {
      TLB_INVALID =0,
      TLB_SECTION =1,
      TLB_LARGEPAGE =2,
      TLB_SMALLPAGE =3,
      TLB_TINYPAGE =4,
    } tlb_mapping_t;

  const uint32_t SECTION_MASK=  0x000FFFFF;
  const uint32_t LARGEPAGE_MASK=0x0000FFFF;
  const uint32_t SMALLPAGE_MASK=0x00000FFF;
  const uint32_t TINYPAGE_MASK= 0x000003FF;


  class ARM_TLBEntry:public TLBEntry<BUS32>
  {
  public:
    uint32_t phy_addr;
    uint32_t ap[4];
    uint32_t domain;
    uint32_t C;
    uint32_t B;

    tlb_mapping_t mapping_type;

    ARM_TLBEntry():TLBEntry<BUS32>(),
                   phy_addr(0), ap(), domain(0), C(0), B(0)
                  ,mapping_type(TLB_INVALID)
    {
    };

    uint32_t getPA(uint32_t va) {
      return phy_addr | (va & mask);
    };

    int getAP(uint32_t virt_addr)
    {
      return ap[0];
    };
  } ;


  class Section:public ARM_TLBEntry{
  public:
    Section(uint32_t va,uint32_t desc):ARM_TLBEntry(){
      mask=SECTION_MASK;
      mapping_type=TLB_SECTION;
      virt_addr = va & ~SECTION_MASK;
      phy_addr = desc & ~SECTION_MASK;
      ap[0] = bits<uint32_t>(desc,11,10);
      domain = bits<uint32_t>(desc,8,5);
      C=bit<uint32_t>(desc,3);
      B=bit<uint32_t>(desc,2);
    };
  };

  class LargePage:public ARM_TLBEntry{
  public:
    LargePage(uint32_t va,uint32_t desc,uint32_t _domain):ARM_TLBEntry(){
      mask=LARGEPAGE_MASK;
      mapping_type=TLB_LARGEPAGE;
      virt_addr = va & ~LARGEPAGE_MASK;
      phy_addr = desc & ~LARGEPAGE_MASK;
      domain = _domain;
      C=bit<uint32_t>(desc,3);
      B=bit<uint32_t>(desc,2);

      ap[0]=bits<uint32_t>(desc,5,4);
      ap[3]=bits<uint32_t>(desc,11,10);
      ap[2]=bits<uint32_t>(desc,9,8);
      ap[1]=bits<uint32_t>(desc,7,6);
    };

    int getAP(uint32_t va){
      uint32_t subpage = (va >> 14) & 3; //page index[15:0],take bit[15:14] to decide the subpage
      return ap[subpage];
    }
  };

  class SmallPage:public ARM_TLBEntry{
  public:
    SmallPage(uint32_t va,uint32_t desc,uint32_t _domain):ARM_TLBEntry(){
      mask=SMALLPAGE_MASK;
      mapping_type=TLB_SMALLPAGE;
      virt_addr = va & ~SMALLPAGE_MASK;
      phy_addr = desc & ~SMALLPAGE_MASK;
      ap[3]= bits<uint32_t>(desc,11,10);
      ap[2]= bits<uint32_t>(desc,9,8);
      ap[1]= bits<uint32_t>(desc,7,6);
      ap[0]= bits<uint32_t>(desc,5,4);
      domain = _domain;
      C=bit<uint32_t>(desc,3);
      B=bit<uint32_t>(desc,2);
    };

    int getAP(uint32_t va){
      uint32_t subpage = (va>> 10) & 3; //page index[11:0],take bit[11:10] to decide the subpage
      return ap[subpage];
    };
  };

  class TinyPage:public ARM_TLBEntry{
  public:
    TinyPage(uint32_t va,uint32_t desc,uint32_t _domain):ARM_TLBEntry(){
      mask=TINYPAGE_MASK;
      mapping_type=TLB_TINYPAGE;
      virt_addr = va & ~TINYPAGE_MASK;
      phy_addr = desc & TINYPAGE_MASK;
      ap[0]= bits<uint32_t>(desc,5,4);
      domain = _domain;
      C=bit<uint32_t>(desc,3);
      B=bit<uint32_t>(desc,2);
    };
  };


  class PageTable{
  public:
    uint32_t va;
    uint32_t base;
    uint32_t domain;
    PageTable():va(0),base(0),domain(0){};
    virtual uint32_t get_page_table_addr()=0;
    virtual ARM_TLBEntry* parse_page_entry(uint32_t desc)=0;
    virtual ~PageTable(){};
  };

  class CoarsePage:public PageTable
  {
  public:
    CoarsePage(uint32_t _va,uint32_t _desc):PageTable(){
      va=_va;
      base=topbits<uint32_t>(_desc,10);
      domain=bits<uint32_t>(_desc,8,5);
    };

    uint32_t get_page_table_addr()
    {
      return (base | bits<uint32_t>(va,19,10)) & ~3; //va[19:12] and 00 so get va[19:10]
    };

    ARM_TLBEntry* parse_page_entry(uint32_t desc){
      switch(bits<uint32_t>(desc,1,0))
        {
        case 0:
          throw MMU_Faults<BUS32>(va,PAGE_TRANSLATION_FAULT,domain);
        case 1:
          return new LargePage(va,desc,domain);
          break;
        case 2:
          return new SmallPage(va,desc,domain);
          break;
        case 3:
          return new TinyPage(va,desc,domain);
          break;
        default:
          assert(false);
          return NULL;
        }
    };
  };

  class FinePage:public PageTable
  {
  public:
    FinePage(uint32_t _va,uint32_t _desc):PageTable(){
      va=_va;
      base=topbits<uint32_t>(_desc,12);
      domain=bits<uint32_t>(_desc,8,5);
    };

    uint32_t get_page_table_addr()
    {
      return (base | bits<uint32_t>(va,19,8)) & ~3; //va[19:10] and 00 so get va[19:8]
    };

    ARM_TLBEntry* parse_page_entry(uint32_t desc){
      switch(bits<uint32_t>(desc,1,0))
        {
        case 0:
          throw MMU_Faults<BUS32>(va,PAGE_TRANSLATION_FAULT,domain);
        case 1:
          return new LargePage(va,desc,domain);
          break;
        case 2:
          return new SmallPage(va,desc,domain);
          break;
        case 3:
          return new TinyPage(va,desc,domain);
          break;
        default:
          assert(false);
          return  NULL;

        }
    };
  };

  class ARM_TLB: public TLB<BUS32> {
  public:
    typedef uint32_t word_t;
    bool isLock;
    ARM_TLB* next;

    ARM_TLB(const char* tlb_name, uint32_t tlb_size,
            bool lockable_=false);
    ~ARM_TLB(){};
    TLBEntry<word_t> **search_entry(word_t virt_addr);
    void add_entry(TLBEntry<word_t> *entry, word_t index);
    void invalidate_all_entries();
    void invalidate_single_entry(word_t virt_addr);
  };

} // namespace simsoc

#endif // ARM_TLB_HPP
