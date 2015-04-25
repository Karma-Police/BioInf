#include <iostream>
#include <cstdio>
#include <cassert>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAXN = int(5e3);
const int string_len = 350;

struct edge {
  int to, w;
  edge(int _to, int _w) : to(_to), w(_w) { }
};

int str_to_num(const string & s)
{
  int res = 0;
  for (size_t i = 0; i < s.length(); i++)
    res = res * 10 + (s[i] - '0');

  return res;
}

vector<string> basis;
vector<string> nodes;
vector<vector<edge> > gr;
int color[MAXN];


string generate(const string & s, int p)
{
  int n = s.length();
  string res;

  for (int i = 0; i < n; i++)
  {
    if (rand() % 5001 < p) {
      res += char((rand() % 2) + 'a');
      cerr << res[i] << "!" << endl;
    } else res += s[i];
  }
  
  return res;
}

int get_distance(const string & a, const string & b)
{
  int res = 0;
  int n = a.length();
  for (int i = 0; i < n; i++)
    if (a[i] != b[i]) ++res;

  return res;
}


int main(int args, char ** argv)
{
  srand(time(NULL));

  ofstream out;
  out.open("./test.in", ios::out | ios::trunc);

  if (args != 4) {
    cerr << "ERROR! smth wrong with get_tests arguments" << endl;
    out.close();
    return -23;
  }

  int n = str_to_num(argv[1]),
      k = str_to_num(argv[2]),
      p = str_to_num(argv[3]);
  cerr << "!! " << n << " " << k << " " << p << endl;

  for (int i = 0; i < k; i++)
  {
    string nxt;
    for (int j = 0; j < string_len; j++)
      nxt += char(rand() % 2 + 'a');
    basis.push_back(nxt);
  }

  int val = n;
  for (int i = 0; i < k; i++)
  {
    int m = rand() % (val - (k - i - 1)) + 1;
    if (i == k - 1) m = val;
    val -= m;
    for (int j = 0; j < m; j++) 
    {
      color[nodes.size()] = i;
      nodes.push_back(generate(basis[i], p));
    }
  }

  assert(color[n - 1] == k - 1);

  gr.resize(n); 
  int E = 0;
  for (int i = 0; i < n; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      int tmp = get_distance(nodes[i], nodes[j]);
      if (tmp < 4) {
	gr[i].push_back(edge(j, tmp));
	gr[j].push_back(edge(i, tmp));
	++E;
      }
    }
  }

  for (int i = 0; i < k; i++)
    cerr << "! basis: " << basis[i] << endl;
  cerr << endl;
  for (int i = 0; i < n; i++)
    cerr << "! node: " << nodes[i] << endl;

  out << n << " " << E << " 001" << endl;
  for (int i = 0; i < n; i++)
  {
    for (size_t j = 0; j < gr[i].size(); j++)
      out << gr[i][j].to + 1 << " " << 901 - gr[i][j].w *  gr[i][j].w * 100 << " ";
    out << endl;
  }

  out.close();
  out.open("./test.info", ios::out | ios::trunc);

  out << n << endl;
  for (int i = 0; i < n; i++)
    out << color[i] << endl;

  out.close();

  return 0;
}





