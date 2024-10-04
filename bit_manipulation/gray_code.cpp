/**
 * @brief Program to generate n-bit [Gray 
 * code](https://en.wikipedia.org/wiki/Gray_code)
 * 
 * @details
 * Gray code is a binary numeral system
 * where consecutive values differ in exactly 1 bit.
 * The following code offers one of many possible Gray codes 
 * given some pre-determined number of bits.
 */

#include <bitset>  /// for gray code representation
#include <cassert>  /// for assert
#include <iostream>  /// for IO operations
#include <vector>  /// for vector data structure

/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */
namespace bit_manipulation {
/**
 * @namespace gray_code
 * @brief Generate n-bit Gray code
 */
namespace gray_code {
/**
 * @brief The main function to generate n-bit Gray code
 *
 * @param n Number of bits
 * @return A vector that stores the n-bit Gray code
 */
std::vector<std::bitset<32>> gray_code_generation(int n) {
    std::vector<std::bitset<32>> gray_code = {};  // Initialise empty vector

    // No Gray codes for non-positive values of n
    if (n <= 0) {
        return gray_code;
    }
    
    int total_codes = 1 << n;  // Number of n-bit gray codes

    for (int i = 0; i < total_codes; i++) {
        int gray_num = i ^ (i >> 1);  // Gray code formula
        gray_code.push_back(std::bitset<32>(gray_num));  // Store the value
    }

    return gray_code;
} 
}  // namespace gray_code
}  // namespace bit_manipulation

/**
 * @brief Self-test implementation
 *
 * @returns void
 */
static void test() { 
    std::vector<std::bitset<32>> gray_code_negative_1 = {};

    std::vector<std::bitset<32>> gray_code_0 = {};

    std::vector<std::bitset<32>> gray_code_1 = {
        std::bitset<32>(0), std::bitset<32>(1)
    };

    std::vector<std::bitset<32>> gray_code_2 = {
        std::bitset<32>(0), std::bitset<32>(1), std::bitset<32>(3), std::bitset<32>(2)
    };

    std::vector<std::bitset<32>> gray_code_3 = {
        std::bitset<32>(0), std::bitset<32>(1), std::bitset<32>(3), std::bitset<32>(2),
        std::bitset<32>(6), std::bitset<32>(7), std::bitset<32>(5), std::bitset<32>(4)
    };

    std::vector<std::bitset<32>> gray_code_4 = {
        std::bitset<32>(0), std::bitset<32>(1), std::bitset<32>(3), std::bitset<32>(2),
        std::bitset<32>(6), std::bitset<32>(7), std::bitset<32>(5), std::bitset<32>(4),
        std::bitset<32>(12), std::bitset<32>(13), std::bitset<32>(15), std::bitset<32>(14),
        std::bitset<32>(10), std::bitset<32>(11), std::bitset<32>(9), std::bitset<32>(8)
    };

    std::vector<std::bitset<32>> gray_code_5 = {
        std::bitset<32>(0), std::bitset<32>(1), std::bitset<32>(3), std::bitset<32>(2),
        std::bitset<32>(6), std::bitset<32>(7), std::bitset<32>(5), std::bitset<32>(4),
        std::bitset<32>(12), std::bitset<32>(13), std::bitset<32>(15), std::bitset<32>(14),
        std::bitset<32>(10), std::bitset<32>(11), std::bitset<32>(9), std::bitset<32>(8),
        std::bitset<32>(24), std::bitset<32>(25), std::bitset<32>(27), std::bitset<32>(26),
        std::bitset<32>(30), std::bitset<32>(31), std::bitset<32>(29), std::bitset<32>(28),
        std::bitset<32>(20), std::bitset<32>(21), std::bitset<32>(23), std::bitset<32>(22),
        std::bitset<32>(18), std::bitset<32>(19), std::bitset<32>(17), std::bitset<32>(16)
    };

    // invalid values for n
    assert(bit_manipulation::gray_code::gray_code_generation(-1) == gray_code_negative_1);
    assert(bit_manipulation::gray_code::gray_code_generation(0) == gray_code_0);

    // valid values for n
    assert(bit_manipulation::gray_code::gray_code_generation(1) == gray_code_1);
    assert(bit_manipulation::gray_code::gray_code_generation(2) == gray_code_2);
    assert(bit_manipulation::gray_code::gray_code_generation(3) == gray_code_3);
    assert(bit_manipulation::gray_code::gray_code_generation(4) == gray_code_4);
    assert(bit_manipulation::gray_code::gray_code_generation(5) == gray_code_5);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  //Run self-test implementation
    return 0;
}
