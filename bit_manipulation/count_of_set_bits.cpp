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
 * Worst Case Time Complexity: O(log n)
 * Space complexity: O(1)
 * @author [Swastika Gupta](https://github.com/Swastyy)
 * @author [Prashant Thakur](https://github.com/prashant-th18)
 */
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
std::uint64_t countSetBits(
    std ::int64_t n) {  // int64_t is preferred over int so that
                        // no Overflow can be there.

    int count = 0;  // "count" variable is used to count number of set-bits('1')
                    // in binary representation of number 'n'
    while (n != 0) {
        ++count;
        n = (n & (n - 1));
    }
    return count;
    // Why this algorithm is better than the standard one?
    // Because this algorithm runs the same number of times as the number of
    // set-bits in it. Means if my number is having "3" set bits, then this
    // while loop will run only "3" times!!
}
}  // namespace count_of_set_bits
}  // namespace bit_manipulation

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
