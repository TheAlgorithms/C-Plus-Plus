/**
 * @file
 * @brief [Factorial](https://en.wikipedia.org/wiki/Factorial) calculation using
 * recursion and [memoization](https://en.wikipedia.org/wiki/Memoization)
 * @details
 * This program computes the factorial of a non-negative integer using recursion
 * with memoization (top-down dynamic programming). It stores intermediate
 * results to avoid redundant calculations for improved efficiency.
 *
 * Memoization is a form of caching where the result to an expensive function
 * call is stored and returned. Example: Input: n = 5 Output: 120
 *
 * Explanation: 5! = 5 × 4 × 3 × 2 × 1 = 120
 *
 * The program uses a recursive function which caches computed
 * results in a memo array to avoid recalculating factorials for the same
 * numbers.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <cassert>  // For test cases
#include <cstdint>  // For uint64_t
#include <vector>   // For std::vector

class MemorisedFactorial {
    std::vector<std::uint64_t> known_values = {1};

 public:
    /**
     * @note This function was intentionally written as recursive
     * and it does not handle overflows.
     * @returns factorial of n
     */
    std::uint64_t operator()(std::uint64_t n) {
        if (n >= this->known_values.size()) {
            this->known_values.push_back(n * this->operator()(n - 1));
        }
        return this->known_values.at(n);
    }
};

void test_MemorisedFactorial_in_order() {
    auto factorial = MemorisedFactorial();
    assert(factorial(0) == 1);
    assert(factorial(1) == 1);
    assert(factorial(5) == 120);
    assert(factorial(10) == 3628800);
}

void test_MemorisedFactorial_no_order() {
    auto factorial = MemorisedFactorial();
    assert(factorial(10) == 3628800);
}

/**
 * @brief Main function to run tests
 * @returns 0 on program success
 */
int main() {
    test_MemorisedFactorial_in_order();
    test_MemorisedFactorial_no_order();
    return 0;
}
