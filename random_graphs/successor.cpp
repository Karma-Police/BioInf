#include <iostream>
#include <cstdio>
#include <cassert>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
  ifstream metis;
  ifstream inf;
  metis.open("./metis.out", ios::in);
  inf.open("./test.info", ios::in);

  int n; inf >> n;
  int error = 0;
  for (int i = 0; i < n; i++)
  {
    int a, b;
    metis >> a;
    inf >> b;
    if (a != b) ++error;
  }
  
  metis.close();
  inf.close();

  cout << n << " " << error << endl;
}
