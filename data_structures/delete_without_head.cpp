/* This is a problem from geeksforgeeks and i am just adding the problem
solution i am not adding the insertion and all other code */

/*
struct Node {
  int data;
  struct Node *next;
  Node(int x) {
    data = x;
    next = NULL;
  }
}*head;
*/
// This function should delete node from linked list. The function
// may assume that node exists in linked list and is not last node
// node: reference to the node which is to be deleted
void deleteNode(Node *node)
{
   // Your code here
   node->data=node->next->data;
  // node->next=node->next->next;
  Node *temp=node->next;
  node->next=node->next->next;
  delete temp;
}
