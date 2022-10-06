// Bottom Up manner
class Solution
{
    int *solve(TreeNode *root)
    {
        int *res = new int[2];

        if (!root)
        {
            res[0] = 0, res[1] = 0;
            return res;
        }

        int *left = solve(root->left);
        int *right = solve(root->right);

        res[0] = max(left[0], left[1]) + max(right[0], right[1]);
        res[1] = root->val + left[0] + right[0];
        return res;
    }

public:
    int rob(TreeNode *root)
    {
        int *res = solve(root);
        return max(res[0], res[1]);
    }
};

// Recursive + Memoization
class Solution
{
    map<pair<TreeNode *, bool>, int> dp;

public:
    int rob(TreeNode *root, bool prev = false)
    {
        if (!root)
            return 0;

        if (dp.find({root, prev}) != dp.end())
            return dp[{root, prev}];

        if (prev)
            return rob(root->left, false) + rob(root->right, false);

        int doNotRobThis = rob(root->left, false) + rob(root->right, false);
        int robThis = root->val + rob(root->left, true) + rob(root->right, true);

        return dp[{root, prev}] = max(robThis, doNotRobThis);
    }
};