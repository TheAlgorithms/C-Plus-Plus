

#include <iostream> 
using namespace std; 
  

class Node { 
    public:
    int data; 
    struct Node* next; 
}; 
  
void push(Node** head_ref, int new_data) 
{ 
    
    Node* new_node = new Node; 

    new_node->data = new_data; 

    new_node->next = (*head_ref); 
  
    (*head_ref) = new_node; 
} 
  
// Returns true if there is a loop in linked list 
// else returns false. 
bool detectLoop(struct Node* h) 
{ 
    Node* temp1 = h;
    Node* temp2 = h;
    if (h == NULL){
            return false;
        }
    while(temp1){
        temp1 = (temp1->next)->next;
        temp2 = temp2->next;
        if(temp1==temp2){
            return true;
        }
    }
    return false;
} 
  

int main() 
{ 
    
    Node* head = NULL; 
  
    push(&head, 20); 
    push(&head, 4); 
    push(&head, 15); 
    push(&head, 10); 
  
    /* Create a loop for testing */
    head->next->next->next->next = head; 
  
    if (detectLoop(head)) 
        cout << "Loop found"; 
    else
        cout << "No Loop"; 
  
    return 0; 
} 

