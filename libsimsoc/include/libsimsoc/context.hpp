//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <libsimsoc/components/elf_loader.hpp>
#include <libsimsoc/module.hpp>
#include <libsimsoc/command_line.hpp>

namespace simsoc {

  struct module_tracelevel: std::pair<std::string,TraceLevel>{
    module_tracelevel(std::string str, TraceLevel TrLvl):std::pair<std::string,TraceLevel>(str,TrLvl){}
    bool operator<(const module_tracelevel& trlvl) const
    {return strcmp(first.c_str(),trlvl.first.c_str())<0; }
  };

  /*
   * The class Context contain data related to the simulation context.
   * It is meant to expand as the simulation includes new features
   */
  class Context: Module {
  public:
    Context(sc_core::sc_module_name name);
    ~Context();
    void end_of_elaboration();
    void print_usage();
    void read_args(int argc, char **argv);
    void register_parameter(ParameterAbstract *pa);
    TraceLevel get_tracelevel(std::string module_name,TraceLevel default_trlvl);

    const char *register_processor(ProcessorBase *p);
    // return the name of the program file executed by this processor

    Architecture get_architecture();
    bool is_big_endian();
    MIPS_SpecFlag get_mips_spec();
    uint32_t get_debugger_port() {return debugger_port++;}
    uint32_t  get_elf_brk();
    bool has_user_arg();
    int get_user_argc();
    char** get_user_argv();

    // for debug:
    uint64_t start;
    uint64_t period;
    uint64_t number;

   private:
    void compute_arch();
    ElfLoader *elf_loader;
    std::vector<ParameterAbstract*> parameters;
    std::deque<char *> files;
    const char *progname;
    uint32_t debugger_port;
    Architecture arch;
    bool big_endian;
    uint32_t elf_brk;
    bool user_arg_set;
    int user_argc;
    char** user_argv;

   std::vector<module_tracelevel> particular_tracelevel;
  };

  extern Context &main_context();

  void simsoc_init(int argc, char **argv);
  bool simsoc_get_user_arg(int& argc, char*** argv);

} // namespace simsoc

#endif // CONTEXT_HPP
