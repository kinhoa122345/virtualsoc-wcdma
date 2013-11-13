//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ISS_EXCEPTION_HPP
#define ISS_EXCEPTION_HPP

#include <stdexcept>

namespace simsoc {

  class ISS_Exception: public std::exception {
  public:
    const char *what() const throw() {return msg;}
    explicit ISS_Exception(const char *message): exception(), msg(message) {}
    ~ISS_Exception() throw() {}
  private:
    const char *msg;
  };

} // namespace simsoc

#endif // ISS_EXCEPTION_HPP
