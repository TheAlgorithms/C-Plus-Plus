/**
 * @file
 * @brief Iterative implementation of factorial
 *
 * @author [Renjian-buchai](https://github.com/Renjian-buchai)
 */

#include <stdint.h>

#include <cassert>
#include <exception>
#include <iostream>

/// @brief Calculates the factorial iteratively.
/// @param n Nth factorial.
/// @return Factorial.
/// @warning Maximum=20 because 21! returns 1.419e+19, which is not 21! but
/// (21! % UINT64_MAX) after overflowing twice. No 128-bit variables in C++, so
/// unless you use [abseil](https://abseil.io) or similar libraries, maximum is
/// 20!.
unsigned long long iterativeFactorial(unsigned short n) {
    if (n > 20)
        throw new std::invalid_argument("Maximum n value is 20");

    /// 1 because 0! == 1
    unsigned long long accumulator = 1;

    while (n > 0) {
        accumulator *= n;
        --n;
    }

    return accumulator;
}

static void test() {
    /// Exception case
    assert(iterativeFactorial(0) == 1);

    /// Base case
    assert(iterativeFactorial(1) == 1);

    /// Small case
    assert(iterativeFactorial(5) == 120);

    /// Medium case
    assert(iterativeFactorial(10) == 3628800);

    /// Maximum case
    unsigned long long f20 = 2432902008176640000;
    assert(iterativeFactorial(20) == f20);
}

int main() {
    test();

    std::cout << "10! = " << iterativeFactorial(10);

    return 0;
}