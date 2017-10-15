#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
using namespace std;

char stack[100];
int top=0;

void push(char ch)
{
	stack[top++]=ch;
}

char pop()
{
	return stack[--top];
}

bool check(char x, char y)
{
	if ((x=='(' && y==')') || (x=='{' && y=='}') || (x=='[' && y==']') || (x=='<' && y=='>'))
	{
		return true;
	}
	else
	{
		return false;
	}
}



int main()
{
	char exp[100];
	cout<<"Enter The Expression : ";
	gets(exp);
	for (int i = 0; i < strlen(exp); i++)
	{
			if (exp[i]=='(' || exp[i]=='{' || exp[i]=='[' || exp[i]=='<')
			{
				push(exp[i]);
			}
			else if (exp[i]==')' || exp[i]=='}' || exp[i]==']' || exp[i]=='>')
			{
				if(!check(pop(), exp[i]))
				{
					cout<<"\nWrong Expression";
					exit(0);
				}
			}
	}

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
