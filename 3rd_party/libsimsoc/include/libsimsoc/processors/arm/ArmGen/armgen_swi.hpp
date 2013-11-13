//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARMGEN_SWI_HPP
#define ARMGEN_SWI_HPP

#include "armgen.hpp"

class SWI_Generator: public ARM_Generator {
public:
  void generate();
protected:

  void generate_swi_func_table(const std::string table_name,
                               const std::string prefix);

  void generate_swi_instruction(const std::string func_table,
                                const ConditionCode cond);
};

#endif
