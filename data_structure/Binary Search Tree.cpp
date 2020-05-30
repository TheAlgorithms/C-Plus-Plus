#include<iostream>
#include<queue>
struct node
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
	public:
		virtual node *insert(node *root,int data)=0;
		virtual void preorder(node *root)=0;
		virtual void inorder(node *root)=0;
		virtual void postorder(node *root)=0;
		virtual void BFS(node *root)=0;
		virtual remove(int data)=0;
};
class BST:public tree{
	public:
		node *insert(node *root,int data)
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
		void inorder(node *root)
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
		void preorder(node *root)
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
		void postorder(node *root)
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
		void BFS(node *root)
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
};
