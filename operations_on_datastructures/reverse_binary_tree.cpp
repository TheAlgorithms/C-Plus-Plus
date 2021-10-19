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
            return new Node(data);  ///< Create new node
        }
        if (data <= pivot->data) {
            pivot->left =
                insert(data, pivot->left);  ///< Insert Node to the left
        } else {
            pivot->right =
                insert(data, pivot->right);  ///< Insert node to the right
        }
        return pivot;
    }
    /**
     * @brief Reverses a Binary Tree recursively by swapping the left and
     * right subtrees and their children.
     * @param pivot A reference to the root of the (sub)tree
     * @returns Node pointer to root node
     */
    Node* reverseBinaryTree(Node* pivot) {
        if (pivot == NULL) {
            return pivot;  ///< Base case
        }
        Node* temp = pivot->left;  ///< pointer to the left subtree
        pivot->left = reverseBinaryTree(pivot->right);  ///< Swap
        pivot->right = reverseBinaryTree(temp);         ///< Swap
        return pivot;
    }

 public:
    /**
     * @brief Creates a BinaryTree with a root pointing to NULL.
     */
    BinaryTree() { root = NULL; }
    /**
     * @brief Creates a BinaryTree with a root with an initial value.
     */
    BinaryTree(int data) { root = new Node(data); }
    /**
     * @brief Adds a new Node to the Binary Tree
     */
    void add(int data) { root = insert(data, root); }
    /**
     * Reverses the Binary Tree
     */
    void reverse() { root = reverseBinaryTree(root); }
    /**
     * @brief Level order traversal of a tree consists of visiting its
     * elements, top to bottom, left to right. This function performs
     * level order traversal and returns the node datas as a vector.
     * @details The function uses a queue to append and remove elements
     * as they are visited, and then adds their children, if any. This
     * ensures that the elements are visited layer-by-layer, starting
     * from the root of the Tree.
     * @returns vector<int> of nodes of the tree.
     */
    std::vector<int> get_level_order() {
        std::vector<int> data;  ///< Result vector of int
        if (root == NULL) {
            return data;  ///< Return empty vector if root is Invalid
        }
        std::queue<Node*> nodes;  ///< Queue of the nodes in the tree
        nodes.push(root);         ///< Insert root into the queue
        while (!nodes.empty()) {
            Node* temp = nodes.back();   ///< Copy the first element
            data.push_back(temp->data);  ///< Add the element to the data
            nodes.pop();                 ///< Remove element
            if (temp->left != NULL) {
                nodes.push(temp->left);  ///< Insert left node
            }
            if (temp->right != NULL) {
                nodes.push(temp->right);  ///< Insert right node
            }
        }  /// Add nodes while Tree is not empty
        return data;
    }
    /**
     * @brief Prints all of the elements in the tree to stdout
     * level-by-level, using the get_level_order() function.
     * @returns void
     */
    void print() {
        for (int i : get_level_order()) {
            std::cout << i << " ";  /// Print each element in the tree
        }
        std::cout << "\n";  /// Print newline
    }
};

}  // namespace reverse_binary_tree
}  // namespace operations_on_datastructures

/**
 * @namespace tests
 */
namespace tests {
using operations_on_datastructures::reverse_binary_tree::BinaryTree;
void test1() {
    BinaryTree bst;
    bst.add(5);
    bst.print();
}
void test2() {
    BinaryTree bst;
    bst.add(7);
    bst.add(5);
    bst.add(9);
    bst.print();
}
}  // namespace tests

static void test() {
    tests::test1();
    tests::test2();
}

int main() {
    test();
    return 0;
}