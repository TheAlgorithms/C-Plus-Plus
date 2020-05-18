#include <iostream>
// Finding coefficients of a and b ie x and y in gcd(a, b) = a * x + b * y
// d is gcd(a, b)
// This is also used in finding Modular multiplicative inverse of a number.
// (A * B)%M == 1 Here B is the MMI of A for given M,
// so extendedEuclid (A, M) gives B.

int d, x, y;
void extendedEuclid(int A, int B) {
    if (B == 0) {
        d = A;
        x = 1;
        y = 0;
    } else {
        extendedEuclid(B, A%B);
        int temp = x;
        x = y;
        y = temp - (A/B)*y;
    }
}

int main() {
    int a, b;
    std::cin >> a >> b;
    extendedEuclid(a, b);
    std::cout << x << " " << y << std::endl;
    return 0;
}
