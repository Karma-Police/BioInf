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
const int string_len = 300;
const int BASIS_COUNT = 1;
const int random_M = 1001;
const int BASIS_P = 11;
const int INF = 1e4;

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
    if (rand() % random_M < p) {
      res += char((rand() % 4) + 'a');
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

string random_changing(const string & s)
{
  string res = s;
  int n = res.length();
  for (int _i = 0; _i < BASIS_COUNT; _i++)
    for (int i = 0; i < n; i++)
      if ((rand() % random_M) < BASIS_P) res[i] = (rand() % 4) + 'a';
  return res;
}

void count_colors(int k, int n)
{
  if (n < k) {
    cerr << "the number of partitions must be less then n" << endl;
    exit(-1);
  }

  for (int cur_color = 0; cur_color < k; cur_color++)
  {
    for (int i = n / k * cur_color; i < n / k * (cur_color + 1); i++)
      color[i] = cur_color;
  }
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

  string BASIS;
  for (int j = 0; j < string_len; j++)
    BASIS += char(rand() % 4 + 'a');

  cerr << "! basis distance:   "; 
  for (int i = 0; i < k; i++)
  {
    basis.push_back(random_changing(BASIS));
    cerr << get_distance(BASIS, basis[i]) << " ";
  }
  cerr << endl;


  count_colors(k, n);
  for (int i = 0; i < n; i++)
    nodes.push_back(generate(basis[color[i]], p));

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
      } else {
	gr[i].push_back(edge(j, -1));
	gr[j].push_back(edge(i, -1));
      }
      ++E;
    }
  }

  cerr << "! colors: ";
  for (int i = 0; i < n; i++)
    cerr << color[i] << " ";
  cerr << endl;

  for (int i = 0; i < k; i++)
    cerr << "! basis: " << basis[i] << endl;
  cerr << endl;
  for (int i = 0; i < n; i++)
    cerr << "! node: " << nodes[i] << endl;

  out << n << " " << E << " 001" << endl;
  for (int i = 0; i < n; i++)
  {
    for (size_t j = 0; j < gr[i].size(); j++) {
      if (gr[i][j].w < 0) out << gr[i][j].to + 1 << " " << 1 << " ";
      else out << gr[i][j].to + 1 << " " << INF - gr[i][j].w *  gr[i][j].w * 1000 << " ";

      cerr << gr[i][j].w *  gr[i][j].w * 100 << " ";
    }
    cerr << " waat " << endl;
    out << endl;
  }

  out.close();
  out.open("./test.info", ios::out | ios::trunc);

  out << n << " " << k << endl;
  for (int i = 0; i < n; i++)
    out << color[i] << endl;

  out.close();

  return 0;
}





