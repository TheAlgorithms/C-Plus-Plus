// Iterative C++ program to search 
// an element in linked list 
#include <iostream.h>
using namespace std; 

/* Link list node */class Node 
{ 
	public: 
	int key; 
	Node* next; 
}; 


void push(Node** head_ref, int new_key) 
{ 
	Node* new_node = new Node(); 

	new_node->key = new_key; 

	new_node->next = (*head_ref); 

	(*head_ref) = new_node; 
} 


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

int main() 
{ 
	
	Node* head = NULL; 
	int x = 21; 

	
	push(&head, 10); 
	push(&head, 30); 
	push(&head, 11); 
	push(&head, 21); 
	push(&head, 14); 

	search(head, 21)? cout<<"Yes" : cout<<"No"; 
	return 0; 
} 


