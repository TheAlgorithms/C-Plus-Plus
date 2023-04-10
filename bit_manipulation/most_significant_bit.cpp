/**
 * @file
 * @breif functions for determining the most significant bit of a given number
 * and its position in O(1) time complexity [as seen
 * here](https://www.geeksforgeeks.org/find-significant-set-bit-number)
 * @details
 * Given an integer x: 0b00011001 (in this example we will use an 8 bit number
 * for simplicity) we can find its msb (most significant digit) by first setting
 * every bit until msb, and then by adding 1 we will have out msb one place
 * shifted, so we'll shift it back one space (x <<= 1). First we make sure that
 * the first bit form msb to 0 bit is setted, x |= (x >> 1), this will set the
 * msb-1 bit Then we can conclude that both msb AND msb-1 bits are setted, so we
 * can set the next 2 bits by using the same logic, x |= (x >> 2) As we can see,
 * now all four bits from msb to msb-4 are setted, so we can use those again, x
 * |= (x >> 4) Now if we do one more set we will overflow, and it obvious that
 * we had setted all bits from msb to first bit All that is remaning for us is
 * to extract the higher bit by adding one, and shifting to the left
 * @author [Bordei Cosmin](https://github.com/C-0-S-M-1-N)
 * */

#include <cassert>   ///for asserts
#include <iostream>  ///for IO operations

/**
 * @namespace bit_manipulation
 * @breif Bit manipulation algorithms
 * */
namespace bit_manipulation {
/**
 * @namespace most_significant_bit
 * @breif Functions for determening the most significant bit of a number
 * */

namespace most_significant_bit {

/**
 * @breif Function that retuns the most significant bit of a 64bit number with a
 * complexity of O(1)
 * @param x the number
 * @returns a number that only has the most significant bit seted
 * */
uint64_t msb(uint64_t x) {
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    x |= (x >> 32);
    x++;
    x >>= 1;
    return x;
}

/**
 * @breif Function that returns the position of the most significnt bit
 * @param x the number
 * @returns the position where the most significant number appears
 * */
uint64_t msb_position(uint64_t x) {
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    x |= (x >> 32);
    x++;
    x >>= 1;
    int ret = 0;
    while (x > 1) {
        ret++;
        x >>= 1;
    }
    // 	std::cerr << ret << '\n';
    return ret;
}

};  // namespace most_significant_bit

};  // namespace bit_manipulation

/**
 * @breif Self-test implementations
 * @returns void
 * */
static void test() {
    int i = 0;
    std::cout << "case " << i << ' ';
    assert(bit_manipulation::most_significant_bit::msb(203) == 128);
    std::cout << "passed\n";
    i++;

    std::cout << "case " << i << ' ';
    assert(bit_manipulation::most_significant_bit::msb(13) == 8);
    std::cout << "passed\n";
    i++;

    std::cout << "case " << i << ' ';
    assert(bit_manipulation::most_significant_bit::msb(469366124) == 268435456);
    std::cout << "passed\n";
    i++;

    std::cout << "case " << i << ' ';
    assert(bit_manipulation::most_significant_bit::msb_position(203) == 7);
    std::cout << "passed\n";
    i++;

    std::cout << "case " << i << ' ';
    assert(bit_manipulation::most_significant_bit::msb_position(13) == 3);
    std::cout << "passed\n";
    i++;

    std::cout << "case " << i << ' ';
    assert(bit_manipulation::most_significant_bit::msb_position(469366124) ==
           28);
    std::cout << "passed\n";
    i++;
}
/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char* argv[]) {
    test();
    return 0;
}
