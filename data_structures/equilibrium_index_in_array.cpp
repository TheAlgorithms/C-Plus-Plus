#include <iostream>
#include <vector>
#include <cassert>

/**
 * @brief Find the equilibrium index of an array.
 * 
 * The equilibrium index of an array is an index such that the sum of
 * elements at lower indexes is equal to the sum of elements at higher indexes.
 */
namespace EquilibriumIndex {
    /**
     * @brief Function to find the equilibrium index of an array.
     * 
     * @param arr The input array of integers.
     * @return int The equilibrium index or -1 if no equilibrium index exists.
     */
    int findEquilibriumIndex(std::vector<int>& arr) {
        int totalSum = 0; // Total sum of the array
        int leftSum = 0;  // Sum of elements to the left of the current index

        // Calculate the total sum of the array
        for (int num : arr)
            totalSum += num;
	// Can also use `int totalSum = std::accumulate(arr.begin(),arr.end());`

        // Iterate through the array to find the equilibrium index
        for (int i = 0; i < arr.size(); ++i) {
            totalSum -= arr[i]; // Subtract the current element from the total sum
            if (leftSum == totalSum) // Check if the sum to the left is equal to the sum to the right
                return i; // Return the current index as the equilibrium index
            leftSum += arr[i]; // Add the current element to the sum to the left
        }

        return -1; // Return -1 if no equilibrium index is found
    }

    /**
     * @brief Function to perform tests.
     * 
     * It runs tests on various test cases using assert statements to verify the correctness of the findEquilibriumIndex function.
     */
    void test() {
        // Test cases
        std::vector<std::pair<std::vector<int>, int>> testCases = {
            {{-7, 1, 5, 2, -4, 3, 0}, 3},   // Expected output: 3
            {{1, 2, 3, 4, 5}, -1},           // Expected output: -1
            {{1, 1, 1, 1, 1}, 2},            // Expected output: 2
            {{2, 4, 6, 8, 10, 3}, -1}        // Expected output: -1
        };

        // Perform tests
        for (auto& testCase : testCases) {
            int result = findEquilibriumIndex(testCase.first);
            assert(result == testCase.second);
        }

        std::cout << "All tests passed successfully!" << std::endl;
    }
}

int main() {
    EquilibriumIndex::test(); // Run the test function
    return 0;
}

