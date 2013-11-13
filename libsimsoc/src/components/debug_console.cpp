//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "debug_console.hpp"
#include "libsimsoc/display.hpp"
#include "libsimsoc/processors/common.hpp"
#include "libsimsoc/context.hpp"

using namespace std;
using namespace sc_core;

namespace simsoc {

  DebugConsole::DebugConsole(sc_module_name name,
                             StopBox *sb, uint32_t _wait_num, bool be):
    Module(name),
    str_get_size(0),
    stop_box(sb), wait_num(_wait_num),
    half_of_64_loaded(false), half_of_64(0), big_endian(be)
  {
    target_socket.register_b_transport(this,&DebugConsole::b_transport);//bind slave port
    debug() <<"constructor called" <<endl;
  }

  DebugConsole::~DebugConsole() {
    debug() <<"destructor called" <<endl;
  }

  void DebugConsole::b_transport(tlm::tlm_generic_payload &payload,
                                 sc_core::sc_time &delay_time) {
    assert(payload.get_response_status()==tlm::TLM_INCOMPLETE_RESPONSE);
    if (payload.get_streaming_width()<payload.get_data_length()) {
      warning() <<"received transaction with invalid streaming width.\n";
      payload.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
    } else if (payload.get_byte_enable_ptr()) {
      warning() <<"byte enable not supported.\n";
      payload.set_response_status(tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE);
    } else {
      switch (payload.get_command()) {
      default:
        warning() <<"command not supported.\n";
        payload.set_response_status(tlm::TLM_COMMAND_ERROR_RESPONSE);
        break;
      case tlm::TLM_WRITE_COMMAND:
        if (payload.get_data_length()==4) {
          write_word(static_cast<uint32_t>(payload.get_address()),
                     *reinterpret_cast<uint32_t*>(payload.get_data_ptr()));
        } else if (payload.get_data_length()==2) {
          // get addr and fix endianness
          const uint32_t addr = static_cast<uint32_t>(payload.get_address())&~2;
          write_half(addr, *reinterpret_cast<uint16_t*>(payload.get_data_ptr()));
        } else if (payload.get_data_length()==1) {
          // get addr and fix endianness
          const uint32_t addr = static_cast<uint32_t>(payload.get_address())&~3;
          write_byte(addr, *reinterpret_cast<uint8_t*>(payload.get_data_ptr()));
        } else {
          warning() <<"received read transaction with invalid data length"
            " (should be 1 or 2 or 4).\n";
          payload.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
        }
        payload.set_response_status(tlm::TLM_OK_RESPONSE);
        break;
      case tlm::TLM_READ_COMMAND:
        if (payload.get_data_length()==4) {
          *reinterpret_cast<uint32_t*>(payload.get_data_ptr()) =
            read_word(static_cast<uint32_t>(payload.get_address()));
          payload.set_response_status(tlm::TLM_OK_RESPONSE);
        } else {
          warning() <<"received read transaction with invalid data length"
            " (should be 4).\n";
          payload.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
        }
        break;
      }
    }
  }

  uint32_t DebugConsole::read_word(uint32_t addr) {
    switch (addr) {
    case STR_GET_SIZE:
      return str_get_size;
    default:
      error() <<"invalid read word access at offset " <<hex <<addr <<".\n";
      exit(1);
    }
    return 0;
  }

  bool DebugConsole::do_print(uint32_t data) {
    if (half_of_64_loaded) {
      half_of_64_loaded = false;
      return true;
    } else {
      half_of_64_loaded = true;
      half_of_64 = data;
      return false;
    }
  }

  uint64_t DebugConsole::merge_halves(uint32_t low, uint32_t high) {
    if (same_endianness())
      return static_cast<uint64_t>(high)<<32|static_cast<uint64_t>(low);
    else
      return static_cast<uint64_t>(low)<<32|static_cast<uint64_t>(high);
  }

  void DebugConsole::write_word(uint32_t addr, uint32_t data) {
    switch (addr) {
    case PUT_DEC_INT:
      cout <<dec <<(int32_t) data;
      return;
    case PUT_DEC_UINT:
      cout <<dec <<data;
      return;
    case PUT_HEX_UINT:
      cout <<hex <<data;
      return;
    case PUT_DEC_INT_LOW:
      if (do_print(data))
        cout <<dec <<static_cast<int64_t>(merge_halves(data,half_of_64));
      return;
    case PUT_DEC_INT_HIGH:
      if (do_print(data))
        cout <<dec <<static_cast<int64_t>(merge_halves(half_of_64,data));
      return;
    case PUT_DEC_UINT_LOW:
      if (do_print(data))
        cout <<dec <<merge_halves(data,half_of_64);
      return;
    case PUT_DEC_UINT_HIGH:
      if (do_print(data))
        cout <<dec <<merge_halves(half_of_64,data);
      return;
    case PUT_HEX_UINT_LOW:
      if (do_print(data))
        cout <<hex <<merge_halves(data,half_of_64);
      return;
    case PUT_HEX_UINT_HIGH:
      if (do_print(data))
        cout <<hex <<merge_halves(half_of_64,data);
      return;

    case STR_PUT_ADDR:
      {
        tlm::tlm_generic_payload pl;
        pl.set_streaming_width(1);
        pl.set_command(tlm::TLM_READ_COMMAND);
        uint8_t value=0;
        if (main_context().get_architecture()==MIPS &&
            main_context().get_mips_spec()==MIPS64) {
          set_payload(pl,sign_ext<uint64_t>(data),(unsigned char*)(&value),1);
          unsigned int tmp = initiator_socket->transport_dbg(pl);
          assert(tmp==1 && "transaction failed");

          for(char c = value; c;) {
            std::cout <<c;
            set_payload(pl, sign_ext<uint64_t>(++data),(unsigned char*)(&c),1);
            tmp = initiator_socket->transport_dbg(pl);
            assert(tmp==1 && "transaction failed");
          }
        } else {//other architecture
          set_payload(pl,data,(unsigned char*)(&value),1);
          unsigned int tmp = initiator_socket->transport_dbg(pl);
          assert(tmp==1 && "transaction failed");

          for (char c = value; c;) {
            std::cout <<c;
            set_payload(pl,++data,(unsigned char*)(&c),1);
            tmp = initiator_socket->transport_dbg(pl);
            assert(tmp==1 && "transaction failed");
          }
        }
      }
      return;

    case STR_GET_ADDR:
      {
        char *buffer = new char[str_get_size];
        cin.getline(buffer,str_get_size);
        uint32_t i = 0;
        tlm::tlm_generic_payload pl;
        unsigned int tmp;
        pl.set_streaming_width(1);
        pl.set_command(tlm::TLM_WRITE_COMMAND);
        if (main_context().get_architecture()==MIPS &&
            main_context().get_mips_spec()==MIPS64) {
          for (; buffer[i]; ++i) {
            set_payload(pl, sign_ext<uint64_t>(data+i),(unsigned char*)(&buffer[i]),1);
            tmp = initiator_socket->transport_dbg(pl);
            assert(tmp==1 && "transaction failed");
          }
          unsigned char value=0;
          set_payload(pl,sign_ext<uint64_t>(data+i),&value,1);
          initiator_socket->transport_dbg(pl);
            assert(tmp==1 && "transaction failed");
        } else { //other architecture
          for (; buffer[i]; ++i){
            set_payload(pl,data+i,(unsigned char*)(&buffer[i]),1);
            tmp = initiator_socket->transport_dbg(pl);
            assert(tmp==1 && "transaction failed");
          }
          unsigned char value=0;
          set_payload(pl,data+i,&value,1);
          tmp = initiator_socket->transport_dbg(pl);
          assert(tmp==1 && "transaction failed");
        }
      }
      return;

    case STR_GET_SIZE:
      str_get_size = data;
      return;
    case HALT:
      if(wait_num--){
        if (stop_box)
          stop_box->stop();
        else {
          info() <<"sc_stop called." <<endl;
          sc_core::sc_stop();
        }
      }
#ifdef PARALLEL
      pthread_exit(0);
#else
      wait(never_notified); // block the process
      UNREACHABLE;
#endif
    case SET_ERROR_LEVEL:
      set_trace_level(ERROR_LEVEL,data);
      return;
    case SET_WARNING_LEVEL:
      set_trace_level(WARNING_LEVEL,data);
      return;
    case SET_INFO_LEVEL:
      set_trace_level(INFO_LEVEL,data);
      return;
    case SET_DEBUG_LEVEL:
      set_trace_level(DEBUG_LEVEL,data);
      return;
    case DTMODE:
      TODO("dynamic modification of the dynamc translation mode");
      return;
    default:
      error() <<"invalid write word access at offset " <<hex <<addr <<".\n";
      exit(1);
    }
  }

  void DebugConsole::write_half(uint32_t addr, uint16_t data) {
    switch (addr) {
    case PUT_DEC_INT:
      cout <<dec <<(int16_t) data;
      return;
    case PUT_DEC_UINT:
      cout <<dec <<data;
      return;
    case PUT_HEX_UINT:
      cout <<hex <<data;
      return;
    default:
      error() <<"invalid write half access at offset " <<hex <<addr <<".\n";
      exit(1);
    }
  }

  void DebugConsole::write_byte(uint32_t addr, uint8_t data) {
    switch (addr) {
    case PUT_CHAR:
      cout <<(char) data;
      return;
    case PUT_DEC_INT:
      cout <<dec <<(int16_t) (int8_t) data;
      return;
    case PUT_DEC_UINT:
      cout <<dec <<(uint16_t) data;
      return;
    case PUT_HEX_UINT:
      cout <<hex <<(uint16_t) data;
      return;
    default:
      error() <<"invalid write byte access at offset " <<hex <<addr <<".\n";
      exit(1);
    }
  }

  void DebugConsole::set_trace_level(TraceLevel tl, uint32_t data) {
    if (data) {
      string s = "";
      tlm::tlm_generic_payload pl;
      unsigned int tmp;
      pl.set_streaming_width(1);
      pl.set_command(tlm::TLM_READ_COMMAND);
      unsigned char value=0;
      set_payload(pl,data,&value,1);
      tmp = initiator_socket->transport_dbg(pl);
      assert(tmp==1 && "transaction failed");
      for (char c = value; c;) {
        s.push_back(c);
        set_payload(pl,++data,(unsigned char*)(&c),1);
        tmp = initiator_socket->transport_dbg(pl);
        assert(tmp==1 && "transaction failed");
      }
      Module::set_trace_level(s.c_str(),tl);
    } else
      main_output_manager.set_trace_level(tl);
  }

} // namespace simsoc
