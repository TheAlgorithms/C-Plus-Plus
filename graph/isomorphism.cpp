// A C++ program to check if two given trees are isomorphic 
#include <iostream> 
using namespace std; 

/* A binary tree node has data, pointer to left and right children */
struct node 
{ 
	int data; 
	struct node* left; 
	struct node* right; 
}; 

/* Given a binary tree, print its nodes in reverse level order */
bool isIsomorphic(node* n1, node *n2) 
{ 
// Both roots are NULL, trees isomorphic by definition 
if (n1 == NULL && n2 == NULL) 
	return true; 

// Exactly one of the n1 and n2 is NULL, trees not isomorphic 
if (n1 == NULL || n2 == NULL) 
	return false; 

if (n1->data != n2->data) 
	return false; 

// There are two possible cases for n1 and n2 to be isomorphic 
// Case 1: The subtrees rooted at these nodes have NOT been "Flipped". 
// Both of these subtrees have to be isomorphic, hence the && 
// Case 2: The subtrees rooted at these nodes have been "Flipped" 
return
(isIsomorphic(n1->left,n2->left) && isIsomorphic(n1->right,n2->right))|| 
(isIsomorphic(n1->left,n2->right) && isIsomorphic(n1->right,n2->left)); 
} 

/* Helper function that allocates a new node with the 
given data and NULL left and right pointers. */
node* newNode(int data) 
{ 
	node* temp = new node; 
	temp->data = data; 
	temp->left = NULL; 
	temp->right = NULL; 

	return (temp); 
} 

/* Driver program to test above functions*/
int main() 
{ 
	// Let us create trees shown in above diagram 
	struct node *n1 = newNode(1); 
	n1->left	 = newNode(2); 
	n1->right	 = newNode(3); 
	n1->left->left = newNode(4); 
	n1->left->right = newNode(5); 
	n1->right->left = newNode(6); 
	n1->left->right->left = newNode(7); 
	n1->left->right->right = newNode(8); 

	struct node *n2 = newNode(1); 
	n2->left		 = newNode(3); 
	n2->right	 = newNode(2); 
	n2->right->left = newNode(4); 
	n2->right->right = newNode(5); 
	n2->left->right = newNode(6); 
	n2->right->right->left = newNode(8); 
	n2->right->right->right = newNode(7); 

	if (isIsomorphic(n1, n2) == true) 
	cout << "Yes"; 
	else
	cout << "No"; 

	return 0; 
} 
