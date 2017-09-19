#include <iostream>
#include <string>
#include <stack>
using namespace std;

int precedence(char c) //to check the priority of characters
{
	if(c=='^')
	return 3;
	else if(c=='*' || c=='/')
	return 2;
	else if(c=='+' || c=='-')
	return 1;
	else 
	return -1;
}

void converttopostfix(string s)
{
	stack<char> st;
	st.push('N'); // an arbitrary character pushed to stack
	int l=s.length();
	string ns;
	for(int i=0;i<l;i++)
	{
		if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
		ns=ns+s[i];
		else if(s[i] == '(')
		st.push('(');
		else if(s[i] == ')') //pop until we get left parenthesis
		{
			while(st.top() != 'N' && st.top() != '(')
			{
				char c=st.top();
				st.pop();
				ns=ns+c;
			}
			if(st.top() == '(')
			{
				char c=st.top();
				st.pop();
			}
		}
		else
		{
			while(st.top() != 'N' && (precedence(s[i])<=precedence(st.top())))
			{
				char c=st.top();
				st.pop();
				ns=ns+c;
			}
			st.push(s[i]);
		}
	}
	while(st.top() != 'N') //keep popping until stack top is N
	{
		char c=st.top();
		st.pop();
		ns=ns+c;
	}
	
	cout<<ns<<endl;
}

int main()
{		
	string s;
        cin>>s;
        converttopostfix(s);
	return 0;
}
