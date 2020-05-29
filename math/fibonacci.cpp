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
 */
int fibonacci(unsigned int n)
{
    /* If the input is 0 or 1 just return the same
       This will set the first 2 values of the sequence */
    if (n <= 1)
        return n;

    /* Add the last 2 values of the sequence to get next */
    return fibonacci(n - 1) + fibonacci(n - 2);
}

/// Main function
int main()
{
    int n;
    std::cin >> n;
    assert(n >= 0);
    std::cout << "F(" << n << ")= " << fibonacci(n) << std::endl;
}
