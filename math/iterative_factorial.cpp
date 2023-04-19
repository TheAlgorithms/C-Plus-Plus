/**
 * @file
 * @brief Iterative implementation of factorial
 *
 * @author [Renjian-buchai](https://github.com/Renjian-buchai)
 */

#include <stdint.h>

#include <cassert>
#include <iostream>

/// @brief Calculates the factorial iteratively.
/// @param n Nth factorial. Maximum=20 because it's the biggest that is accepted
/// without giving a warning.
/// @return Factorial.
/// @warning Assert cannot detect inaccuracies (>20)! because the int overflows.
unsigned long long iterativeFactorial(unsigned int n) {
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

    std::cout << "10! = " << iterativeFactorial(10) << "\n"
              << "Overflow:\n"
                 "21! = "
              << iterativeFactorial(21) << " == (21! \% UINT64_MAX("
              << UINT64_MAX
              << "))\n"
                 "(Overflows 2 times)";

    return 0;
}