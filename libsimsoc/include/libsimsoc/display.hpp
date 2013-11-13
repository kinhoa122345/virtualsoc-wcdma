//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

// define NDEBUG if NINFO defined
#ifdef NINFO
#ifndef NDEBUG
#define NDEBUG
#endif
#endif

#include <cstdlib>
#include <iostream>
#include <sstream>

namespace simsoc {

const int BUG_NUM = 9;
const int TBD_NUM = 8;

#define HERE '[' <<__FILE__ <<':' <<std::dec <<__LINE__ <<"] "

#define TODO(msg) {                                             \
    ::simsoc::error() <<HERE <<"not implemented yet: " <<msg <<std::endl;       \
    simsoc::gdb_bkpt(simsoc::TBD_NUM);                                          \
    exit(simsoc::TBD_NUM);}

#define UNREACHABLE {                                                   \
    ::simsoc::error() <<HERE <<"this line should be unreachable" <<std::endl; \
    simsoc::gdb_bkpt(simsoc::BUG_NUM);                                          \
    exit(simsoc::BUG_NUM);}

void gdb_bkpt(unsigned int n);

struct NullStream: std::ostream
{
  NullStream(): std::ios(0), std::ostream(0) {}
};
extern NullStream null_stream;

struct VeryNullStream {
  const VeryNullStream& operator<<(std::ostream& (*f)(std::ostream&)) const {
    return *this;
  }
};
template<typename T>
const VeryNullStream& operator<<(const VeryNullStream &x, const T &y) {return x;}
extern VeryNullStream very_null_stream;

typedef enum {INHERIT_LEVEL=0,
              ERROR_LEVEL=1,
              WARNING_LEVEL=2,
              INFO_LEVEL=3,
              DEBUG_LEVEL=4} TraceLevel;

struct OutputManager {
  OutputManager(std::ostream &e = std::cout,
                std::ostream &w = std::cout,
                std::ostream &i = null_stream,
                std::ostream &d = null_stream);

  void set_trace_level(TraceLevel l);

  void set_error_stream(std::ostream &os);
  void set_warning_stream(std::ostream &os);
  void set_info_stream(std::ostream &os);
  void set_debug_stream(std::ostream &os);

  std::ostream &get_error_stream()   {return *p_error;}
  std::ostream &get_warning_stream() {return *p_warning;}
  std::ostream &get_info_stream()    {return *p_info;}
  std::ostream &get_debug_stream()   {return *p_debug;}

private:
  friend std::ostream &error();
  friend std::ostream &warning();
#ifndef NINFO
  friend std::ostream &info();
#endif
#ifndef NDEBUG
  friend std::ostream &debug();
#endif

  std::ostream *p_error;
  std::ostream *p_warning;
  std::ostream *p_info;
  std::ostream *p_debug;
};
extern OutputManager main_output_manager;

inline std::ostream &error()   {return *main_output_manager.p_error   <<"Error:   ";}
inline std::ostream &warning() {return *main_output_manager.p_warning <<"Warning: ";}

#ifdef NINFO
inline VeryNullStream &info()  {return very_null_stream;}
inline VeryNullStream &debug() {return very_null_stream;}
#elif defined NDEBUG
inline std::ostream &info()    {return *main_output_manager.p_info    <<"Info:    ";}
inline VeryNullStream &debug() {return very_null_stream;}
#else
inline std::ostream &info()    {return *main_output_manager.p_info    <<"Info:    ";}
inline std::ostream &debug()   {return *main_output_manager.p_debug   <<"Debug:   ";}
#endif

struct Printable {
  virtual ~Printable() {}
  virtual std::ostream& display(std::ostream& os) const =0;
};
inline std::ostream& operator<<(std::ostream& os, const Printable& obj) {
  return obj.display(os);
}

// converter from any T to string
template <class T>
std::string string_of(const T &val, bool hexa = false) {
  std::ostringstream oss(std::ostringstream::out);
  if (hexa)
    oss <<std::showbase <<std::hex;
  oss <<val;
  return oss.str();
}

} // namespace simsoc

#endif //DISPLAY_HPP
