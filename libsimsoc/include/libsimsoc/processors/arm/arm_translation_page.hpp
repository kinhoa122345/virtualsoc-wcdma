//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARM_TRANSLATION_PAGE_HPP
#define ARM_TRANSLATION_PAGE_HPP

#include <libsimsoc/translation_page.hpp>

namespace simsoc {

  class ARM_Instruction;
  class ARM32_Instruction;
  class THUMB_Instruction;

  class ARM_TranslationPage: public TranslationPage {
  public:
    ARM_TranslationPage(uint32_t *host_address, bool is_thumb = false);
    ~ARM_TranslationPage();

    virtual ARM_Instruction * locateInstr(uint32_t a) const = 0;

  protected:
    size_t instr_size;
    size_t nb_instr;
    ARM_Instruction **instructions;
  };

  class ARM32_TranslationPage: public ARM_TranslationPage {
  public:
    ARM32_TranslationPage(uint32_t *host_address);
    void decode();
    void fill(ARM32_Instruction*);
    inline ARM_Instruction * locateInstr(uint32_t a) const;
    inline ARM_Instruction **locateInstrPtr(uint32_t a) const;
    uint32_t getBincode(uint32_t pc);
  };

  class Thumb_TranslationPage: public ARM_TranslationPage {
  public:
    Thumb_TranslationPage(uint32_t *host_address);
    void decode();
    void fill(THUMB_Instruction*);
    inline ARM_Instruction * locateInstr(uint32_t a) const;
    inline ARM_Instruction **locateInstrPtr(uint32_t a) const;
    uint16_t getBincode(uint32_t pc);
  };

  ARM_Instruction * ARM32_TranslationPage::locateInstr(uint32_t addr) const {
    return instructions[((addr-8)&(TR_PAGE_SIZE-1))/4];
  }

  ARM_Instruction **ARM32_TranslationPage::locateInstrPtr(uint32_t addr) const {
    return &instructions[((addr-8)&(TR_PAGE_SIZE-1))/4];
  }

  ARM_Instruction * Thumb_TranslationPage::locateInstr(uint32_t addr) const {
    return instructions[((addr-4)&(TR_PAGE_SIZE-1))/2];
  }

  ARM_Instruction **Thumb_TranslationPage::locateInstrPtr(uint32_t addr) const {
    return &instructions[((addr-4)&(TR_PAGE_SIZE-1))/2];
  }

} // namespace simsoc

#endif //ARM_TRANSLATION_PAGE_HPP
