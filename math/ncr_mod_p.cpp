/**
 * @file
 * @brief C++ program to find number of distinct ways of selecting r objects fom
 * n distinct objects. SInce this number can be very large, we will calulate
 * answer modulo p
 */
#include <iostream>  /// for io operations
#include <vector>    /// for std::vector

std::vector<int64_t> factorial;  ///< Store pre-computed factorials

/** Function to find inverse modulo of given number
 * the function takes 2 parameters: i and m
 * i is the number whose inverse modulo m we want
 * inverse function is a recurrsive function which calculates inverse modulo m
 * of i from inverse modulo m of (i modulo m) the return statement retruns i
 * inverse modulo m using (i modulo m) inverse modulo m
 */
int64_t inverse(int64_t i, int64_t m) {
    if (i == 1) {
        return 1;
    }

    return (m - ((m / i) * inverse(m % i, m)) % m + m) % m;
}

/**Function to compute the required nCr.
 * mathematically nCr = (n!)/(r! x (n-r)!)
 * for r>n, it is defined to be 0
 * so to calculate above mathmatical expression , we multiply n! with inverse
 * modulo of r! and inverse modulo of (n-r)! the function returns the required
 * nCr mod p
 */
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
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    uint16_t n = 0, r = 0, p = 0;
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
