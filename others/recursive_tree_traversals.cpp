/********************************************************************************
 * @file
 * @brief Recursive version of Inorder, Preorder, and Postorder [Traversal of
 *the Tree] (https://en.wikipedia.org/wiki/Tree_traversal)
 * @author [Lajat Manekar](https://github.com/Lazeeez)
 * @details
 *
 * ### Recursive Inorder Traversal of a tree
 * Before processing any node, the left subtree is processed first, followed by
 * the node, and the right subtree is processed at last. These operations can
 * be defined recursively for each node. The recursive implementation is
 *referred to as a Depth-First Search (DFS), as the search tree is deepened as
 *much as possible on each child before going to the next sibling.
 *
 * ### Recursive Preorder Traversal of a tree
 * Only after processing any node, the left subtree is processed, followed by
 * the right subtree is processed. These operations can be defined recursively
 * for each node. The recursive implementation is referred to as a Depth-First
 *Search (DFS), as the search tree is deepened as much as possible on each child
 *before going to the next sibling.
 *
 * ### Recursive Postorder Traversal of a tree
 * Before processing any node, the left subtree is processed first, followed by
 * the right subtree, and the node is processed at last. These operations can
 * be defined recursively for each node. The recursive implementation is
 *referred to as a Depth-First Search (DFS), as the search tree is deepened as
 *much as possible on each child before going to the next sibling.
 *******************************************************************************/
#include <cassert>   /// for `assert`
#include <iostream>  /// for I/O operations
#include <vector>    /// for `vector`

/********************************************************************************
 *@namespace Results
 *@brief To be used to store the results
 *******************************************************************************/
namespace results {

std::vector<int64_t> inorder_result;   ///< list of values, sorted in in-order.
std::vector<int64_t> preorder_result;  ///< list of values, sorted in pre-order.
std::vector<int64_t>
    postorder_result;  ///< list of values, sorted in post-order.
}  // namespace results

/********************************************************************************
 * @namespace others
 * @brief Other algorithms
 *******************************************************************************/
namespace others {

/*******************************************************************************
 * @namespace recursive_tree_traversals
 * @brief Functions for the [Traversal of the
 *Tree](https://en.wikipedia.org/wiki/Tree_traversal) algorithm
 *******************************************************************************/
namespace recursive_tree_traversals {

/*******************************************************************************
 * @brief Defines the structure of a node of the tree
 *******************************************************************************/
struct Node {
    int64_t data = 0;      ///< The value/key of the node.
    struct Node *left{};   ///< Struct pointer to left subtree.
    struct Node *right{};  ///< Struct pointer to right subtree.
};

/*******************************************************************************
 * @brief Defines the functions associated with the binary tree
 *******************************************************************************/
class BinaryTree {
 public:
    Node *createNewNode(
        int64_t);  ///< Function that will create new node for insertion.
    std::vector<int64_t> inorder(
        Node *);  ///< Function that takes root of the tree as an argument, and
                  ///< returns its postorder traversal.
    std::vector<int64_t> preorder(
        Node *);  ///< Function that takes root of the tree as an argument, and
                  ///< returns its preorder traversal.
    std::vector<int64_t> postorder(
        Node *);  ///< Function that takes root of the tree as an argument, and
                  ///< returns its postorder traversal.
};

/*******************************************************************************
 * @brief Will allocate the memory for a node and along the data and return the
 *node.
 * @param data value that a particular node will contain.
 * @return Pointer to the newly created node with assigned data.
 *******************************************************************************/
Node *BinaryTree::createNewNode(int64_t data) {
    auto *node = new Node();
    node->data = data;
    node->left = node->right = nullptr;
    return node;
}

/*******************************************************************************
 * @brief inorder() function that will perform the inorder traversal
 *recursively, and return the result array that contain the inorder traversal of
 *a tree.
 * @param root head/root node of a tree
 * @return result that is containing the inorder traversal of a tree
 *******************************************************************************/
std::vector<int64_t> BinaryTree::inorder(Node *root) {
    if (root == nullptr) {  ///< return if the current node is empty
        return {};
    }

    BinaryTree::inorder(root->left);  ///< Traverse the left subtree
    results::inorder_result.push_back(
        root->data);  ///< Display the data part of the root (or current node)
    BinaryTree::inorder(root->right);  ///< Traverse the right subtree
    return results::inorder_result;
}

/*******************************************************************************
 * @brief preorder() function that will perform the preorder traversal
 *recursively, and return the result array that contain the preorder traversal
 *of a tree.
 * @param root head/root node of a tree
 * @return result that is containing the preorder traversal of a tree
 *******************************************************************************/
std::vector<int64_t> BinaryTree::preorder(Node *root) {
    if (root == nullptr) {  ///< if the current node is empty
        return {};
    }

    results::preorder_result.push_back(
        root->data);  ///< Display the data part of the root (or current node)
    BinaryTree::preorder(root->left);   ///< Traverse the left subtree
    BinaryTree::preorder(root->right);  ///< Traverse the right subtree
    return results::preorder_result;
}

/*******************************************************************************
 * @brief postorder() function that will perform the postorder traversal
 *recursively, and return the result array that contain the postorder traversal
 *of a tree.
 * @param root head/root node of a tree
 * @return result that is containing the postorder traversal of a tree
 *******************************************************************************/
std::vector<int64_t> BinaryTree::postorder(Node *root) {
    if (root == nullptr) {  ///< if the current node is empty
        return {};
    }

    BinaryTree::postorder(root->left);   ///< Traverse the left subtree
    BinaryTree::postorder(root->right);  ///< Traverse the right subtree
    results::postorder_result.push_back(
        root->data);  ///< Display the data part of the root (or current node)
    return results::postorder_result;
}
}  // namespace recursive_tree_traversals
}  // namespace others

/*******************************************************************************
 * @brief Self-test implementations #1
 * @returns void
 *******************************************************************************/

static void test1() {
    /*******************************************************************************
     *   Creating a tree with the following structure.
     *               2
     *             /  \
     *            /    \
     *           7      5
     *          / \      \
     *         2   6      9
     *            / \    /
     *           5   11 4
     *
     *******************************************************************************/

    others::recursive_tree_traversals::BinaryTree
        binaryTree;  ///< instace of BinaryTree, used to access its members
                     ///< functions.
    others::recursive_tree_traversals::Node *root = binaryTree.createNewNode(2);

    root->left = binaryTree.createNewNode(7);
    root->right = binaryTree.createNewNode(5);
    root->left->left = binaryTree.createNewNode(2);
    root->left->right = binaryTree.createNewNode(6);
    root->right->right = binaryTree.createNewNode(9);
    root->left->right->left = binaryTree.createNewNode(5);
    root->left->right->right = binaryTree.createNewNode(11);
    root->right->right->left = binaryTree.createNewNode(4);

    std::vector<int64_t> actual_result_inorder{2, 7, 5, 6, 11, 2, 5, 4, 9};
    std::vector<int64_t> actual_result_preorder{2, 7, 2, 6, 5, 11, 5, 9, 4};
    std::vector<int64_t> actual_result_postorder{2, 5, 11, 6, 7, 4, 9, 5, 2};
    std::vector<int64_t> result_inorder;
    std::vector<int64_t> result_preorder;
    std::vector<int64_t> result_postorder;

    uint64_t size = actual_result_inorder.size();

    // inorder traversal
    result_inorder = binaryTree.inorder(
        root);  ///< Calling inorder() function by passing a root node and
                ///< storing the inorder traversal in result_inorder.
    std::cout << "Test1 Inorder Traversal...";
    for (int i = 0; i < size; ++i) {
        assert(actual_result_inorder[i] ==
               result_inorder[i]);  ///< Self-testing the result using `assert`
    }
    std::cout << "Passed" << std::endl;

    // preorder traversal
    result_preorder = binaryTree.preorder(
        root);  ///< Calling preorder() function by passing a root node and
                ///< storing the preorder traversal in result_preorder.
    std::cout << "Test1 Preorder Traversal...";
    for (int i = 0; i < size; ++i) {
        assert(actual_result_preorder[i] ==
               result_preorder[i]);  ///< Self-testing the result using `assert`
    }
    std::cout << "Passed" << std::endl;

    // postorder traversal
    result_postorder = binaryTree.postorder(
        root);  ///< Calling postorder() function by passing a root node and
                ///< storing the postorder traversal in result_postorder.
    std::cout << "Test1 Postorder Traversal...";
    for (int i = 0; i < size; ++i) {
        assert(
            actual_result_postorder[i] ==
            result_postorder[i]);  ///< Self-testing the result using `assert`
    }
    std::cout << "Passed" << std::endl;

    std::cout << std::endl;
}

/*******************************************************************************
 * @brief Self-test implementations #2
 * @returns void
 *******************************************************************************/

static void test2() {
    /*******************************************************************************
     *   Creating a tree with the following structure.
     *               1
     *             /  \
     *            /    \
     *           2      3
     *          /      /  \
     *         4      5    6
     *               / \
     *              7   8
     *
     *
     *******************************************************************************/

    others::recursive_tree_traversals::BinaryTree
        binaryTree;  ///< instace of BinaryTree, used to access its members
                     ///< functions.
    others::recursive_tree_traversals::Node *root = binaryTree.createNewNode(1);

    root->left = binaryTree.createNewNode(2);
    root->right = binaryTree.createNewNode(3);
    root->left->left = binaryTree.createNewNode(4);
    root->right->left = binaryTree.createNewNode(5);
    root->right->right = binaryTree.createNewNode(6);
    root->right->left->left = binaryTree.createNewNode(7);
    root->right->left->right = binaryTree.createNewNode(8);

    std::vector<int64_t> actual_result_inorder{4, 2, 1, 7, 5, 8, 3, 6};
    std::vector<int64_t> actual_result_preorder{1, 2, 4, 3, 5, 7, 8, 6};
    std::vector<int64_t> actual_result_postorder{4, 2, 7, 8, 5, 6, 3, 1};
    std::vector<int64_t> result_inorder;
    std::vector<int64_t> result_preorder;
    std::vector<int64_t> result_postorder;

    uint64_t size = actual_result_inorder.size();

    // inorder traversal
    result_inorder = binaryTree.inorder(
        root);  ///< Calling inorder() function by passing a root node and
                ///< storing the inorder traversal in result_inorder.
    std::cout << "Test2 Inorder Traversal...";
    for (int i = 0; i < size; ++i) {
        assert(actual_result_inorder[i] ==
               result_inorder[i]);  ///< Self-testing the result using `assert`
    }
    std::cout << "Passed" << std::endl;

    // preorder traversal
    result_preorder = binaryTree.preorder(
        root);  ///< Calling preorder() function by passing a root node and
                ///< storing the preorder traversal in result_preorder.
    std::cout << "Test2 Preorder Traversal...";
    for (int i = 0; i < size; ++i) {
        assert(actual_result_preorder[i] ==
               result_preorder[i]);  ///< Self-testing the result using `assert`
    }
    std::cout << "Passed" << std::endl;

    // postorder traversal
    result_postorder = binaryTree.postorder(
        root);  ///< Calling postorder() function by passing a root node and
                ///< storing the postorder traversal in result_postorder.
    std::cout << "Test2 Postorder Traversal...";
    for (int i = 0; i < size; ++i) {
        assert(
            actual_result_postorder[i] ==
            result_postorder[i]);  ///< Self-testing the result using `assert`
    }
    std::cout << "Passed" << std::endl;

    std::cout << std::endl;
}

/*******************************************************************************
 * @brief Self-test implementations #3
 * @returns void
 *******************************************************************************/

static void test3() {
    /*******************************************************************************
     *   Creating a tree with the following structure.
     *             1
     *            / \
     *           2   3
     *          / \
     *         4   5
     *
     *******************************************************************************/

    others::recursive_tree_traversals::BinaryTree
        binaryTree;  ///< instace of BinaryTree, used to access its members
                     ///< functions.
    others::recursive_tree_traversals::Node *root = binaryTree.createNewNode(1);

    root->left = binaryTree.createNewNode(2);
    root->right = binaryTree.createNewNode(3);
    root->left->left = binaryTree.createNewNode(4);
    root->left->right = binaryTree.createNewNode(5);

    std::vector<int64_t> actual_result_inorder{4, 2, 5, 1, 3};
    std::vector<int64_t> actual_result_preorder{1, 2, 4, 5, 3};
    std::vector<int64_t> actual_result_postorder{4, 5, 2, 3, 1};
    std::vector<int64_t> result_inorder;
    std::vector<int64_t> result_preorder;
    std::vector<int64_t> result_postorder;

    uint64_t size = actual_result_inorder.size();

    // inorder traversal
    result_inorder = binaryTree.inorder(
        root);  ///< Calling inorder() function by passing a root node and
                ///< storing the inorder traversal in result_inorder.
    std::cout << "Test3 Inorder Traversal...";
    for (int i = 0; i < size; ++i) {
        assert(actual_result_inorder[i] ==
               result_inorder[i]);  ///< Self-testing the result using `assert`
    }
    std::cout << "Passed" << std::endl;

    // preorder traversal
    result_preorder = binaryTree.preorder(
        root);  ///< Calling preorder() function by passing a root node and
                ///< storing the preorder traversal in result_preorder.
    std::cout << "Test3 Preorder Traversal...";
    for (int i = 0; i < size; ++i) {
        assert(actual_result_preorder[i] ==
               result_preorder[i]);  ///< Self-testing the result using `assert`
    }
    std::cout << "Passed" << std::endl;

    // postorder traversal
    result_postorder = binaryTree.postorder(
        root);  ///< Calling postorder() function by passing a root node and
                ///< storing the postorder traversal in result_postorder.
    std::cout << "Test3 Postorder Traversal...";
    for (int i = 0; i < size; ++i) {
        assert(
            actual_result_postorder[i] ==
            result_postorder[i]);  ///< Self-testing the result using `assert`
    }
    std::cout << "Passed" << std::endl;

    std::cout << std::endl;
}

/*******************************************************************************
 * @brief Self-test implementations #4
 * @returns void
 *******************************************************************************/

static void test4() {  ///< Testcase with negative numbers
    /*******************************************************************************
     *   Creating a tree with the following structure.
     *               -1
     *              /  \
     *            -2   -3
     *           /  \
     *         -4   -5
     *
     *******************************************************************************/

    others::recursive_tree_traversals::BinaryTree
        binaryTree;  ///< instace of BinaryTree, used to access its members
                     ///< functions.
    others::recursive_tree_traversals::Node *root = binaryTree.createNewNode(1);

    root->left = binaryTree.createNewNode(2);
    root->right = binaryTree.createNewNode(3);
    root->left->left = binaryTree.createNewNode(4);
    root->left->right = binaryTree.createNewNode(5);

    root->data = -1;
    root->left->data = -2;
    root->right->data = -3;
    root->left->left->data = -4;
    root->left->right->data = -5;

    std::vector<int64_t> actual_result_inorder{-4, -2, -5, -1, -3};
    std::vector<int64_t> actual_result_preorder{-1, -2, -4, -5, -3};
    std::vector<int64_t> actual_result_postorder{-4, -5, -2, -3, -1};
    std::vector<int64_t> result_inorder;
    std::vector<int64_t> result_preorder;
    std::vector<int64_t> result_postorder;

    uint64_t size = actual_result_inorder.size();

    // inorder traversal
    result_inorder = binaryTree.inorder(
        root);  ///< run inorder-recursive test on negative values
    std::cout << "Test4 Inorder Traversal...";
    for (int i = 0; i < size; ++i) {
        assert(actual_result_inorder[i] ==
               result_inorder[i]);  ///< Self-testing the result using `assert`
    }
    std::cout << "Passed" << std::endl;

    // preorder traversal
    result_preorder = binaryTree.preorder(
        root);  ///< run preorder-recursive test on negative values
    std::cout << "Test4 Preorder Traversal...";
    for (int i = 0; i < size; ++i) {
        assert(actual_result_preorder[i] ==
               result_preorder[i]);  ///< Self-testing the result using `assert`
    }
    std::cout << "Passed" << std::endl;

    // postorder traversal
    result_postorder = binaryTree.postorder(
        root);  ///< run postorder-recursive test on negative values
    std::cout << "Test4 Postorder Traversal...";
    for (int i = 0; i < size; ++i) {
        assert(
            actual_result_postorder[i] ==
            result_postorder[i]);  ///< Self-testing the result using `assert`
    }
    std::cout << "Passed" << std::endl;

    std::cout << std::endl;
}

/********************************************************************************
 * @brief Main function
 * @returns 0 on exit
 *******************************************************************************/

int main() {
    std::cout << "TestCase #1" << std::endl;  ///< Testcase #1
    test1();
    results::inorder_result.clear();
    results::preorder_result.clear();
    results::postorder_result.clear();

    std::cout << "TestCase #2" << std::endl;  ///< Testcase #2
    test2();
    results::inorder_result.clear();
    results::preorder_result.clear();
    results::postorder_result.clear();

    std::cout << "TestCase #3" << std::endl;  ///< Testcase #3
    test3();
    results::inorder_result.clear();
    results::preorder_result.clear();
    results::postorder_result.clear();

    std::cout << "TestCase #4" << std::endl;  ///< Testcase #4
    test4();
    results::inorder_result.clear();
    results::preorder_result.clear();
    results::postorder_result.clear();

    return 0;
}