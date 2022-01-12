/**
 * @file
 * @brief Recursive version of Inorder, Preorder, and Postorder [Traversal of
 * the Tree] (https://en.wikipedia.org/wiki/Tree_traversal)
 *
 * @details
 *
 * ### Iterative Inorder Traversal of a tree
 * For traversing a (non-empty) binary tree in an inorder fashion, we must do
 * these three things for every node n starting from the tree’s root:
 *
 * (L) Recursively traverse its left subtree. When this step is finished,
 * we are back at n again.
 * (N) Process n itself.
 * (R) Recursively traverse its right subtree. When this step is finished,
 * we are back at n again.
 *
 * In normal inorder traversal, we visit the left subtree before the right
 * subtree. If we visit the right subtree before visiting the left subtree, it
 * is referred to as reverse inorder traversal.
 *
 * ### Iterative Preorder Traversal of a tree
 * For traversing a (non-empty) binary tree in a preorder fashion, we must do
 * these three things for every node n starting from the tree’s root:
 *
 * (N) Process n itself.
 * (L) Recursively traverse its left subtree. When this step is finished,
 * we are back at n again.
 * (R) Recursively traverse its right subtree. When this step is finished,
 * we are back at n again.
 *
 * In normal preorder traversal, visit the left subtree before the right
 * subtree. If we visit the right subtree before visiting the left subtree, it
 * is referred to as reverse preorder traversal.
 *
 * ### Iterative Postorder Traversal of a tree
 * For traversing a (non-empty) binary tree in a postorder fashion, we must do
 * these three things for every node n starting from the tree’s root:
 *
 * (L) Recursively traverse its left subtree. When this step is finished,
 * we are back at n again.
 * (R) Recursively traverse its right subtree. When this step is finished,
 * we are back at n again.
 * (N) Process n itself.
 *
 * In normal postorder traversal, visit the left subtree before the right
 * subtree. If we visit the right subtree before visiting the left subtree, it
 * is referred to as reverse postorder traversal.
 *
 * @author [Lajat Manekar](https://github.com/Lazeeez)
 *
 */

#include <cassert>   /// for assert
#include <iostream>  /// for I/O operations
#include <vector>    /// for vector

/**
 * @namespace others
 * @brief Other algorithms
 */
namespace others {

/**
 * @namespace interpolation_search
 * @brief Functions for the Recursive version of Inorder, Preorder, and
 * Postorder [Traversal of the
 * Tree](https://en.wikipedia.org/wiki/Tree_traversal) algorithm implementation
 */
namespace recursive_tree_traversals {

/**
 * @brief The structure to hold Nodes of the tree.
 * @param data Value that will be stored in the node.
 * @param left follow up left subtree.
 * @param right follow up right subtree.
 */
struct Node {
    uint64_t data = 0;     ///< The value/key of the node.
    struct Node *left{};   ///< struct pointer to left subtree.
    struct Node *right{};  ///< struct pointer to right subtree.
};
/**
 * @brief BT used to make the entire structure of the binary tree and the
 * functions associated with the binary tree
 */
class BT {
 public:
    std::vector<uint64_t>
        inorder_result;  // vector to store the inorder traversal of the tree.
    std::vector<uint64_t>
        preorder_result;  // vector to store the preorder traversal of the tree.
    std::vector<uint64_t> postorder_result;  // vector to store the preorder
                                             // traversal of the tree.

    Node *createNewNode(
        uint64_t);  // function that will create new node for insertion.

    std::vector<uint64_t> inorder(
        Node *);  // function that takes root of the tree as an argument and
                  // returns its inorder traversal.
    std::vector<uint64_t> preorder(
        Node *);  // function that takes root of the tree as an argument and
                  // returns its preorder traversal.
    std::vector<uint64_t> postorder(
        Node *);  // function that takes root of the tree as an argument and
                  // returns its postorder traversal.
};

/**
 * @brief will allocate the memory for a node and, along the data and return the
 * node.
 * @param data value that a particular node will contain.
 * @return pointer to the newly created node with assigned data.
 */
Node *BT::createNewNode(uint64_t data) {
    Node *node = new Node();
    node->data = data;
    node->left = node->right = nullptr;
    return node;
}

/*
 * @brief inorder() function that will perform the inorder traversal
 * recursively, and return the resultant vector that contain the inorder
 * traversal of a tree.
 * @param root head/root node of a tree
 * @return result that is containing the inorder traversal of a tree
 **/
std::vector<uint64_t> BT::inorder(Node *root) {
    if (root == nullptr) {  // return if the current node is empty
        return {};
    }

    inorder(root->left);  // Traverse the left subtree
    BT::inorder_result.push_back(
        root->data);  // Display the data part of the root (or current node)
    inorder(root->right);  // Traverse the right subtree

    return inorder_result;
}

/**
 * @brief preorder function that will perform the preorder traversal
 * recursively, and return the resultant vector that contain the preorder
 * traversal of a tree.
 * @param root head/root node of a tree
 * @return result that is containing the preorder traversal of a tree
 */
std::vector<uint64_t> BT::preorder(Node *root) {
    if (root == nullptr) {  // if the current node is empty
        return {};
    }

    BT::preorder_result.push_back(
        root->data);  // Display the data part of the root (or current node)
    preorder(root->left);   // Traverse the left subtree
    preorder(root->right);  // Traverse the right subtree

    return preorder_result;
}

/**
 * @brief postorder function that will perform the postorder traversal
 * recursively, and return the result vector that contain the postorder
 * traversal of a tree.
 * @param root head/root node of a tree
 * @return result that is containing the postorder traversal of a tree
 */
std::vector<uint64_t> BT::postorder(Node *root) {
    if (root == nullptr) {  // if the current node is empty
        return {};
    }

    postorder(root->left);   // Traverse the left subtree
    postorder(root->right);  // Traverse the right subtree
    BT::postorder_result.push_back(
        root->data);  // Display the data part of the root (or current node)

    return postorder_result;
}

}  // namespace recursive_tree_traversals

}  // namespace others

/**
 * @brief 1st test-case
 * @returns void
 */
void test1() {
    others::recursive_tree_traversals::BT obj1;
    others::recursive_tree_traversals::Node *root = obj1.createNewNode(2);
    root->left = obj1.createNewNode(7);
    root->right = obj1.createNewNode(5);
    root->left->left = obj1.createNewNode(2);
    root->left->right = obj1.createNewNode(6);
    root->right->right = obj1.createNewNode(9);
    root->left->right->left = obj1.createNewNode(5);
    root->left->right->right = obj1.createNewNode(11);
    root->right->right->left = obj1.createNewNode(4);

    std::vector<uint64_t> actual_result_inorder{2, 7, 5, 6, 11, 2, 5, 4, 9};
    std::vector<uint64_t> actual_result_preorder{2, 7, 2, 6, 5, 11, 5, 9, 4};
    std::vector<uint64_t> actual_result_postorder{2, 5, 11, 6, 7, 4, 9, 5, 2};
    std::vector<uint64_t> result_inorder;    ///< result stores the inorder
                                             ///< traversal of the binary tree
    std::vector<uint64_t> result_preorder;   ///< result stores the preorder
                                             ///< traversal of the binary tree
    std::vector<uint64_t> result_postorder;  ///< result stores the postorder
                                             ///< traversal of the binary tree

    uint64_t size = actual_result_inorder.size();

    // Calling inorder() function by passing a root node,
    // and storing the inorder traversal in result_inorder.
    result_inorder = obj1.inorder(root);
    std::cout << "Testcase #1: Inorder Traversal...";
    for (auto i = 0; i < size; ++i) {
        assert(actual_result_inorder[i] == result_inorder[i]);
    }
    std::cout << "Passed!" << std::endl;

    // Calling preorder() function by passing a root node,
    // and storing the preorder traversal in result_preorder.
    result_preorder = obj1.preorder(root);
    std::cout << "Testcase #1: Preorder Traversal...";
    for (auto i = 0; i < size; ++i) {
        assert(actual_result_preorder[i] == result_preorder[i]);
    }
    std::cout << "Passed!" << std::endl;

    // Calling postorder() function by passing a root node,
    // and storing the postorder traversal in result_postorder.
    result_postorder = obj1.postorder(root);
    std::cout << "Testcase #1: Postorder Traversal...";
    for (auto i = 0; i < size; ++i) {
        assert(actual_result_postorder[i] == result_postorder[i]);
    }
    std::cout << "Passed!" << std::endl;

    std::cout << std::endl;
}

/**
 * @brief 2nd test-case
 * @returns void
 */
void test2() {
    others::recursive_tree_traversals::BT obj2;
    others::recursive_tree_traversals::Node *root = obj2.createNewNode(1);
    root->left = obj2.createNewNode(2);
    root->right = obj2.createNewNode(3);
    root->left->left = obj2.createNewNode(4);
    root->right->left = obj2.createNewNode(5);
    root->right->right = obj2.createNewNode(6);
    root->right->left->left = obj2.createNewNode(7);
    root->right->left->right = obj2.createNewNode(8);

    std::vector<uint64_t> actual_result_inorder{4, 2, 1, 7, 5, 8, 3, 6};
    std::vector<uint64_t> actual_result_preorder{1, 2, 4, 3, 5, 7, 8, 6};
    std::vector<uint64_t> actual_result_postorder{4, 2, 7, 8, 5, 6, 3, 1};
    std::vector<uint64_t> result_inorder;    ///< result stores the inorder
                                             ///< traversal of the binary tree
    std::vector<uint64_t> result_preorder;   ///< result stores the preorder
                                             ///< traversal of the binary tree
    std::vector<uint64_t> result_postorder;  ///< result stores the postorder
                                             ///< traversal of the binary tree

    uint64_t size = actual_result_inorder.size();

    // Calling inorder() function by passing a root node,
    // and storing the inorder traversal in result_inorder.
    result_inorder = obj2.inorder(root);
    std::cout << "Testcase #2: Inorder Traversal...";
    for (auto i = 0; i < size; ++i) {
        assert(actual_result_inorder[i] == result_inorder[i]);
    }
    std::cout << "Passed!" << std::endl;

    // Calling preorder() function by passing a root node,
    // and storing the preorder traversal in result_preorder.
    result_preorder = obj2.preorder(root);
    std::cout << "Testcase #2: Preorder Traversal...";
    for (auto i = 0; i < size; ++i) {
        assert(actual_result_preorder[i] == result_preorder[i]);
    }
    std::cout << "Passed!" << std::endl;

    // Calling postorder() function by passing a root node,
    // and storing the postorder traversal in result_postorder.
    result_postorder = obj2.postorder(root);
    std::cout << "Testcase #2: Postorder Traversal...";
    for (auto i = 0; i < size; ++i) {
        assert(actual_result_postorder[i] == result_postorder[i]);
    }
    std::cout << "Passed!" << std::endl;

    std::cout << std::endl;
}

/**
 * @brief 3rd test-case
 * @returns void
 */
void test3() {
    others::recursive_tree_traversals::BT obj3;
    others::recursive_tree_traversals::Node *root = obj3.createNewNode(1);
    root->left = obj3.createNewNode(2);
    root->right = obj3.createNewNode(3);
    root->left->left = obj3.createNewNode(4);
    root->left->right = obj3.createNewNode(5);

    std::vector<uint64_t> actual_result_inorder{4, 2, 5, 1, 3};
    std::vector<uint64_t> actual_result_preorder{1, 2, 4, 5, 3};
    std::vector<uint64_t> actual_result_postorder{4, 5, 2, 3, 1};
    std::vector<uint64_t> result_inorder;    ///< result stores the inorder
                                             ///< traversal of the binary tree
    std::vector<uint64_t> result_preorder;   ///< result stores the preorder
                                             ///< traversal of the binary tree
    std::vector<uint64_t> result_postorder;  ///< result stores the postorder
                                             ///< traversal of the binary tree

    uint64_t size = actual_result_inorder.size();

    // Calling inorder() function by passing a root node,
    // and storing the inorder traversal in result_inorder.

    result_inorder = obj3.inorder(root);
    std::cout << "Testcase #3: Inorder Traversal...";
    for (auto i = 0; i < size; ++i) {
        assert(actual_result_inorder[i] == result_inorder[i]);
    }
    std::cout << "Passed!" << std::endl;

    // Calling preorder() function by passing a root node,
    // and storing the preorder traversal in result_preorder.
    result_preorder = obj3.preorder(root);
    std::cout << "Testcase #3: Preorder Traversal...";
    for (auto i = 0; i < size; ++i) {
        assert(actual_result_preorder[i] == result_preorder[i]);
    }
    std::cout << "Passed!" << std::endl;

    // Calling postorder() function by passing a root node,
    // and storing the postorder traversal in result_postorder.
    result_postorder = obj3.postorder(root);
    std::cout << "Testcase #3: Postorder Traversal...";
    for (auto i = 0; i < size; ++i) {
        assert(actual_result_postorder[i] == result_postorder[i]);
    }
    std::cout << "Passed!" << std::endl;

    std::cout << std::endl;
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    std::cout << "1st test-case" << std::endl;
    test1();  // run 1st test-case
    std::cout << "2nd test-case" << std::endl;
    test2();  // run 2nd test-case
    std::cout << "3rd test-case" << std::endl;
    test3();  // run 3rd test-case
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // run self-test implementations
    return 0;
}
