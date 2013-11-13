//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef MODULE_HPP
#define MODULE_HPP

#include <iostream>
#include <map>
#include <cstring>
#include <algorithm>
#include <utility>
#include <systemc>
#include "libsimsoc/display.hpp"

namespace simsoc {

struct ltstr {
  bool operator()(const char* s1, const char* s2) const
  {return strcmp(s1, s2) < 0;}
};

class Module: public sc_core::sc_module {
public:
  Module(sc_core::sc_module_name name,
         TraceLevel l = INHERIT_LEVEL,
         bool is_context=false);

  void set_trace_level(TraceLevel l);
  void set_initial_tracelevel(TraceLevel l);

  void set_error_stream(std::ostream &os);
  void set_warning_stream(std::ostream &os);
  void set_info_stream(std::ostream &os);
  void set_debug_stream(std::ostream &os);

  std::ostream &error() const;
  std::ostream &warning() const;

#ifdef NINFO
  VeryNullStream &info() const {return very_null_stream;}
  VeryNullStream &debug() const {return very_null_stream;}
#elif defined NDEBUG
  std::ostream &info() const;
  VeryNullStream &debug() const {return very_null_stream;}
#else
  std::ostream &info() const;
  std::ostream &debug() const;
#endif

  static Module* find_module(const char *name);
  static void set_trace_level(const char *name, TraceLevel tl);
  static void set_error_level(const char *name);
  static void set_warning_level(const char *name);
  static void set_info_level(const char *name);
  static void set_debug_level(const char *name);

protected:
  static std::map<const char*, Module*, ltstr> &modules();

private:
  std::ostream *p_error;
  std::ostream *p_warning;
  std::ostream *p_info;
  std::ostream *p_debug;

};

} // namespace simsoc

#endif /* MODULE_HPP */
