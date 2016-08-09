#include<iostream>
using namespace std;

struct node
{
	int val;
	node *next;
};


node *front, *rear;


void push(int x)
{
	if (rear==NULL)
	{
		node *n= new node;
		n->val=x;
		n->next=NULL;
		rear=n;
		front=n;
	}

	else
	{

		node *n = new node;
		n->val=x;
		n->next=NULL;
		rear->next=n;
		rear=n;
	}
}

void pop()
{
	if (rear==front)
	{
		cout<<"\nUnderflow";
	}
	else
	{
		node *t = front;
		cout<<"\n"<<t->val<<" deleted";
		front=front->next;
		delete t;
	}
}

void show()
{
	node *t=front;
	while(t!=NULL)
	{
		cout<<t->val<<"\t";
		t=t->next;
	}
}

int main()
{
	int ch, x;
	do
	{
		cout<<"\n1. Push";
		cout<<"\n2. Pop";
		cout<<"\n3. Print";
		cout<<"\nEnter Your Choice : ";
		cin>>ch;
		if (ch==1)
		{
			cout<<"\nInsert : ";
			cin>>x;
			push(x);
		}
		else if (ch==2)
		{
			pop();
		}
		else if (ch==3)
		{
			show();
		}
	}
	while(ch!=0);

	return 0;
}

