//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include <libsimsoc/context.hpp>
#include <libsimsoc/processors/processor.hpp>

#include <algorithm>

using namespace std;

namespace simsoc {

  static bool parameter_cmp(const ParameterAbstract *a,const ParameterAbstract *b) {
    return *a<*b;
  }

  Context::Context(sc_core::sc_module_name name):
    Module(name,WARNING_LEVEL,true),
    start(0), period(1), number(0),
    elf_loader(NULL),
    parameters(),
    files(),
    progname(NULL),
    debugger_port(7000),
    arch(LAST_ARCH),
    elf_brk(0),
    user_arg_set(false),
    user_argc(0),
    user_argv(NULL)
  {}

  Context::~Context() {
    delete elf_loader;
  }

  void Context::end_of_elaboration() {
    if (!progname) {
      error() <<"simsoc_init(argc,argv) has not been called.\n";
      exit(1);
    }

    vector<module_tracelevel>::iterator it=particular_tracelevel.begin();
    vector<module_tracelevel>::const_iterator vect_end=particular_tracelevel.end();
    std::map<const char*, Module*, ltstr>::const_iterator map_end=modules().end();
    while (it!=vect_end) {
      if (modules().find((it->first).c_str())==map_end)
        warning() <<"Module \"" <<it->first
                  <<"\" does not exist. Trace level option ignored.\n";
      ++it;
    }
  }

  void Context::print_usage() {
    cout <<"Usage: " <<progname <<" <parameters> <ELF files>\n"
         <<"* global parameters:\n"
         <<"  -q or -q=<module_name> \tdisable warnings for all or for <module_name>\n"
         <<"  -v or -v=<module_name>\tbe verbose\n"
         <<"  -V or -V=<module_name>\tbe very verbose\n"
         <<"  -h\tprint this help and exit before simulation\n"
         <<"  <ELF files>\tspecify the corresponding ELFs file of all processors in sequence.\n"
      "\t\tFor processors that do not have to load ELF file, use the string \"NoELF\" instead.\n"
         <<"  -userarg\tspecify after all of the simulation options as a start of the user level arguments\n";
    sort(parameters.begin(),parameters.end(),&parameter_cmp);
    const char *previous_kind = "global parameters";
    for (size_t i=0, ei=parameters.size(); i!=ei; ++i) {
      ParameterAbstract *pa = parameters[i];
      assert(pa);
      if (strcmp(pa->kind,previous_kind)) {
        previous_kind = pa->kind;
        cout <<"* " <<previous_kind <<" parameters:\n";
      }
      cout <<"  " <<pa->name;
      pa->print_usage(cout);
      cout <<'\t' <<pa->message <<'\n';
      if (pa->is_set())
        cout <<"\tcurrent value: " <<*pa <<'\n';
    }
  }

  void Context::read_args(int argc, char **argv) {
    int usage_status = 0;
    assert(argc>=1);
    progname = argv[0];
    for (int i = 1; i<argc; ++i) {
      if (argv[i][0]=='-') {
        short opt_len=strcspn(argv[i],"=");
        string arg_type(argv[i],opt_len);
        if (!arg_type.compare("-v")) {
          if (argv[i][opt_len]=='\0') { // classic option
            main_output_manager.set_trace_level(INFO_LEVEL);
            this->set_trace_level(INFO_LEVEL);
          } else { // stock module name for specific option
            module_tracelevel tmp(argv[i]+opt_len+1,INFO_LEVEL);
            particular_tracelevel.push_back(tmp);
          }
        } else if (!arg_type.compare("-q")) {
          if (argv[i][opt_len]=='\0') { // classic option
            main_output_manager.set_trace_level(ERROR_LEVEL);
            this->set_trace_level(ERROR_LEVEL);
          } else { // stock module name for specific option
            module_tracelevel tmp(argv[i]+opt_len+1,ERROR_LEVEL);
            particular_tracelevel.push_back(tmp);
          }
        } else if (!arg_type.compare("-V")) {
          if (argv[i][opt_len]=='\0') { // classic option
            main_output_manager.set_trace_level(DEBUG_LEVEL);
            this->set_trace_level(DEBUG_LEVEL);
          } else { // stock module name for specific option
            module_tracelevel tmp(argv[i]+opt_len+1,DEBUG_LEVEL);
            particular_tracelevel.push_back(tmp);
          }
        } else if (!arg_type.compare("-h")||!arg_type.compare("-H")||
                   !arg_type.compare("--help")||!arg_type.compare("-help")) {
          usage_status = 1;
        } else if (!arg_type.compare("-userarg")){
          user_arg_set=true;
          user_argc=argc-i;
          user_argv=&argv[i];
          break;
        } else if (!arg_type.compare("-s")) {
          if (strlen(argv[i])<=3) {
            error() <<"missing number for parameter -s=\n";
            exit(1);
          }
          start = strtoull(argv[i]+3,NULL,0);
        } else if (!arg_type.compare("-p")) {
          if (strlen(argv[i])<=3) {
            error() <<"missing number for parameter -p=\n";
            exit(1);
          }
          period = strtoull(argv[i]+3,NULL,0);
        } else if (!arg_type.compare("-n")) {
          if (strlen(argv[i])<=3) {
            error() <<"missing number for parameter -n=\n";
            exit(1);
          }
          number = strtoull(argv[i]+3,NULL,0);
        } else {
          size_t p = 0, ep = parameters.size();
          for (; p!=ep; ++p)
            if (!arg_type. compare(parameters[p]->name)) {
              const char *tmp = strchr(argv[i],'=');
              parameters[p]->set(tmp? tmp+1: "");
              break;
            }
          if (p==ep) {
            error() <<"unrecognized option: " <<argv[i] <<"\n\n";
            if (usage_status==0)
              usage_status = 2; // exit will be called at the end of this method
          }
        }
      } else {
        files.push_back(argv[i]);
      }
    }
    if (usage_status>0) {
      print_usage();
      exit(usage_status-1);
    }
    sort(particular_tracelevel.begin(),particular_tracelevel.end());
  }

  void Context::register_parameter(ParameterAbstract *pa) {
    parameters.push_back(pa);
  }
  
  TraceLevel Context::get_tracelevel(std::string module_name, TraceLevel default_trlvl) {
    vector<module_tracelevel>::iterator it = 
      lower_bound(particular_tracelevel.begin(),
                  particular_tracelevel.end(),
                  module_tracelevel(module_name,INHERIT_LEVEL));
    if (it!=particular_tracelevel.end() && it->first==module_name)
      return it->second;    
    else
      return default_trlvl;
  }

  const char *Context::register_processor(ProcessorBase *proc) {
    if (!elf_loader)
      elf_loader = new ElfLoader("ELF_LOADER");
    if (files.empty()) {
      error() <<"missing ELF file for processor " <<proc->name() <<endl;
      exit(1);
    }
    const char *program_file = files.front();
    elf_loader->set_file(proc,program_file);
    if (files.size()>1)
      files.pop_front();
    return program_file;
  }

  void Context::compute_arch() {
    if (arch==LAST_ARCH) {
      if (files.empty()) {
        error() <<"no ELF file available\n";
        exit(1);
      }
      ElfFile elf_file(files.front());
      arch = elf_file.get_architecture();
      big_endian = elf_file.is_big_endian();
    }
  }

  Architecture Context::get_architecture() {
    compute_arch();
    assert(arch!=LAST_ARCH);
    return arch;
  }

  bool Context::is_big_endian() {
    compute_arch();
    assert(arch!=LAST_ARCH);
    return big_endian;
  }

  MIPS_SpecFlag Context::get_mips_spec() {
    if (files.empty()) {
      error() <<"no ELF file available\n";
      exit(1);
    }
    ElfFile elf_file(files.front());
    return elf_file.get_mips_spec();
  }

  uint32_t Context::get_elf_brk(){
    if (files.empty()) {
      error() <<"no ELF file available\n";
      exit(1);
    }
    ElfFile elf_file(files.front());//to optimize
    arch = elf_file.get_architecture();
    assert(arch!=LAST_ARCH);
    elf_brk = elf_file.get_elf_brk();
    return elf_brk;
  }

  bool Context::has_user_arg(){
    return user_arg_set;
  }

  int Context::get_user_argc(){
    return user_argc;
  }

  char** Context::get_user_argv(){
    return user_argv;
  }

  Context &main_context() { // build on 1st use
    static Context *env_ptr = new Context("MAIN_CONTEXT");
    return *env_ptr;
  }

  void simsoc_init(int argc, char **argv) {
    main_context().read_args(argc,argv);
  }

  bool simsoc_get_user_arg(int& argc,char*** argv){
    if( main_context().has_user_arg()){
      argc=main_context().get_user_argc();
      *argv=main_context().get_user_argv();
      return true;
    }else
      return false;
  }

} // namespace simsoc
