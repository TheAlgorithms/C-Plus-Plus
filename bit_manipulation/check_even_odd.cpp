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
 * Worst Case Time Complexity: O(1)
 * Space Complexity: O(1)
 *
 * @author [Vedant Mukhedkar](https://github.com/git5v)
 */

#include <cassert>   /// for assert
#include <cstdint>
#include <iostream>  /// for IO operations
#include <string>

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
        std::string checkEvenOdd(std::int64_t N) {
            return (N & 1) == 0 ? "Even" : "Odd";
        }

    }  // namespace even_odd
}  // namespace bit_manipulation

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    using bit_manipulation::even_odd::checkEvenOdd;

    // Test Even numbers
    assert(checkEvenOdd(0) == "Even");
    assert(checkEvenOdd(2) == "Even");
    assert(checkEvenOdd(100) == "Even");
    assert(checkEvenOdd(-4) == "Even");
    assert(checkEvenOdd(-1000) == "Even");

    // Test Odd numbers
    assert(checkEvenOdd(1) == "Odd");
    assert(checkEvenOdd(3) == "Odd");
    assert(checkEvenOdd(101) == "Odd");
    assert(checkEvenOdd(-5) == "Odd");
    assert(checkEvenOdd(-999) == "Odd");

    std::cout << "All test cases successfully passed!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations

    // Example usage:
    // std::int64_t num;
    // std::cout << "Enter a number: ";
    // std::cin >> num;
    // std::cout << num << " is " << bit_manipulation::even_odd::checkEvenOdd(num) << std::endl;

    return 0;
}
