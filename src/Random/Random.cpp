#include <iostream>
#include <random>
#include <cstdlib>
#include <chrono>

#include "Random.h"

void Random::resetRand()
{
  unsigned seed = time(0);
  srand(seed);
}

unsigned Random::randomInt(int min, int max)
{
  return rand() % (max - min + 1) + min;
}