#include <iostream>
#include <random>
#include <cstdlib>
#include <chrono>

#include "Random.h"

// A jelenlegi időhöz igazítja a random szám generálást
void Random::resetRand()
{
  unsigned seed = time(0);
  srand(seed);
}

// Visszaadja egy random számot [min, max] intervallumban
unsigned Random::randomInt(int min, int max)
{
  return rand() % (max - min + 1) + min;
}