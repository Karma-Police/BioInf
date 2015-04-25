#include <iostream>
#include <cstdio>
#include <cassert>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

const int MAXN = 1000;

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

  ofstream out;
  out.open(string(argc[1]) + ".ok", ofstream::out | ofstream::trunc);

  int n, m, trash;
  try{
    in >> n >> m >> trash;
    out << " " << n << " " << m << " 001" << endl;
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
	w = 901 - 100 * w * w;
	out << x << " " << w << " ";
      }
      out << endl;
    }
  } 
  catch(...)
  {
    cerr << "ERROR! Invalid graph format! Make sure that you convert what you need :)" << endl;
    throw;
  }

  in.close();
  out.close();
}



