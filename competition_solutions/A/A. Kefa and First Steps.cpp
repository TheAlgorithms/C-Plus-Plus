#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    long long int arr[n];
    for(int i=0; i<n; i++)
    {
        cin>>arr[i];
    }
    if(n==1)
    {
        cout<<"1"<<endl;
        return 0;
    }
    int ans=1,mx=0;
    for(int i=0; i<n-1; i++)
    {
        mx=max(ans,mx);
        if(arr[i]<=arr[i+1])
        {
            ans+=1;

            mx=max(ans,mx);
        }

        else
        {
            ans=1;
        }

    }
    //cout<<cnet<<endl;
    cout<<mx<<endl;

    return 0;
}
