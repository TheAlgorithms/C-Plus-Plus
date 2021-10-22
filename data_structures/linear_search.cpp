// Iterative C++ program to search
// an element in linked list
#include <bits/stdc++.h>
using namespace std;
 
/* Link list node */
class Node
{
    public:
    int key;
    Node* next;
};
 
/* Given a reference (pointer to pointer) to the head
of a list and an int, push a new node on the front
of the list. */
void push(Node** head_ref, int new_key)
{
    /* allocate node */
    Node* new_node = new Node();
 
    /* put in the key */
    new_node->key = new_key;
 
    /* link the old list off the new node */
    new_node->next = (*head_ref);
 
    /* move the head to point to the new node */
    (*head_ref) = new_node;
}
 
/* Checks whether the value x is present in linked list */
bool search(Node* head, int x)
{
    Node* current = head; // Initialize current
    while (current != NULL)
    {
        if (current->key == x)
            return true;
        current = current->next;
    }
    return false;
}
 
/* Driver program to test count function*/
int main()
{
    /* Start with the empty list */
    Node* head = NULL;
    int x = 21;
 
    /* Use push() to construct below list
    14->21->11->30->10 */
    push(&head, 10);
    push(&head, 30);
    push(&head, 11);
    push(&head, 21);
    push(&head, 14);
 
    search(head, 21)? cout<<"Yes" : cout<<"No";
    return 0;
}
 
// This is code is contributed by Bhagyashree
