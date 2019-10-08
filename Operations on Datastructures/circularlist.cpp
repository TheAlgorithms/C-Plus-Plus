#include <iostream>
using namespace std;

//creating a node in the circular queue
struct node
{
	int val;
	node *next;
};

node *start;

//function for inserting an element in the circular queue
void insert(int x)
{
	node *t = start;

	if (start != NULL)
	{
		while (t->next != start)
		{
			t = t->next;
		}
		node *n = new node;
		t->next = n;
		n->val = x;
		n->next = start;
	}
	else
	{
		node *n = new node;
		n->val = x;
		start = n;
		n->next = start;
	}
}

//function to remove an element from the circular queue
void remove(int x)
{
	node *t = start;
	node *p;
	while (t->val != x)
	{
		p = t;
		t = t->next;
	}
	p->next = t->next;
	delete t;
}

//function for searching an element in the circular queue
void search(int x)
{
	node *t = start;
	int found = 0;
	while (t->next != start-1)
	{
		if (t->val == x)
		{
			cout << "\nFound";
			found = 1;
			break;
		}
		t = t->next;
	}
	if (found == 0)
	{
		cout << "\nNot Found";
	}
}

//function for printing the circular queue
void show()
{
	node *t = start;
	do
	{
		cout << t->val << "\t";
		t = t->next;
	} while (t != start);
}

int main()
{
	int choice, x;
	do
	{
		cout << "\n1. Insert";
		cout << "\n2. Delete";
		cout << "\n3. Search";
		cout << "\n4. Print";
		cout << "\n\nEnter you choice : ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "\nEnter the element to be inserted : ";
			cin >> x;
			insert(x);
			break;
		case 2:
			cout << "\nEnter the element to be removed : ";
			cin >> x;
			remove(x);
			break;
		case 3:
			cout << "\nEnter the element to be searched : ";
			cin >> x;
			search(x);
			break;
		case 4:
			show();
			break;
		}
	} while (choice != 0);

	return 0;
}
