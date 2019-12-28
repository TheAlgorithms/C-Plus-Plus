#include <cmath>
#include <iostream>
#include <stdexcept>

// will find the greatest common denominator of two ints integers
// Euclidean algorithm can be found here
// https://en.wikipedia.org/wiki/Euclidean_algorithm
int gcd(int num1, int num2) {
    if (num1 <= 0 | num2 <= 0) {
        throw std::domain_error("Euclidean algorithm domain is for ints > 0");
    }

    if (num1 == num2) {
        return num1;
    }

    int base_num = 0;
    int previous_remainder = 1;

    if (num1 > num2) {
        base_num = num1;
        previous_remainder = num2;
    } else {
        base_num = num2;
        previous_remainder = num1;
    }

    while ((base_num % previous_remainder) != 0) {
        int old_base = base_num;
        base_num = previous_remainder;
        previous_remainder = old_base % previous_remainder;
    }

    return previous_remainder;
}

int main() {
    std::cout << "gcd of 120,7 is " << (gcd(120, 7)) << std::endl;
    try {
        std::cout << "gcd of -120,10 is " << gcd(-120, 10) << std::endl;
    } catch (const std::domain_error &e) {
        std::cout << "Error handling was successful" << std::endl;
    }
    std::cout << "gcd of 312,221 is " << (gcd(312, 221)) << std::endl;
    std::cout << "gcd of 289,204 is " << (gcd(289, 204)) << std::endl;

    return 0;
}
