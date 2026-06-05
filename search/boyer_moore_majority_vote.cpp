/**
 * @file
 * @brief Implementation of the [Boyer-Moore Majority Vote Algorithm](https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm).
 * @details The algorithm finds the majority element (an element that appears more than n/2 times) in O(n) time and O(1) space complexity.
 */

#include <cassert>
#include <iostream>
#include <vector>

/**
 * @namespace search
 * @brief Search algorithms
 */
namespace search {
/**
 * @namespace boyer_moore_majority
 * @brief Functions for Boyer-Moore Majority Vote algorithm
 */
namespace boyer_moore_majority {

/**
 * @brief Finds the majority element in a given vector.
 * @param arr vector to search through
 * @return the majority element
 */
int find_majority(const std::vector<int>& arr) {
    // TODO: Implement the target logic here
    int candidate = 0;
    int count = 0;

    for (int num : arr) {
        if (count == 0) {
            candidate = num;
        }
        count += (num == candidate) ? 1 : -1;
    }

    // Optional: The repository usually appreciates a verification step 
    // to ensure the candidate actually appears more than n/2 times, 
    // in case a majority element doesn't exist.
    
    return candidate;
}

}  // namespace boyer_moore_majority
}  // namespace search

/**
 * @brief Self-test implementations
 * @return void
 */
static void test() {
    // Test case 1: Standard majority element
    std::vector<int> test_1 = {2, 2, 1, 1, 1, 2, 2};
    assert(search::boyer_moore_majority::find_majority(test_1) == 2);

    // Test case 2: All identical elements
    std::vector<int> test_2 = {5, 5, 5, 5};
    assert(search::boyer_moore_majority::find_majority(test_2) == 5);

    // Test case 3: Majority element at the end
    std::vector<int> test_3 = {1, 2, 3, 4, 4, 4, 4, 4, 4};
    assert(search::boyer_moore_majority::find_majority(test_3) == 4);

    std::cout << "All tests passed successfully!" << std::endl;
}

/**
 * @brief Main function
 * @return 0 on success
 */
int main() {
    test();  // run self-test implementations
    return 0;
}