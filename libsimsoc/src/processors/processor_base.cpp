//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include <libsimsoc/processors/processor_base.hpp>

namespace simsoc {

  ProcessorBase::ProcessorBase(sc_core::sc_module_name nm, Architecture arch):
    Module(nm), architecture(arch)
  { 
    #define NO_MMU
    #ifndef NO_MMU
    const char *program_file = main_context().register_processor(this);
    info()
      << "executing program: " << program_file
      << std::endl;
    #endif
  }

  void ProcessorBase::set_endian_little() {
    error() <<"Little endian is not implemented for this architecture.\n";
    exit(1);
  }

  void ProcessorBase::set_endian_big() {
    error() <<"Big endian is not implemented for this architecture.\n";
    exit(1);
  }

} // namespace simsoc
