#include <iostream>
#include <string>
#include <vector>

#include "../Random/Random.h"
#include "../Slot/Slot.h"
#include "Board.h"

using namespace std;

Board::Board()
{
  int col = 0;
  int row = 0;

  do
  {
    try
    {
      string a;
      string b;

      cout << "Kerlek adja meg a tabla mereteit!" << endl;
      cout << "Oszlopok szama: ";
      cin >> a;
      cout << "Sorok szama: ";
      cin >> b;

      col = stoi(a);
      row = stoi(b);

      if (col <= 0 || row <= 0)
      {
        throw invalid_argument("Nem adhatsz meg 0 vagy a negativ szamokat!");
      }
      else
      {
        break;
      }
    }
    catch (const std::invalid_argument &ia)
    {
      cout << "Kerlek pozitiv egesz szamot adj meg!" << endl;
    }

  } while (true);

  this->columns = col;
  this->rows = row;
  this->round = 0;

  for (unsigned i = 0; i < this->columns * this->rows; i++)
  {
    *this += new Slot();
  }
}

Board::Board(const unsigned $columns, const unsigned $rows)
{
  if ($columns <= 0 || $rows <= 0)
  {
    cout << "Nem adhatsz meg 0 vagy a negativ szamokat!" << endl;
    return;
  }

  this->columns = $columns;
  this->rows = $rows;
  this->round = 0;

  for (unsigned i = 0; i < $columns * $rows; i++)
  {
    *this += new Slot();
  }
}

Board::~Board() {}

void Board::operator+=(Slot *other)
{
  this->slots.push_back(other);
}