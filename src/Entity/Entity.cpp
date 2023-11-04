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

// Visszaadja a karakter nevét
string Entity::getName()
{
  return this->name;
}

// Visszaadja azt az érteket, hogy a karakter melyik körben lépett utoljára
unsigned Entity::getRoundMove()
{
  return this->roundMove;
}

// Beafrágja utoljára melyik körben lépett a karakter
void Entity::setRoundMove(const unsigned &roundMove)
{
  this->roundMove = roundMove;
}

// Visszaadja a karakter statisztikáit
void Entity::getStats()
{
  cout << "Name: " << this->name << endl;
  cout << "Damage: " << to_string(this->damage) << endl;
  cout << "Limit: " << to_string(this->limit) << endl;
  cout << "Level: " << to_string(this->level) << endl;
  cout << "---------------------------------------------------" << endl;
}

// Visszaadja a karakter sebzését
unsigned Entity::getDamage()
{
  return this->damage;
}

// Hozzáad egy megadott értéket a karakter sebzéséhez
void Entity::addDamage(unsigned damage)
{
  this->damage += damage;
}

// Visszaadja a karakter szintet
unsigned Entity::getLevel()
{
  return this->level;
}

// Feltételeknek megfelelően lépteti a karakter szintjét
string Entity::levelUp()
{
  string history = "";
  // Szintlépés ha elérte a limit damage-t
  if (this->damage >= this->limit)
  {
    this->level++;
    this->damage = Random::randomInt(25, 50);
    history = (this->getName() + " a(z) " + to_string(this->level) + ". szintre lépett!\n");
  }
  return history;
}

void Entity::operator+=(Entity *other)
{
  this->addDamage((*other).getDamage());
}

// Két karakter közül eldönti melyik az "erősebb"
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