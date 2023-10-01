#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    // Recursive function to find the maximum profit
    int solve(int i, int buy, int k, vector<int>& prices, vector<vector<vector<int>>>& dp) {
        // Base case: If we've exhausted the number of transactions (k) or reached the end of prices array (i),
        // return 0 as there are no more transactions or prices to consider.
        if (k == 0 || i == prices.size()) {
            return 0;
        }

        // If the result is already computed, return it to avoid re-computation.
        if (dp[i][buy][k] != -1) {
            return dp[i][buy][k];
        }

        int profit = 0;

        if (buy) {
            // If we're in a buying state (buy = 1), we can either buy a stock (decrease profit) or skip it.
            profit = max(-prices[i] + solve(i + 1, 0, k, prices, dp), solve(i + 1, 1, k, prices, dp));
        } else {
            // If we're in a selling state (buy = 0), we can either sell a stock (increase profit) or skip it.
            profit = max(prices[i] + solve(i + 1, 1, k - 1, prices, dp), solve(i + 1, 0, k, prices, dp));
        }

        // Store the result in the dynamic programming table and return it.
        return dp[i][buy][k] = profit;
    }

    // Main function to find the maximum profit
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        // Create a dynamic programming table dp[i][j][k], where i represents the day, j represents the buying state,
        // and k represents the number of transactions left.
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, -1)));

        // Initialize the base case for the last day (no transactions left).
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 3; k++) {
                dp[n][j][k] = 0;
            }
        }

        // Loop through the prices array from right to left (backward) and compute the maximum profit using dynamic programming.
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < 2; j++) {
                for (int k = 1; k < 3; k++) {
                    int profit = 0;

                    if (j) {
                        // If we're in a buying state (buy = 1), calculate profit for buying or skipping.
                        profit = max(-prices[i] + dp[i + 1][0][k], dp[i + 1][1][k]);
                    } else {
                        // If we're in a selling state (buy = 0), calculate profit for selling or skipping.
                        profit = max(prices[i] + dp[i + 1][1][k - 1], dp[i + 1][0][k]);
                    }

                    // Update the dp table with the maximum profit.
                    dp[i][j][k] = profit;
                }
            }
        }

        // The maximum profit is stored in dp[0][1][2], where we've completed 2 transactions and in a selling state.
        return dp[0][1][2];
    }
};
void test() {
    Solution solution;

    // Test Case 1
    vector<int> prices1 = {3, 2, 6, 5, 0, 3};
    int expected1 = 7; // Buy on day 2 (2), sell on day 4 (6), buy on day 5 (0), and sell on day 6 (3).
    int result1 = solution.maxProfit(prices1);
    assert(result1 == expected1);

    // Test Case 2
    vector<int> prices2 = {1, 2, 3, 4, 5};
    int expected2 = 4; // Buy on day 1 (1) and sell on day 5 (5).
    int result2 = solution.maxProfit(prices2);
    assert(result2 == expected2);

    // Test Case 3 (Empty input)
    vector<int> prices3;
    int expected3 = 0; // No transactions can be made with an empty input.
    int result3 = solution.maxProfit(prices3);
    assert(result3 == expected3);

    // Add more test cases as needed

    cout << "All tests passed!" << endl;
}

int main() {
    test(); // Run the test function

    return 0;
}
