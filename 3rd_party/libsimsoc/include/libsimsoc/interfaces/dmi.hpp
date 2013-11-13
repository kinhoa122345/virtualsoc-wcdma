//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef DMI_HPP
#define DMI_HPP

#include "libsimsoc/translation_table.hpp"
#include <tlm.h>

namespace simsoc {

  class Processor;

  class DirectInstrCacheExtension: public tlm::tlm_extension<DirectInstrCacheExtension>
  {
  public:
    TranslationTable *table;
    Processor *user;

    DirectInstrCacheExtension(Processor *u): table(NULL), user(u) {}
    ~DirectInstrCacheExtension() {}

    void copy_from(const tlm_extension_base &extension) {
      table = static_cast<const DirectInstrCacheExtension&>(extension).table;
      user = static_cast<const DirectInstrCacheExtension&>(extension).user;
    }

    tlm::tlm_extension_base *clone() const {
      return new DirectInstrCacheExtension(*this);
    }

  };

} // namespace simsoc

#endif //DMI_HPP
