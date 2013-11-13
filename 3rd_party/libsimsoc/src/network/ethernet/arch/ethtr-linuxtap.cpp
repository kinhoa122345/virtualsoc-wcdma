//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/network/ethernet/ether-transport.hpp"

#include <cstdlib>

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <linux/if_tun.h>
#include <net/if.h>

#define EXN_TAP "linux-tap"

namespace simsoc {
  // ------------------------------------------------------------------
  TAP_EtherTransport::TAP_EtherTransport(const std::string &device)
    :m_tap(-1)
  {
    struct ifreq ifr;

    if ((m_tap = open("/dev/net/tun", O_RDWR)) < 0)
      throw EtherTransport_Exn(EXN_TAP, "cannot open tun device", errno);

    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
    strncpy(ifr.ifr_name, device.c_str(), IFNAMSIZ);
    if (ioctl(m_tap, TUNSETIFF, (void *) &ifr) < 0)
      throw EtherTransport_Exn(EXN_TAP, "cannot TUNSETIFF device", errno);
  }

  // ------------------------------------------------------------------
  TAP_EtherTransport::~TAP_EtherTransport() {
    if (m_tap >= 0)
      ::close(m_tap);
  }

  // ------------------------------------------------------------------
  bool TAP_EtherTransport::_send(const EtherBuffer &buffer) {
    ssize_t rr;

    do {
      rr = ::write(m_tap, buffer.at(0), buffer.length());
    } while (rr < 0 && errno == EINTR);

    if (rr < 0 && (errno != EAGAIN && errno != EWOULDBLOCK))
      throw EtherTransport_Exn(EXN_TAP, "TAP-send failed", errno);
    return rr >= 0;
  }

  // ------------------------------------------------------------------
  bool TAP_EtherTransport::_recv(EtherBuffer &buffer) {
    ssize_t rr;

    while (true) {
      do {
        rr = ::read(m_tap, buffer.at(0), buffer.capacity());
      } while (rr < 0 && errno == EINTR);

      if (rr < 0) {
        if (errno != EAGAIN && errno != EWOULDBLOCK)
          throw EtherTransport_Exn(EXN_TAP, "TAP-recv failed", errno);
        return false;           // Non blocking mode
      }

      buffer.set_length(rr);
      return true;
    }
  }

  // ------------------------------------------------------------------
  void TAP_EtherTransport::setnonblocking(bool nonblocking) {
    int flags = fcntl(m_tap, F_GETFL, 0);

    if (flags < 0)
      throw EtherTransport_Exn(EXN_TAP, "fcntl(F_GETFL) failed", errno);
    if (nonblocking)
      flags |= O_NONBLOCK;
    else
      flags &= ~O_NONBLOCK;
    if (fcntl(m_tap, F_SETFL, flags) < 0)
      throw EtherTransport_Exn(EXN_TAP, "fcntl(F_SETFL) failed", errno);
  }

  // ------------------------------------------------------------------
  int TAP_EtherTransport::handle() {
    return m_tap;
  }
}
