/**
 * @file
 * @brief A happy number is a number whose sum of digits is calculated until the
 * sum is a single digit, and this sum turns out to be 1
 */

#include <iostream>

/**
 * Checks if a decimal number is a happy number
 * \returns true if happy else false
 */
template <typename T>
bool is_happy(T n) {
    T s = 0;              // stores sum of digits
    while (n > 9) {       // while number is > 9, there are more than 1 digit
        while (n != 0) {  // get digit
            T d = n % 10;
            s += d;
            n /= 10;
        }
        n = s;
        s = 0;
    }
    return (n == 1) ? true : false;  // true if k == 1
}

/** Main function */
int main() {
    int n;
    std::cout << "Enter a number:";
    std::cin >> n;

    if (is_happy(n))
        std::cout << n << " is a happy number" << std::endl;
    else
        std::cout << n << " is not a happy number" << std::endl;
    return 0;
}
