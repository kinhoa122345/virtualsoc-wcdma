//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include <cassert>

#include <libsimsoc/display.hpp>


using namespace std;

namespace simsoc {

void gdb_bkpt(unsigned int n) {
  // function to ease putting a gdb breakpoint on all UNREACHABLE ot TODO calls.
}

NullStream null_stream;
VeryNullStream very_null_stream;
OutputManager main_output_manager;

OutputManager::OutputManager(std::ostream &e,
                             std::ostream &w,
                             std::ostream &i,
                             std::ostream &d):
  p_error(&e), p_warning(&w), p_info(&i), p_debug(&d)
{
  std::cout <<std::showbase;
  std::cout <<std::showbase;
}

void OutputManager::set_trace_level(TraceLevel l) {
  switch (l) {
  case INHERIT_LEVEL:
    error() <<HERE <<"the main output manager cannot use the \"inherit\" level" <<endl;
    exit(1);
  case ERROR_LEVEL:
    p_warning = &null_stream;
    p_info = &null_stream;
    p_debug = &null_stream;
    break;
  case WARNING_LEVEL:
    p_warning = &cout;
    p_info = &null_stream;
    p_debug = &null_stream;
    break;
  case INFO_LEVEL:
    p_warning = &cout;
#ifdef NINFO
    warning() <<"INFO level traces have been statically disabled\n";
#else
    p_info = &cout;
    p_debug = &null_stream;
#endif
    break;
  case DEBUG_LEVEL:
    p_warning = &cout;
#ifdef NINFO
    warning() <<"INFO and DEBUG level traces have been statically disabled\n";
#elif defined NDEBUG
    p_info = &cout;
    warning() <<"DEBUG level traces have been statically disabled\n";
#else
    p_info = &cout;
    p_debug = &cout;
#endif
    break;
  }
}

void OutputManager::set_error_stream(ostream &os) {
  p_error = &os;
}

void OutputManager::set_warning_stream(ostream &os) {
  p_warning = &os;
}

void OutputManager::set_info_stream(ostream &os) {
#ifdef NINFO
  warning() <<"INFO and DEBUG level traces have been statically disabled\n";
#else
  p_info = &os;
#endif
}

void OutputManager::set_debug_stream(ostream &os) {
#ifdef NINFO
  warning() <<"INFO and DEBUG level traces have been statically disabled\n";
#elif defined NDEBUG
  warning() <<"DEBUG level traces have been statically disabled\n";
#else
  p_debug = &os;
#endif
}

} // namespace simsoc
