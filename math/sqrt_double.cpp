/**
 * @file
 * @brief Computes square root of a positive real number using the bisection method.
 *
 * @details
 * This implementation solves the equation \f$x^2 = a\f$ using binary search.
 * Only the positive root is returned. Time complexity is \f$O(\log N)\f$.
 *
 * @note
 * Can be implemented using faster and better algorithms like:
 * - numerical_methods/newton_raphson_method.cpp
 * - numerical_methods/false_position.cpp
 */
#include <cassert>
#include <format>

/**
 * @brief Mathematical algorithms
 * @namespace
 */
namespace math {
    /** 
     * @brief Bisection method implemented for the function \f$x^2-a=0\f$
     * whose roots are \f$\pm\sqrt{a}\f$ and only the positive root is returned.
     * @param num Number to find the square root for
     * @param eps Determines the output precision. A good value lies between 1e-7 to 1e-12
     * @returns Square root of input
     */
    double Sqrt(double num, double eps = 1e-12) {
        // Error: Sqrt for neg numbers is not defined
        if (num < 0) return -1;

        // Handling floats that are 0 < x <= 1
        // (1 / sqrt(1 / num)) is same as sqrt(num)
        if ( 0 < num && num < 1 )
            return 1 / Sqrt(1 / num, eps);

        // Binary search to find the value whose
        // square is equal to or off the target by 
        // utmost eps
        double low = 0, high = num;
        while (low <= high) {
            double mid = (low + high) / 2;
            double sq = mid * mid;
            if (sq <= num && sq >= num - eps)
                return mid;
            else if (sq > num)
                high = mid;
            else
                low = mid;
        }

        return -1;
    }
} // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
void test() {
    // eps = 1e-12
    assert(std::format("{:.12f}", math::Sqrt(   2)) ==  "1.414213562373");    
    assert(std::format("{:.12f}", math::Sqrt(  17)) ==  "4.123105625618");
    assert(std::format("{:.12f}", math::Sqrt(  49)) ==  "7.000000000000");    
    assert(std::format("{:.12f}", math::Sqrt( 311)) == "17.635192088548");
    assert(std::format("{:.12f}", math::Sqrt(0.42)) ==  "0.648074069841");    
    assert(std::format("{:.12f}", math::Sqrt(0.11)) ==  "0.331662479036");    
    assert(std::format("{:.12f}", math::Sqrt(0.03)) ==  "0.173205080757");    

    // eps = 1e-8
    assert(std::format("{:.8f}", math::Sqrt(   2, 1e-8)) ==  "1.41421356");    
    assert(std::format("{:.8f}", math::Sqrt(  17, 1e-8)) ==  "4.12310563");
    assert(std::format("{:.8f}", math::Sqrt(  49, 1e-8)) ==  "7.00000000");    
    assert(std::format("{:.8f}", math::Sqrt( 311, 1e-8)) == "17.63519209");
    assert(std::format("{:.8f}", math::Sqrt(0.42, 1e-8)) ==  "0.64807407");    
    assert(std::format("{:.8f}", math::Sqrt(0.11, 1e-8)) ==  "0.33166248");    
    assert(std::format("{:.8f}", math::Sqrt(0.03, 1e-8)) ==  "0.17320508");    
}

/**
 * @brief Main Function
 * @returns 0 on exit
 */
int main() {
    test(); 
    return 0;
}
