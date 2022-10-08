// approach
// 1-simply remember its a DFS and in DFS this is inorder traversal(left-root-right)
// 2-first we will traverse extreme left sub tree and then extreme right sub tree

// link-https://leetcode.com/problems/path-sum/
// link of striver vedio to understant-https://www.youtube.com/watch?v=jmy0LaGET1I
// this is my best approach ti solve this question

class Solution {
public:
bool hasPathSum(TreeNode* root, int targetSum) {
if(root==NULL)
   return false;
if(root->left==NULL && root->right==NULL){
   if(targetSum-root->val==0)
     return true;
   else
    return false;

   }
    return hasPathSum(root->left,targetSum-root->val) || hasPathSum(root->right,targetSum-root->val);
       
}
};