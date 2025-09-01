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

#include <cstdint>      ///< For uint32_t 
#include <iostream>     ///< For input/output stream handling (std::cin, std::cout)
#include <vector>       ///< For dynamic array storage (std::vector)
#include <unordered_set>///< For storing distinct primes without duplicates (std::unordered_set)
#include <algorithm>    ///< For algorithms like std::count
#include <cassert>      ///< For assert-based testing

const uint32_t MAX = 1e6;  ///< Upper bound for prime sieve
static std::vector<bool> is_prime;

/**
 * @namespace bit_manipulation
 * @brief Bit manipulation algorithms
 */
namespace bit_manipulation {

    /**
     * @brief Precomputes all prime numbers up to MAX using Sieve of Eratosthenes.
     */
    void precomputePrimes() {
        is_prime.assign(MAX + 1, true);
        is_prime[0] = is_prime[1] = false;
        for (uint32_t i = 2; i * i <= MAX; i++) {
            if (is_prime[i]) {
                for (uint32_t j = i * i; j <= MAX; j += i) {
                    is_prime[j] = false;
                }
            }
        }
    }
    
    int popcount(uint32_t x) {
        int count = 0;
        while (x) {
            count += x & 1;
            x >>= 1;
        }
        return count;
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
    
        for (uint32_t i = 2; i < limit; i++) {
            if (popcount(i) <= k && is_prime[i]) {
                if (!seen.count(i)) {
                    cnt++;
                    seen.insert(i);
                }
            }
        }
    
        return cnt;
    }

} // namespace bit_manipulation

/**
 * @brief Static test function using assertions instead of I/O.
 */
static void tests() {
    using namespace bit_manipulation;

    precomputePrimes();

    // Example test cases
    assert(countPrimeBinaryStrings("1") == 0);     // Only "1" -> not prime
    assert(countPrimeBinaryStrings("11") == 2);     // Should form primes like 3
    assert(countPrimeBinaryStrings("101") == 3);    // Can form primes like 5
    assert(countPrimeBinaryStrings("000") == 0);   // No 1s -> no primes possible
}

/**
 * @brief Main function to run tests.
 * @returns 0 on successful exit
 */
int main() {
    tests();
    return 0;
}
