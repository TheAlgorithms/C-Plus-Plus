//Kadane Algorithm used to find largest sum of subarray in O(n) time complexity.
#include<bits/stdc++.h>
typedef long long int ll;
#define for(i,a,b) for(ll i=a;i<b;i++)
using namespace std;
int main()
{
ios::sync_with_stdio(0);
//cin.tie(0);
ll n;
cout<<"ENTER THE SIZE OF ARRAY:"<<"\n";
cin>>n;
ll arr[n],sum=0,best=0;
for(i,0,n)
{cin>>arr[i];
}
for(i,0,n)
{// This is used to find the largest sum upto ith element
	sum=max(arr[i],sum+arr[i]);
	best=max(best,sum);
}
cout<<best<<"\n";
}

