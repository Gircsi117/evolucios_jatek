#define HISTORY_TXT "./history.txt"

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>

#include "History.h"

using namespace std;

void History::clearHistory()
{
  std::ofstream file(HISTORY_TXT, std::ofstream::trunc);
  file.close();
}

void History::writeHistory(string input)
{
  ofstream myfile;
  myfile.open(HISTORY_TXT, ios::app);
  myfile << input << endl;
  myfile.close();
}