#include <iostream>
using namespace std;

int queue[10];
int front = 0;
int rear = 0;

void Enque(int x)
{
	if (rear == 10)
	{
		cout << "\nOverflow";
	}
	else
	{
		queue[rear++] = x;
	}
}

void Deque()
{
	if (front == rear)
	{
		cout << "\nUnderflow";
	}

	else
	{
		cout << "\n"
			 << queue[front++] << " deleted";
		for (int i = front; i < rear; i++)
		{
			queue[i - front] = queue[i];
		}
		rear = rear - front;
		front = 0;
	}
}

void show()
{
	for (int i = front; i < rear; i++)
	{
		cout << queue[i] << "\t";
	}
}

int main()
{
	int ch, x;
	do
	{
		cout << "\n1. Enque";
		cout << "\n2. Deque";
		cout << "\n3. Print";
		cout << "\nEnter Your Choice : ";
		cin >> ch;
		if (ch == 1)
		{
			cout << "\nInsert : ";
			cin >> x;
			Enque(x);
		}
		else if (ch == 2)
		{
			Deque();
		}
		else if (ch == 3)
		{
			show();
		}
	} while (ch != 0);

	return 0;
}
