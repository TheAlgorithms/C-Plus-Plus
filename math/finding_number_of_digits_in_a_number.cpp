/**
 * @author [aminos 🇮🇳](https://github.com/amino19)
 * @file
 *
 * @brief [Program to count digits 
 * in an integer](https://www.geeksforgeeks.org/program-count-digits-integer-3-different-methods)
 * @details It is a very basic math of finding number of digits in a given
 * number i.e, we can use it by inputting values whether it can be a
 * positive/negative value, let's say: an integer. There is also a second method: 
 * by using "K = floor(log10(N) + 1)", but it's only applicable for
 * numbers (not integers).
 * For more details, refer to the [Algorithms-Explanation](https://github.com/TheAlgorithms/Algorithms-Explanation/blob/master/en/Basic%20Math/Finding the number of digits in a number.md) repository.
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    // Initialize `n` & `count` by 0
    int n = 0;
    int count = 0;

    std::cout << "Enter an integer: ";
    std::cin >> n;

    // iterate until `n` becomes 0
    // remove last digit from `n` in each iteration
    // increase `count` by 1 in each iteration 
    while (n != 0) {
        // we can also use `n = n / 10`
        n /= 10;
        // each time the loop is running, `count` will be incremented by 1.
        ++count;
    }
    std::cout << "Number of digits: " << count;

    return 0;
}
