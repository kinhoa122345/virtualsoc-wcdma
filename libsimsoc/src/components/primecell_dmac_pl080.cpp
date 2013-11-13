//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "primecell_dmac_pl080.hpp"

using namespace std;
using namespace sc_core;

namespace simsoc {

  PrimeCell_DMAC_PL080::Channel::Channel(PrimeCell_DMAC_PL080 &m, size_t channel_num):
    Module((string("channel_"+string_of<size_t>(channel_num))).c_str()),
    num(channel_num),
    master(m),
    src(0), dest(0), lli(0), control(0), configuration(0)
  {}

const size_t PrimeCell_DMAC_PL080::Channel::BURST_SIZES[8] = {1,4,8,16,32,64,128,256};

PrimeCell_DMAC_PL080::PrimeCell_DMAC_PL080(sc_module_name name):
  Module(name),
  target_socket("target_socket"),
  initiator_socket("initiator_socket"),
  strict(true),
  DMACConfiguration(0),
  transfer_time(10,SC_NS)
{
  for (size_t i = 0; i<CHANNEL_NB; ++i)
    channels[i] = new Channel(*this,i);
  target_socket.register_b_transport(this, &PrimeCell_DMAC_PL080::custom_b_transport);
  SC_THREAD(compute);
  dont_initialize();
  sensitive <<enable_event;
}

PrimeCell_DMAC_PL080::~PrimeCell_DMAC_PL080() {}

void PrimeCell_DMAC_PL080::custom_b_transport(tlm::tlm_generic_payload &payload,
                                              sc_core::sc_time &delay_time) {
  assert(payload.get_response_status()==tlm::TLM_INCOMPLETE_RESPONSE);
  if (payload.get_data_length()!=4) {
    warning() <<"received transaction with invalid data length (should be 4).\n";
    payload.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
  } else if (payload.get_streaming_width()<payload.get_data_length()) {
    warning() <<"received transaction with invalid streaming width.\n";
    payload.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
  } else if (payload.get_byte_enable_ptr()) {
    warning() <<"byte enable not supported.\n";
    payload.set_response_status(tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE);
  } else {
    switch (payload.get_command()) {
    default:
      info() <<"command not supported.\n";
      payload.set_response_status(tlm::TLM_COMMAND_ERROR_RESPONSE);
      break;
    case tlm::TLM_WRITE_COMMAND:
      write_word(static_cast<uint32_t>(payload.get_address()),
                 *reinterpret_cast<uint32_t*>(payload.get_data_ptr()));
      payload.set_response_status(tlm::TLM_OK_RESPONSE);
      break;
    case tlm::TLM_READ_COMMAND:
      *reinterpret_cast<uint32_t*>(payload.get_data_ptr()) =
        read_word(static_cast<uint32_t>(payload.get_address()));
      payload.set_response_status(tlm::TLM_OK_RESPONSE);
      break;
    }
  }
}

uint32_t PrimeCell_DMAC_PL080::read_word(uint32_t addr) {
  debug() <<"read from offset " <<hex <<addr <<endl;
  if (CHANNEL_REGISTERS_BEGIN<=addr&&addr<CHANNEL_REGISTERS_END) {
    size_t n = (addr-CHANNEL_REGISTERS_BEGIN)/0x20;
    assert(n<8);
    uint32_t offset = (addr-CHANNEL_REGISTERS_BEGIN)%0x20;
    switch (offset) {
    case DMAC_CHANNEL_SRC_ADDR:
      if (channels[n]->get_A())
        warning() <<"Techincal Reference Manual does not recommend to read"
          " DMACCxSrcAddr while channel is active\n";
      return channels[n]->src;
    case DMAC_CHANNEL_DEST_ADDR:
      if (channels[n]->get_A())
        warning() <<"Techincal Reference Manual does not recommend to read"
          " DMACCxDestAddr while channel is active\n";
      return channels[n]->dest;
    case DMAC_CHANNEL_LLI:
      return channels[n]->lli;
    case DMAC_CHANNEL_CONTROL:
      if (channels[n]->get_A())
        warning() <<"Techincal Reference Manual does not recommend to read"
          " DMACCxControl while channel is active\n";
      return channels[n]->control;
    case DMAC_CHANNEL_CONFIGURATION:
      return channels[n]->configuration;
    default:
      error() <<"no regsiter at offset " <<hex <<addr  <<" (read access)\n";
      exit(1);
    }
  } else {
    switch (addr) {
    case DMAC_INT_STATUS: return DMACIntStatus();
    case DMAC_INT_TC_STATUS: return DMACIntTCStatus();
    case DMAC_INT_TC_CLEAR:
      if (strict) {
        error() <<"register DMACIntTCClear is write-only\n";
        exit(1);
      } else {
        warning() <<"register DMACIntTCClear is write-only\n";
        return 0;
      }
    case DMAC_INT_ERROR_STATUS: return DMACIntErrorStatus();
    case DMAC_INT_ERROR_CLEAR:
      if (strict) {
        error() <<"register DMACIntErrorClear is write-only\n";
        exit(1);
      } else {
        warning() <<"register DMACIntErrorClear is write-only\n";
        return 0;
      }
    case DMAC_RAW_INT_TC_STATUS: return DMACRawIntTCStatus;
    case DMAC_RAW_INT_ERROR_STATUS: return DMACRawIntErrorStatus;
    case DMAC_ENABLED_CHANNEL: return DMACEnbldChns();
    case DMAC_SOFT_BURST_REQ: TODO("DMACSoftBReq register (read access)");
    case DMAC_SOFT_SINGLE_REQ: TODO("DMACSoftSReq register (read access)");
    case DMAC_SOFT_LAST_BURST_REQ: TODO("DMACSoftLBReq register (read access)");
    case DMAC_SOFT_LAST_SINGLE_REQ: TODO("DMACSoftLSReq register (read access)");
    case DMAC_CONFIGURATION: return DMACConfiguration;
    case DMAC_SYNC: TODO("DMACSync register (read access)");
    case DMAC_PERIPH_ID0: return DMAC_PERIPH_ID0_VALUE;
    case DMAC_PERIPH_ID1: return DMAC_PERIPH_ID1_VALUE;
    case DMAC_PERIPH_ID2: return DMAC_PERIPH_ID2_VALUE;
    case DMAC_PERIPH_ID3: return DMAC_PERIPH_ID3_VALUE;
    case DMAC_PRIMECELL_ID0: return DMAC_PRIMECELL_ID0_VALUE;
    case DMAC_PRIMECELL_ID1: return DMAC_PRIMECELL_ID1_VALUE;
    case DMAC_PRIMECELL_ID2: return DMAC_PRIMECELL_ID2_VALUE;
    case DMAC_PRIMECELL_ID3: return DMAC_PRIMECELL_ID3_VALUE;
    default:
      error() <<"no regsiter at offset " <<hex <<addr <<" (read access)\n";
      exit(1);
    }
  }
}

void PrimeCell_DMAC_PL080::write_word(uint32_t addr, uint32_t data) {
  debug() <<"write " <<hex <<data <<" to offset " <<addr <<endl;
  if (CHANNEL_REGISTERS_BEGIN<=addr&&addr<CHANNEL_REGISTERS_END) {
    size_t n = (addr-CHANNEL_REGISTERS_BEGIN)/0x20;
    assert(n<8);
    uint8_t offset = (addr-CHANNEL_REGISTERS_BEGIN)%0x20;
    switch (offset) {
    case DMAC_CHANNEL_SRC_ADDR:
      if (channels[n]->get_E()) {
        error() <<"reprogramming channel " <<dec <<n <<" while enabled (register DMACCxSrcAddr)\n";
        exit(1);
      }
      channels[n]->src = data;
      return;
    case DMAC_CHANNEL_DEST_ADDR:
      if (channels[n]->get_E()) {
        error() <<"reprogramming channel " <<dec <<n <<" while enabled (register DMACCxDestAddr)\n";
        exit(1);
      }
      channels[n]->dest = data;
      return;
    case DMAC_CHANNEL_LLI:
      if (channels[n]->get_E()) {
        error() <<"reprogramming channel " <<dec <<n <<" while enabled (register DMACCxLLI)\n";
        exit(1);
      }
      channels[n]->lli = data;
      return;
    case DMAC_CHANNEL_CONTROL:
      if (channels[n]->get_E()) {
        error() <<"reprogramming channel " <<dec <<n <<" while enabled (register DMACCxControl)\n";
        exit(1);
      }
      channels[n]->control = data;
      if (channels[n]->get_DWidth()>2) {
        error() <<"cannot set DWith to "
                <<dec <<channels[n]->get_DWidth()
                <<" (can only be 0, 1 or 2)\n";
        exit(1);
      }
      if (channels[n]->get_SWidth()>2) {
        error() <<"cannot set SWith to "
                <<dec <<channels[n]->get_SWidth()
                <<" (can only be 0, 1 or 2)\n";
        exit(1);
      }
      return;
    case DMAC_CHANNEL_CONFIGURATION:
      write_channel_configuration(n,data);
      return;
    default:
      error() <<"no register at offset " <<hex <<addr  <<" (write access)\n";
      exit(1);
    }
  } else {
    switch (addr) {
    case DMAC_INT_STATUS:
      error() <<"register DMACIntStatus is read-only\n";
      exit(1);
    case DMAC_INT_TC_STATUS:
      error() <<"register DMACIntTCStatus is read-only\n";
      exit(1);
    case DMAC_INT_TC_CLEAR:
      DMACIntTCClear((uint8_t)data);
      return;
    case DMAC_INT_ERROR_STATUS:
      error() <<"register DMACIntErrorStatus is read-only\n";
      exit(1);
    case DMAC_INT_ERROR_CLEAR:
      DMACIntErrorClear((uint8_t)data);
      return;
    case DMAC_RAW_INT_TC_STATUS:
      error() <<"register DMACRawIntTCStatus is read-only\n";
      exit(1);
    case DMAC_RAW_INT_ERROR_STATUS:
      error() <<"register DMACRawIntErrorStatus is read-only\n";
      exit(1);
    case DMAC_ENABLED_CHANNEL:
      error() <<"register DMACEnbldChns is read-only\n";
      exit(1);
    case DMAC_SOFT_BURST_REQ: TODO("DMACSoftBReq register (write access)");
    case DMAC_SOFT_SINGLE_REQ: TODO("DMACSoftSReq register (write access)");
    case DMAC_SOFT_LAST_BURST_REQ: TODO("DMACSoftLBReq register (write access)");
    case DMAC_SOFT_LAST_SINGLE_REQ: TODO("DMACSoftLSReq register (write access)");
    case DMAC_CONFIGURATION:
      set_DMACConfiguration(data&DMAC_CONFIGURATION_MSK);
      return;
    case DMAC_SYNC: TODO("DMACSync register (write access)");
    case DMAC_PERIPH_ID0:
    case DMAC_PERIPH_ID1:
    case DMAC_PERIPH_ID2:
    case DMAC_PERIPH_ID3:
    case DMAC_PRIMECELL_ID0:
    case DMAC_PRIMECELL_ID1:
    case DMAC_PRIMECELL_ID2:
    case DMAC_PRIMECELL_ID3:
      error() <<"identification registers are read-only (offset: " <<hex <<addr <<")\n";
      exit(1);
    default:
      error() <<"no regsiter at offset " <<hex <<addr <<" (or not implemented)\n";
      exit(1);
    }
  }
}

uint32_t PrimeCell_DMAC_PL080::DMACIntStatus() const {
  return DMACIntTCStatus()|DMACIntErrorStatus();
}

uint32_t PrimeCell_DMAC_PL080::DMACIntTCStatus() const {
  return DMACRawIntTCStatus&get_IntTC_mask();
}

uint32_t PrimeCell_DMAC_PL080::DMACIntErrorStatus() const {
  return DMACRawIntErrorStatus&get_IntError_mask();
}

void PrimeCell_DMAC_PL080::DMACIntTCClear(uint32_t data) {
  DMACRawIntTCStatus &=~ data;
  dmacinttc = DMACIntTCStatus();
  dmacintr = dmacinterr||dmacinttc;
}

void PrimeCell_DMAC_PL080::DMACIntErrorClear(uint32_t data) {
  DMACRawIntErrorStatus &=~ data;
  dmacinterr = DMACIntErrorStatus();
  dmacintr = dmacinterr||dmacinttc;
}

uint32_t PrimeCell_DMAC_PL080::DMACEnbldChns() const {
  uint32_t enabled = 0;
  for (size_t i = 0; i<CHANNEL_NB; ++i)
    if (channels[i]->get_E())
      enabled |= (1<<i);
  return enabled;
}

void PrimeCell_DMAC_PL080::set_DMACConfiguration(uint32_t value) {
  if (is_enabled()&&!(value&1)) {
    if (DMACEnbldChns()) {
      error() <<"trying to disable the DMAC while some channels are still active\n"
        "\t\t\t(see section 3.2.2 of the Technical Reference Manual for the PL080)\n";
      exit(1);
    }
    info() <<"DMAC disabled\n";
  } else if (!is_enabled()&&(value&1)) {
    assert(!DMACEnbldChns());
    info() <<"DMAC enabled\n";
  }
  if (is_in_big_endian_mode(1)||is_in_big_endian_mode(2)) {
    TODO("big endian mode");
  }
  DMACConfiguration = value;
}

bool PrimeCell_DMAC_PL080::is_enabled() const {
  return DMACConfiguration&1;
}

bool PrimeCell_DMAC_PL080::is_in_big_endian_mode(size_t n) const {
  assert(1<=n&&n<=2);
  return DMACConfiguration&(1<<n);
}

uint32_t PrimeCell_DMAC_PL080::get_IntTC_mask() const {
  uint32_t mask = 0;
  for (size_t i = 0; i<CHANNEL_NB; ++i)
    if (channels[i]->get_ITC())
      mask |= (1<<i);
  return mask;
}

uint32_t PrimeCell_DMAC_PL080::get_IntError_mask() const {
  uint32_t mask = 0;
  for (size_t i = 0; i<CHANNEL_NB; ++i)
    if (channels[i]->get_IE())
      mask |= (1<<i);
  return mask;
}

void PrimeCell_DMAC_PL080::write_channel_configuration(size_t n, uint32_t data) {
  if (!is_enabled()) {
    if (strict) {
      error() <<"dmac must be enabled before configuring a channel\n";
      exit(1);
    } else {
      warning() <<"dmac must be enabled before configuring a channel\n";
      warning() <<"strict mode off; enable dmac automatically.\n";
      set_DMACConfiguration(DMACConfiguration|1);
    }
  }
  assert(is_enabled());
  if (data&~Channel::CONFIGURATION_MSK) {
    warning() <<"when writing to a channel configuration register, undefined bits should be write as zero.\n";
    data &= Channel::CONFIGURATION_MSK;
    assert(!(data&~Channel::CONFIGURATION_MSK));
  }
  data &=~ (1<<17); // clear A bit if set
  uint32_t diff = (data^channels[n]->configuration) &~(1<<17);
  channels[n]->configuration = data | (channels[n]->configuration&(1<<17));
  if (diff&1) {
    if (channels[n]->get_E()) {
      info() <<"enable channel #" <<dec <<n <<'\n';
      enable_event.notify();
    } else {
      info() <<"disable channel #" <<dec <<n <<" (from software)\n";
      if (channels[n]->get_A()) {
        info() <<"channel #" <<dec <<n <<" was active; data lost may has occured\n";
        channels[n]->configuration &=~ (1<<17);
      }
    }
  }
}

void PrimeCell_DMAC_PL080::compute() {
  tlm::tlm_generic_payload pl;
  pl.set_streaming_width(4);
  while (true) {
    size_t n = ffs(DMACEnbldChns())-1;
    while (n>=CHANNEL_NB) {
      info() <<"waiting\n";
      wait(enable_event);
      n = ffs(DMACEnbldChns())-1;
    }
    if (channels[n]->get_FlowCntrl()) {
      cout <<hex <<channels[n]->configuration <<endl;
      TODO("transfer from or to a peripheral");
    }
    if (channels[n]->get_L()) {
      TODO("lock control");
    }
    if (channels[n]->get_H()) {
      TODO("halt bit");
    }
    info() <<"activate channel #" <<dec <<n <<'\n';
    channels[n]->configuration |= (1<<17);

    do {
      if (channels[n]->get_DWidth()!=channels[n]->get_SWidth()) {
        TODO("transfer with DWidth!=SWidth");
      }
      sc_time wait_time = transfer_time*channels[n]->get_TransferSize();
      while (channels[n]->get_TransferSize()) {
        switch (channels[n]->get_DWidth()) {
        case 0:
          {
            uint8_t data=0;
            pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
            pl.set_command(tlm::TLM_READ_COMMAND);
            pl.set_address(channels[n]->src);
            pl.set_data_length(1);
            pl.set_data_ptr(reinterpret_cast<uint8_t*>(&data));
            initiator_socket->b_transport(pl,wait_time);
            if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
              TODO("should report the error to the processor.");
            pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
            pl.set_command(tlm::TLM_WRITE_COMMAND);
            pl.set_address(channels[n]->dest);
            initiator_socket->b_transport(pl,wait_time);
            if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
              TODO("should report the error to the processor.");
          }
          break;
        case 1:
          {
            uint16_t data=0;
            pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
            pl.set_command(tlm::TLM_READ_COMMAND);
            pl.set_address(channels[n]->src);
            pl.set_data_length(2);
            pl.set_data_ptr(reinterpret_cast<uint8_t*>(&data));
            initiator_socket->b_transport(pl,wait_time);
            if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
              TODO("should report the error to the processor.");
            pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
            pl.set_command(tlm::TLM_WRITE_COMMAND);
            pl.set_address(channels[n]->dest);
            initiator_socket->b_transport(pl,wait_time);
            if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
              TODO("should report the error to the processor.");
          }
          break;
        case 2:
          {
            uint32_t data = 0;
            pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
            pl.set_command(tlm::TLM_READ_COMMAND);
            pl.set_address(channels[n]->src);
            pl.set_data_length(4);
            pl.set_data_ptr(reinterpret_cast<uint8_t*>(&data));
            initiator_socket->b_transport(pl,wait_time);
            if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
              TODO("should report the error to the processor.");
            pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
            pl.set_command(tlm::TLM_WRITE_COMMAND);
            pl.set_address(channels[n]->dest);
            initiator_socket->b_transport(pl,wait_time);
            if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
              TODO("should report the error to the processor.");
          }
          break;
        default: abort();
        }
        if (channels[n]->get_SI()) {
          debug() <<"increment source address\n";
          channels[n]->src += 1<<channels[n]->get_SWidth();
        }
        if (channels[n]->get_DI()) {
          debug() <<"increment destination address\n";
          channels[n]->dest += 1<<channels[n]->get_DWidth();
        }
        channels[n]->decrement_TransferSize();
      }
      wait(wait_time);
    } while (load_lli(n));
    info() <<"disable channel #" <<dec <<n <<" (from controller)\n";
    channels[n]->configuration &=~ (1|(1<<17));
    if (channels[n]->get_I()) {
      info() <<"raise TC interrupt (unless masked)\n";
      DMACRawIntTCStatus |= 1<<n;
      dmacinttc = DMACIntTCStatus();
      if (dmacinttc)
        debug() <<"DMACINTTC is HIGH\n";
      else
        debug() <<"DMACINTTC is LOW\n";
      dmacintr = dmacinterr||dmacinttc;
      if (dmacintr)
        debug() <<"DMACINTR is HIGH\n";
      else
        debug() <<"DMACINTR is LOW\n";
    }
  }
}

bool PrimeCell_DMAC_PL080::load_lli(size_t n) {
  const uint32_t lli = channels[n]->lli;
  if (!lli)
    return false;
  else {
    info() <<"load LLI for channel #" <<dec <<n <<'\n';
    sc_time wait_time = 2*transfer_time;
    // common payload initialization
    tlm::tlm_generic_payload pl;
    pl.set_streaming_width(4);
    pl.set_data_length(4);
    pl.set_command(tlm::TLM_READ_COMMAND);
    // 1st transfer: src
    pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    pl.set_address(lli);
    pl.set_data_ptr(reinterpret_cast<uint8_t*>(&channels[n]->src));
    initiator_socket->b_transport(pl,wait_time);
    if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
      TODO("should report the error to the processor.");
    // 2nd transfer: dest
    pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    pl.set_address(lli+4);
    pl.set_data_ptr(reinterpret_cast<uint8_t*>(&channels[n]->dest));
    initiator_socket->b_transport(pl,wait_time);
    if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
      TODO("should report the error to the processor.");
    // 3rd transfer: lli
    pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    pl.set_address(lli+8);
    pl.set_data_ptr(reinterpret_cast<uint8_t*>(&channels[n]->lli));
    initiator_socket->b_transport(pl,wait_time);
    if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
      TODO("should report the error to the processor.");
    // 4th transfer: control
    pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    pl.set_address(lli+12);
    pl.set_data_ptr(reinterpret_cast<uint8_t*>(&channels[n]->control));
    initiator_socket->b_transport(pl,wait_time);
    if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
      TODO("should report the error to the processor.");
    // check loaded values
    if (channels[n]->get_DWidth()>2) {
      error() <<"cannot set DWith to "
              <<dec <<channels[n]->get_DWidth()
              <<" (can only be 0, 1 or 2)\n";
      exit(1);
    }
    if (channels[n]->get_SWidth()>2) {
      error() <<"cannot set SWith to "
              <<dec <<channels[n]->get_SWidth()
              <<" (can only be 0, 1 or 2)\n";
      exit(1);
    }
    wait(wait_time);
    return true;
  }
}

} // namespace simsoc
