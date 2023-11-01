#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <vector>

#include "../Random/Random.h"
#include "../Slot/Slot.h"
#include "../Direction/Direction.h"

class Board
{
private:
  unsigned columns;
  unsigned rows;
  unsigned round;
  vector<Slot *> slots;

  void drawHorisontalSeparator();

public:
  Board();
  Board(const int $columns, const int $rows);
  ~Board();

  const unsigned &getRound();

  void generateSlots();
  vector<Slot *> getEmptySlots();

  void generateEntities(unsigned $entityCount);

  void getStats();
  void getStats(const string &id);

  void drawTable();

  void move(Slot *from, Slot *to);

  void moveEntities();
  void fightEntities();
  void levelUpEntities();

  void operator+=(Slot *other);
};

#endif