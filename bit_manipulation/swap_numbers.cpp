/**
 * @details
 * we are given two integer numbers
 * we need to swap their values without temporary variables
 *
 * Time Complexity : O(1)
 * Space Complexity : O(1)
 * @author [vi](https://github.com/ViCppDev)
 */

#include <cassert>
#include <cstdint>
#include <iostream>

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
    /*
     * an XOR operator will xor the values of 'a' and 'b' and store them in 'a'
     * this works similiar to a += b; b = a - b; a -= b;
     * example:
     * a = 7 = 0b111, b = 8 = 0b1000
     * a ^= b; a == 0b1111 == 15
     * b = a ^ b; b == 0b111 == 7
     * a ^= b; a = 0b1000 == 8
     */
    a ^= b;
    b = a ^ b;
    a ^= b;
}
} // namespace bit_manipulation

inline static void test() noexcept {
    int64_t a{}, b{};

    a = 7;
    b = 8;
    bit_manipulation::BitSwap(a, b);
    assert(a == 8 && b == 7);

    a = -3;
    b = -4;
    bit_manipulation::BitSwap(a, b);
    assert(a == -4 && b == -3);

    a = 48384;
    b = -37484;
    bit_manipulation::BitSwap(a, b);
    assert(a == -37484 && b == 48384);

    a = -484984949;
    b = -37484;
    bit_manipulation::BitSwap(a, b);
    assert(a == -37484 && b == -484984949);

    std::cout << "ALL TESTS HAVE PASSED SUCCESSFULLY\n";
}

int main() {
    test();
}
