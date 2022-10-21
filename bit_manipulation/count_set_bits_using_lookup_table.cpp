/**
 * @file
 * @brief Implementation to [count number of set bits of a number]
 * (https://www.geeksforgeeks.org/count-set-bits-in-an-integer/) in an
 * integer.
 *
 * @details
 * We are given an integer number. We need to calculate the number of set bits
 * in it.
 *
 * A binary number consists of two digits. They are 0 & 1. Digit 1 is known as
 * set bit in computer terms.
 * Worst Case Time Complexity: O(1)
 * Space complexity: O(1)
 * @author [KartikeySharma](https://github.com/KartikeySharma)
 */
#include <bitset>    /// for bitwise operations
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
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
 * @returns total number of set-bits in the binary representation of number `n`
 */

// Macros to generate the lookup table (at compile-time)
#define B2(n)      n, n + 1, n + 1, n + 2
#define B4(n)      B2(n), B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n)      B4(n), B4(n + 1), B4(n + 1), B4(n + 2)
#define COUNT_BITS B6(0), B6(1), B6(1), B6(2)

unsigned int lookup[256] = {COUNT_BITS};
std::uint64_t countSetBits(
    std ::int64_t n) {  // int64_t is preferred over int so that
                        // no Overflow can be there.

    // "count" variable is used to count number of set-bits('1')
    // in binary representation of number 'n'
    int count = lookup[n & 0xff] +          // consider the first 8 bits
                lookup[(n >> 8) & 0xff] +   // consider the next 8 bits
                lookup[(n >> 16) & 0xff] +  // consider the next 8 bits
                lookup[(n >> 24) & 0xff];   // consider last 8 bits

    return count;
    // Why this algorithm is better than the standard one?
    // Because this algorithm runs in O(1) time by using a lookup table which is
    // generated during compile time.
}
}  // namespace count_of_set_bits
}  // namespace bit_manipulation

static void test() {
    // n = 4 return 1
    assert(bit_manipulation::count_of_set_bits::countSetBits(-1) == 32);
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
    // n = 97 return 3
    assert(bit_manipulation::count_of_set_bits::countSetBits(97) == 3);
    // n = 31 return 5
    assert(bit_manipulation::count_of_set_bits::countSetBits(31) == 5);
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
