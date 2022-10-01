#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s;
    cin>>s;
    int len=s.size();
    transform(s.begin(),s.end(),s.begin(),::tolower);
    for(int i=0;i<len;i++)
    {
        if(s[i]=='a' || s[i]=='e' || s[i]=='i' || s[i]=='o' || s[i]=='u' || s[i]=='y')
        {
            continue;
        }
        else
        {
            cout<<"."<<s[i]<<"";
        }

    }
    return 0;

}
