#define MAX_BOARD_SIZE = 20
#define LETTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <conio.h>
#include <algorithm>

#include "../Random/Random.h"
#include "../Slot/Slot.h"
#include "../Direction/Direction.h"
#include "../History/History.h"
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

  this->generateSlots();
}

Board::Board(const int $columns, const int $rows)
{
  if ($columns <= 0 || $rows <= 0)
  {
    cout << "Nem adhatsz meg 0 vagy a negativ szamokat!" << endl;
    return;
  }

  this->columns = $columns;
  this->rows = $rows;
  this->round = 0;

  this->generateSlots();
}

Board::~Board() {}

void Board::generateSlots()
{
  History::writeHistory(to_string(this->columns) + " x " + to_string(this->rows) + " tábla létrehozva!\n");

  for (unsigned i = 0; i < this->rows; i++)
  {
    for (unsigned j = 0; j < this->columns; j++)
    {
      vector<Direction> directions;

      if (i == 0 && j == 0)
      {
        directions = {Direction::RIGHT, Direction::DOWN};
      }
      else if (i == 0 && j == this->columns - 1)
      {
        directions = {Direction::LEFT, Direction::DOWN};
      }
      else if (i == this->rows - 1 && j == 0)
      {
        directions = {Direction::RIGHT, Direction::UP};
      }
      else if (i == this->rows - 1 && j == this->columns - 1)
      {
        directions = {Direction::LEFT, Direction::UP};
      }
      else
      {
        if (i == 0)
        {
          directions = {Direction::RIGHT, Direction::LEFT, Direction::DOWN};
        }
        else if (i == this->rows - 1)
        {
          directions = {Direction::RIGHT, Direction::LEFT, Direction::UP};
        }
        else
        {
          if (j == 0)
          {
            directions = {Direction::UP, Direction::DOWN, Direction::RIGHT};
          }
          else if (j == this->columns - 1)
          {
            directions = {Direction::UP, Direction::DOWN, Direction::LEFT};
          }
          else
          {
            directions = {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT};
          }
        }
      }

      string id = LETTERS[j] + to_string(i + 1);
      *this += new Slot(id, directions);
    }
  }
}

const unsigned &Board::getRound()
{
  return this->round;
}

vector<Slot *> Board::getEmptySlots()
{
  vector<Slot *> emptySlots;
  for (unsigned i = 0; i < this->slots.size(); i++)
  {
    if (this->slots[i]->entityCount() == 0)
    {
      emptySlots.push_back(this->slots[i]);
    }
  }
  return emptySlots;
}

void Board::getStats()
{
  for (unsigned i = 0; i < this->slots.size(); i++)
  {
    if (this->slots[i]->entityCount() > 0)
    {
      Entity a = *this->slots[i]->getFirstEntity();
      cout << "Mezo: " << this->slots[i]->getId() << endl;
      a.getStats();
    }
  }
}

void Board::getStats(const string &id)
{
  auto it = find_if(this->slots.begin(), this->slots.end(), [id](Slot *slot)
                    { return slot->getId() == id; });

  if (it != this->slots.end())
  {
    Slot *a = *it;

    if (a->entityCount() > 0)
    {
      Entity b = *a->getFirstEntity();
      cout << "Mezo: " << a->getId() << endl;
      b.getStats();
    }
    else
    {
      cout << "A mezo ures!" << endl;
    }
  }
  else
  {
    cout << "A mezo nem talalhato!" << endl;
  }
}

void Board::generateEntities(unsigned $entityCount)
{
  for (unsigned i = 0; i < $entityCount; i++)
  {
    vector<Slot *> emptySlots = this->getEmptySlots();
    if (emptySlots.size() == 0)
    {
      History::writeHistory(to_string(i + 1) + " entitás hozzaadva a játéktérhez!");
      cout << "Nincs tobb hely a jatekosokhoz!" << endl;
      cout << "Nyomj entert a folytatashoz!";
      while (_getch() != '\r')
        ;
      return;
    }

    unsigned index = Random::randomInt(0, emptySlots.size() - 1);

    string name = "Entitty_" + to_string(i + 1);

    *emptySlots[index] += new Entity(name);
  }
  History::writeHistory(to_string($entityCount) + " entitás hozzaadva a játéktérhez!");
}

// Megrajzolja a vízszintes tábla elemet
void Board::drawHorisontalSeparator()
{
  cout << "   ";
  for (unsigned i = 0; i < this->columns; i++)
  {
    cout << "+---";
  }
  cout << "+\n";
}

// Megrajzolja a táblát
void Board::drawTable()
{
  system("clear");
  unsigned index = 0;

  cout << "--------------------------------------------------" << endl
       << endl;
  // Betűk kiírása
  cout << "     ";
  for (unsigned i = 0; i < this->columns; i++)
  {
    cout << LETTERS[i] << "   ";
  }
  cout << endl;
  this->drawHorisontalSeparator();
  // Entitások kirajzolása
  for (unsigned i = 0; i < this->rows; i++)
  {
    cout << " " << i + 1 << " |";
    for (unsigned j = 0; j < this->columns; j++)
    {
      cout << " "
           << ((this->slots[index]->entityCount() > 0) ? "O" : " ")
           << " |";
      index++;
    }
    cout << endl;
    this->drawHorisontalSeparator();
  }
}

void Board::move(Slot *from, Slot *to)
{
  Entity *a = from->getFirstEntity();

  if (a->getRoundMove() >= this->round)
  {
    return;
  }

  History::writeHistory(a->getName() + " : " + from->getId() + " -> " + to->getId());

  a->setRoundMove(this->round);
  to->addEntity(a);
  from->deleteFirstEntity();
}

void Board::moveEntities()
{
  this->round++;
  for (unsigned i = 0; i < this->slots.size(); i++)
  {
    Slot *a = this->slots[i];

    if (a->entityCount() == 0)
    {
      continue;
    }

    Direction dir = a->getRandomDirection();

    switch (dir)
    {
    case Direction::UP:
      this->move(a, this->slots[i - this->columns]);
      break;
    case Direction::DOWN:
      this->move(a, this->slots[i + this->columns]);
      break;
    case Direction::LEFT:
      this->move(a, this->slots[i - 1]);
      break;
    case Direction::RIGHT:
      this->move(a, this->slots[i + 1]);
      break;
    default:
      break;
    }
  }
}

void Board::fightEntities()
{
  for (unsigned i = 0; i < this->slots.size(); i++)
  {
    this->slots[i]->fight();
  }
}

void Board::levelUpEntities()
{
  if (this->round % 10 == 0 && this->round != 0)
  {
    for (unsigned i = 0; i < this->slots.size(); i++)
    {
      Entity *a = this->slots[i]->getFirstEntity();
      a->levelUp();
    }
  }
}

void Board::operator+=(Slot *other)
{
  this->slots.push_back(other);
}