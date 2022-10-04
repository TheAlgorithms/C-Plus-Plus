#include <bits/stdc++.h>
#include <cinttypes>
using namespace std;

// Node Class
class Node {
	public : 
	    int data;
	    Node* xnode;
};

// Function for returning XOR value of x and y
Node* Xor(Node* x, Node* y)
{
	return reinterpret_cast<Node*>(
		reinterpret_cast<uintptr_t>(x)
		^ reinterpret_cast<uintptr_t>(y));
}

// Insertion in XOR linked list
void insert(Node** head_ref, int data)
{
	Node* new_node = new Node();
	new_node -> data = data;

	new_node -> xnode = *head_ref;

	if (*head_ref != NULL) {
		(*head_ref)	-> xnode = Xor(new_node, (*head_ref) -> xnode);
	}
	*head_ref = new_node;
}

// Printing Linked List
void printList(Node* head)
{
	Node* curr = head;
	Node* prev = NULL;
	Node* next;

	cout << "Nodes of Linked list : \n";
	while (curr != NULL) {
		cout << curr -> data << " ";
		next = Xor(prev, curr -> xnode);
		prev = curr;
		curr = next;
	}
}

// Main Function
int main()
{
	Node* head = NULL;
	insert(&head, 1);
	insert(&head, 2);
	insert(&head, 3);
	insert(&head, 4);

	printList(head);

	return (0);
}
