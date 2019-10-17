#ifndef TREE_HEADER
#define TREE_HEADER

typedef struct Tree
{
  int data;
  struct Tree *left, *right;
} tree;

tree *insert(tree *root, int data);
void inorderFake(tree *root);

#endif