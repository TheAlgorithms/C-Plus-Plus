/**
 * @file
 * @brief [Heavy Light
 * Decomposition](https://en.wikipedia.org/wiki/Heavy_path_decomposition)
 * implementation
 * @author [Aniruthan R](https://github.com/aneee004)
 *
 * @details
 * Heavy-Light Decomposition is a technique on trees, that supports the
 * following:
 * 1. Update node s, with a value v
 * 2. Return the (sum) of all node values on the simple path from a to b
 * (sum) can also be replced with XOR, OR, AND, min, or max
 *
 * The update is done in O(log n) time, and
 * the query is done in O(log^2 n) time with HLD
 * where, n is the number of nodes
 *
 * The template type is the data type of the value stored in the nodes.
 * If a non-primitive data-type is used as a template,
 * the coressponding operators must be overloaded.
 *
 * An HLD object can only be created with a constant number of nodes, and
 * it cannot be changed later. Creaty an empty instance is not supported.
 *
 * To start answering updates and queries,
 * 1. Create an instance of HLD<X> object (obj), with the required data type.
 * 2. Read in the edge/parent information and update it with obj.add_edge().
 * Note: The edges addes must be 0 indexed.
 * 3. Create a vector with initial node values, and call set_node_val() with it.
 * 4. Call obj.init() to populate the required information for supporting
 * operations.
 * 5. Call obj.update(node, new_val), to update the value at index 'node' to the
 * new value. Note: node must be 0 indexed
 * 6. Call obj.query(a, b) to get the (sum) of node values in the simple path
 * from a to b. Note: a and b, must be 0 indexed.
 *
 * Sample I/O at the bottom.
 * @todo Support edge weight queries, by storing the edge weight value in it's
 * child algorithm verified by testing in CSES path queries:
 * https://cses.fi/problemset/task/1138
 */

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
#include <list>
#include <numeric>
#include <string>
#include <vector>

/**
 * @namespace range_queries
 * @brief Algorithms and Data Structures that support range queries and updates.
 */
namespace range_queries {
/**
 * @namespace heavy_light_decomposition
 * @brief Heavy light decomposition algorithm
 */
namespace heavy_light_decomposition {
/**
 * @brief A Basic Tree, which supports binary lifting
 * @tparam the data type of the values stored in the tree nodes
 * @details Deleting the default constructor
 * An instance can only be created with the number of nodes
 * Defaults:
 * t_node indexing are zero based
 * t_root is 0
 * depth of root_node is 0
 * Supports:
 * lift :- lift a node k units up the tree
 * kth_ancestor :- returns the kth ancestor
 * lca :- returns the least common ancestor
 */
template <typename X> class Tree {
  //

private:
  std::vector<std::list<int>>
      t_adj;         ///< an adjacency list to stores the tree edges
  const int t_nodes, ///< number of nodes
      t_maxlift;     ///< maximum possible height of the tree
  std::vector<std::vector<int>>
      t_par;                ///< a matrix to store every node's 2^kth parent
  std::vector<int> t_depth, ///< a vector to store the depth of a node,
      t_size; ///< a vector to store the subtree size rooted at node

  int t_root;           ///< the root of the tree
  std::vector<X> t_val; ///< values of nodes
  template <typename T> friend class HLD;

  /**
   * @brief Utility function to compute sub-tree sizes
   * @param u current dfs node
   * @param p the parent of node @param u
   * @returns void
   */
  void dfs_size(int u, int p = -1) {
    for (const int &v : t_adj[u]) {
      if (v ^ p) {
        dfs_size(v, u);
        t_size[u] += t_size[v];
      }
    }
  }

  /**
   * @brief Utility function to populate the t_par vector
   * @param u current dfs node
   * @param p the parent of node u
   * @returns void
   */
  void dfs_lca(int u, int p = -1) {
    t_par[u][0] = p;
    if (p != -1) {
      t_depth[u] = 1 + t_depth[p];
    }
    for (int k = 1; k < t_maxlift; k++) {
      if (t_par[u][k - 1] != -1) {
        t_par[u][k] = t_par[t_par[u][k - 1]][k - 1];
      }
    }

    for (const int &v : t_adj[u]) {
      if (v ^ p) {
        dfs_lca(v, u);
      }
    }
  }

public:
  /**
   * @brief Class parameterized constructor, resizes the and initializes the
   * data members
   * @param nodes the total number of nodes in the tree
   */
  explicit Tree(int nodes)
      : t_nodes(nodes), t_maxlift(static_cast<int>(floor(log2(nodes))) + 1) {
    /* Initialize and resize all the vectors */
    t_root = 0; /* Default */
    t_adj.resize(t_nodes);
    t_par.assign(t_nodes, std::vector<int>(t_maxlift, -1));
    t_depth.assign(t_nodes, 0);
    t_size.assign(t_nodes, 1);
    t_val.resize(t_nodes);
  }

  /**
   * @brief Adds an undirected edge from node u to node v in the tree
   * @param u the node where the edge is from
   * @param v the node where the edge is to
   * @returns void
   */
  void add_edge(const int u, const int v) {
    t_adj[u].push_back(v);
    t_adj[v].push_back(u);
  }

  /**
   * @brief Set the root for the tree
   * @param new_root the new root
   * @returns void
   */
  void change_root(int new_root) { t_root = new_root; }

  /**
   * @brief Set the values for all the nodes
   * @param node_val a vector of size n, with all the node values where, n is
   * the number of nodes
   * @returns void
   */
  void set_node_val(const std::vector<X> &node_val) {
    assert(static_cast<int>(node_val.size()) == t_nodes);
    t_val = node_val;
  }

  /**
   * @brief This function must be called after the tree adjacency list and node
   * values are populated The function initializes the required parameters, and
   * populates the segment tree
   * @returns void
   */
  void init() {
    assert(t_nodes > 0);
    dfs_size(t_root);
    dfs_lca(t_root);
  }

  /**
   * @brief The function lifts a node, k units up the tree.
   * The lifting is done in place, and the result is stored in the address
   * pointed by p.
   * @param p a pointer to the variable that stores the node id
   * @param dist the distance to move up the tree
   * @returns void
   */
  void lift(int *const p, int dist) {
    for (int k = 0; k < t_maxlift; k++) {
      if (*p == -1) {
        return;
      }
      if (dist & 1) {
        *p = t_par[*p][k];
      }
      dist >>= 1;
    }
  }

  /**
   * @brief The function returns the kth ancestor of a node
   * @param p the node id whose kth ancestor is to be found
   * @param dist the distance to move up the tree
   * @returns the kth ancestor of node
   */
  int kth_ancestor(int p, const int &dist) {
    lift(&p, dist);
    return p;
  }

  /**
   * @brief The function returns the least common ancestor of two nodes
   * @param a node id_1
   * @param b node id_2
   * @returns the least common ancestor of node a, and node b
   */
  int lca(int a, int b) {
    assert(a >= 0 and b >= 0 and a < t_nodes and b < t_nodes);
    if (t_depth[a] > t_depth[b]) {
      lift(&a, t_depth[a] - t_depth[b]);
    }
    if (t_depth[b] > t_depth[a]) {
      lift(&b, t_depth[b] - t_depth[a]);
    }
    if (a == b) {
      return a;
    }
    for (int k = t_maxlift - 1; k >= 0; k--) {
      if (t_par[a][k] != t_par[b][k]) {
        a = t_par[a][k];
        b = t_par[b][k];
      }
    }
    return t_par[a][0];
  }
};

/**
 * @brief Segment Tree, to store heavy chains
 * @tparam the data type of the values stored in the tree nodes
 */
template <typename X> class SG {
private:
  /**
   * @brief Everything here is private,
   * and can only be accessed through the methods,
   * in the derived class (HLD)
   */

  std::vector<X> s_tree; ///< the segment tree, stored as a vector
  int s_size;            ///< number of leaves in the segment tree
  X sret_init = 0;       ///< inital query return value
  template <typename T> friend class HLD;

  /**
   * @brief Function that specifies the type of operation involved when segments
   * are combined
   * @param lhs the left segment
   * @param rhs the right segment
   * @returns the combined result
   */
  X combine(X lhs, X rhs) { return lhs + rhs; }

  /**
   * @brief Class parameterized constructor. Resizes the and initilizes the data
   * members.
   * @param nodes the total number of nodes in the tree
   * @returns void
   */
  explicit SG(int size) {
    s_size = size;
    s_tree.assign(2 * s_size, 0ll);
  }

  /**
   * @brief Update the value at a node
   * @param p the node to be udpated
   * @param v the update value
   * @returns void
   */
  void update(int p, X v) {
    for (p += s_size; p > 0; p >>= 1) {
      s_tree[p] += v;
    }
  }

  /**
   * @brief Make a range query from node label l to node label r
   * @param l node label where the path starts
   * @param r node label where the path ends
   * @returns void
   */
  X query(int l, int r) {
    X lhs = sret_init, rhs = sret_init;
    for (l += s_size, r += s_size + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1) {
        lhs = combine(lhs, s_tree[l++]);
      }
      if (r & 1) {
        rhs = combine(s_tree[--r], rhs);
      }
    }
    return combine(lhs, rhs);
  }

  /**
   * @brief Set the initialization for the query data type, based on requirement
   *
   * @details
   * Change the sret_init, based on requirement:
   * * Sum Query: 0 (Default)
   * * XOR Query: 0 (Default)
   * * Min Query: Infinity
   * * Max Query: -Infinity
   * @param new_sret_init the new init
   */
  void set_sret_init(X new_sret_init) { sret_init = new_sret_init; }
};

/**
 * @brief The Heavy-Light Decomposition class
 * @tparam the data type of the values stored in the tree nodes
 */
template <typename X> class HLD : public Tree<X>, public SG<X> {
private:
  int label;                ///< utility member to assign labels in dfs_labels()
  std::vector<int> h_label, ///< stores the label of a node
      h_heavychlid,         ///< stores the heavy child of a node
      h_parent;             ///< stores the top of the heavy chain from a node

  /**
   * @brief Utility function to assign heavy child to each node (-1 for a leaf
   * node)
   * @param u current dfs node
   * @param p the parent of node u
   * @returns void
   */
  void dfs_hc(int u, int p = -1) {
    int hc_size = -1, hc_id = -1;
    for (const int &v : Tree<X>::t_adj[u]) {
      if (v ^ p) {
        dfs_hc(v, u);
        if (Tree<X>::t_size[v] > hc_size) {
          hc_size = Tree<X>::t_size[v];
          hc_id = v;
        }
      }
    }
    h_heavychlid[u] = hc_id;
  }

  /**
   * @brief Utility function to assign highest parent that can be reached though
   * heavy chains
   * @param u current dfs node
   * @param p the parent of node u
   * @returns void
   */
  void dfs_par(int u, int p = -1) {
    if (h_heavychlid[u] != -1) {
      h_parent[h_heavychlid[u]] = h_parent[u];
      dfs_par(h_heavychlid[u], u);
    }
    for (const int &v : Tree<X>::t_adj[u]) {
      if (v ^ p and v ^ h_heavychlid[u]) {
        dfs_par(v, u);
      }
    }
  }

  /**
   * @brief Utility function to lable the nodes so that heavy chains have a
   * contigous lable
   * @param u current dfs node
   * @param p the parent of node u
   * @returns void
   */
  void dfs_labels(int u, int p = -1) {
    h_label[u] = label++;
    if (h_heavychlid[u] != -1) {
      dfs_labels(h_heavychlid[u], u);
    }
    for (const int &v : Tree<X>::t_adj[u]) {
      if (v ^ p and v ^ h_heavychlid[u]) {
        dfs_labels(v, u);
      }
    }
  }

  /**
   * @brief Utility function to break down a path query into two chain queries
   * @param a node where the path starts
   * @param b node where the path ends
   * a and b must belong to a single root to leaf chain
   * @returns the sum of ndoe values in the simple path from a to b
   */
  X chain_query(int a, int b) {
    X ret = SG<X>::sret_init;
    if (Tree<X>::t_depth[a] < Tree<X>::t_depth[b]) {
      std::swap(a, b);
    }
    while (Tree<X>::t_depth[a] >= Tree<X>::t_depth[b]) {
      int l = h_label[h_parent[a]];
      int r = h_label[a];
      if (Tree<X>::t_depth[h_parent[a]] < Tree<X>::t_depth[b]) {
        l += Tree<X>::t_depth[b] - Tree<X>::t_depth[h_parent[a]];
      }
      ret = SG<X>::combine(ret, SG<X>::query(l, r));
      a = Tree<X>::t_par[h_parent[a]][0];
      if (a == -1) {
        break;
      }
    }
    return ret;
  }

public:
  /**
   * @brief Class parameterized constructor. Resizes the and initilizes the data
   * members.
   * @param nodes the total number of nodes in the tree
   */
  explicit HLD<X>(int nodes) : Tree<X>(nodes), SG<X>(nodes) {
    /* Initialization and resize vectors */
    label = 0;
    h_label.assign(Tree<X>::t_nodes, -1);
    h_heavychlid.assign(Tree<X>::t_nodes, -1);
    h_parent.resize(Tree<X>::t_nodes);
    iota(h_parent.begin(), h_parent.end(), 0);
  }

  /**
   * @brief This function must be called after the tree adjacency list and node
   * values are populated The function initializes the required parametes, and
   * populates the segment tree
   * @returns void
   */
  void init() {
    Tree<X>::init();

    // Fill the heavy child, greatest parent, and labels
    label = 0;
    dfs_hc(Tree<X>::t_root);
    dfs_par(Tree<X>::t_root);
    dfs_labels(Tree<X>::t_root);

    // Segment Tree Initialization
    for (int i = 0; i < Tree<X>::t_nodes; i++) {
      SG<X>::s_tree[h_label[i] + Tree<X>::t_nodes] = Tree<X>::t_val[i];
    }
    for (int i = Tree<X>::t_nodes - 1; i > 0; i--) {
      SG<X>::s_tree[i] =
          SG<X>::combine(SG<X>::s_tree[i << 1], SG<X>::s_tree[i << 1 | 1]);
    }
  }

  /**
   * @brief This function updates the value at node with val
   * @param node the node where the update is done
   * @param val the value that is being updated
   * @returns void
   */
  void update(int node, X val) {
    X diff = val - Tree<X>::t_val[node];
    SG<X>::update(h_label[node], diff);
    Tree<X>::t_val[node] = val;
  }

  /**
   * @brief This function returns the sum of node values in the simple path from
   * from node_1 to node_2
   * @param a the node where the simple path starts
   * @param b the node where the simple path ends
   * (parameters are interchangeable, i.e., the function is commutative)
   * @returns the sum of node values in the simple path from a to b
   */
  X query(int a, int b) {
    int lc = Tree<X>::lca(a, b);
    X ret = SG<X>::sret_init;
    assert(lc != -1);
    ret += chain_query(a, lc);
    ret += chain_query(b, lc);
    return ret - Tree<X>::t_val[lc];
  }
};
} // namespace heavy_light_decomposition
} // namespace range_queries

/**
 * Test implementations
 * @returns none
 */
static void test_1() {
  std::cout << "Test 1:\n";

  // Test details
  int n = 5;
  std::vector<int64_t> node_values = {4, 2, 5, 2, 1};
  std::vector<std::vector<int>> edges = {{1, 2}, {1, 3}, {3, 4}, {3, 5}};
  std::vector<std::vector<int>> queries = {
      {2, 1, 4},
      {1, 3, 2},
      {2, 1, 4},
  };
  std::vector<int> expected_result = {11, 8};
  std::vector<int> code_result;

  range_queries::heavy_light_decomposition::HLD<int64_t> hld(n);
  hld.set_node_val(node_values);
  for (int i = 0; i < n - 1; i++) {
    int u = edges[i][0], v = edges[i][1];
    hld.add_edge(u - 1, v - 1);
  }
  hld.init();
  for (const auto &q : queries) {
    int type = q[0];
    if (type == 1) {
      int p = q[1], x = q[2];
      hld.update(p - 1, x);
    } else if (type == 2) {
      int a = q[1], b = q[2];
      code_result.push_back(hld.query(a - 1, b - 1));
    } else {
      continue;
    }
  }
  for (int i = 0; i < static_cast<int>(expected_result.size()); i++) {
    assert(expected_result[i] == code_result[i]);
  }
  std::cout << "\nTest 1 passed!\n";
}

/**
 * Second test implementations
 * @returns void
 */
static void test_2() {
  std::cout << "Test 2:\n";

  // Test details (Bamboo)
  int n = 10;
  std::vector<int64_t> node_values = {1, 8, 6, 8, 6, 2, 9, 2, 3, 2};
  std::vector<std::vector<int>> edges = {
      {10, 5}, {6, 2}, {10, 7}, {5, 2}, {3, 9}, {8, 3}, {1, 4}, {6, 4}, {8, 7}};
  std::vector<std::vector<int>> queries = {
      {2, 1, 10}, {2, 1, 6}, {1, 3, 4}, {2, 1, 9}, {1, 5, 3},
      {1, 7, 8},  {2, 1, 4}, {2, 1, 8}, {1, 1, 4}, {1, 2, 7}};
  std::vector<int> expected_result = {27, 11, 45, 9, 34};
  std::vector<int> code_result;

  range_queries::heavy_light_decomposition::HLD<int64_t> hld(n);
  hld.set_node_val(node_values);
  for (int i = 0; i < n - 1; i++) {
    int u = edges[i][0], v = edges[i][1];
    hld.add_edge(u - 1, v - 1);
  }
  hld.init();
  for (const auto &q : queries) {
    int type = q[0];
    if (type == 1) {
      int p = q[1], x = q[2];
      hld.update(p - 1, x);
    } else if (type == 2) {
      int a = q[1], b = q[2];
      code_result.push_back(hld.query(a - 1, b - 1));
    } else {
      continue;
    }
  }
  for (int i = 0; i < static_cast<int>(expected_result.size()); i++) {
    assert(expected_result[i] == code_result[i]);
  }
  std::cout << "\nTest2 passed!\n";
}

/**
 * Third test implementations
 * @returns void
 */
static void test_3() {
  std::cout << "Test 3:\n";

  // Test details
  int n = 8;
  std::vector<int64_t> node_values = {1, 8, 6, 8, 6, 2, 9, 2};
  std::vector<std::vector<int>> edges = {{1, 2}, {2, 3}, {3, 4}, {1, 5},
                                         {6, 3}, {7, 5}, {8, 7}};
  std::vector<std::vector<int>> queries = {
      {2, 6, 8}, {2, 3, 6}, {1, 3, 4}, {2, 7, 1}, {1, 5, 3},
      {1, 7, 8}, {2, 6, 4}, {2, 7, 8}, {1, 1, 4}, {1, 2, 7}};
  std::vector<int> expected_result = {34, 8, 16, 14, 10};
  std::vector<int> code_result;

  range_queries::heavy_light_decomposition::HLD<int64_t> hld(n);
  hld.set_node_val(node_values);
  for (int i = 0; i < n - 1; i++) {
    int u = edges[i][0], v = edges[i][1];
    hld.add_edge(u - 1, v - 1);
  }
  hld.init();
  for (const auto &q : queries) {
    int type = q[0];
    if (type == 1) {
      int p = q[1], x = q[2];
      hld.update(p - 1, x);
    } else if (type == 2) {
      int a = q[1], b = q[2];
      code_result.push_back(hld.query(a - 1, b - 1));
    } else {
      continue;
    }
  }
  for (int i = 0; i < static_cast<int>(expected_result.size()); i++) {
    assert(expected_result[i] == code_result[i]);
  }
  std::cout << "\nTest3 passed!\n";
}

/**
 * Main function
 */
int main() {
  test_1();
  test_2();
  test_3();
  return 0;
}
