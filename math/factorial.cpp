/**
 * @file
 * @brief C++ program to find factorial of given number
 */
#include <ctime>
#include <iostream>
/** function to find factorial of given number */
unsigned long long int factorial(unsigned long int n) {
    if (n == 0)
        return 1;
    for (int i = 0; i < 10000; i++) {
    }

    return n * factorial(n - 1);
}

unsigned long long int fact(unsigned long long int n) {
    unsigned long long int ans = 1;
    for (unsigned long long int i = n; i > 0; i--) {
        ans *= i;
    }
    return ans;
}
/** Main function */
int main() {
    unsigned long long int num = 60;
    unsigned long long int a;

    std::cout << "Factorial of " << num << " is :" << fact(num) << std::endl;
    return 0;
}
