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

// Visszaadja a mező azonosítóját
const string &Slot::getId()
{
  return this->id;
}

// Visszaadja a mezo első elemét
Entity *Slot::getFirstEntity()
{
  return this->entities[0];
}

// Eltávolítja az első elemet
void Slot::deleteFirstEntity()
{
  this->entities.erase(this->entities.begin());
}

// Az adott mezőn lévő elemek harcolnak
string Slot::fight()
{
  string text = "";

  // Ha nincs legalább 2 entitás, nem lehet harcolni
  if (this->entityCount() < 2)
  {
    return text;
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

  text = strongest->getName() + " legyozte oket a(z) " + this->id + " mezon:\n";

  // A nyertes entitás erősítése, a többi entitás eltávolítása
  auto it = this->entities.begin();
  while (it != this->entities.end())
  {
    if (*it != strongest)
    {
      text += "\t" + (*it)->getName() + ";\n";
      *strongest += *it;
      delete *it;
      it = this->entities.erase(it);
    }
    else
    {
      ++it;
    }
  }
  return text;
}

// Visszaadja a mező elemeinek a számát
unsigned Slot::entityCount()
{
  return this->entities.size();
}

// Visszaad egy lehetséges random irányt
const Direction &Slot::getRandomDirection()
{
  return this->directions[Random::randomInt(0, this->directions.size() - 1)];
}

// Hozzáad egy entitást
void Slot::addEntity(Entity *other)
{
  this->entities.push_back(other);
}

void Slot::operator+=(Entity *other)
{
  this->entities.push_back(other);
}