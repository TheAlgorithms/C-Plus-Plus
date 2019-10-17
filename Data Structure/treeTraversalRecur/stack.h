#ifndef STACK_HEADER
#define STACK_HEADER

#include "tree.h"

typedef struct Node
{
  tree *top;
  struct Node *next;
} node;

node *getNode(tree *c);
void display(node *st);
int isempty(node *st);
void push(tree *adr, node **st);
void pop(node **st);

#endif