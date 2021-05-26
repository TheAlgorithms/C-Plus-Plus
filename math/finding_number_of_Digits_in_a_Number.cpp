/**
 * @author [ANSHUMAAN](https://github.com/amino19)
 * @file [Program to count digits in an
 * integer](https://www.geeksforgeeks.org/program-count-digits-integer-3-different-methods)
 *
 * @brief Finding number of Digits in a Number
 * @details It is a very basic math of finding number of digits in a given
 * number i.e, we can use it by inputting values whether it can be a
 * positive/negative value, lets say integer. There is also second method to do
 * it with, by using "K = floor(log10(N) + 1)", but its only applicable for
 * numbers (not integers).
 * For more details, refer Algorithms-Explanation
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
        // Initialize 'n' & 'count' by 0
    int n = 0;
    int count = 0;

    /* 'cout' to ask input from user..
     * 'cin' to taking integer as input..
     */
    std::cout << "Enter an integer: ";
    std::cin >> n;

    /* iterate until n becomes 0
     * remove last digit from n in each iteration
     * increase count by 1 in each iteration */
    while (n != 0) {
        // we can also use: n = n/10
        n /= 10;
        /*  each time while loop running, count will
         *  be increment by 1.
         */
        ++count;
    }

    std::cout << "Number of digits: " << count;

    return 0;
}
