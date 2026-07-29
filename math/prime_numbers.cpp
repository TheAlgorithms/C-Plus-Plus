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
std::vector<size_t> primes(size_t max) {
    std::vector<size_t> res;
    std::vector<bool> is_not_prime(max + 1, false);
    for (size_t i = 2; i <= max; i++) {
        if (!is_not_prime[i]) {
            res.emplace_back(i);
        }
        for (size_t p : res) {
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

    // Guard clause: Handle non-numeric (letters) and negative inputs
    if (std::cin.fail() || n < 0) {
        std::cout << "Error: Please enter a valid positive number.\n";
        return 1;
    }

    // Now, Input is safe
    // C++ converts the safe 'int n' to 'size_t' automatically

    std::vector<size_t> ans = primes(n);
    for (size_t p : ans) std::cout << p << ' ';
    std::cout << std::endl;
}
