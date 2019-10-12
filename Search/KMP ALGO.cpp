#include<bits/stdc++.h>
using namespace std;

int main()
{
    string s1,s2;
    cin>>s1>>s2;

    int m=s2.length();
    int dp[m];
    dp[0]=0;
    int i=0,j=1;
    while(j<m)
    {
        if(s2[i]==s2[j])
        {
            dp[j]=dp[j-1]+1;
            i++,j++;
        }
        else
        {
            int f=0;
            while(i>0 || s2[i]==s2[j])
            {
                if(s2[i]==s2[j])
                {
                    f=1;
                    dp[j]=dp[i]+1;
                    break;
                }
                else
                    i=dp[i-1];
            }
            if(f==0)
            {
                if(s2[i]!=s2[j])
                    dp[j]=0;
                else
                    dp[j]=1;
            }
            j++;
        }
    }
    /*for(int i=0;i<m;i++)
        cout<<dp[i]<<" ";*/

    i=j=0;
    int l=0;
    while(i<s1.length())
    {
        cout<<i<<" "<<j<<"###"<<endl;
        if(j==s2.length())
        {
            cout<<i<<"^^^"<<j<<endl;
            cout<<"$$$$"<<endl;
            break;
        }

        else
        {
            if(s1[i]==s2[j])
            {
                i++,j++;
            }
            else if(j==0 && s1[i]!=s2[j])
            {
                i++;
            }
            else
            {
                j=dp[j-1];
                //cout<<j<<"$$$"<<endl;
            }
        }
    }

    cout<<i<<" "<<j<<endl;

    return 0;
}
