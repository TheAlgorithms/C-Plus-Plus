/**
 * @file
 * @brief Program to calculate [Binomial
 * coefficients](https://en.wikipedia.org/wiki/Binomial_coefficient)
 *
 * @author [astronmax](https://github.com/astronmax)
 */

#include <cassert>  /// for assert
#include <cstdint>  /// for int32_t type
#include <cstdio>   /// for printf
#include <cstdlib>  /// for atoi

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
/**
 * @brief Function to calculate binomial coefficients
 * @param n first value
 * @param k second value
 * @return binomial coefficient for n and k
 */
size_t binomial(int32_t n, int32_t k) {
    // basic cases
    if (k > (n / 2))
        k = n - k;
    if (k == 1)
        return n;
    if (k == 0)
        return 1;

    size_t result = 1;
    for (int32_t i = 1; i <= k; ++i) {
        result *= n - k + i;
        result /= i;
    }

    return result;
}
}  // namespace math

/**
 * @brief Test implementations
 * @returns void
 */

static void binomial_test() {
    // test for n from 1 to 62
    assert(math::binomial(1, 1) == 1);
    assert(math::binomial(57, 57) == 1);
    assert(math::binomial(6, 3) == 20);
    assert(math::binomial(10, 5) == 252);
    assert(math::binomial(20, 10) == 184756);
    assert(math::binomial(30, 15) == 155117520);
    assert(math::binomial(40, 20) == 137846528820);
    assert(math::binomial(50, 25) == 126410606437752);
    assert(math::binomial(60, 30) == 118264581564861424);
    assert(math::binomial(62, 31) == 465428353255261088);

    printf("[+] Binomial coefficients test completed\n");
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main(int argc, const char* argv[]) {
    // run test
    binomial_test();

    if (argc < 3) {
        printf("Usage ./binomial {n} {k}\n");
        return 0;
    }

    int32_t n = atoi(argv[1]);
    int32_t k = atoi(argv[2]);

    printf("%zd\n", math::binomial(n, k));
    return 0;
}
