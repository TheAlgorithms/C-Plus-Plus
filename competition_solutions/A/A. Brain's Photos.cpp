#include<bits/stdc++.h>
using namespace std;
int main()
{
    int l,k,i,j,c=0;
    cin>>l>>k;
    for(i=0;i<l*k;i++)
    {
            string s;
            cin>>s;
            if(s=="C" || s=="M" || s=="Y")c++;

    }
    if(c)cout<<"#Color\n";
    else cout<<"#Black&White\n";
    return 0;
}
