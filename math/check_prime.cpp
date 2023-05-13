/**
 * @file
 * @brief
 * A simple program to check if the given number is a prime or not.
 * https://en.wikipedia.org/wiki/Primality_test
 * @details
 * A prime number is any number that can be divided only by itself and 1. It must
 * be positive and a whole number, therefore any prime number is part of the
 * set of natural numbers. The majority of prime numbers are even numbers, with
 * the exception of 2. This algorithm finds prime numbers using this information.
 * additional ways to solve the prime check problem:
 * https://cp-algorithms.com/algebra/primality_tests.html#practice-problems
 * @author [Omkar Langhe](https://github.com/omkarlanghe)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

 * @brief Function to check if the given number is prime or not.
 * @param num number to be checked.
 * @return true if number is a prime
 * @return false if number is not a prime.
 */
namespace math {
    bool is_prime(long long num) {
        /*!
         * Reduce all possibilities of a number which cannot be prime with the first
         * 3 if, else if conditionals. Example: Since no even number, except 2 can
         * be a prime number and the next prime we find after our checks is 5,
         * we will start the for loop with i = 5. then for each loop we increment
         * i by +6 and check if i or i+2 is a factor of the number; if it's a factor
         * then we will return false. otherwise, true will be returned after the
         * loop terminates at the terminating condition which is i*i <= num
         */
        if (num <= 1) {
            return false;
        } else if (num == 2 || num == 3) {
            return true;
        } else if (num % 2 == 0 || num % 3 == 0) {
            return false;
        } else {
            for (long long i = 5; i * i <= num; i = i + 6) {
                if (num % i == 0 || num % (i + 2) == 0) {
                    return false;
                }
            }
        }
        return true;
    }
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    assert(is_prime(1) == false);
    assert(is_prime(2) == true);
    assert(is_prime(3) == true);
    assert(is_prime(4) == false);
    assert(is_prime(-4) == false);
    assert(is_prime(7) == true);
    assert(is_prime(-7) == false);
    assert(is_prime(19) == true);
    assert(is_prime(50) == false);
    assert(is_prime(115249) == true);

    std::cout << "All tests have successfully passed!" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // perform self-tests implementations
    return 0;
}
