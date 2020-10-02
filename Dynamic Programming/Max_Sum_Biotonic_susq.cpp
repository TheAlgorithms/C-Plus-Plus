/*
Maximum Sum Bitonic Subsequence
Given an array of integers A. A subsequence of A is called Bitonic if it is first increasing then decreasing.
Input:
The first line contains an integer T denoting the no of test cases. Each test case consist of two lines.
 The first line contains an integer N denoting the size of the array. 
Then in the next line are N space separated values of the array A[].
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#include<string.h>
#include<cmath>
int min(int a,int b){
	if(a>b){return b;}
	return a;
}
int main(){
	std::ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	int t;
	cin>>t;
	int n;
	while(t--){
	    cin>>n;
	    int arr[n];
	    for (int i = 0; i < n; ++i)
	    {
	    	cin>>arr[i];
	    }
	    int DP[n+1];
	    int DP_1[n+1];
	    for (int i = 0; i < n; ++i)
	    {
	    	DP[i]=arr[i];
	    	DP_1[i]=arr[i];

	    }
	    for (int i = 1; i < n; ++i)
	    {
	    	for (int j = 0; j < i; ++j)
	    	{
	    		if (arr[i] > arr[j] && DP[i]<DP[j]+arr[i])
	    		{
	    			 DP[i]=DP[j]+arr[i];
	    		}
	    	}
	    }
	    for (int i = n-2; i >=0 ; i--)
	    {
	    	for (int j = n-1; j>i; j--)
	    	{
	    		if (arr[i] > arr[j] && DP_1[i]<DP_1[j]+arr[i])
	    		{
	    			DP_1[i]=DP_1[j]+arr[i];
	    		}
	    	}
	    }
	    int final[n+1];
	    for (int i = 0; i < n; ++i)
	    {
	    	final[i]=DP[i]+DP_1[i]-arr[i];
	    }
	    int max=final[0];
	   	for (int i = 0; i < n; ++i)
	   	{
	   		if (final[i]>max)
	   		{
	   			max=final[i];
	   		}
	   	}
	   	cout<<max<<endl;
	}
	return 0;

}
