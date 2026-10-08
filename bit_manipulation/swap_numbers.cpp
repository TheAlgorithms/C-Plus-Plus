/**
 * @file
 * @brief implementatuon for the
 * [XOR swap algorithm](https://en.wikipedia.org/wiki/XOR_swap_algorithm)
 *
 * @details
 * we are given two integer numbers
 * we need to swap their values without temporary variables
 * example:
 *
 * zero stage (no changes yet):
 * variable |   a   |    b   |
 * ===========================
 * binary   | 0b111 | 0b1000 |
 * ===========================
 * decimal  |   7   |    8   |
 *
 * first stage (action: a ^= b):
 * variable |   a    |    b   |
 * ============================
 * binary   | 0b1111 | 0b1000 |
 * ============================
 * decimal  |   15   |    8   |
 *
 * second stage (action: b = a ^ b):
 * variable |   a    |    b   |
 * ============================
 * binary   | 0b1111 | 0b1000 |
 * ============================
 * decimal  |   15   |    8   |
 *
 * third/last stage (action: a ^= b):
 * variable |   a   |    b   |
 * ===========================
 * binary   | 0b111 | 0b1000 |
 * ===========================
 * decimal  |   7   |    8  |
 *
 * explanation:
 * an XOR operator will xor the values of 'a' and 'b' and store them in 'a'
 * this works similiar to a += b; b = a - b; a -= b;
 *
 * Time Complexity : O(1)
 * Space Complexity : O(1)
 * @author [vi](https://github.com/ViCppDev)
 */

#include <cassert>  // for assert
#include <cstdint>  // for int64_t type
#include <iostream> // for IO operations

/**
 * @namespace bit_manipulation
 * @brief bit manipulation algorithms
 */
namespace bit_manipulation {
/**
 * @brief the function will swap the values of two numbers
 * @param a is the first number to apply swap on
 * @param b is the second number to apply swap on
 * @return void
 */
constexpr inline void BitSwap(int64_t& a, int64_t& b) noexcept {
    a ^= b;
    b = a ^ b;
    a ^= b;
}
} // namespace bit_manipulation

/**
 * @brief self-test implementation
 * @returns void
 */
static void test() {
    int64_t a{}, b{};

    // 1st test
    a = 7;
    b = 8;
    bit_manipulation::BitSwap(a, b);
    assert(a == 8 && b == 7);

    // 2nd test
    a = -3;
    b = -4;
    bit_manipulation::BitSwap(a, b);
    assert(a == -4 && b == -3);

    // 3rd test
    a = 48384;
    b = -37484;
    bit_manipulation::BitSwap(a, b);
    assert(a == -37484 && b == 48384);

    // 4th test
    a = -484984949;
    b = -37484;
    bit_manipulation::BitSwap(a, b);
    assert(a == -37484 && b == -484984949);

    // 5th test
    a = -4434;
    b = a;
    bit_manipulation::BitSwap(a, b);
    assert(a == -4434 && b == -4434);

    std::cout << "ALL TESTS HAVE PASSED SUCCESSFULLY\n";
}

/**
 * @brief main function
 * @returns 0 on exit
 */
int main() {
    test();
    return 0;
}
