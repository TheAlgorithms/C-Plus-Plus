
/******************************************************************************
 * @details
Given an integer array nums, return the length of the longest strictly
increasing subsequence.

The longest increasing subsequence is described as a subsequence of an array
where: All elements of the subsequence are in increasing order. This subsequence
itself is of the longest length possible.

For solving this problem we have Three Approaches :-

Approach 1 :- Using Brute Force
The first approach that came to your mind is the Brute Force approach where we
generate all subsequences and then manually filter the subsequences whose
elements come in increasing order and then return the longest such subsequence.
Time Complexity :- O(2^n)
It's time complexity is exponential. Therefore we will try some other
approaches.

Approach 2 :- Using Dynamic Programming
To generate all subsequences we will use recursion and in the recursive logic we
will figure out a way to solve this problem. Recursive Logic to solve this
problem:-
1. We only consider the element in the subsequence if the element is grater then
the last element present in the subsequence
2. When we consider the element we will increase the length of subsequence by 1
Time Complexity: O(N*N)
Space Complexity: O(N*N) + O(N)

This approach is better then the previous Brute Force approach so, we can
consider this approach.

But when the Constraints for the problem is very larger then this approach fails

Approach 3 :- Using Binary Search
Other approaches use additional space to create a new subsequence Array.
Instead, this solution uses the existing nums Array to build the subsequence
array. We can do this because the length of the subsequence array will never be
longer than the current index.

Time complexity: O(n∗log(n))
Space complexity: O(1)

This approach consider Most optimal Approach for solving this problem

 *******************************************************************************/

#include <cassert>  /// for std::assert
#include <iostream> /// for IO operations
#include <vector>   /// for std::vector

/**
 * @brief Function to find the length of Longest Increasing Subsequence (LIS)
 * using Binary Search
 * @param nums Input integer array
 * @return Length of the longest increasing subsequence
 */
int Longest_Increasing_Subsequence_using_binary_search(std::vector<int>& nums){
    
    if(nums.size() == 0) return 0;

    std::vector<int> ans;
    ans.push_back(nums[0]);
    for(int i=1;i<nums.size();i++){
        if(nums[i] > ans.back()){
            ans.push_back(nums[i]);
        }
        else{
            int idx = lower_bound(ans.begin(),ans.end(),nums[i]) -ans.begin();
            ans[idx] = nums[i];
        }
    }
    return ans.size();
}

/**
 * @brief test implementations
 * @returns void
 */
static void tests() {
    std::vector<int> arr = {10, 9, 2, 5, 3, 7, 101, 18};
    assert(Longest_Increasing_Subsequence_using_binary_search(arr) == 4);

    std::vector<int> arr2 = {0, 1, 0, 3, 2, 3};
    assert(Longest_Increasing_Subsequence_using_binary_search(arr2) == 4);

    std::vector<int> arr3 = {7, 7, 7, 7, 7, 7, 7};
    assert(Longest_Increasing_Subsequence_using_binary_search(arr3) == 1);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();
    return 0;
}
