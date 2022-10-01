#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,i;
    cin>>n;
    string s1,s2;
    set<pair<string,string>>s;
    for(i=0;i<n;i++)
    {
        cin>>s1>>s2;
        s.insert(make_pair(s1,s2));
    }
    cout<<s.size()<<endl;
}
