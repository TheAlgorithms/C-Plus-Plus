#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
    ll n,i;
    cin>>n;
    ll arr[n];
    for(i=0;i<n;i++)cin>>arr[i];
    ll mx=0,loc;
    for(i=0;i<n;i++)
    {
        if(mx<arr[i])
        {
            mx=arr[i];
            loc=i;
        }
    }
    cout<<loc+1<<" ";
    sort(arr,arr+n);
    cout<<arr[n-2]<<"\n";
}
