#include <iostream>
#include <vector>
#include <cassert> // Include the cassert library for testing

using namespace std;

class Solution {
public:
    // Function to calculate the maximum profit with at most 'k' transactions
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        
        // Create a 3D dynamic programming table dp[i][j][cap], where:
        // - i represents the day (0 to n)
        // - j represents the buying state (0: not holding, 1: holding)
        // - cap represents the number of transactions left (0 to k)
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(k + 1, 0)));

        // Initialize the base case for the last day (no transactions left).
        for (int j = 0; j < 2; j++) {
            for (int cap = 0; cap <= k; cap++) {
                dp[n][j][cap] = 0;
            }
        }

        // Loop through the prices array from right to left (backward) and compute the maximum profit using dynamic programming.
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < 2; j++) {
                for (int cap = 1; cap <= k; cap++) {
                    int profit = 0;

                    if (j) {
                        // If we're in a buying state (buy = 1), calculate profit for buying or skipping.
                        profit = max(-prices[i] + dp[i + 1][0][cap], dp[i + 1][1][cap]);
                    } else {
                        // If we're in a selling state (buy = 0), calculate profit for selling or skipping.
                        profit = max(prices[i] + dp[i + 1][1][cap - 1], dp[i + 1][0][cap]);
                    }

                    // Update the dp table with the maximum profit.
                    dp[i][j][cap] = profit;
                }
            }
        }
        
        // The maximum profit is stored in dp[0][1][k], where we've completed 'k' transactions and in a selling state.
        return dp[0][1][k];
    }
};

// Test function to run the algorithm on random test data
void test() {
    Solution solution;

    // Test Case 1
    vector<int> prices1 = {2, 4, 1};
    int k1 = 2;
    int expected1 = 2; // Buy on day 1 (2), sell on day 2 (4), and buy on day 3 (1).
    int result1 = solution.maxProfit(k1, prices1);
    assert(result1 == expected1);

    // Test Case 2
    vector<int> prices2 = {3, 2, 6, 5, 0, 3};
    int k2 = 2;
    int expected2 = 7; // Buy on day 2 (2), sell on day 4 (6), buy on day 5 (0), and sell on day 6 (3).
    int result2 = solution.maxProfit(k2, prices2);
    assert(result2 == expected2);

    // Test Case 3 (Empty input)
    vector<int> prices3;
    int k3 = 2;
    int expected3 = 0; // No transactions can be made with an empty input.
    int result3 = solution.maxProfit(k3, prices3);
    assert(result3 == expected3);

    // Add more test cases as needed

    cout << "All tests passed!" << endl;
}

int main() {
    test(); // Run the test function

    return 0;
}
