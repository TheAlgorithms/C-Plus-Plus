#include <iostream>
#include <cassert>

/* Calculate the the value on Fibonacci's sequence given an
integer as input
Fibonacci =  0, 1, 1, 2, 3, 5,
             8, 13, 21, 34, 55,
             89, 144, ...       */

int fibonacci(uint n) {
    /* If the input is 0 or 1 just return the same
       This will set the first 2 values of the sequence */
    if (n <= 1)
        return n;

    /* Add the last 2 values of the sequence to get next */
    return fibonacci(n-1) + fibonacci(n-2);
}

int main() {
    int n;
    std::cin >> n;
    assert(n >= 0);
    std::cout << "F(" << n << ")= " << fibonacci(n) << std::endl;
}
