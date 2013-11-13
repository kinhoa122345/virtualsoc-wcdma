//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/network/pcaplog.hpp"

#include <sys/time.h>

#include <iostream>
#include <fstream>
#include <ios>

namespace simsoc {

  // All header a written in host endianess.
  struct header {
    uint32_t magic;             // Magic ()
    uint32_t major:16;          // Major (here = 2)
    uint32_t minor:16;          // Minor (here = 4)
     int32_t thiszone;          // TZ shift from GMT
    uint32_t sigfigs;           // Accuracy
    uint32_t snaplen;           // Maximum capture length
    uint32_t network;           // Network type (1 = ethernet)
  };

  struct pheader {
    uint32_t ts_sec;    // timestamp seconds
    uint32_t ts_usec;   // timestamp microseconds
    uint32_t incl_len;  // number of octets of packet saved in file
    uint32_t orig_len;  // actual length of packet
  };

  PCAPLogger::~PCAPLogger() {
    if (m_output.is_open())
      m_output.close();
  }

  void PCAPLogger::initialize(std::string filename) {
    if (m_output.is_open())
      m_output.close();

    const std::ios_base::openmode mode
      = std::ios_base::binary
      | std::ios_base::out
      | std::ios_base::trunc;

    struct header header = { PCAP_MAGIC, PCAP_MAJOR, PCAP_MINOR, 0, 0, 65535, 1 };

    m_output.open(filename.c_str(), mode);
    m_output.write((char*) &header, sizeof(header));
    m_output.flush();
  }

  void PCAPLogger::finalize() {
    if (m_output.is_open())
      m_output.close();
  }

  void PCAPLogger::packet(const void *data, size_t size, const pcaptime *time) {
    if (!m_output.is_open())
      return ;

   struct pheader pheader;

    if (size == 0)
      return ;

    if (time) {
      pheader.ts_sec  = time->ts_sec;
      pheader.ts_usec = time->ts_usec;
    } else {
      struct timeval tv;
      (void) gettimeofday(&tv, NULL);
      pheader.ts_sec  = tv.tv_sec;
      pheader.ts_usec = tv.tv_usec;
    }

    pheader.incl_len = size;
    pheader.orig_len = size;

    m_output.write((char*) &pheader, sizeof(pheader));
    m_output.write((char*) data, size);
    m_output.flush();
  };

}

