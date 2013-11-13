//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef DECODE_ARGS_HPP
#define DECODE_ARGS_HPP

#include "libsimsoc/display.hpp"

struct ISC_Args {
  simsoc::TraceLevel trace_level;
  const char * isc_file;
  const char * out_file;

  ISC_Args():
    trace_level(simsoc::WARNING_LEVEL), isc_file(0), out_file(0)
  {}

  void parse(int argc, char *argv[]);
  void usage();
};

#endif //DECODE_ARGS_HPP
