#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>
#include <vector>

#include "../Random/Random.h"
#include "../Direction/Direction.h"

using namespace std;

class Entity
{
private:
  string name;
  unsigned damage;
  unsigned limit;
  unsigned level;
  unsigned roundMove;
  Direction lastMove;

public:
  Entity();
  Entity(string name);
  Entity(string name, unsigned damage, unsigned limit = 100, unsigned level = 1);
  ~Entity();

  string getName();

  void getStats();

  unsigned getRoundMove();

  void setRoundMove(const unsigned &roundMove);

  unsigned getDamage();
  void addDamage(unsigned damage);

  unsigned getLevel();

  string levelUp();

  void operator+=(Entity *other);

  bool operator<(const Entity &other);
};

#endif