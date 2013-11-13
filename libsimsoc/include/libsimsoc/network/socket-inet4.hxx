//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined(SIMSOC_NETWORK_SOCKET_INET4_HPP__) || defined(SIMSOC_NETWORK_SOCKET_INET4_HXX__)
# error "DO NOT INCLUDE THIS FILE DIRECTLY"
#endif

#define SIMSOC_NETWORK_SOCKET_INET4_HXX__

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>

// --------------------------------------------------------------------
inline uint16_t IPV4_Address::port() const {
  return ntohs(m_address.sin_port);
}

inline uint32_t IPV4_Address::ip() const {
  return ntohl(m_address.sin_addr.s_addr);
}

inline IPV4_Address::IPV4_Address() {
  m_address.sin_family      = AF_INET;
  m_address.sin_port        = 0;
  m_address.sin_addr.s_addr = 0;
}

inline IPV4_Address::IPV4_Address(uint32_t address, uint16_t port) {
  m_address.sin_family      = AF_INET;
  m_address.sin_port        = htons(port);
  m_address.sin_addr.s_addr = htonl(address);
}

inline IPV4_Address::IPV4_Address(c_address_t &address) {
  if (address.sin_family != AF_INET)
    abort();
  memcpy(&m_address, &address, sizeof(m_address));
}

inline IPV4_Address& IPV4_Address::operator=(const c_address_t &address) {
  if (address.sin_family != AF_INET)
    abort();
  m_address.sin_port        = address.sin_port;
  m_address.sin_addr.s_addr = address.sin_addr.s_addr;
  return *this;
}

inline void IPV4_Address::copyto(c_address_t &output) const {
  memcpy(&output, &m_address, sizeof(c_address_t));
}

// --------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &output, const IPV4_Address &address) {
  std::ostringstream format;

  format
    << ((address.ip() >> 24) & 0xFF) << '.'
    << ((address.ip() >> 16) & 0xFF) << '.'
    << ((address.ip() >>  8) & 0xFF) << '.'
    << ((address.ip()      ) & 0xFF) << ':'
    << address.port();
  output << format.str();

  return output;
}

// --------------------------------------------------------------------
inline SocketIPV4::SocketIPV4(socket_t clientfd)
  :Socket<socket_IPV4>(clientfd)
{}

inline SocketIPV4::SocketIPV4(SocketType type)
  :Socket<socket_IPV4>(AF_INET, (int) type)
{}

inline void SocketIPV4::bind(const address_t &address) {
  Socket<socket_IPV4>::bind(address);
}

inline void SocketIPV4::bind(uint32_t address, uint16_t port) {
  this->bind(IPV4_Address(address, port));
}
