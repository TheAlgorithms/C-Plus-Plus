/**
 * @file
 * @brief C++ Program to calculate number of divisors
 *
 * This algorithm uses the prime factorization approach.
 * Any number can be written in multiplication of its prime factors.
 * <br/>Let N = P1^E1 * P2^E2 ... Pk^Ek
 * <br/>Therefore. number-of-divisors(N) = (E1+1) * (E2+1) ... (Ek+1).
 * <br/>Where P1, P2 ... Pk are prime factors and E1, E2 ... Ek are exponents
respectively.
 *
 * Example:-
 * <br/>N = 36
 * <br/>36 = (3^2 * 2^2)
 * <br/>number_of_positive_divisors(36) = (2+1) * (2+1) = 9.
 * <br/>list of positive divisors of 36 = 1, 2, 3, 4, 6, 9, 12, 18, 36.
 *
 * Similarly if N is -36 at that time number of positive divisors remain same.
 *
 * Example:-
 * <br/>N = -36
 * <br/>-36 = -1 * (3^2 * 2^2)
 * <br/>number_of_positive_divisors(-36) = (2+1) * (2+1) = 9.
 * <br/>list of positive divisors of -36 = 1, 2, 3, 4, 6, 9, 12, 18, 36.
 *
**/

#include <cassert>
#include <iostream>
#include <vector>

/**
 * Algorithm
 */
int number_of_positive_divisors(int n) {
    if (n < 0) {
        n = -n;
    }

    int divisors_count = 1;
    for (int i = 2; i * i <= n; i++) {
        int prime_count = 0;
        while (n % i == 0) {
            prime_count++;
            n /= i;
        }
        divisors_count *= prime_count + 1;
    }
    if (n > 1) {
        divisors_count *= 2;
    }

    return divisors_count;
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
}
