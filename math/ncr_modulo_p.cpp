/**
 * @file
 * @brief This program aims at calculating [nCr modulo
 * p](https://cp-algorithms.com/combinatorics/binomial-coefficients.html).
 * @details nCr is defined as n! / (r! * (n-r)!) where n! represents factorial
 * of n. In many cases, the value of nCr is too large to fit in a 64 bit
 * integer. Hence, in competitive programming, there are many problems or
 * subproblems to compute nCr modulo p where p is a given number.
 * @author [Kaustubh Damania](https://github.com/KaustubhDamania)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for io operations
#include <vector>    /// for std::vector

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
/**
 * @namespace ncr_modulo_p
 * @brief Functions for [nCr modulo
 * p](https://cp-algorithms.com/combinatorics/binomial-coefficients.html)
 * implementation.
 */
namespace ncr_modulo_p {
/**
 * @brief Class which contains all methods required for calculating nCr mod p
 */
class NCRModuloP {
 private:
    std::vector<uint64_t> fac{};  /// stores precomputed factorial(i) % p value
    uint64_t p = 0;               /// the p from (nCr % p)

 public:
    /** Constructor which precomputes the values of n! % mod from n=0 to size
     *  and stores them in vector 'fac'
     *  @params[in] the numbers 'size', 'mod'
     */
    NCRModuloP(const uint64_t& size, const uint64_t& mod) {
        p = mod;
        fac = std::vector<uint64_t>(size);
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
    uint64_t gcdExtended(const uint64_t& a, const uint64_t& b, int64_t* x,
                         int64_t* y) {
        if (a == 0) {
            *x = 0, *y = 1;
            return b;
        }

        int64_t x1 = 0, y1 = 0;
        uint64_t gcd = gcdExtended(b % a, a, &x1, &y1);

        *x = y1 - (b / a) * x1;
        *y = x1;
        return gcd;
    }

    /** Find modular inverse of a with m i.e. a number x such that (a*x)%m = 1
     *
     * @params[in] the numbers 'a' and 'm' from above equation
     * @returns the modular inverse of a
     */
    int64_t modInverse(const uint64_t& a, const uint64_t& m) {
        int64_t x = 0, y = 0;
        uint64_t g = gcdExtended(a, m, &x, &y);
        if (g != 1) {  // modular inverse doesn't exist
            return -1;
        } else {
            int64_t res = ((x + m) % m);
            return res;
        }
    }

    /** Find nCr % p
     *
     * @params[in] the numbers 'n', 'r' and 'p'
     * @returns the value nCr % p
     */
    int64_t ncr(const uint64_t& n, const uint64_t& r, const uint64_t& p) {
        // Base cases
        if (r > n) {
            return 0;
        }
        if (r == 1) {
            return n % p;
        }
        if (r == 0 || r == n) {
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
}  // namespace ncr_modulo_p
}  // namespace math

/**
 * @brief Test implementations
 * @param ncrObj object which contains the precomputed factorial values and
 * ncr function
 * @returns void
 */
static void tests(math::ncr_modulo_p::NCRModuloP ncrObj) {
    // (52323 C 26161) % (1e9 + 7) = 224944353
    assert(ncrObj.ncr(52323, 26161, 1000000007) == 224944353);
    // 6 C 2 = 30, 30%5 = 0
    assert(ncrObj.ncr(6, 2, 5) == 0);
    // 7C3 = 35, 35 % 29 = 8
    assert(ncrObj.ncr(7, 3, 29) == 6);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    // populate the fac array
    const uint64_t size = 1e6 + 1;
    const uint64_t p = 1e9 + 7;
    math::ncr_modulo_p::NCRModuloP ncrObj =
        math::ncr_modulo_p::NCRModuloP(size, p);
    // test 6Ci for i=0 to 7
    for (int i = 0; i <= 7; i++) {
        std::cout << 6 << "C" << i << " = " << ncrObj.ncr(6, i, p) << "\n";
    }
    tests(ncrObj);  // execute the tests
    std::cout << "Assertions passed\n";
    return 0;
}
