//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined (LIBSIMSOC_NETWORK_POLL_HPP__)
# define LIBSIMSOC_NETWORK_POLL_HPP__

# include <inttypes.h>
# include <sys/select.h>
# include <cmath>
# include <algorithm>
# include <exception>

namespace simsoc {
  class Poll;

  // ------------------------------------------------------------------
  class PollFDSet {
    friend class Poll;

  public:
    PollFDSet();

    void set  (int fd);
    void unset(int fd);
    bool is_set(int fd) const;
    void clear();

  protected:
    int maxfd() const;

  protected:
    static bool pollable(int fd);
    static void check_pollable(int fd);

  private:
    mutable int    m_maxfd;
    /*---*/ fd_set m_fdset;
  };

  inline PollFDSet::PollFDSet() {
    this->clear();
  }

  inline void PollFDSet::set(int fd) {
    PollFDSet::check_pollable(fd);
    FD_SET(fd, &this->m_fdset);
    if (this->m_maxfd >= 0)
      this->m_maxfd = std::max(1+fd, this->m_maxfd);
    else if (std::abs(this->m_maxfd) <= 1+fd)
      this->m_maxfd = 1+fd;
  }

  inline void PollFDSet::unset(int fd) {
    PollFDSet::check_pollable(fd);
    FD_CLR(fd, &this->m_fdset);
    if (this->m_maxfd > 0)
      this->m_maxfd = -this->m_maxfd;
  }

  inline bool PollFDSet::is_set(int fd) const {
    PollFDSet::check_pollable(fd);
    return FD_ISSET(fd, &this->m_fdset);
  }

  inline void PollFDSet::clear() {
    FD_ZERO(&this->m_fdset);
    this->m_maxfd = 0;
  }

  inline int PollFDSet::maxfd() const {
    if (this->m_maxfd < 0) {
      for (size_t i = -this->m_maxfd; i != 0; i --) {
        if (FD_ISSET(i-1, &this->m_fdset)) {
          this->m_maxfd = i;
          break ;
        }
      }
      if (this->m_maxfd < 0)
        this->m_maxfd = 0;
    }
    return this->m_maxfd - 1;
  }

  inline bool PollFDSet::pollable(int fd) {
    return (fd >= 0) && (fd < FD_SETSIZE);
  }

  inline void PollFDSet::check_pollable(int fd) {
    if (!PollFDSet::pollable(fd))
      throw std::exception();   // FIXME
  }

  // ------------------------------------------------------------------
  class PollResult {
    friend class Poll;

  public:
    bool readable(int fd) const { return m_read.is_set (fd); }
    bool writable(int fd) const { return m_write.is_set(fd); }

  private:
    PollFDSet m_read, m_write;
  };

  // ------------------------------------------------------------------
  class Poll {
  public:
    enum direction {
      D_IN  = 1 << 0,
      D_OUT = 1 << 1,
    };

  public:
    void record(int fd, uint32_t directions);
    void clear (int fd, uint32_t directions);
    void remove(int fd);
    void reset ();

    void wait(PollResult &result);

  private:
    PollFDSet m_read, m_write;
  };

}

#endif // !LIBSIMSOC_NETWORK_POLL_HPP__
