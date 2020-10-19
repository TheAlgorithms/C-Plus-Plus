/*
To find the longest sequence of balanced parentheses
for example in ()()())
answer is 6
 in (()))()(())
 answer is 6


*/





#include <bits\stdc++.h>
 using namespace std;
 int main()
 {
	 stack <int> index;
	 stack <char> b;
	 string s;
	cin>>s;
	int max = 0 ;
	index.push(-1);
	for(int i=0;i<s.length();++i)
	{
		if(s[i] == '(')
		{
			index.push(i);
			b.push('(');
		}
		else
		{
			if(!b.empty() && b.top() == '(' )
			{
				index.pop();
				b.pop();
				int temp = i-index.top();
				if(max<temp)
					max = temp;
				
			}
			else{
				index.push(i);
			}
		}
	}
	 cout<<max<<endl;
	 return 0;
	 
 }
