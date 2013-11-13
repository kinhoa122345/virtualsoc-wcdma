//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef TRANSLATION_PAGE_HPP
#define TRANSLATION_PAGE_HPP

#include <libsimsoc/display.hpp>
#include <inttypes.h>

namespace simsoc {

class TranslationPage {
public:
  static const unsigned TR_PAGE_SIZE = 0x1000; // in Bytes
  static uint32_t pageId(uint32_t addr) {return addr>>12;}

  TranslationPage(uint32_t *host_addr):
    host_address(host_addr) {}

  virtual ~TranslationPage() {}

protected:
  const uint32_t* host_address;
};

} // namespace simsoc

#endif //TRANSLATION_PAGE_HPP
