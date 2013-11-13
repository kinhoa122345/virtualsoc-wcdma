//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/translation_table.hpp"
#include "libsimsoc/processors/arm/arm_translation_page.hpp"
#include "libsimsoc/processors/arm_v6/arm_v6_translation_page.hpp"
//#include "libsimsoc/processors/ppc/ppc_translation_page.hpp"
//#include "libsimsoc/processors/mips/mips_translation_page.hpp"

namespace simsoc {

TranslationTableItem::TranslationTableItem():
  //mips32(NULL),
  //mips64(NULL),
  arm32(NULL),
  thumb(NULL),
  arm_v6(NULL),
  thumb_v6(NULL)/*,
  ppc(NULL)*/ {}

TranslationTableItem::~TranslationTableItem() {
  //delete ppc;
  delete thumb_v6;
  delete arm_v6;
  delete thumb;
  delete arm32;
  //delete mips64;
  //delete mips32;
}

void TranslationTableItem::clear(std::list<TranslationPage*> &pages) {
  //if (mips32) {
    //pages.push_front(static_cast<TranslationPage*>(mips32));
    //mips32 = NULL;
  //}
  //if (mips64) {
    //pages.push_front(static_cast<TranslationPage*>(mips64));
    //mips64 = NULL;
  //}
  if (arm32) {
    pages.push_front(static_cast<TranslationPage*>(arm32));
    arm32 = NULL;
  }
  if (thumb) {
    pages.push_front(static_cast<TranslationPage*>(thumb));
    thumb = NULL;
  }
  if (arm_v6) {
    pages.push_front(static_cast<TranslationPage*>(arm_v6));
    arm_v6 = NULL;
  }
  if (thumb_v6) {
    pages.push_front(static_cast<TranslationPage*>(thumb_v6));
    thumb_v6 = NULL;
  }
  //if (ppc) {
    //pages.push_front(static_cast<TranslationPage*>(ppc));
    //ppc = NULL;
  //}
}

} // namespace simsoc
