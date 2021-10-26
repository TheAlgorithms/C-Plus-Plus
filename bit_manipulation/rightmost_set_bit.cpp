/**
 * @file
 * @brief Implementation to [find the position of rightmost bit]
 * (https://www.geeksforgeeks.org/position-of-rightmost-set-bit/) in an
 * integer.
 *
 * @details
 * We are given an integer number. We need to find the position of
 * rightmost set bit in that integer.
 *
 * A binary number consists of two digits. They are 0 & 1. Digit 1 is known as
 * set bit in computer terms.
 * Worst Case Time Complexity: O(log n)
 * Space complexity: O(1)
 * @author [Diksha Singhal](https://github.com/diksha137)
 */
#include <cassert>   /// for assert
#include <iostream> /// for IO operations
#include <cmath>   /// for math operations like log2
/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */
namespace bit_manipulation {
/**
 * @namespace rightmost_set_bit
 * @brief Functions for the [rightmost set
 * bit](https://www.geeksforgeeks.org/position-of-rightmost-set-bit/)
 * implementation
 */
namespace rightmost_set_bit {
/**
 * @brief The main function implements set bit count
 * @param n is the number whose rightmost set bit position will be returned
 * @returns position of rightmost set bit in binary representation of number `n`
 */
std::uint64_t rightmostsetbit(std :: int64_t n) { // int64_t is preferred over int so that
                                          // no Overflow can be there.
                                          
    //Here log2 will return you, number of times we can express that number in power of two.
    //For all binary number containing only rightmost set bit as 1 like 2 , 4, 8, 16, 32….
    //We will find that position of right most set bit is always equals to log2(Number)+1
    return log2(n & -n) + 1;
    
}
}  // namespace rightmost_set_bit
}  // namespace bit_manipulation

static void test() {
    // n = 4 return 3
    assert(bit_manipulation::rightmost_set_bit::countSetBits(4) == 3);
    // n = 6 return 2
    assert(bit_manipulation::rightmost_set_bit::countSetBits(6) == 2);
    // n = 12 return 3
    assert(bit_manipulation::rightmost_set_bit::countSetBits(12) == 3);
    // n = 9 return 1
    assert(bit_manipulation::rightmost_set_bit::countSetBits(9) == 1);
    // n = 15 return 1
    assert(bit_manipulation::rightmost_set_bit::countSetBits(15) == 1);
    // n = 25 return 1
    assert(bit_manipulation::rightmost_set_bit::countSetBits(25) == 1);
    // n = 96 return 6
    assert(bit_manipulation::rightmost_set_bit::countSetBits(96) == 6);
    // n = 64 return 7
    assert(bit_manipulation::rightmost_set_bit::countSetBits(64) == 7);
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