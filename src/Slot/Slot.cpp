#include <iostream>
#include <string>
#include <vector>

#include "Slot.h"
#include "../History/History.h"

using namespace std;

Slot::Slot(string $id, vector<Direction> $directions)
{
  this->id = $id;
  this->directions = $directions;
}

Slot::~Slot() {}

const string &Slot::getId()
{
  return this->id;
}

Entity *Slot::getFirstEntity()
{
  return this->entities[0];
}

void Slot::deleteFirstEntity()
{
  this->entities.erase(this->entities.begin());
}

void Slot::fight()
{
  // Ha nincs legalább 2 entitás, nem lehet harcolni
  if (this->entityCount() < 2)
  {
    return;
  }

  // Legerősebb entitás kiválasztása
  Entity *strongest = this->entities[0];

  for (unsigned i = 1; i < this->entities.size(); i++)
  {
    // A legerősebb kiválasztása
    if (*strongest < *this->entities[i])
    {
      strongest = this->entities[i];
    }
  }

  string text = strongest->getName() + " legyozte oket a(z) " + this->id + " mezon: ";

  // A nyertes entitás erősítése, a többi entitás eltávolítása
  auto it = this->entities.begin();
  while (it != this->entities.end())
  {
    if (*it != strongest)
    {
      text += "\n\t" + (*it)->getName() + "; ";
      *strongest += *it;
      delete *it;
      it = this->entities.erase(it);
    }
    else
    {
      ++it;
    }
  }
  History::writeHistory(text);
}

unsigned Slot::entityCount()
{
  return this->entities.size();
}

const Direction &Slot::getRandomDirection()
{
  return this->directions[Random::randomInt(0, this->directions.size() - 1)];
}

void Slot::addEntity(Entity *other)
{
  this->entities.push_back(other);
}

void Slot::operator+=(Entity *other)
{
  this->entities.push_back(other);
}