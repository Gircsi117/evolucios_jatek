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

  for (unsigned i = 0; i < this->entities.size(); i++)
  {
    // A nagyobb szintű nyer
    if (this->entities[i]->getLevel() > strongest->getLevel())
    {
      strongest = this->entities[i];
    }
    // Egyenlő szint esetén az erősebb
    else if (this->entities[i]->getLevel() == strongest->getLevel() &&
             this->entities[i]->getDamage() > strongest->getDamage())
    {
      strongest = this->entities[i];
    }
    // Egyforma erősségű és szintű entitások esetén aki előbb van az nyer.
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