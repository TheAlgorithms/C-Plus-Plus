/**
 * @file
 * @brief Implementation of [Freivalds' algorithm]
 * (https://en.wikipedia.org/wiki/Freivalds%27_algorithm)
 * @author [Darshana Sarma](https://github.com/Darshana-Sarma)
 * @details
 * Given three n × n matrices A, B, and
 * C, a general problem is to verify whether AB=C
 *
 * It is a randomised algorithm with the probability of success 1-1/2^(m) i.e.
 * close to 1 The time Complexity of the algorithm is O(n^{2}).
 */
#include <array>     //   for std::array
#include <cassert>   //   for assert
#include <iostream>  //   for io operations

/**
 * @namespace others
 * @brief Other algorithms
 */
namespace others {
/**
 * @namespace freivalds
 * @brief Functions for [Freivalds']
 * (https://en.wikipedia.org/wiki/Freivalds%27_algorithm) algorithm
 */
namespace freivalds {
/**
 * The function will check AB=C by applying Freidvald's algorithm
 * @tparam N dimension of square matrix NxN
 * @param A square matrix A
 * @param B square matrix B
 * @param C resultant square matrix C
 * @returns boolean value
 */
template <std::size_t N>
bool CoppersmithAlgo(const std::array<std::array<double, N>, N> A,
                     const std::array<std::array<double, N>, N> B,
                     const std::array<std::array<double, N>, N> C) {
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
}  // namespace freivalds
}  // namespace others

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

    bool result = others::freivalds::CoppersmithAlgo(A, B, C);
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

    bool result = others::freivalds::CoppersmithAlgo(A, B, C);
    std::cout << result << "\n";

    assert(result == false);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test_1();
    test_2();

    return 0;
}
