/**
 * @file
 * @brief Exponentiating by squaring is a general method for fast computation of large positive integer powers of a number.
 * (https://en.wikipedia.org/wiki/Exponentiation_by_squaring)
 *@details
 * Program that computes \f$a^b\f$ in \f$O(logN)\f$ time.
 * It is based on formula that:
 * 1. if \f$b\f$ is even:
 *  \f$a^b = a^\frac{b}{2} \cdot a^\frac{b}{2} = {a^\frac{b}{2}}^2\f$
 * 2. if \f$b\f$ is odd: \f$a^b = a^\frac{b-1}{2}
 *  \cdot a^\frac{b-1}{2} \cdot a = {a^\frac{b-1}{2}}^2 \cdot a\f$
 *
 * We can compute \f$a^b\f$ recursively using above algorithm.
 * @author
 * @see
 */

#include <cassert>  /// for assert
#include <cmath>    /// for std::pow
#include <cstdint>  /// for int64_t
#include <cstdlib>  /// for std::rand
#include <ctime>    /// for std::time
#include <iostream> /// for IO operations


/**
 * @namespace math
 * @brief algorithm implementation for \f$a^b\f$
 */

namespace math {

/**
 * @brief Functions for fast computation of large positive integer powers of a number.
 * @param a The base
 * @param b The exponent
 * @returns The result of \f$a^b\f$
 */

    template <typename T>
    double fast_power_recursive(T a, T b) {
        /*When the base number is 0 and the exponent is non-positive, it is defined as meaningless
        */
        if(a==0 && b<=0){
            return NAN;
        }

        // negative power. a^b = 1 / (a^-b)
        if (b < 0)
            return 1.0 / fast_power_recursive(a, -b);

        if (b == 0)
            return 1;
        T bottom = fast_power_recursive(a, b >> 1);
        // Since it is integer division b/2 = (b-1)/2 where b is odd.
        // Therefore, case2 is easily solved by integer division.

        double result;
        if ((b & 1) == 0)  // case1
            result = bottom * bottom;
        else  // case2
            result = bottom * bottom * a;
        return result;
    }

/**
    Same algorithm with little different formula.
    It still calculates in \f$O(\log N)\f$
*/
    template <typename T>
    double fast_power_linear(T a, T b) {
        /*When the base number is 0 and the exponent is non-positive, it is defined as meaningless
        */
        if(a==0 && b<=0){
            return NAN;
        }

        // negative power. a^b = 1 / (a^-b)
        if (b < 0)
            return 1.0 / fast_power_linear(a, -b);

        double result = 1;
        while (b) {
            if (b & 1)
                result = result * a;
            a = a * a;
            b = b >> 1;
        }
        return result;
    }

}// namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    /* The following program will generate and test 1000 pairs of random base and exponential combinations 
    (ranging from -10 to 9), simulating power operations. The results of verifying fast_power_recursive(a, b) 
    and fast_power_linear(a, b) are identical to those of the standard library functions std::pow(a, b) 
    */
    std::srand(std::time(nullptr));
    std::ios_base::sync_with_stdio(false);
    /*When the exponent is negative, it is often unreliable to use the == operator directly.
    When comparing comparison results, we use a small threshold (epsilon) to determine whether they are "close enough."
    */
    const double epsilon = 1e-8;

    for (int i = 0; i < 1000; i++) {
        int a = std::rand() % 20 - 10;
        int b = std::rand() % 20 - 10;
        /*When the base number is 0 and the exponent is non-positive, it is defined as meaningless
        */
        if(a==0&&b<=0){
            continue;
        }
        double result_recursive = math::fast_power_recursive(a, b);
        double result_linear = math::fast_power_linear(a, b);
        double result_pow = std::pow(a, b);

        assert(std::fabs(result_recursive - result_pow) < epsilon);
        assert(std::fabs(result_linear - result_pow) < epsilon);
    }

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main() {

    test();  // run self-test implementations
    // std::cout << math::fast_power_recursive(-10, -10) << "\n"<<std::pow(-10, -10)<<std::endl;
    return 0;
}
