/**
 * @file
 * @brief simple implementation of adaption modular multiplicative inverse
 * algorithm
 *
 * @details
 * this algorithm calculate the modular inverse iteratively
 *
 * @ref
 * https://en.wikipedia.org/wiki/Modular_multiplicative_inverse
 */

#include <cassert>   /// for assert
#include <cstdint>   /// for uint64_t type
#include <iostream>  /// for IO operations

/**
 * @brief Function imod
 *  Responsible for calculating the modular inverse from x % y
 * @param x number
 * @param y number
 * @returns the modular inverse
 */
uint64_t imod(uint64_t x, uint64_t y) {  // positive integer expected
    uint64_t aux = 0;                    // auxiliary variable
    uint64_t itr = 0;                    // iteration counter

    do {  // run the algorithm while not find the inverse
        aux = y * itr + 1;
        itr++;
    } while (aux % x);  // while module aux % x is different of zero

    return aux / x;
}

/**
 * @brief  self-test implementations
 * @returns void
 */
static void test() {
    std::cout << "First case testing... \n";
    // for a = 3 and b = 11 return 4
    assert(imod(3, 11) == 4);
    std::cout << "\nPassed!\n";

    std::cout << "Second case testing... \n";
    // for a = 3 and b = 26 return 9
    assert(imod(3, 26) == 9);
    std::cout << "\nPassed!\n";

    std::cout << "Third case testing... \n";
    // for a = 7 and b = 26 return 15
    assert(imod(7, 26) == 15);
    std::cout << "\nPassed!\n";

    std::cout << "\nAll test cases have successfully passed!\n";
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run  self-test implementations
};
