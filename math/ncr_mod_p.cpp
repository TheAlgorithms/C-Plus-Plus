/**
 * @file
 * @brief C++ program to find number of distinct ways of selecting r objects fom
 * n distinct objects. SInce this number can be very large, we will calulate
 * answer modulo p
 */
#include <iostream>
#include <vector>

std::vector<int64_t> factorial;  // Store pre-computed factorials

/** function to find inverse modulo of given number */
int64_t inverse(int64_t i, int64_t m) {
    if (i == 1) {
        return 1;
    }

    return (m - ((m / i) * inverse(m % i, m)) % m + m) % m;
}

int64_t nCr(int64_t n, int64_t r, int64_t p) {
    if (r > n) {
        return 0;
    } else if (r == 0 || r == n) {
        return 1;
    } else {
        return (((factorial[n] * inverse(factorial[r], p)) % p) *
                inverse(factorial[n - r], p)) %
               p;
    }
}
/** Main function */
int main() {
    int n = 0, r = 0, p = 0;
    // p should be a prime number
    std::cin >> n >> r >> p;

    factorial = std::vector<int64_t>(n + 1);

    factorial[0] = 1;

    // Loop to pre-calculate i factorial for 0<=i<=n
    for (int i = 1; i <= n; i++) {
        factorial[i] = (factorial[i - 1] * i) % p;
    }

    int64_t answer = nCr(n, r, p);

    std::cout << answer;

    return 0;
}