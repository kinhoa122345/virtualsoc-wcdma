//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/network/ethernet/ether-transport.hpp"

#include <cstdlib>
#include <inttypes.h>
#include <sys/time.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#define ETHER_MCAST_PORT 8805u
#define ETHER_MCAST_ADDR "224.0.0.252"

#define EXN_MCAST "mcast"

namespace simsoc {
  struct mcast_header {
    uint32_t magic;
    uint32_t length;
  };

  // ------------------------------------------------------------------
  MCast_EtherTransport::MCast_EtherTransport(uint32_t magic)
    :m_socket(SocketIPV4::IPV4_DGRAM)
    ,m_magic (magic)
  {
    while (m_magic == 0) {
      struct timeval tv;

      gettimeofday(&tv, NULL);
      m_magic
        = (((uint32_t) tv.tv_sec ) << 16)
        | (((uint32_t) tv.tv_usec) & 0xffff);
    }

    try {
      m_socket.setsockopt(SOL_SOCKET, SO_REUSEADDR, true);
#if defined(SO_REUSEPORT)
      m_socket.setsockopt(SOL_SOCKET, SO_REUSEPORT, true);
#endif

      m_socket.bind(IPV4_Address(INADDR_ANY, ETHER_MCAST_PORT));

      struct ip_mreq mreq;

      memset(&mreq, 0, sizeof(mreq));
      inet_pton(AF_INET, ETHER_MCAST_ADDR, &mreq.imr_multiaddr);
      mreq.imr_interface.s_addr = INADDR_ANY;

      m_socket.setsockopt(IPPROTO_IP, IP_MULTICAST_LOOP, true);
      m_socket.setsockopt(IPPROTO_IP, IP_MULTICAST_TTL, 1);
      m_socket.setsockopt(IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
    } catch (SocketError e) {
      throw EtherTransport_Exn
        (EXN_MCAST, "failing creating multicast socket", e.geterror());
    }
  }

  // ------------------------------------------------------------------
  bool MCast_EtherTransport::_send(const EtherBuffer &buffer) {
    mcast_header header;

    header.magic  = htonl(m_magic);
    header.length = htonl(buffer.length());

    struct iovec iovec[2];

    iovec[0].iov_base = (void*) &header;
    iovec[0].iov_len  = sizeof(header);
    iovec[1].iov_base = (void*) buffer.at(0);
    iovec[1].iov_len  = buffer.length();

    struct sockaddr_in remote;

    memset(&remote, 0, sizeof(remote));
    remote.sin_family = AF_INET;
    remote.sin_port   = htons(ETHER_MCAST_PORT);
    inet_pton(AF_INET, ETHER_MCAST_ADDR, &remote.sin_addr);

    ssize_t rr;

    try {
      rr = m_socket.sendv(iovec, 2, remote);
    } catch (SocketError e) {
      throw EtherTransport_Exn
        (EXN_MCAST, "transport-send failed", e.geterror());
    }

    return rr >= 0;
  }

  // ------------------------------------------------------------------
  bool MCast_EtherTransport::_recv(EtherBuffer &buffer) {
    while (true) {
      mcast_header header;
      struct iovec iovec[2];

      iovec[0].iov_base = (void*) &header;
      iovec[0].iov_len  = sizeof(header);
      iovec[1].iov_base = buffer.at(0);
      iovec[1].iov_len  = buffer.capacity();

      ssize_t rr;

      try {
        rr = m_socket.readv(iovec, 2);
      } catch (SocketError e) {
        throw EtherTransport_Exn
          (EXN_MCAST, "transport-receive failed", e.geterror());
      }

      if (rr < 0)               // Non blocking mode
        return false;

      if (rr < (ssize_t) sizeof(header))
        continue ;
      rr -= sizeof(header);

      header.magic  = ntohl(header.magic);
      header.length = ntohl(header.length);

      if (header.length != (uint32_t) rr)
        continue ;
      if (header.magic == m_magic)
        continue ;

      buffer.set_length(rr);

      return true;
    }
  }

  // ------------------------------------------------------------------
  void MCast_EtherTransport::setnonblocking(bool nonblocking) {
    m_socket.setnonblocking(nonblocking);
  }

  // ------------------------------------------------------------------
  int MCast_EtherTransport::handle() {
    return m_socket.handle();
  }

}
