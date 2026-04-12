#include <cassert>
#include <cstdint>
#include <iostream>

/**
 * @brief Compute the nth Catalan number using a combinatorial approach
 *
 * Catalan Numbers:
 * Sequence: 1, 1, 2, 5, 14, 42, ...
 *
 * Applications:
 * - Count of valid parentheses expressions
 * - Number of Binary Search Trees with n nodes
 * - Polygon triangulation
 *
 * Formula:
 * Cn = (2n)! / ((n+1)! * n!)
 *
 * This implementation uses an iterative relation:
 * Cn = C(n-1) * 2*(2n-1)/(n+1)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 *
 * Note:
 * Works reliably for n <= 35 (fits in uint64_t)
 */

uint64_t catalan(uint32_t n) {
    uint64_t res = 1;  // C0 = 1

    for (uint32_t i = 0; i < n; i++) {
        res = res * 2 * (2 * i + 1) / (i + 2);
    }

    return res;
}

// ------------------ TESTS ------------------

static void test() {
    assert(catalan(0) == 1);
    assert(catalan(1) == 1);
    assert(catalan(2) == 2);
    assert(catalan(3) == 5);
    assert(catalan(4) == 14);
    assert(catalan(5) == 42);
    assert(catalan(10) == 16796);
}

// ------------------ MAIN ------------------

int main() {
    test();
    std::cout << "All tests passed!\n";
    return 0;
}