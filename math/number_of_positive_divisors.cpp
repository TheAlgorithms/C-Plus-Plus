/// C++ Program to calculate number of divisors.

#include<iostream>
#include<vector>

/**
 * This algorithm use the prime factorization approach.
 * Any number can be written in multiplication of its prime factors.
 * Let N = P1^E1 * P2^E2 ... Pk^Ek
 * Therefore. number-of-divisors(N) = (E1+1) * (E2+1) ... (Ek+1).
 * Where P1, P2 ... Pk are prime factors and E1, E2 ... Ek are exponents respectively.
 *
 * Example:-
 * N = 36
 * 36 = (3^2 * 2^2)
 * number_of_positive_divisors(36) = (2+1) * (2+1) = 9.
 * list of positive divisors of 36 = 1, 2, 3, 4, 6, 9, 12, 18, 36.
 *
 * Similarly if N is -36 at that time number of positive divisors remain same.
 *
 * Example:-
 * N = -36
 * -36 = -1 * (3^2 * 2^2)
 * number_of_positive_divisors(-36) = (2+1) * (2+1) = 9.
 * list of positive divisors of -36 = 1, 2, 3, 4, 6, 9, 12, 18, 36.
 *
**/

int number_of_positive_divisors(int n) {
    std::vector<int> prime_exponent_count;
    for (int i=2; i*i <= n; i++) {
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

    for (int i=0; i < prime_exponent_count.size(); i++) {
        divisors_count = divisors_count * (prime_exponent_count[i]+1);
    }

    return divisors_count;
}

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
