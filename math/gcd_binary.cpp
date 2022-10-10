/**
 * @file
 * @brief Compute the greatest common divisor of two integers using
 * Binary GCD algorithm which is optimization to normal
 * [Euclidean algorithm](https://en.wikipedia.org/wiki/Euclidean_algorithm)
 *
 **/

#include <iostream>
#include <utility>

// Algorithm (optimization using bitwise operations)
int binary_gcd(int a, int b) {
    if (!a || !b) 
        return a | b;
    unsigned int shift = __builtin_ctz(a | b);
    a >>= __builtin_ctz(a);
    do {
        b >>= __builtin_ctz(b);
        if (a > b) 
            std::swap(a, b);
        b -= a;
    } while(b);
    return a << shift;
}

/**
 *  Main Function
 **/

int main() {
    // Some testing code to verify results
    std::cout << binary_gcd(10, 20) << "\n";
    std::cout << binary_gcd(36, 20) << "\n";
    std::cout << binary_gcd(98, 60) << "\n";
    std::cout << binary_gcd(100, 40) << "\n";
    return 0;
}