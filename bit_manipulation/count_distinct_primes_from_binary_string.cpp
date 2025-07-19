/**
 * @file count_distinct_primes_from_binary_string.cpp
 * @brief Count distinct primes formed from binary strings using allowed operations.
 * 
 * @author Rudraksh Tank
 * @date July 2025
 *
 * @details
 * Given a binary string, the task is to count how many distinct prime decimal numbers
 * can be formed by:
 * - Swapping any two characters (makes position irrelevant)
 * - Changing any '1' to '0' (not the reverse)
 *
 * Efficient solution using bit manipulation and Sieve of Eratosthenes.
 *
 * Tags: Bit Manipulation, Prime Numbers, Combinatorics, Greedy, Bitmask
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

const int MAX = 1e6;
std::vector<bool> is_prime;

/**
 * @brief Precomputes prime numbers up to MAX using the Sieve of Eratosthenes.
 */
void precomputePrimes() {
    is_prime.assign(MAX + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= MAX; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAX; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

/**
 * @brief Counts distinct prime numbers that can be formed from the given binary string.
 * @param s Binary string input
 * @return Number of distinct primes possible after allowed transformations
 */
int countPrimeBinaryStrings(const std::string &s) {
    int n = s.length();
    int k = std::count(s.begin(), s.end(), '1');
    int cnt = 0;
    int limit = 1 << n;

    std::unordered_set<int> seen;

    for (int i = 2; i < limit; i++) {
        if (__builtin_popcount(i) <= k && is_prime[i]) {
            if (!seen.count(i)) {
                cnt++;
                seen.insert(i);
            }
        }
    }

    return cnt;
}

/**
 * @brief Main function to test the algorithm.
 */
int main() {
    precomputePrimes();
    std::string s;
    std::cin >> s;
    std::cout << countPrimeBinaryStrings(s) << std::endl;
    return 0;
}

