//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARM_V6_TRANSLATION_PAGE_HPP
#define ARM_V6_TRANSLATION_PAGE_HPP

#include "simlight/slv6_iss.h"
#include <libsimsoc/translation_page.hpp>

namespace simsoc {

  struct SLv6_Instruction;

  class ARMv6_TranslationPage: 
    public TranslationPage {
  public:
    ARMv6_TranslationPage(uint32_t *host_address, int instr_size);
    ~ARMv6_TranslationPage();

    void fill_with_empty_cells();

  protected:
    const size_t nb_instr; //  = TR_PAGE_SIZE/instr_size;
    SLv6_Instruction *instructions;
  };

  class ARMv6_ArmTranslationPage: 
    public ARMv6_TranslationPage {
  public:
    ARMv6_ArmTranslationPage(uint32_t *host_address);

    void decode();
    inline SLv6_Instruction *locateInstr(uint32_t pc_offset);

  protected:
    static const int instr_size = 4;
  };

  SLv6_Instruction* ARMv6_ArmTranslationPage::locateInstr(uint32_t pc_offset) {
    return &instructions[((pc_offset-8)&(TR_PAGE_SIZE-1))/4];
  }

  class ARMv6_ThumbTranslationPage: 
    public ARMv6_TranslationPage {
  public:
    ARMv6_ThumbTranslationPage(uint32_t *host_address);

    void decode();
    inline SLv6_Instruction *locateInstr(uint32_t pc_offset);

  protected:
    static const int instr_size = 2;
  };

  SLv6_Instruction* ARMv6_ThumbTranslationPage::locateInstr(uint32_t pc_offset) {
    return &instructions[((pc_offset-4)&(TR_PAGE_SIZE-1))/2];
  }

} // namespace simsoc

#endif //ARM_V6_TRANSLATION_PAGE_HPP
