/*
 * C++ Program to find the modular inverse using Fermat's Little Theorem.
 * Fermat's Little Theorem state that => ϕ(m) = m-1, where m is a prime number.
 *
 * (a * x) ≡ 1 mod m.
 * x ≡ (a^(-1)) mod m.
 *
 * Using Euler's theorem we can modify the equation.
 *
 * (a^ϕ(m)) ≡ 1 mod m (Where '^' denotes the exponent operator)
 * Here 'ϕ' is Euler's Totient Function. For modular inverse existence 'a' and 'm' must be relatively primes numbers.
 * To apply Fermat's Little Theorem is necessary that 'm' must be a prime number.
 * Generally in many competitive programming competitions 'm' is either 1000000007 (1e9+7) or 998244353.
 *
 * We considered m as large prime (1e9+7).
 * (a^ϕ(m)) ≡ 1 mod m (Using Euler's Theorem)
 * ϕ(m) = m-1 using Fermat's Little Theorem.
 * (a^(m-1)) ≡ 1 mod m
 * Now multiplying both side by (a^(-1)).
 * (a^(m-1)) * (a^(-1)) ≡  (a^(-1)) mod m
 * (a^(m-2)) ≡  (a^(-1)) mod m
 *
 * We will find the exponent using binary exponentiation. Such that the algorithm works in O(log(m)) time.
 *
 * Example: -
 * a = 3 and m = 7
 * (a^(-1) mod m) is equivalent to (a^(m-2) mod m)
 * (3^(5) mod 7) = (243 mod 7) = 5
 * Hence, ( 3^(-1) mod 7 ) = 5
 * or ( 3 * 5 ) mod 7 = 1 mod 7 (as a*(a^(-1)) = 1)
 */

#include<iostream>
#include<vector>

// Recursive function to calculate exponent in O(log(n)) using binary exponent.
int64_t binExpo(int64_t a, int64_t b, int64_t m) {
    a %= m;
    int64_t res = 1;
    while (b > 0) {
        if (b%2) {
            res = res * a % m;
        }
        a = a * a % m;
        // Dividing b by 2 is similar to right shift.
        b >>= 1;
    }
    return res;
}

// Prime check in O(sqrt(m)) time.
bool isPrime(int64_t m) {
    if (m <= 1) {
        return false;
    } else {
        for (int i=2; i*i <= m; i++) {
            if (m%i == 0) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int64_t a, m;
    // Take input of  a and m.
    std::cout << "Computing ((a^(-1))%(m)) using Fermat's Little Theorem";
    std::cout << std::endl << std::endl;
    std::cout << "Give input 'a' and 'm' space separated : ";
    std::cin >> a >> m;
    if (isPrime(m)) {
        std::cout << "The modular inverse of a with mod m is (a^(m-2)) : ";
        std::cout << binExpo(a, m-2, m) << std::endl;
    } else {
        std::cout << "m must be a prime number.";
        std::cout << std::endl;
    }
}
