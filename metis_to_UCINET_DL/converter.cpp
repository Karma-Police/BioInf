#include <iostream>
#include <cstdio>
#include <cassert>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAXN = 1000;

struct edge {
  int to, w;
  edge(int _to, int _w) : to(_to), w(_w) { }
};

int gr[MAXN][MAXN], color[MAXN], color_rev[MAXN], result[MAXN][MAXN];
bool used[MAXN];
int cur_color = 0;

void recolor(int cur, int n)
{
  if (used[cur]) return;
  used[cur] = true;
  color[cur] = cur_color;
  for (int i = 0; i < n; i++)
    if (gr[cur][i] == 100) recolor(i, n);
}

int main(int args, char ** argc)
{
  srand(time(NULL));

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

    for (int i = 0; i < n; i++)
    {
      if (!used[i]) {
        recolor(i, n);
	color_rev[cur_color] = i;
        cur_color += 1;
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

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
      result[color[i]][color[j]] = max(result[color[i]][color[j]], gr[i][j]);
  }
  
  cerr << "! old vertex count: " << n << endl;
  cerr << "! new vertex count: " << cur_color << endl;

  out << "dl" << endl << "format=edgelist1" << endl;
  out << "n=3" << endl << "data:" << endl;

  for (int i = 0; i < cur_color; i++)
  {
    for (int j = i + 1; j < cur_color; j++)
      if (result[i][j] >= 99) out << i + 1 << " " << j + 1 << " " << result[i][j] << endl;
  }

  out << endl;

  out.close();
}



