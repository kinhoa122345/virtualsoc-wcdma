//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/network/ethernet/ether-transport.hpp"

#include <pcap.h>
#include <poll.h>

#define EXN_PCAP "pcap"

namespace simsoc {
  // ------------------------------------------------------------------
  PCAP_EtherTransport::PCAP_EtherTransport(const std::string &device)
    :m_pcap    (NULL)
    ,m_blocking(true)
  {
    char pcerror[PCAP_ERRBUF_SIZE];

    if (!(m_pcap = pcap_open_live(device.c_str(), 65535, 1, 0, pcerror)))
      throw EtherTransport_Exn(EXN_PCAP, pcerror);
    pcap_setnonblock(m_pcap, 0, NULL);
  }

  // ------------------------------------------------------------------
  PCAP_EtherTransport::~PCAP_EtherTransport() {
    if (m_pcap)
      pcap_close(m_pcap);
  }

  // ------------------------------------------------------------------
  bool PCAP_EtherTransport::_send(const EtherBuffer &buffer) {
    if (!m_blocking) {
      struct pollfd pfd = { pcap_fileno(m_pcap), POLLOUT, 0 };
      if (poll(&pfd, 1, 0) <= 0)
        return false;
    }

    if (pcap_sendpacket(m_pcap, buffer.at(0), buffer.length()) < 0)
      throw EtherTransport_Exn(EXN_PCAP, pcap_geterr(m_pcap));
    return true;
  }

  // ------------------------------------------------------------------
  bool PCAP_EtherTransport::_recv(EtherBuffer &buffer) {
    while (true) {
      if (!m_blocking) {
        struct pollfd pfd = { pcap_fileno(m_pcap), POLLIN, 0 };
        if (poll(&pfd, 1, 0) <= 0)
          return false;
      }

      struct pcap_pkthdr *header;
      const u_char *packet;

      int rr = pcap_next_ex(m_pcap, &header, &packet);

      if (rr < 0)
        throw EtherTransport_Exn(EXN_PCAP, pcap_geterr(m_pcap));

      if (header->caplen != header->len || header->len > buffer.capacity()) {
        if (m_blocking)
          continue ;
        return false;
      }

      memcpy(buffer.at(0), packet, header->len);
      buffer.set_length(header->len);

      return true;
    }
  }

  // ------------------------------------------------------------------
  void PCAP_EtherTransport::setnonblocking(bool nonblocking) {
    m_blocking = !nonblocking;
  }

  // ------------------------------------------------------------------
  int PCAP_EtherTransport::handle() {
    return pcap_fileno(m_pcap);
  }
}
