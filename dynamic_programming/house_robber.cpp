/**
 * @file
 * @brief Implementation of [House Robber Problem] algorithm
 * @details
 * Solution of House robber problem uses a dynamic programming concept that
 * works in \f$O(n)\f$ time and works in \f$O(1)\f$ space.
 */

#include <cassert>   /// for assert
#include <iostream>  /// for io operations
#include <vector>    /// for std::vector
#include <climits>   /// for std::max
/**
 * @namespace dynamic_programming
 * @brief House robber algorithm
 */
namespace dynamic_programming {
/**
 * @namespace house_robber
 * @brief Functions for House Robber algorithm
 */
namespace house_robber {
/**
 * @brief The main function implements house robber algorithm using dynamic
 * programming
 * @param money array containing money in the ith house
 * @param n size of array
 * @returns maximum amount of money that can be robbed
 */
std::uint64_t houseRobber(const std::vector<int> &money, int n) {
    if (n == 0) {  // if there is no house
        return 0;
    }
    if (n == 1) {  // if there is only one house
        return money[0];
    }
    if (n == 2) {  // if there are two houses, one with the maximum amount of
                   // money will be robbed
        return std::max(money[0], money[1]);
    }
    int max_value = 0;  // contains maximum stolen value at the end
    int value1 = money[0];
    int value2 = std::max(money[0], money[1]);
    for (int i = 2; i < n; i++) {
        max_value = std::max(money[i] + value1, value2);
        value1 = value2;
        value2 = max_value;
    }

    return max_value;
}
}  // namespace house_robber
}  // namespace dynamic_programming

/**
 * @brief Test implementations
 * @returns void
 */
static void test() {
    // Test 1
    // [1, 2, 3, 1] return 4
    std::vector<int> array1 = {1, 2, 3, 1};
    std::cout << "Test 1... ";
    assert(
        dynamic_programming::house_robber::houseRobber(array1, array1.size()) ==
        4);  // here the two non-adjacent houses that are robbed are first and
             // third with total sum money as 4
    std::cout << "passed" << std::endl;

    // Test 2
    // [6, 7, 1, 3, 8, 2, 4] return 19
    std::vector<int> array2 = {6, 7, 1, 3, 8, 2, 4};
    std::cout << "Test 2... ";
    assert(
        dynamic_programming::house_robber::houseRobber(array2, array2.size()) ==
        19);  // here the four non-adjacent houses that are robbed are first,
              // third, fifth and seventh with total sum money as 19
    std::cout << "passed" << std::endl;

    // Test 3
    // [] return 0
    std::vector<int> array3 = {};
    std::cout << "Test 3... ";
    assert(
        dynamic_programming::house_robber::houseRobber(array3, array3.size()) ==
        0);  // since there is no house no money can be robbed
    std::cout << "passed" << std::endl;

    // Test 4
    // [2,7,9,3,1] return 12
    std::vector<int> array4 = {2, 7, 9, 3, 1};
    std::cout << "Test 4... ";
    assert(
        dynamic_programming::house_robber::houseRobber(array4, array4.size()) ==
        12);  // here the three non-adjacent houses that are robbed are first,
              // third and fifth with total sum money as 12
    std::cout << "passed" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // execute the test
    return 0;
}
