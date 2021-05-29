
/**
 * @file cycle_check_undirected graph.cpp
 *
 * @brief  Disjoint Set (Or Union-Find) algorithm to check for cycle in a undirected graph.
 *
 * @author [Ashish Jha](mailto:b.ashishjha13@gmail.com)
 *
 */

#include <iostream> // for std::cout
#include <utility>  // for std::pair
#include <vector>   // for std::vector

/**
 * Implementation of Graph class.
 * 
 * Check if a undirected graph has a cycle or not.
 *
 * This class provides 3 methods to check for cycle in a undirected graph:
 * find, union1 & hasCycle.
 *
 * - find method is used to find the parent of the node pass as one of the parameter of the method.
 * - union1 method is used to assign the parent.
 * - hasCycle method checks for every edge and calls find and union1 methods to check for cycle in a graph using Disjoint Set algorithm.
 */

class Graph
{
private:
      /** Helper function of "hasCycle".
       *
       * @param u is the node.
       * @param parent is the vector stores the parent of the nodes of the graph.
       * 
       * @return parent of the node else -1 if node is root node.
       */
      static int find(int u, std::vector<int> &parent)
      {
            // if u is the root node then return -1.
            if (parent[u] == -1)
            {
                  return u;
            }
            return find(parent[u], parent);
      }

      /** Helper function of "hasCycle".
       *
       * @param u is the first node.
       * @param v is the second node.
       * @param parent is the vector stores the parent of the nodes of the graph.
       * 
       * put the node u and v in the same set by making the parent of u and v same.
       */

      static void union1(int u, int v, std::vector<int> &parent)
      { //find the parent of u and v;
            u = find(u, parent);
            v = find(v, parent);
            // making the parent of u and v same
            parent[u] = v;
      }

public:
      /** Driver function to check if a graph has a cycle.
       *
       * This function uses Disjoint Set (Or Union-Find) to check for cycle in the graph.
       *
       * @param u and @param v are nodes of the edge which needs to be evaluated for the presence of cycle.
       * @return true if a cycle is detected, else false.
       */
      static bool hasCycle(int u, int v, std::vector<int> &parent)
      {
            /** checking if the parent of u and v are same are not.
             * if both nodes parent are same then this edges must create cycle in the grap
             * h.
             * hence return true;
             */
            if (find(u, parent) == find(v, parent))
            {
                  return true;
            }
            /** if the parent of both nodes are different then both belongs to diffrent set.
             * hence call the union1 method and return false.
             */
            union1(u, v, parent);
            return false;
      }
};

/**
 * Main function
 */
int main()
{
      // Initialise parent of every node to -1.
      std::vector<int> parent(5, -1);
      // Implementation of non-weighted undirected edges of a graph.
      std::vector<std::pair<int, int>> edges{{1, 2}, {2, 3}, {3, 0}, {3, 4}, {4, 1}};
      bool cycle = false;
      // loop through the edges to check the presence of cycle in the graph.
      for (int i = 0; i < edges.size(); ++i)
      {
            if (Graph::hasCycle(edges[i].first, edges[i].second, parent))
            {
                  /** if due to this edge graph contains cycle then make @param cycle true.
                   * and break;
                   */
                  std::cout << "The graph contains cycle\n";
                  cycle = true;
                  break;
            }
      }
      /** check whether the value of @param is false.
       * if false then the graph doesn't contain cylce.
       */
      if (!cycle)
            std::cout << "The graph doesn't contains cycle\n";
      return 0;
}
