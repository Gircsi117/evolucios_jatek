#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <chrono>

#include "./src/Random/Random.h"
#include "./src/Entity/Entity.h"
#include "./src/Slot/Slot.h"

using namespace std;

int main(int argc, const char **argv)
{
  Random::resetRand();
  string input = "";

  Slot slot;

  slot += new Entity("a", 28);
  slot += new Entity("b", 43);
  slot += new Entity("c", 39);
  slot += new Entity("d", 16);
  slot += new Entity("e", 27);

  slot.fight();

  return 0;
}