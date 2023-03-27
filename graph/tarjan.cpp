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
 
#include<iostream> /// for general input and output
#include<vector> /// for storing graph
#include<queue> /// used for BFS algorithm in below namespace
#include<list>  /// used for making adjacency list representation of graph
#include<set>   /// for returning result of tarjan's agorithm

/**
 * @namespace graph
 * @brief Graph algorithms
 */
namespace graph {
class Graph
{
public:

    std::vector<std::list<std::pair<int, int>>> g;   // adjecency list to store graph
    int vertex;                                     // Total number of vertices in graph
    bool isDirected=false;                          // to check is graph is directed or not
    int flag=0;                                 
    std::vector<std::pair<int,int>> allEdges;                           // for keeping track of all edges used for cycle detection.
    std::vector<std::pair<int,std::pair<int,int> >> allWEdges;         //it stores weight and vertex of edges.


    explicit Graph(int default_vertex = 10)      // Constructor for Graph Class, default_vertex -> formal argument that sets default vertex size.
    {
        g.resize(vertex);               // resizing the adjecency list
        this->vertex=default_vertex;    // setting value of class variable.
    }

    /*
                                UNDIRECTED GRAPH
    */

    void addEdge(int uvertex, int vvertex, int weight = 0)          // if graph is undirected then this function is called.
    {                                                              //  formal arguments uvertex,vvertex -> it suggest that there exists edge between this two vertices, weight is used if graph is weighted.
        if(isDirected) {            
        return;
        }

        allEdges.emplace_back(uvertex,vvertex);
        
        allWEdges.emplace_back(weight,std::make_pair(uvertex,vvertex));
        
        flag=1;
        g[uvertex].emplace_back(std::make_pair(vvertex, weight));
        g[vvertex].emplace_back(std::make_pair(uvertex, weight));
    }

    
    /*
                                DIRECTED GRAPH
    */

    void addDirectedEdge(int uvertex, int vvertex, int weight = 0) // use when we need to directed graph
    {
        if(!isDirected && flag!=0)
        {
            return;
        }
        
        allEdges.emplace_back(std::make_pair(uvertex,vvertex));
       
            allWEdges.emplace_back(std::make_pair(weight,std::make_pair(uvertex,vvertex)));

        isDirected=true;
        g[uvertex].emplace_back(std::make_pair(vvertex, weight));
    }

    std::vector<int> BFS(int start_vertex)
    {
        std::vector<int> ans;
        std::vector<bool> visited(vertex,false);
        std::queue<int> q;
        q.push(start_vertex);
        visited[start_vertex]=true;

        while(!q.empty())
        {
            int u=q.front();
            ans.emplace_back(u);
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
    void DFS(int start_vertex , std::vector<int> &result)
    {
        static std::vector<bool> visited(vertex,false);
        visited[start_vertex]=true;
        result.emplace_back(start_vertex);

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
        std::cout<<"This graph follows adjacency list representation as vector< list< pair<int,int> > > \n here int pair first is vertex and second is weight of that vertex by default it is zero."<<std::endl;
        std::cout<<"Number of vertices : "<<vertex<<std::endl;

        for(const auto& i:g)
        {
            for(auto j : i)
            {
             std::cout<<"Vertex "<<j.first<<" Weight "<<j.second<<std::endl;
            }
        }
    }

};

}

void tarjans_ap(graph::Graph&tg,int start_vertex,std::set<int> &result)
{
    static std::vector<bool> visited(tg.vertex,false);
    static std::vector<int> discovery_time(tg.vertex,0);
    static std::vector<int> low_time(tg.vertex,0);
    static std::vector<int> parent(tg.vertex,-1);
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

            low_time[start_vertex] = std::min(low_time[it.first],low_time[start_vertex]);

            if(parent[start_vertex]==-1 && child>1)
            {
                result.insert(start_vertex);
            }
            else if(parent[start_vertex]!=-1 && discovery_time[start_vertex]<=low_time[it.first])
            {
                result.insert(start_vertex);
            }
        }
        else if(it.first!=parent[start_vertex])
        {
            low_time[start_vertex] = std::min(low_time[start_vertex],discovery_time[it.first]);
        }
    }
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    std::set<int> result;
    graph::Graph tarjan(7);

    tarjan.addEdge(0,1);
    tarjan.addEdge(0,3);
    tarjan.addEdge(1,2);
    tarjan.addEdge(2,3);
    tarjan.addEdge(2,6);
    tarjan.addEdge(3,4);
    tarjan.addEdge(3,5);
    tarjan.addEdge(4,5);

    std::cout<<"BFS"<<std::endl;
    std::vector<int>bfs = tarjan.BFS(0);

    for(auto i : bfs)
    {
        std::cout<<i<<" ";
    }
    std::cout<<std::endl;

    std::cout<<"DFS"<<std::endl;
    std::vector<int> dfs;
    tarjan.DFS(0,dfs);
    for(auto i : dfs)
    {
        std::cout<<i<<" ";
    }
    std::cout<<std::endl;


    std::cout<<"Articulation Points By Tarjan's Algorithm : "<<std::endl;

    tarjans_ap(tarjan,0,result);
    for(auto i : result)
    {
        std::cout<<i<<" ";
    }
    std::cout<<std::endl;
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
