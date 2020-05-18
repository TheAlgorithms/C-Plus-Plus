#include <iostream>
#include <vector>

using namespace std;

class graph
{
  private:
    vector<vector<int>> adj;
    int cc;
    void dfs();
    void explore(int, vector<bool>&);
  public:
    graph(int n): adj(n,vector<int>()), cc(0) {}
    void addEdge(int,int);
    int getConnectedComponents()
    {
      dfs();
      return cc;
    }
};

void graph::addEdge(int u, int v)
{
  adj[u-1].push_back(v-1);
  adj[v-1].push_back(u-1);
}

void graph::dfs()
{
  int n = adj.size();
  vector<bool> visited(n,false);

  for(int i = 0;i<n;i++)
  {
    if (!visited[i])
    {
      explore(i,visited);
      cc++;
    }
  }
}

void graph::explore(int u, vector<bool> &visited)
{
  visited[u] = true;
  for(auto v : adj[u])
  {
    if(!visited[v])
      explore(v,visited);
  }
}

int main()
{
  graph g(4);
  g.addEdge(1,2);
  g.addEdge(3,2);
  cout<<g.getConnectedComponents();
  return 0;
}
