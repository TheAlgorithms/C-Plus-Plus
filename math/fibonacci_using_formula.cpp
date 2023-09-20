/**
 * Resource : https://math.hmc.edu/funfacts/fibonacci-number-formula/
 * @file
 * @brief Generate fibonacci sequence
 * @see fibonacci_using_formula.cpp
 * author : dev-madhurendra
 * git id : https://github.com/dev-madhurendra
 */
#include <cassert>
#include <iostream>
#include <cmath>

/**
 * Function to calculate the nth Fibonacci number using the formula.
 * @param n The input value for which to calculate the Fibonacci number.
 * @returns The nth Fibonacci number.
 */
uint64_t fibonacci(uint64_t n) {
    const double sqrt5 = std::sqrt(5);
    const double phi = (1 + sqrt5) / 2;
    const double psi = (1 - sqrt5) / 2;

    double result = (std::pow(phi, n) - std::pow(psi, n)) / sqrt5;

    // Round the result to the nearest integer
    return static_cast<uint64_t>(std::round(result));
}

/**
 * Function for testing the fibonacci() function with a few
 * test cases and assert statements.
 * @returns `void`
 */
static void test() {
    uint64_t test_case_1 = fibonacci(0);
    assert(test_case_1 == 0);
    std::cout << "Passed Test 1!" << std::endl;

    uint64_t test_case_2 = fibonacci(1);
    assert(test_case_2 == 1);
    std::cout << "Passed Test 2!" << std::endl;

    uint64_t test_case_3 = fibonacci(2);
    assert(test_case_3 == 1);
    std::cout << "Passed Test 3!" << std::endl;

    uint64_t test_case_4 = fibonacci(3);
    assert(test_case_4 == 2);
    std::cout << "Passed Test 4!" << std::endl;

    uint64_t test_case_5 = fibonacci(4);
    assert(test_case_5 == 3);
    std::cout << "Passed Test 5!" << std::endl;

    uint64_t test_case_6 = fibonacci(15);
    assert(test_case_6 == 610);
    std::cout << "Passed Test 6!" << std::endl << std::endl;
}

/// Main function
int main() {
    test();
    int n = 0;
    std::cin >> n;
    assert(n >= 0);
    std::cout << "F(" << n << ")= " << fibonacci(n) << std::endl;
    return 0;
}
