//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ISC_HPP
#define ISC_HPP

#include <string>
#include <vector>
#include <iostream>
#include <inttypes.h>

class ICoding {
public:
  typedef enum {ZERO, ONE, UNDEF} bit_value;

  ICoding(const std::string b, const std::string c, unsigned ln);
  ICoding(const ICoding& i, unsigned num);

  unsigned nb_bits() const;
  unsigned total_nb_bits() const;
  bit_value get(unsigned n) const;
  void gencode(const char * filename, std::ostream &os=std::cout) const;
  std::ostream& display(std::ostream &os) const;
  bool is_undef() const;
  bool operator<(const ICoding& b) const;

protected:
  void gencode_param(std::ostream &os, char name, unsigned start, unsigned length) const;

  static const char unused[];
  unsigned line_number;
  std::string bits;
  std::string c_code;
  std::vector<bit_value> pattern;
};
std::ostream& operator<<(std::ostream &os, const ICoding& i);

class Isc {
public:
  Isc(unsigned nb_bits, const char * filename);
  Isc(const Isc& old, unsigned num, ICoding::bit_value is_not);
  Isc(const Isc& old); // remove first ICoding
  unsigned nb_bits() const;
  unsigned total_nb_bits() const;
  void add(const std::string& bits, const std::string& c_code, unsigned line_number);
  void add(const ICoding& i, unsigned num);
  void gencode(std::ostream &os=std::cout);

protected:
  void gencode_split(std::ostream &os, unsigned i);
  void gencode_first(std::ostream &os=std::cout);
  void update_uzo();
  void print_uzo(std::ostream &os=std::cout);
  void print_pattern(uint64_t maks, uint64_t value, std::ostream &os);

  const char * isc_file;
  unsigned nbits;
  std::vector<ICoding> icodings;
  std::vector<unsigned> undefs;
  std::vector<unsigned> zeros;
  std::vector<unsigned> ones;
  std::vector<unsigned> real_nums;
  uint64_t seen_mask;
  uint64_t seen_value;
};

#endif //ISC_HPP
