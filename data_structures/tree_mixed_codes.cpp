#include <iostream>
#include <cstdlib>
#include <climits>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int data) {
    if (root == nullptr)
        return new Node(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}

void inorder(Node* root) {
    if (root == nullptr)
        return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

bool isBST(Node* root, int min, int max) {
    if (root == nullptr)
        return true;
    if (root->data < min || root->data > max)
        return false;
    return isBST(root->left, min, root->data - 1) &&
           isBST(root->right, root->data + 1, max);
}

bool validateBST(Node* root) {
    return isBST(root, INT_MIN, INT_MAX);
}

int findHeight(Node* root) {
    if (root == nullptr)
        return -1;
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

bool isBalanced(Node* root) {
    if (root == nullptr)
        return true;
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    return (abs(leftHeight - rightHeight) <= 1) &&
           isBalanced(root->left) && isBalanced(root->right);
}

Node* findLCA(Node* root, int n1, int n2) {
    if (root == nullptr)
        return nullptr;
    if (root->data > n1 && root->data > n2)
        return findLCA(root->left, n1, n2);
    if (root->data < n1 && root->data < n2)
        return findLCA(root->right, n1, n2);
    return root;
}

int main() {
    Node* root = nullptr;
    int choice, data, n1, n2;

    while (true) {
        cout << "\nBinary Search Tree Operations:\n";
        cout << "1. Insert\n2. Inorder Traversal\n3. Check if BST\n4. Validate BST\n";
        cout << "5. Find Height\n6. Check if Balanced\n7. Find LCA\n8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter data to insert: ";
                cin >> data;
                root = insert(root, data);
                break;
            case 2:
                cout << "Inorder Traversal: ";
                inorder(root);
                cout << endl;
                break;
            case 3:
                if (isBST(root, INT_MIN, INT_MAX))
                    cout << "Tree is a BST\n";
                else
                    cout << "Tree is not a BST\n";
                break;
            case 4:
                if (validateBST(root))
                    cout << "Tree is a valid BST\n";
                else
                    cout << "Tree is not a valid BST\n";
                break;
            case 5:
                cout << "Height of the tree: " << findHeight(root) << endl;
                break;
            case 6:
                if (isBalanced(root))
                    cout << "Tree is balanced\n";
                else
                    cout << "Tree is not balanced\n";
                break;
            case 7:
                cout << "Enter two nodes to find their LCA: ";
                cin >> n1 >> n2;
                Node* lca = findLCA(root, n1, n2);
                if (lca != nullptr)
                    cout << "LCA of " << n1 << " and " << n2 << " is " << lca->data << endl;
                else
                    cout << "LCA not found\n";
                break;
            case 8:
                cout << "Exiting the program.\n";
                return 0;
            default:
                cout << "Invalid choice\n";
        }
    }

    return 0;
}
