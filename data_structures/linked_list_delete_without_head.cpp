/**
 * @file
 * \brief Delete a node in a linked list without the head pointer
 * \details
 * This algortihm helps delete a node in a linked list without the access of a head pointer
 * @author rakshaa2000
*/

//Delete without a head pointer.
/*You are given a pointer/ reference to the node which is to be deleted from the linked list of N nodes. The task is to delete the node. Pointer/ reference to head node is not given. 
Note: No head reference is given to you.*/

/*
Example 1:

Input:
N = 3
value[] = {1,2,3}
node = 1
Output: 2 3
Explanation: After deleting 1 from the
linked list, we have remaining nodes
as 2 and 3.

Example 2:

Input:
N = 4
value[] = {70,20,60,30}
node = 20
Output: 40 60 30
Explanation: After deleting 20 from
the linked list, we have remaining
nodes as 40, 60 and 30.

*/

#include <iostream>
//Driver Code starts
//Linked list node structure
struct Node{
  int data;
  Node *next;
  explicit Node(int x){
    data=x;
    next=nullptr;
  }
} *head;

//To search for the given node
Node *findNode(Node *head, int search){
  Node *cur= head;
  while(cur!=nullptr){
    if(cur->data==search)
      break;
    cur=cur->next;
  }
}

//To populate the linked list
void insert(){
  int n, value;
  Node *temp;
  std::cin>>&n;
  for(int i=0; i<n; i++){
    std::cin>>&value;
    if(i==0){
      head= new Node(value);
      temp=head;
      continue;
    }
    else{
      temp->next=new Node(value);
      temp=temp->next;
      new Node(value);
      temp->next=nullptr;
    }
  }
}

//To print the entire list
void printList (Node *node){
  while(node!=nullptr){
    std::cout<<node->data;
    node=node->next;
  }
  std::cout<<endl;
}

//Driver Code Ends

//Function to locate the node to be deleted
void deleteNode(Node *m)
{
   *m=*m->next;
}

//Main function
int main(){
  int k;
  insert();
  cin>>&k;
  Node *del= findNode(head,k);
  if(del!=nullptr && del->next!=nullptr){
    deleteNode(del);
  }
  printList(head);
  return 0;
}
