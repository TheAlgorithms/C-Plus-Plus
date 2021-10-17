/**
 * @file
 * \brief Library functions to compute [QR
 * decomposition](https://en.wikipedia.org/wiki/QR_decomposition) of a given
 * matrix.
 * \author [Krishna Vedala](https://github.com/kvedala)
 */

#ifndef NUMERICAL_METHODS_QR_DECOMPOSE_H_
#define NUMERICAL_METHODS_QR_DECOMPOSE_H_

#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <valarray>
#ifdef _OPENMP
#include <omp.h>
#endif

/** \namespace qr_algorithm
 * \brief Functions to compute [QR
 * decomposition](https://en.wikipedia.org/wiki/QR_decomposition) of any
 * rectangular matrix
 */
namespace qr_algorithm {
/**
 * operator to print a matrix
 */
template <typename T>
std::ostream &operator<<(std::ostream &out,
                         std::valarray<std::valarray<T>> const &v) {
    const int width = 12;
    const char separator = ' ';

    out.precision(4);
    for (size_t row = 0; row < v.size(); row++) {
        for (size_t col = 0; col < v[row].size(); col++)
            out << std::right << std::setw(width) << std::setfill(separator)
                << v[row][col];
        out << std::endl;
    }

    return out;
}

/**
 * operator to print a vector
 */
template <typename T>
std::ostream &operator<<(std::ostream &out, std::valarray<T> const &v) {
    const int width = 10;
    const char separator = ' ';

    out.precision(4);
    for (size_t row = 0; row < v.size(); row++) {
        out << std::right << std::setw(width) << std::setfill(separator)
            << v[row];
    }

    return out;
}

/**
 * Compute dot product of two vectors of equal lengths
 *
 * If \f$\vec{a}=\left[a_0,a_1,a_2,...,a_L\right]\f$ and
 * \f$\vec{b}=\left[b_0,b_1,b_1,...,b_L\right]\f$ then
 * \f$\vec{a}\cdot\vec{b}=\displaystyle\sum_{i=0}^L a_i\times b_i\f$
 *
 * \returns \f$\vec{a}\cdot\vec{b}\f$
 */
template <typename T>
inline double vector_dot(const std::valarray<T> &a, const std::valarray<T> &b) {
    return (a * b).sum();
    // could also use following
    // return std::inner_product(std::begin(a), std::end(a), std::begin(b),
    // 0.f);
}

/**
 * Compute magnitude of vector.
 *
 * If \f$\vec{a}=\left[a_0,a_1,a_2,...,a_L\right]\f$ then
 * \f$\left|\vec{a}\right|=\sqrt{\displaystyle\sum_{i=0}^L a_i^2}\f$
 *
 * \returns \f$\left|\vec{a}\right|\f$
 */
template <typename T>
inline double vector_mag(const std::valarray<T> &a) {
    double dot = vector_dot(a, a);
    return std::sqrt(dot);
}

/**
 * Compute projection of vector \f$\vec{a}\f$ on \f$\vec{b}\f$ defined as
 * \f[\text{proj}_\vec{b}\vec{a}=\frac{\vec{a}\cdot\vec{b}}{\left|\vec{b}\right|^2}\vec{b}\f]
 *
 * \returns NULL if error, otherwise pointer to output
 */
template <typename T>
std::valarray<T> vector_proj(const std::valarray<T> &a,
                             const std::valarray<T> &b) {
    double num = vector_dot(a, b);
    double deno = vector_dot(b, b);

    /*! check for division by zero using machine epsilon */
    if (deno <= std::numeric_limits<double>::epsilon()) {
        std::cerr << "[" << __func__ << "] Possible division by zero\n";
        return a;  // return vector a back
    }

    double scalar = num / deno;

    return b * scalar;
}

/**
 * Decompose matrix \f$A\f$ using [Gram-Schmidt
 *process](https://en.wikipedia.org/wiki/QR_decomposition).
 *
 * \f{eqnarray*}{
 * \text{given that}\quad A &=&
 *\left[\mathbf{a}_1,\mathbf{a}_2,\ldots,\mathbf{a}_{N-1},\right]\\
 * \text{where}\quad\mathbf{a}_i &=&
 * \left[a_{0i},a_{1i},a_{2i},\ldots,a_{(M-1)i}\right]^T\quad\ldots\mbox{(column
 * vectors)}\\
 * \text{then}\quad\mathbf{u}_i &=& \mathbf{a}_i
 *-\sum_{j=0}^{i-1}\text{proj}_{\mathbf{u}_j}\mathbf{a}_i\\
 * \mathbf{e}_i &=&\frac{\mathbf{u}_i}{\left|\mathbf{u}_i\right|}\\
 * Q &=& \begin{bmatrix}\mathbf{e}_0 & \mathbf{e}_1 & \mathbf{e}_2 & \dots &
 * \mathbf{e}_{N-1}\end{bmatrix}\\
 * R &=& \begin{bmatrix}\langle\mathbf{e}_0\,,\mathbf{a}_0\rangle &
 * \langle\mathbf{e}_1\,,\mathbf{a}_1\rangle &
 * \langle\mathbf{e}_2\,,\mathbf{a}_2\rangle & \dots \\
 *                  0 & \langle\mathbf{e}_1\,,\mathbf{a}_1\rangle &
 * \langle\mathbf{e}_2\,,\mathbf{a}_2\rangle & \dots\\
 *                  0 & 0 & \langle\mathbf{e}_2\,,\mathbf{a}_2\rangle &
 * \dots\\ \vdots & \vdots & \vdots & \ddots
 *      \end{bmatrix}\\
 * \f}
 */
template <typename T>
void qr_decompose(
    const std::valarray<std::valarray<T>> &A, /**< input matrix to decompose */
    std::valarray<std::valarray<T>> *Q,       /**< output decomposed matrix */
    std::valarray<std::valarray<T>> *R        /**< output decomposed matrix */
) {
    std::size_t ROWS = A.size();        // number of rows of A
    std::size_t COLUMNS = A[0].size();  // number of columns of A
    std::valarray<T> col_vector(ROWS);
    std::valarray<T> col_vector2(ROWS);
    std::valarray<T> tmp_vector(ROWS);

    for (int i = 0; i < COLUMNS; i++) {
        /* for each column => R is a square matrix of NxN */
        int j;
        R[0][i] = 0.; /* make R upper triangular */

        /* get corresponding Q vector */
#ifdef _OPENMP
// parallelize on threads
#pragma omp for
#endif
        for (j = 0; j < ROWS; j++) {
            tmp_vector[j] = A[j][i]; /* accumulator for uk */
            col_vector[j] = A[j][i];
        }
        for (j = 0; j < i; j++) {
            for (int k = 0; k < ROWS; k++) {
                col_vector2[k] = Q[0][k][j];
            }
            col_vector2 = vector_proj(col_vector, col_vector2);
            tmp_vector -= col_vector2;
        }

        double mag = vector_mag(tmp_vector);

#ifdef _OPENMP
// parallelize on threads
#pragma omp for
#endif
        for (j = 0; j < ROWS; j++) Q[0][j][i] = tmp_vector[j] / mag;

            /* compute upper triangular values of R */
#ifdef _OPENMP
// parallelize on threads
#pragma omp for
#endif
        for (int kk = 0; kk < ROWS; kk++) {
            col_vector[kk] = Q[0][kk][i];
        }

#ifdef _OPENMP
// parallelize on threads
#pragma omp for
#endif
        for (int k = i; k < COLUMNS; k++) {
            for (int kk = 0; kk < ROWS; kk++) {
                col_vector2[kk] = A[kk][k];
            }
            R[0][i][k] = (col_vector * col_vector2).sum();
        }
    }
}
}  // namespace qr_algorithm

#endif  // NUMERICAL_METHODS_QR_DECOMPOSE_H_
