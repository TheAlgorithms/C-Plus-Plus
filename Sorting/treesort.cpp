/*
 Tree sort

In tree sort we make use of property of binary search tree.
Inorder traversal of Binary search tree gives sorted order.
time :- O(nlogn)
space :- O(n)
*/
#include<bits/stdc++.h> 
using namespace std; 
class Node 
{ 
public:
	int key; 
	struct Node *left, *right; 
}; 

Node *newNode(int item) 
{ 
	Node *p = new Node; 
	p -> key = item; 
	p -> left = p -> right = NULL; 
	return p; 
} 
// get inoder traversal of the BST 
void inorder(Node *root, int arr[], int &i) 
{ 
	if (root != NULL) 
	{ 
		inorder(root -> left, arr, i); 
		arr[i++] = root -> key; 
		inorder(root -> right, arr, i); 
	} 
} 
// Function to insert node in binary tree
Node* insert(Node* node, int key) 
{ 
	if (node == NULL) 
		return newNode(key); 

	if (key < node -> key) 
		node -> left = insert(node -> left, key); 
	else if (key > node -> key) 
		node -> right = insert(node -> right, key); 
	return node; 
} 
// Wrapper function
void sort(int arr[], int n) 
{ 
	struct Node *root = NULL; 

	root = insert(root, arr[0]); 
	for (int i = 1; i < n; i++) 
		insert(root, arr[i]); 
	int i = 0; 
	// do inorder traversal to get sorted order
	inorder(root, arr, i); 
} 
int main() 
{ 
	int a[] = {4, 5, 3, 1, 2, 8, 7, 9, 5, 6}; 
	int n = sizeof(a) / sizeof(a[0]);
	// sort the array 
	sort(a, n); 
	// print sorted array
	for (int i=0; i<n; i++) 
		cout << a[i] << " "; 
	return 0; 
}
