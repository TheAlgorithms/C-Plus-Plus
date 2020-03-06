#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

vector<int> root, rnk;

void CreateSet(int n) {
  root = vector<int> (n+1);
  rnk = vector<int> (n+1, 1);
  for (int i = 1; i <= n; ++i) {
    root[i] = i;
  }
}

int Find(int x) {
  if (root[x] == x) {
    return x;
  }
  return root[x] = Find(root[x]);
}

bool InSameUnion(int x, int y) {
  return Find(x) == Find(y);
}

void Union(int x, int y) {
  int a = Find(x), b = Find(y);
  if (a != b) {
    if (rnk[a] < rnk[b]) {
      root[a] = b;
    } else if (rnk[a] > rnk[b]) {
      root[b] = a;
    } else {
      root[a] = b;
      ++rnk[b];
    }
  }
}

int main() {
  // tests CreateSet & Find
  int n = 100;
  CreateSet(n);
  for (int i = 1; i <= 100; ++i) {
    if (root[i] != i) {
      cout << "Fail" << endl;
      break;
    }
  }
  // tests InSameUnion & Union
  cout << "1 and 2 are initially not in the same subset" << endl;
  if (InSameUnion(1, 2)) {
    cout << "Fail" << endl;
  }
  Union(1, 2);
  cout << "1 and 2 are now in the same subset" << endl;
  if (!InSameUnion(1, 2)) {
    cout << "Fail" << endl;
  }
  return 0;
}
