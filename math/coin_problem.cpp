/**
 * @file
 * @brief A program to solve the coin problem (https://en.wikipedia.org/wiki/Coin_problem)
 * @details
 * The coin problem is a math riddle also known as the Frobenius coin problem,
 * postage stamp problem, and Chicken McNugget Theorem. The problem asks that
 * given 2 items with different positive weights/value (for example coins/stamps with monetary value),
 * what is the largest total weight/value that cannot be achieved using any combination of
 * those two items? If the two items (a & b) are relatively prime, this can be solved using the
 * formula (a*b)-(a+b). If they are not relatively prime, there is no solution.
 * @author [Jason Baron](https://github.com/pkyu)
 */

#include <cassert>   /// for assert
#include <iostream>  /// for std::cin and std::cout

 /**
  * @namespace math
  * @brief Mathematical algorithms
  */
namespace math {

    /**
     * @brief Determine if the numbers are relatively prime.
     * If they are, return the solution using Frobenius number formula.
     * If not, there is no solution. Return -1.
     * @param a,b input numbers
     * @return answer
     */

    int coin_problem(int a, int b) {
        /// Compute solution if they were relatively prime
        int solution = (a * b) - (a + b);
        /// Use Euclid's algorithm to find GCD
        while (a != b) {
            if (a > b) a = a - b;
            else b = b - a;
        }
        /// If GCD is 1, a & b are relatively prime - return solution.
        /// If GCD is not 1, there is no solution - return -1.
        if (a == 1) return solution;
        return -1;
    }
} // namespace math

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    std::cout << "a=3, b=7";
    assert(math::coin_problem(3, 7) == 11);
    std::cout << "\npass\n";

    std::cout << "a=2, b=23";
    assert(math::coin_problem(2, 23) == 21);
    std::cout << "\npass\n";

    std::cout << "a=23, b=45";
    assert(math::coin_problem(23, 45) == 967);
    std::cout << "\npass\n";

    std::cout << "a=455, b=93";
    assert(math::coin_problem(455, 93) == 41767);
    std::cout << "\npass\n";

    std::cout << "a=4, b=6";
    assert(math::coin_problem(4, 6) == -1);
    std::cout << "\npass\n";

    std::cout << "a=1, b=1";
    assert(math::coin_problem(3, 3) == -1);
    std::cout << "\npass\n";
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char* argv[]) {
    test();  // run self-test implementations
    return 0;
}
