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
 * {1,3}, {1,4}, {2,3}, {2,4}, and {3,4}, so \f$ \binom{4}{2} =6.\f$ " [Another good
 * example/explanation](https://math.stackexchange.com/questions/2172355/probability-notation-two-numbers-stacked-inside-brackets)
 *
 * @note An identity of the binomial coefficient is \f$ \binom{n}{n-k} \f$ This is explained
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
 * @namespace binomial
 * @brief Functions for [Binomial
 * coefficients](https://en.wikipedia.org/wiki/Binomial_coefficient)
 * implementation
 */
namespace binomial {
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
     * Why do we do if k > (n/2) then k = n-k? Because \f$ \binom{n}{k} \f$ is the same as
     * \f$ \binom{n}{n-k} \f$ or, in this case, \f$ \binom{6}{4} \f$ is the same as \f$ \binom{6}{2} \f$ since both are
     * calculated for \f$ n!/k!(n-k)! \f$, in this case \f$ 6!/4!2! \f$. By replacing \f$ k \f$ with
     * \f$ n-k \f$ we get \f$ 6!/2!4! \f$ which is the same sum. the benefit however, is our
     * loop further on in this implementation now requires less iterations to
     * find the same answer.
     *
     * k == 1 and k == 0 follow the same rule as \f$ n^1 \f$and \f$ n^0 \f$ respectively
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
}  // namespace binomial

/**
 * @brief Test implementations
 * @returns void
 */
static void tests() {
    assert(binomial::calculate(1, 1) == 1);
    assert(binomial::calculate(57, 57) == 1);
    assert(binomial::calculate(6, 3) == 20);
    assert(binomial::calculate(10, 5) == 252);
    assert(binomial::calculate(20, 10) == 184756);
    assert(binomial::calculate(30, 15) == 155117520);
    assert(binomial::calculate(40, 20) == 137846528820);
    assert(binomial::calculate(50, 25) == 126410606437752);
    assert(binomial::calculate(60, 30) == 118264581564861424);
    assert(binomial::calculate(62, 31) == 465428353255261088);

    std::cout << "Binomial coefficients tests successfully passed"
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
