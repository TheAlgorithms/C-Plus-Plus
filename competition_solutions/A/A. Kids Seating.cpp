#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,nn=0;
        cin>>n;
        int cnet=4*n;
        for(int i=0; i<n; i++)
        {
            cout<<cnet<<" ";
            cnet-=2;
        }
        cout<<"\n";

    }
    return 0;
}
