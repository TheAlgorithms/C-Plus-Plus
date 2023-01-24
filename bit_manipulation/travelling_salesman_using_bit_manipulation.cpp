/**
 * @file
 * @brief Implementation to
 * [Travelling Salesman problem using bit-masking]
 * (https://www.geeksforgeeks.org/travelling-salesman-problem-set-1/)
 *
 * @details
 * Given the distance/cost(as and adjacency matrix) between each city/node to
 * the other city/node , the problem is to find the shortest possible route that
 * visits every city exactly once and returns to the starting point or we can
 * say the minimum cost of whole tour.
 *
 * Explanation:
 *  INPUT -> You are given with a adjacency matrix A = {} which contains the
 * distance between two cities/node.
 *
 *  OUTPUT ->  Minimum cost of whole tour from starting point
 *
 * Worst Case Time Complexity: O(n^2 * 2^n)
 * Space complexity: O(n)
 * @author [Utkarsh Yadav](https://github.com/Rytnix)
 */
#include <algorithm>  /// for std::min
#include <cassert>    /// for assert
#include <iostream>   /// for IO operations
#include <limits>     /// for limits of integral types
#include <vector>     /// for std::vector

/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */
namespace bit_manipulation {
/**
 * @namespace travellingSalesman_bitmanipulation
 * @brief Functions for the [Travelling Salesman
 * Bitmask](https://www.geeksforgeeks.org/travelling-salesman-problem-set-1/)
 * implementation
 */
namespace travelling_salesman_using_bit_manipulation {
/**
 * @brief The function implements travellingSalesman using bitmanipulation
 * @param dist is the cost to reach between two cities/nodes
 * @param setOfCitites represents the city in bit form.\
 * @param city is taken to track the current city movement.
 * @param n is the no of citys .
 * @param dp vector is used to keep a record of state to avoid the
 * recomputation.
 * @returns minimum cost of traversing whole nodes/cities from starting point
 * back to starting point
 */
std::uint64_t travelling_salesman_using_bit_manipulation(
    std::vector<std::vector<uint32_t>>
        dist,  // dist is the adjacency matrix containing the distance.
               // setOfCities as a bit represent the cities/nodes. Ex: if
               // setOfCities = 2 => 0010(in binary) means representing the
               // city/node B if city/nodes are represented as D->C->B->A.
    std::uint64_t setOfCities,
    std::uint64_t city,  // city is taken to track our current city/node
                         // movement,where we are currently.
    std::uint64_t n,     // n is the no of cities we have.
    std::vector<std::vector<uint32_t>>
        &dp)  // dp is taken to memorize the state to avoid recomputition
{
    // base case;
    if (setOfCities == (1 << n) - 1) {  // we have covered all the cities
        return dist[city][0];  // return the cost from the current city to the
                               // original city.
    }

    if (dp[setOfCities][city] != -1) {
        return dp[setOfCities][city];
    }
    // otherwise try all possible options
    uint64_t ans = 2147483647;
    for (int choice = 0; choice < n; choice++) {
        // check if the city is visited or not.
        if ((setOfCities & (1 << choice)) ==
            0) {  // this means that this perticular city is not visited.
            std::uint64_t subProb =
                dist[city][choice] +
                travelling_salesman_using_bit_manipulation(
                    dist, setOfCities | (1 << choice), choice, n, dp);
            // Here we are doing a recursive call to tsp with the updated set of
            // city/node and choice which tells that where we are currently.
            ans = std::min(ans, subProb);
        }
    }
    dp[setOfCities][city] = ans;
    return ans;
}
}  // namespace travelling_salesman_using_bit_manipulation
}  // namespace bit_manipulation

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // 1st test-case
    std::vector<std::vector<uint32_t>> dist = {
        {0, 20, 42, 35}, {20, 0, 30, 34}, {42, 30, 0, 12}, {35, 34, 12, 0}};
    uint32_t V = dist.size();
    std::vector<std::vector<uint32_t>> dp(1 << V, std::vector<uint32_t>(V, -1));
    assert(bit_manipulation::travelling_salesman_using_bit_manipulation::
               travelling_salesman_using_bit_manipulation(dist, 1, 0, V, dp) ==
           97);
    std::cout << "1st test-case: passed!"
              << "\n";

    // 2nd test-case
    dist = {{0, 5, 10, 15}, {5, 0, 20, 30}, {10, 20, 0, 35}, {15, 30, 35, 0}};
    V = dist.size();
    std::vector<std::vector<uint32_t>> dp1(1 << V,
                                           std::vector<uint32_t>(V, -1));
    assert(bit_manipulation::travelling_salesman_using_bit_manipulation::
               travelling_salesman_using_bit_manipulation(dist, 1, 0, V, dp1) ==
           75);
    std::cout << "2nd test-case: passed!"
              << "\n";
    // 3rd test-case
    dist = {{0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};
    V = dist.size();
    std::vector<std::vector<uint32_t>> dp2(1 << V,
                                           std::vector<uint32_t>(V, -1));
    assert(bit_manipulation::travelling_salesman_using_bit_manipulation::
               travelling_salesman_using_bit_manipulation(dist, 1, 0, V, dp2) ==
           80);

    std::cout << "3rd test-case: passed!"
              << "\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
