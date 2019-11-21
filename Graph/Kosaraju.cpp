/* Implementation of Kosaraju's Algorithm to find out the strongly connected components (SCCs) in a graph. 
   Author:Anirban166
*/   

#include<iostream>
#include<vector>

using namespace std;

/*Common terms/anotations used as parameters in functions below:
  V: number of vertices,
  adj[]: array of vectors to represent graph,
  vis[]: array to keep track of visited nodes, (boolean type)
  grev[]: graph with reverse edges.
*/  

//iterative function/method to print graph:
void print(vector<int> a[],int V)
{
    for(int i=0;i<V;i++)
    {
        if(!a[i].empty())
            cout<<"i="<<i<<"-->";
        for(int j=0;j<a[i].size();j++)
            cout<<a[i][j]<<" ";
        if(!a[i].empty())
            cout<<endl;
    }
}

//recursive function/method to push vertices into stack passed as parameter: (referenced)
void push_vertex(int v,stack<int> &st,bool vis[],vector<int> adj[])
{
    vis[v]=true;
    for(auto i=adj[v].begin();i!=adj[v].end();i++)
    {
        if(vis[*i]==false)
            push_vertex(*i,st,vis,adj);
    }
    st.push(v);
}

//recursive function/method to implement depth first traversal(dfs):
void dfs(int v,bool vis[],vector<int> grev[])
{
    vis[v]=true;
    // cout<<v<<" ";
    for(auto i=grev[v].begin();i!=grev[v].end();i++)
    {
        if(vis[*i]==false)
            dfs(*i,vis,grev);
    }
}

//function/method to implement Kosaraju's Algorithm:
int kosaraju(int V, vector<int> adj[])
{
    bool vis[V]={};
    stack<int> st;
    for(int v=0;v<V;v++)
    {
        if(vis[v]==false)
            push_vertex(v,st,vis,adj);
    }
    //making new graph (grev) with reverse edges as in adj[]:
    vector<int> grev[V];
    for(int i=0;i<V+1;i++)
    {
        for(auto j=adj[i].begin();j!=adj[i].end();j++)
        {
            grev[*j].push_back(i);
        }
    }
    // cout<<"grev="<<endl; ->debug statement
    // print(grev,V);       ->debug statement
    //reinitialise visited to 0
    for(int i=0;i<V;i++)
        vis[i]=false;
    int count_scc=0;
    while(!st.empty())
    {
        int t=st.top();
        st.pop();
        if(vis[t]==false)
        {
            dfs(t,vis,grev);
            count_scc++;
        }
    }
    // cout<<"count_scc="<<count_scc<<endl; //in case you want to print here itself, uncomment & change return type of function to void.
    return count_scc;
}

//All critical/corner cases have been taken care of.
//Input your required values: (not hardcoded)
int main()
{
    int t;
    cin>>t; 
    while(t--)
    {
        int a,b ; //a->number of nodes, b->directed edges.
   	  cin>>a>>b;
   	  int m,n;
   	  vector<int> adj[a+1];
        for(int i=0;i<b;i++) //take total b inputs of 2 vertices each required to form an edge.
        {
            cin>>m>>n; //take input m,n denoting edge from m->n.
            adj[m].push_back(n);
        }
        //pass number of nodes and adjacency array as parameters to function:
        cout<<kosaraju(a, adj)<<endl;
    }
    return 0;
}
