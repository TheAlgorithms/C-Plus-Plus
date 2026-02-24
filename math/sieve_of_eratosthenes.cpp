/**
 * @file sieve_of_eratosthenes.cpp
 * @brief Generates all prime numbers up to N with sieve method.
 * @details
 * Builds a boolean table and marks multiples of each discovered prime.
 * Remaining unmarked indices are prime. This implementation runs in
 * O(N log log N) time and uses O(N) space.
 * @author OpenAI
 * @see https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

/**
 * @brief Computes all prime numbers in [2, n].
 * @param n upper bound for the sieve.
 * @returns list of all primes less than or equal to n.
 */
std::vector<int> sieve_of_eratosthenes(int n) {
    if (n < 2) {
        return {};
    }
    std::vector<bool> is_prime(n + 1, true);
    is_prime[0] = false;
    is_prime[1] = false;
    for (int p = 2; p * p <= n; ++p) {
        if (is_prime[p]) {
            for (int multiple = p * p; multiple <= n; multiple += p) {
                is_prime[multiple] = false;
            }
        }
    }

    std::vector<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

/**
 * @brief Validates sieve implementation with representative tests.
 * @returns void.
 */
static void test() {
    assert(sieve_of_eratosthenes(0).empty());
    assert(sieve_of_eratosthenes(1).empty());

    std::vector<int> p10 = sieve_of_eratosthenes(10);
    assert((p10 == std::vector<int>{2, 3, 5, 7}));

    std::vector<int> p2 = sieve_of_eratosthenes(2);
    assert((p2 == std::vector<int>{2}));

    std::vector<int> p100 = sieve_of_eratosthenes(100);
    assert(p100.size() == 25);
    assert(p100.back() == 97);

    std::cout << "All tests passed!\n";
}

int main() {
    test();
    return 0;
}
