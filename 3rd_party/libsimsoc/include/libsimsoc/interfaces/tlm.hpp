//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef TLM_HPP
#define TLM_HPP

#include <systemc>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <inttypes.h>

namespace simsoc {

  class PayLoad : public tlm::tlm_generic_payload {

  public:
    bool deprecated;

    PayLoad() { deprecated = false ;} // by default the new protocol
    PayLoad(bool comp) { deprecated = comp;}

    // set_address already exists on generic payload

    void set_data8(uint8_t *data) {
      set_data_ptr((unsigned char *)data);set_data_length(1);
    }
    void set_data16(uint16_t *data) {
      set_data_ptr((unsigned char *)data);set_data_length(2);
    }
    void set_data32(uint32_t *data) {
      set_data_ptr((unsigned char *)data);set_data_length(4);
    }
    void set_data64(uint64_t *data) {
      set_data_ptr((unsigned char *)data); set_data_length(8);
    }

    void set_read_transaction() { set_command(tlm::TLM_READ_COMMAND); }
    void set_write_transaction() { set_command(tlm::TLM_WRITE_COMMAND); }

    void set_payload(const uint64_t addr, unsigned char * data,
                     const unsigned int length) {
      set_address(addr); set_data_ptr(data); set_data_length(length);
    }

    void get_payload(uint64_t *addr, unsigned char ** data,
                     const unsigned int *length) {
      *addr = get_address();
      *data = get_data_ptr();
    }
  };

  class RW_Target
  {
  public:
    virtual ~RW_Target() {}

    virtual void trans_read_data(PayLoad &pl) = 0;

    virtual void trans_write_data(PayLoad &pl) = 0;

    virtual bool in_addr_arrange(uint32_t address) {return true;};

  };

  // Define initiator to call the TLM2 blocking transport interface

  class RW_InitiatorPort: public tlm_utils::simple_initiator_socket<RW_InitiatorPort>,
                            public RW_Target
  {
  public:
    RW_InitiatorPort():
      tlm_utils::simple_initiator_socket<RW_InitiatorPort>("initiator_socket")
    {}

    RW_InitiatorPort(const RW_InitiatorPort&):
      tlm_utils::simple_initiator_socket<RW_InitiatorPort>("initiator_socket")
    {}

    RW_Target* operator -> () {
      return (RW_Target*) this;
    }

    const RW_Target* operator -> () const {
      return (RW_Target*) this;
    }

    void trans_read_data(PayLoad &pl) {
      sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
      pl.set_command(tlm::TLM_READ_COMMAND);
      (*static_cast<tlm_utils::simple_initiator_socket<RW_InitiatorPort>*>(this))
        ->b_transport(pl, delay);
    }

    void trans_write_data(PayLoad &pl) {
      sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
      pl.set_command(tlm::TLM_WRITE_COMMAND);
      (*static_cast<tlm_utils::simple_initiator_socket<RW_InitiatorPort>*>(this))
        ->b_transport(pl, delay);
    }

    // Required and unused virtual methods required for hierarchical connectivity
    void invalidate_direct_mem_ptr(sc_dt::uint64 start_range, sc_dt::uint64 end_range) {}

    tlm::tlm_sync_enum nb_transport_bw(PayLoad &payload,
                                       tlm::tlm_phase &phase,
                                       sc_core::sc_time &delta){
      assert(false);return tlm::TLM_ACCEPTED;}
  };

  class RW_TargetPort: public tlm::tlm_fw_transport_if<> {
  public:
    static int n;
    std::vector<tlm::tlm_target_socket<>*> sockets;

    RW_TargetPort():
      sockets(),
      target(NULL)
    {}

    ~RW_TargetPort() {
      for (std::vector<tlm::tlm_target_socket<>*>::iterator i = sockets.begin(),
             ei = sockets.end(); i!=ei; ++i)
        delete *i;
    }

    operator tlm::tlm_target_socket<>& () {
      std::ostringstream oss;
      oss <<"target_socket_" <<++n;
      tlm::tlm_target_socket<> *socket = new tlm::tlm_target_socket<>(oss.str().c_str());
      sockets.push_back(socket);
      (*socket)(*this);
      return *socket;
    }

    void operator()(RW_Target &t) {
      target = &t;
    }

    void b_transport(tlm::tlm_generic_payload & trans,
                     sc_core::sc_time &delay_time) {
      PayLoad &pl = (PayLoad &) trans;
      switch (pl.get_command()) {
      case tlm::TLM_READ_COMMAND :
        target->trans_read_data(pl);
        break;
      case tlm::TLM_WRITE_COMMAND :
        target->trans_write_data(pl);
        break;
      default:
        assert(false);
      }
      pl.set_response_status(tlm::TLM_OK_RESPONSE);
    }

    bool get_direct_mem_ptr(tlm::tlm_generic_payload &, tlm::tlm_dmi&) {
      return false;
    }

    unsigned int transport_dbg(tlm::tlm_generic_payload &) {
      return 0;
    }

    tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload &,
                                       tlm::tlm_phase&, sc_core::sc_time&) {
      assert(false);
      return tlm::TLM_ACCEPTED;
    }

  private:
    RW_Target *target;
  };

} // namespace simsoc

#endif //TLM_LIAMA_HPP
