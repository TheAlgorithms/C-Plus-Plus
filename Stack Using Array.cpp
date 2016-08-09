#include<iostream>
using namespace std;

int stack[10];
int top=0;

void push(int x)
{
	if(top==10)
	{
		cout<<"\nOverflow";
	}
	else
	{
		stack[top++]=x;
	}
}

void pop()
{
	if (top==0)
	{
		cout<<"\nUnderflow";
	}
	else
	{
		cout<<"\n"<<stack[--top]<<" deleted";
	}
}

void show()
{
	for (int i = 0; i < top; i++)
	{
		cout<<stack[i]<<"\n";
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

