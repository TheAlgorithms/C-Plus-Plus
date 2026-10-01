/**
 * @file
 * @brief [Conditional
 * Probability](https://en.wikipedia.org/wiki/Conditional_probability)
 * @details
 * In probability theory, conditional probability is a measure of the
 * probability of an event occurring, given that another event (by assumption,
 * presumption, assertion, or evidence) is already known to have occurred.
 *
 * This particular method relies on event A occurring with some sort of
 * relationship with another event B. In this situation, the event A can be
 * analyzed by a conditional probability with respect to B.
 *
 * If the event of interest is A and the event B is known or assumed to have
 * occurred, "the conditional probability of A given B", or "the probability of
 * A under the condition B" is given by the formula:
 *
 * \f[P(A|B) = \frac{P(A \cap B)}{P(B)}\f]
 * where: \f$P(B) > 0\f$.
 *
 *
 * @author [SomrajBanik](https://github.com/SomrajBanik)
 */

#include <cassert>    /// for assert
#include <cmath>      /// for std::fabs
#include <iostream>   /// for IO operations
#include <stdexcept>  /// for std::invalid_argument
#include <string>     /// for std::string

/**
 * @namespace probability
 * @brief Probability algorithms
 */
namespace probability {
/**
 * @namespace conditional_probability
 * @brief Functions for the [Conditional
 * Probability](https://en.wikipedia.org/wiki/Conditional_probability) algorithm
 * implementation
 */
namespace conditional_probability {
/**
 * @brief Computes the conditional probability P(X|Y)
 * @param p_intersect probability that both X and Y occur, in [0, P(Y)]
 * @param p_given probability of the event that is given (Y), in (0, 1]
 * @returns P(X|Y)
 * @throws std::invalid_argument if p_given is not in (0, 1], or if
 * p_intersect is not in [0, p_given]
 */
double conditional_compute(double p_intersect, double p_given) {
    if (p_given <= 0.0 || p_given > 1.0) {
        throw std::invalid_argument("The given probability must be in (0, 1].");
    }
    if (p_intersect < 0.0 || p_intersect > p_given) {
        throw std::invalid_argument(
            "P(intersection) must be between 0 and the given probability.");
    }

    return p_intersect / p_given;
}

}  // namespace conditional_probability
}  // namespace probability

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    using probability::conditional_probability::conditional_compute;

    const double epsilon = 1e-9;  /// tolerance for double comparison

    std::cout << "\n\n";
    std::cout << "Testing conditional probability...\n\n";

    // Test case 1
    std::cout << "Test 1: P(A and B) = 0.2, P(B) = 0.5\n";
    std::cout << "Expected: P(A|B) = 0.4\n";
    std::cout << "Result: P(A|B) = " << conditional_compute(0.2, 0.5) << "\n";
    assert(std::fabs(conditional_compute(0.2, 0.5) - 0.4) < epsilon);
    std::cout << "--PASSED--\n\n";

    // Test case 2
    std::cout << "Test 2: A always happens when B does (B is a subset of A)\n";
    std::cout << "Expected: P(A|B) = 1.0\n";
    std::cout << "Result: P(A|B) = " << conditional_compute(0.5, 0.5) << "\n";
    assert(std::fabs(conditional_compute(0.5, 0.5) - 1.0) < epsilon);
    std::cout << "--PASSED--\n\n";

    // Test case 3
    std::cout << "Test 3: A and B never happen together (mutually exclusive "
                 "events)\n";
    std::cout << "Expected: P(A|B) = 0.0\n";
    std::cout << "Result: P(A|B) = " << conditional_compute(0.0, 0.3) << "\n";
    assert(std::fabs(conditional_compute(0.0, 0.3) - 0.0) < epsilon);
    std::cout << "--PASSED--\n\n";

    // Test case 4
    std::cout << "Test 4: One die, A = 'roll is 2', B = 'roll is even'\n";
    std::cout << "Expected: P(A|B) = 1/3 or 0.333333(approx)\n";
    std::cout << "Result: P(A|B) = "
              << conditional_compute(1.0 / 6.0, 1.0 / 2.0) << " (approx) "
              << "\n";
    assert(std::fabs(conditional_compute(1.0 / 6.0, 1.0 / 2.0) - 1.0 / 3.0) <
           epsilon);
    std::cout << "--PASSED--\n\n";

    // Error handling test 1 (Test case 5)
    std::cout << "Test 5: Error handling - P(B) = 0 (invalid)\n";
    bool thrown = false;
    try {
        conditional_compute(0.2, 0.0);
    } catch (const std::invalid_argument &e) {
        std::cout << "Error caught: " << e.what() << "\n";
        assert(std::string(e.what()) ==
               "The given probability must be in (0, 1].");
        thrown = true;
    }
    assert(thrown);
    std::cout << "--PASSED--\n\n";

    // Error handling test 2 (Test case 6)
    std::cout << "Test 6: Error handling - P(A and B) < 0 (invalid)\n";
    thrown = false;
    try {
        conditional_compute(-0.1, 0.5);
    } catch (const std::invalid_argument &e) {
        std::cout << "Error caught: " << e.what() << "\n";
        assert(std::string(e.what()) ==
               "P(intersection) must be between 0 and the given probability.");
        thrown = true;
    }
    assert(thrown);
    std::cout << "--PASSED--\n\n";

    // Error handling test 3 (Test case 7)
    std::cout << "Test 7: Error handling - P(B) > 1 (invalid)\n";
    thrown = false;
    try {
        conditional_compute(0.2, 1.5);
    } catch (const std::invalid_argument &e) {
        std::cout << "Error caught: " << e.what() << "\n";
        assert(std::string(e.what()) ==
               "The given probability must be in (0, 1].");
        thrown = true;
    }
    assert(thrown);
    std::cout << "--PASSED--\n\n";

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test(); // run self test implementations
    return 0;
}
