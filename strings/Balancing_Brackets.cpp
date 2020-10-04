/*link to problem for practice:-"https://www.codechef.com/problems/BRACKETS"*/

/*using simple loops and conditions*/

#include <iostream>
using namespace std;

int main() {
	int t;
	cin>>t;
	while(t--){
	    string s;
	    cin>>s;
	    int b=0,bMax=0;
      //using this loop to count the number of balance '()' pair present note that ')(' or '((' or '))' are automatically excluded and then we have 1 count for each '()' this pair found in the string
	    for(int i=0;i<s.length();++i){
	        if(s[i]=='(') 
			b++;
	        else 
			b--;
	        bMax = max(b,bMax);
	    }
	    b=bMax;
      //running the loop to print the '()' brackets accordingly by adjusting the correct positions
	    while(b--) cout<<'(';
	    while(bMax--) cout<<')';
	    cout<<endl;
	}
	return 0;
}

// CPP program to check for balanced parenthesis in case any body wants to check only balance in question*/
#include <iostream>
//include bits/stdc++.h to include stl library of the stack e.g.<stack> s;
using namespace std; 

// function to check if paranthesis are balanced 
bool areParanthesisBalanced(string expr) 
{ 

	stack<char> s; 
	char x; 

	// Traversing the Expression 
	for (int i = 0; i < expr.length(); i++) { 
		if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{') 
    { 
			// Push the element in the stack 
			s.push(expr[i]); 
			continue; 
		} 

		// IF current current character is not opening 
		// bracket, then it must be closing. So stack 
		// cannot be empty at this point. 
		if (s.empty()) 
			return false; 

		switch (expr[i]) 
		{ 
		case ')': 

			// Store the top element in a 
			x = s.top(); 
			s.pop(); 
			if (x == '{' || x == '[') 
				return false; 
			break; 

		case '}': 

			// Store the top element in b 
			x = s.top();
			s.pop();
			if (x == '(' || x == '[') 
				return false; 
			break; 

		case ']': 

			// Store the top element in c 
			x = s.top(); 
			s.pop(); 
			if (x == '(' || x == '{') 
				return false; 
			break; 
		} 
	} 

	// Check Empty Stack 
	return (s.empty()); 
} 

// Driver program to test above function 
int main() 
{ 
	string expr = "{()}[]"; 

	if (areParanthesisBalanced(expr)) 
		cout << "Balanced"; 
	else
		cout << "Not Balanced"; 
	return 0; 
} 


/*
example
1
()((()()))
((()))*/
