#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <ctime>
#include <cstdlib>

/**
 * @brief Solves the 0-1 Knapsack problem using Dynamic Programming.
 *
 * This function calculates the maximum value that can be obtained from a given set of items
 * with weights and values, while not exceeding a given weight capacity.
 *
 * @tparam n Size of the weight and value arrays.
 * @param capacity Capacity of the carrying bag (knapsack).
 * @param weight Array representing the weight of items.
 * @param value Array representing the value of items.
 * @return Maximum value obtainable with the given capacity.
 */


// Function to solve the 0-1 Knapsack problem using Dynamic Programming
int knapSack(int capacity, std::vector<int>& weights, std::vector<int>& values) {
    int n = weights.size();
    
    // Create a 1D DP array to store the state of the maximum possible return
    // for a given weight capacity.
    std::vector<int> dp(capacity + 1, 0);
    
    // Fill the DP array
    for (int i = 0; i < n; i++) {
        for (int w = capacity; w >= weights[i]; w--) {
            // Choose the maximum value between including and excluding the current item
            dp[w] = std::max(dp[w], dp[w - weights[i]] + values[i]);
        }
    }
    
    // The maximum value will be in the last cell of the DP array
    return dp[capacity];
}

// Function to test the knapSack() function
void test() {
    // Test Case 1
    std::vector<int> weights1 = {10, 20, 30};
    std::vector<int> values1 = {60, 100, 120};
    int weightCapacity1 = 50;
    int expected1 = 220;
    int result1 = knapSack(weightCapacity1, weights1, values1);
    assert(result1 == expected1);

    // Test Case 2
    std::vector<int> weights2 = {5, 10, 15};
    std::vector<int> values2 = {10, 30, 20};
    int weightCapacity2 = 30;
    int expected2 = 60;
    int result2 = knapSack(weightCapacity2, weights2, values2);
    assert(result2 == expected2);

    // Add more test cases here as needed

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    // Seed the random number generator
    srand(static_cast<unsigned>(time(0)));
    
    // Run the tests
    test();
    
    return 0;
}
