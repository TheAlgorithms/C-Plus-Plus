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
#include <iostream>  /// for std::cout
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
 * @namespace utils
 * @brief this namespace contains the definitions of the functions called from
 * the class math::ncr_modulo_p::NCRModuloP
 */
namespace utils {
/**
 * @brief finds the values x and y such that a*x + b*y = gcd(a,b)
 *
 * @param[in] a the first input of the gcd
 * @param[in] a the second input of the gcd
 * @param[out] x the Bézout coefficient of a
 * @param[out] y the Bézout coefficient of b
 * @return the gcd of a and b
 */
int64_t gcdExtended(const int64_t& a, const int64_t& b, int64_t& x,
                    int64_t& y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }

    int64_t x1 = 0, y1 = 0;
    const int64_t gcd = gcdExtended(b % a, a, x1, y1);

    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

/** Find modular inverse of a modulo m i.e. a number x such that (a*x)%m = 1
 *
 * @param[in] a the number for which the modular inverse is queried
 * @param[in] m the modulus
 * @return the inverce of a modulo m, if it exists, -1 otherwise
 */
int64_t modInverse(const int64_t& a, const int64_t& m) {
    int64_t x = 0, y = 0;
    const int64_t g = gcdExtended(a, m, x, y);
    if (g != 1) {  // modular inverse doesn't exist
        return -1;
    } else {
        return ((x + m) % m);
    }
}
}  // namespace utils
/**
 * @brief Class which contains all methods required for calculating nCr mod p
 */
class NCRModuloP {
 private:
    const int64_t p = 0;  /// the p from (nCr % p)
    const std::vector<int64_t>
        fac;  /// stores precomputed factorial(i) % p value

    /**
     * @brief computes the array of values of factorials reduced modulo mod
     * @param max_arg_val argument of the last factorial stored in the result
     * @param mod value of the divisor used to reduce factorials
     * @return vector storing factorials of the numbers 0, ..., max_arg_val
     * reduced modulo mod
     */
    static std::vector<int64_t> computeFactorialsMod(const int64_t& max_arg_val,
                                                     const int64_t& mod) {
        auto res = std::vector<int64_t>(max_arg_val + 1);
        res[0] = 1;
        for (int64_t i = 1; i <= max_arg_val; i++) {
            res[i] = (res[i - 1] * i) % mod;
        }
        return res;
    }

 public:
    /**
     * @brief constructs an NCRModuloP object allowing to compute (nCr)%p for
     * inputs from 0 to size
     */
    NCRModuloP(const int64_t& size, const int64_t& p)
        : p(p), fac(computeFactorialsMod(size, p)) {}

    /**
     * @brief computes nCr % p
     * @param[in] n the number of objects to be chosen
     * @param[in] r the number of objects to choose from
     * @return the value nCr % p
     */
    int64_t ncr(const int64_t& n, const int64_t& r) const {
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
        const auto denominator = (fac[r] * fac[n - r]) % p;
        const auto denominator_inv = utils::modInverse(denominator, p);
        if (denominator_inv < 0) {  // modular inverse doesn't exist
            return -1;
        }
        return (fac[n] * denominator_inv) % p;
    }
};
}  // namespace ncr_modulo_p
}  // namespace math

/**
 * @brief tests math::ncr_modulo_p::NCRModuloP
 */
static void tests() {
    struct TestCase {
        const int64_t size;
        const int64_t p;
        const int64_t n;
        const int64_t r;
        const int64_t expected;

        TestCase(const int64_t size, const int64_t p, const int64_t n,
                 const int64_t r, const int64_t expected)
            : size(size), p(p), n(n), r(r), expected(expected) {}
    };
    const std::vector<TestCase> test_cases = {
        TestCase(60000, 1000000007, 52323, 26161, 224944353),
        TestCase(20, 5, 6, 2, 30 % 5),
        TestCase(100, 29, 7, 3, 35 % 29),
        TestCase(1000, 13, 10, 3, 120 % 13),
        TestCase(20, 17, 1, 10, 0),
        TestCase(45, 19, 23, 1, 23 % 19),
        TestCase(45, 19, 23, 0, 1),
        TestCase(45, 19, 23, 23, 1),
        TestCase(20, 9, 10, 2, -1)};
    for (const auto& tc : test_cases) {
        assert(math::ncr_modulo_p::NCRModuloP(tc.size, tc.p).ncr(tc.n, tc.r) ==
               tc.expected);
    }

    std::cout << "\n\nAll tests have successfully passed!\n";
}

/**
 * @brief example showing the usage of the math::ncr_modulo_p::NCRModuloP class
 */
void example() {
    const int64_t size = 1e6 + 1;
    const int64_t p = 1e9 + 7;

    // the ncrObj contains the precomputed values of factorials modulo p for
    // values from 0 to size
    const auto ncrObj = math::ncr_modulo_p::NCRModuloP(size, p);

    // having the ncrObj we can efficiently query the values of (n C r)%p
    // note that time of the computation does not depend on size
    for (int i = 0; i <= 7; i++) {
        std::cout << 6 << "C" << i << " mod " << p << " = " << ncrObj.ncr(6, i)
                  << "\n";
    }
}

int main() {
    tests();
    example();
    return 0;
}
