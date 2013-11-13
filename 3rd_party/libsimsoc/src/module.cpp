//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include <libsimsoc/module.hpp>
#include <libsimsoc/context.hpp>


using namespace std;


namespace simsoc {

  std::map<const char*, Module*, ltstr> &Module::modules() {
    // build on 1st use
    static std::map<const char*, Module*, ltstr> *modules_ptr =
      new std::map<const char*, Module*, ltstr>();
    return *modules_ptr;
  }

  Module::Module(sc_core::sc_module_name name, TraceLevel l,bool is_context):
    sc_module(name),
    p_error(NULL),
    p_warning(NULL),
    p_info(NULL),
    p_debug(NULL)
  {
    if (is_context)
      set_trace_level(l);
    else 
      set_initial_tracelevel(l);
    modules()[this->name()] = this;
  }
  
  void Module::set_initial_tracelevel(TraceLevel l) {
    set_trace_level(main_context().get_tracelevel(this->name(),l));
  }

  void Module::set_trace_level(TraceLevel l) {
    switch (l) {
    case INHERIT_LEVEL: {
      sc_object* o = get_parent();
      if (!o) {
        p_error   = &main_output_manager.get_error_stream();
        p_warning = &main_output_manager.get_warning_stream();
        p_info    = &main_output_manager.get_info_stream();
        p_debug   = &main_output_manager.get_debug_stream();
        return;
      }
      Module* m = dynamic_cast<Module*>(o);
      if (!m) {
        p_error   = &main_output_manager.get_error_stream();
        p_warning = &main_output_manager.get_warning_stream();
        p_info    = &main_output_manager.get_info_stream();
        p_debug   = &main_output_manager.get_debug_stream();
        return;
      }
      p_error   = m->p_error;
      p_warning = m->p_warning;
      p_info    = m->p_info;
      p_debug   = m->p_debug;
      break;
    }
    case ERROR_LEVEL:
      p_error   = &cout;
      p_warning = &null_stream;
      p_info    = &null_stream;
      p_debug   = &null_stream;
      break;
    case WARNING_LEVEL:
      p_error   = &cout;
      p_warning = &cout;
      p_info    = &null_stream;
      p_debug   = &null_stream;
      break;
    case INFO_LEVEL:
      p_error   = &cout;
      p_warning = &cout;
#ifdef NINFO
      warning() <<"INFO level traces have been statically disabled\n";
#else
      p_info  = &cout;
      p_debug = &null_stream;
#endif
      break;
    case DEBUG_LEVEL:
      p_error   = &cout;
      p_warning = &cout;
#ifdef NINFO
      warning() <<"INFO and DEBUG level traces have been statically disabled\n";
#elif defined NDEBUG
      p_info = &cout;
      warning() <<"DEBUG level traces have been statically disabled\n";
#else
      p_info  = &cout;
      p_debug = &cout;
#endif
      break;
    }
  }

  void Module::set_error_stream(ostream &os) {
    p_error = &os;
  }

  void Module::set_warning_stream(ostream &os) {
    p_warning = &os;
  }

  void Module::set_info_stream(ostream &os) {
#ifdef NINFO
    warning() <<"INFO and DEBUG level traces have been statically disabled\n";
#else
    p_info = &os;
#endif
  }

  void Module::set_debug_stream(ostream &os) {
#ifdef NINFO
    warning() <<"INFO and DEBUG level traces have been statically disabled\n";
#elif defined NDEBUG
    warning() <<"DEBUG level traces have been statically disabled\n";
#else
    p_debug = &os;
#endif
  }

  std::ostream &Module::error() const {
    return *p_error <<"Error: [" <<name() <<" @ " <<sc_core::sc_time_stamp() <<"] ";}
  std::ostream &Module::warning() const {
    return *p_warning <<"Warning: [" <<name() <<" @ " <<sc_core::sc_time_stamp() <<"] ";}

#ifdef NINFO
#elif defined NDEBUG
  std::ostream &Module::info() const {
    return *p_info <<'[' <<name() <<" @ " <<sc_core::sc_time_stamp() <<"] ";}
#else
  std::ostream &Module::info() const {
    return *p_info <<'[' <<name() <<" @ " <<sc_core::sc_time_stamp() <<"] ";}
  std::ostream &Module::debug() const {
    return *p_debug <<'[' <<name() <<" @ " <<sc_core::sc_time_stamp() <<"] ";}
#endif

  Module* Module::find_module(const char *name) {
    map<const char*, Module*>::iterator i = modules().find(name);
    if (i==modules().end())
      return NULL;
    else
      return i->second;
  }

  void Module::set_trace_level(const char *name, TraceLevel tl) {
    Module *m = Module::find_module(name);
    if (m)
      m->set_trace_level(tl);
    else {
      ::simsoc::warning() <<"module \"" <<name
                          <<"\" not found; \"set_trace_level\" request ignored.\n";
    }
  }

  void Module::set_error_level(const char *name) {
    set_trace_level(name,ERROR_LEVEL);
  }
  void Module::set_warning_level(const char *name) {
    set_trace_level(name,WARNING_LEVEL);
  }
  void Module::set_info_level(const char *name) {
    set_trace_level(name,INFO_LEVEL);
  }
  void Module::set_debug_level(const char *name) {
    set_trace_level(name,DEBUG_LEVEL);
  }

} // namespace simsoc
