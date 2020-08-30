/**
 * @file
 * @brief C++ program to find nth term in the fibonacci series.
 */
#include <iostream>
using namespace std;

size_t arr[1000000] = {0, 1};

size_t fib(int n) {
    if (n <= 1)
        return arr[n];
    if (!arr[n]) {
        arr[n] = fib(n - 1) + fib(n - 2);
    }
    return arr[n];
}
int main(int argc, char const *argv[]) {
    int n;
    cout << "Enter n: ";
    cin >> n;
    cout << "Fibonacci number is " << fib(n) << endl;
    return 0;
}