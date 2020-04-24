#include <iostream>
using namespace std;

struct node
{
	int val;
	node *next;
};

node *top;

void push(int x)
{
	node *n = new node;
	n->val = x;
	n->next = top;
	top = n;
}

void pop()
{
	if (top == NULL)
	{
		cout << "\nUnderflow";
	}
	else
	{
		node *t = top;
		cout << "\n"
			 << t->val << " deleted";
		top = top->next;
		delete t;
	}
}

void show()
{
	node *t = top;
	while (t != NULL)
	{
		cout << t->val << "\n";
		t = t->next;
	}
}

int main()
{
	int ch, x;
	do
	{
		cout << "\n1. Push";
		cout << "\n2. Pop";
		cout << "\n3. Print";
		cout << "\nEnter Your Choice : ";
		cin >> ch;
		if (ch == 1)
		{
			cout << "\nInsert : ";
			cin >> x;
			push(x);
		}
		else if (ch == 2)
		{
			pop();
		}
		else if (ch == 3)
		{
			show();
		}
	} while (ch != 0);

	return 0;
}
