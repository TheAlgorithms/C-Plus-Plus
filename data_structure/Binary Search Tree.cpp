#include<iostream>
#include<queue>
struct node // binary tree node structure
{
	int data;
	node *left;   // left pointer
	node *right; // right pointer
};
node *creat_node(int data)
{
	node *root=new node;
	root->data=data;
	root->left=NULL;
	return root;
}
class tree{
	// every type of binary tree has following function
	public:
		 void preorder(node *root);
		 void inorder(node *root);
		 void postorder(node *root);
		 void BFS(node *root);
};
void tree::BFS(node *root)
{
	if(root!=NULL)
	{
		queue<node*> q;
		q.push(root);
		while(!q.empty())
		{
			node *temp=q.front();
			cout<<temp->data<<" ";
			if(temp->left!=NULL)
			{
				q.push(temp->left) // pushing left child into the queue
			}
			if(temp->right!=NULL)
			{
				q.push(temp->right) // to push right child into the queue
			}
			q.pop() // popping out the present root from the queue
		}
	}
}
void tree::inorder(node *root)
{
	if(root==NULL)
	{
		return ;// to return void 
	}
	else
	{
		inorder(root->left); // to travel to left of root
		cout<<roor->data<<" ";
		inorder(root->right); // back tracking all right node
	}
}
void tree::preorder(node *root)
{
	if(root==NULL)
	{
		return ;// to return void 
	}
	else
	{
		cout<<roor->data<<" ";
		preorder(root->left); // to travel to left of root
		preorder(root->right); // back tracking all right node
	}
}
void tree::postorder(node *root)
{
	if(root==NULL)
	{
		return ;// to return void 
	}
	else
	{
		postorder(root->left); // to travel to left of root
		postorder(root->right); // back tracking all right node
		cout<<roor->data<<" ";
	}
}
class BST:public tree // inheriting all function of tree class
{
	public:
		node *insert(node *root,int data);
		void remove(int data);
};
node *BST::insert(node *root,int data)
{
	if(root==NULL)
	{
		return creat_node(data);
	}
	else
	{
		if(root->data<data)
		{
			root->right=insert(root->right,data);
		}
		else
		{
			root->left=insert(root->left,data);
		}
		return root; // default return
	}
}
int main()
{
	
}
