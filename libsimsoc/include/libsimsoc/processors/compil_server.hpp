//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef COMPIL_SERVER_HPP
#define COMPIL_SERVER_HPP

#include <simsoc-config.h>
#include <pthread.h>

#ifndef SIMSOC_HAVE_LLVM
#error This file requires LLVM
#endif

namespace simsoc {
  
#if 0 // scheme of a compliant T type
  struct T {
    typedef ... BasicBlock;
    typedef ... OptimziedBasicBlock;
    static size_t get_count(const BasicBlock *bb) {return bb->count;}
    static void unprotect(BasicBlock *bb) {bb->inside_comp_queue = false;}
    static LLVM_GEN &get();
  };

  struct LLVM_GEN {
    T::OptimziedBasicBlock *compile(const T::BasicBlock*);
  };
#endif // end of comment

  template <typename T>
  struct CompilationQueue {
    typedef typename T::BasicBlock T_BasicBlock;
    CompilationQueue();
    ~CompilationQueue();
    T_BasicBlock *select_candidate();
    void add_candidate(T_BasicBlock *bb);
    void remove_candidate(T_BasicBlock *bb);
  private:
    const size_t size;
    T_BasicBlock **candidates;
    size_t index;
  };

  template <typename T>
  struct CompilationServer {
    typedef typename T::BasicBlock T_BasicBlock;
    typedef typename T::OptimizedBasicBlock T_OptimizedBasicBlock;
    CompilationServer(); // constructor
    void compute(); // main (boost) thread
    void do_that(T_BasicBlock *bb); // called by the ISS
    T_BasicBlock *get_task(); // call by the compilation server
    void thats_done(T_OptimizedBasicBlock *obb); // call by the compilation server
    T_OptimizedBasicBlock *get_result(); // called by the ISS
  private:
    T_BasicBlock *todo_bb;
    T_OptimizedBasicBlock *done_obb;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    pthread_t thread;
  };

} // namespace simsoc

#endif // COMPIL_SERVER_HPP
