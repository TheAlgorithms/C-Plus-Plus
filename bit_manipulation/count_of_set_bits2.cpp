/**
 * @file
 * @brief Finding No of Set Bits in O(k).
 * https://www.geeksforgeeks.org/builtin-functions-gcc-compiler/
 * @details
 * How to calculate the no of Set bits in a number.
 * math equations, etc.
 * @author [Aman Deoli](https://github.com/deoliaman00)
 * @see related_file.cpp, another_file.cpp
 */

#include <cassert>  /// for assert
#include <iostream>
/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */
namespace bit_manipulation {
/**
 * @namespace no_of_set_bits
 * @brief Functions for the [count sets
 * bits](https://www.geeksforgeeks.org/builtin-functions-gcc-compiler/)
 * implementation
 */
namespace no_of_set_bits {
/**
 * @brief The main function implements set bit count
 * @param n is the number whose set bit will be counted
 * @returns total number of set-bits in the binary representation of number `n`
 */
std::uint64_t countSetBits(
    std ::int64_t n) {  // int64_t is preferred over int so that
                        // no Overflow can be there.

    return __builtin_popcount(n);
    // Why this algorithm is better than the standard one?
    // Because this algorithm takes O(k) time where k is no of set bits
}
}  // namespace no_of_set_bits
}  // namespace bit_manipulation

/**
 * @brief Self-test implementations
 * @returns void
 */

static void test() {
    // n = 1 return 1
    assert(bit_manipulation::no_of_set_bits::countSetBits(1) == 1);
    // n = 3 return 2
    assert(bit_manipulation::no_of_set_bits::countSetBits(3) == 2);
    // n = 10 return 2
    assert(bit_manipulation::no_of_set_bits::countSetBits(10) == 2);
    // n = 13 return 2
    assert(bit_manipulation::no_of_set_bits::countSetBits(13) == 3);
    // n = 15 return 4
    assert(bit_manipulation::no_of_set_bits::countSetBits(15) == 4);
    // n = 25 return 3
    assert(bit_manipulation::no_of_set_bits::countSetBits(25) == 3);
    // n = 31 return 5
    assert(bit_manipulation::no_of_set_bits::countSetBits(31) == 5);
    // n = 32 return 1
    assert(bit_manipulation::no_of_set_bits::countSetBits(32) == 1);
    std::cout << "Test cases passed successfully" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    std::cout << std::endl;
    return 0;
}
