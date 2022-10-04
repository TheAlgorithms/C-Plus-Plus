/**
 * @file
 * @brief [Disjoint union](https://cp-algorithms.com/data_structures/disjoint_set_union.html)
 *
 * @details
 * This data structure provides the following capabilities. We are given several elements, each of which is a separate set. A DSU will have an operation to combine any two sets, and it will be able to tell in which set a specific element is. The classical version also introduces a third operation, it can create a set from a new element.
 *
 * ### Algorithm
 * In Graph, if you have to find out the minimum spanning tree, i.e. a subgraph which is actually a tree and total weight of that tree is minimum, then DSU could be used.
 *
 * @author [Aman Agrawal](https://github.com/amanagr6697)
 */
/** Optimizations:
* 1. Works like assigning main parent to all intermediate nodes while unwinding from recursion
* 2. Here merge happens by height that is if one connected component height's is x, another is y and x>y then while merging x and y, y would get attached to x
* These 2 optimzations make DSU way faster making it runable in approximately amorized constant time
**/
#include <iostream> //for io
#include<vector>    //for vector
#include <algorithm> //for sorting
using namespace std;


// Par array stores final parent of the node after running findpar function
vector<int> par(100009, 0);

//Height stores the height of connected component in which the node belongs.
vector<int> height(100009, 0);

//sz stores the size of connected component of a node.
vector<int> sz(100009, 0);

//creating graph for adjancey list
vector<pair<int,pair<int,int>>> vec;

//stores minimum spanning tree cost
int min_spanning_tree_cost;
void initialize()
{
  // initializing standard values
  // initially parent of i would be i itself
  for (int i = 0; i < 100005; i++)
  {
    par[i] = i;
    height[i] = 0;
    sz[i] = 1;
  }
}

int findpar(int u)
{
  // if parent found return
  if (par[u] == u)
  {
    return u;
  }
  // and also save that while unwinding for all subsequent nodes in the path
  return par[u] = findpar(par[u]);
}

void combine(int u, int v)
{
  // finding actual parent of nodes which i want to merge
  u = findpar(u);
  v = findpar(v);
  if (u == v)
  {
    return;
  }
  // if both parent same then no need to merge

  // if height of both parent same then we need to make 1 longer to make it work
  if (height[u] == height[v])
  {
    height[u]++;
  }

  // optimzation 2
  // if u's height is greater then swap
  if (height[u] > height[v])
  {
    swap(u, v);
  }
  // linking both components by assigning parent of u as v
  par[u] = v;

  // increasing size of v
  sz[v] += sz[u];
}
void test()
{
  initialize();
  vec.clear();
  int nodes,edges;
  cin>>nodes>>edges;
  while(edges--)
  {
    int node_a,node_b,cost;
    cin>>node_a>>node_b>>cost;
    vec.push_back({cost,{node_a,node_b}});
  }
  sort(vec.begin(),vec.end());
  for(int i=0;i<nodes;i++)
  {
    if(findpar(vec[i].second.first)==findpar(vec[i].second.second))
    continue;
    else
    {
      combine(vec[i].second.first,vec[i].second.second);
      min_spanning_tree_cost+=vec[i].first;
    }
    
  }
}
int main()
{
  test();
  cout<<min_spanning_tree_cost;
  return 0;
}