/**
 * @file lu_decomposition.h
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @brief Functions associated with [LU
 * Decomposition](https://en.wikipedia.org/wiki/LU_decomposition)
 * of a square matrix.
 */
#pragma once

#include <iostream>
#include <valarray>
#include <vector>
#ifdef _OPENMP
#include <omp.h>
#endif

/** Define matrix type as a `std::vector` of `std::valarray` */
template <typename T>
using matrix = std::vector<std::valarray<T>>;

/** Perform LU decomposition on matrix
 * \param[in] A matrix to decompose
 * \param[out] L output L matrix
 * \param[out] U output U matrix
 * \returns 0 if no errors
 * \returns negative if error occurred
 */
template <typename T>
int lu_decomposition(const matrix<T> &A, matrix<double> *L, matrix<double> *U) {
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
            for (j = 0; j < row; j++) {
                lu_sum += L[0][row][j] * U[0][j][col];
            }

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
            for (j = 0; j < row; j++) {
                lu_sum += L[0][col][j] * U[0][j][row];
            }

            // Evaluate U[i,k]
            L[0][col][row] = (A[col][row] - lu_sum) / U[0][row][row];
        }
    }

    return 0;
}

/**
 * Compute determinant of an NxN square matrix using LU decomposition.
 * Using LU decomposition, the determinant is given by the product of diagonal
 * elements of matrices L and U.
 *
 * @tparam T datatype of input matrix - int, unsigned int, double, etc
 * @param A input square matrix
 * @return determinant of matrix A
 */
template <typename T>
double determinant_lu(const matrix<T> &A) {
    matrix<double> L(A.size(), std::valarray<double>(A.size()));
    matrix<double> U(A.size(), std::valarray<double>(A.size()));

    if (lu_decomposition(A, &L, &U) < 0)
        return 0;

    double result = 1.f;
    for (size_t i = 0; i < A.size(); i++) {
        result *= L[i][i] * U[i][i];
    }
    return result;
}
