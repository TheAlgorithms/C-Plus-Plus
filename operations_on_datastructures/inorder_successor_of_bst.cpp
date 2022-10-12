/**
 * @file
 * @brief An implementation for finding the [Inorder successor of a binary
 * search tree](https://www.youtube.com/watch?v=5cPbNCrdotA) Inorder
 * successor of a node is the next node in Inorder traversal of the Binary Tree.
 * Inorder Successor is NULL for the last node in Inorder traversal.
 * @details
 * ### Case 1: The given node has the right node/subtree
 *
 *      * In this case, the left-most deepest node in the right subtree will
 * come just after the given node as we go to left deep in inorder.
 *      - Go deep to left most node in right subtree.
 *        OR, we can also say in case if BST, find the minimum of the subtree
 * for a given node.
 *
 * ### Case 2: The given node does not have a right node/subtree
 *
 * #### Method 1: Use parent pointer (store the address of parent nodes)
 *      * If a node does not have the right subtree, and we already visited the
 * node itself, then the next node will be its parent node according to inorder
 * traversal, and if we are going to parent from left, then the parent would be
 * unvisited.
 *      * In other words, go to the nearest ancestor for which given node would
 * be in left subtree.
 *
 * #### Method 2: Search from the root node
 *      * In case if there is no link from a child node to the parent node, we
 * need to walk down the tree starting from the root node to the given node, by
 * doing so, we are visiting every ancestor of the given node.
 *      * In order successor would be the deepest node in this path for which
 * given node is in left subtree.
 *
 * @author [Nitin Sharma](https://github.com/foo290)
 * */

#include <cassert>   ///  for assert
#include <iostream>  ///  for IO Operations
#include <vector>    ///  for std::vector

/**
 * @namespace operations_on_datastructures
 * @brief Operations on data structures
 */
namespace operations_on_datastructures {

/**
 * @namespace inorder_successor_of_bst
 * @brief Functions for the [Inorder successor of a binary search
 * tree](https://www.youtube.com/watch?v=5cPbNCrdotA) implementation
 */
namespace inorder_traversal_of_bst {

/**
 * @brief A Node structure representing a single node in BST
 */
class Node {
 public:
    int64_t data;  ///< The key/value of the node
    Node *left;    ///< Pointer to Left child
    Node *right;   ///< Pointer to right child
};

/**
 * @brief Allocates a new node in heap for given data and returns it's pointer.
 * @param data Data for the node.
 * @returns A pointer to the newly allocated Node.
 * */
Node *makeNode(int64_t data) {
    Node *node = new Node();
    node->data = data;      ///< setting data for node
    node->left = nullptr;   ///< setting left child as null
    node->right = nullptr;  ///< setting right child as null
    return node;
}

/**
 * @brief Inserts the given data in BST while maintaining the properties of BST.
 * @param root Pointer to the root node of the BST
 * @param data Data to be inserted.
 * @returns Node* Pointer to the root node.
 * */
Node *Insert(Node *root, int64_t data) {
    if (root == nullptr) {
        root = makeNode(data);
    } else if (data <= root->data) {
        root->left = Insert(root->left, data);
    } else {
        root->right = Insert(root->right, data);
    }
    return root;
}

/**
 * @brief Searches the given data in BST and returns the pointer to the node
 * containing that data.
 * @param root Pointer to the root node of the BST
 * @param data Data to be Searched.
 * @returns Node* pointer to the found node
 * */
Node *getNode(Node *root, int64_t data) {
    if (root == nullptr) {
        return nullptr;
    } else if (root->data == data) {
        return root;  /// Node found!
    } else if (data > root->data) {
        /// Traverse right subtree recursively as the given data is greater than
        /// the data in root node, data must be present in right subtree.
        return getNode(root->right, data);
    } else {
        /// Traverse left subtree recursively as the given data is less than the
        /// data in root node, data must be present in left subtree.
        return getNode(root->left, data);
    }
}

/**
 * @brief Finds and return the minimum node in BST.
 * @param root A pointer to root node.
 * @returns Node* Pointer to the found node
 * */
Node *findMinNode(Node *root) {
    if (root == nullptr) {
        return root;
    }
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

/**
 * @brief Prints the BST in inorder traversal using recursion.
 * @param root A pointer to the root node of the BST.
 * @returns void
 * */
void printInorder(Node *root) {
    if (root == nullptr) {
        return;
    }

    printInorder(root->left);  /// recursive call to left subtree
    std::cout << root->data << " ";
    printInorder(root->right);  /// recursive call to right subtree
}

/**
 * @brief This function is used in test cases to quickly create BST containing
 * large data instead of hard coding it in code. For a given root, this will add
 * all the nodes containing data passes in data vector.
 * @param root Pointer to the root node.
 * @param data A vector containing integer values which are suppose to be
 * inserted as nodes in BST.
 * @returns Node pointer to the root node.
 * */
Node *makeBST(Node *root, const std::vector<int64_t> &data) {
    for (int64_t values : data) {
        root = Insert(root, values);
    }
    return root;
}

/**
 * @brief Inorder successor of a node is the next node in inorder traversal of
 * the Binary Tree. This function takes the root node and the data of the node
 * for which we have to find the inorder successor, and returns the inorder
 * successor node.
 * @details Search from the root node as we need to walk the tree starting from
 * the root node to the given node, by doing so, we are visiting every ancestor
 * of the given node. In order successor would be the deepest node in this path
 * for which given node is in left subtree. Time complexity O(h)
 * @param root A pointer to the root node of the BST
 * @param data The data (or the data of node) for which we have to find inorder
 * successor.
 * @returns Node pointer to the inorder successor node.
 * */
Node *getInorderSuccessor(Node *root, int64_t data) {
    Node *current = getNode(root, data);
    if (current == nullptr) {
        return nullptr;
    }

    // Case - 1
    if (current->right != nullptr) {
        return findMinNode(current->right);
    }
    // case - 2
    else {
        Node *successor = nullptr;
        Node *ancestor = root;

        while (ancestor != current && ancestor != nullptr) {
            // This means my current node is in left of the root node
            if (current->data < ancestor->data) {
                successor = ancestor;
                ancestor = ancestor->left;  // keep going left
            } else {
                ancestor = ancestor->right;
            }
        }
        return successor;  // Nodes with maximum vales will not have a successor
    }
}

/**
 * @brief This function clears the memory allocated to entire tree recursively.
 * Its just for clean up the memory and not relevant to the actual topic.
 * @param root Root node of the tree.
 * @returns void
 * */
void deallocate(Node *rootNode) {
    if (rootNode == nullptr) {
        return;
    }
    deallocate(rootNode->left);
    deallocate(rootNode->right);
    delete (rootNode);
}

}  // namespace inorder_traversal_of_bst
}  // namespace operations_on_datastructures

/**
 * @brief class encapsulating the necessary test cases
 */
class TestCases {
 private:
    /**
     * @brief A function to print given message on console.
     * @tparam T Type of the given message.
     * @returns void
     * */
    template <typename T>
    void log(T msg) {
        // It's just to avoid writing cout and endl
        std::cout << "[TESTS] : ---> " << msg << std::endl;
    }

 public:
    /**
     * @brief Executes test cases
     * @returns void
     * */
    void runTests() {
        log("Running Tests...");

        testCase_1();
        testCase_2();
        testCase_3();

        log("Test Cases over!");
        std::cout << std::endl;
    }

    /**
     * @brief A test case contains edge case, printing inorder successor of last
     * node.
     * @returns void
     * */
    void testCase_1() {
        const operations_on_datastructures::inorder_traversal_of_bst::Node
            *expectedOutput = nullptr;  ///< Expected output of this test

        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        log("This is test case 1 : ");
        log("Description:");
        log("   EDGE CASE : Printing inorder successor for last node in the "
            "BST, Output will be nullptr.");

        operations_on_datastructures::inorder_traversal_of_bst::Node *root =
            nullptr;
        std::vector<int64_t> node_data{
            20, 3, 5, 6, 2, 23, 45, 78, 21};  ///< Data to make nodes in BST

        root = operations_on_datastructures::inorder_traversal_of_bst::makeBST(
            root,
            node_data);  ///< Adding nodes to BST

        std::cout << "Inorder sequence is : ";
        operations_on_datastructures::inorder_traversal_of_bst::printInorder(
            root);  ///< Printing inorder to cross-verify.
        std::cout << std::endl;

        operations_on_datastructures::inorder_traversal_of_bst::Node
            *inorderSuccessor = operations_on_datastructures::
                inorder_traversal_of_bst::getInorderSuccessor(
                    root, 78);  ///< The inorder successor node for given data

        log("Checking assert expression...");
        assert(inorderSuccessor == expectedOutput);
        log("Assertion check passed!");

        operations_on_datastructures::inorder_traversal_of_bst::deallocate(
            root);  /// memory cleanup!

        log("[PASS] : TEST CASE 1 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }

    /**
     * @brief A test case which contains main list of 100 elements and sublist
     * of 20.
     * @returns void
     * */
    void testCase_2() {
        const int expectedOutput = 21;  ///< Expected output of this test

        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        log("This is test case 2 : ");

        operations_on_datastructures::inorder_traversal_of_bst::Node *root =
            nullptr;
        std::vector<int64_t> node_data{
            20, 3, 5, 6, 2, 23, 45, 78, 21};  ///< Data to make nodes in BST

        root = operations_on_datastructures::inorder_traversal_of_bst::makeBST(
            root,
            node_data);  ///< Adding nodes to BST

        std::cout << "Inorder sequence is : ";
        operations_on_datastructures::inorder_traversal_of_bst::printInorder(
            root);  ///< Printing inorder to cross-verify.
        std::cout << std::endl;

        operations_on_datastructures::inorder_traversal_of_bst::Node
            *inorderSuccessor = operations_on_datastructures::
                inorder_traversal_of_bst::getInorderSuccessor(
                    root, 20);  ///< The inorder successor node for given data

        log("Checking assert expression...");
        assert(inorderSuccessor->data == expectedOutput);
        log("Assertion check passed!");

        operations_on_datastructures::inorder_traversal_of_bst::deallocate(
            root);  /// memory cleanup!

        log("[PASS] : TEST CASE 2 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }

    /**
     * @brief A test case which contains main list of 50 elements and sublist
     * of 20.
     * @returns void
     * */
    void testCase_3() {
        const int expectedOutput = 110;  ///< Expected output of this test

        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        log("This is test case 3 : ");

        operations_on_datastructures::inorder_traversal_of_bst::Node *root =
            nullptr;
        std::vector<int64_t> node_data{
            89,  67,  32, 56, 90, 123, 120,
            110, 115, 6,  78, 7,  10};  ///< Data to make nodes in BST

        root = operations_on_datastructures::inorder_traversal_of_bst::makeBST(
            root,
            node_data);  ///< Adding nodes to BST

        std::cout << "Inorder sequence is : ";
        operations_on_datastructures::inorder_traversal_of_bst::printInorder(
            root);  ///< Printing inorder to cross-verify.
        std::cout << std::endl;

        operations_on_datastructures::inorder_traversal_of_bst::Node
            *inorderSuccessor = operations_on_datastructures::
                inorder_traversal_of_bst::getInorderSuccessor(
                    root, 90);  ///< The inorder successor node for given data

        log("Checking assert expression...");
        assert(inorderSuccessor->data == expectedOutput);
        log("Assertion check passed!");

        operations_on_datastructures::inorder_traversal_of_bst::deallocate(
            root);  /// memory cleanup!

        log("[PASS] : TEST CASE 3 PASS!");
        log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }
};

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    TestCases tc;
    tc.runTests();
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();  // run self-test implementations

    operations_on_datastructures::inorder_traversal_of_bst::Node *root =
        nullptr;  ///< root node of the bst
    std::vector<int64_t> node_data{3,  4, 5,
                                   89, 1, 2};  ///< Data to add nodes in BST

    int64_t targetElement = 4;  ///< An element to find inorder successor for.
    root = operations_on_datastructures::inorder_traversal_of_bst::makeBST(
        root, node_data);  ///< Making BST

    operations_on_datastructures::inorder_traversal_of_bst::Node
        *inorderSuccessor = operations_on_datastructures::
            inorder_traversal_of_bst::getInorderSuccessor(root, targetElement);

    std::cout << "In-order sequence is : ";
    operations_on_datastructures::inorder_traversal_of_bst::printInorder(root);
    std::cout << std::endl;

    if (inorderSuccessor == nullptr) {
        std::cout << "Inorder successor for last node is NULL" << std::endl;
    } else {
        std::cout << "Target element is : " << targetElement << std::endl;
        std::cout << "Inorder successor for target element is : "
                  << inorderSuccessor->data << std::endl;
    }

    deallocate(root);  /// memory cleanup!

    return 0;
}
