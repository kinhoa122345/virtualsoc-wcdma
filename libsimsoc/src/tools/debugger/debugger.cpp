//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "debugger.hpp"
#include "libsimsoc/network/socket-inet4.hpp"
#include "libsimsoc/io.hpp"

#include <cstring>
#include <cctype>

#include <algorithm>
#include <limits>
#include <climits>
#include <stdexcept>

#include <sstream>
#include <iomanip>

#include <netinet/tcp.h>

#define GDB_MAX_READ (1 << 24)

namespace simsoc {

  // ------------------------------------------------------------------
  enum command_e {
    CMD_BREAK    ,
    CMD_READREGS ,
    CMD_READREG  ,
    CMD_READMEM  ,
    CMD_CONTINUE ,
    CMD_LASTSIG  ,
    CMD_UNKNOWN  ,
  };

  enum bkkind_e {
    BK_SOFT     = 0x00,
    BK_HARD     = 0x01,
    BK_RD_WATCH = 0x02,
    BK_WR_WATCH = 0x03,
    BK_AC_WATCH = 0x04,
  };

  struct cmd_breakpoint {
    bkkind_e kind   ;
    uint64_t address;
    uint64_t length ;
    bool     remove ;
  };

  struct cmd_memread {
    uint64_t address;
    size_t   length ;
  };

  struct cmd_continue {
    uint64_t address ;
    bool     fromaddr;
    bool     step    ;
  };

  // ------------------------------------------------------------------
  class GdbPacket {
  public:
    GdbPacket()
      :m_command(CMD_UNKNOWN)
    {}

  public:                       // Getters
    command_e command() const { return m_command; }

    const cmd_breakpoint& as_A_BREAK() const {
      if (m_command != CMD_BREAK)
        abort();
      return m_breakpt;
    }

    const cmd_memread& as_A_READ_MEM() const {
      if (m_command != CMD_READMEM)
        abort();
      return m_memread;
    }

    const cmd_continue& as_A_CONTINUE() const {
      if (m_command != CMD_CONTINUE)
        abort();
      return m_continue;
    }

    const size_t as_A_READ_REG() const {
      if (m_command != CMD_READREG)
        abort();
      return m_regread;
    }

  public:                       // Setters
    void set_A_UNKNOWN() {
      m_command = CMD_UNKNOWN;
    }

    void set_A_READ_REGS() {
      m_command = CMD_READREGS;
    }

    void set_A_READ_REG(size_t reg_num) {
      m_command = CMD_READREG;
      m_regread = reg_num;
    }

    void set_A_READ_MEM(uint64_t address, size_t length) {
      m_command = CMD_READMEM;
      m_memread.address = address;
      m_memread.length  = length ;
    }

    void set_A_BREAK(const cmd_breakpoint &data) {
      m_command = CMD_BREAK;
      m_breakpt = data;
    }

    void set_A_CONTINUE(bool step) {
      m_command = CMD_CONTINUE;
      m_continue.address  = 0;
      m_continue.fromaddr = false;
      m_continue.step     = step;
    }

    void set_A_CONTINUE(bool step, uint64_t address) {
      m_command = CMD_CONTINUE;
      m_continue.address  = address;
      m_continue.fromaddr = true;
      m_continue.step     = step;
    }

    void set_A_LASTSIG() {
      m_command = CMD_LASTSIG;
    }

  protected:
    command_e m_command;

    union {
      cmd_breakpoint m_breakpt ;
      cmd_memread    m_memread ;
      cmd_continue   m_continue;
      size_t m_regread;
    };
  };

  // ------------------------------------------------------------------
  uint8_t crc(const uint8_t *data, size_t size) {
    uint8_t result = 0x00;

    while (size-- != 0)
      result += *data++;
    return result;
  }

  // ------------------------------------------------------------------
  char hextochar(uint8_t byte) {
    static const char *HEXCHARS = "0123456789abcdef";
    return HEXCHARS[byte & 0xF];
  }

  int hexofchar(char byte) {
    if (!isxdigit(byte))
      return -1;
    return isdigit(byte) ? (byte - '0') : (tolower(byte) - 'a' + 10);
  }

  bool hexs(const uint8_t *input, int separator, std::vector<uint64_t> &out) {
    uint8_t *endptr;

    while (*input != '\0') {
      uint64_t value = 0;
      int      cvalue;

      if (!isxdigit(*input))
        return false;
      while ((cvalue = hexofchar(*input++)) != -1)
        value = 16 * value + cvalue;
      if (*(--input) == separator)
        ++input;
      out.push_back(value);
    }

    return true;
  }

  // ------------------------------------------------------------------
  class GdbOutput {
  public:
    typedef std::vector<uint8_t> bytes_t;

    const bytes_t& raw() const { return m_buffer; }

  public:
    GdbOutput() {
      this->clear();
    }

  public:
    void clear() {
      this->m_buffer.resize(1);
      this->m_buffer[0] = '$';
    }

    void finalize() {
      if (m_buffer.size() < 1 || m_buffer[0] != '$')
        abort();

      uint8_t thecrc = crc(&m_buffer[1], m_buffer.size() - 1);
      this->push('#');
      this->push_M(&thecrc, 1);
    }

    void push(uint8_t byte) {
      this->m_buffer.push_back(byte);
    }

    void push(const std::string &data) {
      if (data.size() > (m_buffer.max_size() - m_buffer.size()))
        throw std::bad_alloc();

      size_t position = this->m_buffer.size();

      m_buffer.resize(m_buffer.size() + data.size());
      memcpy(&m_buffer[position], data.c_str(), data.size());
    }

    void push_M(const uint8_t *data, size_t size) {
      if (size > (m_buffer.max_size() - m_buffer.size()) / 2)
        throw std::bad_alloc();

      size_t position = this->m_buffer.size();

      m_buffer.resize(m_buffer.size() + 2*size);
      while (size-- != 0) {
        m_buffer[position++] = hextochar((*data >> 4) & 0x0F);
        m_buffer[position++] = hextochar((*data >> 0) & 0x0F);
        ++data;
      }
    }

  private:
    bytes_t m_buffer;
  };

  // ------------------------------------------------------------------
  class GdbInput {
  public:
    static bool check_crc(uint8_t crc, uint8_t *rawcrc);

  public:
    GdbInput(SocketIPV4 &socket);
    virtual ~GdbInput();

  public:
    typedef std::vector<uint8_t> bytes_t;

    const GdbPacket& packet() const { return m_packet; }
    const bytes_t& rawcommand() const { return m_command; }

    bool read();

  protected:
    void _decode_packet();

  private:
    InBuffer *m_buffer;
    bytes_t   m_command;
    GdbPacket m_packet;
  };

  GdbInput::GdbInput(SocketIPV4 &socket)
    :m_buffer(0)
  {
    this->m_buffer = new Socket_InBuffer<socket_IPV4>(socket);
  }

  GdbInput::~GdbInput() {
    if (this->m_buffer)
      delete this->m_buffer;
  }

  bool GdbInput::check_crc(uint8_t crc, uint8_t *rawcrc) {
    int hex1 = hexofchar(rawcrc[0]);
    int hex2 = hexofchar(rawcrc[1]);

    if (hex1 < 0 || hex2 < 0)
      return false;
    return ((uint8_t) (hex1 << 4 | hex2)) == crc;
  }

  bool GdbInput::read() {
    uint8_t byte;
    uint8_t crc = 0x00;
    uint8_t rawcrc[2];

    m_command.clear();

    while (m_buffer->getc() != '$') {}

    while ((byte = m_buffer->getc()) != '#') {
      crc += byte;
      m_command.push_back(byte);
    }

    m_buffer->read(&rawcrc[0], sizeof(rawcrc));

    if (!this->check_crc(crc, rawcrc))
      return false;

    this->_decode_packet(); return true;
  }

  void GdbInput::_decode_packet() {
    m_packet.set_A_UNKNOWN();

    if (m_command.size() == 0)
      return ;

    m_command.push_back('\0');   // \0-terminated

    const uint8_t *arg_start = &m_command[1];

    uint8_t action;

    switch ((action = m_command[0])) {
    case '?':
      m_packet.set_A_LASTSIG();
      break ;

    case 'g':                   // Read all registers
      if (arg_start[0] == '\0')
        m_packet.set_A_READ_REGS();
      break ;

    case 'p':{
      std::vector<uint64_t> args;
      if (hexs(arg_start, ',', /*out*/ args) && args.size() == 1)
        m_packet.set_A_READ_REG(args[0]);
      break;
    }

    case 'm': {                            // Read memory
      std::vector<uint64_t> args;
      if (hexs(arg_start, ',', /*out*/ args) && args.size() == 2)
        m_packet.set_A_READ_MEM(args[0], args[1]);
      break ;
    }

    case 's':                   // Step
    case 'c': {                 // Continue
      const bool step = (action == 's');
      std::vector<uint64_t> args;

      if (hexs(arg_start, ',', /*out*/ args) && args.size() < 2) {
        if (args.size() == 1)
          m_packet.set_A_CONTINUE(step, args[0]);
        else
          m_packet.set_A_CONTINUE(step);
      }
      break ;
    }

    case 'z':                   // Remove BKPT
    case 'Z': {                 // Add BKPT
      std::vector<uint64_t> args;

      if (hexs(arg_start, ',', /*out*/ args) && args.size() == 3) {
        cmd_breakpoint data;

        if (args[2] > UINT_MAX)
          args[2] = UINT_MAX;

        data.kind    = (bkkind_e) args[0];
        data.address = args[1];
        data.length  = args[2];
        data.remove  = (action == 'z');

        m_packet.set_A_BREAK(data);
      }
      break ;
    }
    }
  }

  // ------------------------------------------------------------------
  class GdbClient {
  public:
    static const uint8_t SIG_TRAP = 0x05;

  public:
#if defined(SIMSOC_DEBUG_GDB_PROTOCOL)
    GdbClient(SocketIPV4 *socket, Module *logto)
#else
    GdbClient(SocketIPV4 *socket)
#endif
      :m_socket(socket)
      ,m_receive(*socket)
#if defined(SIMSOC_DEBUG_GDB_PROTOCOL)
      ,m_logto(logto)
#endif
    {
      socket->setsockopt(IPPROTO_TCP, TCP_NODELAY, true);
    }

    virtual ~GdbClient() {
      delete m_socket;
    }

  public:
    bool read() {
      const bool recvok = m_receive.read();

#if defined(SIMSOC_DEBUG_GDB_PROTOCOL)
      if (m_logto != NULL) {
        std::stringstream display;

        const bytes_t &command = m_receive.rawcommand();

        for (size_t i = 0; i < command.size(); ++i) {
          if (isprint(command[i]))
            display << (char) command[i];
          else
            display << std::setw(2) << std::hex << (unsigned) command[i];
        }

        m_logto->info() << "GDB: RECV: " << display.str() << std::endl;
      }
#endif

      return recvok;
    }

    const GdbPacket& packet() const { return m_receive.packet(); }

  public:                       // Answers
    void ack(bool success) {
      this->_send((uint8_t*) (success ? "+" : "-"), 1);
    }

    void signal(uint8_t signal) {
      this->m_send.clear();
      this->m_send.push("S");
      this->m_send.push_M(&signal, 1);
      this->m_send.finalize();
      this->_send_prepared();
    }

    void unsupported() {
      this->m_send.clear();
      this->m_send.finalize();
      this->_send_prepared();
    }

    void failure() {
      this->m_send.clear();
      this->m_send.push("E01");
      this->m_send.finalize();
      this->_send_prepared();
    }

    void success() {
      this->m_send.clear();
      this->m_send.push("OK");
      this->m_send.finalize();
      this->_send_prepared();
    }

    void binary(const uint8_t *data, size_t size) {
      this->m_send.clear();
      this->m_send.push_M(data, size);
      this->m_send.finalize();
      this->_send_prepared();
    }

  protected:
    void _send(const uint8_t *data, size_t length) {
#if defined(SIMSOC_DEBUG_GDB_PROTOCOL)
      if (m_logto != NULL) {
        std::stringstream display;

        const bytes_t &command = m_receive.rawcommand();

        for (size_t i = 0; i < length; ++i) {
          if (isprint(data[i]))
            display << (char) data[i];
          else
            display << std::setw(2) << std::hex << (unsigned) data[i];
        }

        m_logto->info() << "GDB: SEND: " << display.str() << std::endl;
      }
#endif
      m_socket->send(data, length);
    }

    void _send_prepared() {
      const bytes_t &raw = m_send.raw();

      this->_send(raw.data(), raw.size());
      m_send.clear();
    }

  protected:
    typedef std::vector<uint8_t> bytes_t;

    SocketIPV4 *m_socket;
    GdbInput    m_receive;
    GdbOutput   m_send;
#if defined(SIMSOC_DEBUG_GDB_PROTOCOL)
    Module     *m_logto;
#endif
  };

  // ------------------------------------------------------------------
#if defined(SIMSOC_DEBUG_GDB_PROTOCOL)
  Debugger::Debugger(DebugInterface &dbgi, Module *logto)
#else
  Debugger::Debugger(DebugInterface &dbgi)
#endif
    :m_dbgi(dbgi)
    ,m_client(NULL)
    ,m_events(0)
    ,m_remaining(-1)
    ,m_initialize(true)
#if defined(SIMSOC_DEBUG_GDB_PROTOCOL)
    ,m_logto(logto)
#endif
  {}

  // ------------------------------------------------------------------
  Debugger::~Debugger() {
    if (m_client)
      delete m_client;
  }

  // ------------------------------------------------------------------
  void Debugger::start() {
    if (m_client != NULL) abort();

    SocketIPV4 server(SocketIPV4::IPV4_STREAM);

    server.setsockopt(SOL_SOCKET, SO_REUSEADDR, true);
    server.bind(SocketIPV4::ANY, 7000);
    server.listen();

#if defined(SIMSOC_DEBUG_GDB_PROTOCOL)
    m_client = new GdbClient(server.accept(), m_logto);
#else
    m_client = new GdbClient(server.accept());
#endif

    server.close();
  }

  // ------------------------------------------------------------------
  void Debugger::stop() {
    if (m_client)
      delete m_client;
    m_client = NULL;
  }

  // ------------------------------------------------------------------
  void Debugger::notify(enum events_e event) {
    this->m_events |= (uint32_t) event;
  }

  // ------------------------------------------------------------------
  void Debugger::cycle() {
    if (m_client == NULL)
      return ;

    if (m_remaining > 0)
      --m_remaining;

    if (m_initialize) {
      try {
        this->_client_interaction();
      } catch (...) {
        this->_reset(); return ;
      }

      m_initialize = false;
    } else {
      if ((m_events & EV_TRAP) || m_remaining == 0) {
        m_remaining  = -1;
        m_events    &= ~((uint32_t) EV_TRAP);

        m_dbgi.disable_traps();
        m_client->signal(GdbClient::SIG_TRAP);

        try {
          this->_client_interaction();
        } catch (...) {
          this->_reset(); return ;
        }

        m_dbgi.enable_traps();
      }
    }
  }

  // ------------------------------------------------------------------
  void Debugger::_reset() {
    if (m_client != NULL) {
      delete m_client; m_client = NULL;
    }
    m_initialize = true;
    m_events     = 0;
    m_remaining  = -1;
  }

  // ------------------------------------------------------------------
  void Debugger::_client_interaction() {
    while (true) {
      if (!m_client->read()) {
        m_client->ack(false);
        continue ;
      }

      m_client->ack(true);

      const GdbPacket &packet = m_client->packet();

      switch (packet.command()) {
      case CMD_BREAK: {
        const cmd_breakpoint &data = packet.as_A_BREAK();

        if (data.kind != BK_SOFT)
          m_client->failure();
        else {
          bool success;

          if (data.remove)
            success = m_dbgi.del_breakpoint(data.address, data.length);
          else
            success = m_dbgi.add_breakpoint(data.address, data.length);
          if (success)
            m_client->success();
          else
            m_client->failure();
        }
        break ;
      }

      case CMD_READMEM: {
        const cmd_memread &data = packet.as_A_READ_MEM();
        std::vector<uint8_t> bytes;

        size_t length = data.length;

        if (length > GDB_MAX_READ)
          length = GDB_MAX_READ;

        bytes.reserve(data.length);
        if (!m_dbgi.read(data.address, data.length, /*out*/ bytes))
          m_client->failure();
        else {
          m_client->binary(bytes.data(), bytes.size());
        }
        break ;
      }

      case CMD_READREGS: {
        std::vector<uint8_t> bytes;

        if (!m_dbgi.readregs(/*out*/ bytes))
          m_client->failure();
        else {
          m_client->binary(bytes.data(), bytes.size());
        }
        break ;
      }

      case CMD_READREG: {
        std::vector<uint8_t> bytes;

        if (!m_dbgi.readreg(packet.as_A_READ_REG(),/*out*/ bytes))
          m_client->failure();
        else {
          m_client->binary(bytes.data(), bytes.size());
        }
        break ;
      }

      case CMD_CONTINUE:
        if (packet.as_A_CONTINUE().step)
          m_remaining = 1;
        return ;

      case CMD_LASTSIG:
        m_client->signal(GdbClient::SIG_TRAP);
        continue ;

      case CMD_UNKNOWN:
        m_client->unsupported();
        continue ;
      }
    }
  }

}
