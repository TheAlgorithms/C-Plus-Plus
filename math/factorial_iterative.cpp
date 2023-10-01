/**
 * Factorial of a number in iterative way
 * e.g. factorial(5) = 5*4*3*2*1 = 1*2*3*4*5
 */

#include <cassert>   /// for assert
#include <iostream>  /// for I/O operations

/**
 * @namespace
 * @brief Mathematical algorithms
 */
namespace math {

/**
 * @brief function to find factorial of given number
 * @param n is the number which is to be factorialized
 * @warning Maximum value for the parameter is 20 as 21!
 * cannot be represented in 64 bit unsigned int
 */
uint64_t factorial(uint8_t n) {
    uint64_t fact = 1;
    if(n==0)
        return 1;
    
    for(int i=1; i<=n; ++i){
        fact *= i;
    }
    return fact;
}  // namespace math
}

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    assert(math::factorial(1) == 1);
    assert(math::factorial(0) == 1);
    assert(math::factorial(5) == 120);
    assert(math::factorial(10) == 3628800);
    assert(math::factorial(20) == 2432902008176640000);
    std::cout << "All tests have passed successfully!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // run self-test implementations
    return 0;
}
