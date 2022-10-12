#include <iostream>
#include <vector>
using namespace std;


bool isSubsetSum(vector<int> arr, int sum)
{
    int n = arr.size();

    vector<bool> dp(sum + 1); 

    for (int i = 0; i < n; i++) // i represents index in dp matrix
    {
        vector<bool> temp(sum + 1);
        for (int j = 0; j <= sum; j++) // j represents sum in dp matrix
        {
            if (j == 0)
            {
                temp[j] = true; // or dp[i][0], they're same
            }
            else if (i == 0)
            {
                temp[j] = arr[i] == j;
            }
            else
            {
                bool pick = (arr[i] <= j) ? dp[j - arr[i]] : false;

                bool non_pick = dp[j];

                temp[j] = pick or non_pick;
            }
        }
        dp = temp;
    }
    return dp[sum];
}

bool canPartition(vector<int> &nums)
{
    int n = nums.size();
    int sum = 0;

    // collecting accumulative sum of the array
    for (const auto &i : nums)
        sum += i;

    // if the acc sum is odd, there's no way we can divide the array into two equal partitions
    if (sum % 2 == 1)
        return false;

    // but if the acc sum is even,
    // we just have to find if the array contains a subset of sum, sum/2, so that, it'll be proven that the other sum/2 is also present in the array.
    // which divides it in two equal partitions

    return isSubsetSum(nums, sum / 2);
}