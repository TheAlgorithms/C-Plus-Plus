/**
 * @file
 * @brief [Minimum coins](https://leetcode.com/problems/coin-change/) change
 * problem is a problem used to find the minimum number of coins required to
 * completely reach a target amount.
 *
 * @details
 * This problem can be solved using 2 methods:
 * 1. Top down approach
 * 2. Bottom up appraoch
 * Top down approach involves a vector with all elements initialised to 0.
 * It is based on optimal substructure and overlapping subproblems.
 * Overall time complexity of coin change problem is O(n*t)
 * For example: example 1:-
 * Coins: {1,7,10}
 * Target:15
 * Therfore minimum number of coins required = 3 of denomination 1,7 and 7.
 * @author [Divyansh Kushwaha](https://github.com/webdesignbydivyansh)
 */

#include <cassert>   // for assert
#include <climits>   // for INT_MAX
#include <iostream>  // for io operations
#include <vector>    // for std::vector

/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithm
 */
namespace dynamic_programming {
/**
 * @namespace mincoins_topdown
 * @brief Functions for [minimum coin
 * exchange](https://leetcode.com/problems/coin-change/) problem
 */
namespace mincoins_topdown {
/**
 * @brief This implementation is for finding minimum number of coins .
 * @param T template-type to use any kind of value
 * @param n amount to be reached
 * @param coins vector of coins
 * @param t deontes the number of coins
 * @param dp initilised to 0
 * @returns minimum number of coins
 */
template <typename T>
int64_t mincoins(const T &n, const std::vector<T> &coins, const int16_t &t,
                 std::vector<T> dp) {
    if (n == 0) {
        return 0;
    }
    if (dp[n] != 0) {
        return dp[n];
    }
    int ans = INT_MAX;  // variable to store min coins
    for (int i = 0; i < t; i++) {
        if (n - coins[i] >= 0) {  // if after subtracting the current
                                  // denomination is it greater than 0 or not
            int sub = mincoins(n - coins[i], coins, t, dp);
            ans = std::min(ans, sub + 1);
        }
    }
    dp[n] = ans;
    return dp[n];  // returns minimum number of coins
}

}  // namespace mincoins_topdown
}  // namespace dynamic_programming

/**
 * @brief Test implementations
 * @returns void
 */
static void test() {
    // example 1: number of coins=3 and minimum coins required=3(7,7,1)
    const int64_t n1 = 15;
    const int8_t t1 = 3, a1 = 0;
    std::cout << "\nTest 1...";
    std::vector<int64_t> arr1{1, 7, 10};
    std::vector<int64_t> dp1(n1 + 1);
    fill(dp1.begin(), dp1.end(), a1);
    assert(dynamic_programming::mincoins_topdown::mincoins(n1, arr1, t1, dp1) ==
           3);
    std::cout << "Passed\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // execute the test
    return 0;
}
