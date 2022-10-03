//Par array stores final parent of the node after running findpar function
//Optimizations:
//1. Works like assigning main parent to all intermediate nodes while unwinding from recursion
//2. Here merge happens by height that is if one connected component height's is x, another is y and x>y then while merging x and y, y would get attached to x
//These 2 optimzations make DSU way faster making it runable in approximately amorized constant time
int par[100009];
int height[100009];
int sz[100009];
void initialize()
{
  //initializing standard values
  //initially parent of i would be i itself
  for(int i=0;i<100005;i++)
  {
    par[i] = i;
    height[i] = 0;
    sz[i] = 1;
  }
}

int findpar(int u)
{
  //if parent found return 
  if (par[u] == u)
    return u;
  // and also save that while unwinding for all subsequent nodes in the path
  return par[u] = findpar(par[u]);
}
void combine(int u, int v)
{
  //finding actual parent of nodes which i want to merge
  u = findpar(u);
  v = findpar(v);
  if (u == v)
    return;
  //if both parent same then no need to merge

  //if height of both parent same then we need to make 1 longer to make it work
  if (height[u] == height[v])
    height[u]++;
  
  //optimzation 2
  //if u's height is greater then swap
  if (height[u] > height[v])
    swap(u, v);
  //linking both components by assigning parent of u as v
  par[u] = v;

  //increasing size of v
  sz[v] += sz[u];
}