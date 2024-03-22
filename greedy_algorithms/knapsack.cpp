/******************************************************************************
 * @file
 * @brief Implementation of the [Knapsack
 * Algorithm](https://en.wikipedia.org/wiki/Knapsack_problem)
 * @details
 * The Knapsack Problem is a classic optimization problem in computer science
 * and combinatorial optimization. It's about selecting a combination of items
 * with the highest value while staying within a limited capacity (weight or
 * volume).
 *
 * ## Implementation
 *
 * ### Step 1
 * It initializes a 1-dimensional array dp to store the maximum profit
 * achievable for different capacities (from 0 to the total capacity).
 *
 * ### Step 2
 * It iterates over each item in the arr vector and for each item, and for each
 * possible capacity value, it checks whether adding the current item would
 * increase the profit. If adding the item increases the profit, it updates the
 * dp array with the new maximum profit achievable for that capacity.
 *
 * ### Step 3
 * Finally, it returns the maximum profit achievable for the given capacity.
 *
 * The time complexity of the knapsack algorithm is typically O(nW), where n is
 * the number of items and W is the capacity of the knapsack. This makes it an
 * efficient solution for moderately sized problem instances.
 *
 * @author [Lajat Manekar](https://github.com/Lazeeez)
 *
 *******************************************************************************/

#include <algorithm>  /// for std::max and std::fill
#include <cassert>    /// for assert
#include <iostream>   /// for I/O operations
#include <vector>     /// for std::vector

/* @namespace greedy_algorithms
 * @brief greedy algorithms is a namespace which is bound to greedy algorithms
 */

namespace greedy_algorithms {

/*@namespace knapsack 
 *@brief knapsack is a namespace which is bound to the knapsack algorithm
 */

namespace knapsack {

// Struct representing an item with profit and weight
struct Item {
    uint64_t profit;  ///< Profit of the item
    uint64_t weight;  ///< Weight of the item
};

/* @brief Function to find the maximum profit using the knapsack algorithm
 * @params capacity: capacity is the upper limit of the algorithm
 * @params arr: arr is the vector which contains the profit and the weight 
 * @params size: size is the size of the vector
 * @returns the max value of the knapsack in uint64_t type
 */
uint64_t knapSack(uint64_t capacity, const std::vector<Item>& arr,
                  uint64_t size) {
    // Making and initializing dp array for dynamic programming
    std::vector<uint64_t> dp(capacity + 1);
    std::fill(dp.begin(), dp.end(), 0);  // Initialize all elements of dp to 0

    // Loop through each item
    for (uint64_t iterator_1 = 1; iterator_1 < size + 1; iterator_1++) {
        // Loop through each capacity value
        for (uint64_t iterator_2 = capacity; iterator_2 > 0; iterator_2--) {
            if (arr[iterator_1 - 1].weight <= iterator_2) {
                // Finding the maximum value by considering including or
                // excluding the current item
                dp[iterator_2] =
                    std::max(dp[iterator_2],
                             dp[iterator_2 - arr[iterator_1 - 1].weight] +
                                 arr[iterator_1 - 1].profit);
            }
        }
    }
    // Returning the maximum value of knapsack
    return dp[capacity];
}
}  // namespace knapsack
}  // namespace greedy_algorithms


// Testcases
/* @breif this function implements the unit testing of the algorithm
 * @params none
 * @returns nothing
 */
static void testcases() {
	std::vector<greedy_algorithms::knapsack::Item> arr {{60, 10}, {100, 20}, {120, 30}};
	uint64_t capacity = 50;
	std::vector<uint64_t>::size_type size = arr.size();
	uint64_t expected_result = 220;
	uint64_t derived_result = greedy_algorithms::knapsack::knapsack(capacity, arr, size);
	assert(expected_result == derived result)

    	std::vector<greedy_algorithms::knapsack::Item> arr{{1, 4}, {2, 5}, {3, 1}};
	uint64_t capacity = 4;
    	std::vector<uint64_t>::size_type size = arr.size();
        uint64_t expected_result = 3;
        uint64_t derived_result = greedy_algorithms::knapsack::knapSack(capacity, arr, size);
        assert(expected_result == derived_result);

        std::vector<greedy_algorithms::knapsack::Item> arr{{1, 4}, {2, 5}, {3, 6}};
        uint64_t capacity = 3;
        std::vector<uint64_t>::size_type size = arr.size();
        uint64_t expected_result = 0;
        uint64_t derived_result = greedy_algorithms::knapsack::knapSack(capacity, arr, size);
        assert(expected_result == derived_result);
}

// Driver code to run test cases
int main() {
    testcases();
    std::cout << "All test cases passed!" << std::endl;
    return 0;
}
