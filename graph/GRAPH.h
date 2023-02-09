#include<iostream>
#include<vector>
#include<queue>
#include<list>
#include<tuple>
#include<set>


#ifndef GRAPH_h
#define GRAPH_h

class graph
{
public:

    vector<list<pair<int, int>>> g;
    int vertex;
    bool isDirected=false;
    int flag=0;
    vector<pair<int,int>> allEdges; // for keeping track of all edges used for cycle detection.
    vector<pair<int,pair<int,int> >> allWEdges; //it stores weight and vertex of edges.


    graph(int default_vertex = 10)
    {
        vertex = default_vertex;
        g.resize(vertex);
        // visited.resize(vertex);
    }

    /*
                                UNDIRECTED GRAPH
    */

    void addEdge(int uvertex, int vvertex, int weight = 0)
    {
        if(isDirected==true)
        return;

        allEdges.push_back(make_pair(uvertex,vvertex));
        
        allWEdges.push_back(make_pair(weight,make_pair(uvertex,vvertex)));
        
        flag=1;
        g[uvertex].push_back(make_pair(vvertex, weight));
        g[vvertex].push_back(make_pair(uvertex, weight));
    }

    
    /*
                                DIRECTED GRAPH
    */

    void addDirectedEdge(int uvertex, int vvertex, int weight = 0) // use when we need to directed graph
    {
        if(!isDirected && flag!=0)
        return;
        
        allEdges.push_back(make_pair(uvertex,vvertex));
       
            allWEdges.push_back(make_pair(weight,make_pair(uvertex,vvertex)));

        isDirected=true;
        g[uvertex].push_back(make_pair(vvertex, weight));
    }

    vector<int> BFS(int start_vertex)
    {
        vector<int> ans;
        vector<bool> visited(vertex,false);
        queue<int> q;
        q.push(start_vertex);
        visited[start_vertex]=true;

        while(!q.empty())
        {
            int u=q.front();
            ans.push_back(u);
            q.pop();
            for(auto i : g[u])
            {
                if(visited[i.first]==false)
                {
                    q.push(i.first);
                    visited[i.first]=true;
                }
            }
        }
        return ans;
    }
    void DFS(int start_vertex , vector<int> &result)
    {
        static vector<bool> visited(vertex,false);
        visited[start_vertex]=true;
        result.push_back(start_vertex);

        for(auto i : g[start_vertex])
        {
            if(!visited[i.first])
            {
                DFS(i.first,result);
            }
        }
    }
    void getInfo()
    {
        cout<<"This graph follows adjacency list representation as vector< list< pair<int,int> > > \n here int pair first is vertex and second is weight of that vertex by default it is zero."<<endl;
        cout<<"Number of vertices : "<<vertex<<endl;

        for(const auto& i:g)
        {
            for(auto j : i)
            {
                cout<<"Vertex "<<j.first<<" Weight "<<j.second<<endl;
            }
        }
    }

};

#endif
