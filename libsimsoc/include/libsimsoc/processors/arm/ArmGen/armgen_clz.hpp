//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARMGEN_CLZ_HPP
#define ARMGEN_CLZ_HPP

#include "armgen.hpp"


class CLZ_Generator : public ARM_Generator {
public:
  void generate();
protected:

  void generate_clz_func_table (const std::string table_name,
                                const std::string prefix);

  void generate_clz_instruction(const std::string func_name,
                                const ConditionCode cond);
};


#endif
