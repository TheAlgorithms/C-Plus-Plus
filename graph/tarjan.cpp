#include "GRAPH.h"  /*  DO DOWNLOAD GRAPH.H USERDEFINED LIB TOO.*/
using namespace std;


/*
AUTHOR -> NISARG PIPALIYA
ALGORITHM -> TARJAN'S ARTICULATION POINT ALGORITHM

here in tarjan's algorithm to find articulation point we are searching for backedges in graph.
here the discovery time array keeps track of the vertex we are visiting by assigning discovery time to it that is just a variable having 
of number of vertex we visited and from low_time array we come to know that the vertex we are visiting was that previously visited by us?
if yes then low_time[i] < discovery_time[i] which means back-edge exists and this current vertex is not articulation point.
*/

void tarjans_ap(graph&tg,int start_vertex,set<int> &result)
{
    static vector<bool> visited(tg.vertex,false);
    static vector<int> discovery_time(tg.vertex,0);
    static vector<int> low_time(tg.vertex,0);
    static vector<int> parent(tg.vertex,-1);
    static int time=1;

    visited[start_vertex]=true;
    int child=0;
    low_time[start_vertex]=discovery_time[start_vertex]=time++;

    for(auto it : tg.g[start_vertex])
    {
        if(visited[it.first]==false)
        {
            child++;
            parent[it.first]=start_vertex;
            tarjans_ap(tg,it.first,result);

            low_time[start_vertex] = min(low_time[it.first],low_time[start_vertex]);

            if(parent[start_vertex]==-1 && child>1)
            result.insert(start_vertex);
            else if(parent[start_vertex]!=-1 && discovery_time[start_vertex]<=low_time[it.first])
            result.insert(start_vertex);
        }
        else if(it.first!=parent[start_vertex])
        low_time[start_vertex]=min(low_time[start_vertex],discovery_time[it.first]);
    }
}

int main(void)
{
    set<int> result;
    graph tarjan(7);

    tarjan.addEdge(0,1);
    tarjan.addEdge(0,3);
    tarjan.addEdge(1,2);
    tarjan.addEdge(2,3);
    tarjan.addEdge(2,6);
    tarjan.addEdge(3,4);
    tarjan.addEdge(3,5);
    tarjan.addEdge(4,5);

    cout<<"BFS"<<endl;
    vector<int>bfs = tarjan.BFS(0);

    for(auto i : bfs)
    {
        cout<<i<<" ";
    }
    cout<<endl;

    cout<<"DFS"<<endl;
    vector<int> dfs;
    tarjan.DFS(0,dfs);
    for(auto i : dfs)
    {
        cout<<i<<" ";
    }
    cout<<endl;
    

    cout<<"Articulation Points By Tarjan's Algorithm : "<<endl;
    
    tarjans_ap(tarjan,0,result);
    for(auto i : result)
    {
        cout<<i<<" ";
    }
    cout<<endl;

    return 0;
}
