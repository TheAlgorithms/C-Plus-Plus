/* In this Input will be Prefix Expression on which particular operations will be 
performed using stacks and output will be the result of that expression.
Eg. Input => - + 7 * 4 5 + 2 0       Output => 25
Evaluation =>(7+(4*5)-(2+0)) = 25
*/

//code by Sanskruti Shahu (https://github.com/sanskruti-shahu)

#include<iostream>
#include <stack>
using namespace std;

int prefixEval (string s)
{
	stack<int> st;
	int operand1,operand2;
	for(int i=(s.size()-1);i>=0;i--)
	{
		if(s[i]>=48)
        {
			st.push(s[i]-48);
		}
		else
        {
			operand1=st.top();       
			st.pop();           
			operand2=st.top();        
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
    cout<<"Result = "<<prefixEval(s)<<endl;
}

/* SAMPLE
Testcase 1
INPUT   -+7*45+20
OUTPUT  25
Testcase 2
INPUT   -*97/81
OUTPUT  55
Time Complexity is O(n)  (where n is length of string)
Space Complexity is O(1)   */
