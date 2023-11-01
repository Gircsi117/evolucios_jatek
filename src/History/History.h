#ifndef HISTORY_H
#define HISTORY_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class History
{
public:
  static void clearHistory();
  static void writeHistory(string input);
};

#endif // !HISTORY_H