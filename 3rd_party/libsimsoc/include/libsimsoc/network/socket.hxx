//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined(SIMSOC_NETWORK_SOCKET_HPP__) || defined(SIMSOC_NETWORK_SOCKET_HXX__)
# error "DO NOT INCLUDE THIS FILE DIRECTLY"
#endif

#define SIMSOC_NETWORK_SOCKET_HXX__

#include <sys/types.h>
#include <sys/socket.h>

#include <cerrno>
#include <cstring>
#include <unistd.h>

#include <unistd.h>
#include <fcntl.h>

// --------------------------------------------------------------------
inline SocketError::SocketError(handle_t handle, action action, int error)
 :m_handle(handle)
 ,m_action(action)
 ,m_error(error)
{}

inline SocketError::action SocketError::getaction() const {
  return this->m_action;
}

inline int SocketError::geterror () const {
  return this->m_error;
}

// --------------------------------------------------------------------
template < class T >
SocketError Socket<T>::m_SocketError(SocketError::action action) const {
  return SocketError(m_handle, action, errno);
}

// --------------------------------------------------------------------
template < class T >
SocketDisconnected Socket<T>::m_SocketDisconnected() const {
  return SocketDisconnected();
}

// --------------------------------------------------------------------
template < class T >
Socket<T>::Socket(int family, int type, int proto)
  :m_handle(-1)
{
  m_handle = socket(family, type, proto);
  if (m_handle < 0)
    throw m_SocketError(SocketError::SK_SOCK_CREATE);
}

template < class T >
Socket<T>::Socket(socket_t handle)
  :m_handle(handle)
{}

// --------------------------------------------------------------------
template < class T >
Socket<T>::~Socket() {
  if (m_handle >= 0)
    (void) ::close(m_handle);
}

// --------------------------------------------------------------------
template < class T >
const typename Socket<T>::address_t& Socket<T>::local() const {
  if (!m_local.get()) {
    c_address_t addr;
    socklen_t   addrlen = sizeof(addr);

    memset(&addr, 0, sizeof(addr));
    int rr = ::getsockname(m_handle, (sockaddr*) &addr, &addrlen);
    if (rr < 0 && errno != ENOTCONN)
      throw m_SocketError(SocketError::SK_SOCK_NAME);
    m_local.reset(new address_t(addr));
  }

  return *m_local;
}

// --------------------------------------------------------------------
template < class T >
const typename Socket<T>::address_t& Socket<T>::remote() const {
  if (!m_remote.get()) {
    c_address_t addr;
    socklen_t   addrlen = sizeof(addr);

    memset(&addr, 0, sizeof(addr));
    int rr = ::getpeername(m_handle, (sockaddr*) &addr, &addrlen);
    if (rr < 0 && errno != ENOTCONN)
      throw m_SocketError(SocketError::SK_PEER_NAME);
    m_remote.reset(new address_t(addr));
  }

  return *m_remote;
}

// --------------------------------------------------------------------
template < class T >
typename Socket<T>::Socket_t* Socket<T>::accept() {
  socket_t clientfd = -1;

  do {
    clientfd = ::accept(m_handle, NULL, NULL);
  } while (clientfd < 0 && errno == EINTR);

  if (clientfd < 0) {
    if (errno == EAGAIN || errno == EWOULDBLOCK)
      return NULL;
    throw m_SocketError(SocketError::SK_ACCEPT);
  }

  return new Socket_t(clientfd);
}

// --------------------------------------------------------------------
template < class T >
void Socket<T>::bind(const address_t& address) {
  m_local.release();
  if (::bind(m_handle, (sockaddr*) &address, sizeof(address)) < 0)
    throw m_SocketError(SocketError::SK_BIND);
  (void) this->local();
}

// --------------------------------------------------------------------
template < class T >
bool Socket<T>::connect(const address_t& address) {
  int rr;

  m_remote.release();
  do {
    rr = ::connect(m_handle, (sockaddr*) &address, sizeof(address));
  } while (rr < 0 && errno == EINTR);
  if (rr < 0) {
    if (errno == EWOULDBLOCK || errno == EINPROGRESS)
      return false;
    throw m_SocketError(SocketError::SK_CONNECT);
  }
  (void) this->remote();
  return true;
}

// --------------------------------------------------------------------
template < class T >
void Socket<T>::listen(int backlog) {
  if (::listen(m_handle, backlog) < 0)
    throw m_SocketError(SocketError::SK_LISTEN);
}

// --------------------------------------------------------------------
template < class T >
void Socket<T>::setsockopt(int         level,
                           int         optname,
                           const void *optval,
                           socklen_t   optlen)
{
  if (::setsockopt(m_handle, level, optname, optval, optlen) < 0)
    throw m_SocketError(SocketError::SK_SETSOCKOPT);
}

template < class T >
void Socket<T>::setsockopt(int level, int optname, bool bvalue) {
  int value = (int) bvalue;

  this->setsockopt(level, optname, &value, sizeof(value));
}

template < class T >
void Socket<T>::setsockopt(int level, int optname, int value) {
  this->setsockopt(level, optname, &value, sizeof(value));
}

// --------------------------------------------------------------------
template < class T >
ssize_t Socket<T>::recv(void *buffer, size_t size, int flags) {
  ssize_t rr;

  do {
    rr = ::recv(m_handle, buffer, size, flags);
  } while (rr < 0 && errno == EINTR);

  if (rr < 0) {
    if (errno == EAGAIN || errno == EWOULDBLOCK)
      return -1;
    throw m_SocketError(SocketError::SK_RECV);
  }

  if (rr == 0)
    throw m_SocketDisconnected();

  return rr;
}

// --------------------------------------------------------------------
template < class T >
ssize_t Socket<T>::recv(void *buffer, size_t size, address_t &address, int flags) {
  ssize_t     rr;
  c_address_t c_address;
  socklen_t   c_addrlen;

  memset(&c_address, 0, sizeof(c_address));
  c_addrlen = sizeof(c_address);

  do {
    rr = ::recvfrom(m_handle, buffer, size, flags,
                    (sockaddr*) &c_address, &c_addrlen);
  } while (rr < 0 && errno == EINTR);

  if (rr < 0) {
    if (errno == EAGAIN || errno == EWOULDBLOCK)
      return -1;
    throw m_SocketError(SocketError::SK_RECV);
  }

  if (rr == 0)
    throw m_SocketDisconnected();

  address = c_address;

  return rr;
}

// --------------------------------------------------------------------
template < class T >
ssize_t Socket<T>::_send(const void        *buffer ,
                         size_t             length ,
                         const c_address_t *address,
                         int                flags  )
{
  ssize_t   rr;
  socklen_t addrlen = address ? sizeof(c_address_t) : 0;

  do {
    rr = ::sendto(m_handle, buffer, length, flags,
                  (sockaddr*) address, addrlen);
  } while (rr < 0 && errno == EINTR);

  if (rr < 0) {
    if (errno == EAGAIN || errno == EWOULDBLOCK)
      return -1;
    if (errno == EPIPE)
      throw m_SocketDisconnected();
    throw m_SocketError(SocketError::SK_SEND);
  }

  return rr;
}

// --------------------------------------------------------------------
template < class T >
ssize_t Socket<T>::send(const void *buffer, size_t length, int flags) {
  return this->_send(buffer, length, NULL, flags);
}

// --------------------------------------------------------------------
template < class T >
ssize_t Socket<T>::send(const void      *buffer ,
                        size_t           length ,
                        const address_t &address,
                        int              flags  )
{
  c_address_t c_address;
  address.copyto(c_address);
  return this->_send(buffer, length, &c_address, flags);
}

// --------------------------------------------------------------------
template < class T >
ssize_t Socket<T>::_sendv(const iovec       *iov   ,
                         int                count  ,
                         const c_address_t *address,
                         int                flags  )
{
  struct msghdr msghdr;

  memset(&msghdr, 0, sizeof(msghdr));

  if (address != NULL) {
    msghdr.msg_name = (void*) address;
    msghdr.msg_namelen = sizeof(c_address_t);
  }

  msghdr.msg_iov = (iovec*) iov;
  msghdr.msg_iovlen = count;

  ssize_t rr;

  do {
    rr = ::sendmsg(m_handle, &msghdr, flags);
  } while (rr < 0 && errno == EINTR);

  if (rr < 0) {
    if (errno == EAGAIN || errno == EWOULDBLOCK)
      return -1;
    if (errno == EPIPE)
      throw m_SocketDisconnected();
    throw m_SocketError(SocketError::SK_SEND);
  }

  return rr;
}

// --------------------------------------------------------------------
template < class T >
ssize_t Socket<T>::sendv(const iovec     *iov    ,
                         int              count  ,
                         const address_t &address,
                         int              flags  )
{
  c_address_t c_address;
  address.copyto(c_address);
  return this->_sendv(iov, count, &c_address, flags);
}

// --------------------------------------------------------------------
template < class T >
ssize_t Socket<T>::sendv(const iovec *iov  ,
                         int          count,
                         int          flags)
{
  return this->_sendv(iov, count, NULL, flags);
}

// --------------------------------------------------------------------
template < class T >
ssize_t Socket<T>::writev(const struct iovec *iov, int count) {
  ssize_t rr;

  do {
    rr = ::writev(m_handle, iov, count);
  } while (rr < 0 && errno == EINTR);

  if (rr < 0) {
    if (errno == EAGAIN || errno == EWOULDBLOCK)
      return -1;
    if (errno == EPIPE)
      throw m_SocketDisconnected();
    throw m_SocketError(SocketError::SK_SEND);
  }

  return rr;
}

// --------------------------------------------------------------------
template < class T >
ssize_t Socket<T>::readv(struct iovec *iov, int count) {
  ssize_t rr;

  do {
    rr = ::readv(m_handle, iov, count);
  } while (rr < 0 && errno == EINTR);

  if (rr < 0) {
    if (errno == EAGAIN || errno == EWOULDBLOCK)
      return -1;
    throw m_SocketError(SocketError::SK_RECV);
  }

  if (rr == 0)
    throw m_SocketDisconnected();

  return rr;
}

// --------------------------------------------------------------------
template < class T >
void Socket<T>::close() {
  if (m_handle >= 0)
    (void) ::close(m_handle);   // No check
}

// ------------------------------------------------------------------
template < class T >
void Socket<T>::setnonblocking(bool set) {
  int flags = fcntl(m_handle, F_GETFL);

  if (flags >= 0)               // FIXME: errors
    fcntl(m_handle, F_SETFL, flags | O_NONBLOCK);
}
