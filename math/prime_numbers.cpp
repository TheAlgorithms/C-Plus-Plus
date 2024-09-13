/**
 * @file
 * @brief Get list of prime numbers
 * @see primes_up_to_billion.cpp sieve_of_eratosthenes.cpp
 */
#include <iostream>
#include <vector>

/** Generate an increasingly large number of primes
 * and store in a list
 */
std::vector<int> primes(size_t max) {
    std::vector<int> res;
    std::vector<bool> is_not_prime(max + 1, false);
    for (size_t i = 2; i <= max; i++) {
        if (!is_not_prime[i]) {
            res.emplace_back(i);
        }
        for (int p : res) {
            size_t k = i * p;
            if (k > max) {
                break;
            }
            is_not_prime[k] = true;
            if (i % p == 0) {
                break;
            }
        }
    }
    return res;
}

/** main function */
int main() {
    std::cout << "Calculate primes up to:\n>> ";
    int n = 0;
    std::cin >> n;
    std::vector<int> ans = primes(n);
    for (int p : ans) std::cout << p << ' ';
    std::cout << std::endl;
}
