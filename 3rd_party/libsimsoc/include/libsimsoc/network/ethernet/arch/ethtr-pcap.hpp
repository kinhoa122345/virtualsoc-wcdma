//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined(LIBSIMSOC_NETWORK_ETHTR_HPP__)
# error "never include this file directly"
#endif

#include <pcap.h>

namespace simsoc {
  // ------------------------------------------------------------------
  class PCAP_EtherTransport
    : public IEtherTransport
  {
  public:
    PCAP_EtherTransport(const std::string &device);
    virtual ~PCAP_EtherTransport();

  public:                       // IEtherTransport
    virtual void setnonblocking(bool nonblocking);
    virtual int  handle();

  protected:
    virtual bool _recv(EtherBuffer &buffer);
    virtual bool _send(const EtherBuffer &buffer);

  protected:
    pcap_t *m_pcap;
    bool    m_blocking;
  };

}
