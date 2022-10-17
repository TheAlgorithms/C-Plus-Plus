/*
* @file
* @brief Implementation of The Jacobi Method
  https://en.wikipedia.org/wiki/Jacobi_method#Algorithm
* @details
This is an iterative method to solve the system of linear equations
with two assumptions :-
1) that system has a unique solution.
2) that the coefficient matrix has notzeroson main diagonal.
*Implementation:
model problem:
a11*x + a12*y + a13*z = b1 |\
a21*x + a22*y + a23*z = b2    >> Given system of Equation.
a31*x + a32*y + a33*z = b3 |/

Taking the Coefficient matrix A and Column vector B are as
    |a11 a12 a13 |      |b1|
A = |a21 a22 a23 | b =  |b2|
    |a31 a32 a33 |      |b3|

Then we have a initial approximation values variabels in vecotr X = [x0,y0,z0]

Iterations : (Note: in xi,yi,zi , i represent the iteration no.)
x(i+1) = (b1 - a12*yi - a13*zi)/a11
y(i+1) = (b2 - a21*xi - a23*zi)/a22
z(i+1) = (b3 - a32*xi - a32*yi)/a33

Please refer the link for more generic description of iterations formulas
https://en.wikipedia.org/wiki/Jacobi_method#Algorithm
https://mathworld.wolfram.com/JacobiMethod.html


@author [Nitish Pal](https://github.com/NitishPal2013)
*/

#include <cassert>   /// for assert function
#include <iostream>  /// for IO operations

using std::cout;

/*
 * @namespace numerical_methods/jacobi_method.cpp
 * @brief
 */

namespace jacobi {

class jacobi_method {
 private:
    int n;
    float coeff_matrix[n][n];
    float col_vector[n];
    float calc(float *arr, float *x, int k, int n);
    void update(float *from_update, float *to_update, int n)

        public : jacobi_method(float *coeff_mat, float *col_vect, int n);
    ~jacobi_method();
    float *jacobi(float *c_m, float *c_v, int n, int ite);
};

jacobi_method::jacobi_method(float *coeff_mat, float *col_vect, int order) {
    coeff_matrix = coeff_mat;
    col_vector = col_vect;
    n = order;
}

jacobi_method::~jacobi_method() {}

float jacobi_method::calc(float *arr, float *x, int k, int n) {
    int sum = 0;  // for consecutive summation
    for (int i = 0; i < n; i++) {
        if (i == k) {
            continue;
        }

        sum += arr[i] * x[i];
    }

    return sum;
}

void jacobi_method::update(float *from_update, float *to_update, int n) {
    for (int i = 0; i < n; i++) {
        to_update[i] = from_update[i];
    }
}

float *jacobi_method::jacobi(float *c_m, float *c_v, int n, int ite) {
    float x[n] = {0};
    float x_update[n] = {0};
    for (int i = 0; i < ite; i++) {
        for (int k = 0; k < n; k++) {
            x_update[k] = (c_v[k] - calc(c_m[k], x, k, n)) / c_m[k][k];
        }
        update(x_update, x);
    }
    return x_update;
}

}  // namespace jacobi

/*
 *@brief Slef-test implementations
 *@return void
 */

static void test() {
    float arr[3][3] = {{5, -2, 3}, {-3, 9, 1}, {2, -1, -7}};
    float b[3] = {-1, 2, 3};
    float result = { 0.186, 0.331, -0.423 }
}