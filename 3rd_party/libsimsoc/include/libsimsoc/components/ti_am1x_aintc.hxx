//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined(LIBSIMSOC_TI_AM1X_AINTC_HPP__) || defined(LIBSIMSOC_TI_AM1X_AINTC_HXX__)
# error "DO NOT INCLUDE THIS FILE DIRECTLY"
#endif

#define LIBSIMSOC_TI_AM1X_AINTC_HXX__

#define chan_t AINTC_R_Int::chan_t
#define bits_t AINTC_R_Int::bits_t

#include "libsimsoc/bitwise_operator.hpp"
#include <cstring>

namespace simsoc  {
namespace TI_AM1x {

  // ------------------------------------------------------------------
  inline AINTC_R_Int::AINTC_R_Int() {
    memset(m_rawpending, 0, sizeof(m_rawpending));
    memset(m_enabled   , 0, sizeof(m_enabled));
    memset(m_channels  , 0, sizeof(m_channels));
  }

  // ------------------------------------------------------------------
  inline size_t AINTC_R_Int::segment_ck(size_t interrupt) {
    return (interrupt / (8 * sizeof(bits_t)));
  }

  inline size_t AINTC_R_Int::offset_ck(size_t interrupt) {
    return (interrupt % (8 * sizeof(bits_t)));
  }

  inline bits_t AINTC_R_Int::mask_of_ck(size_t chunkid) {
    if (chunkid >= NCHUNKS)
      return 0;
    return full<bits_t>(NINTERRUPTS - (chunkid * CK_SIZE));
  }

  // ------------------------------------------------------------------
  inline bool AINTC_R_Int::is_enabled(size_t it) {
    if (it >= NINTERRUPTS) abort();
    return is_set<bits_t>(m_enabled[segment_ck(it)], offset_ck(it));
  }

  inline bool AINTC_R_Int::is_rawpending(size_t it) {
    if (it >= NINTERRUPTS) abort();
    return is_set<bits_t>(m_rawpending[segment_ck(it)], offset_ck(it));
  }

  inline bool AINTC_R_Int::is_pending(size_t it) {
    if (it >= NINTERRUPTS) abort();

    const size_t segment = segment_ck(it);
    const bits_t mask    = m_rawpending[segment] & m_enabled[segment];

    return is_set<bits_t>(mask, offset_ck(it));
  }

  // ------------------------------------------------------------------
  inline void AINTC_R_Int::set_enabled_ck(size_t chunkid, bits_t enabled) {
    if (chunkid >= NCHUNKS) abort();
    this->m_enabled[chunkid] |= (enabled & mask_of_ck(chunkid));
  }

  inline void AINTC_R_Int::set_rawpending_ck(size_t chunkid, bits_t pending) {
    if (chunkid >= NCHUNKS) abort();
    this->m_rawpending[chunkid] |= (pending & mask_of_ck(chunkid));
  }

  inline void AINTC_R_Int::clear_enabled_ck(size_t chunkid, bits_t enabled) {
    if (chunkid >= NCHUNKS) abort();
    this->m_enabled[chunkid] &= ~(enabled & mask_of_ck(chunkid));
  }

  inline void AINTC_R_Int::clear_rawpending_ck(size_t chunkid, bits_t pending) {
    if (chunkid >= NCHUNKS) abort();
    this->m_rawpending[chunkid] &= ~(pending & mask_of_ck(chunkid));
  }

  // ------------------------------------------------------------------
  inline void AINTC_R_Int::set_rawpending(size_t it) {
    if (it >= NINTERRUPTS) abort();
    return set_bit<bits_t>(m_rawpending[segment_ck(it)], offset_ck(it));
  }

  inline void AINTC_R_Int::clear_rawpending(size_t it) {
    if (it >= NINTERRUPTS) abort();
    return unset_bit<bits_t>(m_rawpending[segment_ck(it)], offset_ck(it));
  }

  inline void AINTC_R_Int::set_enabled(size_t it) {
    if (it >= NINTERRUPTS) abort();
    return set_bit<bits_t>(m_enabled[segment_ck(it)], offset_ck(it));
  }

  inline void AINTC_R_Int::clear_enabled(size_t it) {
    if (it >= NINTERRUPTS) abort();
    return unset_bit<bits_t>(m_enabled[segment_ck(it)], offset_ck(it));
  }

  // ------------------------------------------------------------------
  inline bits_t AINTC_R_Int::rawpending_ck(size_t chunkid) const {
    if (chunkid >= NCHUNKS) abort();
    return m_rawpending[chunkid];
  }

  inline bits_t AINTC_R_Int::enabled_ck(size_t chunkid) const {
    if (chunkid >= NCHUNKS) abort();
    return m_enabled[chunkid];
  }

  inline bits_t AINTC_R_Int::pending_ck(size_t chunkid) const {
    if (chunkid >= NCHUNKS) abort();
    return (m_rawpending[chunkid] & m_enabled[chunkid]);
  }

  // ------------------------------------------------------------------
  inline chan_t AINTC_R_Int::get_channel(size_t interrupt) const {
    if (interrupt >= NINTERRUPTS) abort();
    return this->m_channels[interrupt];
  }

  inline void AINTC_R_Int::set_channel(size_t it, chan_t channel) {
    if (it >= NINTERRUPTS) abort();
    this->m_channels[it] = channel;
  }

  inline bits_t AINTC_R_Int::get_channel_gp(size_t intgroup) const {
    if (intgroup >= NINTS_GP) abort();
    return *(bits_t*)(m_channels+4*intgroup);
  }

  inline void AINTC_R_Int::set_channel_gp(size_t intgroup, bits_t value) {
    if (intgroup >= NINTS_GP) abort();
    *(bits_t*)(m_channels+4*intgroup) = value;
  }


  // ------------------------------------------------------------------
  inline AINTC_R_Control::AINTC_R_Control()
    :m_value(0)
  {}

  inline uint32_t AINTC_R_Control::value() const {
    return this->m_value;
  }

  inline bool AINTC_R_Control::holdmode() const {
    return b_HOLD::is_set(m_value);
  }

  inline AINTC_R_Control::nestmode_e AINTC_R_Control::nestmode() const {
    return (nestmode_e) b_NEST::get(m_value);
  }

  inline void AINTC_R_Control::set(uint32_t value) {
    this->m_value = (value &= MASK);
  }

  // ------------------------------------------------------------------
  inline AINTC_R_Serving::AINTC_R_Serving(const AINTC_R_Vector &intvector)
    :m_intvector(intvector)
  {
    memset(m_nesting  , 0, sizeof(m_nesting));
    memset(m_vector   , 0, sizeof(m_nesting));
    memset(m_interrupt, 0, sizeof(m_nesting));
  }

  // ------------------------------------------------------------------
  inline AINTC_R_GlobalEnable::AINTC_R_GlobalEnable()
    :m_enabled(false)
  {}

  inline bool AINTC_R_GlobalEnable::enabled() const {
    return m_enabled;
  }

  inline void AINTC_R_GlobalEnable::set(uint32_t value) {
    m_enabled = value & 0x01;
  }

  inline uint32_t AINTC_R_GlobalEnable::get() const {
    return m_enabled ? 0x01 : 0x00;
  }

  // ------------------------------------------------------------------
  inline AINTC_R_HostInt::AINTC_R_HostInt()
    :m_value(0)
  {}

  inline uint32_t AINTC_R_HostInt::get() const {
    return this->m_value;
  }

  inline void AINTC_R_HostInt::set(uint32_t value) {
    m_value = value & 0x3;
  }

  inline void AINTC_R_HostInt::enabled_set(uint32_t data) {
    size_t offset = (data & 0x01) ? IDX_IRQ : IDX_FIQ;
    set_bit<uint32_t>(m_value, offset);
  }

  inline void AINTC_R_HostInt::enabled_clear(uint32_t data) {
    size_t offset = (data & 0x01) ? IDX_IRQ : IDX_FIQ;
    unset_bit<uint32_t>(m_value, offset);
  }

  inline bool AINTC_R_HostInt::is_enabled(AINTC_idx_interrupts_e id) {
    return is_set<uint32_t>(m_value, (int) id);
  }

  // ------------------------------------------------------------------
  inline AINTC_R_Vector::AINTC_R_Vector()
    :m_base(0)
    ,m_size(0)
    ,m_null(0)
  {}

  inline uint32_t AINTC_R_Vector::base() const {
    return this->m_base;
  }

  inline uint32_t AINTC_R_Vector::size() const {
    return this->m_size;
  }

  inline uint32_t AINTC_R_Vector::null() const {
    return this->m_null;
  }

  inline void AINTC_R_Vector::set_base(uint32_t value) {
    this->m_base = value;
  }

  inline void AINTC_R_Vector::set_size(uint32_t value) {
    this->m_size = value;
  }

  inline void AINTC_R_Vector::set_null(uint32_t value) {
    this->m_null = value;
  }

  inline uint32_t AINTC_R_Vector::branch_for_irq(size_t interrupt) const {
    return m_base + interrupt * m_size;
  }

}
}

// ------------------------------------------------------------------
#undef chan_t
#undef bits_t
