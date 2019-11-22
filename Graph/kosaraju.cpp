/* Implementation of Kosaraju's Algorithm to find out the strongly connected components (SCCs) in a graph. 
   Author:Anirban166
*/   

#include<iostream>
#include<vector>

using namespace std;

/**
* Iterative function/method to print graph:
* @param a[] : array of vectors (2D)
* @param V : vertices
* @return void 
**/
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

/**
* //Recursive function/method to push vertices into stack passed as parameter:
* @param v : vertices
* @param &st : stack passed by reference
* @param vis[] : array to keep track of visited nodes (boolean type)
* @param adj[] : array of vectors to represent graph
* @return void 
**/
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


/**
* //Recursive function/method to implement depth first traversal(dfs):
* @param v : vertices
* @param vis[] : array to keep track of visited nodes (boolean type)
* @param grev[] : graph with reversed edges
* @return void 
**/
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
/**
* Info about the method
* @param V : vertices in graph
* @param adj[] : array of vectors that represent a graph (adjacency list/array)
* @return int ( 0, 1, 2..and so on, only unsigned values as either there can be no SCCs i.e. none(0) or there will be x no. of SCCs (x>0))
   i.e. it returns the count of (number of) strongly connected components (SCCs) in the graph. (variable 'count_scc' within function)
**/
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
