/**
 * @file extended_gcd.cpp
 * @brief Extended Euclidean algorithm for gcd and Bézout coefficients.
 * @details
 * Computes gcd(a, b) and coefficients x, y such that ax + by = gcd(a, b).
 * The recursive algorithm runs in O(log(min(a,b))) time and O(log(min(a,b)))
 * recursion depth.
 * @author OpenAI
 * @see https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm
 */

#include <cassert>
#include <iostream>

/**
 * @brief Stores the result of extended gcd.
 */
struct ExtendedGcdResult {
    long long gcd;
    long long x;
    long long y;
};

/**
 * @brief Computes gcd(a,b) and coefficients x,y with ax + by = gcd.
 * @param a first integer.
 * @param b second integer.
 * @returns structure containing gcd, x and y.
 */
ExtendedGcdResult extended_gcd(long long a, long long b) {
    if (b == 0) {
        return {a >= 0 ? a : -a, a >= 0 ? 1 : -1, 0};
    }
    ExtendedGcdResult next = extended_gcd(b, a % b);
    return {next.gcd, next.y, next.x - (a / b) * next.y};
}

/**
 * @brief Verifies correctness with assertions.
 * @returns void.
 */
static void test() {
    ExtendedGcdResult r1 = extended_gcd(30, 20);
    assert(r1.gcd == 10);
    assert(30 * r1.x + 20 * r1.y == r1.gcd);

    ExtendedGcdResult r2 = extended_gcd(17, 31);
    assert(r2.gcd == 1);
    assert(17 * r2.x + 31 * r2.y == 1);

    ExtendedGcdResult r3 = extended_gcd(0, 7);
    assert(r3.gcd == 7);
    assert(0 * r3.x + 7 * r3.y == 7);

    ExtendedGcdResult r4 = extended_gcd(-24, 18);
    assert(r4.gcd == 6);
    assert((-24) * r4.x + 18 * r4.y == 6);

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
