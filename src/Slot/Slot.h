#ifndef SLOT_H
#define SLOT_H

#include <iostream>
#include <string>
#include <vector>

#include "../Random/Random.h"
#include "../Entity/Entity.h"
#include "../Direction/Direction.h"

using namespace std;

class Slot
{
private:
  string id;
  vector<Entity *> entities;
  vector<Direction> directions;

public:
  Slot(string $id, vector<Direction> $direction);
  ~Slot();

  const string &getId();

  Entity *getFirstEntity();

  void deleteFirstEntity();

  void fight();

  unsigned entityCount();

  const Direction &getRandomDirection();

  void addEntity(Entity *other);

  void operator+=(Entity *other);
};

#endif // !SLOT_H
