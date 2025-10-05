/*
 * Armstrong Number Checker in C++
 *
 * An Armstrong number (narcissistic number) is a number equal to the sum of
 * its digits raised to the power of the number of digits.
 *
 * Example: 153 -> 1^3 + 5^3 + 3^3 = 153
 *
 * This implementation is beginner-friendly, with interactive input and tests.
 */

#include <cassert>
#include <cmath>
#include <iostream>
using namespace std;

// Function to count digits
int count_digits(int num) {
    return (num == 0) ? 1 : static_cast<int>(log10(num)) + 1;
}

// Function to check Armstrong number
bool isArmstrong(int num) {
    if (num < 0)
        return false;

    int sum = 0;
    int n = count_digits(num);
    int temp = num;

    while (temp > 0) {
        int digit = temp % 10;
        sum += pow(digit, n);
        temp /= 10;
    }
    return sum == num;
}

// Self-test function
void test() {
    assert(isArmstrong(0) == true);
    assert(isArmstrong(153) == true);
    assert(isArmstrong(370) == true);
    assert(isArmstrong(225) == false);
    assert(isArmstrong(-23) == false);
    assert(isArmstrong(12) == false);
    cout << "All self-tests passed!\n";
}

// Main function for interactive usage
int main() {
    test();  // Run automated tests

    int number;
    cout << "Enter a number to check if it is an Armstrong number: ";
    cin >> number;

    if (isArmstrong(number))
        cout << number << " is an Armstrong number!\n";
    else
        cout << number << " is NOT an Armstrong number.\n";

    return 0;
}
