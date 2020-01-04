#include <iostream>
using namespace std;

int *stack;
int top = 0, size;

void push(int x)
{
	if (top == size)
	{
		cout << "\nOverflow";
	}
	else
	{
		stack[top++] = x;
	}
}
void pop()
{
	if (top == 0)
	{
		cout << "\nUnderflow";
	}
	else
	{
		cout << "\n"
			 << stack[--top] << " deleted";
	}
}
void show()
{
	for (int i = 0; i < top; i++)
	{
		cout << stack[i] << "\n";
	}
}
void topmost()
{
	cout << "\nTopmost element: " << stack[top - 1];
}
void print_by_choice()
{
	cout<<"\nEnter element no: ";
	int ele_no;
	cin>>ele_no;
  if(ele_no<top) cout<<"\nElement no "<<ele_no<<" is: "<<stack[ele_no-1]<<"\n";
  else cout<<"\nEnter no under size:\n ";
}
int main()
{
	cout << "\nEnter Size of stack : ";
	cin >> size;
	stack = new int[size];
	int ch, x;
	do
	{
		cout << "\n1. Push";
		cout << "\n2. Pop";
		cout << "\n3. Print";
		cout << "\n4. Print topmost element:";
		cout<<"\n5. Print element of your choice:";
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
		else if (ch == 4)
		{
			topmost();
		}
		else if (ch == 5)
		{
			print_by_choice();
		}
	} while (ch != 0);
	return 0;
}
