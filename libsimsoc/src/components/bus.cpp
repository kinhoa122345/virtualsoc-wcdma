//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "bus.hpp"
#include <algorithm>

using namespace std;
using namespace sc_core;
using namespace tlm;

namespace simsoc {

  Bus::Bus(sc_module_name name):
    Module(name),
    target_sockets("target_sockets"),
    initiator_sockets("initiator_sockets"),
    intervals()
  {
    target_sockets.register_b_transport(this, &Bus::b_transport);
    target_sockets.register_nb_transport_fw(this, &Bus::nb_transport_fw);
    target_sockets.register_get_direct_mem_ptr(this, &Bus::get_direct_mem_ptr);
    target_sockets.register_transport_dbg(this, &Bus::transport_dbg);
    initiator_sockets.register_nb_transport_bw(this, &Bus::nb_transport_bw);
    initiator_sockets.register_invalidate_direct_mem_ptr(this, &Bus::invalidate_dm_ptr);
  }

  void Bus::before_end_of_elaboration() {
    // sort intervals
    std::sort(intervals.begin(),intervals.end());
    // check intervals for overlaps
    for (size_t i = 1, ei = intervals.size(); i!=ei; ++i)
      if (intervals[i].addr+intervals[i].size>intervals[i-1].addr) {
        error() <<"at least two intervals overlap in memory map.\n";
        print_mmap();
        exit(1);
      }
  }

  void Bus::bind_target(base_target_socket_type &port,
                        uint32_t addr, uint32_t size) {
    assert(addr<=addr+size-1);
    size_t n = intervals.size();
    assert((size_t)initiator_sockets.size()==n);
    initiator_sockets(port);
    intervals.push_back(Interval(n,addr,size));
  }

  void Bus::b_transport(int id, tlm::tlm_generic_payload& pl, sc_time& delay) {
    assert(pl.get_response_status()==TLM_INCOMPLETE_RESPONSE);
    uint64_t addr = pl.get_address();
    size_t index;
    if (resolve(addr,index)) {
      pl.set_address(addr);
      initiator_sockets[index]->b_transport(pl, delay);
    } else {
      pl.set_response_status(TLM_ADDRESS_ERROR_RESPONSE);
    }
  }

  tlm::tlm_sync_enum Bus::nb_transport_fw(int id, tlm::tlm_generic_payload& pl,
                                          tlm::tlm_phase& phase, sc_time& delay) {
    uint64_t addr = pl.get_address();
    size_t index;
    if (resolve(addr,index)) {
      route_extension* ext = 0;
      if (phase==tlm::BEGIN_REQ) {
        ext = new route_extension;
        ext->id = id;
        accessor(pl).set_extension(ext);
      }
      pl.set_address(addr);
      tlm::tlm_sync_enum status;
      status = initiator_sockets[index]->nb_transport_fw(pl, phase, delay);
      if (status==tlm::TLM_COMPLETED) {
        accessor(pl).clear_extension(ext);
        delete ext;
      }
      return status;
    } else {
      pl.set_response_status(TLM_ADDRESS_ERROR_RESPONSE);
      return TLM_COMPLETED;
    }
  }

  tlm::tlm_sync_enum Bus::nb_transport_bw(int id, tlm::tlm_generic_payload& pl,
                                          tlm::tlm_phase& phase, sc_time& delay) {
    route_extension* ext = 0;
    accessor(pl).get_extension(ext);
    assert(ext);
    tlm::tlm_sync_enum status;
    status = target_sockets[ext->id]->nb_transport_bw(pl, phase, delay );
    if (status==tlm::TLM_COMPLETED) {
      accessor(pl).clear_extension(ext);
      delete ext;
    }
    return status;
  }

  unsigned int Bus::transport_dbg(int id, tlm::tlm_generic_payload& pl) {
    assert(pl.get_response_status()==TLM_INCOMPLETE_RESPONSE);
    uint64_t addr = pl.get_address();
    size_t index;
    if (resolve(addr,index)) {
      pl.set_address(addr);
      const unsigned int reply = initiator_sockets[index]->transport_dbg(pl);
      return reply;
    } else {
      pl.set_response_status(TLM_ADDRESS_ERROR_RESPONSE);
      return 0;
    }
  }

  bool Bus::get_direct_mem_ptr(int id, tlm::tlm_generic_payload& pl,
                               tlm::tlm_dmi& dmi_data) {
    assert(pl.get_response_status()==TLM_INCOMPLETE_RESPONSE);
    uint64_t addr = pl.get_address();
    const uint64_t orig_addr = addr;
    uint64_t base = 0;
    size_t index;
    if (resolve(addr,index,base)) {
      pl.set_address(addr);
      bool status = initiator_sockets[index]->get_direct_mem_ptr(pl, dmi_data);
      uint64_t dmi_start = base + dmi_data.get_start_address();
      uint64_t dmi_end = base + dmi_data.get_end_address();
      dmi_data.set_start_address(dmi_start);
      dmi_data.set_end_address(dmi_end);
      pl.set_address(orig_addr);
      return status;
    } else {
      pl.set_response_status(TLM_ADDRESS_ERROR_RESPONSE);
      return false;
    }
  }

  void Bus::invalidate_dm_ptr(int id, sc_dt::uint64 start_range,
                              sc_dt::uint64 end_range) {
    size_t i = 0, ei = intervals.size();
    while (i!=ei && i!=intervals[i].index) ++i;
    assert(i!=ei && i==intervals[i].index && "invalid id");
    assert(start_range<intervals[i].size && "start address outside target range");
    const uint64_t start = intervals[i].addr + start_range;
    if (end_range>intervals[i].size) {
      warning() <<"invalidate_direct_mem_ptr: end_range is outside target size\n.";
      end_range = intervals[i].size;
    }
    const uint64_t end = intervals[i].addr + end_range;
    for (unsigned int i = 0; i<target_sockets.size(); ++i)
      target_sockets[i]->invalidate_direct_mem_ptr(start, end);
  }

  void Bus::print_mmap(ostream &os) {
    for (vector<Bus::Interval>::iterator i = intervals.begin(),
           ei = intervals.end(); i!=ei; ++i)
      os <<"interval [" <<hex <<i->addr <<',' <<i->addr+i->size
         <<") mapped to port #" <<dec <<i->index <<endl;
  }

  // return true if a target is found at this address
  bool Bus::resolve(uint64_t &addr, size_t &index) {
    std::vector<Bus::Interval>::iterator i =
      lower_bound(intervals.begin(),intervals.end(),Interval(0,addr,0));
    if (i==intervals.end() || i->addr+i->size-1<addr) {
      return false;
    } else {
      addr -= i->addr;
      index = i->index;
      return true;
    }
  }

  // return true if a target is found at this address
  bool Bus::resolve(uint64_t &addr, size_t &index, uint64_t &base) {
    std::vector<Bus::Interval>::iterator i =
      lower_bound(intervals.begin(),intervals.end(),Interval(0,addr,0));
    if (i==intervals.end() || i->addr+i->size-1<addr) {
      return false;
    } else {
      addr -= i->addr;
      index = i->index;
      base = i->addr;
      return true;
    }
  }

} // namespace simsoc
