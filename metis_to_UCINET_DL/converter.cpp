#include <iostream>
#include <cstdio>
#include <cassert>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

const int MAXN = 1000;

struct edge {
  int to, w;
  edge(int _to, int _w) : to(_to), w(_w) { }
};

int gr[MAXN][MAXN];

int main(int args, char ** argc)
{
  if (args != 2) {
    cerr << "Wrong input format!" << endl;
    cerr << "Usage: prog_name [path_to_file]" << endl;
    return -1;
  }

  ifstream in; 
  in.open(argc[1], ifstream::in);
  if (!in.is_open()) {
    cerr << "ERROR, cant open the source file!" << endl;
    return -2;
  }


  int n, m, trash;
  try{
    in >> n >> m >> trash;
    string line; getline(in, line);
    
    for (int i = 0; i < n; i++)
    {
      getline(in, line);
      istringstream ss(line.c_str()); 
      while (!ss.eof())
      {
	int x, w;
	ss >> x >> w;
	if (ss.eof()) break;
	cerr << x << " " << w << endl;
	--x; w = 100 - w;
	gr[i][x] = w;
      }
    }
  } 
  catch(...)
  {
    cerr << "ERROR! Invalid graph format! Make sure that you convert what you need :)" << endl;
    throw;
  }
  in.close();

  ofstream out;
  out.open(string(argc[1]) + ".dl", ofstream::out | ofstream::trunc);

  out << "dl" << endl << "format=edgelist1" << endl;
  out << "n=3" << endl << "data:" << endl;

  for (int i = 0; i < n; i++)
  {
    for (int j = i + 1; j < n; j++)
      if (gr[i][j] >= 100) out << i + 1 << " " << j + 1 << " " << gr[i][j] << endl;
  }

  out << endl;

  out.close();
}



