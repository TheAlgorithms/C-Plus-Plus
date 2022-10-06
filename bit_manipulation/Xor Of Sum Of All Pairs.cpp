//1. You are given an array of integers.
//2. You have to find the XOR of sum of all pairs in the array.

#include<bits/stdc++.h>
using namespace std;

int solution(vector<int> &v1)
{
    int ans=0;
    for(int &ele:v1) ans^=(ele+ele);
    return ans;
}

int main()
{
    int n;
    cin>>n;
    vector<int> v1(n);
    for(int i=0;i<n;++i) cin>>v1[i];
    cout<<solution(v1)<<"\n";
    return 0;
}
