#include "GRAPH.h"  /*  DO DOWNLOAD GRAPH.H USERDEFINED LIB TOO.*/
/**
 * @namespace graph
 * @brief Graph algorithms
 */
namespace graph {


/**
 * @file
 * @brief Implementation for [Tarjan's articulation points algorithm](https://en.wikipedia.org/wiki/Biconnected_component#Algorithms)
 * @author [Nisarg Pipaliya](https://github.com/NisargPipaliya)
 * @details From Wikipedia:
 * The classic sequential algorithm for computing biconnected components
 * in a connected undirected graph is due to John Hopcroft and Robert Tarjan (1973).
 * It runs in linear time, and is based on depth-first search.
 * The idea is to run a depth-first search while maintaining the following information:
 *      1.the depth of each vertex in the depth-first-search tree (once it gets visited), and
 *      2.for each vertex v, the lowest depth of neighbors of all descendants of v (including v itself) in the depth-first-search tree, called the lowpoint.
 */
/**
 * @brief Find articulation points with Tarjan's algorithm
 * @param tg Pointer to target graph
 * @param start_vertex Location to start the search
 * @param result Pointer to location to store the results
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

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
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
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main()
{
    test(); // Run self-test implementations
    return 0;
}
