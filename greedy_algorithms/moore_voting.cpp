/**
 * @file
 * @brief [Moore's Voting Algorithm](https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm)
 * implementation
 * @details
 * Moore's Voting Algorithm is used to find the majority element in an array,
 * which is the element that appears more than n/2 times, where n is the size of the array.
 * This algorithm works in O(n) time complexity and O(1) space complexity.
 *
 * @author [Ayush Kumar](https://github.com/SuprHUlk)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace
 * @brief Greedy Algorithms
 */
namespace greedy_algorithms {
/**
 * @namespace
 * @brief Functions for Moore's Voting Algorithm implementation
 */
namespace moore_voting {

/**
 * @brief Function to find the candidate for majority element.
 * This function selects a candidate that could be a majority element.
 * The candidate may or may not be the actual majority element.
 * 
 * @param arr the input array
 * @return the candidate element for the majority
 */
int find_candidate(const std::vector<int>& arr) {
    int candidate = arr[0];
    int count = 1;
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] == candidate) {
            count++;
        } else {
            count--;
        }
        if (count == 0) {
            candidate = arr[i];
            count = 1;
        }
    }
    return candidate;
}

/**
 * @brief Function to check if the candidate is the majority element.
 * After a candidate is selected, this function verifies whether it is 
 * actually the majority element by counting its occurrences.
 * 
 * @param arr the input array
 * @param candidate the candidate to check
 * @return true if the candidate is the majority, false otherwise
 */
bool is_majority(const std::vector<int>& arr, int candidate) {
    int count = 0;
    for (int num : arr) {
        if (num == candidate) {
            count++;
        }
    }
    return count > arr.size() / 2;
}

/**
 * @brief Main function to find the majority element using Moore's Voting Algorithm.
 * This function finds and returns the majority element if it exists, otherwise it returns -1.
 * 
 * @param arr the input array
 * @return the majority element or -1 if no majority element exists
 */
int moore_voting_algorithm(const std::vector<int>& arr) {
    int candidate = find_candidate(arr);
    if (is_majority(arr, candidate)) {
        return candidate;
    } else {
        return -1;  // No majority element found
    }
}
}  // namespace moore_voting
}  // namespace greedy_algorithms

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    std::vector<int> test1 = {2, 2, 1, 1, 1, 2, 2};
    assert(greedy_algorithms::moore_voting::moore_voting_algorithm(test1) == 2);

    std::vector<int> test2 = {3, 3, 4, 2, 4, 4, 2, 4, 4};
    assert(greedy_algorithms::moore_voting::moore_voting_algorithm(test2) == 4);

    std::vector<int> test3 = {3, 1, 3, 3, 2};
    assert(greedy_algorithms::moore_voting::moore_voting_algorithm(test3) == 3);

    std::vector<int> test4 = {1, 2, 3, 4};
    assert(greedy_algorithms::moore_voting::moore_voting_algorithm(test4) == -1);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // run self-test implementations
    return 0;
}
