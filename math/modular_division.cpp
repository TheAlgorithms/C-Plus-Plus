/**
 * @file
 * @brief An algorithm to divide two numbers under modulo p [Modular
 * Division](https://www.geeksforgeeks.org/modular-division)
 * @details To calculate division of two numbers under modulo p
 * Modulo operator is not distributive under division, therefore
 * we first have to calculate the inverse of divisor using
 * [Fermat's little
 theorem](https://en.wikipedia.org/wiki/Fermat%27s_little_theorem)
 * Now, we can multiply the dividend with the inverse of divisor
 * and modulo is distributive over multiplication operation.
 * Let,
 * We have 3 numbers a, b, p
 * To compute (a/b)%p
 * (a/b)%p ≡ (a*(inverse(b)))%p ≡ ((a%p)*inverse(b)%p)%p
 * NOTE: For the existence of inverse of 'b', 'b' and 'p' must be coprime
 * For simplicity we take p as prime
 * Time Complexity: O(log(b))
 * Example: ( 24 / 3 ) % 5 => 8 % 5 = 3 --- (i)
            Now the inverse of 3 is 2
            (24 * 2) % 5 = (24 % 5) * (2 % 5) = (4 * 2) % 5 = 3 --- (ii)
            (i) and (ii) are equal hence the answer is correct.
 * @see modular_inverse_fermat_little_theorem.cpp, modular_exponentiation.cpp
 * @author [Shubham Yadav](https://github.com/shubhamamsa)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
/**
 * @namespace modular_division
 * @brief Functions for [Modular
 * Division](https://www.geeksforgeeks.org/modular-division) implementation
 */
namespace modular_division {
/**
 * @brief This function calculates a raised to exponent b under modulo c using
 * modular exponentiation.
 * @param a integer base
 * @param b unsigned integer exponent
 * @param c integer modulo
 * @return a raised to power b modulo c
 */
uint64_t power(uint64_t a, uint64_t b, uint64_t c) {
    uint64_t ans = 1;  /// Initialize the answer to be returned
    a = a % c;         /// Update a if it is more than or equal to c
    if (a == 0) {
        return 0;  /// In case a is divisible by c;
    }
    while (b > 0) {
        /// If b is odd, multiply a with answer
        if (b & 1) {
            ans = ((ans % c) * (a % c)) % c;
        }
        /// b must be even now
        b = b >> 1;  /// b = b/2
        a = ((a % c) * (a % c)) % c;
    }
    return ans;
}

/**
 * @brief This function calculates modular division
 * @param a integer dividend
 * @param b integer divisor
 * @param p integer modulo
 * @return a/b modulo c
 */
uint64_t mod_division(uint64_t a, uint64_t b, uint64_t p) {
    uint64_t inverse = power(b, p - 2, p) % p;  /// Calculate the inverse of b
    uint64_t result =
        ((a % p) * (inverse % p)) % p;  /// Calculate the final result
    return result;
}
}  // namespace modular_division
}  // namespace math

/**
 * Function for testing power function.
 * test cases and assert statement.
 * @returns `void`
 */
static void test() {
    uint64_t test_case_1 = math::modular_division::mod_division(8, 2, 2);
    assert(test_case_1 == 0);
    std::cout << "Test 1 Passed!" << std::endl;
    uint64_t test_case_2 = math::modular_division::mod_division(15, 3, 7);
    assert(test_case_2 == 5);
    std::cout << "Test 2 Passed!" << std::endl;
    uint64_t test_case_3 = math::modular_division::mod_division(10, 5, 2);
    assert(test_case_3 == 0);
    std::cout << "Test 3 Passed!" << std::endl;
    uint64_t test_case_4 = math::modular_division::mod_division(81, 3, 5);
    assert(test_case_4 == 2);
    std::cout << "Test 4 Passed!" << std::endl;
    uint64_t test_case_5 = math::modular_division::mod_division(12848, 73, 29);
    assert(test_case_5 == 2);
    std::cout << "Test 5 Passed!" << std::endl;
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();  // execute the tests
    return 0;
}
