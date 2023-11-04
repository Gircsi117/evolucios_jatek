#define MAX_BOARD_SIZE 9
#define LETTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define CLEAR_SCREEN

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

      if (col <= 1 || row <= 1 || col > MAX_BOARD_SIZE || row > MAX_BOARD_SIZE)
      {
        throw invalid_argument("A megadott szam nincs benne a megadott intervallumban!");
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

Board::Board(const int columns, const int rows)
{
  if (columns <= 0 || rows <= 0)
  {
    cout << "A megadott ertek nincs benne a megadott intervallumban!" << endl;
    cout << "A tabla meretei beallitva a legkissebb lehetseges allapotra!" << endl;
    this->columns = 2;
    this->rows = 2;
  }
  else if (columns > MAX_BOARD_SIZE || rows > MAX_BOARD_SIZE)
  {
    cout << "A megadott ertek nincs benne a megadott intervallumban!" << endl;
    cout << "A tabla meretei beallitva a legnagyobb lehetseges allapotra!" << endl;
    this->columns = 9;
    this->rows = 9;
  }
  else
  {
    this->columns = columns;
    this->rows = rows;
  }

  this->round = 0;
  this->generateSlots();
}

Board::~Board() {}

// Legeneralja a mezőket
void Board::generateSlots()
{
  History::writeHistory(to_string(this->columns) + " x " + to_string(this->rows) + " tabla letrehozva!\n");

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

// Visszaadja a jelenlegi kör szamat
const unsigned &Board::getRound()
{
  return this->round;
}

// Visszaadja az összes üres mezőt
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

bool Board::isHaveWinner()
{
  if (this->getEmptySlots().size() == (this->columns * this->rows - 1))
  {
    return true;
  }
  return false;
}

// Az összes entitas adatait kiirja
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

// A megadott id-val rendelkező entitas parametereit irja ki
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

void Board::generateEntities(int entityCount)
{
  if (entityCount <= 1)
  {
    cout << "Nem adtal meg elegendo jatekost!" << endl;
    cout << "Az entitasok szama beallitva a legkisebb lehetseges allapotra!" << endl;
    entityCount = 2;
  }

  for (int i = 0; i < entityCount; i++)
  {
    vector<Slot *> emptySlots = this->getEmptySlots();
    if (emptySlots.size() == 0)
    {
      History::writeHistory(to_string(i + 1) + " entitas hozzaadva a jatekterhez!");
      cout << "Nincs tobb hely a jatekosokhoz!" << endl;
      return;
    }

    unsigned index = Random::randomInt(0, emptySlots.size() - 1);

    string name = "Entitty_" + to_string(i + 1);

    *emptySlots[index] += new Entity(name);
  }
  History::writeHistory(to_string(entityCount) + " entitas hozzaadva a jatekterhez!");
}

// Megrajzolja a vizszintes tabla elemet
void Board::drawHorisontalSeparator()
{
  cout << "   ";
  for (unsigned i = 0; i < this->columns; i++)
  {
    cout << "+---";
  }
  cout << "+\n";
}

// Megrajzolja a tablat
void Board::drawTable()
{
#ifdef CLEAR_SCREEN
  if (this->round > 0)
  {
    system("clear 2> nul");
    system("cls 2> nul");
  }
#endif // DEBUG
  unsigned index = 0;

  cout << "--------------------------------------------------" << endl
       << endl;
  // Betűk kiirasa
  cout << "     ";
  for (unsigned i = 0; i < this->columns; i++)
  {
    cout << LETTERS[i] << "   ";
  }
  cout << endl;
  this->drawHorisontalSeparator();
  // Entitasok kirajzolasa
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

// athelyezi a paraméterül megadott mező első entitasat a megadott mezőre
string Board::move(Slot *from, Slot *to)
{
  string history = "";
  Entity *a = from->getFirstEntity();

  if (a->getRoundMove() >= this->round)
  {
    return history;
  }

  history = (a->getName() + " : " + from->getId() + " -> " + to->getId()) + "\n";

  a->setRoundMove(this->round);
  to->addEntity(a);
  from->deleteFirstEntity();

  return history;
}

// Mozgatja az entitasokat
void Board::moveEntities()
{
  string history = "";
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
      history += this->move(a, this->slots[i - this->columns]);
      break;
    case Direction::DOWN:
      history += this->move(a, this->slots[i + this->columns]);
      break;
    case Direction::LEFT:
      history += this->move(a, this->slots[i - 1]);
      break;
    case Direction::RIGHT:
      history += this->move(a, this->slots[i + 1]);
      break;
    default:
      break;
    }
  }
  if (history != "")
  {
    History::writeHistory("Mozgasok:\n" + history);
  }
}

// Harcoltatja az entitasokat
void Board::fightEntities()
{
  string history = "";
  for (unsigned i = 0; i < this->slots.size(); i++)
  {
    history += this->slots[i]->fight();
  }

  if (history != "")
  {
    History::writeHistory("Harcok:\n" + history);
  }
}

// Fejleszti az entitasokat
void Board::levelUpEntities()
{
  if (this->round % 10 == 0 && this->round != 0)
  {
    string history = "";

    for (unsigned i = 0; i < this->slots.size(); i++)
    {
      if (this->slots[i]->entityCount() > 0)
      {
        Entity *a = this->slots[i]->getFirstEntity();
        history += a->levelUp();
      }
    }

    if (history != "")
    {
      History::writeHistory("Szintlepesek:\n" + history);
    }
  }
}

void Board::operator+=(Slot *other)
{
  this->slots.push_back(other);
}