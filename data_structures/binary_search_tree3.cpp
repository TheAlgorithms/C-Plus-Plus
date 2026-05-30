/**
 * @file
 * @brief Binary Search Tree (BST) Implementation using modern C++ features.
 * @details A class-based implementation of a Binary Search Tree that supports
 * insertion, deletion, searching, and various traversal techniques (DFS and BFS).
 * @author [Abdo Al Adawy](https://github.com/Abdo2000-1)
 */

#include <iostream>
#include <vector>
#include <cassert> 
#include <queue> 
#include <string>

 /**
  * @brief Node structure representing a single node in the BST.
  * @tparam T The data type of the value stored in the node.
  */
template <typename T>
struct Node {
    T data{};         ///< Value stored in the node
    Node* left;       ///< Pointer to the left child
    Node* right;      ///< Pointer to the right child

    /**
     * @brief Parameterized constructor for Node.
     * @param value The value to be stored in the node.
     */
    explicit Node(T value) : data(value), left(nullptr), right(nullptr) {}
};

/**
 * @brief Binary Search Tree (BST) class implementation.
 * @tparam T The data type of the elements inside the tree.
 */
template <typename T>
class BST {
private:
    Node<T>* root; ///< Pointer to the root node of the tree

    /**
     * @brief Helper function to recursively insert a value into the BST.
     * @param node The current sub-tree root node.
     * @param value The value to insert.
     * @return Node<T>* The updated node pointer after insertion.
     */
    Node<T>* insert(Node<T>* node, T value) {
        if (!node) return new Node<T>(value);

        if (value < node->data) {
            node->left = insert(node->left, value);
        }
        else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        return node;
    }

    /**
     * @brief Helper function to recursively search for a value in the BST.
     * @param node The current sub-tree root node.
     * @param value The target value to search for.
     * @return true if the value exists in the sub-tree, false otherwise.
     */
    bool search(Node<T>* node, T value) {
        if (!node) return false;

        if (node->data == value) {
            return true;
        }
        else if (node->data < value) {
            return search(node->right, value);
        }
        else {
            return search(node->left, value);
        }
    }

    /**
     * @brief Helper function to find the minimum value node in a sub-tree.
     * @param node The current sub-tree root node.
     * @return Node<T>* The node containing the minimum value.
     */
    Node<T>* successor(Node<T>* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    /**
     * @brief Helper function to find the maximum value node in a sub-tree.
     * @param node The current sub-tree root node.
     * @return Node<T>* The node containing the maximum value.
     */
    Node<T>* predecessor(Node<T>* node) {
        while (node && node->right) {
            node = node->right;
        }
        return node;
    }

    /**
     * @brief Helper function to recursively delete a node with a specific value.
     * @param node The current sub-tree root node.
     * @param value The value to delete.
     * @return Node<T>* The updated node pointer after deletion.
     */
    Node<T>* remove(Node<T>* node, T value) {
        if (!node) return nullptr;

        if (value < node->data) {
            node->left = remove(node->left, value);
        }
        else if (value > node->data) {
            node->right = remove(node->right, value);
        }
        else {
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            else if (!node->left) {
                Node<T>* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                Node<T>* temp = node->left;
                delete node;
                return temp;
            }
            else {
                Node<T>* temp = successor(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data);
            }
        }
        return node;
    }

    /**
     * @brief Helper function for Pre-Order traversal (Root -> Left -> Right).
     * @param node The current sub-tree root node.
     */
    void pre_order(Node<T>* node) {
        if (!node) return;
        std::cout << node->data << " ";
        pre_order(node->left);
        pre_order(node->right);
    }

    /**
     * @brief Helper function for In-Order traversal (Left -> Root -> Right).
     * @param node The current sub-tree root node.
     */
    void in_order(Node<T>* node) {
        if (!node) return;
        in_order(node->left);
        std::cout << node->data << " ";
        in_order(node->right);
    }

    /**
     * @brief Helper function for Post-Order traversal (Left -> Right -> Root).
     * @param node The current sub-tree root node.
     */
    void post_order(Node<T>* node) {
        if (!node) return;
        post_order(node->left);
        post_order(node->right);
        std::cout << node->data << " ";
    }

    /**
     * @brief Helper function for Breadth-First Search (BFS) / Level-Order traversal.
     * @param node The current node to start traversal from.
     */
    void bfs(Node<T>* node) {
        if (!node) return;

        std::queue<Node<T>*> q;
        q.push(node);

        while (!q.empty()) {
            Node<T>* u = q.front();
            q.pop();

            std::cout << u->data << " ";

            if (u->left) q.push(u->left);
            if (u->right) q.push(u->right);
        }
    }

    /**
     * @brief Helper function to recursively clear all nodes and free memory.
     * @param node The current sub-tree root node.
     */
    void clear(Node<T>* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    /**
     * @brief Helper function to collect nodes recursively in In-Order sequence.
     * @param node The current sub-tree root node.
     * @param res Reference to the vector where elements are stored.
     */
    void get_in_order(Node<T>* node, std::vector<T>& res) const {
        if (!node) return;
        get_in_order(node->left, res);
        res.push_back(node->data);
        get_in_order(node->right, res);
    }

    /**
     * @brief Helper function to recursively validate the BST properties.
     * @param node The current sub-tree root node.
     * @param min_val Pointer to the minimum allowed value.
     * @param max_val Pointer to the maximum allowed value.
     * @return true if valid, false otherwise.
     */
    bool is_valid_bst(Node<T>* node, const T* min_val, const T* max_val) const {
        if (!node) return true;
        if ((min_val && node->data <= *min_val) || (max_val && node->data >= *max_val)) {
            return false;
        }
        return is_valid_bst(node->left, min_val, &(node->data)) &&
            is_valid_bst(node->right, &(node->data), max_val);
    }

public:
    /**
     * @brief Default constructor initializing an empty tree.
     */
    BST() : root(nullptr) {}

    /**
     * @brief Public method to insert a value into the BST.
     * @param value The value to insert.
     */
    void insert(T value) {
        root = insert(root, value);
    }

    /**
     * @brief Public method to check if a value exists in the BST.
     * @param value The target value to search for.
     * @return true if found, false otherwise.
     */
    bool search(T value) {
        return search(root, value);
    }

    /**
     * @brief Public method to delete a value from the BST.
     * @param value The value to delete.
     */
    void remove(T value) {
        root = remove(root, value);
    }

    /**
     * @brief Public method to trigger Pre-Order traversal.
     */
    void pre_order() { pre_order(root); std::cout << "\n"; }

    /**
     * @brief Public method to trigger In-Order traversal.
     */
    void in_order() { in_order(root); std::cout << "\n"; }

    /**
     * @brief Public method to trigger Post-Order traversal.
     */
    void post_order() { post_order(root); std::cout << "\n"; }

    /**
     * @brief Public method to trigger BFS traversal.
     */
    void bfs() { bfs(root); std::cout << "\n"; }

    /**
     * @brief Public method to get tree elements in sorted In-Order inside a vector.
     * @return std::vector<T> Sorted vector containing BST elements.
     */
    std::vector<T> get_in_order() const {
        std::vector<T> result;
        get_in_order(root, result);
        return result;
    }

    /**
     * @brief Public method to get tree elements in BFS order inside a vector.
     * @return std::vector<T> Vector containing BST elements level by level.
     */
    std::vector<T> get_bfs() const {
        std::vector<T> result;
        if (!root) return result;

        std::queue<Node<T>*> q;
        q.push(root);
        while (!q.empty()) {
            Node<T>* u = q.front();
            q.pop();
            result.push_back(u->data);
            if (u->left) q.push(u->left);
            if (u->right) q.push(u->right);
        }
        return result;
    }

    /**
     * @brief Public method to check if the tree satisfies the BST property.
     * @return true if the tree is a valid BST, false otherwise.
     */
    bool is_valid_bst() const {
        return is_valid_bst(root, nullptr, nullptr);
    }

    /**
     * @brief Destructor to automatically clean up tree memory.
     */
    ~BST() {
        clear(root);
    }
};

/**
 * @brief Self-test implementations using assert.
 * @returns void
 */
static void test() {
    // Test with integers
    BST<int> tree;
    assert(tree.is_valid_bst() == true);

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);

    assert(tree.is_valid_bst() == true);

    std::vector<int> expected_in_order = { 20, 30, 40, 50, 70 };
    assert(tree.get_in_order() == expected_in_order);

    std::vector<int> expected_bfs = { 50, 30, 70, 20, 40 };
    assert(tree.get_bfs() == expected_bfs);

    assert(tree.search(40) == true);
    assert(tree.search(70) == true);
    assert(tree.search(90) == false);

    tree.remove(20);
    assert(tree.search(20) == false);
    assert(tree.is_valid_bst() == true);

    tree.remove(30);
    std::vector<int> after_delete_in_order = { 40, 50, 70 };
    assert(tree.get_in_order() == after_delete_in_order);
    assert(tree.is_valid_bst() == true);

    // Test with strings to verify Template functionality
    BST<std::string> string_tree;
    string_tree.insert("mango");
    string_tree.insert("apple");
    string_tree.insert("banana");

    assert(string_tree.is_valid_bst() == true);
    assert(string_tree.search("apple") == true);
    assert(string_tree.search("orange") == false);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();
    return 0;
}