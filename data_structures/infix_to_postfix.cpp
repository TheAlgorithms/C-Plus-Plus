#include <iostream>
#include <stack>
using namespace std;

bool isOperator(char c)
/* If the scanned character is an operand, add it to output string.*/
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
	{
		return true;
	}
	else
	{
		return false;
	}
}

int precedence(char c)
{
	if (c == '^') //Highest precedence
		return 3;
	else if (c == '*' || c == '/')
		return 2;
	else if (c == '+' || c == '-') //owest precedence
		return 1;
	else
		return -1;
}
/* The main function to convert infix expression to postfix expression*/
string InfixToPostfix(stack<char> s, string infix) //we are using stack here
{
	string postfix;
	for (int i = 0; i < infix.length(); i++)
	{
		/*If the scanned character is an operand, add it to output string.*/
		if ((infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z'))
		{
			postfix += infix[i];
		}
		/*If the scanned character is an ‘(‘, push it to the stack.*/
		else if (infix[i] == '(')
		{
			s.push(infix[i]);
		}
		/*If the scanned character is an ‘)’,pop and to output string 
        from the stack until an ‘(‘ is encountered.*/
		else if (infix[i] == ')')
		{
			while ((s.top() != '(') && (!s.empty()))
			{
				char temp = s.top();
				postfix += temp;
				s.pop();
			}
			if (s.top() == '(')
			{
				s.pop();
			}
		}
		else if (isOperator(infix[i])) /* initialize before loop*/
		{
			if (s.empty())
			{
				s.push(infix[i]);
			}
			else
			{
				//If an operator is scanned

				if (precedence(infix[i]) > precedence(s.top()))
				{
					s.push(infix[i]);
				}
				else if ((precedence(infix[i]) == precedence(s.top())) && (infix[i] == '^'))
				{
					/* so pop all higher 
                precendence operator and */
					s.push(infix[i]);
				}
				else
				{
					while ((!s.empty()) && (precedence(infix[i]) <= precedence(s.top())))
					/* because just above while loop will terminate we have 
                    oppped one extra item 
                    for which condition fails and loop terminates, so that one*/
					{
						postfix += s.top();
						s.pop();
					}
					s.push(infix[i]);
				}
			}
		}
	}
	// Pop all the remaining elements from the stack
	while (!s.empty())
	{
		postfix += s.top();
		s.pop();
	}

	return postfix;
}

int main()
{

	string infix_exp, postfix_exp;
	cout << "Enter a Infix Expression :" << endl;
	cin >> infix_exp; /*Take infix expression*/
	stack<char> stack;
	cout << "INFIX EXPRESSION: " << infix_exp << endl;
	postfix_exp = InfixToPostfix(stack, infix_exp); /*Change expression*/
	cout << endl
		 << "POSTFIX EXPRESSION: " << postfix_exp; /* print postfix expression */

	return 0;
}
