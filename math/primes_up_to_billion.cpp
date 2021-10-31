/**
 * @file
 * @brief Compute prime numbers upto 1 billion
 * @see prime_numbers.cpp sieve_of_eratosthenes.cpp
 */
#include <iostream>
#include <bitset>

/** bitset to store the primes */
std::bitset<1000000000> prime;

/** Perform Sieve algorithm */
void Sieve(int64_t n) { 
    prime[0] = 0;                     // 0 is not prime
    prime[1] = 0;                     // 1 is not prime
    for (int64_t p = 2; p * p <= n; p++) {
        if (prime[p] == 1) {
            for (int64_t i = p * p; i <= n; i += p)
                prime[i] = 0;  // set all multiples of p to false
        }
    }
}

/** Main function */
int main() {
    prime.set();  // intitize '1' to every index
    Sieve(100000000);
    int64_t n;
    std::cin >> n;  // 10006187
    if (prime[n])
        std::cout << "YES\n";
    else
        std::cout << "NO\n";

    return 0;
}
