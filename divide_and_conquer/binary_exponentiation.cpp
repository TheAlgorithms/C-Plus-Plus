/**
 * @file
 * @brief Implementation of the [Binary Exponentiation (divide-and-conquer)](https://en.wikipedia.org/wiki/Exponentiation_by_squaring) algorithm
 * @author [jay-tux](github.com/jay-tux)
 * Computes base ^ exp by dividing exp by two while squaring base (reducing the
 * amount of multiplications).
 */

#include <cassert>  /// for assert
#include <cmath>    /// for powl
#include <cstdint>  /// for uint64_t
#include <cstdlib>  /// for srand, rand
#include <ctime>    /// for time

/**
 * @namespace divide_and_conquer
 * @brief Divide and Conquer algorithms
 */
namespace divide_and_conquer {
/**
 * @namespace binary_exponentiation
 * @brief Binary Exponentiation using bitshifts
 */
namespace binary_exponentiation {
/**
 * @brief Result type is a type alias for long long unsigned int
 */
using result_t = std::uint64_t;
/**
 * @brief Input type is a type aligas for long long unsigned int
 */
using input_t = std::uint64_t;

/**
 * @brief Computes base^exp
 * @param base the base to exponentiate
 * @param exp the power to which to exponentiate
 * @returns base^exp (without overflow checking)
 */
result_t binaryExp(input_t base, input_t exp) {
    if (exp == 0) {
        return 1;
    }
    result_t sub = binaryExp(base, exp >> 1);  // divide by 2 by shifting
    sub = sub * sub;                           // square
    return (exp & 1) ? sub * base : sub;
}
}  // namespace binary_exponentiation
}  // namespace divide_and_conquer

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    std::srand(std::time(nullptr));

    using divide_and_conquer::binary_exponentiation::binaryExp;
    using divide_and_conquer::binary_exponentiation::input_t;
    using divide_and_conquer::binary_exponentiation::result_t;

    input_t base = 0, exp = 0;
    result_t res = 0, stdlib = 0;

    // test base case 100 times
    for (int i = 0; i < 100; i++) {
        base = std::rand();
        assert(binaryExp(base, exp) == 1);  // a^0 = 1
    }

    // test each of 100 random bases with 100 random exponents
    // check using builtin exponentiation
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            // limit ranges to avoid overflow errors
            base = std::rand() % 12;
            exp = std::rand() % 12;
            res = binaryExp(base, exp);
            stdlib = static_cast<result_t>(
                std::pow(static_cast<double>(base), static_cast<double>(exp)));
            assert(res == stdlib);  // a^b = a^b
        }
    }
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();  // run self-test implementations
    return 0;
}
