//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef TRANSLATION_TABLE_HPP
#define TRANSLATION_TABLE_HPP

#include <list>
#include <vector>
#include "libsimsoc/translation_page.hpp"
#include "libsimsoc/processors/common.hpp"

namespace simsoc {

  template <typename word_t> class MIPS_TranslationPage;
  class ARM32_TranslationPage;
  class Thumb_TranslationPage;
  class ARMv6_ArmTranslationPage;
  class ARMv6_ThumbTranslationPage;
  class PPC_TranslationPage;

  struct TranslationTableItem {
    TranslationTableItem();
    ~TranslationTableItem();
    void clear(std::list<TranslationPage*> &pages);

    MIPS_TranslationPage<BUS32> * mips32;
    MIPS_TranslationPage<BUS64> * mips64;
    ARM32_TranslationPage * arm32;
    Thumb_TranslationPage * thumb;
    ARMv6_ArmTranslationPage * arm_v6;
    ARMv6_ThumbTranslationPage * thumb_v6;
    PPC_TranslationPage * ppc;
  };

typedef std::vector<TranslationTableItem> TranslationTable;

} // namespace simsoc

#endif // TRANSLATION_TABLE_HPP
