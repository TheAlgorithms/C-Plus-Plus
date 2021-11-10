/******************************************************************************
 * @file
 * @brief Implementation of the [Partition
 * Problem](https://en.wikipedia.org/wiki/Partition_problem )
 * @details
 * The partition problem, or number partitioning, is the task of deciding
 * whether a given multiset S of positive integers can be partitioned into two
 * subsets S1 and S2 such that the sum of the numbers in S1 equals the sum of
 * the numbers in S2. Although the partition problem is NP-complete, there is a
 * pseudo-polynomial time dynamic programming solution, and there are heuristics
 * that solve the problem in many instances, either optimally or approximately.
 * For this reason, it has been called "the easiest hard problem".
 *
 * The worst case time complexity of Jarvis’s Algorithm is O(n^2). Using
 * Graham’s scan algorithm, we can find Convex Hull in O(nLogn) time.
 *
 * ### Implementation
 *
 * Step 1
 * Calculate sum of the array. If sum is odd, there can not be two subsets with
 * equal sum, so return false.
 *
 * Step 2
 * If sum of array elements is even, calculate sum/2 and find a subset of array
 * with sum equal to sum/2.
 *
 * @author [Lajat Manekar](https://github.com/Lazeeez)
 *
 *******************************************************************************/
#include <cassert>   /// for assert
#include <iostream>  /// for IO Operations
#include <numeric>   /// for std::accumulate
#include <vector>    /// for std::vector

/******************************************************************************
 * @namespace dp
 * @brief Dynamic programming algorithms
 *******************************************************************************/
namespace dp {

/******************************************************************************
 * @namespace partitionProblem
 * @brief Partition problem algorithm
 *******************************************************************************/
namespace partitionProblem {

/******************************************************************************
 * @brief Returns true if arr can be partitioned in two subsets of equal sum,
 * otherwise false
 * @param arr vector containing elements
 * @param size Size of the vector.
 * @returns @param bool whether the vector can be partitioned or not.
 *******************************************************************************/
bool findPartiion(const std::vector<uint64_t> &arr, uint64_t size) {
    uint64_t sum = std::accumulate(arr.begin(), arr.end(),
                                   0);  // Calculate sum of all elements

    if (sum % 2 != 0) {
        return false;  // if sum is odd, it cannot be divided into two equal sum
    }
    std::vector<bool> part;
    // bool part[sum / 2 + 1];

    // Initialize the part array as 0
    for (uint64_t it = 0; it <= sum / 2; ++it) {
        part.push_back(false);
    }

    // Fill the partition table in bottom up manner
    for (uint64_t it = 0; it < size; ++it) {
        // The element to be included in the sum cannot be greater than the sum
        for (uint64_t it2 = sum / 2; it2 >= arr[it];
             --it2) {  // Check if sum - arr[i]
            // ould be formed from a subset using elements before index i
            if (part[it2 - arr[it]] == 1 || it2 == arr[it]) {
                part[it2] = true;
            }
        }
    }
    return part[sum / 2];
}
}  // namespace partitionProblem
}  // namespace dp

/*******************************************************************************
 * @brief Self-test implementations
 * @returns void
 *******************************************************************************/
static void test() {
    std::vector<uint64_t> arr = {{1, 3, 3, 2, 3, 2}};
    uint64_t n = arr.size();
    bool expected_result = true;
    bool derived_result = dp::partitionProblem::findPartiion(arr, n);
    std::cout << "1st test: ";
    assert(expected_result == derived_result);
    std::cout << "Passed!" << std::endl;
}

/*******************************************************************************
 * @brief Main function
 * @returns 0 on exit
 *******************************************************************************/
int main() {
    test();  // run self-test implementations
    return 0;
}
