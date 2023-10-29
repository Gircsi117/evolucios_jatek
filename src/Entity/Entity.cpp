#include <iostream>
#include <string>
#include <vector>

#include "../Random/Random.h"
#include "../Direction/Direction.h"
#include "Entity.h"

using namespace std;

Entity::Entity()
{
  this->name = "Entity";
  this->damage = Random::randomInt(25, 75);
  this->limit = 100;
  this->level = 1;
  this->lastMove = Direction::NONE;
}

Entity::Entity(string name)
{
  this->name = name;
  this->damage = Random::randomInt(25, 75);
  this->limit = 100;
  this->level = 1;
  this->lastMove = Direction::NONE;
}

Entity::Entity(string name, unsigned damage, unsigned limit, unsigned level)
{
  this->name = name;
  this->damage = damage;
  this->limit = limit;
  this->level = level;
  this->lastMove = Direction::NONE;
}

Entity::~Entity()
{
}

string Entity::getName()
{
  return this->name;
}

unsigned Entity::getDamage()
{
  return this->damage;
}

void Entity::addDamage(unsigned damage)
{
  this->damage += damage;
}

unsigned Entity::getLevel()
{
  return this->level;
}

void Entity::levelUp()
{
  // Szintlépés ha elérte a limit damage-t
  if (this->damage >= this->limit)
  {
    this->level++;
    this->limit += 100;
  }
}

void Entity::operator+=(Entity *other)
{
  this->addDamage((*other).getDamage());
}

bool Entity::operator<(const Entity &other)
{
  // A legnagyobb szintű nyer
  if (this->level < other.level)
  {
    return true;
  }
  // Azonos szintűek esetén az erősebb nyer
  else if (this->level == other.level && this->damage < other.damage)
  {
    return true;
  }
  return false;
}