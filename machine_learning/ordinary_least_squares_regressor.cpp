/**
 * @file
 * \brief Linear regression example using [Ordinary least
 * squares](https://en.wikipedia.org/wiki/Ordinary_least_squares)
 *
 * Program that gets the number of data samples and number of features per
 * sample along with output per sample. It applies OLS regression to compute
 * the regression output for additional test data samples.
 *
 * \author [Krishna Vedala](https://github.com/kvedala)
 */
#include <cassert>
#include <cmath>    // for std::abs
#include <iomanip>  // for print formatting
#include <iostream>
#include <vector>

/**
 * operator to print a matrix
 */
template <typename T>
std::ostream &operator<<(std::ostream &out,
                         std::vector<std::vector<T>> const &v) {
    const int width = 10;
    const char separator = ' ';

    for (size_t row = 0; row < v.size(); row++) {
        for (size_t col = 0; col < v[row].size(); col++) {
            out << std::left << std::setw(width) << std::setfill(separator)
                << v[row][col];
        }
        out << std::endl;
    }

    return out;
}

/**
 * operator to print a vector
 */
template <typename T>
std::ostream &operator<<(std::ostream &out, std::vector<T> const &v) {
    const int width = 15;
    const char separator = ' ';

    for (size_t row = 0; row < v.size(); row++) {
        out << std::left << std::setw(width) << std::setfill(separator)
            << v[row];
    }

    return out;
}

/**
 * function to check if given matrix is a square matrix
 * \returns 1 if true, 0 if false
 */
template <typename T>
inline bool is_square(std::vector<std::vector<T>> const &A) {
    // Assuming A is square matrix
    size_t N = A.size();
    for (size_t i = 0; i < N; i++) {
        if (A[i].size() != N) {
            return false;
        }
    }
    return true;
}

/**
 * Matrix multiplication such that if A is size (mxn) and
 * B is of size (pxq) then the multiplication is defined
 * only when n = p and the resultant matrix is of size (mxq)
 *
 * \returns resultant matrix
 **/
template <typename T>
std::vector<std::vector<T>> operator*(std::vector<std::vector<T>> const &A,
                                      std::vector<std::vector<T>> const &B) {
    // Number of rows in A
    size_t N_A = A.size();
    // Number of columns in B
    size_t N_B = B[0].size();

    std::vector<std::vector<T>> result(N_A);

    if (A[0].size() != B.size()) {
        std::cerr << "Number of columns in A != Number of rows in B ("
                  << A[0].size() << ", " << B.size() << ")" << std::endl;
        return result;
    }

    for (size_t row = 0; row < N_A; row++) {
        std::vector<T> v(N_B);
        for (size_t col = 0; col < N_B; col++) {
            v[col] = static_cast<T>(0);
            for (size_t j = 0; j < B.size(); j++) {
                v[col] += A[row][j] * B[j][col];
            }
        }
        result[row] = v;
    }

    return result;
}

/**
 * multiplication of a matrix with a column vector
 * \returns resultant vector
 */
template <typename T>
std::vector<T> operator*(std::vector<std::vector<T>> const &A,
                         std::vector<T> const &B) {
    // Number of rows in A
    size_t N_A = A.size();

    std::vector<T> result(N_A);

    if (A[0].size() != B.size()) {
        std::cerr << "Number of columns in A != Number of rows in B ("
                  << A[0].size() << ", " << B.size() << ")" << std::endl;
        return result;
    }

    for (size_t row = 0; row < N_A; row++) {
        result[row] = static_cast<T>(0);
        for (size_t j = 0; j < B.size(); j++) result[row] += A[row][j] * B[j];
    }

    return result;
}

/**
 * pre-multiplication of a vector by a scalar
 * \returns resultant vector
 */
template <typename T>
std::vector<float> operator*(float const scalar, std::vector<T> const &A) {
    // Number of rows in A
    size_t N_A = A.size();

    std::vector<float> result(N_A);

    for (size_t row = 0; row < N_A; row++) {
        result[row] += A[row] * static_cast<float>(scalar);
    }

    return result;
}

/**
 * post-multiplication of a vector by a scalar
 * \returns resultant vector
 */
template <typename T>
std::vector<float> operator*(std::vector<T> const &A, float const scalar) {
    // Number of rows in A
    size_t N_A = A.size();

    std::vector<float> result(N_A);

    for (size_t row = 0; row < N_A; row++) {
        result[row] = A[row] * static_cast<float>(scalar);
    }

    return result;
}

/**
 * division of a vector by a scalar
 * \returns resultant vector
 */
template <typename T>
std::vector<float> operator/(std::vector<T> const &A, float const scalar) {
    return (1.f / scalar) * A;
}

/**
 * subtraction of two vectors of identical lengths
 * \returns resultant vector
 */
template <typename T>
std::vector<T> operator-(std::vector<T> const &A, std::vector<T> const &B) {
    // Number of rows in A
    size_t N = A.size();

    std::vector<T> result(N);

    if (B.size() != N) {
        std::cerr << "Vector dimensions shouldbe identical!" << std::endl;
        return A;
    }

    for (size_t row = 0; row < N; row++) result[row] = A[row] - B[row];

    return result;
}

/**
 * addition of two vectors of identical lengths
 * \returns resultant vector
 */
template <typename T>
std::vector<T> operator+(std::vector<T> const &A, std::vector<T> const &B) {
    // Number of rows in A
    size_t N = A.size();

    std::vector<T> result(N);

    if (B.size() != N) {
        std::cerr << "Vector dimensions shouldbe identical!" << std::endl;
        return A;
    }

    for (size_t row = 0; row < N; row++) result[row] = A[row] + B[row];

    return result;
}

/**
 * Get matrix inverse using Row-trasnformations. Given matrix must
 * be a square and non-singular.
 * \returns inverse matrix
 **/
template <typename T>
std::vector<std::vector<float>> get_inverse(
    std::vector<std::vector<T>> const &A) {
    // Assuming A is square matrix
    size_t N = A.size();

    std::vector<std::vector<float>> inverse(N);
    for (size_t row = 0; row < N; row++) {
        // preallocatae a resultant identity matrix
        inverse[row] = std::vector<float>(N);
        for (size_t col = 0; col < N; col++) {
            inverse[row][col] = (row == col) ? 1.f : 0.f;
        }
    }

    if (!is_square(A)) {
        std::cerr << "A must be a square matrix!" << std::endl;
        return inverse;
    }

    // preallocatae a temporary matrix identical to A
    std::vector<std::vector<float>> temp(N);
    for (size_t row = 0; row < N; row++) {
        std::vector<float> v(N);
        for (size_t col = 0; col < N; col++) {
            v[col] = static_cast<float>(A[row][col]);
        }
        temp[row] = v;
    }

    // start transformations
    for (size_t row = 0; row < N; row++) {
        for (size_t row2 = row; row2 < N && temp[row][row] == 0; row2++) {
            // this to ensure diagonal elements are not 0
            temp[row] = temp[row] + temp[row2];
            inverse[row] = inverse[row] + inverse[row2];
        }

        for (size_t col2 = row; col2 < N && temp[row][row] == 0; col2++) {
            // this to further ensure diagonal elements are not 0
            for (size_t row2 = 0; row2 < N; row2++) {
                temp[row2][row] = temp[row2][row] + temp[row2][col2];
                inverse[row2][row] = inverse[row2][row] + inverse[row2][col2];
            }
        }

        if (temp[row][row] == 0) {
            // Probably a low-rank matrix and hence singular
            std::cerr << "Low-rank matrix, no inverse!" << std::endl;
            return inverse;
        }

        // set diagonal to 1
        auto divisor = static_cast<float>(temp[row][row]);
        temp[row] = temp[row] / divisor;
        inverse[row] = inverse[row] / divisor;
        // Row transformations
        for (size_t row2 = 0; row2 < N; row2++) {
            if (row2 == row) {
                continue;
            }
            float factor = temp[row2][row];
            temp[row2] = temp[row2] - factor * temp[row];
            inverse[row2] = inverse[row2] - factor * inverse[row];
        }
    }

    return inverse;
}

/**
 * matrix transpose
 * \returns resultant matrix
 **/
template <typename T>
std::vector<std::vector<T>> get_transpose(
    std::vector<std::vector<T>> const &A) {
    std::vector<std::vector<T>> result(A[0].size());

    for (size_t row = 0; row < A[0].size(); row++) {
        std::vector<T> v(A.size());
        for (size_t col = 0; col < A.size(); col++) v[col] = A[col][row];

        result[row] = v;
    }
    return result;
}

/**
 * Perform Ordinary Least Squares curve fit. This operation is defined as
 * \f[\beta = \left(X^TXX^T\right)Y\f]
 * \param X feature matrix with rows representing sample vector of features
 * \param Y known regression value for each sample
 * \returns fitted regression model polynomial coefficients
 */
template <typename T>
std::vector<float> fit_OLS_regressor(std::vector<std::vector<T>> const &X,
                                     std::vector<T> const &Y) {
    // NxF
    std::vector<std::vector<T>> X2 = X;
    for (size_t i = 0; i < X2.size(); i++) {
        // add Y-intercept -> Nx(F+1)
        X2[i].push_back(1);
    }
    // (F+1)xN
    std::vector<std::vector<T>> Xt = get_transpose(X2);
    // (F+1)x(F+1)
    std::vector<std::vector<T>> tmp = get_inverse(Xt * X2);
    // (F+1)xN
    std::vector<std::vector<float>> out = tmp * Xt;
    // cout << endl
    //      << "Projection matrix: " << X2 * out << endl;

    // Fx1,1    -> (F+1)^th element is the independent constant
    return out * Y;
}

/**
 * Given data and OLS model coeffficients, predict
 * regression estimates. This operation is defined as
 * \f[y_{\text{row}=i} = \sum_{j=\text{columns}}\beta_j\cdot X_{i,j}\f]
 *
 * \param X feature matrix with rows representing sample vector of features
 * \param beta fitted regression model
 * \return vector with regression values for each sample
 **/
template <typename T>
std::vector<float> predict_OLS_regressor(std::vector<std::vector<T>> const &X,
                                         std::vector<float> const &beta /**< */
) {
    std::vector<float> result(X.size());

    for (size_t rows = 0; rows < X.size(); rows++) {
        // -> start with constant term
        result[rows] = beta[X[0].size()];
        for (size_t cols = 0; cols < X[0].size(); cols++) {
            result[rows] += beta[cols] * X[rows][cols];
        }
    }
    // Nx1
    return result;
}

/** Self test checks */
void ols_test() {
    int F = 3, N = 5;

    /* test function = x^2 -5 */
    std::cout << "Test 1 (quadratic function)....";
    // create training data set with features = x, x^2, x^3
    std::vector<std::vector<float>> data1(
        {{-5, 25, -125}, {-1, 1, -1}, {0, 0, 0}, {1, 1, 1}, {6, 36, 216}});
    // create corresponding outputs
    std::vector<float> Y1({20, -4, -5, -4, 31});
    // perform regression modelling
    std::vector<float> beta1 = fit_OLS_regressor(data1, Y1);
    // create test data set with same features = x, x^2, x^3
    std::vector<std::vector<float>> test_data1(
        {{-2, 4, -8}, {2, 4, 8}, {-10, 100, -1000}, {10, 100, 1000}});
    // expected regression outputs
    std::vector<float> expected1({-1, -1, 95, 95});
    // predicted regression outputs
    std::vector<float> out1 = predict_OLS_regressor(test_data1, beta1);
    // compare predicted results are within +-0.01 limit of expected
    for (size_t rows = 0; rows < out1.size(); rows++) {
        assert(std::abs(out1[rows] - expected1[rows]) < 0.01);
    }
    std::cout << "passed\n";

    /* test function = x^3 + x^2 - 100 */
    std::cout << "Test 2 (cubic function)....";
    // create training data set with features = x, x^2, x^3
    std::vector<std::vector<float>> data2(
        {{-5, 25, -125}, {-1, 1, -1}, {0, 0, 0}, {1, 1, 1}, {6, 36, 216}});
    // create corresponding outputs
    std::vector<float> Y2({-200, -100, -100, 98, 152});
    // perform regression modelling
    std::vector<float> beta2 = fit_OLS_regressor(data2, Y2);
    // create test data set with same features = x, x^2, x^3
    std::vector<std::vector<float>> test_data2(
        {{-2, 4, -8}, {2, 4, 8}, {-10, 100, -1000}, {10, 100, 1000}});
    // expected regression outputs
    std::vector<float> expected2({-104, -88, -1000, 1000});
    // predicted regression outputs
    std::vector<float> out2 = predict_OLS_regressor(test_data2, beta2);
    // compare predicted results are within +-0.01 limit of expected
    for (size_t rows = 0; rows < out2.size(); rows++) {
        assert(std::abs(out2[rows] - expected2[rows]) < 0.01);
    }
    std::cout << "passed\n";

    std::cout << std::endl;  // ensure test results are displayed on screen
                             // (flush stdout)
}

/**
 * main function
 */
int main() {
    ols_test();

    size_t N = 0, F = 0;

    std::cout << "Enter number of features: ";
    // number of features = columns
    std::cin >> F;
    std::cout << "Enter number of samples: ";
    // number of samples = rows
    std::cin >> N;

    std::vector<std::vector<float>> data(N);
    std::vector<float> Y(N);

    std::cout
        << "Enter training data. Per sample, provide features and one output."
        << std::endl;

    for (size_t rows = 0; rows < N; rows++) {
        std::vector<float> v(F);
        std::cout << "Sample# " << rows + 1 << ": ";
        for (size_t cols = 0; cols < F; cols++) {
            // get the F features
            std::cin >> v[cols];
        }
        data[rows] = v;
        // get the corresponding output
        std::cin >> Y[rows];
    }

    std::vector<float> beta = fit_OLS_regressor(data, Y);
    std::cout << std::endl << std::endl << "beta:" << beta << std::endl;

    size_t T = 0;
    std::cout << "Enter number of test samples: ";
    // number of test sample inputs
    std::cin >> T;
    std::vector<std::vector<float>> data2(T);
    // vector<float> Y2(T);

    for (size_t rows = 0; rows < T; rows++) {
        std::cout << "Sample# " << rows + 1 << ": ";
        std::vector<float> v(F);
        for (size_t cols = 0; cols < F; cols++) std::cin >> v[cols];
        data2[rows] = v;
    }

    std::vector<float> out = predict_OLS_regressor(data2, beta);
    for (size_t rows = 0; rows < T; rows++) std::cout << out[rows] << std::endl;

    return 0;
}
