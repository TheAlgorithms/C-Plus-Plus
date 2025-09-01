/**
 * @file
 * @brief Implementation to [Check if a number is Even or Odd using Bitwise Operator]
 * (https://www.log2base2.com/c-examples/bitwise/odd-or-even-program-in-c-using-bitwise-operator.html)
 *
 * @details
 * Given an integer N, determine whether it is even or odd using bitwise manipulation.
 * The least significant bit (LSB) of a binary number determines its parity:
 * - If the LSB is 0, the number is even.
 * - If the LSB is 1, the number is odd.
 *
 * This can be checked efficiently using the bitwise AND operator (&) with 1.
 * - If (N & 1) == 0, N is even.
 * - If (N & 1) == 1, N is odd.
 *
 * Example:
 * Consider 8-bit binary representations of two numbers:
 *     Number: 10 (decimal) -> 00001010 (binary)
 *       LSB = 0 -> Even number
 * 
 *     Number: 13 (decimal) -> 00001101 (binary)
 *       LSB = 1 -> Odd number
 *
 * In both cases, evaluating (N & 1) isolates the LSB:
 * - For 10: 00001010 & 00000001 = 0  (Even)
 * - For 13: 00001101 & 00000001 = 1  (Odd)
 *
 * Worst Case Time Complexity: O(1)
 * Space Complexity: O(1)
 *
 * @author [Vedant Mukhedkar](https://github.com/git5v)
 */

#include <cassert>   /// for assert
#include <cstdint>   /// for uint32_t
#include <iostream>  /// for IO operations
#include <string>    /// for std::string

/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */
namespace bit_manipulation {
/**
 * @namespace even_odd
 * @brief Functions for checking if a number is even or odd using bitwise operations
 */
namespace even_odd {

/**
 * @brief Checks if a number is even or odd using bitwise AND.
 * @param N The number to check.
 * @returns "Even" if N is even, "Odd" if N is odd.
     */
        bool is_even(std::int64_t N) {
            return (N & 1) == 0 ? true : false;
        }

    }  // namespace even_odd
}  // namespace bit_manipulation

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    using bit_manipulation::even_odd::is_even;

    // Test Even numbers
    assert(is_even(0) == true);
    assert(is_even(2) == true);
    assert(is_even(100) == true);
    assert(is_even(-4) == true);
    assert(is_even(-1000) == true);

    // Test Odd numbers
    assert(is_even(1) == false);
    assert(is_even(3) == false);
    assert(is_even(101) == false);
    assert(is_even(-5) == false);
    assert(is_even(-999) == false);

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
