//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined(SIMSOC_NETWORK_PCAPLOG_HPP__)
# define SIMSOC_NETWORK_PCAPLOG_HPP__

# include <sys/types.h>
# include <inttypes.h>

# include <string>
# include <fstream>

namespace simsoc {

  struct pcaptime {
    uint32_t ts_sec;
    uint32_t ts_usec;
  };

  class PCAPLogger {
  public:
    virtual ~PCAPLogger();

    static const uint32_t PCAP_MAGIC = 0xa1b2c3d4;
    static const uint32_t PCAP_MAJOR = 2;
    static const uint32_t PCAP_MINOR = 4;

    void initialize(std::string filename);
    void finalize  ();

    void packet(const void *data, size_t size, const pcaptime *time = NULL);

    bool good() const { return m_output.good(); }
    bool fail() const { return m_output.fail(); }
    bool bad () const { return m_output.bad (); }

    bool is_open() const { return m_output.is_open(); }

  private:
    std::ofstream m_output;
  };

}

#endif // !PCAPLOG_HPP__
