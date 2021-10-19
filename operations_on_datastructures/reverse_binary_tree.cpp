/**
 * @file
 * @brief Implementation for the [Reversing a Binary
 * Tree](https://www.geeksforgeeks.org/reverse-tree-path/) recursively
 * algorithm.
 * @details A binary tree can be reversed by swapping the left and
 * right child of a node at each node, starting from the root, and
 * cascading below. This solution aims to provide an implementation of
 * a recursive reversal of a binary tree.
 * @author [Alvin](https://github.com/polarvoid)
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
 * @brief Functions for the [Reverse a Binary
 * Tree](https://www.geeksforgeeks.org/reverse-tree-path/) implementation
 */
namespace reverse_binary_tree {

/**
 * @brief A Node struct that represents a single node in a Binary Tree
 */
struct Node {
    int64_t data;  ///< The value of the Node
    Node* left;    ///< The Node's left child
    Node* right;   ///< The Node's right child
    /**
     * @brief Creates a new Node with some initial data
     */
    explicit Node(int64_t _data) {
        data = _data;     ///< Set value of Node data
        left = nullptr;   ///< Initialize left child to NULL
        right = nullptr;  ///< Initialize right child to NULL
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
    Node* insert(int64_t data, Node* pivot) {
        if (pivot == nullptr) {
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
        if (pivot == nullptr) {
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
    BinaryTree() { root = nullptr; }
    /**
     * @brief Creates a BinaryTree with a root with an initial value.
     */
    explicit BinaryTree(int64_t data) { root = new Node(data); }
    /**
     * @brief Adds a new Node to the Binary Tree
     */
    void add(int64_t data) { root = insert(data, root); }
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
     * @returns vector<int64_t> of nodes of the tree.
     */
    std::vector<int64_t> get_level_order() {
        std::vector<int64_t> data;  ///< Result vector of int
        if (root == nullptr) {
            return data;  ///< Return empty vector if root is Invalid
        }
        std::queue<Node*> nodes;  ///< Queue of the nodes in the tree
        nodes.push(root);         ///< Insert root into the queue
        while (!nodes.empty()) {
            Node* temp = nodes.front();  ///< Copy the first element
            data.push_back(temp->data);  ///< Add the element to the data
            nodes.pop();                 ///< Remove element
            if (temp->left != nullptr) {
                nodes.push(temp->left);  ///< Insert left node
            }
            if (temp->right != nullptr) {
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
 * @brief Testcases to check Reversal of Binary Tree.
 */
namespace tests {
using operations_on_datastructures::reverse_binary_tree::
    BinaryTree;  ///< Use the BinaryTree
/**
 * @brief A Test to check an edge case (single element reversal)
 */
void test1() {
    BinaryTree bst;
    std::vector<int64_t> pre_reversal, post_reversal;
    std::cout << "TEST CASE 1\n";
    std::cout << "Initializing tree with a single element (5)\n";
    bst.add(5);
    pre_reversal = bst.get_level_order();
    std::cout << "Before reversal: ";
    bst.print();
    std::cout << "After reversal: ";
    bst.reverse();
    post_reversal = bst.get_level_order();
    assert(pre_reversal.size() ==
           post_reversal.size());  ///< Check for equal sizes
    assert(pre_reversal.size() ==
           1);  ///< Ensure that there is only one element
    assert(pre_reversal[0] ==
           post_reversal[0]);  ///< Check if both elements are same
    bst.print();
    std::cout << "TEST PASSED!\n\n";
}
/**
 * @brief A Test to check an edge case (NULL root element)
 */
void test2() {
    BinaryTree bst;
    std::vector<int64_t> pre_reversal, post_reversal;
    std::cout << "TEST CASE 2\n";
    std::cout << "Creating empty tree (root points to NULL)\n";
    pre_reversal = bst.get_level_order();
    std::cout << "Before reversal: ";
    bst.print();
    std::cout << "After reversal: ";
    bst.reverse();
    post_reversal = bst.get_level_order();
    assert(pre_reversal.size() ==
           post_reversal.size());  ///< Check for equal sizes
    assert(pre_reversal.size() ==
           0);  ///< Ensure that there is only one element
    bst.print();
    std::cout << "TEST PASSED!\n\n";
}
/**
 * @brief A Test to check correct reversal of a Binary Tree
 */
void test3() {
    BinaryTree bst;
    std::vector<int64_t> pre_reversal, post_reversal;
    std::vector<int64_t> pre_res = {4, 3, 6, 2, 5, 7, 1};
    std::vector<int64_t> post_res = {4, 6, 3, 7, 5, 2, 1};
    std::cout << "TEST CASE 3\n";
    std::cout << "Creating tree with elements (4, 6, 3, 2, 5, 7, 1)\n";
    bst.add(4);
    bst.add(6);
    bst.add(3);
    bst.add(2);
    bst.add(5);
    bst.add(7);
    bst.add(1);
    pre_reversal = bst.get_level_order();
    assert(pre_reversal == pre_res);  ///< Check for equality
    std::cout << "Before reversal: ";
    bst.print();
    std::cout << "After reversal: ";
    bst.reverse();
    post_reversal = bst.get_level_order();
    assert(post_reversal == post_res);  ///< Check for equality
    bst.print();
    std::cout << "TEST PASSED!\n\n";
}
}  // namespace tests

/**
 * @brief Function to test the correctness of the Tree Reversal
 */
static void test() {
    tests::test1();  ///< Single element test
    tests::test2();  ///< No element test
    tests::test3();  ///< Correct reversal test
}

/**
 * @brief main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
