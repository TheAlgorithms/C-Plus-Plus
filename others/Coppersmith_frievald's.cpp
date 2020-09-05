/**
 * @file
 * @brief Implementation of [Freivalds' algorithm]
 * (https://en.wikipedia.org/wiki/Freivalds%27_algorithm)
 * @author [Darshana Sarma](https://github.com/Darshana-Sarma)
 * @details
 * Given three n Ã— n matrices A, B, and
 * C, a general problem is to verify whether AB=C
 *
 * The time Complexity of the algorithm is O(n^{2}).
 */
#include <array>     //for std::array
#include <cassert>   //for assert
#include <iostream>  //for io operations

/**
 * Freivald's algorithm
 * The function will will check AB=C
 * @param A matrix A
 * @param B matrix B
 * @param C resultant matrix C
 * @returns boolean value
 */
template <std::size_t N>
bool CoppersmithAlgo(std::array<std::array<double, N>, N> A,
                     std::array<std::array<double, N>, N> B,
                     std::array<std::array<double, N>, N> C) {
    // Printing matrix A
    std::cout << "\nThe first matrix is:\n ";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << A[i][j] << "\t";
        }
        std::cout << "\n";
    }

    // Printing matrix B
    std::cout << "\nThe Second matrix is:\n ";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << B[i][j] << "\t";
        }
        std::cout << "\n";
    }

    // Printing matrix C
    std::cout << "The resultant matrix: \n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << C[i][j] << "\t";
        }
        std::cout << "\n";
    }
    // generate a random nx1 vector r containing 0/1 elements
    std::array<std::array<const double, N>, 1> a{0};

    // Multiply matrix B with vector 'r' which gives a nx1 vector 'br'
    std::array<std::array<double, N>, 1> br = {};

    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            br[i][0] = br[i][0] + B[i][k] * a[k][0];
        }
    }
    // multiply matrix C with vector 'r' which gives a nx1 vector 'cr'
    std::array<std::array<double, N>, 1> cr{0};
    // double cr[N][1];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 1; j++) {
            for (int k = 0; k < N; k++) {
                cr[i][j] = cr[i][j] + C[i][k] * a[k][j];
            }
        }
    }
    // multiply matrix A with the nx1 matrix 'br' to form a nx1 vector 'abr'
    std::array<std::array<double, N>, 1> abr{0};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 1; j++) {
            for (int k = 0; k < N; k++) {
                abr[i][j] = abr[i][j] + A[i][k] * br[k][j];
            }
        }
    }
    // compute vector p=abr - cr
    for (int i = 0; i < N; i++) {
        abr[i][0] -= cr[i][0];
    }

    // if vector p= 0 then A x B = C
    // if vector p != 0 then A x B != C
    bool flag = true;
    for (int i = 0; i < N; i++) {
        if (abr[i][0] == 0) {
            continue;
        } else {
            flag = false;
        }
    }
    if (flag == true) {
        std::cout << "\nC is the product of matrix A and C\n";
    } else {
        std::cout << "\nC is not the product of matrix A and C\n";
    }
    return flag;
}
/**
 * Error Analysis: If {\displaystyle A\times B=C}{\displaystyle A\times B=C},
 *then the algorithm always returns "Yes". If {\displaystyle A\times B\neq C}A
 *\times B \neq C, then the probability that the algorithm returns "Yes" is less
 *than or equal to one half. This is called one-sided error. By iterating the
 *algorithm k times and returning "Yes" only if all iterations yield "Yes", a
 *runtime of O(kn^{2})and error probability of <= 1/(2^k) is achieve
 */

/**
 * Test function 1 with A = [[1,0],[2,1]]
 * B = [[5,4],[-5,1]]
 * B = [[5,4],[5,9]]
 * @returns none
 */

static void test_1() {
    std::array<std::array<double, 2>, 2> A = {{{1, 0}, {2, 1}}};

    std::array<std::array<double, 2>, 2> B = {{{5, 4}, {-5, 1}}};

    std::array<std::array<double, 2>, 2> C = {{{5, 4}, {5, 9}}};

    bool result = CoppersmithAlgo(A, B, C);
    std::cout << result << "\n";

    assert(result == true);
}

/**
 * Test function 2 with A = [[5,4],[-5,1]]
 * B = [[1,0],[2,1]]
 * B = [[5,4],[5,9]]
 * @returns none
 */
static void test_2() {
    std::array<std::array<double, 2>, 2> A = {{{5, 4}, {-5, 1}}};

    std::array<std::array<double, 2>, 2> B = {{{1, 0}, {2, 1}}};

    std::array<std::array<double, 2>, 2> C = {{{5, 4}, {5, 9}}};

    bool result = CoppersmithAlgo(A, B, C);
    std::cout << result << "\n";

    assert(result == false);
}

/**
 * Main function
 */
int main() {
    test_1();
    test_2();

    return 0;
}