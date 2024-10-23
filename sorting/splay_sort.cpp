/**
 * @file
 * @brief [Splay sort implementation](https://en.wikipedia.org/wiki/Splay_tree)
 * in C++
 * @details
 * Splay sort is a sorting algorithm that uses a Splay Tree, a self-adjusting
 * binary search tree. It inserts elements into a Splay Tree and then performs
 * an in-order traversal to produce a sorted list.
 * The time complexity for inserting an element into a Splay Tree is O(log n)
 * for each insertion on average, but the worst-case complexity is O(n) due to
 * splaying. The overall average time complexity for Splay Sort is O(n log n).
 */

#include <algorithm>  /// for std::is_sorted
#include <cassert>    /// for assert
#include <iostream>   /// for IO operations
#include <vector>     /// for vector

/**
 * @brief A structure for tree node.
 */
struct Node {
    int key;
    Node* left;
    Node* right;

    explicit Node(int key) : key(key), left(nullptr), right(nullptr) {}
};

/**
 * @brief A utility function to perform right rotation on the given root.
 * @param x the root node
 * @returns the new root after rotation
 */
Node* rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

/**
 * @brief A utility function to perform left rotation on the given root.
 * @param x the root node
 * @returns the new root after rotation
 */
Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

/**
 * @brief Splay operation that brings the key to the root if present.
 * @param root the root of the tree
 * @param key the key to splay
 * @returns the new root after splaying
 */
Node* splay(Node* root, int key) {
    if (root == nullptr || root->key == key) {
        return root;
    }

    // Key lies in the left subtree
    if (key < root->key) {
        if (root->left == nullptr)
            return root;

        // Zig-Zig (Left Left)
        if (key < root->left->key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        // Zig-Zag (Left Right)
        else if (key > root->left->key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != nullptr) {
                root->left = leftRotate(root->left);
            }
        }
        return (root->left == nullptr) ? root : rightRotate(root);
    }
    // Key lies in the right subtree
    else {
        if (root->right == nullptr)
            return root;

        // Zag-Zig (Right Left)
        if (key < root->right->key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != nullptr) {
                root->right = rightRotate(root->right);
            }
        }
        // Zag-Zag (Right Right)
        else if (key > root->right->key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        return (root->right == nullptr) ? root : leftRotate(root);
    }
}

/**
 * @brief Function to insert a key into the Splay Tree
 * @param root the root of the tree
 * @param key the key to insert
 * @returns the new root after insertion
 */
Node* insert(Node* root, int key) {
    if (root == nullptr) {
        return new Node(key);
    }

    root = splay(root, key);

    if (root->key == key)
        return root;  // If the key already exists

    Node* newNode = new Node(key);
    if (key < root->key) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = nullptr;
    } else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = nullptr;
    }
    return newNode;
}

/**
 * @brief Function to perform in-order traversal of the Splay Tree
 * @param root the root of the tree
 * @param result a vector to store the sorted elements
 */
void inOrder(Node* root, std::vector<int>& result) {
    if (root == nullptr)
        return;
    inOrder(root->left, result);
    result.push_back(root->key);
    inOrder(root->right, result);
}

/**
 * @brief The splaySort() function is used for sorting the array.
 * @param L - vector of values (int) to be sorted (ascending order)
 * @returns void
 */
void splaySort(std::vector<int>* L) {
    Node* root = nullptr;

    // Insert each element into the Splay Tree
    for (int key : *L) {
        root = insert(root, key);
    }

    // Perform in-order traversal to get sorted elements
    std::vector<int> sortedResult;
    inOrder(root, sortedResult);

    // Copy back sorted elements to the original vector
    for (size_t i = 0; i < L->size(); i++) {
        (*L)[i] = sortedResult[i];
    }
}

/**
 * @brief Function to test sorting algorithm
 * @returns void
 */
void test1() {
    std::vector<int> L = {8, 9, 10, 4, 3, 5, 1};
    splaySort(&L);
    assert(std::is_sorted(std::begin(L), std::end(L)));
}

/**
 * @brief Function to test sorting algorithm, one element
 * @returns void
 */
void test2() {
    std::vector<int> L = {-1};
    splaySort(&L);
    assert(std::is_sorted(std::begin(L), std::end(L)));
}

/**
 * @brief Function to test sorting algorithm, repeating elements
 * @returns void
 */
void test3() {
    std::vector<int> L = {1, 2, 5, 4, 1, 5};
    splaySort(&L);
    assert(std::is_sorted(std::begin(L), std::end(L)));
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main() {
    test1();
    test2();
    test3();

    std::cout << "All tests have successfully passed!\n";
    return 0;
}
