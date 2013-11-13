//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "simsoc-config.h"
#include "libsimsoc/network/ethernet/ether-transport.hpp"

#include <cstdlib>
#include <string>
#include <map>
#include <sstream>

namespace simsoc {

  // ------------------------------------------------------------------
  IEtherTransport* IEtherTransport::create(const std::string &name) {
    std::map<std::string, std::string> options;
    std::string driver;

    { std::stringstream ss(name);
      std::string item;

      while (std::getline(ss, item, ' ')) {
        if (!item.length())
          continue ;

        if (!driver.length())
          driver = item;
        else {
          std::string::size_type eqpos = item.find('=');
          std::string value;

          if (eqpos != std::string::npos) {
            value = item.substr(eqpos+1);
            item  = item.substr(0, eqpos);
          }

          if (item.length() == 0)
            continue ;
          if (options.find(item) != options.end())
            continue ;
          options[item] = value;
        }
      }
    }

    IEtherTransport *transport = NULL;

    if (driver == "null" || driver == "")
      transport = new Null_EtherTransport();

    else if (driver == "mcast")
      transport = new MCast_EtherTransport();

#ifdef SIMSOC_HAVE_LINUXTAP
    else if (driver.substr(0, 3) == "tap")
      transport = new TAP_EtherTransport(driver);
#endif

#ifdef SIMSOC_HAVE_PCAP
    else if (driver.substr(0, 4) == "cap:")
      transport = new PCAP_EtherTransport(driver.substr(4));
#endif

    if (transport == NULL)
      return NULL;

#ifndef SC_NO_PCAPLOGGER
    if (options.find("pcaplog") != options.end()) {
      std::string filename = options.find("pcaplog")->second;

      if (filename == "")
        filename = "pcap.log";
      transport->logger().initialize(filename);
    }
#endif

    return transport;
  }

  // ------------------------------------------------------------------
  IEtherTransport::IEtherTransport()
    :m_rxpad(false)
  {}

  // ------------------------------------------------------------------
  IEtherTransport::~IEtherTransport() {}

  // ------------------------------------------------------------------
  bool IEtherTransport::recv(EtherBuffer &buffer) {
    bool rr = this->_recv(buffer);

    if (rr) {
      this->log(buffer.at(0), buffer.length());
      if (m_rxpad && buffer.length() < (64-4)) {
        // HACK: pad ethernet frame
        if (buffer.capacity() >= 64-4)
          buffer.set_length(64-4);
      }
    }

    return rr;
  }

  // ------------------------------------------------------------------
  bool IEtherTransport::send(const EtherBuffer &buffer) {
    bool rr = this->_send(buffer);

    if (rr)
      this->log(buffer.at(0), buffer.length());
    return rr;
  }

  // ------------------------------------------------------------------
  void IEtherTransport::setrxpad(bool value) {
    m_rxpad = value;
  }

  // ------------------------------------------------------------------
  bool IEtherTransport::getrxpad() const {
    return m_rxpad;
  }

}
