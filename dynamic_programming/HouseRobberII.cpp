/*
=========================================================
🏠 Problem: House Robber II
=========================================================
🔗 LeetCode Link:
https://leetcode.com/problems/house-robber-ii/

📘 Problem Statement:
You are a professional robber planning to rob houses along a street.
Each house has a certain amount of money. All houses are arranged in a circle,
which means the first and last houses are adjacent.
You cannot rob two adjacent houses.

Return the maximum amount of money you can rob tonight without alerting the police.

---------------------------------------------------------
🧠 Approach: Dynamic Programming (Tabulation)
---------------------------------------------------------
- Because the first and last houses are adjacent, we cannot include both.
- So, we compute two scenarios:
  1️⃣ Rob houses from index [0 ... n-2] (skip last)
  2️⃣ Rob houses from index [1 ... n-1] (skip first)
- Take the maximum of both cases.

---------------------------------------------------------
⏱️ Time Complexity:  O(n)
💾 Space Complexity: O(1)
---------------------------------------------------------
📌 Points to Remember:
- For circular arrangements, always consider two linear cases.
- DP base cases are mandatory (at least one).
- Transition: dp[i] = max(dp[i-1], dp[i-2] + nums[i])
---------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int robLinear(vector<int>& nums, int start, int end){
        int n = end - start + 1;  // we don’t always use the full array (so we can't write nums.size())

        // Edge cases:
        if(n == 0) return 0;
        if(n == 1) return nums[start];

        // Initialize the first two states
        int prev2 = nums[start];  // dp[i-2]
        int prev1 = max(nums[start], nums[start + 1]);  // dp[i-1]

        // Iterate over the rest of the houses
        for(int i = start + 2; i <= end; i++){
            int curr = max(prev2 + nums[i], prev1);
            prev2 = prev1;  // move the window forward
            prev1 = curr;
        }

        return prev1;
    }

    int rob(vector<int>& nums){
        int n = nums.size();

        // Edge cases
        if(n == 1) return nums[0];
        if(n == 2) return max(nums[0], nums[1]);

        // Case 1: Rob houses from index 0 to n-2 (exclude last)
        int skipLast = robLinear(nums, 0, n - 2);
        
        // Case 2: Rob houses from index 1 to n-1 (exclude first)
        int skipFirst = robLinear(nums, 1, n - 1);

        // Take maximum of both cases
        return max(skipLast, skipFirst);
    }
};


/*
=========================================================
✅ Example Test (Uncomment to run locally)
=========================================================
int main() {
    Solution sol;
    vector<int> nums = {2, 3, 2};
    cout << "Maximum money robbed: " << sol.rob(nums) << endl;
    return 0;
}
=========================================================

Time complexity = O(n) and Space complexity = O(1) using Dynamic Programming (Tabulation approach)

First & Last houses are adjacent so we can either skip first house or last
Solve for both separately and then return 'maximum' of it

Thumb rule of DP:
    - We always need 'at least one' base case (bcz DP is recurrence based)
    - Always >= 1 base cases

If absolute indices --> i<=end
If relative indices --> i<n (i = 2 ... n-1)
=========================================================
*/
