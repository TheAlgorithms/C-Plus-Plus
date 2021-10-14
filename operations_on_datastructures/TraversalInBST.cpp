#include<iostream>
#include<stack>
#include<vector>
using namespace std;

struct TreeNode {
	int data;
	TreeNode* left, * right;
	TreeNode(int data)
	{
		this->data = data;
		left = right = NULL;
	}
};

TreeNode* newNode(int data)
{
    TreeNode* temp = new TreeNode(data);
    return temp;
}

TreeNode* make_BST(TreeNode* root, int data)
{
	if (root == NULL)    
		return newNode(data);
	else
	{
		if (data <= root->data)
			root->left = make_BST(root->left, data);
		else
			root->right = make_BST(root->right, data);
		
		return root;
	}
}


void Postorder(TreeNode* root)
{
	if (root == NULL)
		return;

	Postorder(root->left);
	Postorder(root->right);

	cout << root->data << " ";
}


void Inorder(TreeNode* root)
{
	if (root == NULL)
		return;

	Inorder(root->left);
	cout << root->data << " ";
	Inorder(root->right);
}

void Preorder(TreeNode* root)
{
	if (root == NULL)
		return;

	cout << root->data << " ";
	Preorder(root->left);
	Preorder(root->right);
}


int main() {
  
	vector<int>v = { 4,2,3,5,1};
	int i = 0;

	TreeNode* root=NULL;
	while (i<v.size()) {
		root= make_BST(root, v[i]);
		i++;
	}
	
	int a;
	cout << "Select the type of traversal \n";
	cout << "1. Pre-Order Traversal \n";
	cout << "2. In-Order Traversal \n";
	cout << "3. Post-Order Traversal \n";
	cin >> a;
	cout<<"\n Answer is : ";
	switch (a) {
	case 1: Preorder(root);
		    break;
	case 2: Inorder(root);
		    break;
	case 3: Postorder(root);
		    break;
	default: cout << "\n Wrong option choosen";

	}

return 0;
	
}