//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/network/ethernet/ether-address.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>

namespace simsoc {
  // --------------------------------------------------------------------
  uint32_t EtherAddress::hi_32() const {
    return
        ((uint32_t) m_address[0] <<  0)
      | ((uint32_t) m_address[1] <<  8)
      | ((uint32_t) m_address[2] << 16)
      | ((uint32_t) m_address[3] << 24);
  }

  uint16_t EtherAddress::lo_16() const {
    return
        ((uint16_t) m_address[4] << 0)
      | ((uint16_t) m_address[5] << 8);
  }

  void EtherAddress::set_hi_32(uint32_t value) {
    m_address[0] = (value >>  0) & 0xff;
    m_address[1] = (value >>  8) & 0xff;
    m_address[2] = (value >> 16) & 0xff;
    m_address[3] = (value >> 24) & 0xff;
  }

  void EtherAddress::set_lo_16(uint16_t value) {
    m_address[0] = (value >> 0) & 0xff;
    m_address[1] = (value >> 8) & 0xff;
  }

  // --------------------------------------------------------------------
  uint16_t EtherAddress::hi_16() const {
    return
        ((uint16_t) m_address[0] << 0)
      | ((uint16_t) m_address[1] << 8);
  }

  uint32_t EtherAddress::lo_32() const {
    return
        ((uint32_t) m_address[2] <<  0)
      | ((uint32_t) m_address[3] <<  8)
      | ((uint32_t) m_address[4] << 16)
      | ((uint32_t) m_address[5] << 24);
  }

  void EtherAddress::set_hi_16(uint16_t value) {
    m_address[4] = (value >> 0) & 0xff;
    m_address[5] = (value >> 8) & 0xff;
  }

  void EtherAddress::set_lo_32(uint32_t value) {
    m_address[2] = (value >>  0) & 0xff;
    m_address[3] = (value >>  8) & 0xff;
    m_address[4] = (value >> 16) & 0xff;
    m_address[5] = (value >> 24) & 0xff;
  }

  // --------------------------------------------------------------------
  uint64_t EtherAddress::as64() const {
    return
        ((uint64_t) this->hi_16() << 32)
      | ((uint64_t) this->lo_32() <<  0);
  }

  void EtherAddress::set_as64(uint64_t value) {
    this->set_hi_16((uint16_t) ((value >> 32) & 0x0000ffff));
    this->set_lo_32((uint32_t) ((value >>  0) & 0xffffffff));
  }

  // --------------------------------------------------------------------
  std::string EtherAddress::asstring() const {
    std::ostringstream ss;
    for (size_t i = 0; i < 6; ++i) {
      if (i != 0) ss << ':';
      ss
	<< std::hex << std::setw(2) << std::setfill('0')
	<< (unsigned) this->m_address[i];
    }
    return ss.str();
  }
}
