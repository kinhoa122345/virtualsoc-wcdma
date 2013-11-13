//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined(SIMSOC_NETWORK_SOCKET_INET4_HPP__)
# define SIMSOC_NETWORK_SOCKET_INET4_HPP__

# include "libsimsoc/network/socket.hpp"

# include <sys/types.h>
# include <arpa/inet.h>

// --------------------------------------------------------------------
class IPV4_Address {
public:
  typedef sockaddr_in c_address_t;

  uint16_t port() const;
  uint32_t ip  () const;

public:
  IPV4_Address();
  IPV4_Address(uint32_t address, uint16_t port);
  IPV4_Address(c_address_t &address);

  IPV4_Address& operator=(const c_address_t &address);

  void copyto(c_address_t &output) const;

protected:
  struct sockaddr_in m_address;
};

// --------------------------------------------------------------------
struct socket_IPV4 {};

class SocketIPV4;

template <>
struct SocketTraits<socket_IPV4> {
  typedef IPV4_Address              address_t;
  typedef IPV4_Address::c_address_t c_address_t;
  typedef SocketIPV4                Socket;
};

// --------------------------------------------------------------------
class SocketIPV4: public Socket<socket_IPV4> {
public:
  typedef SocketTraits<socket_IPV4>::address_t address_t;

  static const uint32_t ANY = INADDR_ANY;

  enum SocketType {
    IPV4_STREAM = SOCK_STREAM,
    IPV4_DGRAM  = SOCK_DGRAM ,
  };

protected:
  friend class Socket<socket_IPV4>;
  SocketIPV4(socket_t clientfd);

public:
  SocketIPV4(enum SocketType type);

public:
  void bind(const address_t &address);
  void bind(uint32_t address, uint16_t port);
};

# include "libsimsoc/network/socket-inet4.hxx"

#endif // !SIMSOC_NETWORK_SOCKET_INET4_HPP__
