//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// Implementation of "mmu.hpp"
// This file is included only by "mmu.cpp"
#include "mmu.hpp"

// #define DEBUG_SIMSOC

using namespace std;

namespace simsoc {
  // initilization
  template <typename word_t>
  MMU<word_t>::MMU(sc_core::sc_module_name name, Processor *proc_, int IDvar, int TILE_ID):  
    Module(name),
    ID(IDvar),
    hmemory(),
    iTLBs(NULL), dTLBs(NULL), user_mode(true),
    proc(proc_)
    #ifdef NO_MMU
    ,wr_arm11("wr_arm11",IDvar,TILE_ID)
    #endif
  {
    #ifdef DEBUG_SIMSOC
    cout << "MMU IDvar " << hex << (int)IDvar << endl;
    cout << "MMU ID " << hex << (int)ID << endl;
    #endif
    isUnified = getTLBs();
    #ifndef NO_MMU
    pl.set_streaming_width(sizeof(word_t));
    rw_socket.register_invalidate_direct_mem_ptr(this, &MMU<word_t>::invalidate_dm_ptr);
    #endif
  }

  // free on exit
  template <typename word_t>
  MMU<word_t>::~MMU() {
    if (!isUnified)
      delete iTLBs;
    else
      assert(iTLBs==dTLBs);
    delete dTLBs;
  }

  template <typename word_t>
  void MMU<word_t>::reset() {
    hmemory.reset();
    assert(dTLBs);
    dTLBs->invalidate_all_entries();
    if(!isUnified)
      iTLBs->invalidate_all_entries();
  }

  // memory related operation

  // Get DMI using TLM 2.0.1
  template <typename word_t>
  void MMU<word_t>::get_dmi_at_address(uint64_t addr) {
    #ifdef NO_MMU
    #ifdef DEBUG_SIMSOC
    cout << "I suppose no 'get_dmi_at_address' function" << endl;
    #endif
    #else             
    pl.set_command(tlm::TLM_WRITE_COMMAND);
    pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    pl.set_address(addr);
    pl.set_data_ptr(NULL);
    pl.set_data_length(0);
    DirectInstrCacheExtension ext = DirectInstrCacheExtension(proc);
    pl.set_extension(&ext);
    tlm::tlm_dmi dmi_data;
    dmi_data.init();
    bool status = rw_socket->get_direct_mem_ptr(pl,dmi_data);
    if (!status) {
      info() <<"cannot get DMI access at address " <<hex <<addr <<'\n';
      pl.clear_extension(&ext);
      return;
    }
    if (!dmi_data.is_read_write_allowed()) {
      error() <<"wrong permission for DMI at address " <<hex <<addr <<'\n';
      exit(1);
    }
    if (!ext.table) {
      warning() <<"no instruction cache for DMI at address " <<hex <<addr <<'\n';
    }
    pl.clear_extension(&ext);
    const uint64_t start_addr = dmi_data.get_start_address();
    const uint64_t size = dmi_data.get_end_address()+1-start_addr;
    hmemory.add_dmi(dmi_data.get_dmi_ptr(),size,start_addr,ext.table);
    info() <<"DMI successfully obtained for address " <<hex <<addr <<".\n";
    #endif
  }

  template <typename word_t>
  unsigned int MMU<word_t>::transport_dbg(tlm::tlm_generic_payload &payload) {
    #ifdef NO_MMU
    #ifdef DEBUG_SIMSOC
    cout << "I suppose no 'transport_dbg' function" << endl;
    #endif
    return 0;
    #else         
    const word_t va_begin = payload.get_address();
    const word_t va_end = va_begin+payload.get_data_length();
    debug() <<"debug access from " <<hex <<va_begin << " to " <<va_end-1 <<".\n";
    const uint32_t page_size = TranslationPage::TR_PAGE_SIZE;
    if (va_begin/page_size!=(va_end-1)/page_size) {
      debug() <<"transport_dbg accesses many pages.\n";
      tlm::tlm_generic_payload pl;
      pl.set_command(payload.get_command());
      pl.set_data_ptr(payload.get_data_ptr());
      pl.set_streaming_width(payload.get_streaming_width());
      pl.set_byte_enable_ptr(payload.get_byte_enable_ptr());
      pl.set_byte_enable_length(payload.get_byte_enable_length());
      pl.set_dmi_allowed(false);
      uint32_t count = 0;
      word_t va = va_begin;
      while (count!=payload.get_data_length()) {
        const uint32_t size = std::min(static_cast<uint32_t>(page_size-(va%page_size)),
                                       payload.get_data_length()-count);
        pl.set_address(va);
        pl.set_data_length(size);
        pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
        const uint32_t n = this->transport_dbg(pl);
        count += n;
        if (size!=n || !pl.is_response_ok()) {
          info() <<"a partial transport_dbg access failed.\n";
          payload.set_response_status(pl.get_response_status());
          return count;
        } else {
          va += n;
          pl.set_data_ptr(pl.get_data_ptr()+n);
        }
      }
      return count;
    } else { // access inside one page
      // check command
      mem_op_type op;
      switch (payload.get_command()) {
      case tlm::TLM_READ_COMMAND: op = MMU_READ; break;
      case tlm::TLM_WRITE_COMMAND: op = MMU_WRITE; break;
      default:
        info() <<"transport_dbg command is neither READ nor WRITE.\n";
        payload.set_response_status(tlm::TLM_COMMAND_ERROR_RESPONSE);
        return 0;
      }
      // do the address translation
      word_t pa = va_begin;
      if (data_preprocess_and_is_enabled(pa)) {
        try {
          mmu_data_type dt;
          switch (payload.get_streaming_width()) {
          case 1: dt = MMU_BYTE_TYPE; break;
          case 2: dt = MMU_HALF_TYPE; break;
          case 4: dt = MMU_WORD_TYPE; break;
          default: dt = MMU_DATA_TYPE; break;
          }
          pa = virt_to_phy(pa,dt,op,dTLBs);
        } catch (MMU_Faults<word_t>& faults) {
          info() <<"transport_dbg rejected by MMU.\n";
          payload.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
          return 0;
        }
      } else {
        // check alignment
        const unsigned int sw = payload.get_streaming_width();
        if (pa%sw!=0 || payload.get_data_length()%sw!=0) {
          info() <<"wrong alignment; check streaming_width.\n";
          payload.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
          return 0;
        }
      }
      if (pa!=va_begin) {
        payload.set_address(pa);
        info() <<"address translation: " <<hex <<va_begin <<" -> " <<pa <<'\n';
      }
      // do the access
      const unsigned int sw = payload.get_streaming_width();
      if (is_bigendian() && sw!=sizeof(word_t)) {
        // big endian: we proceed step by step
        unsigned int size = payload.get_data_length();
        unsigned char *data = payload.get_data_ptr();
        tlm::tlm_generic_payload *pl = NULL;
        for (unsigned int i = 0; i<size; i+=sw) {
          const word_t addr = addr_swizzling(pa+i,sw);
          if (hmemory.dmi_address(addr)) {
            // debug() <<"using DMI.\n";
            if (op==MMU_READ)
              memcpy(&data[i],hmemory.raw(addr),sw);
            else
              memcpy(hmemory.raw(addr),&data[i],sw);
          } else {
            // debug() <<"using transaction.\n";
            if (!pl) {
              // initialize pl if necessary
              pl = new tlm::tlm_generic_payload();
              pl->set_streaming_width(sw);
              pl->set_command(op==MMU_READ? tlm::TLM_READ_COMMAND:
                              tlm::TLM_WRITE_COMMAND);
            }
            set_payload(*pl,addr,&data[i],sw);
            const unsigned int n = rw_socket->transport_dbg(*pl);
            if (n!=sw || !pl->is_response_ok()) {
              payload.set_response_status(pl->get_response_status());
              delete pl;
              return i;
            }
          }
        }
        delete pl;
        payload.set_response_status(tlm::TLM_OK_RESPONSE);
        return size;
      } else {
        // no endianness conversion is required
        // debug() <<"using burst transaction.\n";
        return rw_socket->transport_dbg(payload);
      }
    }
    #endif
  }

  template <typename word_t>
  void MMU<word_t>::invalidate_dm_ptr(sc_dt::uint64 start_range,
                                      sc_dt::uint64 end_range) {
    #ifdef NO_MMU
    #ifdef DEBUG_SIMSOC
    cout << "I suppose no 'invalidate_dm_ptr' function" << endl;
    #endif
    #else     
    TODO("invalidate direct memory interface");
    #endif
  }
  
  /*
   * default mmu implementation
   */
  template <typename word_t>
  uint8_t MMU<word_t>::read_byte(word_t va)
  {
    #ifdef NO_MMU
    #ifdef DEBUG_SIMSOC
    cout << "read_byte NEW" << endl;
    #endif
    PINOUT pinout_var;
    
    pinout_var.address = (UINT32_t)va;
    pinout_var.data = 0x0;
    pinout_var.id=this->ID;
    pinout_var.rw = 0;
    pinout_var.fiq = 0; //unused
    pinout_var.irq = 0; //unused
    pinout_var.benable = 1; 
    pinout_var.bw = 1;
    pinout_var.burst = 1;
    
    wr_arm11.fifo_read_by_masterD.write(pinout_var);
    wr_arm11.fifo_written_by_masterD.read(pinout_var);    
    
    return (uint8_t)pinout_var.data;
    #else     
    if (!data_preprocess_and_is_enabled(va)) {
      const uint8_t data= memory_read_byte(va);
      debug()<<hex<<"read byte at ["<<va<<"] return " <<(size_t)data <<endl;
      return data;
    } else {
      try {
        const word_t pa=virt_to_phy(va,MMU_BYTE_TYPE,MMU_READ,dTLBs);
        const uint8_t data=memory_read_byte(pa);
        debug()<<hex<<"read byte at ["<<va<<"]->["<<pa<<"] return "<<(size_t)data <<endl;
        return data;
      } catch(MMU_Faults<word_t>& faults) {
        handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_READ);
        return 0;
      }
    }
    #endif
  }

  template <typename word_t>
  void MMU<word_t>::write_byte(word_t va,uint8_t data){
    #ifdef NO_MMU
    #ifdef DEBUG_SIMSOC
    cout << "write_byte NEW" << endl;
    #endif
    
    PINOUT pinout_var;    
    
    pinout_var.address = (UINT32_t)va;
    pinout_var.data = (UINT32_t)data;
    pinout_var.id=this->ID;
    pinout_var.rw = 1;
    pinout_var.fiq = 0; //unused
    pinout_var.irq = 0; //unused
    pinout_var.benable = 1; 
    pinout_var.bw = 1;
    pinout_var.burst = 1;
    
    wr_arm11.fifo_read_by_masterD.write(pinout_var);   
      
    wr_arm11.fifo_written_by_masterD.read(pinout_var);    
    #else     
    if (!data_preprocess_and_is_enabled(va)) {
      debug()<<hex<<"write byte "<<(size_t)data<<" at ["<<va<<"]"<<endl;
      memory_write_byte(va,data);
    } else {
      try {
        const word_t pa=virt_to_phy(va,MMU_BYTE_TYPE,MMU_WRITE,dTLBs);
        debug()<<hex<<"write byte "<<(size_t)data<<" at ["<<va<<"]->["<<pa<<"]"<<endl;
        memory_write_byte(pa,data);
      } catch(MMU_Faults<word_t>& faults) {
        handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_WRITE);
      }
    }
    #endif
  }

  template <typename word_t>
  uint16_t MMU<word_t>::read_half(word_t va){
    #ifdef NO_MMU
    #ifdef DEBUG_SIMSOC
    cout << "read_half NEW" << endl;
    #endif
    PINOUT pinout_var;
    
    pinout_var.address = (UINT32_t)va;
    pinout_var.data = 0x0;
    pinout_var.id=this->ID;
    pinout_var.rw = 0;
    pinout_var.fiq = 0;//unused
    pinout_var.irq = 0; //unused
    pinout_var.benable = 1; 
    pinout_var.bw = 2;
    pinout_var.burst = 1;
    
    wr_arm11.fifo_read_by_masterD.write(pinout_var);
    wr_arm11.fifo_written_by_masterD.read(pinout_var);    
    
    return (uint16_t)pinout_var.data;
    #else     
    if (!data_preprocess_and_is_enabled(va)) {
      const uint16_t data=memory_read_half(va);
      debug()<<hex<<"read half at ["<<va<<"] return "<<data<<endl;
      return data;
    } else {
      try{
        const word_t pa=virt_to_phy(va,MMU_HALF_TYPE,MMU_READ,dTLBs);
        const uint16_t data=memory_read_half(pa);
        debug()<<hex<<"read half at ["<<va<<"]->["<<pa<<"] return "<<data<<endl;
        return data;
      } catch(MMU_Faults<word_t>& faults) {
        handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_READ);
        return 0;
      }
    }
    #endif
  }

  template <typename word_t>
  void MMU<word_t>::write_half(word_t va,uint16_t data){
    #ifdef NO_MMU
    #ifdef DEBUG_SIMSOC
    cout << "write_half NEW" << endl;
    #endif
    
    PINOUT pinout_var;    
    
    pinout_var.address = (UINT32_t)va;
    pinout_var.data = (UINT32_t)data;
    pinout_var.id=this->ID;
    pinout_var.rw = 1;
    pinout_var.fiq = 0;//unused
    pinout_var.irq = 0; //unused
    pinout_var.benable = 1; 
    pinout_var.bw = 2;
    pinout_var.burst = 1;
    
//    cout << "MEMORY REQUEST\t" << "wh\t" << dec << (int)ID << "\t";
//    cout << hex << va << "\t" << data << "\t";
//    cout << dec << sc_time_stamp() << endl;
    
    wr_arm11.fifo_read_by_masterD.write(pinout_var);   
      
    wr_arm11.fifo_written_by_masterD.read(pinout_var);    
    
//     cout << "MEMORY RESPONSE\t" << "wh\t" << dec << (int)ID << "\t";
//     cout << hex << va << "\t" << data << "\t";
//     cout << dec << sc_time_stamp() << endl;
    
    #else     
    if (!data_preprocess_and_is_enabled(va)) {
      debug()<<hex<<"write half "<<data<<" at ["<<va<<"]"<<endl;
      memory_write_half(va,data);
    } else {
      try {
        const word_t pa=virt_to_phy(va,MMU_HALF_TYPE,MMU_WRITE,dTLBs);
        debug()<<hex<<"write half "<<data<<" at ["<<va<<"]->["<<pa<<"]"<<endl;
        memory_write_half(pa,data);
      } catch(MMU_Faults<word_t>& faults) {
        handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_WRITE);
      }
    }
    #endif
  }

  template <typename word_t>
  uint32_t MMU<word_t>::read_word(word_t va){
    #ifdef NO_MMU
    cout << "I suppose no VA (read_word)" << endl;
    return 0;
    #else     
    if (!data_preprocess_and_is_enabled(va)) {
      const uint32_t data=memory_read_word(va);
      debug() <<hex<<"read word at ["<<va<<"] return "<<data <<endl;
      return data;
    } else {
      try{
        const word_t pa = virt_to_phy(va,MMU_WORD_TYPE,MMU_READ,dTLBs);
        const uint32_t data=memory_read_word(pa);
        debug() <<hex<<"read word at ["<<va<<"]->["<<pa<<"] return "<<data<<endl;
        return data;
      } catch(MMU_Faults<word_t>& faults) {
        handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_READ);
        return 0;
      }
    }
    #endif
  }

  template <typename word_t>
  void MMU<word_t>::write_word(word_t va,uint32_t data){
    #ifdef NO_MMU
    cout << "I suppose no VA (write_word)" << endl;
    #else 
    if (!data_preprocess_and_is_enabled(va)) {
      debug() <<hex<<"write word "<<data<<" at ["<<va<<"]"<<endl;
      memory_write_word(va,data);
    } else {
      try {
        const word_t pa = virt_to_phy(va,MMU_WORD_TYPE,MMU_WRITE,dTLBs);
        debug() <<hex<<"write word "<<data<<" at ["<<va<<"]->["<<pa<<"]"<<endl;
        memory_write_word(pa,data);
      } catch(MMU_Faults<word_t>& faults) {
        handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_WRITE);
      }
    }
    #endif
  }

  template <typename word_t>
  uint64_t MMU<word_t>::read_double(word_t va){
    #ifdef NO_MMU
    cout << "I suppose no VA (read_double)" << endl;
    return 0;
    #else    
    if(!data_preprocess_and_is_enabled(va)) {
      const uint64_t data=memory_read_double(va);
      debug() <<hex<<"read double at ["<<va<<"] return "<<data <<endl;
      return data;
    } else {
      try{
        const word_t pa = virt_to_phy(va,MMU_WORD_TYPE,MMU_READ,dTLBs);
        const uint64_t data=memory_read_double(pa);
        debug() <<hex<<"read double at ["<<va<<"]->["<<pa<<"] return "<<data<<endl;
        return data;
      } catch(MMU_Faults<word_t>& faults) {
        handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_READ);
        return 0;
      }
    }
    #endif
  }

  template <typename word_t>
  void MMU<word_t>::write_double(word_t va,uint64_t data){
    #ifdef NO_MMU
    cout << "I suppose no VA (write_double)" << endl;
    #else
    if (!data_preprocess_and_is_enabled(va)) {
      debug() <<hex<<"write double "<<data<<" at ["<<va<<"]"<<endl;
      memory_write_double(va,data);
    } else {
      try{
        const word_t pa = virt_to_phy(va,MMU_WORD_TYPE,MMU_WRITE,dTLBs);
        debug() <<hex<<"write double "<<data<<" at ["<<va<<"]->["<<pa<<"]"<<endl;
        memory_write_double(pa,data);
      } catch(MMU_Faults<word_t>& faults) {
        handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_WRITE);
      }
    }
    #endif
  }

  template <typename word_t>
  uint32_t MMU<word_t>::load_instr_32(word_t va) {
    #ifdef NO_MMU

    #ifdef DEBUG_SIMSOC
    cout << "load 32-bit instruction at [0x" << hex << va <<"] @" << sc_time_stamp()  <<endl;
    #endif

    PINOUT pinout_var;
    
    pinout_var.address = (UINT32_t)va;
    pinout_var.data = 0x0;
    pinout_var.id=this->ID;
    pinout_var.rw = 0;
    pinout_var.fiq = 0;
    pinout_var.irq = 0;
    pinout_var.benable = 1;
    pinout_var.bw = 0;
    pinout_var.burst = 1;  
    
    #ifdef DEBUG_SIMSOC
    cout << "instruction read: " << hex << pinout_var.data << endl;    
    #endif
    
    sc_time time_1(1,SC_NS);
    sc_time time_2(1,SC_NS);
    sc_time time_3(1,SC_NS);
    
    time_1 = sc_time_stamp();
    
    wr_arm11.fifo_read_by_masterI.write(pinout_var);
        
    wr_arm11.fifo_written_by_masterI.read(pinout_var);    
    
    time_2 = sc_time_stamp();
    
    time_3 = time_2 - time_1;
    
    #ifdef TRACE_SIMSOC
    cout << "INSTR\t32\tPROC" << dec << (int)ID << "\tADDR" << hex << pinout_var.address;
    cout << "\tDATA" << pinout_var.data << "\t" << dec << time_3.to_string() << endl;        
    #endif
    
    #ifdef DEBUG_SIMSOC
    cout << "instruction read: " << hex << pinout_var.data << endl;
    #endif

    return (uint32_t)pinout_var.data;

    #else
    if (!code_preprocess_and_is_enabled(va)) {
      debug() <<hex <<"load instruction at [" <<va <<"]" <<endl;
      return memory_read_word(va);
    } else {
      try {
        const word_t pa = virt_to_phy(va, MMU_WORD_TYPE, MMU_READ, iTLBs);//when unified,iTLBs == dTLBs
        debug() <<hex <<"load instruction at [" <<va <<"]->[" <<pa <<"]" <<endl;
        return  memory_read_word(pa);
      } catch(MMU_Faults<word_t>& faults) {
        handle_instruction_faults(faults.virt_addr,faults.fault,faults.domain);
        return 0;
      }
    }
    #endif
  } 
  
  template <typename word_t>
  uint32_t MMU<word_t>::read_from_fifoI(){

    PINOUT pinout_var;
    pinout_var.data = 0x0;
    wr_arm11.fifo_written_by_masterI.read(pinout_var);

    sc_time time_2 = sc_time_stamp();
    sc_time time_3 = time_2 - time_1_glob;

    #ifdef TRACE_SIMSOC
    cout << "INSTR\t32\tPROC" << dec << (int)ID << "\tADDR" << hex << pinout_var.address;
    cout << "\tDATA" << pinout_var.data << "\t" << dec << time_3.to_string() << endl;  
    #endif

    return pinout_var.data;
  }

 template <typename word_t>
  void MMU<word_t>::write_to_fifoI(word_t va){
    PINOUT pinout_var;
    
//     cout << "Process I - Instruction address: " << hex << (UINT32_t)va << endl;
    pinout_var.address = (UINT32_t)va;
    pinout_var.data = 0x0;
    pinout_var.id=this->ID;
    pinout_var.rw = 0;
    pinout_var.fiq = 0; //unused
    pinout_var.irq = 0; //unused
    pinout_var.benable = 1;
    pinout_var.bw = 0;
    pinout_var.burst = 1;  
    time_1_glob = sc_time_stamp();
    
    wr_arm11.fifo_read_by_masterI.write(pinout_var);
  }


  template <typename word_t>
  uint16_t MMU<word_t>::load_instr_16(word_t va){
    #ifdef NO_MMU
    #ifdef DEBUG_SIMSOC
    cout << "load 16-bit instruction at [0x" << hex << va <<"] @" << sc_time_stamp()  <<endl;
    #endif
    PINOUT pinout_var;
    
    pinout_var.address = (UINT32_t)va;
    pinout_var.data = 0x0;
    pinout_var.id=this->ID;
    pinout_var.rw = 0;
    pinout_var.fiq = 0; //unused
    pinout_var.irq = 0; //unused
    pinout_var.benable = 1;
    pinout_var.bw = 2;
    pinout_var.burst = 1;
    
    wr_arm11.fifo_read_by_masterI.write(pinout_var);
    
    wr_arm11.fifo_written_by_masterI.read(pinout_var);    
    
    return (uint32_t)pinout_var.data;
        
    #else
    if (!code_preprocess_and_is_enabled(va)) {
      debug()<<hex<<"load instruction at ["<<va<<"]"<<endl;
      return memory_read_half(va);
    } else {
      try{
        word_t pa=virt_to_phy(va,MMU_HALF_TYPE,MMU_READ,iTLBs);
        debug()<<hex<<"load instruction at ["<<va<<"]->["<<pa<<"]"<<endl;
        return memory_read_half(pa);
      } catch(MMU_Faults<word_t>& faults) {
        handle_instruction_faults(faults.virt_addr,faults.fault,faults.domain);
        return 0;
      }
    }
    #endif
  };

  
  /*
   * Memory access of data size equal or larger than buswidth for 64bit architecture
   */
  template<>
  uint64_t MMU<uint64_t>::memory_read_double(uint64_t addr) {
    #ifdef NO_MMU
    #ifdef DEBUG_SIMSOC
    cout << "I suppose no 64-bit width bus (memory_read_double)" << endl;
    #endif
    return 0;
    #else
    
    if (hmemory.dmi_address(addr)) {
      return *hmemory.raw64(addr);
    } else {
      uint64_t data=0;
      sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
      set_payload(pl,addr,(unsigned char*)(&data),8);
      pl.set_command(tlm::TLM_READ_COMMAND);
      rw_socket->b_transport(pl,delay);
      if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
      	TODO("should raise an exception (memory abort)");
      return data;
    }
    #endif
  }

  template<>
  void MMU<uint64_t>::memory_write_double(uint64_t addr, uint64_t data){
    #ifdef NO_MMU
    #ifdef DEBUG_SIMSOC
    cout << "I suppose no 64-bit width bus (memory_write_double)" << endl;
    #endif
    #else
    if (hmemory.dmi_address(addr)) {
      *hmemory.raw64(addr)=data;
    } else {
      sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
      set_payload(pl,addr,(unsigned char*)(&data),8);
      pl.set_command(tlm::TLM_WRITE_COMMAND);
      rw_socket->b_transport(pl,delay);
      if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
      	TODO("should raise an exception (memory abort)");
    }
    #endif
  }
  

  /*
   * Memory access of data size equal or larger than buswidth for 32bit architecture
   */
  template<>
  uint64_t MMU<uint32_t>::memory_read_double(uint32_t addr) {
    #ifdef NO_MMU
    #ifdef DEBUG_SIMSOC
    cout << "read double at [0x" << hex << addr << "]";
    #endif
    uint64_t data = 0;
    
    PINOUT pinout_var;
    
    pinout_var.address = (UINT32_t)addr;
    pinout_var.data = 0x0;
    pinout_var.id=this->ID;
    pinout_var.rw = 0;
    pinout_var.fiq = 0; //unused
    pinout_var.irq = 0; //unused
    pinout_var.benable = 1;
    pinout_var.bw = 0;
    pinout_var.burst = 2;

    
    for (int burst_counter=0; burst_counter<2; burst_counter++) {
      wr_arm11.fifo_read_by_masterD.write(pinout_var);    
      wr_arm11.fifo_written_by_masterD.read(pinout_var);    
      
      data |= ((uint64_t)pinout_var.data << burst_counter*32);
    }
    #ifdef DEBUG_SIMSOC
    cout << " return 0x" << hex << data << " @" << sc_time_stamp() << endl;
    #endif
    return data;
    
    #else    
    if (!is_bigendian()){
      if (hmemory.dmi_address(addr)) {
        return *hmemory.raw64(addr);
      } else {
        uint64_t data=0;
        sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
        set_payload(pl,addr,(unsigned char*)(&data),8);
        pl.set_command(tlm::TLM_READ_COMMAND);
        rw_socket->b_transport(pl,delay);
        if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
          TODO("should raise an exception (memory abort)");
        return data;
      }
    }else{
      if (hmemory.dmi_address(addr)) {
        uint64_t data = (uint64_t)(*hmemory.raw32(addr)) << 32;
        assert(hmemory.dmi_address(addr+4));
        data  |= (uint64_t)(*hmemory.raw32(addr + 4));
        return data;
      } else {
        uint64_t host_dword = 0;
        sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
        set_payload(pl,addr,(unsigned char*)(&host_dword),8);
        pl.set_command(tlm::TLM_READ_COMMAND);
        rw_socket->b_transport(pl,delay);
        if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
          TODO("should raise an exception (memory abort)");
        return swap_words<uint32_t>(host_dword);
      }
    }
    #endif
  }

  template<>
  void MMU<uint32_t>::memory_write_double(uint32_t addr, uint64_t data){
    #ifdef NO_MMU
    #ifdef DEBUG_SIMSOC
    cout << " write double at address [0x" <<  hex << addr <<"] value 0x" << hex << data << " @" << sc_time_stamp()  << endl;
    #endif
    
    PINOUT pinout_var;    
    
    pinout_var.address = (UINT32_t)addr;
    pinout_var.data = 0x0;
    pinout_var.id=this->ID;
    pinout_var.rw = 1;
    pinout_var.fiq = 0; //unused
    pinout_var.irq = 0; //unused
    pinout_var.benable = 1; 
    pinout_var.bw = 0;
    pinout_var.burst = 2;

    for (int burst_counter=0; burst_counter<2; burst_counter++) {
      pinout_var.data = (UINT32_t)(data >> burst_counter*32);
      wr_arm11.fifo_read_by_masterD.write(pinout_var);   
      
      wr_arm11.fifo_written_by_masterD.read(pinout_var);    
    }
    
    #else     
    if (!is_bigendian()) {
      if (hmemory.dmi_address(addr)) {
        *hmemory.raw64(addr)=data;
      } else {
        sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
        set_payload(pl,addr,(unsigned char*)(&data),8);
        pl.set_command(tlm::TLM_WRITE_COMMAND);
        rw_socket->b_transport(pl,delay);
        if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
          TODO("should raise an exception (memory abort)");
      }
    } else {
      if (hmemory.dmi_address(addr)) {
        *hmemory.raw32(addr) = (uint32_t)(data>>32);
        assert(hmemory.dmi_address(addr+4));
        *hmemory.raw32(addr+4) = (uint32_t)data;
      } else {
        uint64_t host_dword = swap_words<uint32_t>(data);
        sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
        set_payload(pl,addr,(unsigned char*)(&host_dword),8);
        pl.set_command(tlm::TLM_WRITE_COMMAND);
        rw_socket->b_transport(pl,delay);
        if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
          TODO("should raise an exception (memory abort)");
      }
    }
    #endif
  }

  template <typename word_t>
  uint32_t MMU<word_t>::memory_read_word__transaction(word_t addr) {
    #ifdef NO_MMU
    #ifdef DEBUG_SIMSOC
    cout << " read word transaction at [0x" << hex << addr << "]";
    #endif
    PINOUT pinout_var;
    
    pinout_var.address = (UINT32_t)addr;
    pinout_var.data = 0x0;
    pinout_var.id=this->ID;
    pinout_var.rw = 0;
    pinout_var.fiq = 0; //unused
    pinout_var.irq = 0; //unused
    pinout_var.benable = 1;
    pinout_var.bw = 0;
    pinout_var.burst = 1;
    	    
//    cout << "MEMORY REQUEST\t" << "rw\tPROC" << dec << (int)ID << "\t";
//    cout << hex << pinout_var.address << "\t" << pinout_var.data << "\t";
//    cout << dec << sc_time_stamp() << endl;


    sc_time time_1(1,SC_NS);
    sc_time time_2(1,SC_NS);
    sc_time time_3(1,SC_NS);
    
    time_1 = sc_time_stamp();
    
    wr_arm11.fifo_read_by_masterD.write(pinout_var);
      
    wr_arm11.fifo_written_by_masterD.read(pinout_var);    
    


    time_2 = sc_time_stamp();
    
    time_3 = time_2 - time_1;
    
//     cout << "MEMORY RESPONSE\t" << "ww\tPROC" << dec << (int)ID << "\t";
//     cout << hex << pinout_var.address << "\t" << pinout_var.data << "\t";
//     cout << dec << sc_time_stamp() << endl;
    
    
//     cout << "ACCESS\tWRITE\t" << (int)ID << "\t" << time_1.to_string() << "\ttime1" << endl;
//     cout << "ACCESS\tWRITE\t" << (int)ID << "\t" << time_2.to_string() << "\ttime2" << endl;
    #ifdef TRACE_SIMSOC
    cout << "ACCESS\tREAD\tPROC" << dec << (int)ID << "\tADDR" << hex << pinout_var.address;
    cout << "\tDATA" << pinout_var.data << "\t" << dec << time_3.to_string() << endl;    
    #endif

    
    #ifdef DEBUG_SIMSOC
    cout << " return 0x" << hex << pinout_var.data << " @" << sc_time_stamp() << endl;
    #endif
    return (uint32_t)pinout_var.data;
    
    #else
    uint32_t data=0;
    sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
    set_payload(pl, addr, (unsigned char*)(&data),4);
    pl.set_command(tlm::TLM_READ_COMMAND);
    rw_socket->b_transport(pl,delay);
    if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
      TODO("should raise an exception (memory abort)");
    if (pl.is_dmi_allowed())
      get_dmi_at_address(addr);
    return data;
    #endif
  }

  template <typename word_t>
  void MMU<word_t>::memory_write_word__transaction(word_t addr, uint32_t data){
    #ifdef NO_MMU
    #ifdef DEBUG_SIMSOC
    cout << "write word transaction at [0x"<< hex << addr <<"] value 0x" << hex << data; 
    #endif
    PINOUT pinout_var;
    
    pinout_var.address = (UINT32_t)addr;
    pinout_var.data = (UINT32_t)data;
    pinout_var.id=this->ID;
    pinout_var.rw = 1;
    pinout_var.fiq = 0; //unused
    pinout_var.irq = 0; //unused 
    pinout_var.benable = 1;
    pinout_var.bw = 0;
    pinout_var.burst = 1;
    
//     cout << "MEMORY REQUEST\t" << "ww\tPROC" << dec << (int)ID << "\t";
//     cout << hex << pinout_var.address << "\t" << pinout_var.data << "\t";
//     cout << dec << sc_time_stamp() << endl;


    sc_time time_1(1,SC_NS);
    sc_time time_2(1,SC_NS);
    sc_time time_3(1,SC_NS);
    
    time_1 = sc_time_stamp();
    
    wr_arm11.fifo_read_by_masterD.write(pinout_var);   
      
    wr_arm11.fifo_written_by_masterD.read(pinout_var);    
    
    time_2 = sc_time_stamp();
    
    time_3 = time_2 - time_1;
    
//     cout << "MEMORY RESPONSE\t" << "ww\tPROC" << dec << (int)ID << "\t";
//     cout << hex << pinout_var.address << "\t" << pinout_var.data << "\t";
//     cout << dec << sc_time_stamp() << endl;
    
    
//     cout << "ACCESS\tWRITE\t" << (int)ID << "\t" << time_1.to_string() << "\ttime1" << endl;
//     cout << "ACCESS\tWRITE\t" << (int)ID << "\t" << time_2.to_string() << "\ttime2" << endl;
    #ifdef TRACE_SIMSOC
    cout << "ACCESS\tWRITE\tPROC" << dec << (int)ID << "\tADDR" << hex << pinout_var.address;
    cout << "\tDATA" << pinout_var.data << "\t" << dec << time_3.to_string() << endl;    
    #endif

    
    #ifdef DEBUG_SIMSOC
    cout << " @" << sc_time_stamp() << endl;
    #endif
    #else        
    sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
    set_payload(pl,addr,(unsigned char*)(&data),4);
    pl.set_command(tlm::TLM_WRITE_COMMAND);
    rw_socket->b_transport(pl,delay);
    if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
      TODO("should raise an exception (memory abort)");
    if (pl.is_dmi_allowed())
      get_dmi_at_address(addr);
    #endif
  }

  //access data size smaller than buswidth
  template <typename word_t>
  uint16_t MMU<word_t>::memory_read_half(word_t addr){
    #ifdef NO_MMU    
    #ifdef DEBUG_SIMSOC
    cout << "read half at [0x" << hex << addr << "]"; 
    #endif
    
    PINOUT pinout_var;
    
    pinout_var.address = (UINT32_t)addr;
    pinout_var.data = 0x0;
    pinout_var.id=this->ID;
    pinout_var.rw = 0;
    pinout_var.fiq = 0; //unused
    pinout_var.irq = 0; //unused
    pinout_var.benable = 1; 
    pinout_var.bw = 2;
    pinout_var.burst = 1;
    
    wr_arm11.fifo_read_by_masterD.write(pinout_var);
    
    wr_arm11.fifo_written_by_masterD.read(pinout_var);    
    
    #ifdef DEBUG_SIMSOC
    cout << "return 0x" << hex << pinout_var.data << " @" << sc_time_stamp() << endl;
    #endif
    return (uint32_t)pinout_var.data;
    
    #else    
    if (is_bigendian())
      addr = addr_swizzling(addr,2);
    if (hmemory.dmi_address(addr)) {
      return *hmemory.raw16(addr);
    } else {
      uint16_t data = 0;
      sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
      set_payload(pl,addr,(unsigned char*)(&data),2);
      pl.set_command(tlm::TLM_READ_COMMAND);
        rw_socket->b_transport(pl,delay);
        if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
          TODO("should raise an exception (memory abort)");
        return data;
    }
    #endif
  }

  template <typename word_t>
  void MMU<word_t>::memory_write_byte(word_t addr, uint8_t data){
    #ifdef NO_MMU
    #ifdef DEBUG_SIMSOC
    cout << "write byte at [0x"<< hex << addr <<"] value 0x" << hex << data << " @" << sc_time_stamp()  << endl;
    #endif
    PINOUT pinout_var;
    
    pinout_var.address = (UINT32_t)addr;
    pinout_var.data = (UINT32_t)data;
    pinout_var.id=this->ID;
    pinout_var.rw = 1;
    pinout_var.fiq = 0; //unused
    pinout_var.irq = 0; //unused
    pinout_var.benable = 1;
    pinout_var.bw = 1;
    pinout_var.burst = 1;
    
    wr_arm11.fifo_read_by_masterD.write(pinout_var);
    
    wr_arm11.fifo_written_by_masterD.read(pinout_var);    
    
    #else        
  
    if (is_bigendian())
      addr = addr_swizzling(addr,1);
    if (hmemory.dmi_address(addr)) {
      hmemory[addr]=data;
    } else {
      sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
      set_payload(pl,addr,(unsigned char*)(&data),1);
      pl.set_command(tlm::TLM_WRITE_COMMAND);
      rw_socket->b_transport(pl,delay);
      if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
	TODO("should raise an exception (memory abort)");
    }
    #endif
  }

  template <typename word_t>
  uint8_t MMU<word_t>::memory_read_byte(word_t addr) {
    #ifdef NO_MMU
    #ifdef DEBUG_SIMSOC
    cout << "read byte at [0x"<< hex << addr <<"]"; 
    #endif
    PINOUT pinout_var;
    
    pinout_var.address = (UINT32_t)addr;
    pinout_var.data = 0x0;
    pinout_var.id=this->ID;
    pinout_var.rw = 0;
    pinout_var.fiq = 0; //unused
    pinout_var.irq = 0; //unused
    pinout_var.benable = 1;
    pinout_var.bw = 1;
    pinout_var.burst = 1;
    
    wr_arm11.fifo_read_by_masterD.write(pinout_var);
    
    wr_arm11.fifo_written_by_masterD.read(pinout_var);    
    #ifdef DEBUG_SIMSOC
    cout << " return 0x" << hex << pinout_var.data << " @" << sc_time_stamp() << endl;
    #endif
    return (uint32_t)pinout_var.data;
    
    #else    
  
    if (is_bigendian())
      addr = addr_swizzling(addr,1);
    if (hmemory.dmi_address(addr)) {
      return hmemory[addr];
    } else {
      uint8_t data=0;
      sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
      set_payload(pl,addr,(unsigned char*)(&data),1);
      pl.set_command(tlm::TLM_READ_COMMAND);
      rw_socket->b_transport(pl,delay);
      if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
	TODO("should raise an exception (memory abort)");
      return data;
    }
    #endif
  }

  template <typename word_t>
  void MMU<word_t>::memory_write_half(word_t addr, uint16_t data){
    #ifdef NO_MMU
    #ifdef DEBUG_SIMSOC
    cout << "write half at [0x" << hex << addr <<"] value 0x" << hex << data << " @" << sc_time_stamp() << endl;
    #endif
    PINOUT pinout_var;
    
    pinout_var.address = (UINT32_t)addr;
    pinout_var.data = (UINT32_t)data;
    pinout_var.id=this->ID;
    pinout_var.rw = 1;
    pinout_var.fiq = 0;//unused
    pinout_var.irq = 0;//unused
    pinout_var.benable = 1;
    pinout_var.bw = 2;
    pinout_var.burst = 1;
    
    wr_arm11.fifo_read_by_masterD.write(pinout_var);    
    
    wr_arm11.fifo_written_by_masterD.read(pinout_var);    
    
    #else        
  
    if (is_bigendian())
      addr = addr_swizzling(addr,2);
    if (hmemory.dmi_address(addr)) {
      *hmemory.raw16(addr)=data;
    } else {
      sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
      set_payload(pl,addr,(unsigned char*)(&data),2);
      pl.set_command(tlm::TLM_WRITE_COMMAND);
      rw_socket->b_transport(pl,delay);
      if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
	TODO("should raise an exception (memory abort)");
    }
    #endif
  }

#ifdef NO_MMU
void wrapper_arm11::working_processI()
{
  PINOUT pinout_varI;
  int burstI = 0, i, wait_cycles = 0;
  
  pinout_varI.id = (int)ID;
  
  while (true) {
    fifo_read_by_masterI.read(pinout_varI);

    if(sync_idle) {
      wait(sync_int.negedge_event());
    }
    if(dma_idle) {
      wait(dma_event.negedge_event());
    }
    
    pinoutI.write(pinout_varI);
    request_from_masterI.write(true); 
    wait_cycles = 0;
    cs_I = CS_ACTIVE; trace_cs_I = (int)cs_I;

    if(TRACE_ISS)
      fprintf(ftrace,"[TRACE ISS %d] INST %s addr %08X data %08X burst %d @ %.0f ns\n", ID, pinout_varI.rw ? "W" : "R", pinout_varI.address, pinout_varI.data, pinout_varI.burst, sc_simulation_time());  

    do {
      wait();
      wait_cycles++;
      cs_I = CS_STALLED; trace_cs_I = (int)cs_I;
    } while (ready_to_masterI.read()==false);

    /* in case of MISS in I$ the latency is greater
       than 1 cycle. this is the case to consider 1 active cycle lost */
    if(wait_cycles > 1)

      active_loss++;

    cs_I = CS_ACTIVE; trace_cs_I = (int)cs_I;

    pinout_varI = pinoutI.read();
    fifo_written_by_masterI.write(pinout_varI);

    request_from_masterI.write(false);
    cs_I = CS_STALLED; trace_cs_I = (int)cs_I;
  }    
}

void wrapper_arm11::dma_event_handler()
{
  while (true)
  {
    if(dma_idle)
    {
      while (dma_event.read() == false) {
        wait();
      }
      
      dma_event.write(false);
      dma_idle = false;
    }
    else
      wait();
  } 
}

bool wrapper_arm11::InDmaSleepSpace(uint32_t addr)
{
  return (addr == DMA_WAIT_EVENT_ADDR);
}

void wrapper_arm11::sync_handler()
{
  while (true)
  {
    wait(sync_int.posedge_event());
    sync_idle = true;
    cs_D = CS_IDLE;
    cs_I = CS_IDLE;
    wait(sync_int.negedge_event());
    sync_idle = false;
  } 
}

wrapper_arm11::core_st
wrapper_arm11::core_st_or
(
  const wrapper_arm11::core_st cs_d,
  const wrapper_arm11::core_st cs_i
)
{
  if(sync_idle)
    return CS_IDLE;
  else if((cs_d == CS_ACTIVE) || (cs_i == CS_ACTIVE))
    return CS_ACTIVE;
  else
    return CS_STALLED;
}

void wrapper_arm11::core_status()
{
  while (true)
  {
//     trace_cs_D = (int)cs_D;
//     trace_cs_I = (int)cs_I;


    cs = core_st_or (cs_D, cs_I) ;
    trace_cs = (int)cs;

    statobject->inspectARMv6 ((int)ID, (int)TILE_ID, (int) cs, active_loss);
    wait();
  }
}

void wrapper_arm11::working_processD()
{
  PINOUT pinout_varD;
  int burstD = 0, i;
  bool is_first_cycle;
  pinout_varD.id = (int)ID;
  
  while (true)
  {
    
      
    fifo_read_by_masterD.read(pinout_varD);
    
    if (addresser->PhysicalInSimSupportSpace(addresser->Logical2Physical(pinout_varD.address, ID))) {
      simsuppobject->catch_sim_message(pinout_varD.address - addresser->ReturnSimSupportPhysicalAddress(), &pinout_varD.data, pinout_varD.rw, ID);
      wait();
      fifo_written_by_masterD.write(pinout_varD);
    } else if (InDmaSleepSpace(pinout_varD.address) && pinout_varD.rw) {
      dma_idle = true;
      fifo_written_by_masterD.write(pinout_varD);
    }
    else
    {
      burstD = (int)pinout_varD.burst;
      pinoutD.write(pinout_varD);
      request_from_masterD.write(true);

      is_first_cycle = true;
      cs_D = CS_ACTIVE; trace_cs_D = (int)cs_D;

      if(TRACE_ISS)
        fprintf(ftrace,"[TRACE ISS %d] DATA %s addr %08X data %08X burst %d @ %.0f\n", ID, pinout_varD.rw ? "W" : "R", pinout_varD.address, pinout_varD.data, pinout_varD.burst, sc_simulation_time());  

      for (i = 0; i < burstD; i++)
      {	

        do {
          wait();
          if(is_first_cycle)
          {
            cs_D = CS_ACTIVE;
            trace_cs_D = (int)cs_D;
            is_first_cycle = false;
          } else {
            cs_D = CS_STALLED;
            trace_cs_D = (int)cs_D;
          }
        } while (ready_to_masterD.read()==false);

        active_loss++ ;

        pinout_varD = pinoutD.read();
        fifo_written_by_masterD.write(pinout_varD);

      }

      request_from_masterD.write(false); 

      cs_D = CS_STALLED;
      trace_cs_D = (int)cs_D;
    }

  } 
}
#endif

} // namespace simsoc
