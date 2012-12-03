#include "Random.hh"

namespace Core
{
  namespace Random
  {
    unsigned int rand()
    {
      static mersenne_twister distribution;
      return distribution();
    }
  } // Random
} // Core
