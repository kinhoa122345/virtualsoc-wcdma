//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// template file included from .cpp files (arm_v6 and ppc llvm generators) 
#include "compil_server.hpp"
#include "llvm_gen_parameters.hpp"
#include <cassert>

#ifndef SIMSOC_HAVE_LLVM
#error This file requires LLVM
#endif

namespace simsoc {

  struct LockGuard {
    LockGuard(pthread_mutex_t &mutex): m_mutex(mutex) {pthread_mutex_lock(&mutex);}
    ~LockGuard() {pthread_mutex_unlock(&m_mutex);}
  private:
    pthread_mutex_t &m_mutex;
  };

  template <typename T>
  CompilationQueue<T>::CompilationQueue():
    size(DT3_comp_queue_size.get()),
    candidates(new ARMv6_BasicBlock*[size]),
    index(size-1)
  {
    assert(size>0);
    for (size_t i = 0; i!=size; ++i)
      candidates[i] = NULL;
  }

  template <typename T>
  CompilationQueue<T>::~CompilationQueue() {
    delete[] candidates;
  }

  template <typename T>
  typename T::BasicBlock *CompilationQueue<T>::select_candidate() {
    size_t max = 0;
    T_BasicBlock *bb = NULL;
    for (size_t i = 0; i<size; ++i)
      if (candidates[i]) {
        if (T::get_count(candidates[i])>max) {
          max = T::get_count(candidates[i]);
          bb = candidates[i];
        }
        T::unprotect(candidates[i]);
        candidates[i] = NULL;
      }
    return bb;
  }

  template <typename T>
  void CompilationQueue<T>::add_candidate(typename T::BasicBlock *bb) {
    assert(bb);
    if (candidates[index]) T::unprotect(candidates[index]);
    candidates[index] = bb;
    if (index) --index;
    else index = size-1;
  }

  template <typename T>
  void CompilationQueue<T>::remove_candidate(typename T::BasicBlock *bb) {
    for (size_t i = 0; i<size; ++i)
      if (candidates[i]==bb) {
        candidates[i] = NULL;
        return;
      }
  }

////////////////////////////////////////////////////////////////////////////////

  template <typename T>
  static void *compil_server_wrapper(void *arg) {
    static_cast<CompilationServer<T>*>(arg)->compute();
    return NULL;
  }

  template <typename T>
  CompilationServer<T>::CompilationServer():
    todo_bb(NULL), done_obb(NULL)
  {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_create(&thread, NULL, compil_server_wrapper<T>, this);
  }

  // main boost thread
  template <typename T>
  void CompilationServer<T>::compute() {
    info() <<"start compilation server\n";
    while (true)
      thats_done(T::get().compile(get_task()));
  }

  template <typename T>
  void CompilationServer<T>::do_that(typename T::BasicBlock *bb) {
    // called by the ISS
    LockGuard lg(mutex);
    assert(!done_obb);
    assert(!todo_bb);
    todo_bb = bb;
    pthread_cond_signal(&cond);
  }

  template <typename T>
  typename T::BasicBlock *CompilationServer<T>::get_task() {
    // call by the compilation server
    LockGuard lg(mutex);
    while (!todo_bb) {
      info() <<"compilation server: wait request\n";
      pthread_cond_wait(&cond,&mutex);
    }
    assert(!done_obb);
    assert(todo_bb->being_compiled);
    info() <<"compilation server: request received\n";
    return todo_bb;
  }

  template <typename T>
  void CompilationServer<T>::thats_done(typename T::OptimizedBasicBlock *obb) {
    // call by the compilation server
    LockGuard lg(mutex);
    assert(!done_obb);
    assert(todo_bb);
    todo_bb = NULL;
    done_obb = obb;
    info() <<"compilation server: deliver result\n";
  }

  template <typename T>
  typename T::OptimizedBasicBlock *CompilationServer<T>::get_result() {
    // called by the ISS
    LockGuard lg(mutex);
    if (done_obb) {
      T_OptimizedBasicBlock *obb = done_obb;
      done_obb = NULL;
      assert(!todo_bb);
      return obb;
    } else
      return NULL;
  }

} // namespace simsoc
