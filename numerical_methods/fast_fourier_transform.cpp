/**
 * @file
 * @brief [A fast Fourier transform
 * (FFT)](https://medium.com/@aiswaryamathur/understanding-fast-fouriertransform-from-scratch-to-solve-polynomial-multiplication-8018d511162f)
 is an algorithm that computes the
 * discrete Fourier transform (DFT) of a sequence , or its inverse (IDFT) , this
 algorithm
 * has application in use case scenario where a user wants to find points of a
 function
 * in short period time by just using the coefficents of the polynomial 
 function.
 * It can be also used to find inverse fourier transform by just switching the value of omega.
 * @time complexity
 * this algorithm computes the DFT in O(nlogn) time in comparison to traditional O(n^2).
 * @details
 * https://medium.com/@aiswaryamathur/understanding-fast-fourier-transform-from-scratch-to
  -solve-polynomial-multiplication-8018d511162f
 * @author [Ameya Chawla](https://github.com/ameyachawlaggsipu)
 */

#include <cassert>   /// for assert
#include <cmath>     /// for mathematical-related functions
#include <complex>   /// for storing points and coefficents
#include <iostream>  /// for IO operations
#include <vector>    /// for storing test cases

/**
 * @namespace numerical_methods
 * @brief Numerical algorithms/methods
 */
namespace numerical_methods {
/**
 * @brief FastFourierTransform is a recursive function which returns list of
 * complex numbers
 * @param p List of Coefficents in form of complex numbers
 * @param n Count of elements in list p
 * @returns p if n==1
 * @returns y if n!=1
 */
std::complex<double> *FastFourierTransform(std::complex<double> *p,
                                           uint64_t n) {
    double pi = 2 * asin(1.0);  /// Declaring value of pi

    if (n == 1) {
        return p;  /// Base Case To return
    }

    auto om = std::complex<double>(
        cos(2 * pi / n), sin(2 * pi / n));  /// Calculating value of omega

    auto *pe = new std::complex<double>[n / 2];  /// Coefficents of even power

    auto *po = new std::complex<double>[n / 2];  /// Coefficents of odd power

    uint64_t k1 = 0, k2 = 0;
    for (uint64_t j = 0; j < n; j++) {
        if (j % 2 == 0) {
            pe[k1++] = p[j];  /// Assigning values of even coefficents

        } else
            po[k2++] = p[j];  /// Assigning value of odd coefficents
    }

    auto *ye = FastFourierTransform(pe, n / 2);  /// Recursive Call

    auto *yo = FastFourierTransform(po, n / 2);  /// Recursive Call

    auto *y = new std::complex<double>[n];  /// Final value representation list

    for (uint64_t i = 0; i < n / 2; i++) {
        y[i] = ye[i] + pow(om, i) * yo[i];  /// Updating the first n/2 elements
        y[i + n / 2] =
            ye[i] - pow(om, i) * yo[i];  /// Updating the last n/2 elements
    }
    delete[] ye; /// Deleting dynamic array ye
    delete[] yo; /// Deleting dynamic array yo
    delete[] pe; /// Deleting dynamic array pe
    delete[] po; /// Deleting dynamic array po
    return y;  /// Returns the list
}
}  // namespace numerical_methods

/**
 * @brief Self-test implementations
 * declaring two test cases and checking for the error
 * in predicted and true value is less than 0.000000000001.
 * @returns void
 */
static void test() {
    /* descriptions of the following test */

    auto *t1 = new std::complex<double>[2];  /// Test case 1
    t1[0] = {1, 0};
    t1[1] = {2, 0};

    auto *t2 = new std::complex<double>[4];  /// Test case 2
    t2[0] = {1, 0};
    t2[1] = {2, 0};
    t2[2] = {3, 0};
    t2[3] = {4, 0};

    uint8_t n1 = sizeof(t1) / sizeof(std::complex<double>);
    uint8_t n2 = sizeof(t2) / sizeof(std::complex<double>);

    std::vector<std::complex<double>> r1 = {
        {3, 0}, {-1, 0}};  /// True Answer for test case 1

    std::vector<std::complex<double>> r2 = {
        {10, 0}, {-2, -2}, {-2, 0}, {-2, 2}};  /// True Answer for test case 2

    auto *o1 = numerical_methods::FastFourierTransform(t1, n1);
    auto *o2 = numerical_methods::FastFourierTransform(t2, n2);

    for (uint8_t i = 0; i < n1; i++) {
        assert((r1[i].real() - o1->real() < 0.000000000001) &&
               (r1[i].imag() - o1->imag() <
                0.000000000001));  /// Comparing for both real and imaginary
                                   /// values for test case 1
        o1++;
    }

    for (uint8_t i = 0; i < n2; i++) {
        assert((r2[i].real() - o2->real() < 0.000000000001) &&
               (r2[i].imag() - o2->imag() <
                0.000000000001));  /// Comparing for both real and imaginary
                                   /// values for test case 2
        o2++;
    }

    delete[] o1; /// Deleting dynamic array o1
    delete[] o2; /// Deleting dynamic array o2
    delete[] t1; /// Deleting dynamic array t1
    delete[] t2; /// Deleting dynamic array t2
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * calls automated test function to test the working of fast fourier transform.
 * @returns 0 on exit
 */
int main(int argc, char const *argv[]) {
    test();  // run self-test implementations
    return 0;
}
