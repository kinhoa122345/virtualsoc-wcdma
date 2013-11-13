//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PRIMECELL_DMAC_PL080_HPP
#define PRIMECELL_DMAC_PL080_HPP

// ARM PrimeCell DMA controller PL080
// http://infocenter.arm.com/help/topic/com.arm.doc.ddi0196g/DDI0196.pdf

#include <libsimsoc/module.hpp>
#include <libsimsoc/interfaces/tlm_signal.hpp>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>
#include <inttypes.h>

namespace simsoc {

  class PrimeCell_DMAC_PL080: public Module {
  public:
    // constants
    static const size_t CHANNEL_NB = 8;
    static const size_t REQUEST_NB = 16;

    static const uint32_t DMAC_INT_STATUS = 0x0;
    static const uint32_t DMAC_INT_TC_STATUS = 0x4;
    static const uint32_t DMAC_INT_TC_CLEAR = 0x8;
    static const uint32_t DMAC_INT_ERROR_STATUS = 0xC;
    static const uint32_t DMAC_INT_ERROR_CLEAR = 0x10;
    static const uint32_t DMAC_RAW_INT_TC_STATUS = 0x14;
    static const uint32_t DMAC_RAW_INT_ERROR_STATUS = 0x18;
    static const uint32_t DMAC_ENABLED_CHANNEL = 0x1C;
    static const uint32_t DMAC_SOFT_BURST_REQ = 0x20;
    static const uint32_t DMAC_SOFT_SINGLE_REQ = 0x24;
    static const uint32_t DMAC_SOFT_LAST_BURST_REQ = 0x28;
    static const uint32_t DMAC_SOFT_LAST_SINGLE_REQ = 0x2C;
    static const uint32_t DMAC_CONFIGURATION = 0x30;
    static const uint32_t DMAC_CONFIGURATION_MSK = 1|2|4;
    static const uint32_t DMAC_SYNC = 0x34;

    static const uint32_t CHANNEL_REGISTERS_BEGIN = 0x100;
    static const uint32_t CHANNEL_REGISTERS_END = 0x200;
    static const uint32_t DMAC_CHANNEL_SRC_ADDR = 0x0;
    static const uint32_t DMAC_CHANNEL_DEST_ADDR = 0x4;
    static const uint32_t DMAC_CHANNEL_LLI = 0x8;
    static const uint32_t DMAC_CHANNEL_CONTROL = 0xC;
    static const uint32_t DMAC_CHANNEL_CONFIGURATION = 0x10;

    static const uint32_t DMAC_PERIPH_ID0 = 0xFE0;
    static const uint32_t DMAC_PERIPH_ID0_VALUE = 0x80;
    static const uint32_t DMAC_PERIPH_ID1 = 0xFE4;
    static const uint32_t DMAC_PERIPH_ID1_VALUE = 0x10;
    static const uint32_t DMAC_PERIPH_ID2 = 0xFE8;
    static const uint32_t DMAC_PERIPH_ID2_VALUE = 0x14;
    static const uint32_t DMAC_PERIPH_ID3 = 0xFEC;
    static const uint32_t DMAC_PERIPH_ID3_VALUE = 0x0A;
    static const uint32_t DMAC_PRIMECELL_ID0 = 0xFF0;
    static const uint32_t DMAC_PRIMECELL_ID0_VALUE = 0x0D;
    static const uint32_t DMAC_PRIMECELL_ID1 = 0xFF4;
    static const uint32_t DMAC_PRIMECELL_ID1_VALUE = 0xF0;
    static const uint32_t DMAC_PRIMECELL_ID2 = 0xFF8;
    static const uint32_t DMAC_PRIMECELL_ID2_VALUE = 0x05;
    static const uint32_t DMAC_PRIMECELL_ID3 = 0xFFC;
    static const uint32_t DMAC_PRIMECELL_ID3_VALUE = 0xB1;

    // ports
    tlm_utils::simple_target_socket<PrimeCell_DMAC_PL080> target_socket;
    tlm_utils::simple_initiator_socket<PrimeCell_DMAC_PL080> initiator_socket;

    SignalInitiatorPort<bool> dmacinttc;
    SignalInitiatorPort<bool> dmacinterr;
    SignalInitiatorPort<bool> dmacintr;

    // replace some errors by warnings
    bool strict;

    SC_HAS_PROCESS(PrimeCell_DMAC_PL080);
    PrimeCell_DMAC_PL080(sc_core::sc_module_name name);
    ~PrimeCell_DMAC_PL080();

  protected:
    struct Channel: public Module {
      static const size_t BURST_SIZES[8];
      static const uint32_t CONFIGURATION_MSK = (1<<19)-1-(1<<10)-(1<<5);
      size_t num;
      PrimeCell_DMAC_PL080 &master;
      uint32_t src;
      uint32_t dest;
      uint32_t lli;
      uint32_t control;
      uint32_t configuration;

      Channel(PrimeCell_DMAC_PL080&, size_t channel_num);

      // control
      bool get_I() const {return control&(1<<31);}
      uint8_t get_Prot() const {return (control>>28)&7;}
      bool get_Prot_privileged() const {return control&(1<<28);}
      bool get_Prot_bufferable() const {return control&(1<<29);}
      bool get_Prot_cacheable() const {return control&(1<<30);}
      bool get_DI() const {return control&(1<<27);}
      bool get_SI() const {return control&(1<<26);}
      bool get_D() const {return control&(1<<25);}
      bool get_S() const {return control&(1<<24);}
      size_t get_DWidth() const {return (control>>21)&7;}
      size_t get_SWidth() const {return (control>>18)&7;}
      size_t get_DBSize() const {return BURST_SIZES[(control>>15)&7];}
      size_t get_SBSize() const {return BURST_SIZES[(control>>12)&7];}
      size_t get_TransferSize() const {return control&((1<<12)-1);}
      void decrement_TransferSize() {assert(control&((1<<12)-1)); --control;}

      // configuration
      bool get_H() const {return configuration&(1<<18);}
      bool get_A() const {return configuration&(1<<17);}
      bool get_L() const {return configuration&(1<<16);}
      bool get_ITC() const {return configuration&(1<<15);}
      bool get_IE() const {return configuration&(1<<14);}
      size_t get_FlowCntrl() const {return (configuration>>11)&7;}
      size_t get_DestPeripheral() const {return (configuration>>6)&0xF;}
      size_t get_SrcPeripheral() const {return (configuration>>1)&0xF;}
      bool get_E() const {return configuration&1;}
    };

    Channel* channels[CHANNEL_NB];

    uint32_t DMACRawIntTCStatus;
    uint32_t DMACRawIntErrorStatus;
    uint32_t DMACConfiguration;

    sc_core::sc_time transfer_time;

    sc_core::sc_event enable_event;

    // main thread
    void compute();

    // RW_Target methods
    void custom_b_transport(tlm::tlm_generic_payload &payload,
                            sc_core::sc_time &delay_time);
    uint32_t read_word(uint32_t addr);
    void write_word(uint32_t addr, uint32_t data);

    // registers
    uint32_t DMACIntStatus() const;
    uint32_t DMACIntTCStatus() const;
    void DMACIntTCClear(uint32_t data);
    uint32_t DMACIntErrorStatus() const;
    void DMACIntErrorClear(uint32_t data);
    uint32_t DMACEnbldChns() const;

    void set_DMACConfiguration(uint32_t value);
    bool is_enabled() const;
    bool is_in_big_endian_mode(size_t n) const; // n is 1 or 2

    uint32_t get_IntTC_mask() const;
    uint32_t get_IntError_mask() const;

    void write_channel_configuration(size_t n, uint32_t data);
    bool load_lli(size_t n);
  };

} // namespace simsoc

#endif //PRIMECELL_DMAC_PL080_HPP
