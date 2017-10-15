#include<iostream>
using namespace std;

struct node
{
	int val;
	node *next;
};

node *start;

void insert(int x)
{
	node *t=start;
	if (start!=NULL)
	{
			while(t->next!=NULL)
		{
			t=t->next;
		}
		node *n= new node;
		t->next=n;
		n->val=x;
		n->next=NULL;
	}
	else
	{
		node *n= new node;
		n->val=x;
		n->next=NULL;
		start=n;
	}
}

void remove(int x)
{
	node *t=start;
	node *p;
	while(t->val!=x)
	{
		p=t;
		t=t->next;
	}
	p->next=t->next;
	delete t;
}

void search(int x)
{
	node *t= start;
	int found =0;
	while(t!=NULL)
	{
		if(t->val==x)
		{
			cout<<"\nFound";
			found=1;
			break;
		}
		t=t->next;
	}
	if(found==0)
	{
		cout<<"\nNot Found";
	}
}

void show()
{
	node *t=start;
	while(t!=NULL)
	{
		cout<<t->val<<"\t";
		t=t->next;
	}

}

int main()
{
	int choice, x;
	do
	{
		cout<<"\n1. Insert";
		cout<<"\n2. Delete";
		cout<<"\n3. Search";
		cout<<"\n4. Print";
		cout<<"\n\nEnter you choice : ";
		cin>>choice; 
		switch (choice)
		{
			case 1 : 	cout<<"\nEnter the element to be inserted : ";
					 	cin>>x;;
					 	insert(x);	break;
			case 2 : 	cout<<"\nEnter the element to be removed : ";
						cin>>x;
						remove(x); 	break;
			case 3 : 	cout<<"\nEnter the element to be searched : ";
						cin>>x;
						search(x); 	break;
			case 4 : show();	break;
		}
	}
	while(choice!=0);

	return 0;
}
