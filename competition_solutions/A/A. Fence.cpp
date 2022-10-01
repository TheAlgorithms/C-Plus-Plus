#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int a,b,c;
        cin>>a>>b>>c;
        if((a+b)>c)
        {
            cout<<a+b<<endl;
        }
        else if((b+c)>a)
        {
            cout<<b+c<<endl;
        }
        else if((c+a)>b)
        {
            cout<<c+a;
        }
        else if((a+b+c)>c)
        {
            cout<<a+b+c<<endl;
        }

    }
    return 0;
}
