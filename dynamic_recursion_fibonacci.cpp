/**
* @file
* @brief [Fibonacci Sequence](https://en.wikipedia.org/wiki/Generalizations_of_Fibonacci_numbers#Extension_to_negative_integers)
*
* @details
* This program generates both negative and positive fibonacci sequence
* using recursion and dynamic programming
* @author [Arunabh Bhattacharya](https://github.com/arunabh-cloud)
*/

#include <cmath>   /// for absolute value and pow
#include <vector>  /// for std::vector
#include <cassert>  /// for assert

/**
 * @brief Algorithm implementation for fibonacci using recursion
 * @param n is the input for generating the fibonacci sequence
 * @returns a negative sequence if n is negative
 * @returns 0 or 1 if n is 0 or 1
 * @returns a positive sequence if n is positive
 */
int fibRec(int n) {
    if (n < 0) {
        return (fibRec(-n)) * (int)pow(-1, abs(n));
    }
    else if (n == 0 || n == 1) {
        return n;
    }
    else {
        return fibRec(n - 2) + fibRec(n - 1);
    }
}

/**
 * brief Algorithm implementation for fibonacci using dynamic programming
 * @param n is the input for generating the fibonacci sequence
 * @returns a negative sequence if n is negative
 * @returns 0 or 1 if n is 0 or 1
 * @returns a positive sequence if n is positive
 */
int fibTab(int n) {
    if (n < 0) {
       return (fibTab(-n)) * (int)pow(-1, abs(n));
    }
    else if (n == 0 || n == 1) {
        return n;
    }
    else {
        std::vector<int> dynProgram(n + 1);
        dynProgram[0] = 0;
        dynProgram[1] = 1;
        for (int i = 2; i <= n; i++) {
            dynProgram[i] = dynProgram[i - 2] + dynProgram[i - 1];
        }
        return dynProgram[n];
    }
}

/**
 * @brief Self-test implementations using recursion
 * @returns void
 */
static void testsRec() {
    assert(fibRec(0) == 0);
    assert(fibRec(1) == 1);
    assert(fibRec(2) == 1);
    assert(fibRec(3) == 2);
    assert(fibRec(4) == 3);
    assert(fibRec(5) == 5);
    assert(fibRec(6) == 8);
    assert(fibRec(-1) == -1);
    assert(fibRec(-2) == 1);
    assert(fibRec(-3) == -2);
    assert(fibRec(-4) == 3);
    assert(fibRec(-5) == -5);
    assert(fibRec(-6) == 8);
}

/**
 * @brief Self-test implementations using dynamic programming
 * @returns void
 */
static void testsTab() {
    assert(fibTab(0) == 0);
    assert(fibTab(1) == 1);
    assert(fibTab(2) == 1);
    assert(fibTab(3) == 2);
    assert(fibTab(4) == 3);
    assert(fibTab(5) == 5);
    assert(fibTab(6) == 8);
    assert(fibTab(-1) == -1);
    assert(fibTab(-2) == 1);
    assert(fibTab(-3) == -2);
    assert(fibTab(-4) == 3);
    assert(fibTab(-5) == -5);
    assert(fibTab(-6) == 8);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    testsRec();   /// run self-test implementations using recursion
    testsTab();   /// run self-test implementations using dynamic programming
    return 0;
}
