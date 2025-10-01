/**
 * @file
 * @brief Optimized implementation to count number of set bits in an integer.
 *
 * @details
 * Provides multiple approaches:
 * 1. Compiler built-ins (fastest)
 * 2. Lookup table method
 * 3. Brian Kernighan's algorithm
 * 4. Naive bit-by-bit method
 *
 * Time Complexity:
 * - O(1) for built-ins
 * - O(log n) for Brian Kernighan
 * Space Complexity: O(1)
 *
 * @author Swastika Gupta, Prashant Thakur
 * @author [Contributor] (Optimize set bit counting with compiler built-ins and
 * multiple algorithms)(https://github.com/kokatesaurabh)
 */

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

namespace bit_manipulation {
namespace count_of_set_bits {

// Lookup table for 8-bit numbers
static constexpr unsigned char lookup_table[256] = {
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4,
    2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4,
    2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6,
    4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5,
    3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6,
    4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8};

// 1. Compiler built-ins
inline std::uint64_t countSetBitsBuiltin(std::uint64_t n) {
#if defined(__GNUC__) || defined(__clang__)
    return __builtin_popcountll(n);
#elif defined(_MSC_VER)
    return __popcnt64(n);
#else
    // Fallback
    std::uint64_t count = 0;
    while (n) {
        n &= (n - 1);
        ++count;
    }
    return count;
#endif
}

// 2. Lookup table method
inline std::uint64_t countSetBitsLookup(std::uint64_t n) {
    std::uint64_t count = 0;
    for (int i = 0; i < 8; ++i) {
        count += lookup_table[(n >> (i * 8)) & 0xFF];
    }
    return count;
}

// 3. Brian Kernighan's algorithm
inline std::uint64_t countSetBitsKernighan(std::uint64_t n) {
    std::uint64_t count = 0;
    while (n) {
        n &= (n - 1);
        ++count;
    }
    return count;
}

// 4. Naive bit-by-bit
inline std::uint64_t countSetBitsNaive(std::uint64_t n) {
    std::uint64_t count = 0;
    while (n) {
        count += (n & 1);
        n >>= 1;
    }
    return count;
}

// Default function: uses fastest method available
inline std::uint64_t countSetBits(std::uint64_t n) {
    return countSetBitsBuiltin(n);
}

}  // namespace count_of_set_bits
}  // namespace bit_manipulation

// ===================== Test Cases =====================
static void test() {
    using namespace bit_manipulation::count_of_set_bits;
    std::cout << "Running set bits counting tests...\n";

    std::vector<std::uint64_t> numbers = {
        0, 1, 2, 3, 4, 7, 15, 31, 255, 256, 511, 1023, 123456789, ~0ULL};

    for (auto n : numbers) {
        auto a = countSetBitsBuiltin(n);
        auto b = countSetBitsLookup(n);
        auto c = countSetBitsKernighan(n);
        auto d = countSetBitsNaive(n);
        assert(a == b && b == c && c == d);
    }

    std::cout << "All tests passed! All methods produce consistent results.\n";
}

int main() {
    test();
    return 0;
}
