/**
 * @file
 * \brief Compute real eigen values and eigen vectors of a symmetric matrix
 * using [QR decomposition](https://en.wikipedia.org/wiki/QR_decomposition)
 * method.
 * \author [Krishna Vedala](https://github.com/kvedala)
 */
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#ifdef _OPENMP
#include <omp.h>
#endif

#include "./qr_decompose.h"
using qr_algorithm::operator<<;

#define LIMS 9 /**< limit of range of matrix values */

/**
 * create a symmetric square matrix of given size with random elements. A
 * symmetric square matrix will *always* have real eigen values.
 *
 * \param[out] A matrix to create (must be pre-allocated in memory)
 */
void create_matrix(std::valarray<std::valarray<double>> *A) {
    int i, j, tmp, lim2 = LIMS >> 1;
    int N = A->size();

#ifdef _OPENMP
#pragma omp for
#endif
    for (i = 0; i < N; i++) {
        A[0][i][i] = (std::rand() % LIMS) - lim2;
        for (j = i + 1; j < N; j++) {
            tmp = (std::rand() % LIMS) - lim2;
            A[0][i][j] = tmp;  // summetrically distribute random values
            A[0][j][i] = tmp;
        }
    }
}

/**
 * Perform multiplication of two matrices.
 * * R2 must be equal to C1
 * * Resultant matrix size should be R1xC2
 * \param[in] A first matrix to multiply
 * \param[in] B second matrix to multiply
 * \param[out] OUT output matrix (must be pre-allocated)
 * \returns pointer to resultant matrix
 */
void mat_mul(const std::valarray<std::valarray<double>> &A,
             const std::valarray<std::valarray<double>> &B,
             std::valarray<std::valarray<double>> *OUT) {
    int R1 = A.size();
    int C1 = A[0].size();
    int R2 = B.size();
    int C2 = B[0].size();
    if (C1 != R2) {
        perror("Matrix dimensions mismatch!");
        return;
    }

    for (int i = 0; i < R1; i++) {
        for (int j = 0; j < C2; j++) {
            OUT[0][i][j] = 0.f;
            for (int k = 0; k < C1; k++) {
                OUT[0][i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

namespace qr_algorithm {
/** Compute eigen values using iterative shifted QR decomposition algorithm as
 * follows:
 * 1. Use last diagonal element of A as eigen value approximation \f$c\f$
 * 2. Shift diagonals of matrix \f$A' = A - cI\f$
 * 3. Decompose matrix \f$A'=QR\f$
 * 4. Compute next approximation \f$A'_1 = RQ \f$
 * 5. Shift diagonals back \f$A_1 = A'_1 + cI\f$
 * 6. Termination condition check: last element below diagonal is almost 0
 *   1. If not 0, go back to step 1 with the new approximation \f$A_1\f$
 *   2. If 0, continue to step 7
 * 7. Save last known \f$c\f$ as the eigen value.
 * 8. Are all eigen values found?
 *   1. If not, remove last row and column of \f$A_1\f$ and go back to step 1.
 *   2. If yes, stop.
 *
 * \note The matrix \f$A\f$ gets modified
 *
 * \param[in,out] A matrix to compute eigen values for
 * \param[in] print_intermediates (optional) whether to print intermediate A, Q
 * and R matrices (default = `false`)
 */
std::valarray<double> eigen_values(std::valarray<std::valarray<double>> *A,
                                   bool print_intermediates = false) {
    int rows = A->size();
    int columns = rows;
    int counter = 0, num_eigs = rows - 1;
    double last_eig = 0;

    std::valarray<std::valarray<double>> Q(rows);
    std::valarray<std::valarray<double>> R(columns);

    /* number of eigen values = matrix size */
    std::valarray<double> eigen_vals(rows);
    for (int i = 0; i < rows; i++) {
        Q[i] = std::valarray<double>(columns);
        R[i] = std::valarray<double>(columns);
    }

    /* continue till all eigen values are found */
    while (num_eigs > 0) {
        /* iterate with QR decomposition */
        while (std::abs(A[0][num_eigs][num_eigs - 1]) >
               std::numeric_limits<double>::epsilon()) {
            // initial approximation = last diagonal element
            last_eig = A[0][num_eigs][num_eigs];
            for (int i = 0; i < rows; i++) {
                A[0][i][i] -= last_eig; /* A - cI */
            }

            qr_decompose(*A, &Q, &R);

            if (print_intermediates) {
                std::cout << *A << "\n";
                std::cout << Q << "\n";
                std::cout << R << "\n";
                printf("-------------------- %d ---------------------\n",
                       ++counter);
            }

            // new approximation A' = R * Q
            mat_mul(R, Q, A);

            for (int i = 0; i < rows; i++) {
                A[0][i][i] += last_eig; /* A + cI */
            }
        }

        /* store the converged eigen value */
        eigen_vals[num_eigs] = last_eig;
        // A[0][num_eigs][num_eigs];
        if (print_intermediates) {
            std::cout << "========================\n";
            std::cout << "Eigen value: " << last_eig << ",\n";
            std::cout << "========================\n";
        }

        num_eigs--;
        rows--;
        columns--;
    }
    eigen_vals[0] = A[0][0][0];

    if (print_intermediates) {
        std::cout << Q << "\n";
        std::cout << R << "\n";
    }

    return eigen_vals;
}

}  // namespace qr_algorithm

/**
 * test function to compute eigen values of a 2x2 matrix
 * \f[\begin{bmatrix}
 * 5 & 7\\
 * 7 & 11
 * \end{bmatrix}\f]
 * which are approximately, {15.56158, 0.384227}
 */
void test1() {
    std::valarray<std::valarray<double>> X = {{5, 7}, {7, 11}};
    double y[] = {15.56158, 0.384227};  // corresponding y-values

    std::cout << "------- Test 1 -------" << std::endl;
    std::valarray<double> eig_vals = qr_algorithm::eigen_values(&X);

    for (int i = 0; i < 2; i++) {
        std::cout << i + 1 << "/2 Checking for " << y[i] << " --> ";
        bool result = false;
        for (int j = 0; j < 2 && !result; j++) {
            if (std::abs(y[i] - eig_vals[j]) < 0.1) {
                result = true;
                std::cout << "(" << eig_vals[j] << ") ";
            }
        }
        assert(result);  // ensure that i^th expected eigen value was computed
        std::cout << "found\n";
    }
    std::cout << "Test 1 Passed\n\n";
}

/**
 * test function to compute eigen values of a 2x2 matrix
 * \f[\begin{bmatrix}
 * -4& 4& 2& 0& -3\\
 * 4& -4& 4& -3& -1\\
 * 2& 4& 4& 3& -3\\
 * 0& -3& 3& -1&-1\\
 * -3& -1& -3& -3& 0
 * \end{bmatrix}\f]
 * which are approximately, {9.27648, -9.26948, 2.0181, -1.03516, -5.98994}
 */
void test2() {
    std::valarray<std::valarray<double>> X = {{-4, 4, 2, 0, -3},
                                              {4, -4, 4, -3, -1},
                                              {2, 4, 4, 3, -3},
                                              {0, -3, 3, -1, -3},
                                              {-3, -1, -3, -3, 0}};
    double y[] = {9.27648, -9.26948, 2.0181, -1.03516,
                  -5.98994};  // corresponding y-values

    std::cout << "------- Test 2 -------" << std::endl;
    std::valarray<double> eig_vals = qr_algorithm::eigen_values(&X);

    std::cout << X << "\n"
              << "Eigen values: " << eig_vals << "\n";

    for (int i = 0; i < 5; i++) {
        std::cout << i + 1 << "/5 Checking for " << y[i] << " --> ";
        bool result = false;
        for (int j = 0; j < 5 && !result; j++) {
            if (std::abs(y[i] - eig_vals[j]) < 0.1) {
                result = true;
                std::cout << "(" << eig_vals[j] << ") ";
            }
        }
        assert(result);  // ensure that i^th expected eigen value was computed
        std::cout << "found\n";
    }
    std::cout << "Test 2 Passed\n\n";
}

/**
 * main function
 */
int main(int argc, char **argv) {
    int mat_size = 5;
    if (argc == 2) {
        mat_size = atoi(argv[1]);
    } else {  // if invalid input argument is given run tests
        test1();
        test2();
        std::cout << "Usage: ./qr_eigen_values [mat_size]\n";
        return 0;
    }

    if (mat_size < 2) {
        fprintf(stderr, "Matrix size should be > 2\n");
        return -1;
    }

    // initialize random number generator
    std::srand(std::time(nullptr));

    int i, rows = mat_size, columns = mat_size;

    std::valarray<std::valarray<double>> A(rows);

    for (int i = 0; i < rows; i++) {
        A[i] = std::valarray<double>(columns);
    }

    /* create a random matrix */
    create_matrix(&A);

    std::cout << A << "\n";

    clock_t t1 = clock();
    std::valarray<double> eigen_vals = qr_algorithm::eigen_values(&A);
    double dtime = static_cast<double>(clock() - t1) / CLOCKS_PER_SEC;

    std::cout << "Eigen vals: ";
    for (i = 0; i < mat_size; i++) std::cout << eigen_vals[i] << "\t";
    std::cout << "\nTime taken to compute: " << dtime << " sec\n";

    return 0;
}
