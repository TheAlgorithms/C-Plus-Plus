// C++ Program to find the modular inverse using Fermat's Little Theorem.
// Fermat's Little Theorem state that => ϕ(m) = m-1, where m is prime number.
/*
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
 */

#include<iostream>
#include<vector>

// m is large prime number.
const int64_t m = 1000000007;

// Recursive function to calculate exponent in O(log(n)) using binary exponent.
int64_t binExpo(int64_t a, int64_t b) {
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

int main() {

    int64_t a;
    /*
        Take input of  a.
        (A number for which we want to find modular inverse with m)
    */

    std::cout << "Give input a for computing ((a^(-1))%(m)) : ";
    std::cin >> a;

    std::cout << "The modular inverse of a with mod m is (a^(m-2)) : ";
    std::cout << binExpo(a, m-2) << std::endl;
}




