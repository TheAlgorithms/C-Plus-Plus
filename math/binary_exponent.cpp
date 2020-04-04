/// C++ Program to find Binary Exponent recursively.

#include<iostream>
/*
 * Calculate a^b in O(log(b)) by converting b to a binary number
 * Binary exponentiation (also known as exponentiation by squaring)
 * is a trick which allows to calculate an using only O(logn) multiplications
 * (instead of O(n) multiplications required by the naive approach).
*/

/// Function to calculate exponent in O(log(n)) using binary exponent.
int binExpo(int a, int b) {
    if (b == 0) {
        return 1;
    }
    int res = binExpo(a, b/2);
    if (b%2) {
        return res*res*a;
    } else {
        return res*res;
    }
}

int main() {
    int a, b;
    /// Give two numbers a, b
    std::cin >> a >> b;
    /// Result of a^b
    std::cout << binExpo(a, b) << std::endl;
}
