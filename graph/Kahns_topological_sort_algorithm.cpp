/**
 * \brief 
 * A Topological sort or Topological ordering of a directed graph is a linear ordering of its vertices such that for
 * every directed edge uv from vertex u to vertex v, u comes before v in the ordering. Topological order is possible if and
 * only if the graph has no directed cycles, i.e. if the graph is DAG.
 * Kahn’s topological sort algorithm works by finding vertices with no incoming edges and removing all outgoing edges 
 * from these vertices.
 * \details 
 * Kahn’s - Algorithm (graph)
 * L —> An empty list that will contain the sorted elements
 * S —> A set of all vertices with no incoming edges (i.e., having indegree 0)
 * 
 *  while S is non-empty do
 *      remove a vertex n from S
 *      add n to tail of L
 *      for each vertex m with an edge e from n to m do
 *           remove edge e from the graph
 *          if m has no other incoming edges, then insert m into S
 *          insert m into S
 *
 * 
 *  if graph has edges then
 *      return report “graph has at least one cycle”
 *  else
 *      return L “a topologically sorted order”
 * 
 */
#include <iostream>
#include <vector>
using namespace std;

/** structure to store edges of a graph */
struct Edge {
    int src, dest;
};

/** structure to represent graph */
class Graph
{
public:
/** vector of vector to represent adjacency list */
    vector<vector<int>> adjList;

/** stores indegree of a vertex */
    vector<int> indegree;

/**
 * @brief Graph constructor
 * @param edges 
 * @param n 
 * @return Graph 
 */
    Graph(vector<Edge> const &edges, int n)
    {
        // resize the vector to hold `n` elements of type `vector<int>`
        adjList.resize(n);

        // initialize indegree
        vector<int> temp(n, 0);
        indegree = temp;

        // add edges to the directed graph
        for (auto &edge: edges)
        {
            // add an edge from source to destination
            adjList[edge.src].push_back(edge.dest);

            // increment in-degree of destination vertex by 1
            indegree[edge.dest]++;
        }
    }
};

/**
 * @brief stores indegree of a vertex
 * @param graph 
 * @return  Function 
 */
vector<int> doTopologicalSort(Graph const &graph)
{
    vector<int> L;

    // get the total number of nodes in the graph
    int n = graph.adjList.size();

    vector<int> indegree = graph.indegree;

    // Set of all nodes with no incoming edges
    vector<int> S;
    for (int i = 0; i < n; i++)
    {
        if (!indegree[i]) {
            S.push_back(i);
        }
    }

    while (!S.empty())
    {
        // remove node `n` from `S`
        int n = S.back();
        S.pop_back();

        // add `n` at the tail of `L`
        L.push_back(n);

        for (int m: graph.adjList[n])
        {
            // remove an edge from `n` to `m` from the graph
            indegree[m] -= 1;

            // if `m` has no other incoming edges, insert `m` into `S`
            if (!indegree[m]) {
                S.push_back(m);
            }
        }
    }

    /** if a graph has edges, then the graph has at least one cycle */
    for (int i = 0; i < n; i++)
    {
        if (indegree[i]) {
            return {};
        }
    }

    return L;
}

int main()
{
    /**
     * @brief  vector of graph edges
     */
    vector<Edge> edges =
    {
        { 0, 6 }, { 1, 2 }, { 1, 4 }, { 1, 6 }, { 3, 0 }, { 3, 4 },
        { 5, 1 }, { 7, 0 }, { 7, 1 }
    };

    // total number of nodes in the graph (labelled from 0 to 7)
    int n = 8;

    /**
     * @brief build a graph from the given edges
     * @params edges , n
     * @return Graph
     */
    Graph graph(edges, n);

    /**
     * @brief Perform topological sort
     * @param graph
     * @return vector
     */
    vector<int> L = doTopologicalSort(graph);

    /**
     * @brief print topological order
     * 
     */
    if (L.size()) {
        for (int i: L) {
            cout << i << " ";
        }
    } else {
        cout << "Graph has at least one cycle. Topological sorting is not possible";
    }

    return 0;
}
