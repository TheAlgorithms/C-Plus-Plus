// to run type "gcc treeTraversal.c tree.c stack.c"
// then run the executable file and enter your input

#include <stdio.h>

#include "tree.h"
#include "stack.h"

void printstack(node *stack)
{
  printf("stack: ");
  while (!isempty(stack))
  {
    printf("%p ", stack->top->data);
  }
  printf("\n");
}

int main()
{
  tree *root = NULL;

  int n, val;
  printf("Enter number of nodes: ");
  scanf("%d", &n);

  for (int i = 0; i < n; i++)
  {
    printf("Enter node %d: ", i+1);
    scanf("%d", &val);
    root = insert(root, val);
  }

  //using binary search tree.
  //for an input of 2 1 4 3 5
  //           2
  //         /  \
  //        1    3 
  //            / \
  //           4   5 

  // inorder: 1 2 3 4 5
  // preorder: 2 1 4 3 5
  // postorder: 1 3 5 4 2


  printf("inorder: ");
  inorder(root);
  printf("\n");

  printf("preorder: ");
  preorder(root);
  printf("\n");

  printf("postorder: ");
  postorder(root);
  printf("\n");

  return 0;
}