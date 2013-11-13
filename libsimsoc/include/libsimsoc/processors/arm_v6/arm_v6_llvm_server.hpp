//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef ARM_V6_LLVM_SERVER_HPP
#define ARM_V6_LLVM_SERVER_HPP

#include <libsimsoc/processors/compil_server.hpp>
#include "arm_v6_llvm_generator.hpp"
#include "arm_v6_dyntrans.hpp"
#include <libsimsoc/simsoc-config.h>

#ifndef SIMSOC_HAVE_LLVM
#error This file requires LLVM
#endif

namespace simsoc {

  struct ARMv6_DT3 {
    typedef ARMv6_BasicBlock BasicBlock;
    typedef ARMv6_OptimizedBasicBlock OptimizedBasicBlock;
    static size_t get_count(const BasicBlock *bb) {return bb->count;}
    static void unprotect(BasicBlock *bb) {bb->inside_comp_queue = false;}
    static inline ARMv6_LLVM_Generator &get() {return ARMv6_LLVM_Generator::get();}
  };

  class ARMv6_LLVM_Server {
    ARMv6_LLVM_Server();
    static ARMv6_LLVM_Server *singleton;
  public:
    static ARMv6_LLVM_Server &get();

  public:
    // insert a block into the compilation queue when some threshold is reached
    void add_candidate(ARMv6_BasicBlock *bb);
    void remove_candidate(ARMv6_BasicBlock *bb);

    // get done work from server and provide new, if any
    void synchronize();

  protected:
    CompilationQueue<ARMv6_DT3> comp_queue;
    CompilationServer<ARMv6_DT3> comp_server;
    bool server_busy;
  };

}

#endif // ARM_V6_LLVM_SERVER_HPP
