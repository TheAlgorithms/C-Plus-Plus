/**
 * A simple C++ Program to find the Sum of Digits of input integer.
 */
#include <iostream>

/**
 * Function to find the sum of the digits of an integer.
 * @param num The integer.
 * @return Sum of the digits of the integer.
 */
int sum_of_digits(int num) {
    int sum = 0;
    while (num > 0) {
        sum = sum + (num % 10);
        num = num / 10;
    }
    return sum;
}

int main() {
    int num;
    std::cin >> num;
    if (num < 0) {
        num = -1 * num;
    }
    std::cout << sum_of_digits(num);
    return 0;
}