// https://leetcode.com/problems/house-robber-iii/submissions/

class Solution
{
public:
  pair<int, int> robber(TreeNode *root)
  {
    if (root == NULL)
      return {0, 0};
    pair<int, int> pr;
    pair<int, int> pr1 = robber(root->left);
    pair<int, int> pr2 = robber(root->right);
    // pr first tells if i am taking the nodes value and second if not taking
    // so for first if i am taking the current node value then i definitely can't take it's children values and hence second else if not taking then take max of whether i am taking child or not
    pr.first = root->val + pr1.second + pr2.second;
    pr.second = max(pr1.first, pr1.second) + max(pr2.first, pr2.second);

    return pr;
  }
  int rob(TreeNode *root)
  {
    pair<int, int> pr = robber(root);
    return max(pr.first, pr.second);
  }
};

// DP one is simple
class Solution
{
public:
  map<TreeNode *, int> mp;
  int robber(TreeNode *root)
  {
    if (root == NULL)
      return 0;
    if (mp.count(root))
      return mp[root];
    int lh = robber(root->left);
    int rh = robber(root->right);
    int a = 0;
    int b = 0;
    if (root->left)
      a = robber(root->left->left) + robber(root->left->right);
    if (root->right)
      b = robber(root->right->left) + robber(root->right->right);
    mp[root] = max(lh + rh, root->val + a + b);
    return mp[root];
  }
  int rob(TreeNode *root)
  {
    mp.clear();
    return robber(root);
  }
};