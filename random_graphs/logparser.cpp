#include <iostream>
#include <cstdio>
#include <cassert>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef long double ld;

int main()
{
  ifstream log;
  log.open("./logfile", ios::in);

  ld total = 0, success = 0;
  while (!log.eof())
  {
    int n, ok;
    log >> n >> ok;
    if (log.eof()) break;
    cerr << n << " " << ok << endl;
    total += n;
    success += ok;
  }

  cout << "total vertex number: " << (int) total << " correctly clustered: " << (int) success << endl;
  cout << "success ratio: " << success / total << endl;

  log.close();

  return 0;
}
