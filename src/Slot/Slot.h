#ifndef SLOT_H
#define SLOT_H

#include <iostream>
#include <string>
#include <vector>

#include "../Random/Random.h"
#include "../Entity/Entity.h"

using namespace std;

class Slot
{
private:
  vector<Entity *> entities;

public:
  Slot();
  ~Slot();

  void fight();

  unsigned entityCount();

  void operator+=(Entity *other);
};

#endif // !SLOT_H
