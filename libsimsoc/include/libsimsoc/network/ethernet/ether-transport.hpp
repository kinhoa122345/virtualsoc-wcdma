//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined(LIBSIMSOC_NETWORK_ETHTR_HPP__)
# define LIBSIMSOC_NETWORK_ETHTR_HPP__

# include "simsoc-config.h"

# include "libsimsoc/network/ethernet/ether-buffer.hpp"
# include "libsimsoc/network/pcaplog.hpp"

# include <cstring>
# include <cerrno>

# include <string>
# include <sstream>

# include <exception>

namespace simsoc {
  // ------------------------------------------------------------------
  class EtherTransport_Exn: std::exception {
  public:
    EtherTransport_Exn(const std::string &transport,
                       const std::string &message,
                       int myerrno = 0);

    ~EtherTransport_Exn() throw () {}

    const char* transport() const throw () { return m_transport.c_str(); }
    const char* what     () const throw () { return m_what.c_str(); }

    int syserror() const { return m_errno; }

  private:
    int         m_errno;
    std::string m_transport;
    std::string m_what;
  };

  inline EtherTransport_Exn::EtherTransport_Exn(const std::string &transport,
                                                const std::string &message,
                                                int myerrno)
    :m_errno(myerrno)
    ,m_transport(transport)
    ,m_what()
  {
    std::stringstream ss;

    ss << "transport[" << m_transport << "]: " << message;
    if (errno != 0)
      ss << ": " << strerror(m_errno);
    m_what = ss.str();
  }

  // ------------------------------------------------------------------
  class IEtherTransport {
  public:
    IEtherTransport();
    virtual ~IEtherTransport();

  public:
    virtual void setnonblocking(bool nonblocking) = 0;

  public:
    bool recv(EtherBuffer &buffer);
    bool send(const EtherBuffer &buffer);

  protected:
    virtual bool _recv(EtherBuffer &buffer) = 0;
    virtual bool _send(const EtherBuffer &buffer) = 0;

  public:
    virtual int handle() { return -1; }

  public:
    void setrxpad(bool value);
    bool getrxpad() const;

  protected:
    bool m_rxpad;

  public:
    static IEtherTransport* create(const std::string &name);

  public:
#ifndef SC_NO_PCAPLOGGER
    /*-*/ PCAPLogger& logger() /*-*/ { return m_logger; }
    const PCAPLogger& logger() const { return m_logger; }
#endif

  protected:
    void log(const void *data, size_t size);

#ifndef SC_NO_PCAPLOGGER
  private:
    PCAPLogger m_logger;
#endif

  private:
    IEtherTransport(const IEtherTransport&);            // GNI
    IEtherTransport& operator=(const IEtherTransport&); // GNI
  };

  inline void IEtherTransport::log(const void *data, size_t size) {
#ifndef SC_NO_PCAPLOGGER
    if (m_logger.is_open())
      m_logger.packet(data, size);
#endif
  }
}

# include "arch/ethtr-null.hpp"
# include "arch/ethtr-mcast.hpp"

# if defined(SIMSOC_HAVE_LINUXTAP)
#  include "arch/ethtr-linuxtap.hpp"
# endif

# if defined(SIMSOC_HAVE_PCAP)
#  include "arch/ethtr-pcap.hpp"
# endif

#endif // !LIBSIMSOC_NETWORK_ETHTR_HPP__
