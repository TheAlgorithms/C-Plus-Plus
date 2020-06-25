/**
 * @file
 * @brief Compute [double
 * factorial](https://en.wikipedia.org/wiki/Double_factorial): \f$n!!\f$
 *
 * Double factorial of a non-negative integer `n`, is defined as the product of
 * all the integers from 1 to n that have the same parity (odd or even) as n.
 * <br/>It is also called as semifactorial of a number and is denoted by
 * \f$n!!\f$
 */

#include <cassert>
#include <iostream>

/** Compute double factorial using iterative method
 */
uint64_t double_factorial_iterative(uint64_t n) {
    uint64_t res = 1;
    for (uint64_t i = n;; i -= 2) {
        if (i == 0 || i == 1)
            return res;
        res *= i;
    }
    return res;
}

/** Compute double factorial using resursive method.
 * <br/>Recursion can be costly for large numbers.
 */
uint64_t double_factorial_recursive(uint64_t n) {
    if (n <= 1)
        return 1;
    return n * double_factorial_recursive(n - 2);
}

/** Wrapper to run tests using both recursive and iterative implementations.
 * The checks are only valid in debug builds due to the use of `assert()`
 * statements.
 * \param [in] n number to check double factorial for
 * \param [in] expected expected result
 */
void test(uint64_t n, uint64_t expected) {
    assert(double_factorial_iterative(n) == expected);
    assert(double_factorial_recursive(n) == expected);
}

/**
 * Test implementations
 */
void tests() {
    std::cout << "Test 1:\t n=5\t...";
    test(5, 15);
    std::cout << "passed\n";

    std::cout << "Test 2:\t n=15\t...";
    test(15, 2027025);
    std::cout << "passed\n";

    std::cout << "Test 3:\t n=0\t...";
    test(0, 1);
    std::cout << "passed\n";
}

/**
 * Main function
 */
int main() {
    tests();
    return 0;
}
