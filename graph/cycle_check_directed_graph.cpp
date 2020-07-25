#include <iostream>
#include <vector>
#include <stdlib.h>
using std::vector;
using std::pair;

void explore(int i, vector<vector<int>> &adj, int *state)
{
  state[i] = 1;
  for(auto it2 : adj[i])
  {
    if (state[it2] == 0)
    {
      explore(it2, adj,state);
    }
    if (state[it2] == 1)
    {
      std::cout<<"1";
      exit(0);
    }
  }
  state[i] = 2;
};
int acyclic(vector<vector<int> > &adj,size_t n) {
  //write your code here

  int state[n]; // permitted states are 0 1 and 2 

  // mark the states of all vertices initially to 0
  for(int i=0;i<n;i++)
    state[i] = 0;

  for(auto it1 = 0; it1 != adj.size(); it1++)
  {
    if (state[it1] == 0)
      explore(it1,adj,state);
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
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  acyclic(adj,n);
}
