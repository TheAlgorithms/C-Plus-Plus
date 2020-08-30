/**
 * @file
 * @brief C++ program to find nth term in the fibonacci series.
 * @details
 * deliberately used size_t to increase the calculation of fibb series.
 * Now calculates upto 93 fibbonacci terms.
 */
#include <array>
#include <iostream>
std::array<size_t, 1000000> arr = {0, 1};

size_t fib(int n) {
    if (n <= 1) {
        return arr[n];
    }
    if (!arr[n]) {
        arr[n] = fib(n - 1) + fib(n - 2);
    }
    return arr[n];
}

int main(int argc, char const *argv[]) {
    int n = 0;
    std::cout << "Enter n: ";
    std::cin >> n;
    std::cout << "Fibonacci number is " << fib(n) << std::endl;
    return 0;
}