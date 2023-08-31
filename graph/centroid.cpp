/**
 * @file centroid.cpp
 * @author Zach Appella (https://github.com/flo456123)
 * @date 2023-08-24
 *
 * @attention
 * This algorithm is mainly applicable to unrooted trees
 * because the center of a tree can be used to root it in
 * a balanced manner.
 *
 * @details
 * Finding the center(s) of a tree is a rather straightforward
 * task that can be accomplished relatively simply.
 *
 * The method I am using in this algorithm is going to be to
 * peel away the outer layer of leaf nodes. First, compute
 * the degree of each node, leaf nodes only have a degree of
 * one. Once leaf nodes have been identified, prune them and
 * update the degree of each node. Repeat this process until
 * the center(s) of the tree have been reached.
 *
 * @example
 * A good analogy to gain an understanding of this algorithm
 * is to think about peeling away the layers of an onion.
 * As each layer is peeled away, the center of it becomes
 * easier to reach.
 *
 * The only difference the algorithm has with this analogy
 * is that there is always a possibility for there to be
 * two centers, however there can never be more than two
 * centers. This is because it is possible for different
 * parts of the graph to have similar roles in terms of
 * their centrality as seen below:
 *
 *    A       F
 *     \     /
 *      B - D
 *     /     \
 *    C       G
 *
 * In this graph, both nodes B and D have equidistant from
 * all other nodes on the graph, making two centers of the
 * graph. On the event that there are two centers, either
 * one can be used to root the tree.
 */
#include <cassert>  // for assertions
#include <vector>   // for std::vector

/**
 * @namespace graph
 * @brief Graph algorithms
 */
namespace graph {

using adjacency_list = std::vector<std::vector<int>>;

/**
 * @namespace centroid
 * @brief This centroid implemention is made to use an adjacency list,
 *  but can be implemented to use other graph data structures as well.
 */
namespace centroid {

const int EMPTY_SIZE = 0;
const int MAX_SIZE = 2;

/**
 * Finds the center(s) of a tree.
 *
 * @param tree adjacency matrix representation of a tree
 * @param n    size of the tree
 * @return std::vector<int> center(s) of the tree
 */
std::vector<int> treeCenters(const adjacency_list &tree) {
    const int n = tree.size();
    int degree[n];            // tracks degree of each node
    std::vector<int> leaves;  // stores leaves to be removed
    for (int i = 0; i < n; i++) {
        degree[i] = tree[i].size();  // set degree to size number of children
        if (degree[i] == EMPTY_SIZE || degree[i] == 1) {
            leaves.push_back(i);
            degree[i] = EMPTY_SIZE;  // mark node as explored
        }
    }

    int count = leaves.size();
    while (count < n) {
        std::vector<int> new_leaves;
        for (int node : leaves) {
            for (int neighbor : tree[node]) {
                if (--degree[neighbor] == 1) {  // decrement degree of neighbor
                                                // and check for leaf
                    new_leaves.push_back(neighbor);
                }
            }
            degree[node] = EMPTY_SIZE;
        }
        count += new_leaves.size();  // add leaves of current iteration
        leaves = new_leaves;  // update leaves with the current leaves for
                              // the iteration
    }
    return leaves;
}

}  // namespace centroid
}  // namespace graph

bool valid_centers(const int size) {
    return size > graph::centroid::EMPTY_SIZE &&
           size <= graph::centroid::MAX_SIZE;
}

/**
 * @brief First test case.
 *
 * Visual of tree can be found at:
 * https://i.gyazo.com/c2752f8b3346f87774a285fb6b79e7b7.jpg
 */
void f() {
    const int size = 7;
    graph::adjacency_list tree(size);

    // Construct the tree
    tree[0] = {1, 3, 6};
    tree[1] = {0, 2, 4};
    tree[2] = {1};
    tree[3] = {0};
    tree[4] = {1, 5};
    tree[5] = {4};
    tree[6] = {0};

    std::vector<int> centers = graph::centroid::treeCenters(tree);
    assert(valid_centers(centers.size()));
}

/**
 * @brief Second test case.
 *
 * Visual of tree can be found at:
 * https://i.gyazo.com/97b9ad2bd14c9da682cc9a6406469d89.jpg
 */
void f2() {
    const int size = 31;
    graph::adjacency_list tree(size);

    // BIG TREE!!!
    tree[0] = {1, 3, 5};
    tree[1] = {0};
    tree[2] = {4, 7, 14};
    tree[3] = {0, 4};
    tree[4] = {2, 3};
    tree[5] = {0, 6, 9};
    tree[6] = {5, 10};
    tree[7] = {2, 8, 20};
    tree[8] = {7};
    tree[9] = {5, 12};
    tree[10] = {6};
    tree[11] = {12, 21, 22};
    tree[12] = {9, 11};
    tree[13] = {14, 16};
    tree[14] = {2, 13};
    tree[15] = {16, 17};
    tree[16] = {13, 15};
    tree[17] = {15, 18, 19};
    tree[18] = {17};
    tree[19] = {17};
    tree[20] = {7};
    tree[21] = {11};
    tree[22] = {11, 24};
    tree[23] = {24, 25, 26};
    tree[24] = {22, 23};
    tree[25] = {23, 27, 30};
    tree[26] = {23};
    tree[27] = {25, 29};
    tree[28] = {29};
    tree[29] = {27, 28};
    tree[30] = {25};

    std::vector<int> centers = graph::centroid::treeCenters(tree);
    assert(valid_centers(centers.size()));
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests(); // run self-implemented tests
    return 0;
}
