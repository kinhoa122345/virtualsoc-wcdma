//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined (LIBSIMSOC_RANDOM_HPP)
# define LIBSIMSOC_RANDOM_HPP

namespace simsoc {

  class Random {
  private:
    Random(); // non-instantiable class

  public:
    static void seed();
    static void seed(unsigned int seed);

    static long int random(long int max = -1);
  };

}

#endif // !LIBSIMSOC_RANDOM_HPP
