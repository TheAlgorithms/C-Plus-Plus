/**
 * @file
 * @brief Implementation to [count sets bits](https://www.geeksforgeeks.org/count-set-bits-in-an-integer/) in an integer.
 *
 * @details
 * Time Complexity :- O(log n)
 * Space complexity :- O(1)
 * @author [Swastika Gupta](https://github.com/swastyy)
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
 * @namespace bitCount
 * @brief Functions for the [count sets bits](https://www.geeksforgeeks.org/count-set-bits-in-an-integer/) implementation
 */
namespace bitCount {
/**
 * @brief The main function implements set bit count
 * @param n is the number whose set bit will be counted
 * @returns count , the number set bit in binary representation of n
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
}  // namespace bitCount
}  // namespace bit_manipulation

/**
 * @brief Test implementations
 * @returns void
 */
static void test() {
    // n = 4 return 1
    assert(bit_manipulation::bitCount::countSetBits(4) == 1);
    // n = 6 return 2
    assert(bit_manipulation::bitCount::countSetBits(6) == 2);
    // n = 13 return 3
    assert(bit_manipulation::bitCount::countSetBits(13) == 3);
    // n = 9 return 2
    assert(bit_manipulation::bitCount::countSetBits(9) == 2);
    // n = 15 return 4
    assert(bit_manipulation::bitCount::countSetBits(15) == 4);
    // n = 25 return 3
    assert(bit_manipulation::bitCount::countSetBits(25) == 3);
    std::cout << "All test cases passed" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // execute the test
    return 0;
}
