/**********************
 author: shrutisheoran
***********************/

#include <iostream>
#include <queue>

using namespace std;

typedef struct node {
	int data;
	int height;
	struct node* left;
	struct node* right;
}node;

int max(int a, int b) {
	return a > b ? a : b;
}

node* createNode(int data) {
	node *nn = new node();
	nn->data = data;
	nn->height = 0;
	nn->left = NULL;
	nn->right = NULL;
	return nn;
}

// Returns height of tree
int height(node *root) {
	if(root==NULL)
		return 0;
	return 1 + max(height(root->left), height(root->right));
}

// Returns difference between height of left and right subtree
int getBalance(node *root) {
	return height(root->left) - height(root->right);
}

/************************************
	Returns Node after Right Rotation
*************************************/
node* rightRotate(node *root) {
	node *t = root->left;
	node *u = t->right;
	t->right = root;
	root->left = u;
	return t;
}

/************************************
	Returns Node after Left Rotation
*************************************/
node* leftRotate(node *root) {
	node *t = root->right;
	node *u = t->left;
	t->left = root;
	root->right = u;
	return t;
}

/************************
	Balanced Insertion
************************/
node* insert(node* root, int item) {
	node *nn = createNode(item);
	if(root == NULL)
		return nn;
	if(item<root->data)
		root->left = insert(root->left, item);
	else
		root->right = insert(root->right, item);
	int b = getBalance(root);
	if(b>1) {
		if(getBalance(root->left)<0)
			root->left = leftRotate(root->left);  // Left-Right Case
		return rightRotate(root);				  // Left-Left Case	
	}
	else if(b<-1) {
		if(getBalance(root->right)>0)
			root->right = rightRotate(root->right);  // Right-Left Case
		return leftRotate(root);				    // Right-Right Case
	}
	return root;
}

/**************************************
	LevelOrder (Breadth First Search)
*************************************/
void levelOrder(node* root) {
	queue<node*> q;
	q.push(root);
	while(!q.empty()) {
		root = q.front();
		cout<<root->data<<" ";
		q.pop();
		if(root->left)
			q.push(root->left);
		if(root->right)
			q.push(root->right);
	}
}

int main() {
	node *root = NULL;
	// Testing AVL Tree
	int i;
	for(i = 1 ; i <= 7 ; i++)
		root = insert(root, i);
	cout<<"LevelOrder: ";
	levelOrder(root);
	return 0;
}
