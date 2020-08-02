#include <iostream>
#include <vector>
#include <cstdlib>
using std::vector;
using std::pair;

void explore(int i, const vector<vector<int>> &adj, std::vector<int> *state)
{
  (*state)[i] = 1;
  for (const auto it2 : adj[i])
  {
    if ((*state)[it2] == 0)
    {
      explore(it2, adj, state);
    }
    if ((*state)[it2] == 1)
    {
      std::cout<<"1";
      exit(0);
    }
  }
  (*state)[i] = 2;
};
int acyclic(const vector<vector<int> > &adj, size_t n) {
  //write your code here

  // permitted states are 0 1 and 2
  std::vector<int> state(n, 0);

  // mark the states of all vertices initially to 0
  for (size_t i = 0; i < n; i++)
  {
    state[i] = 0;
  }

  for (size_t it1 = 0; it1 != adj.size(); it1++)
  {
    if (state[it1] == 0)
    {
      explore(it1, adj, &state);
    }
    if (state[it1] == 1)
    {
      std::cout<<"1";
      exit(0);
    }
  }
  std::cout<<"0";
  return 0;
}

int main() {
  size_t n = 0, m = 0;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x = 0, y = 0;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  acyclic(adj,n);
}
