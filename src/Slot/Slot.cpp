#include <iostream>
#include <string>
#include <vector>

#include "Slot.h"

using namespace std;

Slot::Slot()
{
}

Slot::~Slot() {}

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

  // A nyertes entitás erősítése, a többi entitás eltávolítása
  auto it = this->entities.begin();
  while (it != this->entities.end())
  {
    if (*it != strongest)
    {
      *strongest += *it;
      delete *it;
      it = this->entities.erase(it);
    }
    else
    {
      ++it;
    }
  }
}

unsigned Slot::entityCount()
{
  return this->entities.size();
}

void Slot::operator+=(Entity *other)
{
  this->entities.push_back(other);
}