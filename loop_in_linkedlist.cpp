

#include <iostream> 
using namespace std; 
  

struct Node { 
    int data; 
    struct Node* next; 
}; 
  
void push(struct Node** head_ref, int new_data) 
{ 
    
    struct Node* new_node = new Node; 
    new_node->data = new_data; 
    new_node->next = (*head_ref); 
    (*head_ref) = new_node; 
} 
  
 
bool detectLoop(struct Node* h) 
{ 
    struct Node* temp1 = h;
    struct Node* temp2 = h;
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
    
    struct Node* head = NULL; 
  
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

