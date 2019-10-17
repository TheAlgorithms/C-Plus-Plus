#include <stdio.h>
#include <stdarg.h>

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

void inorder(tree *root)
{

  node *stack = NULL;
  push(root, &stack);
  int ok = 1;
  while (!isempty(stack))
  {
    if (stack->top->left && ok)
    {
      push(stack->top->left, &stack);
    }
    else
    {
      ok = 0;
      printf("%d ", stack->top->data);
      tree *adr;
      if (stack->top->right)
      {
        adr = stack->top->right;
        pop(&stack);
        push(adr, &stack);
      }
      else
      {
        pop(&stack);
      }
    }
  }
}

int main()
{
  // FILE *output = freopen("out.txt", "w", stdout);
  // FILE *input = freopen("in.txt", "r", stdin);

  tree *root = NULL;

  int n, val;
  scanf("%d", &n);

  for (int i = 0; i < n; i++)
  {
    scanf("%d", &val);
    root = insert(root, val);
  }

  // inorderFake(root);
  inorder(root);

  // fclose(output);
  // fclose(input);
  return 0;
}