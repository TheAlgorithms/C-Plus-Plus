// An efficient way to calculate nth fibonacci number faster and simpler than
// O(nlogn) method of matrix exponentiation This works by using both recursion
// and dynamic programming. as 93rd fibonacci exceeds 19 digits, which cannot be
// stored in a single long long variable, we can only use it till 92nd fibonacci
// we can use it for 10000th fibonacci etc, if we implement bigintegers.
// This algorithm works with the fact that nth fibonacci can easily found if we
// have already found n/2th or (n+1)/2th fibonacci It is a property of fibonacci
// similar to matrix exponentiation.

#include <cinttypes>
#include <cstdio>
#include <iostream>

const uint64_t MAX = 93;

uint64_t f[MAX] = {0};

uint64_t fib(uint64_t n) {
    if (n == 0) return 0;
    if (n == 1 || n == 2) return (f[n] = 1);

    if (f[n]) return f[n];

    uint64_t k = (n % 2 != 0) ? (n + 1) / 2 : n / 2;

    f[n] = (n % 2 != 0) ? (fib(k) * fib(k) + fib(k - 1) * fib(k - 1))
                        : (2 * fib(k - 1) + fib(k)) * fib(k);
    return f[n];
}

int main() {
    // Main Function
    for (uint64_t i = 1; i < 93; i++) {
        std::cout << i << " th fibonacci number is " << fib(i) << "\n";
    }
    return 0;
}
