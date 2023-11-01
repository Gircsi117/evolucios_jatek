#include <iostream>
#include <string>
#include <vector>

#include "../Random/Random.h"
#include "../Direction/Direction.h"
#include "../History/History.h"
#include "Entity.h"

using namespace std;

Entity::Entity()
{
  this->name = "Entity";
  this->damage = Random::randomInt(25, 50);
  this->limit = 100;
  this->level = 1;
  this->roundMove = 0;
  this->lastMove = Direction::NONE;
}

Entity::Entity(string name)
{
  this->name = name;
  this->damage = Random::randomInt(25, 50);
  this->limit = 100;
  this->level = 1;
  this->roundMove = 0;
  this->lastMove = Direction::NONE;
}

Entity::Entity(string name, unsigned damage, unsigned limit, unsigned level)
{
  this->name = name;
  this->damage = damage;
  this->limit = limit;
  this->level = level;
  this->roundMove = 0;
  this->lastMove = Direction::NONE;
}

Entity::~Entity()
{
}

string Entity::getName()
{
  return this->name;
}

unsigned Entity::getRoundMove()
{
  return this->roundMove;
}

void Entity::setRoundMove(const unsigned &roundMove)
{
  this->roundMove = roundMove;
}

void Entity::getStats()
{
  cout << "Name: " << this->name << endl;
  cout << "Damage: " << to_string(this->damage) << endl;
  cout << "Limit: " << to_string(this->limit) << endl;
  cout << "Level: " << to_string(this->level) << endl;
  cout << "---------------------------------------------------" << endl;
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
    this->damage = Random::randomInt(25, 50);
    History::writeHistory(this->getName() + " a(z) " + to_string(this->level) + ". szintre lépett!");
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