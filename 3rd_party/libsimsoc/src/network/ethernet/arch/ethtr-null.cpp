//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/network/ethernet/ether-transport.hpp"

namespace simsoc {
  // ------------------------------------------------------------------
  Null_EtherTransport::Null_EtherTransport()
    :m_blocking(true)
  {}

  // ------------------------------------------------------------------
  Null_EtherTransport::~Null_EtherTransport()
  {}

  // ------------------------------------------------------------------
  bool Null_EtherTransport::_send(const EtherBuffer &buffer) {
    return true;
  }

  // ------------------------------------------------------------------
  bool Null_EtherTransport::_recv(EtherBuffer &) {
    while (m_blocking)
      pause();
    return false;
  }

  // ------------------------------------------------------------------
  void Null_EtherTransport::setnonblocking(bool nonblocking) {
    this->m_blocking = !nonblocking;
  }
}
