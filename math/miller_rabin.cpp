/**
 * Copyright 2020 @author tjgurwara99
 * @file
 *
 * A basic implementation of Miller-Rabin primality test.
 */

#include <cassert>
#include <iostream>
#include <random>
#include <vector>

/**
 * Function to give a binary representation of a number in reverse order
 * @param num integer number that we want to convert
 * @return result vector of the number input in reverse binary
 */
template <typename T>
std::vector<T> reverse_binary(T num) {
    std::vector<T> result;
    T temp = num;
    while (temp > 0) {
        result.push_back(temp % 2);
        temp = temp / 2;
    }
    return result;
}

/**
 * Function for modular exponentiation.
 * This function is an efficient modular exponentiation function.
 * It can be used with any big integer library such as Boost multiprecision
 * to give result any modular exponentiation problem relatively quickly.
 * @param base number being raised to a power as integer
 * @param rev_binary_exponent reverse binary of the power the base is being
 * raised to
 * @param mod modulo
 * @return r the modular exponentiation of \f$a^{n} \equiv r \mod{m}\f$ where
 * \f$n\f$ is the base 10 representation of rev_binary_exponent and \f$m = mod
 * \f$ parameter.
 */
template <typename T>
T modular_exponentiation(T base, const std::vector<T> &rev_binary_exponent,
                         T mod) {
    if (mod == 1)
        return 0;
    T b = 1;
    if (rev_binary_exponent.size() == 0)
        return b;
    T A = base;
    if (rev_binary_exponent[0] == 1)
        b = base;

    for (typename std::vector<T>::const_iterator it =
             rev_binary_exponent.cbegin() + 1;
         it != rev_binary_exponent.cend(); ++it) {
        A = A * A % mod;
        if (*it == 1)
            b = A * b % mod;
    }
    return b;
}

/** Function for testing the conditions that are satisfied when a number is
 * prime.
 * 	@param d number such that \f$d \cdot 2^r = n - 1\f$ where \f$n = num\f$
 * parameter and \f$r \geq 1\f$
 * 	@param num number being tested for primality.
 * 	@return 'false' if n is composite
 * 	@return 'true' if n is (probably) prime.
 */
template <typename T>
bool miller_test(T d, T num) {
    // random number seed
    std::random_device rd_seed;
    // random number generator
    std::mt19937 gen(rd_seed());
    // Uniformly distributed range [2, num - 2] for random numbers
    std::uniform_int_distribution<> distribution(2, num - 2);
    // Random number generated in the range [2, num -2].
    T random = distribution(gen);
    // vector for reverse binary of the power
    std::vector<T> power = reverse_binary(d);
    // x = random ^ d % num
    T x = modular_exponentiation(random, power, num);
    // miller conditions
    if (x == 1 || x == num - 1) {
        return true;
    }

    while (d != num - 1) {
        x = (x * x) % num;
        d *= 2;
        if (x == 1) {
            return false;
        }
        if (x == num - 1) {
            return true;
        }
    }
    return false;
}

/**
 * Function that test (probabilistically) whether a given number is a prime
 * based on the Miller-Rabin Primality Test.
 * @param num number to be tested for primality.
 * @param repeats number of repetitions for the test to increase probability of
 * correct result.
 * @return 'false' if num is composite
 * @return 'true' if num is (probably) prime
 *
 * \detail
 * First we check whether the num input is less than 4, if so we can determine
 * whether this is a prime or composite by checking for 2 and 3.
 * Next we check whether this num is odd (as all primes greater than 2 are odd).
 * Next we write our num in the following format \f$num = 2^r \cdot d + 1\f$.
 * After finding r and d for our input num, we use for loop repeat number of
 * times inside which we check the miller conditions using the function
 * miller_test. If miller_test returns false then the number is composite After
 * the loop finishes completely without issuing a false return call, we can
 * conclude that this number is probably prime.
 */
template <typename T>
bool miller_rabin_primality_test(T num, T repeats) {
    if (num <= 4) {
        // If num == 2 or num == 3 then prime
        if (num == 2 || num == 3) {
            return true;
        } else {
            return false;
        }
    }
    // If num is even then not prime
    if (num % 2 == 0) {
        return false;
    }
    // Finding d and r in num = 2^r * d + 1
    T d = num - 1, r = 0;
    while (d % 2 == 0) {
        d = d / 2;
        r++;
    }

    for (T i = 0; i < repeats; ++i) {
        if (!miller_test(d, num)) {
            return false;
        }
    }
    return true;
}

/**
 * Functions for testing the miller_rabin_primality_test() function with some
 * assert statements.
 */
void tests() {
    // First test on 2
    assert(((void)"2 is prime but function says otherwise.\n",
            miller_rabin_primality_test(2, 1) == true));
    std::cout << "First test passes." << std::endl;
    // Second test on 5
    assert(((void)"5 should be prime but the function says otherwise.\n",
            miller_rabin_primality_test(5, 3) == true));
    std::cout << "Second test passes." << std::endl;
    // Third test on 23
    assert(((void)"23 should be prime but the function says otherwise.\n",
            miller_rabin_primality_test(23, 3) == true));
    std::cout << "Third test passes." << std::endl;
    // Fourth test on 16
    assert(((void)"16 is not a prime but the function says otherwise.\n",
            miller_rabin_primality_test(16, 3) == false));
    std::cout << "Fourth test passes." << std::endl;
    // Fifth test on 27
    assert(((void)"27 is not a prime but the function says otherwise.\n",
            miller_rabin_primality_test(27, 3) == false));
    std::cout << "Fifth test passes." << std::endl;
}

/**
 * Main function
 */
int main() {
    tests();
    return 0;
}
