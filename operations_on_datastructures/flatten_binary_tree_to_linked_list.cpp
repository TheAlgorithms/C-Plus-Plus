
/**
 * @file flatten_binary_tree_to_linked_list.cpp
 * @author Priyanshu Vaishnav (princepriyanshu.vaishnav@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-10-09
 *
 * @copyright Copyright (c) 2022
 *
 * Problem
Link:https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
 *
 * Description : Given the root of a binary tree, flatten the tree into a
 * "linked list":
 *
 * The "linked list" should use the same TreeNode class where the right child
 * pointer points to the next node in the list and the left child pointer is
 * always null. The "linked list" should be in the same order as a pre-order
 * traversal of the binary tree.
 *
 *
 *
 *   Input: root = [1,2,5,3,4,null,6]                       //Input is a Tree not an array
 *   Output: [1,null,2,null,3,null,4,null,5,null,6]
 * 
 * 
 *              1                                        1
 *            /   \                                       \  
 *           2     5                  ------->             2
 *         /   \    \                                       \ 
 *        3     4    6                                       3 
 *                                                            \
 *                                                             4
 *                                                              \
 *                                                               5        
 *                                                                \      
 *                                                                 6     
 * 
 * */

#include <iostream>
using namespace std;

// defining the structure of Nodes of Tree.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}  // Constructor
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

TreeNode *func(TreeNode *root) {
    if (root == NULL)
        return NULL;

    TreeNode *node = root->right;
    TreeNode *dummy = root;
    root->right = func(root->left);
    node = func(node);
    while (dummy->right != NULL) {
        dummy = dummy->right;
    }
    dummy->right = node;
    root->left = NULL;

    return root;
}

void flatten(TreeNode *root) { func(root); }

void show(TreeNode *root) {
    while (root != NULL) {
        cout << root->val << "  ->" << "\t";
        root = root->right;
    }
    cout << "NULL";
}

int main() { 
    TreeNode *root = new TreeNode(1);
    TreeNode *root_left = new TreeNode(2);
    TreeNode *root_right = new TreeNode(5);
    TreeNode *root_left_left = new TreeNode(3);
    TreeNode *root_left_right = new TreeNode(4);
    TreeNode *root_right_right = new TreeNode(6);

    root->left=root_left;
    root->right = root_right;
    root->left->left=root_left_left;
    root->left->right=root_left_right;
    root->right->right = root_right_right;

    flatten(root);
    //Show Flatten Linked list

    show(root);
    }