//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "armgen_dpi.hpp"
#include "armgen_loadstore.hpp"
#include "armgen_mli.hpp"
#include "armgen_swp.hpp"
#include "armgen_b.hpp"
#include "armgen_clz.hpp"
#include "armgen_swi.hpp"
#include "armgen_ldmstm.hpp"
#include "armgen_mrsmsr.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>

/*
 * main() program. Generate successively all types of instructions
 */

using namespace std;

int main(int argc, char* argv[]) {

  cout << "Generating files for data processing instructions" << endl;
  DPI_Generator dpi_gen;
  dpi_gen.generate();

  cout << "Generating files for load and store instructions" << endl;
  LoadStoreGenerator load_store_gen;
  load_store_gen.generate();

  cout << "Generating files for multiply instructons" << endl;
  MLI_Generator mli_gen;
  mli_gen.generate();

  cout << "Generating files for swp instructons" << endl;
  SWP_Generator swp_gen;
  swp_gen.generate();

  cout << "Generating files for branch instructons" << endl;
  B_Generator b_gen;
  b_gen.generate();

  cout << "Generating files for clz instructon" << endl;
  CLZ_Generator clz_gen;
  clz_gen.generate();

  cout << "Generating files for swi instructon" << endl;
  SWI_Generator swi_gen;
  swi_gen.generate();

  cout << "Generating files for ldm and stm instructons" << endl;
  LdmStmGenerator ldmstm_gen;
  ldmstm_gen.generate();

  cout << "Generating files for mrs and msr instructons" << endl;
  MRSMSR_Generator mrsmsr_gen;
  mrsmsr_gen.generate();

  if (argc==3&&!strcmp(argv[1],"-o")) {
    ofstream empty_file;
    empty_file.open(argv[2]);
    empty_file.close();
  }

  return 0;
}
