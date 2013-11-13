//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "llvm_gen_parameters.hpp"

namespace simsoc {

  ParameterInt DT3_threshold("Mode DT=3", "-ct",
                             "the threshold for dynamic compilation",120000);

  ParameterStrQueue DT3_prof_files("Mode DT=3", "-DT3-prof",
                               "write profiling data to this file");

  ParameterBool DT3_prof_total("Mode DT=3", "-DT3-prof-total",
                                "display the total compilation time");

  ParameterBool DT3_server("Mode DT=3", "-DT3-server",
                           "Enable the parallel compilation server");

  ParameterInt DT3_comp_queue_size("Mode DT=3", "-DT3-cq-size",
                                   "Size of the compilation server queue", 16);

  ParameterInt DT3_comp_queue_threshold("Mode DT=3", "-DT3-cqt",
                                  "Threshold for the insertion inside the server queue",
                                        4096);

} // namespace simsoc
