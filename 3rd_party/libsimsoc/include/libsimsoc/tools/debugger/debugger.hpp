//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef LIBSIMSOC_TOOLS_DEBUGGER_HPP__
# define LIBSIMSOC_TOOLS_DEBUGGER_HPP__

#include <libsimsoc/simsoc-config.h>
#include <libsimsoc/interfaces/gdb.hpp>
#include <libsimsoc/module.hpp>

#include <inttypes.h>

namespace simsoc {

  class GdbClient;

  class Debugger {
  public:
#if defined(SIMSOC_DEBUG_GDB_PROTOCOL)
    Debugger(DebugInterface &dbgi, Module *logto);
#else
    Debugger(DebugInterface &dbgi);
#endif
    virtual ~Debugger ();

  public:
    enum events_e {
      EV_TRAP = 0x01,
    };

  public:
    // Must be called at start of simulation.
    // Function returns when gdb client is connected.
    void start();

    // Must be called at end of simulation.
    // Function forces gdb client disconnection
    void stop();

    // This method must be called by processor on each CPU cycle.
    // It implements the minimal GDB _synchronous_ protocol.
    void cycle();

    // Async notification.
    void notify(enum events_e event);

    // Is debugger connected to a client ?
    bool active() { return m_client != NULL; }

  protected:
    void _reset();
    void _client_interaction();

  protected:
    DebugInterface &m_dbgi;
    GdbClient      *m_client;
    uint32_t        m_events;
    int             m_remaining;
    bool            m_initialize;
#if defined(SIMSOC_DEBUG_GDB_PROTOCOL)
    Module         *m_logto;
#endif

  private:
    Debugger(const Debugger&);            // GNI
    Debugger& operator=(const Debugger&); // GNI
  };

}

#endif // !LIBSIMSOC_TOOLS_DEBUGGER_HPP__
