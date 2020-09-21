// Tree node structure  used in the program

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Return the size of the largest sub-tree which is also a BST
struct info {
    int subtree_size;
    int max;
    int min;
    int largestBST_size;
    bool isBST;
};

// utility function
info largestBSTBT(Node *root) {
    if (!root)
        return {0, INT_MIN, INT_MAX, 0, true};
    if (!root->left and !root->right)
        return {1, root->data, root->data, 1, true};

    info left = largestBSTBT(root->left);
    info right = largestBSTBT(root->right);

    info sol;
    sol.subtree_size = (1 + left.subtree_size + right.subtree_size);

    if (left.isBST and right.isBST and left.max < root->data and
        right.min > root->data) {
        sol.isBST = true;
        sol.min = min(left.min, min(right.min, root->data));
        sol.max = max(right.max, max(left.max, root->data));
        sol.largestBST_size = sol.subtree_size;

        return sol;
    }

    sol.largestBST_size = max(left.largestBST_size, right.largestBST_size);
    sol.isBST = false;

    return sol;
}

int largestBst(Node *root) { return largestBSTBT(root).largestBST_size; }