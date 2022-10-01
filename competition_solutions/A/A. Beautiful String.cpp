#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    read:
    while(t--)
    {
        string s;
        cin>>s;
        char s1='a',s2='b',s3='c';
        int ll = s.size();
        for(int i=0; i<ll; i++)
        {
            if(s[i]==s[i+1] && s[i]!='?')
            {
                cout<<"-1"<<endl;
                goto read;
            }
            if(s[i]=='?')
            {
                if(s[i-1]!='c' && s[i+1]!='c')s[i]='c';
                if(s[i-1]!='b' && s[i+1]!='b')s[i]='b';
                if(s[i-1]!='a' && s[i+1]!='a')s[i]='a';

            }
        }
        cout<<s<<endl;
    }
    return 0;

}
