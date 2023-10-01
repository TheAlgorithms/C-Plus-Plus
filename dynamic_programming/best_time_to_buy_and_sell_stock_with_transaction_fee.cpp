#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    // Function to calculate the maximum profit with a transaction fee
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        
        // Create a 2D dynamic programming table dp[i][j], where:
        // - i represents the day (0 to n)
        // - j represents the holding state (0: not holding, 1: holding)
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));

        // Initialize the base case for the last day (no transactions left).
        dp[n][0] = 0;
        dp[n][1] = 0;

        int profit = 0;

        // Loop through the prices array from right to left (backward).
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < 2; j++) {
                if (j) {
                    // If we're in a holding state (hold = 1), calculate profit for holding or selling.
                    profit = max(-prices[i] + dp[i + 1][0], dp[i + 1][1]);
                } else {
                    // If we're in a not holding state (hold = 0), calculate profit for not holding or buying.
                    profit = max(prices[i] - fee + dp[i + 1][1], dp[i + 1][0]);
                }

                // Update the dp table with the maximum profit.
                dp[i][j] = profit;
            }
        }

        // The maximum profit is stored in dp[0][1], where we're in a not holding state on the first day.
        return dp[0][1];
    }
};void test() {
    Solution solution;

    // Test Case 1
    vector<int> prices1 = {1, 3, 2, 8, 4, 9};
    int fee1 = 2;
    int expected1 = 8; // Buy on day 1 (1), sell on day 3 (3), buy on day 4 (4), and sell on day 6 (9).
    int result1 = solution.maxProfit(prices1, fee1);
    assert(result1 == expected1);

    // Test Case 2
    vector<int> prices2 = {7, 1, 5, 3, 6, 4};
    int fee2 = 1;
    int expected2 = 5; // Buy on day 2 (1), sell on day 3 (5), buy on day 4 (3), and sell on day 5 (6).
    int result2 = solution.maxProfit(prices2, fee2);
    assert(result2 == expected2);

    // Test Case 3 (Empty input)
    vector<int> prices3;
    int fee3 = 2;
    int expected3 = 0; // No transactions can be made with an empty input.
    int result3 = solution.maxProfit(prices3, fee3);
    assert(result3 == expected3);

    // Add more test cases as needed

    cout << "All tests passed!" << endl;
}

int main() {
    test(); // Run the test function

    return 0;
}
