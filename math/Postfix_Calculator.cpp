/*
 * functions.cpp
 *
 *  Created on: 07-Mar-2020
 *      Author: sunbeam
 */

#include<iostream>
using namespace std;
#include<stack>
#include<cstring>

//Declaration of the functions
void infix_to_postfix(char *in, char *post);
bool is_operand(char ch);
int priority(char opr);
int postfix_evaluation(char *post);
int calculate(int op1, int op2, char opr);

//cur = current

void infix_to_postfix(char *in, char *post)
{
	int j=0;
	stack<int> s;

	for( int i = 0 ; in[i] != '\0' ; i++ )
	{
		//if the cur ele is an operand
		if( is_operand(in[i]) )
		{
			//append it into the postfix string
			post[j++] = in[i];
		}
		else
		if( in[i] == '(')//if the current is an opening brace
		{
			//push it into the stack
			s.push(in[i]);
		}
		else
		if( in[i] == ')')//if the cur is a closing brace
		{
			//pop all ele'e from the stack one by one and append them into the
			//postfix string till its corresponding opening brace do not occures
			while( s.top() != '(' )
			{
				post[j++] = s.top();
				s.pop();
			}
			//pop an opening brace from the stack
			s.pop();
		}
		else//if the cur is an operator
		{
			//if stack is not empty && priority(topmost ele) >= priority(cur ele)
			while( !s.empty() && priority(s.top()) >= priority(in[i]))
			{
				//pop ele from the stack and append it into the postfix string
				post[j++] = s.top();
				s.pop();
			}

			s.push(in[i]);
		}

	}

	//pop all ele's one by one from the stack and append them into the postfix string

	while( !s.empty())
	{
		post[j++] = s.top();
		s.pop();
	}

	post[j] = '\0';
}


int postfix_evaluation(char *post)
{
	int result;
	stack<int> s;

	for( int i = 0 ; post[i] != '\0' ; i++ )
	{
		//if the cur ele is an operand
		if( is_operand(post[i]))
		{
			//push it into the stack
			s.push(post[i]-'0');
		}
		else//if the cur ele is an operator
		{
			//pop two ele's from the stack
			//first popped ele will be the second operand
			int op2 = s.top(); s.pop();

			//second popped ele will be the first operand
			int op1 = s.top(); s.pop();

			result = calculate(op1, op2, post[i]);
			//push result into the stack

			s.push(result);
		}
	}

	//pop the final result from the stack and return it to the calling function
	result = s.top(); s.pop();
	return result;
}


bool is_operand(char ch)
{
	return ( (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || (ch >= 48 && ch <= 57) );
}

int calculate(int op1, int op2, char opr)
{
	switch(opr)
	{
	case '+': return ( op1 + op2 );
	case '-': return ( op1 - op2 );
	case '*': return ( op1 * op2 );
	case '/': return ( op1 / op2 );
	case '%': return ( op1 % op2 );
	}
return 0;
}

//we are defining priority for a an operators - programmatically
int priority(char opr)
{
	switch(opr)
	{
	case '(': return 0;

	case '+':
	case '-': return 1;

	case '*':
	case '/':
	case '%': return 2;
	}
	return 0;
}



int main(void)
{
	char infix[64];
	cout<<"Enter Infix Expression :";
	cin>>infix;
	char postfix[64] = "";

	cout<<endl;
	cout << "Infix Expression : " << infix << endl;
	infix_to_postfix(infix, postfix);
	cout << "Postfix Expression : " << postfix << endl;

	cout << "Postfix Evaluation Result = " << postfix_evaluation(postfix) << endl;


	return 0;
}







