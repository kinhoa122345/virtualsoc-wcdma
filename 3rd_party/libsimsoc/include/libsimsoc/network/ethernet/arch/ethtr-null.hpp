//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined(LIBSIMSOC_NETWORK_ETHTR_HPP__)
# error "never include this file directly"
#endif

namespace simsoc {
  // ------------------------------------------------------------------
  class Null_EtherTransport
    : public IEtherTransport
  {
  public:
    Null_EtherTransport();
    virtual ~Null_EtherTransport();

  public:                       // IEtherTransport
    virtual void setnonblocking(bool nonblocking);

  protected:
    virtual bool _recv(EtherBuffer &buffer);
    virtual bool _send(const EtherBuffer &buffer);

  protected:
    bool m_blocking;
  };
}
