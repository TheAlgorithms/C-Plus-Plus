/**
 * @file
 * @brief C++ program to find factorial of given number
 */
#include <iostream>

/** function to find factorial of given number */
long factorial(unsigned int n) {
    return n == 0 ? 1 : n * factorial(n - 1);
}

/** Main function */
int main() {
    int num = 5;
    std::cout << "Factorial of " << num << " is " << factorial(num)
              << std::endl;
    return 0;
}
