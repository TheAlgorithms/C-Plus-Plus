/**
 * @file
 * @brief Program to calculate binomial coefficients.
 *
 * @author [astronmax](https://github.com/astronmax)
 */

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

/**
 * @brief Function to calculate binomial coefficients.
 * @param n first value to calculate binomial coefficient
 * @param k second value to calculate binomial coefficient
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

/**
 * TESTS
 */

void binomial_test() {
    // test for n from 1 to 62
    assert(binomial(1, 1) == 1);
    assert(binomial(57, 57) == 1);
    assert(binomial(6, 3) == 20);
    assert(binomial(10, 5) == 252);
    assert(binomial(20, 10) == 184756);
    assert(binomial(30, 15) == 155117520);
    assert(binomial(40, 20) == 137846528820);
    assert(binomial(50, 25) == 126410606437752);
    assert(binomial(60, 30) == 118264581564861424);
    assert(binomial(62, 31) == 465428353255261088);

    printf("[+] Binomial coefficients test completed\n");
}

/**
 * Main function
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

    printf("%zd\n", binomial(n, k));
}
