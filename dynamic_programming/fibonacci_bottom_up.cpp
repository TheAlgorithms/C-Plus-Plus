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
 * for i the fibonacci store only i-1 th and i-2 th state.
 */
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
/**
 * @namespace dynamic_programming
 * @brief Dynamic Programming algorithms
 */
int fib(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 0;
    }
    int res[3];
    res[0] = 0;
    res[1] = 1;
    for (int i = 2; i <= n; i++) {
        res[2] = res[1] + res[0];
        res[0] = res[1];
        res[1] = res[2];
    }
    return res[1];
}
/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    assert(fib(-2) == -1);
    assert(fib(0) == 0);
    assert(fib(1) == 1);
    assert(fib(17) == 1597);
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
