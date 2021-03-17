/**
 * @brief Evaluate recurrence relation using [matrix
 * exponentiation](https://www.hackerearth.com/practice/notes/matrix-exponentiation-1/).
 * @details
 * Given a recurrence relation; evaluate the value of nth term.
 * For e.g., For fibonacci series, recurrence series is `f(n) = f(n-1) + f(n-2)`
 * where `f(0) = 0` and `f(1) = 1`.
 * Note that the method used only demonstrates
 * recurrence relation with one variable (n), unlike `nCr` problem, since it has
 * two (n, r)
 *
 * ### Algorithm
 * This problem can be solved using matrix exponentiation method.
 * @see here for simple [number exponentiation
 * algorithm](https://github.com/TheAlgorithms/C-Plus-Plus/blob/master/math/modular_exponentiation.cpp)
 * or [explaination
 * here](https://en.wikipedia.org/wiki/Exponentiation_by_squaring).
 * @author [Ashish Daulatabad](https://github.com/AshishYUO)
 */
#include <cassert>   /// for assert
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector STL

/**
 * @namespace math
 * @brief Mathematical algorithms
 */
namespace math {
/**
 * @namespace linear_recurrence_matrix
 * @brief Functions for [Linear Recurrence
 * Matrix](https://www.hackerearth.com/practice/notes/matrix-exponentiation-1/)
 * implementation.
 */
namespace linear_recurrence_matrix {
/**
 * @brief Implementation of matrix multiplication
 * @details Multiplies matrix A and B, given total columns in A are equal to
 * total given rows in column B
 * @tparam T template type for integer as well as floating values, default is
 * long long int
 * @param _mat_a first matrix of size n * m
 * @param _mat_b second matrix of size m * k
 * @returns `_mat_c` resultant matrix of size n * k
 * Complexity: `O(n*m*k)`
 * @note The complexity in this case will be O(n^3) due to the nature of the
 * problem. We'll be multiplying the matrix with itself most of the time.
 */
template <typename T = int64_t>
std::vector<std::vector<T>> matrix_multiplication(
    const std::vector<std::vector<T>>& _mat_a,
    const std::vector<std::vector<T>>& _mat_b, const int64_t mod = 1000000007) {
    // assert that columns in `_mat_a` and rows in `_mat_b` are equal
    assert(_mat_a[0].size() == _mat_b.size());
    std::vector<std::vector<T>> _mat_c(_mat_a.size(),
                                       std::vector<T>(_mat_b[0].size(), 0));
    /**
     * Actual matrix multiplication.
     */
    for (uint32_t i = 0; i < _mat_a.size(); ++i) {
        for (uint32_t j = 0; j < _mat_b[0].size(); ++j) {
            for (uint32_t k = 0; k < _mat_b.size(); ++k) {
                _mat_c[i][j] =
                    (_mat_c[i][j] % mod +
                     (_mat_a[i][k] % mod * _mat_b[k][j] % mod) % mod) %
                    mod;
            }
        }
    }
    return _mat_c;
}
/**
 * @brief Returns whether matrix `mat` is a [zero
 * matrix.](https://en.wikipedia.org/wiki/Zero_matrix)
 * @tparam T template type for integer as well as floating values, default is
 * long long int
 * @param _mat A matrix
 * @returns true if it is a zero matrix else false
 */
template <typename T = int64_t>
bool is_zero_matrix(const std::vector<std::vector<T>>& _mat) {
    for (uint32_t i = 0; i < _mat.size(); ++i) {
        for (uint32_t j = 0; j < _mat[i].size(); ++j) {
            if (_mat[i][j] != 0) {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Implementation of Matrix exponentiation
 * @details returns the matrix exponentiation `(B^n)` in `k^3 * O(log2(power))`
 * time, where `k` is the size of matrix (k by k).
 * @tparam T template type for integer as well as floating values, default is
 * long long int
 * @param _mat matrix for exponentiation
 * @param power the exponent value
 * @returns the matrix _mat to the power `power (_mat^power)`
 */
template <typename T = int64_t>
std::vector<std::vector<T>> matrix_exponentiation(
    std::vector<std::vector<T>> _mat, uint64_t power,
    const int64_t mod = 1000000007) {
    /**
     * Initializing answer as identity matrix. For simple binary
     * exponentiation reference, [see
     * here](https://github.com/TheAlgorithms/C-Plus-Plus/blob/master/math/modular_exponentiation.cpp)
     */
    if (is_zero_matrix(_mat)) {
        return _mat;
    }

    std::vector<std::vector<T>> _mat_answer(_mat.size(),
                                            std::vector<T>(_mat.size(), 0));

    for (uint32_t i = 0; i < _mat.size(); ++i) {
        _mat_answer[i][i] = 1;
    }
    // exponentiation algorithm here.
    while (power > 0) {
        if (power & 1) {
            _mat_answer = matrix_multiplication(_mat_answer, _mat, mod);
        }
        power >>= 1;
        _mat = matrix_multiplication(_mat, _mat, mod);
    }

    return _mat_answer;
}

/**
 * @brief Implementation of nth recurrence series.
 * @details Returns the nth term in the recurrence series.
 * Note that the function assumes definition of base cases from `n = 0`
 * (e.g., for fibonacci, `f(0)` has a defined value `0`)
 * @tparam T template type for integer as well as floating values, default is
 * long long int
 * @param _mat [square matrix](https://en.m.wikipedia.org/wiki/Square_matrix)
 * that evaluates the nth term using exponentiation
 * @param _base_cases 2D array of dimension `1*n` containing values which are
 * defined for some n (e.g., for fibonacci, `f(0)` and `f(1)` are defined, and
 * `f(n)` where `n > 1` is evaluated on previous two values)
 * @param nth_term the nth term of recurrence relation
 * @param constant_or_sum_included whether the recurrence relation has a
 * constant value or is evaluating sum of first n terms of the recurrence.
 * @returns the nth term of the recurrence relation in `O(k^3. log(n))`, where k
 * is number of rows and columns in `_mat` and `n` is the value of `nth_term`
 * If constant_or_sum_included is true, returns the sum of first n terms in
 * recurrence series
 */
template <typename T = int64_t>
T get_nth_term_of_recurrence_series(
    const std::vector<std::vector<T>>& _mat,
    const std::vector<std::vector<T>>& _base_cases, uint64_t nth_term,
    bool constant_or_sum_included = false) {
    assert(_mat.size() == _base_cases.back().size());

    /**
     * If nth term is a base case, then return base case directly.
     */

    if (nth_term < _base_cases.back().size() - constant_or_sum_included) {
        return _base_cases.back()[nth_term - constant_or_sum_included];
    } else {
        /**
         * Else evaluate the expression, so multiplying _mat to itself (n -
         * base_cases.length + 1 + constant_or_sum_included) times.
         */
        std::vector<std::vector<T>> _res_matrix =
            matrix_exponentiation(_mat, nth_term - _base_cases.back().size() +
                                            1 + constant_or_sum_included);

        /**
         * After matrix exponentiation, multiply with the base case to evaluate
         * the answer. The answer is always at the end of the array.
         */
        std::vector<std::vector<T>> _res =
            matrix_multiplication(_base_cases, _res_matrix);

        return _res.back().back();
    }
}
}  // namespace linear_recurrence_matrix
}  // namespace math

/**
 * @brief Self test-implementations
 * @returns void
 */
static void test() {
    /*
     * Example 1: [Fibonacci
     * series](https://en.wikipedia.org/wiki/Fibonacci_number);
     *
     * [fn-2    fn-1]  [0      1]  ==   [fn-1   (fn-2 + fn-1)] => [fn-1   fn]
     *                 [1      1]
     *
     * Let A = [fn-2   fn-1], and B = [0   1]
     *                                [1   1],
     *
     * Since, A.B....(n-1 times) = [fn-1   fn]
     * we can multiply B with itself n-1 times to obtain the required value
     */
    std::vector<std::vector<int64_t>> fibonacci_matrix = {{0, 1}, {1, 1}},
                                      fib_base_case = {{0, 1}};

    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               fibonacci_matrix, fib_base_case, 11) == 89LL);
    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               fibonacci_matrix, fib_base_case, 39) == 63245986LL);
    /*
     * Example 2: [Tribonacci series](https://oeis.org/A000073)
     *                    [0   0   1]
     * [fn-3  fn-2  fn-1] [1   0   1]  =  [(fn-2)  (fn-1)  (fn-3 + fn-2 + fn-1)]
     *                    [0   1   1]
     *                                 => [fn-2     fn-1    fn]
     *
     *                                       [0   0   1]
     * Let A = [fn-3   fn-2   fn-1], and B = [1   0   1]
     *                                       [0   1   1]
     *
     * Since, A.B....(n-2 times) = [fn-2  fn-1   fn]
     * we will have multiply B with itself n-2 times to obtain the required
     * value ()
     */

    std::vector<std::vector<int64_t>> tribonacci = {{0, 0, 1},
                                                    {1, 0, 1},
                                                    {0, 1, 1}},
                                      trib_base_case = {
                                          {0, 0, 1}};  // f0 = 0, f1 = 0, f2 = 1

    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               tribonacci, trib_base_case, 11) == 149LL);
    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               tribonacci, trib_base_case, 36) == 615693474LL);

    /*
     * Example 3: [Pell numbers](https://oeis.org/A000129)
     * `f(n)  = 2* f(n-1) + f(n-2); f(0) = f(1) = 2`
     *
     * [fn-2  fn-1] [0   1]  =  [(fn-1)  fn-2 + 2*fn-1)]
     *              [1   2]
     *                       => [fn-1     fn]
     *
     * Let A = [fn-2  fn-1], and B = [0   1]
     *                               [1   2]
     */

    std::vector<std::vector<int64_t>> pell_recurrence = {{0, 1}, {1, 2}},
                                      pell_base_case = {
                                          {2, 2}};  // `f0 = 2, f1 = 2`

    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               pell_recurrence, pell_base_case, 15) == 551614LL);
    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               pell_recurrence, pell_base_case, 23) == 636562078LL);

    /*
     * Example 4: Custom recurrence relation:
     * Now the recurrence is of the form `a*f(n-1) + b*(fn-2) + ... + c`
     * where `c` is the constant
     * `f(n)  = 2* f(n-1) + f(n-2) + 7; f(0) = f(1) = 2, c = 7`
     *
     *                   [1   0   1]
     * [7,  fn-2,  fn-1] [0   0   1]
     *                   [0   1   2]
     * =  [7,  (fn-1),  fn-2 + 2*fn-1) + 7]
     *
     * => [7,    fn-1,     fn]
     * :: Series will be 2, 2, 13, 35, 90, 222, 541, 1311, 3170, 7658, 18493,
     * 44651, 107802, 260262, 628333, 1516935, 362210, 8841362, 21344941,
     * 51531251
     *
     * Let A = [7,  fn-2,  fn-1], and B = [1   0   1]
     *                                    [0   0   1]
     *                                    [0   1   2]
     */

    std::vector<std::vector<int64_t>>
        custom_recurrence = {{1, 0, 1}, {0, 0, 1}, {0, 1, 2}},
        custom_base_case = {{7, 2, 2}};  // `c = 7, f0 = 2, f1 = 2`

    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               custom_recurrence, custom_base_case, 10, 1) == 18493LL);
    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               custom_recurrence, custom_base_case, 19, 1) == 51531251LL);

    /*
     * Example 5: Sum fibonacci sequence
     * The following matrix evaluates the sum of first n fibonacci terms in
     * O(27. log2(n)) time.
     * `f(n) = f(n-1) + f(n-2); f(0) = 0, f(1) = 1`
     *
     *                           [1   0   0]
     * [s(f, n-1),  fn-2,  fn-1] [1   0   1]
     *                           [1   1   1]
     *   => [(s(f, n-1)+f(n-2)+f(n-1)), (fn-1),  f(n-2)+f(n-1)]
     *
     *   => [s(f, n-1)+f(n),    fn-1,     fn]
     *
     *   => [s(f, n),    fn-1,     fn]
     *
     * Sum of first 20 fibonacci series:
     * 0, 1, 2, 4, 7, 12, 20, 33, 54, 88, 143, 232, 376, 609, 986, 1596, 2583,
     * 4180, 6764
     *          f0  f1  s(f,1)
     * Let A = [0    1    1], and B = [0   1   1]
     *                                [1   1   1]
     *                                [0   0   1]
     */

    std::vector<std::vector<int64_t>> sum_fibo_recurrence = {{0, 1, 1},
                                                             {1, 1, 1},
                                                             {0, 0, 1}},
                                      sum_fibo_base_case = {
                                          {0, 1, 1}};  // `f0 = 0, f1 = 1`

    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               sum_fibo_recurrence, sum_fibo_base_case, 13, 1) == 609LL);
    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               sum_fibo_recurrence, sum_fibo_base_case, 16, 1) == 2583LL);
    /*
     * Example 6: [Tribonacci sum series](https://oeis.org/A000073)
     *                               [0   0   1   1]
     * [fn-3  fn-2  fn-1  s(f, n-1)] [1   0   1   1]
     *                               [0   1   1   1]
     *                               [0   0   0   1]
     *
     * = [fn-2, fn-1, fn-3 + fn-2 + fn-1, (fn-3 + fn-2 + fn-1 + s(f, n-1))]
     *
     * => [fn-2, fn-1, fn,  fn + s(f, n-1)]
     *
     * => [fn-2, fn-1, fn, s(f, n)]
     *
     * Sum of the series is: 0, 0, 1, 2, 4, 8, 15, 28, 52, 96, 177, 326, 600,
     * 1104, 2031, 3736, 6872, 12640, 23249, 42762
     *
     * Let A = [fn-3   fn-2   fn-1   s(f, n-1)], and
     *     [0   0   1   1]
     * B = [1   0   1   1]
     *     [0   1   1   1]
     *     [0   0   0   1]
     *
     * Since, A.B....(n-2 times) = [fn-2  fn-1   fn]
     * we will have multiply B with itself n-2 times to obtain the required
     * value
     */

    std::vector<std::vector<int64_t>> tribonacci_sum = {{0, 0, 1, 1},
                                                        {1, 0, 1, 1},
                                                        {0, 1, 1, 1},
                                                        {0, 0, 0, 1}},
                                      trib_sum_base_case = {{0, 0, 1, 1}};
    // `f0 = 0, f1 = 0, f2 = 1, s = 1`

    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               tribonacci_sum, trib_sum_base_case, 18, 1) == 23249LL);
    assert(math::linear_recurrence_matrix::get_nth_term_of_recurrence_series(
               tribonacci_sum, trib_sum_base_case, 19, 1) == 42762LL);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
