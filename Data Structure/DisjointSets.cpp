#include <iostream>
#include <vector>
using namespace std;

// Find the set to which the vertex belongs
int findParent(vector<int> &par, int n) {
  if (par[n] == -1) {
    return n;
  }
  par[n] = findParent(par, par[n]);
  return par[n];
}

// Union of Two Sets
void unionParent(vector<int> &par, int n, int m) {
  int x = findParent(par, n);
  int y = findParent(par, m);

  par[x] = y;
}
