#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long k,r,i=1;
    cin>>k>>r;
    while(k!=0)
    {
        if((k*i)%10==0)
        {
            cout<<i<<endl;
            break;
        }
        if(((k*i)-r)%10==0)
        {
            cout<<i<<endl;
            break;
        }

        i++;
    }

    return 0;
}
