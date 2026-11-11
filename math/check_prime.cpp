/**
 * @file
 * @brief
 * A simple program to check if the given number is
 * [Prime](https://en.wikipedia.org/wiki/Primality_test) or not.
 * @details
 * A prime number is any number that can be divided only by itself and 1. It
 * must be positive and a whole number, therefore any prime number is part of
 * the set of natural numbers. The majority of prime numbers are even numbers,
 * with the exception of 2. This algorithm finds prime numbers using this
 * information. additional ways to solve the prime check problem:
 * https://cp-algorithms.com/algebra/primality_tests.html#practice-problems
 * @author [Omkar Langhe](https://github.com/omkarlanghe)
 * @author [ewd00010](https://github.com/ewd00010)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @brief Mathematical algorithms
 * @namespace
 */
namespace math {
/**
 * @brief Function to check if the given number is prime or not.
 * @param num number to be checked.
 * @return true if number is a prime
 * @return false if number is not a prime.
 */
bool is_prime(long long num) {
    //i fix  a  x <=1 false
    if(num <= 1) return false;
    //set famous primary primes numbers if it false
    const size_t number_of_famous_primes_number = 7;
    const short famous_primes_number[number_of_famous_primes_number] = {2,3,5,7,11,13,17};
    //filter is devisible number
    for (size_t i = 0; i < number_of_famous_primes_number; i++) 
    {
        //filter is number famous prime number
        if(num == famous_primes_number[i]) return true;
        //filter number is divisible by famous prime number example :{17777777775 % 5 =0 that 0} is devisible
        if((num % famous_primes_number[i]) ==0) return false; 
    }
    /*i set for loop by fix number is prime*/
    for (size_t i = 19; i*i <= num; i+=6) if(num%i == 0|| num%(i+4)==0) return false;
    //that  return true for all exeption
    return true;
    
}
}  // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    assert(math::is_prime(1) == false);
    assert(math::is_prime(2) == true);
    assert(math::is_prime(3) == true);
    assert(math::is_prime(4) == false);
    assert(math::is_prime(-4) == false);
    assert(math::is_prime(7) == true);
    assert(math::is_prime(-7) == false);
    assert(math::is_prime(19) == true);
    assert(math::is_prime(50) == false);
    assert(math::is_prime(115249) == true);
    assert(math::is_prime(1565)==false);
    assert(math::is_prime(123)== false);
    assert(math::is_prime(123456789123456789)==false );
    assert(math::is_prime(1555555555555555555)==false);
    assert(math::is_prime(199999999999999995L)==false);
    assert(math::is_prime(529)==false);
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
