/**
 * @file euler_totient.cpp
 * @brief Computes Euler's totient function for one value and for a range.
 * @details
 * Euler's totient φ(n) is the count of integers in [1, n] that are coprime with n.
 * A single-value routine performs prime factorization in O(sqrt(n)), while the
 * sieve-style routine computes φ(i) for i in [1, N] in O(N log log N) time and
 * O(N) space.
 * @author OpenAI
 * @see https://en.wikipedia.org/wiki/Euler%27s_totient_function
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

/**
 * @brief Computes Euler's totient value for a single n.
 * @param n positive integer.
 * @returns φ(n), and returns 0 for n = 0.
 */
long long phi_single(long long n) {
    if (n == 0) {
        return 0;
    }
    long long result = n;
    long long x = n;
    for (long long p = 2; p * p <= x; ++p) {
        if (x % p == 0) {
            while (x % p == 0) {
                x /= p;
            }
            result -= result / p;
        }
    }
    if (x > 1) {
        result -= result / x;
    }
    return result;
}

/**
 * @brief Computes φ(i) for every i from 1 to n using sieve idea.
 * @param n upper bound.
 * @returns vector tot where tot[i] = φ(i), tot[0] = 0.
 */
std::vector<long long> phi_upto(int n) {
    std::vector<long long> tot(static_cast<size_t>(n + 1));
    for (int i = 0; i <= n; ++i) {
        tot[static_cast<size_t>(i)] = i;
    }
    for (int p = 2; p <= n; ++p) {
        if (tot[static_cast<size_t>(p)] == p) {
            for (int multiple = p; multiple <= n; multiple += p) {
                tot[static_cast<size_t>(multiple)] -= tot[static_cast<size_t>(multiple)] / p;
            }
        }
    }
    if (n >= 0) {
        tot[0] = 0;
    }
    if (n >= 1) {
        tot[1] = 1;
    }
    return tot;
}

/**
 * @brief Self-test routines for totient implementations.
 * @returns void.
 */
static void test() {
    assert(phi_single(0) == 0);
    assert(phi_single(1) == 1);
    assert(phi_single(9) == 6);
    assert(phi_single(36) == 12);
    assert(phi_single(97) == 96);

    std::vector<long long> tot = phi_upto(10);
    assert(tot[1] == 1);
    assert(tot[2] == 1);
    assert(tot[6] == 2);
    assert(tot[10] == 4);

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
