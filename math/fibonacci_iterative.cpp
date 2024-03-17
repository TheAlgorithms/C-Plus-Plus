/**
 * @file
 * @brief Iterative computation of the fibonacci series.
 *
 * An efficient way to calculate nth fibonacci number (F_n) faster and
 * simpler than O(nlog n) method of matrix exponentiation using
 * iteration.
 *
 * The 94th fibonacci number exceeds the size of ant unsigned 64-bit integer,
 * causing it to overflow.
 *
 * According to Wolfram Alpha, the Fibonacci number function would be F_n,
 * where n is the position of the number in the Fibonacci sequence.
 *
 * @see fibonacci_large.cpp, fibonacci.cpp, string_fibonacci.cpp
 */

#include <cassert>    /// For assert
#include <cstdint>    /// For uint8_t, uint64_t
#include <exception>  /// For std::invalid_argument
#include <iostream>   /// For std::cout

/**
 * @namespace
 * @brief Mathematical algorithms
 */
namespace math {

/**
 * @brief Calculates the nth fibonacci number iteratively.
 * @param n nth Fibonacci number
 * @return nth Fibonacci number
 * @note F_n = 1 if n <= 2
 * @warning n <= 93, because 93 is the maximum value of the Fibonacci sequence
 * that fits in a 64-bit unsigned integer.
 */
uint64_t fibonacci(uint8_t n) {
    const uint8_t fibonacciMax = 93;

    // By definition, when n <= 2, F_n = 1
    if (n <= 2) {
        return 1;
    }

    if (n > fibonacciMax) {
        throw std::invalid_argument("Maximum value of n is 93.");
    }

    // Value to return
    uint64_t f1 = 1;

    {
        // Temporary values.
        uint64_t temp = 0, f2 = 1;

        // 2-indexed because if i < 2, you end up finding F_(n + 2 - i)
        // instead of F_n.
        for (uint8_t i = 2; i < n; ++i) {
            temp = f1;
            f1 += f2;
            f2 = temp;
        }
    }

    return f1;
}

}  // namespace math

/**
 * @brief Self-test implementations to test fibonacci function.
 * @note There is 1 special case: n <= 2
 * @note There is 1 exceptional case: n > 93
 */
static void test() {
    // Special test case.
    std::cout << "Special case tests:\n"
                 "Input: 1\n"
                 "Expected output: 1\n\n";
    assert(math::fibonacci(1) == 1);

    std::cout << "Input: 2\n"
                 "Expected output: 1\n\n";
    assert(math::fibonacci(2) == 1);

    // Small test case.
    std::cout << "Small case test:\n"
                 "Input: 10\n"
                 "Expected output: 55\n\n";
    assert(math::fibonacci(10) == 55);

    // Medium test case.
    std::cout << "Medium case test:\n"
                 "Input: 45\n"
                 "Expected output: 1134903170\n\n";
    assert(math::fibonacci(45) == 1134903170);

    // Max test case.
    // Note: Throws a warning because the value is greater than INT64_MAX. Still
    // fits in UINT64_MAX, though.
    std::cout << "Max case test:\n"
                 "Input: 93\n"
                 "Expected output: 12200160415121876738\n\n";
    assert(math::fibonacci(93) == 12200160415121876738);

    // Exception test case.
    std::cout << "Exception case tests:\n"
                 "Input: 93\n"
                 "Expected output: Exception thrown successfully.\n"
                 "Result: ";
    try {
        math::fibonacci(94);
    } catch (std::invalid_argument& e) {
        std::cout << "Exception thrown successfully \nContent: " << e.what()
                  << "\n\n";
    }

    std::cout << "All tests passed successfully.";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test(); // run self-test implementations
    return 0;
}
