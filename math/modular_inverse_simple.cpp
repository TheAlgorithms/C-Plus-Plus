/**
 * @file
 * @brief Simple implementation of [modular multiplicative
 * inverse](https://en.wikipedia.org/wiki/Modular_multiplicative_inverse)
 *
 * @details
 * this algorithm calculates the modular inverse x^{-1} \mod y iteratively
 */

#include <cassert>   /// for assert
#include <cstdint>
#include <cstdio>    /// for fprintf and printf
#include <cstdlib>   /// for exit
#include <iostream>  /// for IO operations

/**
 * @brief Function imod
 * Calculates the modular inverse of x with respect to y, x^{-1} \mod y
 * @param x number
 * @param y number
 * @returns the modular inverse
 * @note Example: imod(3, 11) == 4 because 3 * 4 = 12 = 1 * 11 + 1.
 * @note Supported inputs: x and y must have no common factor; otherwise no
 *       inverse exists and the search does not end.
 */
uint64_t imod(uint64_t x, uint64_t y) {
    uint64_t aux = 0;  // auxiliary variable
    uint64_t itr = 0;  // iteration counter

    do {  // run the algorithm while not find the inverse
        aux = y * itr + 1;
        itr++;
    } while (aux % x);  // while module aux % x non-zero

    return aux / x;
}

/**
 * @brief  self-test implementations
 * @returns void
 */
static void test() {
    std::cout << "First case testing... \n";
    // for a = 3 and b = 11 return 4
    assert(imod(3, 11) == 4);
    std::cout << "\nPassed!\n";

    std::cout << "Second case testing... \n";
    // for a = 3 and b = 26 return 9
    assert(imod(3, 26) == 9);
    std::cout << "\nPassed!\n";

    std::cout << "Third case testing... \n";
    // for a = 7 and b = 26 return 15
    assert(imod(7, 26) == 15);
    std::cout << "\nPassed!\n";

    std::cout << "\nAll test cases have successfully passed!\n";
}
/**
 * Independent reference: smallest r in [1, m-1] with (a * r) % m == 1,
 * or 0 if no such r exists. It searches candidate inverses directly; it does
 * not call imod() and does not use imod's "m * k + 1" method.
 */
static int reference_inverse(int a, int m) {
    for (int r = 1; r < m; r++) {
        if ((a * r) % m == 1) return r;
    }
    return 0;
}

/** Compare imod() with the hand-calculated table and the reference oracle. */
static void test_reference_comparison() {
    const int inv7[]  = {1, 4, 5, 2, 3, 6};
    const int inv11[] = {1, 6, 4, 3, 9, 2, 8, 7, 5, 10};
    const int inv26[] = {1, 0, 9, 0, 21, 0, 15, 0, 3, 0, 19, 0, 0,
                         0, 7, 0, 23, 0, 11, 0, 5, 0, 17, 0, 25};
    struct Row { int m; const int* inv; int n; };
    const Row rows[] = {{7, inv7, 6}, {11, inv11, 10}, {26, inv26, 25}};

    int compared = 0;
    for (const Row& row : rows) {
        for (int a = 1; a <= row.n; a++) {
            int expected = row.inv[a - 1];
            if (expected == 0) {
                assert(reference_inverse(a, row.m) == 0);
                continue;  // unsupported: imod() would never end (modular_inverse_simple.cpp:33)
            }
            int first = imod(a, row.m);   // modular_inverse_simple.cpp:26 imod defined here
            int second = imod(a, row.m);  // modular_inverse_simple.cpp:26 fresh equivalent call
            if (first != expected || second != first) {
                std::fprintf(stderr, "FAIL imod(%d, %d): expected %d, actual %d/%d\n",
                             a, row.m, expected, first, second);
                std::exit(1);
            }
            // the oracle must agree with the table
            assert(reference_inverse(a, row.m) == expected);
            compared++;
        }
    }
    assert(imod(4, 11) == 3);  // modular_inverse_simple.cpp:23 my neighboring input, worked out by hand
    std::printf("COMPARED=%d\n", compared);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    test_reference_comparison();  // run reference-comparison regression tests
    return 0;
}
