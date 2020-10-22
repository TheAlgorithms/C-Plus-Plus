/**
 * @file
 * @brief This program aims at calculating nCr modulo p
 *
 */

#include <cassert>
#include <iostream>
#include <vector>


/** Class which contains all methods required for calculating nCr mod p
 *
 */
class NCRModuloP {
private:
    std::vector<int64_t> fac;
    int64_t p;
public:
    /** Constructor which precomputes the values of n! % mod from n=0 to size
     *  and stores them in vector 'fac'
     *  @params[in] the numbers 'size', 'mod'
    */
    NCRModuloP(int64_t size, int64_t mod){
        p = mod;
        fac = std::vector<int64_t>(size);
        fac[0] = 1;
        for (int i = 1; i <= size; i++) {
            fac[i] = (fac[i - 1] * i) % p;
        }
    }

    /** Finds the value of x, y such that a*x + b*y = gcd(a,b)
     *
     * @params[in] the numbers 'a', 'b' and address of 'x' and 'y' from above
     * equation
     * @returns the gcd of a and b
     */
    int64_t gcdExtended(int64_t a, int64_t b, int64_t *x, int64_t *y) {
        if (a == 0) {
            *x = 0, *y = 1;
            return b;
        }

        int64_t x1 = 0, y1 = 0;
        int64_t gcd = gcdExtended(b % a, a, &x1, &y1);

        *x = y1 - (b / a) * x1;
        *y = x1;
        return gcd;
    }

    /** Find modular inverse of a with m i.e. a number x such that (a*x)%m = 1
     *
     * @params[in] the numbers 'a' and 'm' from above equation
     * @returns the modular inverse of a
     */
    int64_t modInverse(int64_t a, int64_t m) {
        int64_t x = 0, y = 0;
        int64_t g = gcdExtended(a, m, &x, &y);
        if (g != 1) {  // modular inverse doesn't exist
            return -1;
        }
        else {
            int64_t res = (x % m + m) % m;
            return res;
        }
    }

    /** Find nCr % p
     *
     * @params[in] the numbers 'n', 'r' and 'p'
     * @returns the value nCr % p
     */
    int64_t ncr(int64_t n, int64_t r, int64_t p) {
        // Base cases
        if (r > n) {
            return 0;
        }
        if (r == 1) {
            return n % p;
        }
        if (r == 0 || r == n){
            return 1;
        }
        // fac is a global array with fac[r] = (r! % p)
        int64_t denominator = modInverse(fac[r], p);
        if (denominator < 0) {  // modular inverse doesn't exist
            return -1;
        }
        denominator = (denominator * modInverse(fac[n - r], p)) % p;
        if (denominator < 0) {  // modular inverse doesn't exist
            return -1;
        }
        return (fac[n] * denominator) % p;
    }
};

void tests(NCRModuloP ncrObj) {
    // (52323 C 26161) % (1e9 + 7) = 224944353
    assert(ncrObj.ncr(52323, 26161, 1000000007) == 224944353);
    // 6 C 2 = 30, 30%5 = 0
    assert(ncrObj.ncr(6,2,5) == 0);
    // 7C3 = 35, 35 % 29 = 8
    assert(ncrObj.ncr(7,3,29) == 6);
}


/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    // populate the fac array
    const int64_t size = 1e6 + 1;
    const int64_t p = 1e9 + 7;
    NCRModuloP ncrObj = NCRModuloP(size, p);
    // test 6Ci for i=0 to 7
    for (int i = 0; i <= 7; i++) {
        std::cout << 6 << "C" << i << " = " << ncrObj.ncr(6, i, p) << "\n";
    }
    tests(ncrObj);
    std::cout << "Assertions passed\n";
}
