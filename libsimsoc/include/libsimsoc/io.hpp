//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined (LIBSIMSOC_MARSHALLER_HPP__)
# define LIBSIMSOC_MARSHALLER_HPP__

# include <inttypes.h>
# include <vector>
# include <iostream>

# include "libsimsoc/network/socket.hpp"

namespace simsoc {

  // Produce a [hexdump -C] compatible output
  void hexdump(std::ostream &output, const uint8_t *data, size_t size);

  // ------------------------------------------------------------------
  class InBuffer {
  public:
    InBuffer(size_t capacity = 0);
    virtual ~InBuffer();

  public:
    int getc();
    ssize_t read(uint8_t *data, size_t size);

  public:
    virtual ssize_t fetch(uint8_t *data, size_t size) = 0;

  private:
    uint8_t *m_buffer;
    size_t   m_capacity;
    size_t   m_size;
    size_t   m_position;
  };

  // ------------------------------------------------------------------
  template < class T >
  class Socket_InBuffer: public InBuffer {
  public:
    typedef ::Socket<T> Socket;

    Socket_InBuffer(Socket &socket, size_t capacity = 0)
      :InBuffer(capacity)
      ,m_socket(socket)
    {}

  public:
    virtual ssize_t fetch(uint8_t *data, size_t size) {
      return m_socket.recv(data, size);
    }

  private:
    Socket &m_socket;
  };

  // ------------------------------------------------------------------
  class Marshaller {
  public:
    typedef std::vector<uint8_t> bytes_t;

    enum endianess_e { ED_LITTLE, ED_BIG };

    static const endianess_e ED_MY;
    static const endianess_e ED_NETWORK = ED_BIG;

  public:
    Marshaller(bytes_t &output, endianess_e = ED_NETWORK);

  public:
    uint16_t totarget_16(uint16_t data) const;
    uint32_t totarget_32(uint32_t data) const;

    void push_uint8 (uint8_t  data);
    void push_uint16(uint16_t data);
    void push_uint32(uint32_t data);

    void push_raw(const uint8_t *data, size_t size);

  public:
    void target_endianess(endianess_e x) { this->m_target = x; }
    void host_endianess  (endianess_e x) { this->m_host   = x; }

    endianess_e target_endianess() const { return this->m_target; }
    endianess_e host_endianess  () const { return this->m_host  ; }

  public:
    /*-*/ bytes_t& bytes() /*-*/ { return this->m_data; }
    const bytes_t& bytes() const { return this->m_data; }

  protected:
    endianess_e  m_host;
    endianess_e  m_target;
    bytes_t     &m_data;

  private:
    Marshaller(const Marshaller&);            // GNI
    Marshaller& operator=(const Marshaller&); // GNI
  };

}

#endif // !LIBSIMSOC_MARSHALLER_HPP__
