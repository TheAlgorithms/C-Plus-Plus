// A complete working C program to delete a node in a linked list 
// at a given position 
#include <stdio.h> 
#include <stdlib.h> 

// A linked list node 
struct Node 
{ 
	int data; 
	struct Node *next; 
}; 

/* Given a reference (pointer to pointer) to the head of a list 
and an int, inserts a new node on the front of the list. */
void push(struct Node** head_ref, int new_data) 
{ 
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
	new_node->data = new_data; 
	new_node->next = (*head_ref); 
	(*head_ref) = new_node; 
} 

/* Given a reference (pointer to pointer) to the head of a list 
and a position, deletes the node at the given position */
void deleteNode(struct Node **head_ref, int position) 
{ 
// If linked list is empty 
if (*head_ref == NULL) 
	return; 

// Store head node 
struct Node* temp = *head_ref; 

	// If head needs to be removed 
	if (position == 0) 
	{ 
		*head_ref = temp->next; // Change head 
		free(temp);			 // free old head 
		return; 
	} 

	// Find previous node of the node to be deleted 
	for (int i=0; temp!=NULL && i<position-1; i++) 
		temp = temp->next; 

	// If position is more than number of ndoes 
	if (temp == NULL || temp->next == NULL) 
		return; 

	// Node temp->next is the node to be deleted 
	// Store pointer to the next of node to be deleted 
	struct Node *next = temp->next->next; 

	// Unlink the node from linked list 
	free(temp->next); // Free memory 

	temp->next = next; // Unlink the deleted node from list 
} 

// This function prints contents of linked list starting from 
// the given node 
void printList(struct Node *node) 
{ 
	while (node != NULL) 
	{ 
		printf(" %d ", node->data); 
		node = node->next; 
	} 
} 

/* Drier program to test above functions*/
int main() 
{ 
	/* Start with the empty list */
	struct Node* head = NULL; 

	push(&head, 7); 
	push(&head, 1); 
	push(&head, 3); 
	push(&head, 2); 
	push(&head, 8); 

	puts("Created Linked List: "); 
	printList(head); 
	deleteNode(&head, 4); 
	puts("\nLinked List after Deletion at position 4: "); 
	printList(head); 
	return 0; 
} 
