/**
 * @file
 * @brief Program to check if a number is an Armstrong number
 */
#include <cmath>  // for pow function
#include <iostream>

/**
 * This method checks if a given number is an Armstrong number.
 */
bool isArmstrong(int number) {
    int sum = 0, temp = number, remainder, num_digits = 0;

    // Count the number of digits in the number
    while (temp > 0) {
        temp /= 10;
        num_digits++;
    }

    temp = number;

    // Calculate the sum of digits raised to the power of num_digits
    while (temp > 0) {
        remainder = temp % 10;
        sum += pow(remainder, num_digits);
        temp /= 10;
    }

    // If the sum equals the original number, it is an Armstrong number
    return (sum == number);
}

/**
 * This method prints whether the number is an Armstrong number or not.
 */
void printArmstrongResult(int number) {
    if (isArmstrong(number)) {
        std::cout << number << " is an Armstrong number." << std::endl;
    } else {
        std::cout << number << " is not an Armstrong number." << std::endl;
    }
}

int main() {
    int number;
    std::cout << "Enter a number:";
    std::cin >> number;

    printArmstrongResult(number);

    return 0;
}