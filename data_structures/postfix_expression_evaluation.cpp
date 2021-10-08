/* In this Input will be Postfix Expression on which particular operations will be 
performed using stacks and output will be the result of that expression.
Eg. Input => 4 6 + 2 / 5 * 7 +       Output => 32
Evaluation =>((((4+6)/2)*5)+7) = 32
*/

//code by Sanskruti Shahu (https://github.com/sanskruti-shahu)

#include<iostream>
#include <stack>
using namespace std;

int postfixEval (string s)
{
	stack<int> st;
	int operand1,operand2;
	for(int i=0;i<s.size();i++)
	{
		if(s[i]>=48)
        {
			st.push(s[i]-48);
		}
		else
        {
			operand2=st.top();       
			st.pop();           
			operand1=st.top();        
			st.pop();
			if(s[i]=='+')
            {
				st.push(operand1+operand2);
			}
			else if(s[i]=='-')
            {
				st.push(operand1-operand2);
			}
			else if(s[i]=='*')
            {
				st.push(operand1*operand2);
			}
			else if(s[i]=='/')
            {
				st.push(operand1/operand2);
			}
			else if(s[i]=='^')
            {
				st.push(operand1^operand2);
			}
		}
	}
	return st.top();
}

int main()
{
    string s;
    cin>>s;
    cout<<"Result = "<<postfixEval(s)<<endl;
}

/* SAMPLE
Testcase 1
INPUT   34-4*7/8+
OUTPUT  8
Testcase 2
INPUT   90+8/9-
OUTPUT  -8  
Time Complexity is O(n).  (where n is length of string)
Space Complexity is O(1)   */
