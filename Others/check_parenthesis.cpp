#include<iostream>
#include<string.h>
using namespace std;

int check_paranthesis(char *exp)
{
	char stack[20],temp;
	int top=-1,flag=1;
	for(int i=0;i<strlen(exp);i++)
    {
		
		if(exp[i]=='(' || exp[i]=='{' || exp[i]=='[')
			stack[++top]=exp[i];
		if(exp[i]==')' || exp[i]=='}' || exp[i]==']')
			if(top == -1)
			    flag=0;
			else
			{
				temp=stack[top--];
				if(exp[i]==')' && (temp=='{' || temp=='['))
					flag=0;
				if(exp[i]=='}' && (temp=='(' || temp=='['))
					flag=0;
				if(exp[i]==']' && (temp=='(' || temp=='{'))
					flag=0;
			}
	}
	if(top>=0)
		flag=0;
	return flag;
}


int main()
{
	int n;
	cout<<"enter the no of character in the expression>>";
	cin>>n;
	char exp[n];
	cout<<"Enter the expression>>>";
	cin>>exp;
	if(check_paranthesis(exp)==1)
	    cout<<"Valid Expression";
	else 
		cout<<"Invalid Expression";
	cout<<endl;
    return 0;
}
