/**
 * @file
 * @brief Implementation to find n th fibonacci_number
 * (https://en.wikipedia.org/wiki/Fibonacci_number)
 *
 * @details
 * The Fibonacci sequence is a series of numbers where each number is the
 * sum of the two preceding ones, starting with 0 and 1.
 *
 * ### Algorithm
 * The idea of the algorithm is to find the ith fibonacci number.
 * DP state : F(i) = ith fibonacci number
 * DP state transition :
 *      F(i) = F(i-1) + F(i-2)
 * DP base case :
 *      F(0) = 0
 *      F(1) = 1
 * Space reduction :
 *  * for i the fibonacci store only i-1 th and i-2 th state.
 * @author [Santo Cariotti](https://github.com/dcariotti)
 * @author [tapasrnk](https://github.com/tapasrnk)
 */
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <vector>    /// for storing the values of nth fibonacci number
/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */
namespace dynamic_programming {
int fib(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 0;
    }
    std::vector<int> res(3);
    res[0] = 0;
    res[1] = 1;
    for (int i = 2; i <= n; i++) {
        res[2] = res[1] + res[0];
        res[0] = res[1];
        res[1] = res[2];
    }
    return res[1];
}
}  // namespace dynamic_programming

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    assert(dynamic_programming::fib(-2) == -1);
    assert(dynamic_programming::fib(0) == 0);
    assert(dynamic_programming::fib(1) == 1);
    assert(dynamic_programming::fib(17) == 1597);
    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char const *argv[]) {
    test();  // run self-test implementations
    return 0;
}
