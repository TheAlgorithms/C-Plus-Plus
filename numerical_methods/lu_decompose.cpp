/**
 * \file
 * \brief [LU decomposition](https://en.wikipedia.org/wiki/LU_decompositon) of a
 * square matrix
 * \author [Krishna Vedala](https://github.com/kvedala)
 */
#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>
#ifdef _OPENMP
#include <omp.h>
#endif

/** Perform LU decomposition on matrix
 * \param[in] A matrix to decompose
 * \param[out] L output L matrix
 * \param[out] U output U matrix
 * \returns 0 if no errors
 * \returns negative if error occurred
 */
int lu_decomposition(const std::vector<std::vector<double>> &A,
                     std::vector<std::vector<double>> *L,
                     std::vector<std::vector<double>> *U) {
    int row, col, j;
    int mat_size = A.size();

    if (mat_size != A[0].size()) {
        // check matrix is a square matrix
        std::cerr << "Not a square matrix!\n";
        return -1;
    }

    // regularize each row
    for (row = 0; row < mat_size; row++) {
        // Upper triangular matrix
#ifdef _OPENMP
#pragma omp for
#endif
        for (col = row; col < mat_size; col++) {
            // Summation of L[i,j] * U[j,k]
            double lu_sum = 0.;
            for (j = 0; j < row; j++) lu_sum += L[0][row][j] * U[0][j][col];

            // Evaluate U[i,k]
            U[0][row][col] = A[row][col] - lu_sum;
        }

        // Lower triangular matrix
#ifdef _OPENMP
#pragma omp for
#endif
        for (col = row; col < mat_size; col++) {
            if (row == col) {
                L[0][row][col] = 1.;
                continue;
            }

            // Summation of L[i,j] * U[j,k]
            double lu_sum = 0.;
            for (j = 0; j < row; j++) lu_sum += L[0][col][j] * U[0][j][row];

            // Evaluate U[i,k]
            L[0][col][row] = (A[col][row] - lu_sum) / U[0][row][row];
        }
    }

    return 0;
}

/**
 * operator to print a matrix
 */
template <typename T>
std::ostream &operator<<(std::ostream &out,
                         std::vector<std::vector<T>> const &v) {
    const int width = 10;
    const char separator = ' ';

    for (size_t row = 0; row < v.size(); row++) {
        for (size_t col = 0; col < v[row].size(); col++)
            out << std::left << std::setw(width) << std::setfill(separator)
                << v[row][col];
        out << std::endl;
    }

    return out;
}

/** Main function */
int main(int argc, char **argv) {
    int mat_size = 3;  // default matrix size
    const int range = 50;
    const int range2 = range >> 1;

    if (argc == 2)
        mat_size = atoi(argv[1]);

    std::srand(std::time(NULL));  // random number initializer

    /* Create a square matrix with random values */
    std::vector<std::vector<double>> A(mat_size);
    std::vector<std::vector<double>> L(mat_size);  // output
    std::vector<std::vector<double>> U(mat_size);  // output
    for (int i = 0; i < mat_size; i++) {
        // calloc so that all valeus are '0' by default
        A[i] = std::vector<double>(mat_size);
        L[i] = std::vector<double>(mat_size);
        U[i] = std::vector<double>(mat_size);
        for (int j = 0; j < mat_size; j++)
            /* create random values in the limits [-range2, range-1] */
            A[i][j] = static_cast<double>(rand() % range - range2);
    }

    std::clock_t start_t = std::clock();
    lu_decomposition(A, &L, &U);
    std::clock_t end_t = std::clock();
    std::cout << "Time taken: "
              << static_cast<double>(end_t - start_t) / CLOCKS_PER_SEC << "\n";

    std::cout << "A = \n" << A << "\n";
    std::cout << "L = \n" << L << "\n";
    std::cout << "U = \n" << U << "\n";

    return 0;
}
