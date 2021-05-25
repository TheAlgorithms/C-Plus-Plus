/**
 * @author amino19
 * @file
 *
 * \brief Finding number of Digits in a Number
 * \details Basically, its a very basic math of
 *  finding number of digits in a number (input),
 *  For more details, refer Algorithms-Explanation
 */

/* Log based C++ program to count number of
 *  digits in a number/integer */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    int n = 0;
    int count = 0;
    std::cout << "Enter an integer: ";
    std::cin >> n;

    /* iterate until n becomes 0
     *  remove last digit from n in each iteration
     *  increase count by 1 in each iteration */
    while (n != 0) {
        n /= 10;  // n = n/10
        ++count;
    }

    std::cout << "Number of digits: " << count;
}