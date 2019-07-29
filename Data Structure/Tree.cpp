#include<iostream>
using namespace std;


struct node
{
	int val;
	node *left;
	node *right;
};

struct queue
{
	node *t[100];
	int front;
	int rear;
};

queue q;


void enqueue(node *n)
{
	q.t[q.rear++]=n;
}

node * dequeue()
{
	return (q.t[q.front++]);
}



void CreateTree(node *curr, node *n, int x, char pos)
{
	if(n!=NULL)
	{
		char ch;
		cout<<"\nLeft or Right of "<<n->val<<" : ";
		cin>>ch;
		if(ch=='l')
			CreateTree(n, n->left, x, ch);
		else if(ch=='r')
			CreateTree(n, n->right, x, ch);
	}

	else
	{
		node *t=new node;
		t->val=x;
		t->left=NULL;
		t->right=NULL;
		if (pos=='l')
		{
			curr->left=t;
		}
		else if(pos=='r')
		{
			curr->right=t;
		}
	}
}


void BFT(node *n)
{
	if(n!=NULL)
	{
		cout<<n->val<<"  ";
		enqueue(n->left);
		enqueue(n->right);
		BFT(dequeue());
	}
}

void Pre(node *n)
{
	if (n!=NULL)
	{
		cout<<n->val<<"  ";
		Pre(n->left);
		Pre(n->right);
	}
}

void In(node *n)
{
	if (n!=NULL)
	{
		In(n->left);
		cout<<n->val<<"  ";
		In(n->right);
	}
}


void Post(node *n)
{
	if (n!=NULL)
	{
		Post(n->left);
		Post(n->right);
		cout<<n->val<<"  ";
	}
}



int main()
{
	q.front=0;
	q.rear=0;
	int value;
	int ch;
	node *root=new node;
	cout<<"\nEnter the value of root node :";
	cin>>value;
	root->val=value;
	root->left=NULL;
	root->right=NULL;
	do
	{
		cout<<"\n1. Insert : ";
		cout<<"\n2. Breadth First";
		cout<<"\n3. Preorder Depth First";
		cout<<"\n4. Inorder Depth First";
		cout<<"\n5. Postorder Depth First";

		cout<<"\nEnter Your Choice : ";
		cin>>ch;
		switch(ch)
		{
			case 1:
				int x;
				char pos;
				cout<<"\nEnter the value to be Inserted : ";
				cin>>x;
				cout<<"\nLeft or Right of Root : ";
				cin>>pos;
				if(pos=='l')
					CreateTree(root, root->left, x, pos);
				else if(pos=='r')
					CreateTree(root, root->right, x, pos);
				break;
			case 2:
				BFT(root);
				break;
			case 3:
				Pre(root);
				break;
			case 4:
				In(root);
				break;
			case 5:
				Post(root);
				break;
		}
	}
	while(ch!=0);
}
