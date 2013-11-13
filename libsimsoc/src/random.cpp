//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/random.hpp"

#include <cstdlib>
#include <cerrno>

#include <sys/types.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

namespace simsoc {

  // ------------------------------------------------------------------
  void Random::seed() {
    unsigned int myseed = 0;

    int fd = open("/dev/urandom", O_RDONLY);

    if (fd < 0)
      myseed = (time(NULL) * getpid()) + getppid();
    else {
      size_t where = 0;

      while (where != sizeof(myseed)) {
        ssize_t rr;

        rr = read(fd, ((char*) myseed) + where, sizeof(myseed) - where);
        if (rr < 0 && errno != EINTR && errno != EAGAIN)
          break ;
        where += rr;
      }

      if (where != sizeof(myseed))
        myseed = (time(NULL) * getpid()) + getppid();

      (void) close(fd);
    }

    Random::seed(myseed);
  }

  // ------------------------------------------------------------------
  void Random::seed(unsigned int myseed) {
    srandom(myseed);
  }

  // ------------------------------------------------------------------
  long int Random::random(long int max) {
    if (max <= 0)
      return ::random();
    return (long int) (((double) max)*::random() / (1.+RAND_MAX));
  }

}
