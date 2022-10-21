//find all Subset
#include<bits/stdc++.h>
using namespace std;
void subset(string &s,string curr="",int index=0){
if(index==s.size()){
    cout<<curr<<" ";
    return ;
}
subset(s,curr,index+1);
subset(s,curr+s[index],index+1);
}
int main()
{
    string s="ABC";
    subset(s);
return 0;
}
