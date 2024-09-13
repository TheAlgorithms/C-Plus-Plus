/**
 * @file
 * @brief C++ Program to find the modular inverse using [Fermat's Little
 * Theorem](https://en.wikipedia.org/wiki/Fermat%27s_little_theorem)
 *
 * Fermat's Little Theorem state that \f[ϕ(m) = m-1\f]
 * where \f$m\f$ is a prime number.
 * \f{eqnarray*}{
 *  a \cdot x &≡& 1 \;\text{mod}\; m\\
 *  x &≡& a^{-1} \;\text{mod}\; m
 * \f}
 * Using Euler's theorem we can modify the equation.
 *\f[
 * a^{ϕ(m)} ≡ 1 \;\text{mod}\; m
 * \f]
 * (Where '^' denotes the exponent operator)
 *
 * Here 'ϕ' is Euler's Totient Function. For modular inverse existence 'a' and
 * 'm' must be relatively primes numbers. To apply Fermat's Little Theorem is
 * necessary that 'm' must be a prime number. Generally in many competitive
 * programming competitions 'm' is either 1000000007 (1e9+7) or 998244353.
 *
 * We considered m as large prime (1e9+7).
 * \f$a^{ϕ(m)} ≡ 1 \;\text{mod}\; m\f$ (Using Euler's Theorem)
 * \f$ϕ(m) = m-1\f$ using Fermat's Little Theorem.
 * \f$a^{m-1} ≡ 1 \;\text{mod}\; m\f$
 * Now multiplying both side by \f$a^{-1}\f$.
 * \f{eqnarray*}{
 * a^{m-1} \cdot a^{-1} &≡& a^{-1} \;\text{mod}\; m\\
 * a^{m-2} &≡&  a^{-1} \;\text{mod}\; m
 * \f}
 *
 * We will find the exponent using binary exponentiation. Such that the
 * algorithm works in \f$O(\log m)\f$ time.
 *
 * Examples: -
 * * a = 3 and m = 7
 * * \f$a^{-1} \;\text{mod}\; m\f$ is equivalent to
 * \f$a^{m-2} \;\text{mod}\; m\f$
 * * \f$3^5 \;\text{mod}\; 7 = 243 \;\text{mod}\; 7 = 5\f$
 * <br/>Hence, \f$3^{-1} \;\text{mod}\; 7 = 5\f$
 * or \f$3 \times 5  \;\text{mod}\; 7 = 1 \;\text{mod}\; 7\f$
 * (as \f$a\times a^{-1} = 1\f$)
 */

#include <iostream>
#include <vector>

/** Recursive function to calculate exponent in \f$O(\log n)\f$ using binary
 * exponent.
 */
int64_t binExpo(int64_t a, int64_t b, int64_t m) {
    a %= m;
    int64_t res = 1;
    while (b > 0) {
        if (b % 2) {
            res = res * a % m;
        }
        a = a * a % m;
        // Dividing b by 2 is similar to right shift.
        b >>= 1;
    }
    return res;
}

/** Prime check in \f$O(\sqrt{m})\f$ time.
 */
bool isPrime(int64_t m) {
    if (m <= 1) {
        return false;
    } else {
        for (int64_t i = 2; i * i <= m; i++) {
            if (m % i == 0) {
                return false;
            }
        }
    }
    return true;
}

/**
 * Main function
 */
int main() {
    int64_t a, m;
    // Take input of  a and m.
    std::cout << "Computing ((a^(-1))%(m)) using Fermat's Little Theorem";
    std::cout << std::endl << std::endl;
    std::cout << "Give input 'a' and 'm' space separated : ";
    std::cin >> a >> m;
    if (isPrime(m)) {
        std::cout << "The modular inverse of a with mod m is (a^(m-2)) : ";
        std::cout << binExpo(a, m - 2, m) << std::endl;
    } else {
        std::cout << "m must be a prime number.";
        std::cout << std::endl;
    }
}
