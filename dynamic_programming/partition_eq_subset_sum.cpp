/* 
Problem Statement:-
Given a non-empty array nums containing only positive integers
find if the array can be partitioned into two subsets such that
the sum of elements in both subsets is equal.

Simplified Problem Statement:
This problem is essentially reduces to whether a particular subset of the array, has a sum which is half the sum of the whole array.
This will imply that the other half also has a sum equal to half the array sum.

Naive Approach :
A naive approach is to find all
subsets , and see if at least one subset has a sum equal to half the array sum. We can either include or exclude 
an element, and accordingly we will have 2^n subsets, where n is the size of the array. But this is a very inefficient
approach with a time complexity of O(n*2^n).

Dynamic Programming Approach:
We will see that for a particular index, which sums are possible for any subset of the elemnents till that index.. We will only check for sums till half array sum,
because we know that if a subset has a sum greater than the half array sum, it wont be our answer.
So, we loop through the indexes in an ascending order, and run a nester loop for sums, to compute the possible 
sums till that index, in a topdown manner in our dp array. Our dp array stores 0 or 1, 0 for sum not possible,
and 1 for sum possibel .And in the end we'll check if dp[last index][sum/2] is 0 or 1.
This approach has a complexity of O(n*sum), which is a big improvement over the naive approach.
*/


// Including all libraries
#include<bits/stdc++.h>
using namespace std;

// function to see if array can be paritioned into equal sum subsets.
bool canPartition(vector<int>& nums) {
        
    int n=nums.size();

    //finding array sum.
    int sum=0;
    for(int i=0;i<n;i++)
        sum+=nums[i];

    // If the sum is odd, array can't be partitioned, so return false.
    if(sum&1)
        return false;


    // DP table to store dp[i][w], where i is an index between 0 to n-1, and w is a sum between 0 to sum/2.
    int dp[n+1][sum/2+1];

    // Looping through the indices
    for(int i=0;i<=n;i++)
    {
        // Looping through the sums.
        for(int w=0;w<=sum/2;w++)
        {
            // initializing dp[i][w] as 0.
            dp[i][w]=0;

            // If w is 0, empty subset is always possible.
            if(w==0)
            {
                dp[i][w]=1;
            }

            // If i is 0, it implies that no element is there, so dp[i][w] will be 0. A sum of 0 
            // is possible, but it has been covered in the if statement before.
            else if(i==0)
            {
                dp[i][w]=0;
            }

            else
            {
                // If element is greater than w, then w is not possible, so check if element is smaller than w.
                if(nums[i-1]<=w)
                {
                    // If we include current element, then a sum of w-element should be possible till the previous index.
                    dp[i][w]=dp[i-1][w-nums[i-1]];
                }
                
                // If we exclude current element, then w should be possible till previous index.
                dp[i][w] = dp[i][w] || dp[i-1][w];
            }
        }
    }

    // Returning true if till nth index, sum/2 is possible, else false.
    if(dp[n][sum/2]==1)
        return true;
    return false;
    
}


int main()
{
    // array with sum 12, can be partitioned as {1,2,3} and {6}.
    vector<int> arr1{ 1 , 2 , 3 , 6 };

    // array with sum 14, cannot be partitioned into equal sum subsets.
    vector<int> arr2{ 1 , 2 , 3 , 8 };

    bool ans1=canPartition(arr1);
    bool ans2=canPartition(arr2);

    cout<<"1st array ";
    if(ans1)
        cout<<"can be partitioned into an equal sum subset"<<endl;
    else
        cout<<"cannot be partitioned into an equal sum subset"<<endl;

    cout<<"2nd array ";
    if(ans2)
        cout<<"can be partitioned into an equal sum subset"<<endl;
    else
        cout<<"cannot be partitioned into an equal sum subset"<<endl;

    return 0;




}