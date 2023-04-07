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
 
#include<iostream> ///< for general input and output
#include<vector> ///< for storing graph
#include<queue> ///< used for BFS algorithm in below namespace
#include<list>  ///< used for making adjacency list representation of graph
#include<set>   ///< for returning result of tarjan's agorithm

/**
 * @namespace graph
 * @brief Graph algorithms
 */
namespace graph {
class Graph
{
public:

    std::vector<std::list<std::pair<int, int>>> g;   ///< adjecency list to store graph
    int vertex;                                     ///< Total number of vertices in graph
    bool isDirected = false;                        ///< to check is graph is directed or not
    int flag=0;                                     ///< to check if graph is directed or not
    std::vector<std::pair<int, int>> allEdges;         ///< for keeping track of all edges used for cycle detection.
    std::vector<std::pair<int,std::pair<int,int> >> allWEdges;         ///<it stores weight and vertex of edges.

    /**
     * @brief Constructor for Graph Class
     * @param default_vertex -> formal argument that sets default vertex
     * @returns void
    */
    explicit Graph(int default_vertex = 10)      
    {
        g.resize(vertex);               ///< resizing the adjecency list
        this->vertex=default_vertex;    ///< setting value of class variable.
    }

    /**
     * @brief add edges to the graph
     * @param uvertex -> formal argument that represents source vertex
     * @param vvertex -> formal argument that represents destination  vertex
     * @param weight -> if we need to add weighted undirected edge
     * @returns void
     */
    void addEdge(int uvertex, int vvertex, int weight = 0)          ///< if graph is undirected then this function is called.
    {                                                              ///<  formal arguments uvertex,vvertex -> it suggest that there exists edge between this two vertices, weight is used if graph is weighted.
        if(isDirected) {            ///< here it checks that if we have made directed graph then it would not allow us to add an undirected edge
        return;     
        }

        allEdges.emplace_back(uvertex,vvertex); ///< adding edge to the vector
        allWEdges.emplace_back(weight,std::make_pair(uvertex, vvertex));  ///< adding edge to the vector

        flag=1;
        g[uvertex].emplace_back(std::make_pair(vvertex, weight));  ///< adding edge to the adjcency list
        g[vvertex].emplace_back(std::make_pair(uvertex, weight));  ///< adding edge to adjcency list
    }

    
    /*
                                DIRECTED GRAPH
    */
    /**
     * @brief add directed edges to the graph
     * @param uvertex -> formal argument that represents source vertex
     * @param vvertex -> formal argument that represents destination  vertex
     * @param weight -> if we need to add weighted directed edge
     * @returns void
     */
    void addDirectedEdge(int uvertex, int vvertex, int weight = 0) ///< use when we need to directed graph
    {
        if(!isDirected && flag!=0)      ///< if graph is undirected and we try to add directed edge then return and it is not first edge
        {
            return;
        }
        allEdges.emplace_back(
            std::make_pair(uvertex, vvertex));  ///< adding edge to the vector
        allWEdges.emplace_back(std::make_pair(
            weight,
            std::make_pair(uvertex, vvertex)));  ///< adding edge to the vector

        isDirected=true;
        g[uvertex].emplace_back(std::make_pair(vvertex, weight)); ///< adding edge to adjcency list
    }


    /**
     * @brief returns a vector containing list of nodes, in order in which they are encountered in BFS call
     * @param start_vertex formal argument that represents the starting vertex for BFS
     * @returns vector<int>
    */
    std::vector<int> BFS(int start_vertex) {
        std::vector<int> ans;  ///< This vector will hold the BFS result
        std::vector<bool> visited(vertex,false);  ///< This vector will keep track of visited vertices
        std::queue<int> q;  ///< This queue will keep track of vertices to visit next
        q.push(start_vertex);  ///< Add the starting vertex to the queue
        visited[start_vertex] = true;  ///< Mark the starting vertex as visited in the visited vector

        while (!q.empty())  ///< As long as there are vertices left to explore
        {
            int u = q.front();    ///< Get the vertex from the front of the queue
            ans.emplace_back(u);  ///< Add it to the BFS result vector
            q.pop();              ///< Remove it from the queue
            for (auto i : g[u])  ///< Explore all vertices adjacent to the current vertex
            {
                if (visited[i.first] ==  false)  ///< If the vertex has not been visited before
                {
                    q.push(i.first);  ///< Add it to the queue
                    visited[i.first] = true;  ///< Mark it as visited in the visited vector
                }
            }
        }
        return ans;  ///< Return the BFS result vector
    }

    /**
     * @brief This function implements a Depth First Search (DFS) algorithm.
     * @param start_vertex represents the starting vertex for dfs call
     * @param result it will contain the list of nodes that are visited in a dfs call
     * @returns void
     */

    void DFS(int start_vertex, std::vector<int> &result) {
        static std::vector<bool> visited(vertex, false);  ///< This vector will keep track of visited vertices
        visited[start_vertex] = true;  ///< Mark the starting vertex as visited
        result.emplace_back(start_vertex);  ///< Add the starting vertex to the DFS result vector

        for (auto i : g[start_vertex])  ///< Explore all vertices adjacent to the current vertex
        {
            if (!visited[i.first])  ///< If the vertex has not been visited before
            {
                DFS(i.first,result);  ///< Recursively call DFS on the unvisited vertex
            }
        }
    }
};

}

// // This function implements Tarjan's algorithm to find articulation points in
// an undirected graph represented using an adjacency list

void tarjans_ap(graph::Graph &tg, int start_vertex, std::set<int> &result) {
    static std::vector<bool> visited(tg.vertex, false);  ///< This vector will keep track of visited vertices
    static std::vector<int> discovery_time( tg.vertex,0);  ///< This vector will store the time of discovery of each vertex
    static std::vector<int> low_time(tg.vertex, 0);  ///< This vector will store the lowest discovery time of a vertex that can be reached from the current vertex
    static std::vector<int> parent(tg.vertex,-1);  ///< This vector will store the parent of each vertex in the DFS tree
    static int time = 1;  ///< This variable will keep track of the current time  during the DFS traversal

    visited[start_vertex] = true;
    int child = 0;  ///< This variable will count the number of children of the
                    ///< current vertex in the DFS tree

    low_time[start_vertex] = discovery_time[start_vertex] =time++;  ///< Update the discovery and low times for the starting vertex

    for (auto it : tg.g[start_vertex])  ///< Explore all vertices adjacent to the current vertex
    {
        if (visited[it.first] == false)  ///< If the vertex has not been visited before
        {
            child++;  ///< Increment the number of children of the current vertex
            parent[it.first] = start_vertex;  ///< Set the parent of the adjacent vertex in the DFS tree to the current vertex
            tarjans_ap(tg, it.first,result);  ///< Recursively call Tarjan's algorithm on the adjacent vertex

            ///< Update the low time of the current vertex based on the low time of the adjacent vertex
            low_time[start_vertex] = std::min(low_time[it.first], low_time[start_vertex]);

            ///< Check if the current vertex is an articulation point
            if (parent[start_vertex] == -1 && child > 1)  ///< Case 1: If the current vertex is the root of the DFS tree and has more than one child
            {
                result.insert(start_vertex);  ///< Add the current vertex to the
                                              ///< set of articulation points
            } else if (parent[start_vertex] != -1 &&
                       discovery_time[start_vertex] <= low_time[it.first])  ///< Case 2: If the current vertex is not the root of the DFS tree and there is no back edge from any of its descendants to a proper ancestor of the current vertex
            {
                result.insert(start_vertex);  ///< Add the current vertex to the set of articulation points
            }
        } else if (it.first !=parent[start_vertex])  ///< If the adjacent vertex has been visited before and it is not the parent of the current vertex in the DFS tree
        {
            ///< Update the low time of the current vertex based on the discovery time of the adjacent vertex
            low_time[start_vertex] = std::min(low_time[start_vertex], discovery_time[it.first]);
        }
    }
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    ///< Define an empty set called "result"
    std::set<int> result;
    ///< Define a Graph object called "tarjan" with 7 nodes
    graph::Graph tarjan(7);

    ///< Add edges to the graph
    tarjan.addEdge(0, 1);
    tarjan.addEdge(0, 3);
    tarjan.addEdge(1, 2);
    tarjan.addEdge(2, 3);
    tarjan.addEdge(2, 6);
    tarjan.addEdge(3, 4);
    tarjan.addEdge(3, 5);
    tarjan.addEdge(4, 5);

    ///< Print a message to the console
    std::cout << "BFS" << std::endl;
    ///< Call the BFS method of the Graph object with a starting vertex of 0
    std::vector<int> bfs = tarjan.BFS(0);

    ///< Loop through the BFS result and print each vertex
    for (auto i : bfs) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    ///< Print a message to the console
    std::cout << "DFS" << std::endl;
    ///< Define an empty vector called "dfs"
    std::vector<int> dfs;
    ///< Call the DFS method of the Graph object with a starting vertex of 0 and
    ///< pass the "dfs" vector by reference
    tarjan.DFS(0, dfs);
    ///< Loop through the DFS result and print each vertex
    for (auto i : dfs) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    ///< Print a message to the console
    std::cout << "Articulation Points By Tarjan's Algorithm : " << std::endl;
    ///< Call the "tarjans_ap" function with the Graph object, a starting vertex
    ///< of 0, and the "result" set by reference
    tarjans_ap(tarjan, 0, result);
    ///< Loop through the result set and print each articulation point
    for (auto i : result) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main()
{
    test(); ///< Run self-test implementations
    return 0;
}
