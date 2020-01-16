#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m; // For number of Vertices (V) and number of edges (E)
vector<vector<int>> G;
vector<bool> visited;
vector<int> ans;

void dfs(int v)
{
  visited[v] = true;
  for (int u : G[v])
  {
    if (!visited[u])
      dfs(u);
  }
  ans.push_back(v);
}

void topological_sort()
{
  visited.assign(n, false);
  ans.clear();
  for (int i = 0; i < n; ++i)
  {
    if (!visited[i])
      dfs(i);
  }
  reverse(ans.begin(), ans.end());
}
int main()
{
  cout << "Enter the number of vertices and the number of directed edges\n";
  cin >> n >> m;
  int x, y;
  G.resize(n, vector<int>());
  for (int i = 0; i < n; ++i)
  {
    cin >> x >> y;
    x--, y--; // to convert 1-indexed to 0-indexed
    G[x].push_back(y);
  }
  topological_sort();
  cout << "Topological Order : \n";
  for (int v : ans)
  {
    cout << v + 1 << ' '; // converting zero based indexing back to one based.
  }
  cout << '\n';
  return 0;
}
