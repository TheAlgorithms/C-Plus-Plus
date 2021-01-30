/**
 * @file
 * @brief C++ Program to calculate the number of positive divisors
 *
 * This algorithm uses the prime factorization approach.
 * Any positive integer can be written as a product of its prime factors.
 * <br/>Let \f$N = p_1^{e_1} \times p_2^{e_2} \times\cdots\times p_k^{e_k}\f$
 * where \f$p_1,\, p_2,\, \dots,\, p_k\f$ are distinct prime factors of \f$N\f$ and
 * \f$e_1,\, e_2,\, \dots,\, e_k\f$ are respective positive integer exponents.
 * <br/>Each positive divisor of \f$N\f$ is in the form
 * \f$p_1^{g_1}\times p_2^{g_2}\times\cdots\times p_k^{g_k}\f$
 * where \f$0\le g_i\le e_i\f$ are integers for all \f$1\le i\le k\f$.
 * <br/>Finally, there are \f$(e_1+1) \times (e_2+1)\times\cdots\times (e_k+1)\f$
 * positive divisors of \f$N\f$ since we can choose every \f$g_i\f$
 * independently.
 *
 * Example:
 * <br/>\f$N = 36 = (3^2 \cdot 2^2)\f$
 * <br/>\f$\mbox{number_of_positive_divisors}(36) = (2+1) \cdot (2+1) = 9\f$.
 * <br/>list of positive divisors of 36 = 1, 2, 3, 4, 6, 9, 12, 18, 36.
 *
 * Similarly, for N = -36 the number of positive divisors remain same.
**/

#include <cassert>
#include <iostream>

/**
 * Function to compute the number of positive divisors.
 * @param n number to compute divisors for
 * @returns number of positive divisors of n (or 1 if n = 0)
 */
int number_of_positive_divisors(int n) {
    if (n < 0) {
        n = -n; // take the absolute value of n
    }

    int number_of_divisors = 1;

    for (int i = 2; i * i <= n; i++) {
        // This part is doing the prime factorization.
        // Note that we cannot find a composite divisor of n unless we would
        // already previously find the corresponding prime divisor and dvided
        // n by that prime. Therefore, all the divisors found here will
        // actually be primes.
        // The loop terminates early when it is left with a number n which
        // does not have a divisor smaller or equal to sqrt(n) - that means
        // the remaining number is a prime itself.
        int prime_exponent = 0;
        while (n % i == 0) {
            // Repeatedly divide n by the prime divisor n to compute
            // the exponent (e_i in the algorithm description).
            prime_exponent++;
            n /= i;
        }
        number_of_divisors *= prime_exponent + 1;
    }
    if (n > 1) {
        // In case the remaining number n is a prime number itself
        // (essentially p_k^1) the final answer is also multiplied by (e_k+1).
        number_of_divisors *= 2;
    }

    return number_of_divisors;
}

/**
 * Test implementations
 */
void tests() {
    assert(number_of_positive_divisors(36) == 9);
    assert(number_of_positive_divisors(-36) == 9);
    assert(number_of_positive_divisors(1) == 1);
    assert(number_of_positive_divisors(2011) == 2); // 2011 is a prime
    assert(number_of_positive_divisors(756) == 24); // 756 = 2^2 * 3^3 * 7
}

/**
 * Main function
 */
int main() {
    tests();
    int n;
    std::cin >> n;
    if (n == 0) {
        std::cout << "All non-zero numbers are divisors of 0 !" << std::endl;
    } else {
        std::cout << "Number of positive divisors is : ";
        std::cout << number_of_positive_divisors(n) << std::endl;
    }
    return 0;
}
