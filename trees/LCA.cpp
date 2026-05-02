#include <stdexcept>

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

bool find(Node* root, int val) {
    if (!root)
        return false;
    if (root->data == val)
        return true;
    return find(root->left, val) || find(root->right, val);
}

Node* lcaUtil(Node* root, int p, int q) {
    if (!root)
        return nullptr;

    if (root->data == p || root->data == q)
        return root;

    Node* left = lcaUtil(root->left, p, q);
    Node* right = lcaUtil(root->right, p, q);

    if (left && right)
        return root;

    return left ? left : right;
}

Node* LCA(Node* root, int p, int q) {
    if (!root)
        return nullptr;

    if (!find(root, p) || !find(root, q))
        return nullptr;

    return lcaUtil(root, p, q);
}
