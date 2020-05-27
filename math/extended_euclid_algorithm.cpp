#include <iostream>
// Finding coefficients of a and b ie x and y in gcd(a, b) = a * x + b * y
// d is gcd(a, b)
// This is also used in finding Modular multiplicative inverse of a number.
// (A * B)%M == 1 Here B is the MMI of A for given M,
// so extendedEuclid (A, M) gives B.
template <typename T, typename T2>
void extendedEuclid(T A, T B, T *GCD, T2 *x, T2 *y) {
    if (B > A) std::swap(A, B);  // Ensure that A >= B

    if (B == 0) {
        *GCD = A;
        *x = 1;
        *y = 0;
    } else {
        extendedEuclid(B, A % B, GCD, x, y);
        T2 temp = *x;
        *x = *y;
        *y = temp - (A / B) * (*y);
    }
}

int main() {
    uint32_t a, b, gcd;
    int32_t x, y;
    std::cin >> a >> b;
    extendedEuclid(a, b, &gcd, &x, &y);
    std::cout << gcd << " " << x << " " << y << std::endl;
    return 0;
}
