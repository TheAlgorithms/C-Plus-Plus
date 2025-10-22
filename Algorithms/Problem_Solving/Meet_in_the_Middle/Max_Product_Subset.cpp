
/*
---------------------------------------------------------
Algorithm: Meet in the Middle — Maximum Product Subset
---------------------------------------------------------
Problem:
Given an array of integers, find the **maximum product** that can
be obtained from any subset of the array (non-empty subset).

Naive approach:
- Try all 2^N subsets → O(2^N)
- For N > 30, becomes computationally infeasible

Optimization using Meet in the Middle:
- Split array into two halves
- Generate all subset products of both halves
- Combine them efficiently to find the global maximum

Key idea:
We only need to store all subset products and combine them
systematically (similar to subset-sum but using product operation).

---------------------------------------------------------
Example:
Input:  arr = [2, -3, 4, -1]
Output: 24
Explanation: subset [2, -3, 4] → 2 * (-3) * 4 = -24,
but subset [2, 4, -1, -3] → product = 24 (maximum)
---------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------------
// Helper function: generate all subset products
// -----------------------------------------------------
void generateSubsetProducts(const vector<int>& nums, vector<long long>& subsetProducts) {
    int n = nums.size();
    int totalSubsets = 1 << n; // 2^n possible subsets

    for (int mask = 1; mask < totalSubsets; ++mask) { // start from 1 to skip empty subset
        long long product = 1;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i))
                product *= nums[i];
        }
        subsetProducts.push_back(product);
    }
}

// -----------------------------------------------------
// Function to compute maximum subset product
// -----------------------------------------------------
long long maxSubsetProduct(vector<int>& arr) {
    int n = arr.size();
    int mid = n / 2;

    // Split into two halves
    vector<int> leftArr(arr.begin(), arr.begin() + mid);
    vector<int> rightArr(arr.begin() + mid, arr.end());

    // Generate subset products
    vector<long long> leftProducts, rightProducts;
    generateSubsetProducts(leftArr, leftProducts);
    generateSubsetProducts(rightArr, rightProducts);

    // Sort for efficient pairing (not strictly needed here, but useful for extensions)
    sort(leftProducts.begin(), leftProducts.end());
    sort(rightProducts.begin(), rightProducts.end());

    long long maxProduct = LLONG_MIN;

    // Combine both halves
    for (auto leftProd : leftProducts) {
        for (auto rightProd : rightProducts) {
            maxProduct = max(maxProduct, leftProd * rightProd);
        }
    }

    // Also consider individual subset products (in case best subset is within one half)
    for (auto val : leftProducts) maxProduct = max(maxProduct, val);
    for (auto val : rightProducts) maxProduct = max(maxProduct, val);

    return maxProduct;
}

// -----------------------------------------------------
// Driver Code
// -----------------------------------------------------
int main() {
    vector<int> arr = {2, -3, 4, -1};

    cout << "Array: ";
    for (int num : arr) cout << num << " ";
    cout << "\n";

    long long result = maxSubsetProduct(arr);
    cout << "Maximum product among all subsets = " << result << endl;

    return 0;
}

/*
---------------------------------------------------------
🧠 Explanation:

arr = [2, -3, 4, -1]
Left half = [2, -3]
Right half = [4, -1]

Left products = {2, -3, -6}
Right products = {4, -1, -4}

Now combine:
(2*4)=8, (2*-1)=-2, (2*-4)=-8,
(-3*4)=-12, (-3*-1)=3, (-3*-4)=12,
(-6*4)=-24, (-6*-1)=6, (-6*-4)=24 ← ✅ max

Hence, Maximum = 24
---------------------------------------------------------
*/
