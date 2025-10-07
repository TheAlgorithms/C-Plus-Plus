/*
Problem: Count subsets with sum <= target using Meet in the Middle

Example:
Input: arr = [3, 5, 7, 9], target = 12
Output: 5

Explanation:
We split the array into two halves, generate subset sums for each half,
then use binary search to efficiently count valid combinations.

Complexity:
O(2^(N/2) * log(2^(N/2))) ≈ O(N * 2^(N/2))

Technique: Meet in the Middle
*/

#include <bits/stdc++.h>
using namespace std;

// Function to generate all subset sums of a given array range
void generateSubsetSums(vector<int>& arr, vector<long long>& sums, int start,
                        int end, long long curr = 0) {
    if (start > end) {
        sums.push_back(curr);
        return;
    }
    generateSubsetSums(arr, sums, start + 1, end, curr);
    generateSubsetSums(arr, sums, start + 1, end, curr + arr[start]);
}

int main() {
    vector<int> arr = {3, 5, 7, 9};
    int n = arr.size();
    int target = 12;

    vector<long long> left, right;

    // Divide into two halves and generate subset sums
    generateSubsetSums(arr, left, 0, n / 2 - 1);
    generateSubsetSums(arr, right, n / 2, n - 1);

    sort(right.begin(), right.end());
    long long count = 0;

    // For each sum in left, count valid combinations from right
    for (auto s : left) {
        count +=
            upper_bound(right.begin(), right.end(), target - s) - right.begin();
    }

    cout << "Count of subsets with sum <= target: " << count << endl;
    return 0;
}
