/**
 * @file
 * @brief Returns the [Hamming
 * distance](https://en.wikipedia.org/wiki/Hamming_distance) between two
 * integers
 *
 * @details
 * To find hamming distance between two integers, we take their xor, which will
 * have a set bit iff those bits differ in the two numbers.
 * Hence, we return the number of such set bits.
 *
 * @author [Ravishankar Joshi](https://github.com/ravibitsgoa)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for io operations

/**
 * @namespace bit_manipulation
 * @brief Bit Manipulation algorithms
 */
namespace bit_manipulation {
/**
 * This function returns the number of set bits in the given number.
 * @param value the number of which we want to count the number of set bits.
 * @returns the number of set bits in the given number.
 */
uint64_t bitCount(uint64_t value) {
    uint64_t count = 0;
    while (value) {       // until all bits are zero
        if (value & 1) {  // check lower bit
            count++;
        }
        value >>= 1;  // shift bits, removing lower bit
    }
    return count;
}

/**
 * This function returns the hamming distance between two integers.
 * @param a the first number
 * @param b the second number
 * @returns the number of bits differing between the two integers.
 */
uint64_t hamming_distance(uint64_t a, uint64_t b) { return bitCount(a ^ b); }
}  // namespace bit_manipulation

/**
 * @brief Function to the test hamming distance.
 * @returns void
 */
static void test() {
    assert(bit_manipulation::hamming_distance(11, 2) == 2);
    assert(bit_manipulation::hamming_distance(2, 0) == 1);
    assert(bit_manipulation::hamming_distance(11, 0) == 3);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();           // execute the tests
    uint64_t a = 11;  // 1011 in binary
    uint64_t b = 2;   // 0010 in binary

    std::cout << "Hamming distance between " << a << " and " << b << " is "
              << bit_manipulation::hamming_distance(a, b) << std::endl;
}
