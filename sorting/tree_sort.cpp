#include<bits/stdc++.h> 
using namespace std;
struct Node 
{ 
	int key; 
	struct Node *left, *right; 
}; 

struct Node *newNode(int item) 
{ 
	struct Node *temp = new Node; 
	temp->key = item; 
	temp->left = temp->right = NULL; 
	return temp; 
} 

void storeSorted(Node *root, int arr[], int &i) 
{ 
	if (root != NULL) 
	{ 
		storeSorted(root->left, arr, i); 
		arr[i++] = root->key; 
		storeSorted(root->right, arr, i); 
	} 
} 

/* A function to insert a new 
Node with given key in Binary search tree */
Node* insert(Node* node, int key) 
{ 
	/*Return a new Node,if the tree is empty */
	if (node == NULL) return newNode(key); 

	/* Otherwise, recur down the tree */
	if (key < node->key) 
		node->left = insert(node->left, key); 
	else if (key > node->key) 
		node->right = insert(node->right, key); 
	return node; 
} 

// Sort using Tree Sort 
void treeSort(int arr[], int n) 
{ 
	struct Node *root = NULL; 
	root = insert(root, arr[0]); 
	for (int i=1; i<n; i++) 
		root = insert(root, arr[i]); 
	int i = 0; 
	storeSorted(root, arr, i); 
} 

// Driver Program 
int main() 
{ 
	//create input array 
	int arr[] = {5, 4, 7, 2, 11}; 
	int n = sizeof(arr)/sizeof(arr[0]); 
	treeSort(arr, n); 
		for (int i=0; i<n; i++) 
	cout << arr[i] << " "; 
	return 0; 
} 
