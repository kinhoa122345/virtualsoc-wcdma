//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined(LIBSIMSOC_NETWORK_ETHTR_HPP__)
# error "never include this file directly"
#endif

#include "libsimsoc/network/socket-inet4.hpp"

namespace simsoc {
  // ------------------------------------------------------------------
  class MCast_EtherTransport
    : public IEtherTransport
  {
  public:
    MCast_EtherTransport(uint32_t magic = 0);

  public:                       // IEtherTransport
    virtual void setnonblocking(bool nonblocking);
    virtual int  handle();

  protected:
    virtual bool _recv(EtherBuffer &buffer);
    virtual bool _send(const EtherBuffer &buffer);

  protected:
    SocketIPV4 m_socket;
    uint32_t   m_magic;
  };
}
