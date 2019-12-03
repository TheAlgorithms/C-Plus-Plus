#include <iostream>
using namespace std;

struct node
{
	int val;
	node *prev;
	node *next;
};

node *start;

void insert(int x)
{
	node *t = start;
	if (start != NULL)
	{
		while (t->next != NULL)
		{
			t = t->next;
		}
		node *n = new node;
		t->next = n;
		n->prev = t;
		n->val = x;
		n->next = NULL;
	}
	else
	{
		node *n = new node;
		n->val = x;
		n->prev = NULL;
		n->next = NULL;
		start = n;
	}
}

void remove(int x)
{
	node *t = start;
	while (t->val != x)
	{
		t = t->next;
	}
	t->prev->next = t->next;
	t->next->prev = t->prev;
	delete t;
}

void search(int x)
{
	node *t = start;
	int found = 0;
	while (t != NULL)
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

void show()
{
	node *t = start;
	while (t != NULL)
	{
		cout << t->val << "\t";
		t = t->next;
	}
}

void reverseShow()
{
	node *t = start;
	while (t->next != NULL)
	{
		t = t->next;
	}
	while (t != NULL)
	{
		cout << t->val << "\t";
		t = t->prev;
	}
}

int main()
{
	int choice, x;
	do
	{
		cout << "\n1. Insert";
		cout << "\n2. Delete";
		cout << "\n3. Search";
		cout << "\n4. Forward print";
		cout << "\n5. Reverse print";
		cout << "\n\nEnter you choice : ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "\nEnter the element to be inserted : ";
			cin >> x;
			;
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
		case 5:
			reverseShow();
			break;
		}
	} while (choice != 0);

	return 0;
}
