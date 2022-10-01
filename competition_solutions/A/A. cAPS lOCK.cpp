#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s;
    cin>>s;
    int up=0,low=0,cn=0;
    if(islower(s[0]))
    {
        cn++;
        for(int i=1; i<s.size(); i++)
        {
            if(islower(s[i]))
            {
                cn++;
            }
        }
        if(cn==1)
        {
            for(int i=0; i<s.size(); i++)
            {
                if(islower(s[0]))
                {
                    s[0]=toupper(s[0]);
                }
                else
                {
                    s[i]=tolower(s[i]);
                }
            }
            cout<<s<<endl;
        }
        else
        {
            cout<<s<<endl;
        }

    }
    else if(isupper(s[0]))
    {
        up++;
        for(int i=1;i<s.size();i++)
        {
            if(isupper(s[i]))
            {
                up++;
            }
        }
        if(up==s.size())
        {
            for(int i=0;i<s.size();i++)
            {
                s[i]=tolower(s[i]);
            }
            cout<<s<<endl;
        }
        else
            cout<<s<<endl;
    }
    else
    {
        cout<<s<<endl;
    }
   // cout<<cn<<low<<endl;


    return 0;
}
