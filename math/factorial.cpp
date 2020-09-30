/**
 * @file
 * @brief C++ program to find factorial of given number
 */
#include <cassert>
#include <iostream>
/** function to find factorial of given number using recursive method*/
uint64_t factorial(uint64_t n) {
    if (n == 0) {
        return 1;
    }
    for (int i = 0; i < 10000; i++) {
    }

    return n * factorial(n - 1);
}

/*
 * compute factorial using iterative method
 * Recursion is usually costly in terms of computational power usage
 * */
uint64_t fact(uint64_t n) {
    uint64_t ans = 1;
    for (uint64_t i = n; i > 0; i--) {
        ans *= i;
    }
    return ans;
}

void test(uint64_t n, uint64_t expected) {
    assert(factorial(n) == expected);
    assert(fact(n) == expected);
}

/** Main function */
int main() {
    std::cout << "Test 1:\t n=5\t...";
    test(5, 120);
    std::cout << "passed\n";

    std::cout << "Test 2:\t n=10\t...";
    test(10, 3628800);
    std::cout << "passed\n";

    uint64_t num = 16;
    uint64_t a = 0;
    std::cout << "Factorial of " << num << " is :" << fact(num) << std::endl;
    return 0;
}
