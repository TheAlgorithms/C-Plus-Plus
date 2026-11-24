/**
 * @file
 * @brief Implementation of the
 * [Woodbury matrix identity](https://en.wikipedia.org/wiki/Woodbury_matrix_identity)
 * for rank-k matrix inverse updates and rank-1 downdating.
 * @details
 * Computes (A + U C V)^(-1) = A^(-1) - A^(-1) U (C^(-1) + V A^(-1) U)^(-1) V A^(-1)
 * given A^(-1), reducing update complexity from O(n^3) to O(n^2 k + k^3).
 */

#include <algorithm>  /// for std::swap
#include <cassert>    /// for assert
#include <cmath>      /// for std::abs
#include <cstddef>    /// for std::size_t
#include <iostream>   /// for std::cout
#include <stdexcept>  /// for std::invalid_argument
#include <vector>     /// for std::vector

/**
 * @namespace numerical_methods
 * @brief Numerical methods and linear algebra algorithms
 */
namespace numerical_methods {

/**
 * @namespace woodbury
 * @brief Woodbury matrix identity and rank-1 downdate functions
 */
namespace woodbury {

using Matrix = std::vector<std::vector<double>>;

/**
 * @brief Validate that a matrix is non-empty and rectangular.
 * @param mat input matrix
 * @throws std::invalid_argument if empty or jagged
 */
void validate_rectangular(const Matrix& mat) {
    if (mat.empty() || mat[0].empty()) {
        throw std::invalid_argument("matrix must be non-empty");
    }
    const std::size_t cols = mat[0].size();
    for (const auto& row : mat) {
        if (row.size() != cols) {
            throw std::invalid_argument("matrix rows must have uniform length");
        }
    }
}

/**
 * @brief Multiply two matrices A (m x p) and B (p x n).
 * @param a left matrix
 * @param b right matrix
 * @return product matrix of size m x n
 */
Matrix multiply(const Matrix& a, const Matrix& b) {
    const std::size_t rows = a.size();
    const std::size_t inner = b.size();
    const std::size_t cols = b[0].size();
    Matrix result(rows, std::vector<double>(cols, 0.0));
    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t k = 0; k < inner; ++k) {
            const double a_ik = a[i][k];
            for (std::size_t j = 0; j < cols; ++j) {
                result[i][j] += a_ik * b[k][j];
            }
        }
    }
    return result;
}

/**
 * @brief Solve A X = B for square A (k x k) using partial-pivoting Gaussian elimination.
 * @param a square coefficient matrix
 * @param b right-hand side matrix (k x m)
 * @return solution matrix X (k x m)
 * @throws std::invalid_argument if A is singular
 */
Matrix solve_linear_system(Matrix a, Matrix b) {
    constexpr double pivot_tol = 1e-12;
    const std::size_t n = a.size();
    const std::size_t rhs_cols = b[0].size();

    for (std::size_t col = 0; col < n; ++col) {
        std::size_t pivot_row = col;
        double max_val = std::abs(a[col][col]);
        for (std::size_t row = col + 1; row < n; ++row) {
            const double candidate = std::abs(a[row][col]);
            if (candidate > max_val) {
                max_val = candidate;
                pivot_row = row;
            }
        }
        if (max_val < pivot_tol) {
            throw std::invalid_argument("matrix is singular");
        }
        if (pivot_row != col) {
            std::swap(a[col], a[pivot_row]);
            std::swap(b[col], b[pivot_row]);
        }

        const double pivot = a[col][col];
        for (std::size_t row = col + 1; row < n; ++row) {
            const double factor = a[row][col] / pivot;
            for (std::size_t j = col; j < n; ++j) {
                a[row][j] -= factor * a[col][j];
            }
            for (std::size_t j = 0; j < rhs_cols; ++j) {
                b[row][j] -= factor * b[col][j];
            }
        }
    }

    Matrix x(n, std::vector<double>(rhs_cols, 0.0));
    for (std::size_t i = n; i-- > 0;) {
        for (std::size_t j = 0; j < rhs_cols; ++j) {
            double sum = b[i][j];
            for (std::size_t col = i + 1; col < n; ++col) {
                sum -= a[i][col] * x[col][j];
            }
            x[i][j] = sum / a[i][i];
        }
    }
    return x;
}

/**
 * @brief Compute the inverse of a small k x k square matrix.
 * @param mat square matrix
 * @return inverse matrix
 */
Matrix invert_small_matrix(const Matrix& mat) {
    const std::size_t k = mat.size();
    Matrix identity(k, std::vector<double>(k, 0.0));
    for (std::size_t i = 0; i < k; ++i) {
        identity[i][i] = 1.0;
    }
    return solve_linear_system(mat, identity);
}

/**
 * @brief Compute (A + U C V)^(-1) using the Woodbury matrix identity given A^(-1).
 * @param a_inv inverse of base matrix A (n x n)
 * @param u_matrix update factor U (n x k)
 * @param c_matrix inner weight matrix C (k x k)
 * @param v_matrix update factor V (k x n)
 * @return updated inverse matrix (n x n)
 * @throws std::invalid_argument on dimension mismatch or singular C / capacitance matrix
 */
Matrix woodbury_inverse(const Matrix& a_inv, const Matrix& u_matrix,
                        const Matrix& c_matrix, const Matrix& v_matrix) {
    validate_rectangular(a_inv);
    validate_rectangular(u_matrix);
    validate_rectangular(c_matrix);
    validate_rectangular(v_matrix);

    const std::size_t n = a_inv.size();
    const std::size_t k = c_matrix.size();
    if (a_inv[0].size() != n || c_matrix[0].size() != k ||
        u_matrix.size() != n || u_matrix[0].size() != k ||
        v_matrix.size() != k || v_matrix[0].size() != n) {
        throw std::invalid_argument("incompatible dimensions for Woodbury update");
    }

    const Matrix a_inv_u = multiply(a_inv, u_matrix);
    const Matrix v_a_inv = multiply(v_matrix, a_inv);
    const Matrix c_inv = invert_small_matrix(c_matrix);
    const Matrix v_a_inv_u = multiply(v_matrix, a_inv_u);

    Matrix capacitance(k, std::vector<double>(k, 0.0));
    for (std::size_t i = 0; i < k; ++i) {
        for (std::size_t j = 0; j < k; ++j) {
            capacitance[i][j] = c_inv[i][j] + v_a_inv_u[i][j];
        }
    }

    // Solve K * Y = V A^(-1) instead of inverting K explicitly for better stability.
    const Matrix correction = multiply(a_inv_u, solve_linear_system(capacitance, v_a_inv));
    Matrix updated_inv(n, std::vector<double>(n, 0.0));
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            updated_inv[i][j] = a_inv[i][j] - correction[i][j];
        }
    }
    return updated_inv;
}

/**
 * @brief Compute (A - u v^T)^(-1) given A^(-1) as a rank-1 downdate.
 * @param a_inv inverse of base matrix A (n x n)
 * @param u_vec column vector u of length n
 * @param v_vec row vector v of length n
 * @return downdated inverse matrix (n x n)
 */
Matrix rank_one_downdate(const Matrix& a_inv, const std::vector<double>& u_vec,
                         const std::vector<double>& v_vec) {
    if (u_vec.size() != v_vec.size() || u_vec.empty()) {
        throw std::invalid_argument("u_vec and v_vec must be non-empty of equal size");
    }
    Matrix u_mat(u_vec.size(), std::vector<double>(1, 0.0));
    for (std::size_t i = 0; i < u_vec.size(); ++i) {
        u_mat[i][0] = u_vec[i];
    }
    return woodbury_inverse(a_inv, u_mat, {{-1.0}}, {v_vec});
}

}  // namespace woodbury
}  // namespace numerical_methods

/**
 * @brief Self-test implementations
 * @returns void
 */
static void tests() {
    using numerical_methods::woodbury::Matrix;
    using numerical_methods::woodbury::invert_small_matrix;
    using numerical_methods::woodbury::multiply;
    using numerical_methods::woodbury::rank_one_downdate;
    using numerical_methods::woodbury::woodbury_inverse;

    const Matrix a = {{2.0, 1.0, 0.0}, {1.0, 3.0, 1.0}, {0.0, 1.0, 2.0}};
    const Matrix a_inv = invert_small_matrix(a);
    const Matrix u = {{1.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}};
    const Matrix c = {{2.0, 0.0}, {0.0, 0.5}};
    const Matrix v = {{1.0, 0.0, 1.0}, {0.0, 1.0, 0.0}};

    const Matrix updated_inv = woodbury_inverse(a_inv, u, c, v);
    const Matrix ucv = multiply(multiply(u, c), v);
    Matrix a_updated = a;
    for (std::size_t i = 0; i < 3; ++i) {
        for (std::size_t j = 0; j < 3; ++j) {
            a_updated[i][j] += ucv[i][j];
        }
    }
    const Matrix prod = multiply(a_updated, updated_inv);
    for (std::size_t i = 0; i < 3; ++i) {
        for (std::size_t j = 0; j < 3; ++j) {
            const double expected = (i == j) ? 1.0 : 0.0;
            assert(std::abs(prod[i][j] - expected) < 1e-9);
        }
    }

    const Matrix b = {{5.0, 1.0, 0.0}, {1.0, 4.0, 1.0}, {0.0, 1.0, 3.0}};
    const std::vector<double> u_vec = {1.0, 0.0, 1.0};
    const std::vector<double> v_vec = {0.5, 1.0, 0.5};
    const Matrix downdated_inv = rank_one_downdate(invert_small_matrix(b), u_vec, v_vec);
    Matrix b_downdated = b;
    for (std::size_t i = 0; i < 3; ++i) {
        for (std::size_t j = 0; j < 3; ++j) {
            b_downdated[i][j] -= u_vec[i] * v_vec[j];
        }
    }
    const Matrix prod_down = multiply(b_downdated, downdated_inv);
    for (std::size_t i = 0; i < 3; ++i) {
        for (std::size_t j = 0; j < 3; ++j) {
            const double expected = (i == j) ? 1.0 : 0.0;
            assert(std::abs(prod_down[i][j] - expected) < 1e-9);
        }
    }

    bool threw_singular = false;
    try {
        (void)woodbury_inverse({{1.0, 0.0}, {0.0, 1.0}}, {{1.0}, {1.0}}, {{0.0}},
                               {{1.0, 1.0}});
    } catch (const std::invalid_argument&) {
        threw_singular = true;
    }
    assert(threw_singular);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    tests();
    return 0;
}
