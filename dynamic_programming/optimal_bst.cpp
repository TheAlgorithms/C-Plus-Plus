/**
 * @file
 * @brief Implementation of [Optimal Binary Search Tree (OBST)]
 * (https://www.geeksforgeeks.org/dynamic-programming-set-24-optimal-binary-search-tree/)
 *
 * @details
 * Given a sorted array of keys and their corresponding frequencies,
 * the task is to construct a binary search tree with minimum cost.
 * The cost of a BST node is defined as frequency multiplied by depth.
 *
 * ### Algorithm
 * This uses dynamic programming with prefix sum optimization to reduce
 * redundant computation. It builds up the solution for increasing subtree
 * sizes. Time complexity is O(n^3) due to three nested loops.
 *
 * @author Satya
 */

#include <cassert>
#include <climits>
#include <iostream>
#include <vector>

/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */
namespace dynamic_programming {
/**
 * @namespace obst
 * @brief Implementation of Optimal Binary Search Tree
 */
namespace obst {

/**
 * @brief Function to compute the cost of an Optimal Binary Search Tree
 *
 * @param freq Vector of frequencies for sorted keys
 * @return Minimum search cost for OBST
 */
int optimalBST(const std::vector<int>& freq) {
    int n = freq.size();
    if (n == 0)
        return 0;

    // dp[i][j] will hold the minimum cost of OBST that can be built from keys i
    // to j
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

    // prefix sum to quickly compute the total frequency from i to j
    std::vector<int> prefix_sum(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefix_sum[i + 1] = prefix_sum[i] + freq[i];
    }

    // Cost of a single key is its frequency (base case)
    for (int i = 0; i < n; ++i) {
        dp[i][i] = freq[i];
    }

    // Build cost for chains of length 2 to n
    for (int length = 2; length <= n; ++length) {
        for (int i = 0; i <= n - length; ++i) {
            int j = i + length - 1;
            dp[i][j] = INT_MAX;

            int fsum = prefix_sum[j + 1] - prefix_sum[i];

            // Try all keys in [i..j] as root
            for (int r = i; r <= j; ++r) {
                int cost = (r > i ? dp[i][r - 1] : 0) +
                           (r < j ? dp[r + 1][j] : 0) + fsum;
                dp[i][j] = std::min(dp[i][j], cost);
            }
        }
    }

    return dp[0][n - 1];
}
}  // namespace obst
}  // namespace dynamic_programming

/**
 * @brief Function to test the above algorithm
 * @returns void
 */
void test() {
    using dynamic_programming::obst::optimalBST;

    std::vector<int> test1 = {34, 10, 8, 50};
    assert(optimalBST(test1) == 142);

    std::vector<int> test2 = {10, 12};
    assert(optimalBST(test2) == 32);

    std::vector<int> test3 = {10, 12, 20};
    assert(optimalBST(test3) == 82);

    std::vector<int> test4 = {25, 10, 20};
    assert(optimalBST(test4) == 95);

    std::vector<int> test5 = {4, 2, 6, 3};
    assert(optimalBST(test5) == 40);

    std::vector<int> test_single = {42};
    assert(optimalBST(test_single) == 42);

    std::vector<int> test_empty;
    assert(optimalBST(test_empty) == 0);

    std::cout << "All test cases passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on success
 */
int main() {
    test();
    return 0;
}
