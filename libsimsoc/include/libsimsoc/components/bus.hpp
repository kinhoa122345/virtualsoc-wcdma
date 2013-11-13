//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef BUS_HPP
#define BUS_HPP

#include "libsimsoc/module.hpp"
#include "tlm.h"
#include "tlm_utils/multi_passthrough_initiator_socket.h"
#include "tlm_utils/multi_passthrough_target_socket.h"
#include "tlm_utils/instance_specific_extensions.h"
#include <vector>
#include <inttypes.h>

namespace simsoc {

  struct Bus: public Module {

    tlm_utils::multi_passthrough_target_socket<Bus, 32> target_sockets;
    tlm_utils::multi_passthrough_initiator_socket<Bus, 32> initiator_sockets;
    typedef tlm_utils::multi_passthrough_initiator_socket<Bus, 32>::base_target_socket_type base_target_socket_type;

    Bus(sc_core::sc_module_name name);
    void before_end_of_elaboration(); // prepare the memory map
    void bind_target(base_target_socket_type &port, uint32_t base, uint32_t size);

    void b_transport(int id, tlm::tlm_generic_payload& pl, sc_core::sc_time& delay);

    // instance specific extenion used to identify Non-Blocking transactions
    // We reuse code from TLM-2009-07-15/unit_test/tlm/nb2b_adapter/src/nb2b_adapter.cpp
    struct route_extension: tlm_utils::instance_specific_extension<route_extension> {
      int id;
    };
    tlm_utils::instance_specific_extension_accessor accessor;

    tlm::tlm_sync_enum nb_transport_fw(int id, tlm::tlm_generic_payload& pl,
                                       tlm::tlm_phase& phase, sc_core::sc_time& delay);

    tlm::tlm_sync_enum nb_transport_bw(int id, tlm::tlm_generic_payload& pl,
                                       tlm::tlm_phase& phase, sc_core::sc_time& delay);

    unsigned int transport_dbg(int id, tlm::tlm_generic_payload& pl);

    bool get_direct_mem_ptr(int id, tlm::tlm_generic_payload& pl,
                            tlm::tlm_dmi& dmi_data);

    void invalidate_dm_ptr(int id, sc_dt::uint64 start_range,
                           sc_dt::uint64 end_range);

    void print_mmap(std::ostream &os = std::cout);

  protected:

    struct Interval {
      Interval(size_t i, uint64_t a, uint64_t s):
        index(i), addr(a), size(s) {}
      bool operator<(const Interval &b) const {return addr>b.addr;}
      size_t index;
      uint64_t addr;
      uint64_t size;
    };

    std::vector<Interval> intervals;

    bool resolve(uint64_t &addr, size_t &index);
    bool resolve(uint64_t &addr, size_t &index, uint64_t &base);
  };

} // namespace simsoc

#endif //BUS_HPP
