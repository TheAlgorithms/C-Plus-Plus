/**
 * @file
 * @brief [Next higher number with same number of set bits]
 * (https://www.geeksforgeeks.org/next-higher-number-with-same-number-of-set-bits/)
 * implementation
 *
 * @details
 * Given a number x, find next number with same number of 1 bits in it’s binary
 * representation. For example, consider x = 12, whose binary representation is
 * 1100 (excluding leading zeros on 32 bit machine). It contains two logic 1
 * bits. The next higher number with two logic 1 bits is 17 (100012).
 *
 * A binary number consists of two digits. They are 0 & 1. Digit 1 is known as
 * set bit in computer terms.
 * @author [Kunal Nayak](https://github.com/Kunal766)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */
namespace bit_manipulation {

/**
 * @brief The main function implements checking the next number
 * @param x the number that will be calculated
 * @returns a number
 */
uint64_t next_higher_number(uint64_t x) {
    uint64_t rightOne = 0;
    uint64_t nextHigherOneBit = 0;
    uint64_t rightOnesPattern = 0;

    uint64_t next = 0;

    if (x) {
        // right most set bit
        rightOne = x & -static_cast<signed>(x);

        // reset the pattern and set next higher bit
        // left part of x will be here
        nextHigherOneBit = x + rightOne;

        // nextHigherOneBit is now part [D] of the above explanation.

        // isolate the pattern
        rightOnesPattern = x ^ nextHigherOneBit;

        // right adjust pattern
        rightOnesPattern = (rightOnesPattern) / rightOne;

        // correction factor
        rightOnesPattern >>= 2;

        // rightOnesPattern is now part [A] of the above explanation.

        // integrate new pattern (Add [D] and [A])
        next = nextHigherOneBit | rightOnesPattern;
    }

    return next;
}

}  // namespace bit_manipulation

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // x = 4 return 8
    assert(bit_manipulation::next_higher_number(4) == 8);
    // x = 6 return 9
    assert(bit_manipulation::next_higher_number(6) == 9);
    // x = 13 return 14
    assert(bit_manipulation::next_higher_number(13) == 14);
    // x = 64 return 128
    assert(bit_manipulation::next_higher_number(64) == 128);
    // x = 15 return 23
    assert(bit_manipulation::next_higher_number(15) == 23);
    // x= 32 return 64
    assert(bit_manipulation::next_higher_number(32) == 64);
    // x = 97 return 98
    assert(bit_manipulation::next_higher_number(97) == 98);
    // x = 1024 return 2048
    assert(bit_manipulation::next_higher_number(1024) == 2048);

    std::cout << "All test cases have successfully passed!" << std::endl;
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
