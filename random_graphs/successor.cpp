#include <iostream>
#include <cstdio>
#include <cassert>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

vector<int> perm, A, B;

int main()
{
  ifstream metis;
  ifstream inf;
  metis.open("./metis.out", ios::in);
  inf.open("./test.info", ios::in);

  int n, k; inf >> n >> k;
  int N = 1;
  for (int i = 0; i < k; i++)
    perm.push_back(i), N *= (i + 1);

  for (int i = 0; i < n; i++)
  {
    int a, b;
    metis >> a;
    inf >> b;
    A.push_back(a);
    B.push_back(b);
  }

  int min_error = n + 10;
  for (int _i = 0; _i < N; _i++)
  {
    int error = 0;
    for (int i = 0; i < n; i++)
      if (A[i] != perm[B[i]]) ++error;
    min_error = min(min_error, error);
    next_permutation(perm.begin(), perm.end());
  } 
  
  metis.close();
  inf.close();

  cout << n << " " << n - min_error << endl;
}
