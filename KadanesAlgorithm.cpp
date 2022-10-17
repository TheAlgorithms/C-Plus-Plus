#include<bits/stdc++.h>
using namespace std;
long long maxSubarraySum(int arr[], int n){

        int mx=INT_MIN;
        int currsum=0;
        for(int i=0;i<n;i++)
        {
            currsum=max(currsum+arr[i],arr[i]);
            mx=max(currsum,mx);
        }
        return mx;
    }
int main()
{
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    cout<<maxSubarraySum( arr, n)<<endl;
    return 0;
}
