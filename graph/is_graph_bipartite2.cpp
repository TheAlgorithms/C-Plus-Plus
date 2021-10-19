/**
 * @brief Check whether a given graph is bipartite or not
 * @details
 * Using a graph in the form of adjacency list, check whether the 
 * given graph is a bipartite or not.
 * 
 * References used: [GeeksForGeeks](https://www.geeksforgeeks.org/bipartite-graph/)
 * @author [tushar2407](https://github.com/tushar2407)
 */
#include <iostream> /// for IO operations
#include <queue>    /// for queue data structure
#include <vector>   /// for vector data structure
#include <cassert>  /// for assert

/**
 * @brief function to check whether the passed graph is bipartite or not
 * @param graph is a 2D matrix whose rows or the first index signify the node and values in that row signify the nodes it is connected to
 * @param index is the valus of the node currently under observation
 * @param visited is the vector which stores whether a given node has been traversed or not yet
 * @returns boolean
 */
bool checkBipartite(std::vector<std::vector<int64_t>> graph, int64_t index, std::vector<int64_t> visited)
{
    std::queue<int64_t> q; ///< stores the neighbouring node indexes in squence of being reached
    q.push(index);         /// insert the current node into the queue
    visited[index] = 1;    /// mark the current node as travelled
    while(q.size())
    {
        int64_t u = q.front();
        q.pop();
        for(int i=0;i<graph[u].size();i++)
        {
            int64_t v = graph[u][i];    ///< stores the neighbour of the current node
            if(!visited[v])             /// check whether the neighbour node is travelled already or not
            {
                visited[v] = (visited[u]==1)?-1:1;  /// colour the neighbouring node with different colour than the current node
                q.push(v);                          /// insert the neighbouring node into the queue
            }
            else if(visited[v] == visited[u])   /// if both the current node and its neighbour has the same state then it is not a bipartite graph
            {
                return false;
            }
        }
    }
    return true;    /// return true when all the connected nodes of the current nodes are travelled and satisify all the above conditions
}
/**
 * @brief returns true if the given graph is bipartite else returns false
 * @param graph is a 2D matrix whose rows or the first index signify the node and values in that row signify the nodes it is connected to
 * @returns booleans
 */
bool isBipartite(std::vector<std::vector<int64_t>> graph) 
{
    std::vector<int64_t> visited(graph.size()); ///< stores boolean values which signify whether that node had been visited or not
    
    for(int i=0;i<graph.size();i++)
    {    
        if(!visited[i]) /// if the current node is not visited then check whether the sub-graph of that node is a bipartite or not
        {
            if(!checkBipartite(graph, i, visited))
            {
                return false;
            }
        }
    }
    return true;
}
/**
 * @brief Self-test implementations
 * @returns void
 */
static void test()
{
    std::vector<std::vector<int64_t>> graph = {
        {1,3},
        {0,2},
        {1,3},
        {0,2}
    };

    assert(isBipartite(graph) == true); /// check whether the above defined graph is indeed bipartite

    std::vector<std::vector<int64_t>> graph_not_bipartite = {
        {1,2,3},
        {0,2},
        {0,1,3},
        {0,2}
    };

    assert(isBipartite(graph_not_bipartite) == false); /// check whether the above defined graph is indeed bipartite
}
/**
 * @brief Main function
 * Instantitates a dummy graph of a small size with 
 * a few edges between random nodes.
 * On applying the algorithm, it checks if the instantiated 
 * graph is bipartite or not.
 * @returns 0 on exit
 */
int main()
{
    test();  // run self-test implementations
    return 0;
}
