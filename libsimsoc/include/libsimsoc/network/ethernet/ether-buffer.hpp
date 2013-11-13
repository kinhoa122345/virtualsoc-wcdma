//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined(LIBSIMSOC_NETWORK_ETHBUF_HPP__)
# define LIBSIMSOC_NETWORK_ETHBUF_HPP__

# include <sys/types.h>
# include <inttypes.h>

namespace simsoc {

  // ------------------------------------------------------------------
  class EtherBuffer {
    friend class EtherTransport;

  public:
    EtherBuffer(size_t capacity);
    ~EtherBuffer();

  public:
    static const size_t OFF_DESTINATION =  0;
    static const size_t OFF_SOURCE      =  6;
    static const size_t OFF_ETHERTYPE   = 12;

  public:
    size_t capacity() const { return m_capacity; }
    size_t length  () const { return m_length  ; }

    /*-*/ uint8_t* at(size_t position) /*-*/ { return &m_buffer[position]; }
    const uint8_t* at(size_t position) const { return &m_buffer[position]; }

    void set_length(size_t length);

  private:
    uint8_t *m_buffer;
    size_t   m_length;
    size_t   m_capacity;

  private:
    EtherBuffer(const EtherBuffer&);            // GNI
    EtherBuffer& operator=(const EtherBuffer&); // GNI
  };


}

#endif // !LIBSIMSOC_NETWORK_ETHBUF_HPP__
