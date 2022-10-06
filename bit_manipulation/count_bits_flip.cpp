/**
 * @file
 * @brief Implementation to
 * [Count number of bits to be flipped to convert A to B]
 * (https://www.geeksforgeeks.org/count-number-of-bits-to-be-flipped-to-convert-a-to-b/)
 * in an integer.
 *
 * @details
 * We are given two numbers A and B. Our task is to count the number of bits
 * needed to be flipped to convert A to B.
 *
 * Explanation:
 *
 * A  = 01010 B  = 10100
 * As we can see, the bits of A that need to be flipped are 01010.
 * If we flipthese bits, we get 10100, which is B.
 *
 * Worst Case Time Complexity: O(log n)
 * Space complexity: O(1)
 * @author [Yash Raj Singh](https://github.com/yashrajyash)
 */
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */
namespace bit_manipulation {
/**
 * @namespace count_bits_flip
 * @brief Functions for the [count bits
 * flip](https://www.geeksforgeeks.org/count-set-bits-in-an-integer/)
 * implementation
 */
namespace count_bits_flip {
/**
 * @brief The main function implements count of bits flip required
 * @param A is the given number whose bits will be flipped to get number B
 * @param B is the given target number
 * @returns total number of bits needed to be flipped to convert A to B
 */
std::uint64_t countBitsFlip(
    std::int64_t A,
    std::int64_t B) {  // int64_t is preferred over int so that
                       // no Overflow can be there.

    int count =
        0;  // "count" variable is used to count number of bits flip of the
            // number A to form B in binary representation of number 'n'
    A = A ^ B;
    while (A) {
        A = A & (A - 1);
        count++;
    }
    return count;
}
}  // namespace count_bits_flip
}  // namespace bit_manipulation

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // A = 10, B = 20 return 4
    assert(bit_manipulation::count_bits_flip::countBitsFlip(10, 20) == 4);
    // A = 20, B = 25 return 3
    assert(bit_manipulation::count_bits_flip::countBitsFlip(20, 25) == 3);
    // A = 7, B = 10 return 3
    assert(bit_manipulation::count_bits_flip::countBitsFlip(7, 10) == 3);
    // A = 17, B = 25 return 1
    assert(bit_manipulation::count_bits_flip::countBitsFlip(17, 25) == 1);
    // A = 11, B = 8 return 2
    assert(bit_manipulation::count_bits_flip::countBitsFlip(11, 8) == 2);
    // A = 21, B = 22 return 2
    assert(bit_manipulation::count_bits_flip::countBitsFlip(21, 22) == 2);
    // A = 7, B = 786 return 5
    assert(bit_manipulation::count_bits_flip::countBitsFlip(7, 786) == 5);
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
