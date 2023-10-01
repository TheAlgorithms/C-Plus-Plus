#include <iostream>
#include <vector>
#include <cassert> // Include the cassert library for testing

using namespace std;

class Solution {
public:
    // Recursive function to find the maximum profit
    int solve(int i, int allow, vector<int>& prices, vector<vector<int>>& dp) {
        if (i >= prices.size()) {
            return 0; // Base case: If we've reached the end of the prices array, return 0.
        }

        if (dp[i][allow] != -1) {
            return dp[i][allow]; // If the result is already computed, return it to avoid re-computation.
        }

        int take = 0, nottake = 0;

        if (allow == 1) {
            // If we're allowed to buy a stock (allow = 1), we can either take it or skip it.
            take = -prices[i] + solve(i + 1, 0, prices, dp); // Take the stock, deduct its price, and move to the next day without allowing buying.
            nottake = solve(i + 1, allow, prices, dp); // Skip the stock and move to the next day with the same buying allowance.
        } else {
            // If we're not allowed to buy a stock (allow = 0), we can only skip it.
            take = prices[i] + solve(i + 1, 1, prices, dp); // Change the allowance to 1 and move to the next day.
            nottake = solve(i + 1, allow, prices, dp); // Stay in the same state (not buying) and move to the next day.
        }

        // Store the result in the dynamic programming table and return it.
        return dp[i][allow] = max(take, nottake);
    }

    // Main function to find the maximum profit
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        // Create a dynamic programming table dp[i][j] where i represents the day and j represents the buying allowance.
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));

        // Loop through the prices array from right to left (backward).
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < 2; j++) {
                int take = 0, nottake = 0;

                if (j == 1) {
                    // If we're allowed to buy (j = 1), we can either take the stock or skip it.
                    take = -prices[i] + dp[i + 1][0]; // Take the stock, deduct its price, and move to the next day without allowing buying.
                    nottake = dp[i + 1][j]; // Skip the stock and move to the next day with the same buying allowance.
                } else {
                    // If we're not allowed to buy (j = 0), we can only skip the stock.
                    take = prices[i] + dp[i + 1][1]; // Change the allowance to 1 (allow buying) and move to the next day.
                    nottake = dp[i + 1][j]; // Stay in the same state (not buying) and move to the next day.
                }

                // Update the dp table with the maximum of take and nottake.
                dp[i][j] = max(take, nottake);
            }
        }

        // The maximum profit is stored in dp[0][1], where we have no buying allowance.
        return dp[0][1];
    }
};

// Test function to run the algorithm on random test data
void test() {
    Solution solution;

    // Test Case 1
    vector<int> prices1 = {7, 1, 5, 3, 6, 4};
    int expected1 = 5;
    int result1 = solution.maxProfit(prices1);
    assert(result1 == expected1);

    // Test Case 2
    vector<int> prices2 = {7, 6, 4, 3, 1};
    int expected2 = 0;
    int result2 = solution.maxProfit(prices2);
    assert(result2 == expected2);

    // Test Case 3 (Empty input)
    vector<int> prices3;
    int expected3 = 0;
    int result3 = solution.maxProfit(prices3);
    assert(result3 == expected3);

    // Add more test cases as needed
}

int main() {
    test(); 
    return 0;
}
