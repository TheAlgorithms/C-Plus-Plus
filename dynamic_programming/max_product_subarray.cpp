/* 
Problem Statement:-
Given an integer array nums ( can have negative integers ), find a contiguous non-empty subarray 
within the array that has the largest product, and return the product.

Naive Approach :
A naive approach is to find all subarrays , and see if which one has the largest product.
Total number of subarrays are n(n+1)/2, where n is size of array. So complexity will be
O(n^3). We can optimize this to O(n^2), by seeing the product while finding the subarrays,
but we can do better.


Dynamic Programming Approach:
We'll take a top down approach, and the largest and smallest product possible till an
index in a dp array. Dp[i][0] will indicate largest product till index i, and dp[i][1]
will indicate smallest product till index i.
At each index, the possible products are, element*(largest till i-1), or element*(smallest 
till i-1), or just the element itself, if we assume that the subarrays starts from this index.
We'll find these products, and take max for dp[i][0], and min for dp[i][1]. 

Note:- element*(smallest till i-1) can be a candidate for largest, as it may be possible that
smallest till i-1 is negative and element is also negative, which will make the sum positive.
Similarly, element*(largest till i-1) can be a candidate for min.

Complexity :- O(n).
*/

// Including all libraries
#include<bits/stdc++.h>
using namespace std;

// function to find max product subarray.
int maxProduct(vector<int>& nums) {

    int n=nums.size();
    
    // dp array
    int dp[n][2];

    // max till index 0 is 1st element.
    dp[0][0]=nums[0];
    // min till index 0 is 1st element.
    dp[0][1]=nums[0];

    // initialize ans as 1st element.
    int ans=nums[0];
    
    for(int i=1;i<n;i++)
    {
        // element*(largest till i-1)
        int a=dp[i-1][0]*nums[i];

        // element*(smallest till i-1)
        int b=dp[i-1][1]*nums[i];
        // Element itself indicating start of subarray
        int c=nums[i];

        // Finding largest product of subarray ending at i.
        dp[i][0]=max(a,max(b,c));
        // Finding smallest product of subarray ending at i.
        dp[i][1]=min(a,min(b,c));
        
        // Finding max product
        ans=max(ans,dp[i][0]);
    }

    // returning answer
    return ans;
}



int main()
{
    // array with sum 12, can be partitioned as {1,2,3} and {6}.
    vector<int> arr{ 1 , 2 , 3 , -6 };


    int ans=maxProduct(arr);

    cout<<"Max product of subarray in array is "<<ans<<endl;
    
    return 0;




}