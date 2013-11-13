//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/network/poll.hpp"

#include <sys/select.h>
#include <cstring>
#include <cerrno>

namespace simsoc {
  // ------------------------------------------------------------------
  void Poll::record(int fd, uint32_t directions) {
    if ((directions & Poll::D_IN))
      m_read.set(fd);
    if ((directions & Poll::D_OUT))
      m_write.set(fd);
  }

  // ------------------------------------------------------------------
  void Poll::clear(int fd, uint32_t directions) {
    if ((directions & Poll::D_IN))
      m_read.unset(fd);
    if ((directions & Poll::D_OUT))
      m_write.unset(fd);
  }

  // ------------------------------------------------------------------
  void Poll::remove(int fd) {
    m_read .unset(fd);
    m_write.unset(fd);
  }

  // ------------------------------------------------------------------
  void Poll::reset() {
    m_read .clear();
    m_write.clear();
  }

  // ------------------------------------------------------------------
  void Poll::wait(PollResult &result) {
    result.m_read  = this->m_read;
    result.m_write = this->m_write;

    int maxfd = std::max(this->m_read.maxfd(), this->m_write.maxfd());
    int rr;

    do {
      rr = ::select(1+maxfd,
                    &result.m_read.m_fdset,
                    &result.m_write.m_fdset,
                    NULL, NULL);
    } while (rr < 0 && errno == EINTR);

    if (rr < 0)
      throw std::exception(); // FIXME
  }
}

