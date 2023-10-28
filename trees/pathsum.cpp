/**
 * @file
 * @author Yash Kesharwani
 * @brief Implementation of the "Path Sum II" problem using a binary tree.
 * @see [LeetCode Problem](https://leetcode.com/problems/path-sum-ii/)
 */

#include <iostream>
#include <vector>
using namespace std;
// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

class Solution {
 public:
    void solve(TreeNode* root, int target, vector<int>& nums,
               vector<vector<int>>& res) {
        if (root == nullptr) {
            return;
        }
        if (target - root->val == 0 && root->left == nullptr &&
            root->right == nullptr) {
            nums.push_back(root->val);
            res.push_back(vector<int>(nums));
            nums.pop_back();
            return;
        }
        nums.push_back(root->val);
        solve(root->left, target - root->val, nums, res);
        solve(root->right, target - root->val, nums, res);
        nums.pop_back();
    }

    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> res;
        vector<int> nums;
        solve(root, targetSum, nums, res);
        return res;
    }
};

int main() {
    // Create your binary tree and call the pathSum function here
    // Example usage:
    // TreeNode* root = new TreeNode(5);
    // root->left = new TreeNode(4);
    // root->right = new TreeNode(8);
    // root->left->left = new TreeNode(11);
    // root->left->left->left = new TreeNode(7);
    // root->left->left->right = new TreeNode(2);
    // root->right->left = new TreeNode(13);
    // root->right->right = new TreeNode(4);
    // root->right->right->left = new TreeNode(5);
    // root->right->right->right = new TreeNode(1);
    // int targetSum = 22;

    Solution solution;
    // Call solution.pathSum(root, targetSum) and process the result as needed

    return 0;
}
