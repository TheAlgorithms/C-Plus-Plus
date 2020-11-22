/**
 * @file
 * @brief [Combinations](https://en.wikipedia.org/wiki/Combination) n choose r
 * function implementation
 * @details
 * A very basic and efficient method of calculating
 * choosing r from n different choices.
 * \f$ \binom{n}{r} = \frac{n!}{r! (n-r)!} \f$
 *
 * @author [Tajmeet Singh](https://github.com/tjgurwara99)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for io operations

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
/**
 * @brief This is the function implementation of \f$ \binom{n}{r} \f$
 * @details
 * We are calculating the ans with iterations
 * instead of calculating three different factorials.
 * Also, we are using the fact that
 * \f$ \frac{n!}{r! (n-r)!} = \frac{(n - r + 1) \times \cdots \times n}{1 \times
 * \cdots \times r} \f$
 * @tparam T Only for integer types such as long, int_64 etc
 * @param n \f$ n \f$ in \f$ \binom{n}{r} \f$
 * @param r \f$ r \f$ in \f$ \binom{n}{r} \f$
 * @returns ans \f$ \binom{n}{r} \f$
 */
template <class T>
T n_choose_r(T n, T r) {
    if (r > n / 2) {
        r = n - r;  // Because of the fact that  nCr(n, r) == nCr(n, n - r)
    }
    T ans = 1;
    for (int i = 1; i <= r; i++) {
        ans *= n - r + i;
        ans /= i;
    }
    return ans;
}
}  // namespace math

/**
 * @brief Test implementations
 * @returns void
 */
static void test() {
    // First test on 5 choose 2
    uint8_t t = math::n_choose_r(5, 2);
    assert(((void)"10 is the answer but function says otherwise.\n", t == 10));
    std::cout << "First test passes." << std::endl;
    // Second test on 5 choose 3
    t = math::n_choose_r(5, 3);
    assert(
        ((void)"10 is the answer but the function says otherwise.\n", t == 10));
    std::cout << "Second test passes." << std::endl;
    // Third test on 3 choose 2
    t = math::n_choose_r(3, 2);
    assert(
        ((void)"3 is the answer but the function says otherwise.\n", t == 3));
    std::cout << "Third test passes." << std::endl;
    // Fourth test on 10 choose 4
    t = math::n_choose_r(10, 4);
    assert(((void)"210 is the answer but the function says otherwise.\n",
            t == 210));
    std::cout << "Fourth test passes." << std::endl;
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    test();  // executing tests
    return 0;
}
