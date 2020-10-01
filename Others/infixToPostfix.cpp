//Infix To Postfix conversion using Stack
//---------------------------------------

#include<iostream>
#include<string>
#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;


int prec(char c)
{
    if(c=='^')return 3;
    else if(c=='*'||c=='/')return 2;
    else if(c=='+'||c=='-')return 1;
    else
    return -1;
}
void InfiToPost(string s)
{
	std::stack<char> stk;
	stk.push('N');
	int l=s.length();
	string ns;
	
	
	for (int i=0;i<l;i++)
	{
		if(s[i]>='a'&&s[i]<='z'||s[i]>='A'&&s[i]<='Z')
		{
			ns+=s[i];
		}
		else if(s[i]=='(')
		{
			char c;
			c=s[i];
			stk.push(c);
		}
		else if(s[i] == ')')
		{
			while( stk.top()!='N' && stk.top()!='('){
			
				char c=stk.top();
				ns+=c;
				stk.pop();
			}
			if(stk.top()=='(')
			{
				char c=stk.top();
				stk.pop();			
			}
		}
		else
		{
			while(stk.top()!='N' && prec(s[i])<=prec(stk.top()))
			{
				char c=stk.top();
				stk.pop();
				ns+=c;
			}
			stk.push(s[i]);
		}
		
	}
	
	while(stk.top()!='N')
	{
		char c=stk.top();
		ns+=c;
		stk.pop();
	}
	cout<<ns<<endl;
}

int main()
{

	string exp;
	cout<<"Enter your string: ";
	cin>>exp;
	InfiToPost(exp);
	return 0;
}
