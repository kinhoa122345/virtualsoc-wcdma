//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined (LIBSIMSOC_NETWORK_ETHERNET_HPP__)
# define LIBSIMSOC_NETWORK_ETHERNET_HPP__

# include "libsimsoc/bitwise_operator.hpp"

# include <inttypes.h>
# include <cstring>

# include <iostream>
# include <string>

namespace simsoc {

  // ------------------------------------------------------------------
  class EtherAddress {
  public:
    EtherAddress() {
      memset(m_address, 0, sizeof(m_address));
    }

    EtherAddress(const uint8_t *data) {
      memcpy(m_address, data, sizeof(m_address));
    }

  public:
    uint32_t hi_32() const;
    uint16_t lo_16() const;

    void set_hi_32(uint32_t value);
    void set_lo_16(uint16_t value);

  public:
    uint16_t hi_16() const;
    uint32_t lo_32() const;

    void set_hi_16(uint16_t value);
    void set_lo_32(uint32_t value);

  public:
    uint64_t as64() const;
    void set_as64(uint64_t value);

  public:
    uint8_t  at(size_t pos) const { return m_address[pos]; }
    uint8_t& at(size_t pos) /*-*/ { return m_address[pos]; }

  public:
    enum kind_e { UNICAST, MULTICAST, BROADCAST };

    kind_e classify() const {
      if (!(m_address[0] & 0x1))
	return UNICAST;
      if (lo_32() == 0xffffffff && hi_16() == 0xffff)
	return BROADCAST;
      return MULTICAST;
    }

    bool is_unicast() const
    { return this->classify() == UNICAST; }

    bool is_broadcast() const
    { return this->classify() == BROADCAST; }

    bool is_multicast() const
    { return this->classify() == MULTICAST; }

  public:
    std::string asstring() const;

  public:
    bool operator==(const EtherAddress &other) const
    { return memcmp(m_address, other.m_address, 6) == 0; }

    bool operator!=(const EtherAddress &other) const
    { return !this->operator==(other); }

    bool operator<(const EtherAddress &other) const
    { return memcmp(m_address, other.m_address, 6) < 0; }

    bool operator>(const EtherAddress &other) const
    { return memcmp(m_address, other.m_address, 6) > 0; }

    bool operator<=(const EtherAddress &other) const
    { return memcmp(m_address, other.m_address, 6) <= 0; }

    bool operator>=(const EtherAddress &other) const
    { return memcmp(m_address, other.m_address, 6) >= 0; }

  protected:
    uint8_t m_address[6];
  };

  inline std::ostream&
  operator<<(std::ostream &output, const simsoc::EtherAddress &the)
  {
    return output << the.asstring();
  }
}

#endif // !LIBSIMSOC_NETWORK_ETHERNET_HPP__
