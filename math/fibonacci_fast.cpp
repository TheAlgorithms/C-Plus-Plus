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
 * @see fibonacci_large.cpp, fibonacci.cpp, string_fibonacci.cpp
 */

#include <cinttypes>
#include <cstdio>
#include <iostream>

/** maximum number that can be computed - The result after 93 cannot be stored
 * in a `uint64_t` data type. */
const uint64_t MAX = 93;

/** Array of computed fibonacci numbers */
uint64_t f[MAX] = {0};

/** Algorithm */
uint64_t fib(uint64_t n) {
    if (n == 0)
        return 0;
    if (n == 1 || n == 2)
        return (f[n] = 1);

    if (f[n])
        return f[n];

    uint64_t k = (n % 2 != 0) ? (n + 1) / 2 : n / 2;

    f[n] = (n % 2 != 0) ? (fib(k) * fib(k) + fib(k - 1) * fib(k - 1))
                        : (2 * fib(k - 1) + fib(k)) * fib(k);
    return f[n];
}

/** Main function */
int main() {
    // Main Function
    for (uint64_t i = 1; i < 93; i++) {
        std::cout << i << " th fibonacci number is " << fib(i) << std::endl;
    }
    return 0;
}
