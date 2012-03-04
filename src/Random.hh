#ifndef RANDOM_HH_
# define RANDOM_HH_

# include <random>

namespace Random
{
# ifdef _WIN32
  typedef std::mersenne_twister<unsigned int, 32, 624,
          397, 31, 0x9908b0df, 11, 7, 0x9d2c5680,
          15, 0xefc60000, 18> mersenne_twister;
# else
  typedef std::mt19937 mersenne_twister;
# endif

  /*!
  ** Get a random number using a mersenne twister algorithm.
  **
  ** @return A randum number.
  */
  unsigned int rand();
} // Random

#endif /* !RANDOM_HH */
