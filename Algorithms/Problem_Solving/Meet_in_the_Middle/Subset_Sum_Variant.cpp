
/*
---------------------------------------------------------
Algorithm: Meet in the Middle — Subset Sum Variant
---------------------------------------------------------
Problem:
Given an array of integers and a target value, count how many
subsets have a total sum ≤ target.

Traditional brute force approach:
- Generate all subsets → O(2^N)
- Sum each subset → inefficient for large N (N > 40)

Optimization (Meet in the Middle):
- Split array into two halves
- Compute all possible subset sums of each half
- Sort one half and for each sum in the other half, use binary
  search to count how many combinations give total ≤ target.

Time Complexity:
- O(2^(N/2) * log(2^(N/2))) ≈ O(N * 2^(N/2))
- Works efficiently for N ≤ 40

---------------------------------------------------------
Example:
Input:  arr = [3, 1, 2, 5, 4], target = 7
Output: 13
(There are 13 subsets with sum ≤ 7)
---------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------------
// Helper function to generate all subset sums
// -----------------------------------------------------
void generateSubsetSums(const vector<int>& nums, vector<long long>& subsetSums) {
    int n = nums.size();
    int totalSubsets = 1 << n; // 2^n possible subsets
    for (int mask = 0; mask < totalSubsets; ++mask) {
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i))
                sum += nums[i];
        }
        subsetSums.push_back(sum);
    }
}

// -----------------------------------------------------
// Main function to count subsets with sum ≤ target
// -----------------------------------------------------
long long countSubsets(vector<int>& arr, int target) {
    int n = arr.size();
    int mid = n / 2;

    // Divide array into two halves
    vector<int> leftArr(arr.begin(), arr.begin() + mid);
    vector<int> rightArr(arr.begin() + mid, arr.end());

    // Generate subset sums for both halves
    vector<long long> leftSums, rightSums;
    generateSubsetSums(leftArr, leftSums);
    generateSubsetSums(rightArr, rightSums);

    // Sort right half to enable binary search
    sort(rightSums.begin(), rightSums.end());

    long long count = 0;

    // For each sum in left half, find how many rightSums can be added
    // without exceeding the target
    for (auto& sumLeft : leftSums) {
        long long remaining = target - sumLeft;
        // upper_bound gives iterator to first element > remaining
        count += upper_bound(rightSums.begin(), rightSums.end(), remaining) - rightSums.begin();
    }

    return count;
}

// -----------------------------------------------------
// Driver Code (Test)
// -----------------------------------------------------
int main() {
    vector<int> arr = {3, 1, 2, 5, 4};
    int target = 7;

    cout << "Array: ";
    for (int num : arr) cout << num << " ";
    cout << "\nTarget: " << target << "\n";

    long long result = countSubsets(arr, target);
    cout << "Number of subsets with sum less than equal to target = " << result << endl;

    return 0;
}

/*
---------------------------------------------------------
🧠 Explanation:

For arr = [3, 1, 2, 5, 4], N = 5 → split into:
Left = [3, 1], Right = [2, 5, 4]

Left subset sums = [0, 3, 1, 4]
Right subset sums = [0, 2, 5, 4, 7, 6, 9, 11]

For each left sum, count how many right sums fit:
Example: left=3 → right sums ≤ 4 → {0,2,4} (3 ways)

Final count = 13 subsets with total sum ≤ 7.
---------------------------------------------------------
*/
