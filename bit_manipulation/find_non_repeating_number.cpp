/**
 * @file
 * @brief Implementation to find the non repeating integer
 * in an array of repeating integers. [Single
 * Number](https://leetcode.com/problems/single-number/)
 *
 * @details
 * Given an array of integers in which all of the numbers occur exactly
 * twice except one integer which occurs only once. Find the non-repeating
 * integer.
 *
 * Worst Case Time Complexity: O(n)
 * Space complexity: O(1)

 * @author [Ravidev Pandey](https://github.com/literalEval)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <vector>    /// storing the numbers

/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */
namespace bit_manipulation {
/**
 * @namespace find_non_repeating_integer
 * @brief Functions to find the non repeating integer
 * in an array of repeating integers. [Single
 * Number](https://leetcode.com/problems/single-number/)
 */
namespace find_non_repeating_integer {
/**
 * @brief The main function implements find single number
 * @param nums vector of integers
 * @returns returns the integer that occurs only once
 */
int64_t find_non_repeating_integer(const std::vector<int>& nums) {
    // The idea is based on the property of XOR.
    // We know that 'a' XOR 'a' is '0' and '0' XOR 'b'
    // is b.
    // Using this, if we XOR all the elements of the array,
    // the repeating elements will give '0' and this '0'
    // with the single number will give the number itself.

    int _xor = 0;

    for (const int& num : nums) {
        _xor ^= num;
    }

    return _xor;
}
}  // namespace find_non_repeating_integer
}  // namespace bit_manipulation

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // n = 10,2 return 14

    std::vector<int> nums_one{1, 1, 2, 2, 4, 5, 5};
    std::vector<int> nums_two{203, 3434, 4545, 3434, 4545};
    std::vector<int> nums_three{90, 1, 3, 90, 3};

    assert(bit_manipulation::find_non_repeating_integer::
               find_non_repeating_integer(nums_one) ==
           4);  // 4 is non repeating
    assert(bit_manipulation::find_non_repeating_integer::
               find_non_repeating_integer(nums_two) ==
           203);  // 203 is non repeating
    assert(bit_manipulation::find_non_repeating_integer::
               find_non_repeating_integer(nums_three) ==
           1);  // 1 is non repeating

    std::cout << "All test cases successfully passed!" << std::endl;
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
