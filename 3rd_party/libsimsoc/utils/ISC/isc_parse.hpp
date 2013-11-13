//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PARSE_HPP
#define PARSE_HPP

#include "isc.hpp"

Isc * isc_parse(std::istream& is, std::ostream& os, const char * filename);
void isc_epilogue(std::istream& is, std::ostream& os);

#endif //PARSE_HPP
