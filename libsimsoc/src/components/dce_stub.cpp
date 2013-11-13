//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "dce_stub.hpp"
using namespace sc_core;
using namespace std;

namespace simsoc {

DCE_Stub::DCE_Stub(sc_core::sc_module_name name):
  Module(name){}

void DCE_Stub::send(uint8_t c){
  debug() <<"send character '" <<c <<"' (" <<(int) c <<")\n";
}

void DCE_Stub::set_rts(bool rts_signal){
  info() <<"set rts to " <<rts_signal <<endl;
}

void DCE_Stub::set_dtr(bool dtr_signal){
  info() <<"set rts to " <<dtr_signal <<endl;
}

} // namespace simsoc
