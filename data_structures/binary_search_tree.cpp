#include <iostream>
#include <queue>

class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node(int value) : val(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:
    Node* root;

    BinarySearchTree() : root(nullptr) {}

    void insert(int x) {
        if (!root) {
            root = new Node(x);
        } else {
            insertRec(root, x);
        }
    }

    void remove(int x) {
        root = removeRec(root, x);
    }

    void breadthFirstTraversal() const {
        if (!root) return;
        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            std::cout << current->val << " ";
            
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        std::cout << std::endl;
    }

    void preorderTraversal() const {
        preorderRec(root);
        std::cout << std::endl;
    }

    void inorderTraversal() const {
        inorderRec(root);
        std::cout << std::endl;
    }

    void postorderTraversal() const {
        postorderRec(root);
        std::cout << std::endl;
    }

private:
    void insertRec(Node* n, int x) {
        if (x < n->val) {
            if (!n->left) {
                n->left = new Node(x);
            } else {
                insertRec(n->left, x);
            }
        } else {
            if (!n->right) {
                n->right = new Node(x);
            } else {
                insertRec(n->right, x);
            }
        }
    }

    Node* removeRec(Node* n, int x) {
        if (!n) return nullptr;

        if (x < n->val) {
            n->left = removeRec(n->left, x);
        } else if (x > n->val) {
            n->right = removeRec(n->right, x);
        } else {
            if (!n->left && !n->right) {
                delete n;
                return nullptr;
            } else if (!n->left) {
                Node* temp = n->right;
                delete n;
                return temp;
            } else if (!n->right) {
                Node* temp = n->left;
                delete n;
                return temp;
            } else {
                int maxInLeftSubtree = findMax(n->left);
                n->val = maxInLeftSubtree;
                n->left = removeRec(n->left, maxInLeftSubtree);
            }
        }
        return n;
    }

    int findMax(Node* n) const {
        while (n->right) {
            n = n->right;
        }
        return n->val;
    }

    void preorderRec(Node* n) const {
        if (!n) return;
        std::cout << n->val << " ";
        preorderRec(n->left);
        preorderRec(n->right);
    }

    void inorderRec(Node* n) const {
        if (!n) return;
        inorderRec(n->left);
        std::cout << n->val << " ";
        inorderRec(n->right);
    }

    void postorderRec(Node* n) const {
        if (!n) return;
        postorderRec(n->left);
        postorderRec(n->right);
        std::cout << n->val << " ";
    }
};

int main() {
    BinarySearchTree bst;
    int value, choice;

    std::cout << "\nEnter the value of root node: ";
    std::cin >> value;
    bst.insert(value);

    do {
        std::cout << "\n1. Insert"
                  << "\n2. Delete"
                  << "\n3. Breadth First"
                  << "\n4. Preorder Depth First"
                  << "\n5. Inorder Depth First"
                  << "\n6. Postorder Depth First"
                  << "\nEnter Your Choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "\nEnter the value to be Inserted: ";
                std::cin >> value;
                bst.insert(value);
                break;
            case 2:
                std::cout << "\nEnter the value to be Deleted: ";
                std::cin >> value;
                bst.remove(value);
                break;
            case 3:
                bst.breadthFirstTraversal();
                break;
            case 4:
                bst.preorderTraversal();
                break;
            case 5:
                bst.inorderTraversal();
                break;
            case 6:
                bst.postorderTraversal();
                break;
            default:
                std::cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
