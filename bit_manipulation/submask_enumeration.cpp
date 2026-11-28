
/**
 * @file
 * @brief Implementation of [submask enumeration]
 * (https://cp-algorithms.com/algebra/all-submasks.html)
 * using bit manipulation.
 *
 * @details
 * A submask of an integer n is an integer whose set bits
 * are a subset of the set bits of n.
 *
 * For example, if n = 6 (110 in binary), its submasks are
 * 6 (110), 4 (100), 2 (010), and 0 (000).
 *
 * The algorithm enumerates all submasks in descending order
 * using the expression (i - 1) & n.
 *
 * Let k be the number of set bits in n.
 * Time Complexity: O(2^k)
 * Space Complexity: O(2^k)
 * Auxiliary Space Complexity: O(1), excluding the output.
 *
 * @author [Vaibhav C](https://github.com/vaibhavc-coder)
 */
#include <cassert>   /// for assert
#include <cstdint>   /// for uint64_t
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */
namespace bit_manipulation {

/**
 * @namespace submask_enumeration
 * @brief Functions for submask enumeration
 */
namespace submask_enumeration {

/**
 * @brief Enumerates all submasks of a given integer.
 * @param n The input bitmask
 * @returns A vector containing all submasks of n in
 * descending order, including zero.
 */
std::vector<std::uint64_t> enumerateAllSubmasks(std::uint64_t n) {
    std::vector<std::uint64_t> submasks;

    // Subtracting one clears the lowest set bit and sets
    // the lower bits. AND with n removes bits not in n.
    for (std::uint64_t i = n; ; i = (i - 1) & n) {
        submasks.push_back(i);

        if (i == 0) {
            break;
        }
    }

    return submasks;
}

}  // namespace submask_enumeration
}  // namespace bit_manipulation

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    using bit_manipulation::submask_enumeration::enumerateAllSubmasks;

    // Zero bitmask
    assert((enumerateAllSubmasks(0) ==
            std::vector<std::uint64_t>{0}));

    // Smallest positive bitmask
    assert((enumerateAllSubmasks(1) ==
            std::vector<std::uint64_t>{1, 0}));

    // Single set bit
    assert((enumerateAllSubmasks(4) ==
            std::vector<std::uint64_t>{4, 0}));

    // Adjacent set bits
    assert((enumerateAllSubmasks(6) ==
            std::vector<std::uint64_t>{6, 4, 2, 0}));

    // Non-adjacent set bits
    assert((enumerateAllSubmasks(9) ==
            std::vector<std::uint64_t>{9, 8, 1, 0}));

    // Multiple set bits
    assert((enumerateAllSubmasks(13) ==
            std::vector<std::uint64_t>{13, 12, 9, 8, 5, 4, 1, 0}));

    // All four lower bits set
    assert((enumerateAllSubmasks(15) ==
            std::vector<std::uint64_t>{
                15, 14, 13, 12, 11, 10, 9, 8,
                7, 6, 5, 4, 3, 2, 1, 0}));

    // Highest set bit of a 64-bit unsigned integer
    const std::uint64_t large = std::uint64_t{1} << 63;
    assert((enumerateAllSubmasks(large) ==
            std::vector<std::uint64_t>{large, 0}));

    std::cout << "All test cases successfully passed!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();
    return 0;
}
