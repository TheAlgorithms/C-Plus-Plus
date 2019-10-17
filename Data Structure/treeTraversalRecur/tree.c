#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

tree *getTreeNode(int data)
{
  tree *nn = (tree *)malloc(sizeof(tree));
  nn->left = nn->right = NULL;
  nn->data = data;
  return nn;
}

tree *insert(tree *root, int data)
{
  if (!root)
  {
    return getTreeNode(data);
  }
  else if (root->data < data)
  {
    root->right = insert(root->right, data);
  }
  else
  {
    root->left = insert(root->left, data);
  }
  return root;
}

void inorder(tree *root)
{
  if (root)
  {
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
  }
}

void preorder(tree *root)
{
  if (root)
  {
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
  }
}

void postorder(tree *root)
{
  if (root)
  {
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
  }
}
