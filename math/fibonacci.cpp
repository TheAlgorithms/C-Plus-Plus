/**
 * @file
 * @brief Generate fibonacci sequence
 *
 * Calculate the the value on Fibonacci's sequence given an
 * integer as input.
 * \f[\text{fib}(n) = \text{fib}(n-1) + \text{fib}(n-2)\f]
 *
 * @see fibonacci_large.cpp, fibonacci_fast.cpp, string_fibonacci.cpp
 */
#include <cassert>
#include <iostream>

/**
 * Recursively compute sequences
 * @param n input
 * @returns n-th element of the Fbinacci's sequence
 */
uint64_t fibonacci(uint64_t n) {
    /* If the input is 0 or 1 just return the same
       This will set the first 2 values of the sequence */
    if (n <= 1) {
        return n;
    }

    /* Add the last 2 values of the sequence to get next */
    return fibonacci(n - 1) + fibonacci(n - 2);
}

/**
 * Function for testing the fibonacci() function with a few
 * test cases and assert statement.
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
}
