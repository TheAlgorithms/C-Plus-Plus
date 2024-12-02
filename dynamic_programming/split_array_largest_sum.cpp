// NOLINTBEGIN
/**
 * @file split_array_largest_sum.cpp
 * @brief Implementation of the Split Array Largest Sum problem
 * @see https://leetcode.com/problems/split-array-largest-sum/
 * @author Original: ARYA PRATAP SINGH (https://github.com/ARYPROGRAMMER)
 *
 * Given an array of integers and an integer k, split the array into k non-empty
 * contiguous subarrays such that the largest sum of any subarray is minimized.
 * Returns the minimized largest sum of the split.
 *
 * @copyright Original implementation by ARYA PRATAP SINGH, modifications under project's license.
 */

#include <algorithm>
#include <array>
#include <cassert>
#include <climits>
#include <iostream>
#include <vector>

/**
 * @namespace dynamic_programming
 * @brief Contains implementations of dynamic programming algorithms
 */
namespace dynamic_programming {

/**
 * @namespace split_array
 * @brief Implementation of the Split Array Largest Sum problem and related utilities
 */
namespace split_array {

// Constants for maximum array size and maximum number of splits
constexpr std::size_t MAX_ARRAY_SIZE = 1003;
constexpr std::size_t MAX_SPLITS = 53;

/**
 * @class SplitArraySolver
 * @brief Class that implements the solution for the Split Array Largest Sum problem
 */
class SplitArraySolver {  // NOLINT(cppcoreguidelines-special-member-functions)
private:
    // DP table for memoization
    std::array<std::array<int, MAX_SPLITS>, MAX_ARRAY_SIZE> dp_{};  // NOLINT(misc-non-private-member-variables-in-classes)

    /**
     * @brief Recursive helper function to calculate minimum largest sum of split
     * @param i Current index in the array
     * @param j Number of subarrays remaining
     * @param nums Reference to input vector of numbers
     * @return Minimized largest sum for current split configuration
     */
    [[nodiscard]] int solve(const int i, const int j, 
                           const std::vector<int>& nums) noexcept {  // NOLINT(misc-no-recursion)
        if (j < 0) {
            return (i < 0) ? -1 : INT_MAX;
        }
        if (i < 0) {
            return INT_MAX;
        }
        if (dp_[i][j] != -1) {
            return dp_[i][j];
        }

        int result = INT_MAX;
        int current_sum = 0;
        
        for (int k = i; k >= 0; --k) {
            current_sum += nums[k];
            result = std::min(result, 
                            std::max(current_sum, solve(k - 1, j - 1, nums)));
        }
        
        dp_[i][j] = result;
        return result;
    }

public:
    /**
     * @brief Constructor initializes the DP table
     */
    SplitArraySolver() noexcept {
        for (auto& row : dp_) {
            row.fill(-1);
        }
    }

    /**
     * @brief Splits array and finds minimized largest sum
     * @param nums Vector of integers representing the array
     * @param k Number of subarrays to split into
     * @return Minimized largest sum of any subarray after split
     * @throws std::invalid_argument if k is larger than the array size
     */
    [[nodiscard]] int splitArray(const std::vector<int>& nums, const int k) {
        if (k > static_cast<int>(nums.size())) {
            throw std::invalid_argument("k cannot be larger than array size");
        }
        
        return solve(static_cast<int>(nums.size()) - 1, k - 1, nums);
    }
};

}  // namespace split_array
}  // namespace dynamic_programming

/**
 * @brief Test cases for the Split Array Largest Sum implementation
 */
void runTests() {  // NOLINT(misc-use-anonymous-namespace)
    dynamic_programming::split_array::SplitArraySolver solver;

    // Test case 1: Basic case
    {
        const std::vector<int> nums{7, 2, 5, 10, 8};
        assert(solver.splitArray(nums, 2) == 18);
    }

    // Test case 2: Equal split
    {
        const std::vector<int> nums{1, 2, 3, 4, 5};
        assert(solver.splitArray(nums, 2) == 9);
    }

    // Test case 3: Larger array
    {
        const std::vector<int> nums{7, 2, 5, 10, 8, 1, 2, 3, 4, 5};
        assert(solver.splitArray(nums, 3) == 18);
    }

    // Test case 4: Edge case - k equals array size
    {
        const std::vector<int> nums{1, 2, 3};
        assert(solver.splitArray(nums, 3) == 3);
    }

    // Test case 5: Exception case
    {
        const std::vector<int> nums{1, 2};
        try {
            [[maybe_unused]] auto result = solver.splitArray(nums, 3);
            assert(false);  // Should not reach here
        } catch (const std::invalid_argument&) {
            // Expected exception
        }
    }

    std::cout << "All tests passed!\n";
}

/**
 * @brief Main function runs the test suite
 * @return 0 on successful execution
 */
int main() {
    runTests();
    return 0;
}
// NOLINTEND
