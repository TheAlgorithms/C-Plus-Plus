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

void inorderFake(tree *root)
{
  if (root)
  {
    inorderFake(root->left);
    printf("%d ", root->data);
    inorderFake(root->right);
  }
}
