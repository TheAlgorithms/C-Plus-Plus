#include<bits/stdc++.h>
using namespace std;
bool checkValid (char a,char b){
    return (a == '(' && b == ')') || (a == '{' && b == '}') || (a == '[' && b == ']');
}
bool check(string str)
{
    stack<char>s;
    for (int i = 0; i < str.size(); i++)
    {
        if(str[i]=='(' || str[i]=='{'|| str[i]=='['){
            s.push(str[i]);
        }
        else{
        
            if(!s.empty() && checkValid(s.top(),str[i])){
                s.pop();
            }
            else{
                return false;
            }
        }
    }       
    return s.empty()==true;
}
int main()
{
    cout<<check("{}[(())]");
return 0;
}
