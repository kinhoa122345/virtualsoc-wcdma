//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/network/ethernet/ether-buffer.hpp"

#include <cstdlib>
#include <inttypes.h>

namespace simsoc {

  // ------------------------------------------------------------------
  EtherBuffer::EtherBuffer(size_t capacity)
    :m_buffer  (NULL)
    ,m_length  (capacity)
    ,m_capacity(capacity)
  {
    m_buffer = new uint8_t[capacity];
  }

  // ------------------------------------------------------------------
  EtherBuffer::~EtherBuffer() {
    if (m_buffer)
      delete[] m_buffer;
  }

  // ------------------------------------------------------------------
  void EtherBuffer::set_length(size_t length) {
    if (length > m_capacity)
      abort();
    m_length = length;
  }
}
