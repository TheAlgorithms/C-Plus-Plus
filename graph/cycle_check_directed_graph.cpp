/**
 * @file cycle_check_directed graph.cpp
 *
 * @brief BFS and DFS algorithms to check for cycle in a directed graph.
 *
 * @author [Anmol3299](mailto:mittalanmol22@gmail.com)
 *
 */

#include <iostream>     // for std::cout
#include <map>          // for std::map
#include <queue>        // for std::queue
#include <stdexcept>    // for throwing errors
#include <type_traits>  // for std::remove_reference
#include <utility>      // for std::move
#include <vector>       // for std::vector

/**
 * Implementation of non-weighted directed edge of a graph.
 *
 * The source vertex of the edge is labelled "src" and destination vertex is
 * labelled "dest".
 */
struct Edge {
    unsigned int src;
    unsigned int dest;

    Edge() = delete;
    ~Edge() = default;
    Edge(Edge&&) = default;
    Edge& operator=(Edge&&) = default;
    Edge(Edge const&) = default;
    Edge& operator=(Edge const&) = default;

    /** Set the source and destination of the vertex.
     *
     * @param source is the source vertex of the edge.
     * @param destination is the destination vertex of the edge.
     */
    Edge(unsigned int source, unsigned int destination)
        : src(source), dest(destination) {}
};

using AdjList = std::map<unsigned int, std::vector<unsigned int>>;

/**
 * Implementation of graph class.
 *
 * The graph will be represented using Adjacency List representation.
 * This class contains 2 data members "m_vertices" & "m_adjList" used to
 * represent the number of vertices and adjacency list of the graph
 * respectively. The vertices are labelled 0 - (m_vertices - 1).
 */
class Graph {
 public:
    Graph() : m_adjList({}) {}
    ~Graph() = default;
    Graph(Graph&&) = default;
    Graph& operator=(Graph&&) = default;
    Graph(Graph const&) = default;
    Graph& operator=(Graph const&) = default;

    /** Create a graph from vertices and adjacency list.
     *
     * @param vertices specify the number of vertices the graph would contain.
     * @param adjList is the adjacency list representation of graph.
     */
    Graph(unsigned int vertices, AdjList adjList)
        : m_vertices(vertices), m_adjList(std::move(adjList)) {}

    /** Create a graph from vertices and adjacency list.
     *
     * @param vertices specify the number of vertices the graph would contain.
     * @param adjList is the adjacency list representation of graph.
     */
    Graph(unsigned int vertices, AdjList&& adjList)
        : m_vertices(vertices), m_adjList(std::move(adjList)) {}

    /** Create a graph from vertices and a set of edges.
     *
     * Adjacency list of the graph would be created from the set of edges. If
     * the source or destination of any edge has a value greater or equal to
     * number of vertices, then it would throw a range_error.
     *
     * @param vertices specify the number of vertices the graph would contain.
     * @param edges is a vector of edges.
     */
    Graph(unsigned int vertices, std::vector<Edge> const& edges)
        : m_vertices(vertices) {
        for (auto const& edge : edges) {
            if (edge.src >= vertices || edge.dest >= vertices) {
                throw std::range_error(
                    "Either src or dest of edge out of range");
            }
            m_adjList[edge.src].emplace_back(edge.dest);
        }
    }

    /** Return a const reference of the adjacency list.
     *
     * @return const reference to the adjacency list
     */
    std::remove_reference<AdjList>::type const& getAdjList() const {
        return m_adjList;
    }

    /**
     * @return number of vertices in the graph.
     */
    unsigned int getVertices() const { return m_vertices; }

    /** Add vertices in the graph.
     *
     * @param num is the number of vertices to be added. It adds 1 vertex by
     * default.
     *
     */
    void addVertices(unsigned int num = 1) { m_vertices += num; }

    /** Add an edge in the graph.
     *
     * @param edge that needs to be added.
     */
    void addEdge(Edge const& edge) {
        if (edge.src >= m_vertices || edge.dest >= m_vertices) {
            throw std::range_error("Either src or dest of edge out of range");
        }
        m_adjList[edge.src].emplace_back(edge.dest);
    }

    /** Add an Edge in the graph
     *
     * @param source is source vertex of the edge.
     * @param destination is the destination vertex of the edge.
     */
    void addEdge(unsigned int source, unsigned int destination) {
        if (source >= m_vertices || destination >= m_vertices) {
            throw std::range_error(
                "Either source or destination of edge out of range");
        }
        m_adjList[source].emplace_back(destination);
    }

 private:
    unsigned int m_vertices = 0;
    AdjList m_adjList;
};

/**
 * Check if a directed graph has a cycle or not.
 *
 * This class provides 2 methods to check for cycle in a directed graph:
 * isCyclicDFS & isCyclicBFS.
 *
 * - isCyclicDFS uses DFS traversal method to check for cycle in a graph.
 * - isCyclidBFS used BFS traversal method to check for cycle in a graph.
 */
class CycleCheck {
 private:
    enum nodeStates : uint8_t { not_visited = 0, in_stack, visited };

    /** Helper function of "isCyclicDFS".
     *
     * @param adjList is the adjacency list representation of some graph.
     * @param state is the state of the nodes of the graph.
     * @param node is the node being evaluated.
     *
     * @return true if graph has a cycle, else false.
     */
    static bool isCyclicDFSHelper(AdjList const& adjList,
                                  std::vector<nodeStates>* state,
                                  unsigned int node) {
        // Add node "in_stack" state.
        (*state)[node] = in_stack;

        // If the node has children, then recursively visit all children of the
        // node.
        auto const it = adjList.find(node);
        if (it != adjList.end()) {
            for (auto child : it->second) {
                // If state of child node is "not_visited", evaluate that child
                // for presence of cycle.
                auto state_of_child = (*state)[child];
                if (state_of_child == not_visited) {
                    if (isCyclicDFSHelper(adjList, state, child)) {
                        return true;
                    }
                } else if (state_of_child == in_stack) {
                    // If child node was "in_stack", then that means that there
                    // is a cycle in the graph. Return true for presence of the
                    // cycle.
                    return true;
                }
            }
        }

        // Current node has been evaluated for the presence of cycle and had no
        // cycle. Mark current node as "visited".
        (*state)[node] = visited;
        // Return that current node didn't result in any cycles.
        return false;
    }

 public:
    /** Driver function to check if a graph has a cycle.
     *
     * This function uses DFS to check for cycle in the graph.
     *
     * @param graph which needs to be evaluated for the presence of cycle.
     * @return true if a cycle is detected, else false.
     */
    static bool isCyclicDFS(Graph const& graph) {
        auto vertices = graph.getVertices();

        /** State of the node.
         *
         * It is a vector of "nodeStates" which represents the state node is in.
         * It can take only 3 values: "not_visited", "in_stack", and "visited".
         *
         * Initially, all nodes are in "not_visited" state.
         */
        std::vector<nodeStates> state(vertices, not_visited);

        // Start visiting each node.
        for (unsigned int node = 0; node < vertices; node++) {
            // If a node is not visited, only then check for presence of cycle.
            // There is no need to check for presence of cycle for a visited
            // node as it has already been checked for presence of cycle.
            if (state[node] == not_visited) {
                // Check for cycle.
                if (isCyclicDFSHelper(graph.getAdjList(), &state, node)) {
                    return true;
                }
            }
        }

        // All nodes have been safely traversed, that means there is no cycle in
        // the graph. Return false.
        return false;
    }

    /** Check if a graph has cycle or not.
     *
     * This function uses BFS to check if a graph is cyclic or not.
     *
     * @param graph which needs to be evaluated for the presence of cycle.
     * @return true if a cycle is detected, else false.
     */
    static bool isCyclicBFS(Graph const& graph) {
        auto graphAjdList = graph.getAdjList();
        auto vertices = graph.getVertices();

        std::vector<unsigned int> indegree(vertices, 0);
        // Calculate the indegree i.e. the number of incident edges to the node.
        for (auto const& list : graphAjdList) {
            auto children = list.second;
            for (auto const& child : children) {
                indegree[child]++;
            }
        }

        std::queue<unsigned int> can_be_solved;
        for (unsigned int node = 0; node < vertices; node++) {
            // If a node doesn't have any input edges, then that node will
            // definately not result in a cycle and can be visited safely.
            if (!indegree[node]) {
                can_be_solved.emplace(node);
            }
        }

        // Vertices that need to be traversed.
        auto remain = vertices;
        // While there are safe nodes that we can visit.
        while (!can_be_solved.empty()) {
            auto solved = can_be_solved.front();
            // Visit the node.
            can_be_solved.pop();
            // Decrease number of nodes that need to be traversed.
            remain--;

            // Visit all the children of the visited node.
            auto it = graphAjdList.find(solved);
            if (it != graphAjdList.end()) {
                for (auto child : it->second) {
                    // Check if we can visited the node safely.
                    if (--indegree[child] == 0) {
                        // if node can be visited safely, then add that node to
                        // the visit queue.
                        can_be_solved.emplace(child);
                    }
                }
            }
        }

        // If there are still nodes that we can't visit, then it means that
        // there is a cycle and return true, else return false.
        return !(remain == 0);
    }
};

/**
 * Main function.
 */
int main() {
    // Instantiate the graph.
    Graph g(7, std::vector<Edge>{{0, 1}, {1, 2}, {2, 0}, {2, 5}, {3, 5}});
    // Check for cycle using BFS method.
    std::cout << CycleCheck::isCyclicBFS(g) << '\n';

    // Check for cycle using DFS method.
    std::cout << CycleCheck::isCyclicDFS(g) << '\n';
    return 0;
}
