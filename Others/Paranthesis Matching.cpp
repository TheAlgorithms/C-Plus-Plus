#include<iostream>
#include<stdlib.h>
#include<string>
#include<stdio.h>
using namespace std;

const int MAX = 100;

// -------------- stack --------------

char stack[MAX];
int top=0;

void push(char ch)
{
	stack[top++]=ch;
}

char pop()
{
	return stack[--top];
}

// -------------- end stack -----------

int main()
{
	string exp;
	cout<<"Enter The Expression : ";
	cin >> exp;
	for (int i = 0; i < exp.length(); i++)
	{
			if (exp[i]=='(' || exp[i]=='{' || exp[i]=='[' || exp[i]=='<')
			{
				push(exp[i]);
			}
			else if (exp[i]==')' || exp[i]=='}' || exp[i]==']' || exp[i]=='>')
			{
                pop();
			}
	}

    // makes sure the stack is empty after processsing (above)
	if(top==0)
	{
		cout<<"Correct Expression";
	}
	else
	{
		cout<<"\nWrong Expression";
	}

	return 0;
}
