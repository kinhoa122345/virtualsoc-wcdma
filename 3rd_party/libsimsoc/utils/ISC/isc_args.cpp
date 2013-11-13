//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "isc_args.hpp"
#include "libsimsoc/display.hpp"

using namespace std;
using namespace simsoc;

void ISC_Args::parse(int argc, char *argv[]) {
  for (unsigned n = 1; n<(unsigned) argc; ++n) {
    string s = argv[n];
    if (s[0]=='-') {
      if (!string(s).compare("-v")) {
        trace_level = INFO_LEVEL;
      } else if (!string(s).compare("-q")) {
        trace_level = ERROR_LEVEL;
      } else if (!string(s).compare("-V")) {
        trace_level = DEBUG_LEVEL;
      } else if (!string(s).compare("-o")) {
        if (out_file) {
          error() <<"[command line parsing] too many '-o'" <<endl;
          usage();
          exit(2);
        } else {
          if (++n==(unsigned) argc) {
            error() <<"[command line parsing] nothing found after '-o'" <<endl;
            usage();
            exit(2);
          }
          out_file = argv[n];
        }
      } else {
        warning() <<"[command line parsing] unrecognized option: " <<s <<endl;
      }
    } else {
      if (isc_file) {
        error() <<"[command line parsing] too many iscs file found, or missing '-o'" <<endl;
        usage();
        exit(2);
      } else
        isc_file = argv[n];
    }
  }
  if (!isc_file) {
    error() <<"[command line parsing] no files found" <<endl;
    usage();
    exit(2);
  }
  if (!out_file) {
    error() <<"[command line parsing] no out file found" <<endl;
    usage();
    exit(2);
  }
}

void ISC_Args::usage() {
  cout <<"usage: isc [-v][-q] <isc_file> -o <out_file>" <<endl
       <<"\t-q\tdo not print warnings" <<endl
       <<"\t-v\tbe verbose" <<endl
       <<"\t-V\tbe very verbose" <<endl;
}
