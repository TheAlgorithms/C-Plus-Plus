/**
 * @file
 * @brief [A fast Fourier transform
 * (FFT)](https://medium.com/@aiswaryamathur/understanding-fast-fouriertransform-from-scratch-to-solve-polynomial-multiplication-8018d511162f)
 * is an algorithm that computes the
 * discrete Fourier transform (DFT) of a sequence, or its inverse (IDFT).
 * @details
 * This
 * algorithm has application in use case scenario where a user wants to find
 points of a
 * function
 * in a short time by just using the coefficients of the polynomial
 * function.
 * It can be also used to find inverse fourier transform by just switching the
 value of omega.
 * Time complexity
 * this algorithm computes the DFT in O(nlogn) time in comparison to traditional
 O(n^2).
 * @author [Ameya Chawla](https://github.com/ameyachawlaggsipu)
 */

#include <cassert>   /// for assert
#include <cmath>     /// for mathematical-related functions
#include <complex>   /// for storing points and coefficents
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

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
std::complex<double> *FastFourierTransform(std::complex<double> *p, uint8_t n) {
    if (n == 1) {
        return p;  /// Base Case To return
    }

    double pi = 2 * asin(1.0);  /// Declaring value of pi

    std::complex<double> om = std::complex<double>(
        cos(2 * pi / n), sin(2 * pi / n));  /// Calculating value of omega

    auto *pe = new std::complex<double>[n / 2];  /// Coefficients of even power

    auto *po = new std::complex<double>[n / 2];  /// Coefficients of odd power

    int k1 = 0, k2 = 0;
    for (int j = 0; j < n; j++) {
        if (j % 2 == 0) {
            pe[k1++] = p[j];  /// Assigning values of even Coefficients

        } else {
            po[k2++] = p[j];  /// Assigning value of odd Coefficients
        }
    }

    std::complex<double> *ye =
        FastFourierTransform(pe, n / 2);  /// Recursive Call

    std::complex<double> *yo =
        FastFourierTransform(po, n / 2);  /// Recursive Call

    auto *y = new std::complex<double>[n];  /// Final value representation list

    k1 = 0, k2 = 0;

    for (int i = 0; i < n / 2; i++) {
        y[i] =
            ye[k1] + pow(om, i) * yo[k2];  /// Updating the first n/2 elements
        y[i + n / 2] =
            ye[k1] - pow(om, i) * yo[k2];  /// Updating the last n/2 elements

        k1++;
        k2++;
    }

    if (n != 2) {
        delete[] pe;
        delete[] po;
    }

    delete[] ye;  /// Deleting dynamic array ye
    delete[] yo;  /// Deleting dynamic array yo
    return y;
}

}  // namespace numerical_methods

/**
 * @brief Self-test implementations
 * @details
 * Declaring two test cases and checking for the error
 * in predicted and true value is less than 0.000000000001.
 * @returns void
 */
static void test() {
    /* descriptions of the following test */

    auto *t1 = new std::complex<double>[2];  /// Test case 1
    auto *t2 = new std::complex<double>[4];  /// Test case 2

    t1[0] = {1, 0};
    t1[1] = {2, 0};
    t2[0] = {1, 0};
    t2[1] = {2, 0};
    t2[2] = {3, 0};
    t2[3] = {4, 0};

    uint8_t n1 = 2;
    uint8_t n2 = 4;
    std::vector<std::complex<double>> r1 = {
        {3, 0}, {-1, 0}};  /// True Answer for test case 1

    std::vector<std::complex<double>> r2 = {
        {10, 0}, {-2, -2}, {-2, 0}, {-2, 2}};  /// True Answer for test case 2

    std::complex<double> *o1 = numerical_methods::FastFourierTransform(t1, n1);
    std::complex<double> *t3 =
        o1;  /// Temporary variable used to delete memory location of o1
    std::complex<double> *o2 = numerical_methods::FastFourierTransform(t2, n2);
    std::complex<double> *t4 =
        o2;  /// Temporary variable used to delete memory location of o2
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

    delete[] t1;
    delete[] t2;
    delete[] t3;
    delete[] t4;
    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * calls automated test function to test the working of fast fourier transform.
 * @returns 0 on exit
 */

int main(int argc, char const *argv[]) {
    test();  //  run self-test implementations
             //  with 2 defined test cases
    return 0;
}
