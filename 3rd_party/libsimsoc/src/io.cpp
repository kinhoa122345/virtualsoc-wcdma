//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifdef HAVE_CONFIG_H
# include "libsimsoc/config.h"
#endif

#include "libsimsoc/io.hpp"
#include "libsimsoc/bitwise_operator.hpp"

#include <cstdlib>
#include <cstring>

#include <iostream>
#include <iomanip>

namespace simsoc {

#define LINELEN 16u

  void hexdump(std::ostream &output, const uint8_t *data, size_t size) {
    size_t i;

    for (size_t i = 0; i < size; ++i) {
      const size_t line   = i / LINELEN;
      const size_t column = i % LINELEN;

      if (column)
        output << ((column == LINELEN / 2) ? "  " : " ");
      else
        output
          << std::setw(8) << std::setfill('0') << std::hex
          << i << "  ";

      output
        << std::setw(2) << std::setfill('0') << std::hex
        << (unsigned) data[i];

      if (i+1 == size || column+1 == LINELEN) {
        for (size_t c = column+1; c < LINELEN; ++c)
          output << ((c == LINELEN / 2) ? "  " : " ") << "  ";
        output << "  |";
        for (size_t j = i - i%LINELEN; j < i+1; ++j) {
          const char thec = data[j];
          output << ((isgraph(thec) || thec == ' ') ? thec : '.');
        }
        output << '|' << std::endl;
      }
    }

    output
      << std::setw(8) << std::setfill('0') << std::hex
      << size << std::endl;
  }

  // ------------------------------------------------------------------
  InBuffer::InBuffer(size_t capacity)
    :m_buffer  (NULL)
    ,m_capacity(0)
    ,m_size    (0)
    ,m_position(0)
  {
    if (m_capacity == 0)
      m_capacity = 4096;
    m_buffer = new uint8_t[m_capacity];
  }

  // ------------------------------------------------------------------
  InBuffer::~InBuffer() {
    if (m_buffer != NULL)
      delete[] m_buffer;
  }

  // ------------------------------------------------------------------
  int InBuffer::getc() {
    if (m_position >= m_size) {
      ssize_t rr;

      m_position = m_size = 0;
      rr = this->fetch(m_buffer, m_capacity);
      if (rr <= 0)
        return -1;
      m_size = rr;
    }
    return m_buffer[m_position++];
  }

  // ------------------------------------------------------------------
  ssize_t InBuffer::read(uint8_t *data, size_t size) {
    const size_t fullsize = size;

    if (m_position < m_size) {
      size_t tocopy = std::min(m_size - m_position, size);

      memcpy(data, &m_buffer[m_position], tocopy);
      m_position += tocopy;
      size -= tocopy;
      data += tocopy;
    }

    while (size > m_capacity / 2) {
      ssize_t rr = this->fetch(data, size);

      if (rr <= 0)
        return (fullsize - size);
      data += rr;
      size -= rr;
    }

    while (size > 0) {
      if (m_position >= m_size)
        m_position = m_size = 0;

      ssize_t rr = this->fetch(m_buffer, m_capacity);

      if (rr <= 0)
        return (fullsize - size);
      m_size = rr;

      size_t tocopy = std::min(m_size - m_position, size);

      memcpy(data, &m_buffer[m_position], tocopy);
      m_position += tocopy;
      size -= tocopy;
      data += tocopy;
    }

    return (fullsize - size);
  }

  // ------------------------------------------------------------------
#ifdef WORDS_BIGENDIAN
  const Marshaller::endianess_e Marshaller::ED_MY = Marshaller::ED_BIG;
#else
  const Marshaller::endianess_e Marshaller::ED_MY = Marshaller::ED_LITTLE;
#endif

  // ------------------------------------------------------------------
  Marshaller::Marshaller(bytes_t &output, endianess_e target)
    :m_host(ED_MY)
    ,m_target(target)
    ,m_data(output)
  {}

  // ------------------------------------------------------------------
  uint16_t Marshaller::totarget_16(uint16_t data) const {
    return (m_host == m_target) ? data : swap_16(data);
  }

  // ------------------------------------------------------------------
  uint32_t Marshaller::totarget_32(uint32_t data) const {
    return (m_host == m_target) ? data : swap_32(data);
  }

  // ------------------------------------------------------------------
  void Marshaller::push_uint8(uint8_t data) {
    this->m_data.push_back(data);
  }

  // ------------------------------------------------------------------
  void Marshaller::push_uint16(uint16_t data) {
    data = this->totarget_16(data);
    m_data.resize(m_data.size() + 2);
    memcpy(&m_data.end()[-2], &data, 2);
  }

  // ------------------------------------------------------------------
  void Marshaller::push_uint32(uint32_t data) {
    data = this->totarget_32(data);
    m_data.resize(m_data.size() + 4);
    memcpy(&m_data.end()[-4], &data, 4);
  }

  // ------------------------------------------------------------------
  void Marshaller::push_raw(const uint8_t *data, size_t size) {
    if (m_data.max_size() < size)
      abort();
    if (m_data.max_size() - size < m_data.size())
      abort();

    size_t position = m_data.size();

    m_data.resize(m_data.size() + size);
    memcpy(&m_data[position], data, size);
  }

}
