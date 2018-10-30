#include<bits/stdc++.h>
using namespace std;

int main()
{
int num;
cin>>num;

string s1 = to_string(num);
string s2 = s1;

reverse(s1.begin(),s1.end());

if(s1==s2)
  cout<<"true";
else
  cout<<"false";

return 0;
}
