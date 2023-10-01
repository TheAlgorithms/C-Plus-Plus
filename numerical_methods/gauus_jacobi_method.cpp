/**
 * @file
 * @brief Implementation of [The Jacobi Method]
 (https://en.wikipedia.org/wiki/Jacobi_method#Algorithm)
 * @details
 * ### Algorithm
 *
 * 1) Input taken :
 *  A->(coefficient matrix),
 *  b->(column vector),
 *  ite->(number of iterations)
 *
 * 2) Other variables taken :
 *  n->(order of A),
 *  prev->(initial column vector and to store the current value),
 *  succ->(column vector to store updated value)
 *
 * 3) For (i=1, i<=ite, ++i){
 *      For (j=1, j<=n, ++j){
 *          succ[j] = (b[j] - Summation[A[j][k]*prev[k], 1<=k<=n and
 k!=j])/A[j][j]
 *      }
 *      prev = succ
 * }
 *
 * 4) Print[succ]
 *
 * This is an iterative method to solve the system of linear equations
 * with two assumptions :-
 *
 * 1) system has a unique solution.
 * 2) the coefficient matrix has not zeros on main diagonal.
 *
 * Implementation on a model problem :
 * model problem:
 * a11*x + a12*y + a13*z = b1 |\
 * a21*x + a22*y + a23*z = b2    >> Given system of Equation.
 * a31*x + a32*y + a33*z = b3 |/
 *
 * Taking the Coefficient matrix A and Column vector B are as
 *     |a11 a12 a13 |      |b1|
 * A = |a21 a22 a23 | b =  |b2|
 *     |a31 a32 a33 |      |b3|
 *
 * Then we have an initial approximation values variables in vector X =
 * [x0,y0,z0] Iterations : (Note: in xi,yi,zi , i represent the iteration no.)
 * (the Inner loop iterations from the algorithm!)
 * x(i+1) = (b1 - a12*yi - a13*zi)/a11
 * y(i+1) = (b2 - a21*xi - a23*zi)/a22
 * z(i+1) = (b3 - a32*xi - a32*yi)/a33
 *
 * Please refer to the following link for more generic description of iterations
 * formulas
 * https://mathworld.wolfram.com/JacobiMethod.html
 *
 * @author [Nitish Pal](https://github.com/NitishPal2013)
 */

#include <cassert>   /// for assert
#include <cmath>     /// for pow() and round()
#include <iostream>  /// for IO operations
#include <vector>    /// for vector class to storing values

using std::cout;
using std::vector;

/**
 * @namespace jacobi
 * @brief Class for the [Jacobi Method]
 * (https://en.wikipedia.org/wiki/Jacobi_method) implementation
 */

namespace jacobi {

/**
 * @brief jacobi_method documentation
 * jacobi_method class is to implement [The Jacobi Method].
 * This class object taking the essential inputs like
 * 1) The coefficient matrix
 * 2) column vector
 * 3) number of iterations i.e no. of time approximations to be performed
 *
 * Then Function [jacobi()] peforms the algorithm with the data members and
 * returns the final approximation.
 */

class jacobi_method {
 private:
    int n;                               ///< n for order of matrix
    int ite;                             ///< ite for no. of iterations
    vector<vector<float>> coeff_matrix;  ///< for Coefficient Matrix
    vector<float> col_vector;            ///< for Column vector
    vector<float> prev;                  ///< for storing previous values
    vector<float> succ;                  ///< for storind updated values
    float calc(vector<float> x, int k);  ///< short calculation part of formula

 public:
    jacobi_method(vector<vector<float>> c_m, vector<float> c_v, int iterations);
    vector<float> jacobi();  /// Algorithm Implementation
};

/**
 * @brief jacobi_method()
 * This function is class constructor which initiates the class data members.
 * @param c_m coefficient matrix
 * @param c_v column vector
 * @param iterations number of iterations
 */

jacobi_method::jacobi_method(vector<vector<float>> c_m, vector<float> c_v,
                             int iterations) {
    n = c_m.size();
    coeff_matrix = c_m;
    col_vector = c_v;
    prev.assign(n, 0);
    succ.assign(n, 0);
    ite = iterations;
}

/**
 * @brief calc()
 * It performing a small calculation part in the algorithm implementation :
    Summation[A[j][k]*prev[k], 1<=k<=n and k!=j]
 *
 * @param x previous approximated solution values
 * @param k index value of corresponding evaluating function
 * @return float
 */

float jacobi_method::calc(vector<float> x, int k) {
    float sum = 0;  // for consecutive summation
    for (int i = 0; i < n; i++) {
        if (i == k) {
            continue;
        }

        sum += coeff_matrix[k][i] * x[i];
    }

    return sum;
}

/**
 * @brief jacobi()
 * Function performing algorithm with class data members.
 * please refer file documentation for algorithm.
 * @return vector<float>
 */

vector<float> jacobi_method::jacobi() {
    for (int i = 0; i < ite; i++) {
        for (int k = 0; k < n; k++) {
            succ[k] = (col_vector[k] - calc(prev, k)) / coeff_matrix[k][k];
        }
        prev = succ;
    }

    return succ;
}

}  // namespace jacobi

/**
 * @brief roundoff()
 * roundoff the values to some no. of decimals.
 * @param value value to be roundoff
 * @param prec number of decimals places
 * @return double
 */

double roundoff(float value, unsigned char prec) {
    float pow_10 = pow(10.0f, static_cast<float>(prec));
    return round(value * pow_10) / pow_10;
}

/**
 * @brief Self-test implementations
 * @returns void
 */

static void test() {
    vector<vector<float>> A = {{5, -2, 3}, {-3, 9, 1}, {2, -1, -7}};
    vector<float> b = {-1, 2, 3};
    jacobi::jacobi_method obj(A, b, 6);
    vector<float> result = obj.jacobi();
    assert(roundoff(result[0], 3) == (double)0.186);
    assert(roundoff(result[1], 3) == (double)0.331);
    assert(roundoff(result[2], 3) == (double)-0.423);
    cout << "Test Passed!"
         << "\n";
}

/**
 * @brief Main function
 *
 * @returns 0 on exit
 */

int main() {
    test();  // run self-test implementations
    return 0;
}