#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <chrono>

#include "./src/Random/Random.h"
#include "./src/Entity/Entity.h"
#include "./src/Slot/Slot.h"
#include "./src/Board/Board.h"
#include "./src/Direction/Direction.h"
#include "./src/History/History.h"

using namespace std;

void getStats(Board &board)
{
  string input = "";

  cout << "  - all / a - Osszes" << endl;
  cout << "  - one / o - Egy elem" << endl;
  cout << "Muvelet: ";
  getline(cin, input);
  cout << endl;

  if (input == "")
  {
    return;
  }
  else if (input == "all" || input == "a")
  {
    board.getStats();
  }
  else if (input == "one" || input == "o")
  {
    string id = "";
    cout << "Kerem adja meg a mezo azonositojat (Pl.: A5): ";
    getline(cin, id);
    board.getStats(id);
  }
  else
  {
    throw invalid_argument("Nincs ilyen muvelet!");
  }
}

int main(int argc, const char **argv)
{
  Random::resetRand();
  History::clearHistory();
  string input = "";

  Board board = Board(8, 8);
  board.generateEntities(64);
  board.drawTable();

  do
  {
    try
    {
      cout << endl
           << "-----------------------------------------------" << endl
           << endl;

      cout << "Korok szama: " << to_string(board.getRound() + 1) << endl
           << endl;
      cout << "Muveletek:" << endl;
      cout << "  - [Enter] - Kovetkezo kor" << endl;
      cout << "  - clear / c - Terminal 'tisztitasa'" << endl;
      cout << "  - stat / s - Entitas(ok) megtekintese" << endl;
      cout << "  - exit / q - Kilepes" << endl;
      cout << "Muvelet: ";

      getline(cin, input);

      if (input == "")
      {
        History::writeHistory("\n" + to_string(board.getRound() + 1) + ". kör!");
        History::writeHistory("---------------------------------------------------\n");

        History::writeHistory("Mozgások:");
        board.moveEntities();

        History::writeHistory("\nHarcok:");
        board.fightEntities();

        History::writeHistory("\nSzintlépések:");
        board.levelUpEntities();

        board.drawTable();
      }
      else if (input == "stat" || input == "s")
      {
        getStats(board);
      }
      else if (input == "clear" || input == "c")
      {
        board.drawTable();
      }
      else if (input == "exit" || input == "q")
      {
        break;
      }
      else
      {
        throw invalid_argument("Nincs ilyen muvelet!");
      }
    }
    catch (const invalid_argument &e)
    {
      cout << e.what() << endl;
    }

  } while (true);

  return 0;
}