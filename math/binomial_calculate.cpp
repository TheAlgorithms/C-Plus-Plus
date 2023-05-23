/**
 * @file
 * @brief Program to calculate [Binomial
 * coefficients](https://en.wikipedia.org/wiki/Binomial_coefficient)
 *
 * @details
 * quoted from: [Weisstein, Eric W. "Binomial Coefficient." From MathWorld--A
 * Wolfram Web
 * Resource.](https://mathworld.wolfram.com/BinomialCoefficient.html) "The
 * binomial coefficient \f$ \binom{n}{k} \f$ is the number of ways of picking \f$k\f$ unordered
 * outcomes from \f$n\f$ possibilities, also known as a combination or combinatorial
 * number. The symbols \f$ _nC_k \f$ and \f$ \binom{n}{k} \f$ are used to
 * denote a binomial coefficient, and are sometimes read as "n choose k." \f$ \binom{n}{k} \f$
 * therefore gives the number of k-subsets possible out of a set of n distinct
 * items. For example, The 2-subsets of {1,2,3,4} are the six pairs {1,2},
 * {1,3}, {1,4}, {2,3}, {2,4}, and {3,4}, so (4; 2)=6." [Another good
 * example/explanation](https://math.stackexchange.com/questions/2172355/probability-notation-two-numbers-stacked-inside-brackets)
 *
 * @note An identity of the binomial coefficient is (n; n-k) This is explained
 * partially in the comments of this implementation but in more detail at [Prof.
 * Tesler: Chapter 3.3, 4.1, 4.3. Binomial Coefficient
 * Identities](https://mathweb.ucsd.edu/~gptesler/184a/slides/184a_ch4slides_17-handout.pdf
 * page 2)
 *
 * @author [astronmax](https://github.com/astronmax)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for IO operations

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
/**
 * @brief Function to calculate binomial coefficients
 * @param n number of possibilities
 * @param k size of subset
 * @return n if k == 1
 * @return 1 if k == 0
 * @return result if k != 0 || 1
 */
size_t calculate(int32_t n, int32_t k) {
    /*!
     * Why do we do if k > (n/2) then k = n-k? Because (n;k) is the same as
     * (n;n-k) or, in this case, (6;4) is the same as (6;2) since both are
     * calculated for n!/k!(n-k)! , in this case 6!/4!2! . By replacing k with
     * n-k we get 6!/2!4! which is the same sum. the benefit however, is our
     * loop further on in this implementation now requires less iterations to
     * find the same answer.
     *
     * k == 1 and k == 0 follow the same rule as n^1 and n^0 respectively
     */
    if (k == 0) {
        return 1;
    } else if (k == 1) {
        return n;
    } else if (k > (n / 2)) {
        k = n - k;
    }

    /*!
     * (n - k) + i returns 1 higher each loop imitating a factorial calculation.
     * Then imagine i as the size of each set, divide by it to find the amount
     * of possible sets in result amount of possibilities
     */
    size_t result = 1;
    for (int32_t i = 1; i <= k; ++i) {
        result *= (n - k) + i;
        result /= i;
    }

    return result;
}
}  // namespace math

/**
 * @brief Test implementations
 * @returns void
 */
static void tests() {
    assert(math::calculate(1, 1) == 1);
    assert(math::calculate(57, 57) == 1);
    assert(math::calculate(6, 3) == 20);
    assert(math::calculate(10, 5) == 252);
    assert(math::calculate(20, 10) == 184756);
    assert(math::calculate(30, 15) == 155117520);
    assert(math::calculate(40, 20) == 137846528820);
    assert(math::calculate(50, 25) == 126410606437752);
    assert(math::calculate(60, 30) == 118264581564861424);
    assert(math::calculate(62, 31) == 465428353255261088);

    std::cout << "[+] Binomial coefficients calculate test completed"
              << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();  // run self-test implementations
    return 0;
}
