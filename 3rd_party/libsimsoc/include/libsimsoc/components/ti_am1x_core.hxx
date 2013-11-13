//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//


#if !defined(LIBSIMSOC_TI_AM1X_CORE_HPP__) || defined(LIBSIMSOC_TI_AM1X_CORE_HXX__)
# error "DO NOT INCLUDE THIS FILE DIRECTLY"
#endif

#define LIBSIMSOC_TI_AM1X_CORE_HXX__

#include "libsimsoc/interfaces/tlm_helper.hpp"

namespace simsoc  {
namespace TI_AM1x {

  // ------------------------------------------------------------------
  template < class T >
  TI_AM1x_core<T>::TI_AM1x_core(sc_core::sc_module_name name, T *myself)
    :Module(name)
  {
    m_inport.register_b_transport(myself, &TI_AM1x_core::custom_b_transport);
  }

  // ------------------------------------------------------------------
  template < class T >
  TI_AM1x_core<T>::~TI_AM1x_core() {}

  // ------------------------------------------------------------------
  template < class T >
  void TI_AM1x_core<T>::custom_b_transport
  (tlm::tlm_generic_payload &payload, sc_core::sc_time &delay_time)
  {
    assert(payload.get_response_status() == tlm::TLM_INCOMPLETE_RESPONSE);

    if (payload.get_data_length() != 4) {
      warning()
        << "received transaction with invalid data length (should be 4)"
        << std::endl;
      payload.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
      return ;
    }

    if (payload.get_streaming_width() != payload.get_data_length()) {
      warning()
        << "received transaction with invalid streaming width"
        << std::endl;
      payload.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE);
      return ;
    }

    if (payload.get_byte_enable_ptr()) {
      warning()
        << "byte enable not supported"
        << std::endl;
      payload.set_response_status(tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE);
      return ;
    }

    uint32_t  address = (uint32_t) payload.get_address();
    uint32_t *buffer  = reinterpret_cast<uint32_t*>(payload.get_data_ptr());

    switch (payload.get_command()) {
    case tlm::TLM_WRITE_COMMAND:
      write_word(address, *buffer);
      payload.set_response_status(tlm::TLM_OK_RESPONSE);
      break;

    case tlm::TLM_READ_COMMAND:
      *buffer = read_word(address);
      payload.set_response_status(tlm::TLM_OK_RESPONSE);
      break;

    default:
      warning() << "command not supported" << std::endl;
      payload.set_response_status(tlm::TLM_COMMAND_ERROR_RESPONSE);
    }
  }

  // ------------------------------------------------------------------
  template < class T >
  TI_AM1x_oport<T>::TI_AM1x_oport(T *myself)
    :m_delay(sc_core::SC_ZERO_TIME)
  {}

  // ------------------------------------------------------------------
  template < class T >
  TI_AM1x_oport<T>::~TI_AM1x_oport() {}

  // ------------------------------------------------------------------
  template < class T >
  uint8_t TI_AM1x_oport<T>::_rd_8 (uint32_t address) {
    tlm::tlm_generic_payload pl;
    uint8_t aout;

    set_payload(pl, address, (unsigned char*)(&aout), 1);
    pl.set_streaming_width(4);
    pl.set_command(tlm::TLM_READ_COMMAND);
    m_outport->b_transport(pl, m_delay);
    return aout;
  }

  // ------------------------------------------------------------------
  template < class T >
  uint16_t TI_AM1x_oport<T>::_rd_16(uint32_t address) {
    tlm::tlm_generic_payload pl;
    uint16_t aout;

    set_payload(pl, address, (unsigned char*)(&aout), 2);
    pl.set_streaming_width(4);
    pl.set_command(tlm::TLM_READ_COMMAND);
    m_outport->b_transport(pl, m_delay);
    return aout;
  }

  // ------------------------------------------------------------------
  template < class T >
  uint32_t TI_AM1x_oport<T>::_rd_32(uint32_t address) {
    tlm::tlm_generic_payload pl;
    uint32_t aout;

    set_payload(pl, address, (unsigned char*)(&aout), 4);
    pl.set_streaming_width(4);
    pl.set_command(tlm::TLM_READ_COMMAND);
    m_outport->b_transport(pl, m_delay);
    return aout;
  }

  // ------------------------------------------------------------------
  template < class T >
  void TI_AM1x_oport<T>::_wr_8(uint32_t address, uint8_t  input) {
    tlm::tlm_generic_payload pl;

    set_payload(pl, address, (unsigned char*)(&input), 1);
    pl.set_streaming_width(4);
    pl.set_command(tlm::TLM_WRITE_COMMAND);
    m_outport->b_transport(pl, m_delay);
  }

  // ------------------------------------------------------------------
  template < class T >
  void TI_AM1x_oport<T>::_wr_16(uint32_t address, uint16_t input) {
    tlm::tlm_generic_payload pl;

    set_payload(pl, address, (unsigned char*)(&input), 2);
    pl.set_streaming_width(4);
    pl.set_command(tlm::TLM_WRITE_COMMAND);
    m_outport->b_transport(pl, m_delay);
  }

  // ------------------------------------------------------------------
  template < class T >
  void TI_AM1x_oport<T>::_wr_32(uint32_t address, uint32_t input) {
    tlm::tlm_generic_payload pl;

    set_payload(pl, address, (unsigned char*)(&input), 4);
    pl.set_streaming_width(4);
    pl.set_command(tlm::TLM_WRITE_COMMAND);
    m_outport->b_transport(pl, m_delay);
  }

  // ------------------------------------------------------------------
  template < class T >
  void TI_AM1x_oport<T>::_rd(uint8_t *dst, uint32_t addr, uint32_t size) {
    tlm::tlm_generic_payload pl;

    set_payload(pl, addr, (unsigned char*)(dst), size);
    pl.set_streaming_width(1);
    pl.set_command(tlm::TLM_READ_COMMAND);
    m_outport->b_transport(pl, m_delay);
  }

  // ------------------------------------------------------------------
  template < class T >
  void TI_AM1x_oport<T>::_wr(const uint8_t *dst, uint32_t addr, uint32_t size) {
    tlm::tlm_generic_payload pl;

    set_payload(pl, addr, (unsigned char*)(dst), size);
    pl.set_streaming_width(1);
    pl.set_command(tlm::TLM_WRITE_COMMAND);
    m_outport->b_transport(pl, m_delay);
  }

} // TI_AM1x
} // simsoc
