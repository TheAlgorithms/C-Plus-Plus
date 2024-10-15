/**
 * @file
 * @brief Implementation of finding the Lowest Common Ancestor (LCA) in a binary
 * tree
 * @details This program builds a binary tree and finds the LCA of two given
 * nodes. The LCA is the lowest node in the tree that has both the given nodes
 * as descendants.
 * @see [Lowest Common Ancestor
 * (Wikipedia)](https://en.wikipedia.org/wiki/Lowest_common_ancestor)
 */

#include <cassert>
#include <iostream>  /// for standard I/O operations
#include <vector>    /// for std::vector

/**
 * @brief Class representing a node in a binary tree
 */
class Node {
 public:
    int data;     ///< value stored in the node
    Node* left;   ///< pointer to the left child
    Node* right;  ///< pointer to the right child

    /**
     * @brief Constructor to initialize a node with the given data
     * @param data value to initialize the node with
     */
    Node(int data) {
        this->data = data;
        left = right = nullptr;
    }
};

static int idx = -1;  ///< static variable to help with tree building recursion

/**
 * @brief Function to build a binary tree from a vector of integers
 * @param nodes a vector representing the tree where -1 signifies a null node
 * @return pointer to the root of the binary tree
 */
Node* build_tree(const std::vector<int>& nodes) {
    idx++;
    if (nodes[idx] == -1) {
        return nullptr;
    }

    Node* curr_node = new Node(nodes[idx]);
    curr_node->left = build_tree(nodes);
    curr_node->right = build_tree(nodes);

    return curr_node;
}

/**
 * @brief Helper function to find a root-to-node path
 * @param root pointer to the root node of the tree
 * @param n value of the target node to find
 * @param path vector to store the path from the root to the node
 * @return true if the path exists, false otherwise
 */
bool root_to_path(Node* root, int n, std::vector<int>& path) {
    if (root == nullptr) {
        return false;
    }

    path.push_back(root->data);
    if (root->data == n) {
        return true;
    }

    if (root_to_path(root->left, n, path) ||
        root_to_path(root->right, n, path)) {
        return true;
    }

    path.pop_back();  // Backtrack if not on the path to the node
    return false;
}

/**
 * @brief Function to find the Lowest Common Ancestor (LCA) using the path
 * method
 * @param root pointer to the root of the binary tree
 * @param n1 value of the first node
 * @param n2 value of the second node
 * @return value of the LCA node, or -1 if no LCA is found
 */
int find_lca_path(Node* root, int n1, int n2) {
    std::vector<int> path1, path2;

    // Find paths from root to n1 and n2
    if (!root_to_path(root, n1, path1) || !root_to_path(root, n2, path2)) {
        return -1;  // If either path doesn't exist
    }

    // Compare the paths to find the last common element
    int lca = -1;
    for (int i = 0; i < path1.size() && i < path2.size(); i++) {
        if (path1[i] != path2[i]) {
            break;
        }
        lca = path1[i];
    }

    return lca;
}

/**
 * @brief Function to find the Lowest Common Ancestor (LCA) using recursive
 * method
 * @param root pointer to the root of the binary tree
 * @param n1 value of the first node
 * @param n2 value of the second node
 * @return pointer to the LCA node
 */
Node* find_lca_recursive(Node* root, int n1, int n2) {
    if (root == nullptr) {
        return nullptr;
    }

    if (root->data == n1 || root->data == n2) {
        return root;
    }

    Node* left_lca = find_lca_recursive(root->left, n1, n2);
    Node* right_lca = find_lca_recursive(root->right, n1, n2);

    if (left_lca && right_lca) {
        return root;
    }

    return (left_lca != nullptr) ? left_lca : right_lca;
}

/**
 * @brief Self-test function to verify LCA implementations
 */
void test() {
    std::vector<int> nodes = {1, 2, 4, -1, -1, 5, -1, -1, 3, -1, 6, -1, -1};
    Node* root = build_tree(nodes);

    // Test the path-based LCA method
    assert(find_lca_path(root, 4, 5) == 2);
    assert(find_lca_path(root, 4, 6) == 1);
    assert(find_lca_path(root, 3, 6) == 3);

    // Test the recursive LCA method
    assert(find_lca_recursive(root, 4, 5)->data == 2);
    assert(find_lca_recursive(root, 4, 6)->data == 1);
    assert(find_lca_recursive(root, 3, 6)->data == 3);

    std::cout << "All tests passed!\n";
}

int main() {
    test();  // Run self-tests
    return 0;
}
