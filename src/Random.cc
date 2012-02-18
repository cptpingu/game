#include "Random.hh"

namespace Random
{
  unsigned int rand()
  {
    static mersenne_twister distribution;
    return distribution();
  }
}
