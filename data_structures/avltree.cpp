/**
 * @file
 * @brief An implementation of AVL tree.
 */
#include <algorithm>  /// for std::max
#include <cassert>    /// for assert
#include <iostream>   /// for std::cout
#include <memory>     /// for std::unique_ptr
#include <queue>      /// for std::queue
#include <sstream>    /// for std::ostringstream
#include <vector>     /// for std::vector

/**
 * @brief Class for AVL tree.
 * @details AVL tree is a self-balancing binary search tree where the difference
 * between heights of left and right subtrees cannot be more than one for all
 * nodes.
 */
class AVLTree {
 public:
    /**
     * @brief Node structure for AVL tree
     * @details Contains the data, height of the node and pointers to left and
     * right child nodes.
     */
    struct Node {
        int data;
        int height;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        /**
         * @brief Constructor for Node, used to simplify node and
         * smart pointer construction.
         * @param val the value of the node
         */
        Node(int val) : data(val), height(1), left(nullptr), right(nullptr) {}
    };

    AVLTree() : root(nullptr) {}

    /**
     * @brief inserts a new element into AVL tree
     * @param root of the tree
     * @param[in] data the element to be insterted into the tree
     * @return root of the updated tree
     */
    void insert(int data) { root = insert(std::move(root), data); }

    /**
     * @brief removes a given element from AVL tree
     * @param root of the tree
     * @param[in] data the element to be deleted from the tree
     * @return root of the updated tree
     */
    void deleteNode(int data) { root = deleteNode(std::move(root), data); }

    /**
     * @brief prints given tree in the LevelOrder
     * @param[in] root of the tree
     */
    void levelOrder() const {
        if (!root)
            return;
        std::queue<Node*> q;
        q.push(root.get());
        while (!q.empty()) {
            Node* current = q.front();
            std::cout << current->data << " ";
            q.pop();
            if (current->left)
                q.push(current->left.get());
            if (current->right)
                q.push(current->right.get());
        }
        std::cout << "\n";
    }

    /**
     * @brief deletes the tree
     */
    void deleteTree() { root.reset(); }

 private:
    std::unique_ptr<Node> root;

    /**
     * @brief returns the height of the node
     * @param[in] node the node whose height is to be calculated
     * @return height of the node
     */
    int height(const std::unique_ptr<Node>& node) const {
        return node ? node->height : 0;
    }

    /**
     * @brief returns the balance factor of the node
     * @param[in] node the node whose balance factor is to be calculated
     * @return balance factor(difference between height of left and right
     * subtree) of the node
     */
    int getBalance(const std::unique_ptr<Node>& node) const {
        return node ? height(node->left) - height(node->right) : 0;
    }

    /**
     * @brief rotates the node to the right
     * @param[in] y the node to be rotated
     * @return the new root of the subtree
     */
    std::unique_ptr<Node> rightRotate(std::unique_ptr<Node> y) {
        std::unique_ptr<Node> x = std::move(y->left);
        y->left = std::move(x->right);
        x->right = std::move(y);
        x->right->height =
            std::max(height(x->right->left), height(x->right->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;
        return x;
    }

    /**
     * @brief rotates the node to the left
     * @param[in] node the node to be rotated
     * @return the new root of the subtree
     */
    std::unique_ptr<Node> leftRotate(std::unique_ptr<Node> x) {
        std::unique_ptr<Node> y = std::move(x->right);
        x->right = std::move(y->left);
        y->left = std::move(x);
        y->left->height =
            std::max(height(y->left->left), height(y->left->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;
        return y;
    }

    /**
     * @brief inserts a new element into AVL tree
     * @param root of the tree
     * @param[in] data the element to be insterted into the tree
     * @return root of the updated tree
     */
    std::unique_ptr<Node> insert(std::unique_ptr<Node> node, int data) {
        if (!node)
            return std::make_unique<Node>(data);

        if (data < node->data) {
            node->left = insert(std::move(node->left), data);
        } else if (data > node->data) {
            node->right = insert(std::move(node->right), data);
        } else {
            return node;
        }

        node->height = std::max(height(node->left), height(node->right)) + 1;
        int balance = getBalance(node);

        if (balance > 1 && data < node->left->data) {
            return rightRotate(std::move(node));
        }
        if (balance < -1 && data > node->right->data) {
            return leftRotate(std::move(node));
        }
        if (balance > 1 && data > node->left->data) {
            node->left = leftRotate(std::move(node->left));
            return rightRotate(std::move(node));
        }
        if (balance < -1 && data < node->right->data) {
            node->right = rightRotate(std::move(node->right));
            return leftRotate(std::move(node));
        }

        return node;
    }

    /**
     * @brief removes a given element from AVL tree
     * @param root of the tree
     * @param[in] data the element to be deleted from the tree
     * @return root of the updated tree
     */
    std::unique_ptr<Node> deleteNode(std::unique_ptr<Node> root, int data) {
        if (!root)
            return root;

        if (data < root->data) {
            root->left = deleteNode(std::move(root->left), data);
        } else if (data > root->data) {
            root->right = deleteNode(std::move(root->right), data);
        } else {
            if (!root->left || !root->right) {
                return std::move(root->left ? root->left : root->right);
            }

            Node* temp = minValue(root->right.get());
            root->data = temp->data;
            root->right = deleteNode(std::move(root->right), temp->data);
        }

        root->height = std::max(height(root->left), height(root->right)) + 1;
        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0) {
            return rightRotate(std::move(root));
        }
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(std::move(root->left));
            return rightRotate(std::move(root));
        }
        if (balance < -1 && getBalance(root->right) <= 0) {
            return leftRotate(std::move(root));
        }
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(std::move(root->right));
            return leftRotate(std::move(root));
        }

        return root;
    }

    /**
     * @brief returns the node with minimum value in the tree
     * @param[in] node the root of the tree
     * @return the node with minimum value in the tree
     */
    Node* minValue(Node* node) {
        Node* current = node;
        while (current->left != nullptr) current = current->left.get();
        return current;
    }
};

/**
 * @brief Function for testing insert().
 *
 * @returns void
 */
static void test_insert() {
    std::cout << "Testing AVL insert...";

    AVLTree tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(6);

    std::ostringstream oss;
    std::streambuf* old_cout =
        std::cout.rdbuf(oss.rdbuf());  // Redirect std::cout to oss
    tree.levelOrder();
    std::cout.rdbuf(old_cout);  // Restore std::cout
    std::string output = oss.str();
    output.erase(std::remove_if(output.begin(), output.end(), ::isspace),
                 output.end());  // Remove whitespaces
    assert(output == "4356");

    tree.insert(7);
    tree.insert(2);
    tree.insert(1);

    oss.str("");
    oss.clear();
    std::cout.rdbuf(oss.rdbuf());
    tree.levelOrder();
    std::cout.rdbuf(old_cout);
    output = oss.str();
    output.erase(std::remove_if(output.begin(), output.end(), ::isspace),
                 output.end());
    assert(output == "4261357");

    std::cout << "ok" << std::endl;
}

/**
 * @brief Function for testing deleteNode().
 *
 * @returns void
 */
static void test_deleteNode() {
    std::cout << "Testing AVL deleteNode...";

    AVLTree tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(6);

    tree.deleteNode(5);

    std::ostringstream oss;
    std::streambuf* old_cout = std::cout.rdbuf(oss.rdbuf());
    tree.levelOrder();
    std::cout.rdbuf(old_cout);
    std::string output = oss.str();
    output.erase(std::remove_if(output.begin(), output.end(), ::isspace),
                 output.end());
    assert(output == "436");

    tree.deleteNode(4);
    tree.deleteNode(3);

    oss.str("");
    oss.clear();
    std::cout.rdbuf(oss.rdbuf());
    tree.levelOrder();
    std::cout.rdbuf(old_cout);
    output = oss.str();
    output.erase(std::remove_if(output.begin(), output.end(), ::isspace),
                 output.end());
    assert(output == "6");

    tree.deleteNode(6);

    oss.str("");
    oss.clear();
    std::cout.rdbuf(oss.rdbuf());
    tree.levelOrder();
    std::cout.rdbuf(old_cout);
    output = oss.str();
    output.erase(std::remove_if(output.begin(), output.end(), ::isspace),
                 output.end());
    assert(output == "");

    std::cout << "ok" << std::endl;
}

/**
 * @brief Function for testing levelOrder().
 *
 * @returns void
 */
static void test_levelOrder() {
    std::cout << "Testing AVL levelOrder...";

    AVLTree tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(6);

    std::ostringstream oss;
    std::streambuf* old_cout = std::cout.rdbuf(oss.rdbuf());
    tree.levelOrder();
    std::cout.rdbuf(old_cout);
    std::string output = oss.str();
    output.erase(std::remove_if(output.begin(), output.end(), ::isspace),
                 output.end());
    assert(output == "4356");

    std::cout << "ok" << std::endl;
}

/**
 * @brief Function for testing tree balancing.
 *
 * @returns void
 */
static void test_balancing() {
    std::cout << "Testing AVL balancing...";

    AVLTree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);

    std::ostringstream oss;
    std::streambuf* old_cout = std::cout.rdbuf(oss.rdbuf());
    tree.levelOrder();
    std::cout.rdbuf(old_cout);
    std::string output = oss.str();
    output.erase(std::remove_if(output.begin(), output.end(), ::isspace),
                 output.end());
    assert(output == "21435");

    tree.insert(6);
    tree.insert(7);

    oss.str("");
    oss.clear();
    std::cout.rdbuf(oss.rdbuf());
    tree.levelOrder();
    std::cout.rdbuf(old_cout);
    output = oss.str();
    output.erase(std::remove_if(output.begin(), output.end(), ::isspace),
                 output.end());
    assert(output == "4261357");

    std::cout << "ok" << std::endl;
}

/**
 * @brief Function for testing edge cases.
 *
 * @returns void
 */
static void test_edge_cases() {
    std::cout << "Testing AVL edge cases...";

    AVLTree tree;

    // Deleting from an empty tree
    tree.deleteNode(1);
    std::ostringstream oss;
    std::streambuf* old_cout = std::cout.rdbuf(oss.rdbuf());
    tree.levelOrder();
    std::cout.rdbuf(old_cout);
    std::string output = oss.str();
    output.erase(std::remove_if(output.begin(), output.end(), ::isspace),
                 output.end());
    assert(output == "");

    // Inserting duplicate elements
    tree.insert(1);
    tree.insert(1);
    oss.str("");
    oss.clear();
    std::cout.rdbuf(oss.rdbuf());
    tree.levelOrder();
    std::cout.rdbuf(old_cout);
    output = oss.str();
    output.erase(std::remove_if(output.begin(), output.end(), ::isspace),
                 output.end());
    assert(output == "1");

    std::cout << "ok" << std::endl;
}

/**
 * @brief Function for running tests.
 *
 * @returns void
 */
void tests() {
    test_insert();
    test_deleteNode();
    test_levelOrder();
    test_balancing();
    test_edge_cases();
    std::cout << "All tests passed!" << std::endl;
}

/**
 * @brief Main function for running tests.
 *
 * @returns 0 on exit
 */
int main() {
    tests();
    return 0;
}
