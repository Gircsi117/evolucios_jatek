#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <vector>

#include "../Random/Random.h"
#include "../Slot/Slot.h"

class Board
{
private:
  unsigned columns;
  unsigned rows;
  vector<Slot *> slots;
  unsigned round;

public:
  Board();
  Board(const unsigned $columns, const unsigned $rows);
  ~Board();

  void operator+=(Slot *other);
};

#endif