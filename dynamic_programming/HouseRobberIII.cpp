/*
=========================================================
🌲 Problem: House Robber III
=========================================================
🔗 LeetCode Link:
https://leetcode.com/problems/house-robber-iii/

📘 Problem Statement:
The thief has found himself a new place for his thievery again.
There is only one entrance to this area, called the root.
Besides the root, each house has one and only one parent house.
After a tour, the smart thief realized that all houses in this place form a binary tree.
It will automatically contact the police if two directly-connected houses were robbed on the same night.

Return the maximum amount of money the thief can rob without alerting the police.

---------------------------------------------------------
🧠 Approach: Dynamic Programming (Tree DP) + Post-order DFS
---------------------------------------------------------
- Start from the leaf nodes and move towards the root.
- At every node, we have two choices:
  1️⃣ Rob this node → then we *cannot* rob its children.
  2️⃣ Skip this node → we are free to rob or skip its children.

So, at each node we compute:
    - `rob_this  = node->val + skip(left) + skip(right)`
    - `skip_this = max(rob/skip from left) + max(rob/skip from right)`

---------------------------------------------------------
⏱️ Time Complexity:  O(n)
💾 Space Complexity: O(h)   (h = height of tree)
---------------------------------------------------------
📌 Points to Remember:
- This is an example of "Tree DP".
- Each recursive call returns two states: {rob, skip}.
- This problem is an extension of:
    - House Robber I → 1D Array DP
    - House Robber II → Circular Array DP
    - House Robber III → Tree DP
---------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // DFS function that returns a pair:
    // first  --> maximum money if we rob this node
    // second --> maximum money if we skip this node
    pair<int, int> dfs(TreeNode* node){
        // Base case: if node is null, rob=0, skip=0
        if(node == NULL) return {0, 0};

        // Recurse for left and right children
        auto left = dfs(node->left);
        auto right = dfs(node->right);

        // Case 1: Rob this node
        // We cannot rob its children, so we take:
        // node value + skip(left) + skip(right)
        int rob_this = node->val + left.second + right.second;

        // Case 2: Skip this node
        // We are free to rob or skip its children, so take the max of both
        int skip_this = max(left.first, left.second) + max(right.first, right.second);

        return {rob_this, skip_this};
    }

    int rob(TreeNode* root){
        auto ans = dfs(root);  // Get {rob, skip} for root
        return max(ans.first, ans.second);  // Choose best option
    }
};


/*
=========================================================
✅ Example Test (Uncomment to run locally)
=========================================================
int main() {
    // Constructing a sample tree:
    //       3
    //      / \
    //     2   3
    //      \    \
    //       3    1
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(3);
    root->right->right = new TreeNode(1);

    Solution sol;
    cout << "Maximum money robbed: " << sol.rob(root) << endl;
    return 0;
}
=========================================================

Time complexity = O(n) and Space complexity = O(h)
Approach = Dynamic Programming (Tree DP) + Post-order DFS

Start from 'leaf' node and move towards 'root' node
At every node, we have two options:
    - Either rob this node (rob_this) --> then we can't rob it's children
    - Either skip this node (skip_this) --> then we are free to rob or skip it's children 

House Robber I → 1D array DP
House Robber II → Circular array DP
House Robber III → Tree DP
=========================================================
*/
