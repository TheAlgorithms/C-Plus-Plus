/**
 * @file
 * @brief Modern C++ Binary Search Tree implementation using OOP and STL
 */

#include <iostream>
#include <queue>

class BinarySearchTree {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;

        Node(int value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    /* ================= Private Helper Functions ================= */

    Node* insert(Node* node, int value) {
        if (node == nullptr)
            return new Node(value);

        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);

        return node;
    }

    Node* findMax(Node* node) {
        while (node->right != nullptr)
            node = node->right;
        return node;
    }

    Node* remove(Node* node, int value) {
        if (node == nullptr)
            return nullptr;

        if (value < node->data) {
            node->left = remove(node->left, value);
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
            // Case 1: No child
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }

            // Case 2: One child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: Two children
            Node* temp = findMax(node->left);
            node->data = temp->data;
            node->left = remove(node->left, temp->data);
        }

        return node;
    }

    void inorder(Node* node) const {
        if (node == nullptr)
            return;

        inorder(node->left);
        std::cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(Node* node) const {
        if (node == nullptr)
            return;

        std::cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) const {
        if (node == nullptr)
            return;

        postorder(node->left);
        postorder(node->right);
        std::cout << node->data << " ";
    }

    void destroy(Node* node) {
        if (node == nullptr)
            return;

        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree() {
        destroy(root);
    }

    void insert(int value) {
        root = insert(root, value);
    }

    void remove(int value) {
        root = remove(root, value);
    }

    void inorder() const {
        inorder(root);
        std::cout << "\n";
    }

    void preorder() const {
        preorder(root);
        std::cout << "\n";
    }

    void postorder() const {
        postorder(root);
        std::cout << "\n";
    }

    void breadthFirstTraversal() const {
        if (root == nullptr)
            return;

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* temp = q.front();
            q.pop();

            std::cout << temp->data << " ";

            if (temp->left != nullptr)
                q.push(temp->left);

            if (temp->right != nullptr)
                q.push(temp->right);
        }

        std::cout << "\n";
    }
};

/* ================= Example Usage ================= */

int main() {
    BinarySearchTree bst;

    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    std::cout << "Inorder: ";
    bst.inorder();

    std::cout << "Preorder: ";
    bst.preorder();

    std::cout << "Postorder: ";
    bst.postorder();

    std::cout << "BFS: ";
    bst.breadthFirstTraversal();

    bst.remove(70);

    std::cout << "After deleting 70 (Inorder): ";
    bst.inorder();

    return 0;
}