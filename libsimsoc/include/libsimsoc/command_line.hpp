//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef COMMAND_LINE_HPP
#define COMMAND_LINE_HPP

#include "display.hpp"

#include <inttypes.h>
#include <cassert>

#include <deque>
#include <vector>
#include <string>
#include <map>

namespace simsoc {

  struct ParameterAbstract: Printable {
    virtual void set(const char *arg) = 0;
    virtual std::ostream &display(std::ostream &os) const = 0;
    virtual void print_usage(std::ostream &os) const = 0;
    virtual bool is_set() const = 0;

    ParameterAbstract(const char *k, const char *nm, const char *msg);
    const char *kind;
    const char *name;
    const char *message;

    bool operator<(const ParameterAbstract &pa) const;
  };

  struct ParameterStrQueue: ParameterAbstract {
    ParameterStrQueue(const char *kind, const char *name, const char *message);
    void set(const char *arg);
    std::ostream &display(std::ostream &os) const;
    void print_usage(std::ostream &os) const;
    bool is_set() const {return !values.empty();}
    const char *front() const;
    void pop_front();
  private:
    std::deque<const char *> values;
  };

  struct ParameterUintQueue: ParameterAbstract {
    ParameterUintQueue(const char *kind, const char *name,
                       const char *message, uint64_t default_value);
    void set(const char *arg);
    std::ostream &display(std::ostream &os) const;
    void print_usage(std::ostream &os) const;
    bool is_set() const {return !values.empty();}
    uint64_t front() const;
    void pop_front();
  private:
    std::deque<uint64_t> values;
    const uint64_t default_;
  };

  struct ParameterInt: ParameterAbstract {
    ParameterInt(const char *kind, const char *name, const char *message, int def);
    void set(const char *arg);
    std::ostream &display(std::ostream &os) const;
    void print_usage(std::ostream &os) const;
    bool is_set() const {return true;}
    inline int get() const {return value;}
  private:
    int value;
  };

  struct ParameterBool: ParameterAbstract {
    ParameterBool(const char *kind, const char *name, const char *message);
    void set(const char *arg);
    std::ostream &display(std::ostream &os) const;
    void print_usage(std::ostream &os) const;
    bool is_set() const {return value;}
    inline bool get() const {return value;}
  private:
    bool value;
  };

  struct ParameterEnum: ParameterAbstract {
    ParameterEnum(const char *kind, const char *name, const char *message,
                  const char **choices, size_t choice_count, size_t default_);
    void set(const char *arg);
    std::ostream &display(std::ostream &os) const;
    void print_usage(std::ostream &os) const;
    bool is_set() const {return true;}
    inline size_t get() const {return value;}
  private:
    const char **choices;
    const size_t choice_count;
    size_t value;
  };

  struct ParameterEnumQueue: ParameterAbstract {
    ParameterEnumQueue(const char *kind, const char *name, const char *message,
                       const char **choices, size_t choice_count, size_t default_);
    void set(const char *arg);
    std::ostream &display(std::ostream &os) const;
    void print_usage(std::ostream &os) const;
    bool is_set() const {return !values.empty();}
    size_t front() const;
    void pop_front();
  private:
    const char **choices;
    const size_t choice_count;
    std::deque<size_t> values;
    const size_t default_;
  };

  struct eX_line {
    typedef std::map<std::string, std::string> args_map_t;

    std::string name;
    args_map_t arguments;

    static bool parse(const std::string &input, struct eX_line &output);
  };

} // namespace simsoc

#endif // COMMAND_LINE_HPP
