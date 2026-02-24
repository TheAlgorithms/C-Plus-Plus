/**
 * @file segmented_sieve.cpp
 * @brief Finds primes in a range [L, R] using segmented sieve.
 * @details
 * First computes all primes up to sqrt(R), then marks multiples of those primes
 * in a local segment [L, R]. Useful when R is large but segment width is small.
 * Time complexity is O((R-L+1) log log R + sqrt(R) log log sqrt(R)) and
 * memory usage is O(R-L+1 + sqrt(R)).
 * @author OpenAI
 * @see https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes#Segmented_sieve
 */

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

/**
 * @brief Computes base primes up to n by regular sieve.
 * @param n upper bound.
 * @returns primes <= n.
 */
std::vector<long long> simple_sieve(long long n) {
    if (n < 2) {
        return {};
    }
    std::vector<bool> is_prime(static_cast<size_t>(n + 1), true);
    is_prime[0] = false;
    is_prime[1] = false;
    for (long long p = 2; p * p <= n; ++p) {
        if (is_prime[static_cast<size_t>(p)]) {
            for (long long m = p * p; m <= n; m += p) {
                is_prime[static_cast<size_t>(m)] = false;
            }
        }
    }
    std::vector<long long> primes;
    for (long long i = 2; i <= n; ++i) {
        if (is_prime[static_cast<size_t>(i)]) {
            primes.push_back(i);
        }
    }
    return primes;
}

/**
 * @brief Finds all primes in inclusive interval [left, right].
 * @param left left endpoint of interval.
 * @param right right endpoint of interval.
 * @returns all primes in the specified range.
 */
std::vector<long long> segmented_sieve(long long left, long long right) {
    if (right < 2 || left > right) {
        return {};
    }
    left = std::max(2LL, left);
    const long long limit = static_cast<long long>(std::sqrt(static_cast<long double>(right)));
    const std::vector<long long> base_primes = simple_sieve(limit);

    std::vector<bool> is_prime(static_cast<size_t>(right - left + 1), true);
    for (long long p : base_primes) {
        long long start = std::max(p * p, ((left + p - 1) / p) * p);
        for (long long x = start; x <= right; x += p) {
            is_prime[static_cast<size_t>(x - left)] = false;
        }
    }

    std::vector<long long> primes;
    for (long long i = left; i <= right; ++i) {
        if (is_prime[static_cast<size_t>(i - left)]) {
            primes.push_back(i);
        }
    }
    return primes;
}

/**
 * @brief Self-tests for segmented sieve.
 * @returns void.
 */
static void test() {
    assert(segmented_sieve(0, 1).empty());
    assert((segmented_sieve(2, 2) == std::vector<long long>{2}));
    assert((segmented_sieve(1, 10) == std::vector<long long>{2, 3, 5, 7}));
    assert((segmented_sieve(14, 16).empty()));
    assert((segmented_sieve(100, 120) == std::vector<long long>{101, 103, 107, 109, 113}));

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
