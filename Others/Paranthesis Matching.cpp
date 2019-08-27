#include <iostream>
#include <string>

using namespace std;

#define MAX 100

// -------------- stack --------------

char stack[MAX];
int top = -1;

void push(char ch)
{
	stack[++top] = ch;
}

char pop()
{
	return stack[top--];
}

// -------------- end stack -----------

char opening(char ch)
{
	switch (ch)
	{
	case '}':
		return '{';
	case ']':
		return '[';
	case ')':
		return '(';
	case '>':
		return '<';
	}
}

int main()
{

	string exp;
	int valid = 1, i = 0;
	cout << "Enter The Expression : ";
	cin >> exp;

	while (valid == 1 && i < exp.length())
	{
		if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[' || exp[i] == '<')
		{
			push(exp[i]);
		}
		else if (top >= 0 && stack[top] == opening(exp[i]))
		{
			pop();
		}
		else
		{
			valid = 0;
		}
		i++;
	}

	// makes sure the stack is empty after processsing (above)
	if (valid == 1 && top == -1)
	{
		cout << "\nCorrect Expression";
	}
	else
	{
		cout << "\nWrong Expression";
	}

	return 0;
}
