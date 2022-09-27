/**
 * @file
 * @brief [Gram Schmidt Orthogonalisation
 * Process](https://en.wikipedia.org/wiki/Gram%E2%80%93Schmidt_process)
 *
 * @details
 * Takes the input of Linearly Independent Vectors,
 * returns vectors orthogonal to each other.
 *
 * ### Algorithm
 * Take the first vector of given LI vectors as first vector of Orthogonal
 * vectors. Take projection of second input vector on the first vector of
 * Orthogonal vector and subtract it from the 2nd LI vector. Take projection of
 * third vector on the second vector of Othogonal vectors and subtract it from
 * the 3rd LI vector. Keep repeating the above process until all the vectors in
 * the given input array are exhausted.
 *
 * For Example:
 * In R2,
 * Input LI Vectors={(3,1),(2,2)}
 * then Orthogonal Vectors= {(3, 1),(-0.4, 1.2)}
 *
 *  Have defined maximum dimension of vectors to be 10 and number of vectors
 *  taken is 20.
 *  Please do not give linearly dependent vectors
 *
 *
 * @author [Akanksha Gupta](https://github.com/Akanksha-Gupta920)
 */

#include <array>     /// for std::array
#include <cassert>   /// for assert
#include <cmath>     /// for fabs
#include <iostream>  /// for io operations

#include "math.h"

/**
 * @namespace numerical_methods
 * @brief Numerical Methods algorithms
 */
namespace numerical_methods {
/**
 * @namespace gram_schmidt
 * @brief Functions for [Gram Schmidt Orthogonalisation
 * Process](https://en.wikipedia.org/wiki/Gram%E2%80%93Schmidt_process)
 */
namespace gram_schmidt {
/**
 * Dot product function.
 * Takes 2 vectors along with their dimension as input and returns the dot
 * product.
 * @param x vector 1
 * @param y vector 2
 * @param c dimension of the vectors
 *
 * @returns sum
 */
double dot_product(const std::array<double, 10>& x,
                   const std::array<double, 10>& y, const int& c) {
    double sum = 0;
    for (int i = 0; i < c; ++i) {
        sum += x[i] * y[i];
    }
    return sum;
}

/**
 * Projection Function
 * Takes input of 2 vectors along with their dimension and evaluates their
 * projection in temp
 *
 * @param x Vector 1
 * @param y Vector 2
 * @param c dimension of each vector
 *
 * @returns factor
 */
double projection(const std::array<double, 10>& x,
                  const std::array<double, 10>& y, const int& c) {
    double dot =
        dot_product(x, y, c);  /// The dot product of two vectors is taken
    double anorm =
        dot_product(y, y, c);  /// The norm of the second vector is taken.
    double factor =
        dot /
        anorm;  /// multiply that factor with every element in a 3rd vector,
                /// whose initial values are same as the 2nd vector.
    return factor;
}

/**
 * Function to print the orthogonalised vector
 *
 * @param r number of vectors
 * @param c dimenaion of vectors
 * @param B stores orthogonalised vectors
 *
 * @returns void
 */
void display(const int& r, const int& c,
             const std::array<std::array<double, 10>, 20>& B) {
    for (int i = 0; i < r; ++i) {
        std::cout << "Vector " << i + 1 << ": ";
        for (int j = 0; j < c; ++j) {
            std::cout << B[i][j] << " ";
        }
        std::cout << '\n';
    }
}

/**
 * Function for the process of Gram Schimdt Process
 * @param r number of vectors
 * @param c dimension of vectors
 * @param A stores input of given LI vectors
 * @param B stores orthogonalised vectors
 *
 * @returns void
 */
void gram_schmidt(int r, const int& c,
                  const std::array<std::array<double, 10>, 20>& A,
                  std::array<std::array<double, 10>, 20> B) {
    if (c < r) {  /// we check whether appropriate dimensions are given or not.
        std::cout << "Dimension of vector is less than number of vector, hence "
                     "\n first "
                  << c << " vectors are orthogonalised\n";
        r = c;
    }

    int k = 1;

    while (k <= r) {
        if (k == 1) {
            for (int j = 0; j < c; j++)
                B[0][j] = A[0][j];  /// First vector is copied as it is.
        }

        else {
            std::array<double, 10>
                all_projection{};  /// array to store projections
            for (int i = 0; i < c; ++i) {
                all_projection[i] = 0;  /// First initialised to zero
            }

            int l = 1;
            while (l < k) {
                std::array<double, 10>
                    temp{};           /// to store previous projected array
                double factor = NAN;  /// to store the factor by which the
                                      /// previous array will change
                factor = projection(A[k - 1], B[l - 1], c);
                for (int i = 0; i < c; ++i) {
                    temp[i] = B[l - 1][i] * factor;  /// projected array created
                }
                for (int j = 0; j < c; ++j) {
                    all_projection[j] =
                        all_projection[j] +
                        temp[j];  /// we take the projection with all the
                                  /// previous vector and add them.
                }
                l++;
            }
            for (int i = 0; i < c; ++i) {
                B[k - 1][i] =
                    A[k - 1][i] -
                    all_projection[i];  /// subtract total projection vector
                                        /// from the input vector
            }
        }
        k++;
    }
    display(r, c, B);  // for displaying orthogoanlised vectors
}
}  // namespace gram_schmidt
}  // namespace numerical_methods
/**
 * Test Function. Process has been tested for 3 Sample Inputs
 * @returns void
 */
static void test() {
    std::array<std::array<double, 10>, 20> a1 = {
        {{1, 0, 1, 0}, {1, 1, 1, 1}, {0, 1, 2, 1}}};
    std::array<std::array<double, 10>, 20> b1 = {{0}};
    double dot1 = 0;
    numerical_methods::gram_schmidt::gram_schmidt(3, 4, a1, b1);
    int flag = 1;
    for (int i = 0; i < 2; ++i) {
        for (int j = i + 1; j < 3; ++j) {
            dot1 = fabs(
                numerical_methods::gram_schmidt::dot_product(b1[i], b1[j], 4));
            if (dot1 > 0.1) {
                flag = 0;
                break;
            }
        }
    }
    if (flag == 0)
        std::cout << "Vectors are linearly dependent\n";
    assert(flag == 1);
    std::cout << "Passed Test Case 1\n ";

    std::array<std::array<double, 10>, 20> a2 = {{{3, 1}, {2, 2}}};
    std::array<std::array<double, 10>, 20> b2 = {{0}};
    double dot2 = 0;
    numerical_methods::gram_schmidt::gram_schmidt(2, 2, a2, b2);
    flag = 1;
    for (int i = 0; i < 1; ++i) {
        for (int j = i + 1; j < 2; ++j) {
            dot2 = fabs(
                numerical_methods::gram_schmidt::dot_product(b2[i], b2[j], 2));
            if (dot2 > 0.1) {
                flag = 0;
                break;
            }
        }
    }
    if (flag == 0)
        std::cout << "Vectors are linearly dependent\n";
    assert(flag == 1);
    std::cout << "Passed Test Case 2\n";

    std::array<std::array<double, 10>, 20> a3 = {{{1, 2, 2}, {-4, 3, 2}}};
    std::array<std::array<double, 10>, 20> b3 = {{0}};
    double dot3 = 0;
    numerical_methods::gram_schmidt::gram_schmidt(2, 3, a3, b3);
    flag = 1;
    for (int i = 0; i < 1; ++i) {
        for (int j = i + 1; j < 2; ++j) {
            dot3 = fabs(
                numerical_methods::gram_schmidt::dot_product(b3[i], b3[j], 3));
            if (dot3 > 0.1) {
                flag = 0;
                break;
            }
        }
    }
    if (flag == 0)
        std::cout << "Vectors are linearly dependent\n";
    assert(flag == 1);
    std::cout << "Passed Test Case 3\n";
}

/**
 * @brief Main Function
 * @return 0 on exit
 */
int main() {
    int r = 0, c = 0;
    test();  // perform self tests
    std::cout << "Enter the dimension of your vectors\n";
    std::cin >> c;
    std::cout << "Enter the number of vectors you will enter\n";
    std::cin >> r;

    std::array<std::array<double, 10>, 20>
        A{};  /// a 2-D array for storing all vectors
    std::array<std::array<double, 10>, 20> B = {
        {0}};  /// a 2-D array for storing orthogonalised vectors
    /// storing vectors in array A
    for (int i = 0; i < r; ++i) {
        std::cout << "Enter vector " << i + 1
                  << '\n';  /// Input of vectors is taken
        for (int j = 0; j < c; ++j) {
            std::cout << "Value " << j + 1 << "th of vector: ";
            std::cin >> A[i][j];
        }
        std::cout << '\n';
    }

    numerical_methods::gram_schmidt::gram_schmidt(r, c, A, B);

    double dot = 0;
    int flag = 1;  /// To check whether vectors are orthogonal or  not
    for (int i = 0; i < r - 1; ++i) {
        for (int j = i + 1; j < r; ++j) {
            dot = fabs(
                numerical_methods::gram_schmidt::dot_product(B[i], B[j], c));
            if (dot > 0.1)  /// take make the process numerically stable, upper
                            /// bound for the dot product take 0.1
            {
                flag = 0;
                break;
            }
        }
    }
    if (flag == 0)
        std::cout << "Vectors are linearly dependent\n";
    return 0;
}
