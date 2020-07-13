/**
 * @file
 * @brief Faster computation of Fibonacci series
 *
 * An efficient way to calculate nth fibonacci number faster and simpler than
 * \f$O(n\log n)\f$ method of matrix exponentiation This works by using both
 * recursion and dynamic programming. as 93rd fibonacci exceeds 19 digits, which
 * cannot be stored in a single long long variable, we can only use it till 92nd
 * fibonacci we can use it for 10000th fibonacci etc, if we implement
 * bigintegers. This algorithm works with the fact that nth fibonacci can easily
 * found if we have already found n/2th or (n+1)/2th fibonacci It is a property
 * of fibonacci similar to matrix exponentiation.
 *
 * \author [Krishna Vedala](https://github.com/kvedala)
 * @see fibonacci_large.cpp, fibonacci.cpp, string_fibonacci.cpp
 */

#include <cinttypes>
#include <cstdio>
#include <iostream>

/**
 * maximum number that can be computed - The result after 93 cannot be stored
 * in a `uint64_t` data type.
 */

#define MAX 93

/** Algorithm */
uint64_t fib(uint64_t n) {
    static uint64_t f1 = 1,
                    f2 = 1;  // using static keyword will retain the values of
                             // f1 and f2 for the next function call.

    if (n <= 2)
        return f2;
    if (n >= 93) {
        std::cerr
            << "Cannot compute for n>93 due to limit of 64-bit integers\n";
        return 0;
    }

    uint64_t temp = f2;  // we do not need temp to be static
    f2 += f1;
    f1 = temp;

    return f2;
}

/** Main function */
int main() {
    // Main Function
    for (uint64_t i = 1; i < 93; i++) {
        std::cout << i << " th fibonacci number is " << fib(i) << std::endl;
    }
    return 0;
}
