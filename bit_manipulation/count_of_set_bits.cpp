/**
 * @file
 * @brief Implementation to [count sets
 * bits](https://www.geeksforgeeks.org/count-set-bits-in-an-integer/) in an
 * integer.
 *
 * @details
 * We are given an integer number. Let’s say, number. The task is to first
 * calculate the binary digit of a number and then calculate the total set bits
 * of a number.
 *
 * Set bits in a binary number is represented by 1. Whenever we calculate the
 * binary number of an integer value it is formed as the combination of 0’s and
 * 1’s. So digit 1 is known as a set bit in computer terms.
 * Time Complexity: O(log n)
 * Space complexity: O(1)
 * @author [Swastika Gupta](https://github.com/Swastyy)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for io operations
#include <vector>    /// for std::vector

/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */
namespace bit_manipulation {
/**
 * @namespace count_of_set_bits
 * @brief Functions for the [count sets
 * bits](https://www.geeksforgeeks.org/count-set-bits-in-an-integer/)
 * implementation
 */
namespace count_of_set_bits {
/**
 * @brief The main function implements set bit count
 * @param n is the number whose set bit will be counted
 * @returns the count of the number set bit in the binary representation of `n`
 */
std::uint64_t countSetBits(int n) {
    int count = 0;  // "count" variable is used to count number of 1's in binary
                    // representation of the number
    while (n != 0) {
        count += n & 1;
        n = n >> 1;  // n=n/2
    }
    return count;
}
}  // namespace count_of_set_bits
}  // namespace bit_manipulation

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // n = 4 return 1
    assert(bit_manipulation::count_of_set_bits::countSetBits(4) == 1);
    // n = 6 return 2
    assert(bit_manipulation::count_of_set_bits::countSetBits(6) == 2);
    // n = 13 return 3
    assert(bit_manipulation::count_of_set_bits::countSetBits(13) == 3);
    // n = 9 return 2
    assert(bit_manipulation::count_of_set_bits::countSetBits(9) == 2);
    // n = 15 return 4
    assert(bit_manipulation::count_of_set_bits::countSetBits(15) == 4);
    // n = 25 return 3
    assert(bit_manipulation::count_of_set_bits::countSetBits(25) == 3);
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
