#include <iostream>
using namespace std;

struct Node
{
    int data;
    struct node *left,*middle,*right;
};

Node* newNode(int dta)
{
  Node *n = new Node;
  n->data = dta;
  n->left = NULL;
  n->middle = NULL;
  n->right = NULL;
  return n;
}

void pushNode(Node **tail_ref,Node *node)
{
    if(tail_ref == NULL)
    {
        *tail_ref = node;
        node->left = NULL;
        node->middle = NULL;
        node->right = NULL;
    }

    (*tail_ref)->right = node;
    node->left = (*tail_ref);

    node->right = NULL;
    node->middle = NULL;

    (*tail_ref) = node;

}

void ConvertTreetoList(Node *node,Node **head_ref)
{
   Node* tail_ref = NULL;
    if(node == NULL)
        return NULL;

    if(head_ref == NULL)
        head_ref = node;

    Node *lleft = node->left;
    Node *lmiddle = node->middle;
    Node *lright = node->right;

    pushNode(&tail_ref,node);

    ConvertTreetoList(lleft,head_ref);
    ConvertTreetoList(lmiddle,head_ref);
    ConvertTreetoList(lright,head_ref);

}




int main()
{
    Node* root = newNode(30);
    root->left = newNode(5);
    root->middle = newNode(11);
    root->right = newNode(63);

   /* root->left->left = newNode(1);
    root->left->middle = newNode(4);
    root->left->right = newNode(8);

    root->middle->left = newNode(6);
    root->middle->middle = newNode(7);
    root->middle->right = newNode(15);

    root->right->left = newNode(31);
    root->right->middle = newNode(55);
    root->right->right = newNode(65); */
    Node *head = NULL;

    ConvertTreetoList(root,&head);

    return 0;
}
