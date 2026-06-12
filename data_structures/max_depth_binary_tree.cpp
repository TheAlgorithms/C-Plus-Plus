#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
};

TreeNode* newNode(int val) {
    return new TreeNode(val);
}

int main() {
    Solution sol;

    //     3
    //    / \
    //   9  20
    //      / \
    //     15   7
    TreeNode* root1 = newNode(3);
    root1->left = newNode(9);
    root1->right = newNode(20);
    root1->right->left = newNode(15);
    root1->right->right = newNode(7);
    cout << "Test 1: " << sol.maxDepth(root1) << " (expected 3)" << endl;

    // [1, null, 2]
    TreeNode* root2 = newNode(1);
    root2->right = newNode(2);
    cout << "Test 2: " << sol.maxDepth(root2) << " (expected 2)" << endl;

    // empty tree
    cout << "Test 3: " << sol.maxDepth(nullptr) << " (expected 0)" << endl;

    return 0;
}