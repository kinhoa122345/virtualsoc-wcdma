//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PROFILING_HPP
#define PROFILING_HPP

#include <libsimsoc/display.hpp>
#include <sys/time.h>
#include <iomanip>
#include <cassert>

namespace simsoc {

inline void timeval_subtract(timeval * result, const timeval * x, const timeval * y) {
  if (x->tv_usec < y->tv_usec) {
    result->tv_usec = 1000000 + x->tv_usec - y->tv_usec;
    assert(x->tv_sec>=y->tv_sec+1);
    result->tv_sec = x->tv_sec - y->tv_sec - 1;
  } else {
    result->tv_usec = x->tv_usec - y->tv_usec;
    assert(x->tv_sec>=y->tv_sec);
    result->tv_sec = x->tv_sec - y->tv_sec;
  }
}

inline void timeval_add(timeval * result, const timeval * x, const timeval * y) {
  result->tv_usec = x->tv_usec + y->tv_usec;
  result->tv_sec = x->tv_sec + y->tv_sec;
  if (result->tv_usec>=1000000) {
    result->tv_usec-= 1000000;
    result->tv_sec++;
  }
}

  class TimeVal: public Printable {
public:

  TimeVal() {
    tv.tv_sec = 0;
    tv.tv_usec = 0;
  }

  TimeVal(const TimeVal &tv_) {
    tv.tv_sec = tv_.tv.tv_sec;
    tv.tv_usec = tv_.tv.tv_usec;
  }

  void set() {
    gettimeofday(&tv,NULL);
  }

  TimeVal operator+(const TimeVal &tv_) const {
    TimeVal result;
    timeval_add(&result.tv,&tv,&tv_.tv);
    return result;
  }

  TimeVal operator-(const TimeVal &tv_) const {
    TimeVal result;
    timeval_subtract(&result.tv,&tv,&tv_.tv);
    return result;
  }

  std::ostream &display(std::ostream &os) const {
    os <<std::dec <<tv.tv_sec <<'.';
    os.setf(std::ios::right);
    os <<std::setfill('0');
    os.width(6);
    return os <<tv.tv_usec;
  }

protected:
  timeval tv;
};

} // namespace simsoc

#endif //PROFILING_HPP
