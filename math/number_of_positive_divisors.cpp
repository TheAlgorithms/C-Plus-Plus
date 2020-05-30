/**
 * @file
 * @brief C++ Program to calculate number of divisors
 *
 * This algorithm use the prime factorization approach.
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

#include <iostream>
#include <vector>

/**
 * Algorithm
 */
int number_of_positive_divisors(int n) {
    std::vector<int> prime_exponent_count;
    for (int i = 2; i * i <= n; i++) {
        int prime_count = 0;
        while (n % i == 0) {
            prime_count += 1;
            n /= i;
        }
        if (prime_count != 0) {
            prime_exponent_count.push_back(prime_count);
        }
    }
    if (n > 1) {
        prime_exponent_count.push_back(1);
    }

    int divisors_count = 1;

    for (int i = 0; i < prime_exponent_count.size(); i++) {
        divisors_count = divisors_count * (prime_exponent_count[i] + 1);
    }

    return divisors_count;
}

/**
 * Main function
 */
int main() {
    int n;
    std::cin >> n;
    if (n < 0) {
        n = -n;
    }
    if (n == 0) {
        std::cout << "All non-zero numbers are divisors of 0 !" << std::endl;
    } else {
        std::cout << "Number of positive divisors is : ";
        std::cout << number_of_positive_divisors(n) << std::endl;
    }
}
