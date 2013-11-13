//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined(SIMSOC_NETWORK_SOCKET_HPP__)
# define SIMSOC_NETWORK_SOCKET_HPP__

# include <sys/types.h>
# include <sys/socket.h>
# include <sys/uio.h>
# include <memory>

// --------------------------------------------------------------------
class SocketError {
public:
  typedef int handle_t;

  enum action {
    SK_SOCK_CREATE,
    SK_ACCEPT     ,
    SK_CONNECT    ,
    SK_LISTEN     ,
    SK_BIND       ,
    SK_PEER_NAME  ,
    SK_SOCK_NAME  ,
    SK_SETSOCKOPT ,
    SK_RECV       ,
    SK_SEND       ,
  };

  SocketError(handle_t handle, action action, int error);

  action getaction() const;
  int    geterror () const;

private:
  handle_t m_handle;
  action   m_action;
  int      m_error;
};

class SocketDisconnected {
};

// --------------------------------------------------------------------
typedef int socket_t;

// --------------------------------------------------------------------
template < class T >
struct SocketTraits {};

// --------------------------------------------------------------------
template < class T >
class Socket {
public:
  typedef typename SocketTraits<T>::address_t   address_t;
  typedef typename SocketTraits<T>::c_address_t c_address_t;
  typedef typename SocketTraits<T>::Socket      Socket_t;

protected:
  Socket(int family, int type, int proto = 0);
  Socket(socket_t socket);

  virtual ~Socket();

public:
  int handle() const { return m_handle; }

public:
  const address_t& local () const;
  const address_t& remote() const;

  void listen(int backlog = 5);
  Socket_t* accept();

  void bind(const address_t &address);
  bool connect(const address_t &address);

  void setsockopt(int level, int optname, const void *optval, socklen_t optlen);
  void setsockopt(int level, int optname, bool value);
  void setsockopt(int level, int optname, int value);

  ssize_t recv(void *buffer, size_t length,
               int flags = 0);

  ssize_t recv(void *buffer, size_t length,
               address_t &address, int flags = 0);

  ssize_t send(const void *buffer, size_t length, int flags = 0);

  ssize_t send(const void *buffer, size_t length,
               const address_t &address, int flags = 0);

  ssize_t sendv(const iovec *iov, int count, int flags = 0);

  ssize_t sendv(const iovec *iov, int count,
                const address_t &address, int flags = 0);

  ssize_t writev(const iovec *iov, int count);
  ssize_t readv(iovec *iov, int count);

  void close();

  void setnonblocking(bool set);

protected:
  ssize_t _send(const void *buffer, size_t length,
                const c_address_t *address, int flags = 0);

  ssize_t _sendv(const iovec *iov, int count,
                 const c_address_t *address, int flags = 0);

protected:
  typedef std::auto_ptr<address_t> autoaddress_t;

  /*---*/ socket_t      m_handle;
  mutable autoaddress_t m_local;
  mutable autoaddress_t m_remote;

protected:
  SocketError m_SocketError(SocketError::action action) const;
  SocketDisconnected m_SocketDisconnected() const;

private:
  Socket(const Socket& socket); // GNI
  Socket& operator=(const Socket&); // GNI
};

# include "libsimsoc/network/socket.hxx"

#endif // !SIMSOC_NETWORK_SOCKET_HPP__
