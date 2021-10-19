/**
 * @file
 * @brief An implemention for Reversing a Binary Tree recursively.
 *
 */

#include <cassert>   /// For assert
#include <iostream>  /// For IO operations
#include <queue>     /// For std::queue
#include <vector>    /// For std::vector

/**
 * @namespace operations_on_datastructures
 * @brief Operations on Data Structures
 */
namespace operations_on_datastructures {

/**
 * @namespace reverse_binary_tree
 * @brief Functions for Creating and Reversing a Binary Tree
 */
namespace reverse_binary_tree {

/**
 * @brief A Node struct that represents a single node in a Binary Tree
 */
struct Node {
    int data;     ///< The value of the Node
    Node* left;   ///< The Node's left child
    Node* right;  ///< The Node's right child
    /**
     * @brief Creates a new Node with some initial data
     */
    Node(int _data) {
        data = _data;  ///< Set value of Node data
        left = NULL;   ///< Initialize left child to NULL
        right = NULL;  ///< Initialize right child to NULL
    }
};

/**
 * @brief A Binary Tree class that implements a Binary Search Tree
 *(BST) by default.
 */
class BinaryTree {
 private:
    Node* root;  ///< Pointer to root node of Binary Tree
    /**
     * @brief inserts a node in the Binary Tree, with the behaviouur of
     * a Binary Search Tree.
     * @details Nodes with smaller values are inserted in the left
     * subtree, and Nodes with larger values are inserted into the
     * right subtree recursively. Time Complexity: O(log(n))
     * @param data The data/value of the Node to be inserted
     * @param pivot A pointer to the root node of the (sub)tree
     * @returns Node pointer to the root
     */
    Node* insert(int data, Node* pivot) {
        if (pivot == NULL) {
            return new Node(data);
        }
        if (data <= pivot->data) {
            pivot->left = insert(data, pivot->left);
        } else {
            pivot->right = insert(data, pivot->right);
        }
        return pivot;
    }
    Node* reverseBinaryTree(Node* pivot) {
        if (pivot == NULL) {
            return pivot;
        }
        Node* temp = pivot->left;
        pivot->left = reverseBinaryTree(pivot->right);
        pivot->right = reverseBinaryTree(temp);
        return pivot;
    }

 public:
    BinaryTree() { root = NULL; }
    BinaryTree(Node* _root) { root = _root; }
    BinaryTree(int data) { root = new Node(data); }
    void add(int data) { root = insert(data, root); }
    void reverse() { root = reverseBinaryTree(root); }
    std::vector<int> get_level_order() {
        std::vector<int> data;
        if (root == NULL) {
            return data;
        }
        std::queue<Node*> nodes;
        nodes.push(root);
        while (!nodes.empty()) {
            Node* temp = nodes.back();
            data.push_back(temp);
            nodes.pop();
            if (temp->left != NULL) {
                nodes.push(temp->left);
            }
            if (temp->right != NULL) {
                nodes.push(temp->right);
            }
        }
        return data;
    }
};

}  // namespace reverse_binary_tree
}  // namespace operations_on_datastructures

int main() {}