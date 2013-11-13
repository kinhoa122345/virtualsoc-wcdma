//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include <assert.h>
#include <fstream>
#include "libsimsoc/display.hpp"
#include "isc.hpp"
#include "isc_parse.hpp"
#include "isc_args.hpp"

using namespace std;
using namespace simsoc;

int main(int argc, char *argv[])
{
  ISC_Args args;
  args.parse(argc,argv);
  main_output_manager.set_trace_level(args.trace_level);
  ifstream is;
  is.open(args.isc_file);
  ofstream os;
  os.open(args.out_file);
  Isc * I = isc_parse(is,os,args.isc_file);
  assert(I);
  I->gencode(os);
  isc_epilogue(is,os);
  os.close();
  is.close();
  delete(I);
  return 0;
}
