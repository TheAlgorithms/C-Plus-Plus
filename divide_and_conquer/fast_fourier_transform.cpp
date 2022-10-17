/**
 * @file
 * @brief Implementation of the [Fast Fourier Transform algorithm for fast
 * polynomial
 * multiplication](https://www.geeksforgeeks.org/fast-fourier-transformation-poynomial-multiplication/)
 * @details
 * Given two polynomials in coefficient notation we want to multiply them and
 * return the resultant polynomial. Simple approach is to multiply them normally
 * which results in a time complexity of O(n^2). To make it more efficient we
 * will be using the FFT algorithm to find the product which will solve the
 * problem in O(nlogn) of time.
 * @author [Aanjaney Kumar Verma](https://github.com/Akuver)
 */

#include <cassert>   /// for assert
#include <complex>   /// for complex numbers
#include <cstring>   /// for string
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector

/**
 * @namespace divide_and_conquer
 * @brief Divide and Conquer algorithms
 */
namespace divide_and_conquer {
/**
 * @namespace fast_fourier_transform
 */
namespace fast_fourier_transform {
/**
 * @brief The main function implements Fast Fourier Transform algorithm for fast
 * polynomial multiplication
 * @param a the input polynomial
 * @param invert to invert the FFT or to compute it
 * @returns void
 */
void FFT(std::vector<std::complex<double>> &a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;
    std::vector<std::complex<double>> a1(n / 2), a2(n / 2);
    for (int i = 0; i < n / 2; i++) {
        a1[i] = a[2 * i];
        a2[i] = a[2 * i + 1];
    }
    FFT(a1, invert);
    FFT(a2, invert);
    double ang = 2 * M_PI / n;
    if (invert)
        ang = -ang;
    std::complex<double> w = 1;
    std::complex<double> wn(cos(ang), sin(ang));
    for (int i = 0; i < n / 2; i++) {
        a[i] = a1[i] + w * a2[i];
        a[i + n / 2] = a1[i] - w * a2[i];
        w *= wn;
        if (invert) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
    }
    return;
}

/**
 * @brief Polynomial multiplication
 * @param first, the input polynomial 1
 * @param second, the input polynomial 2
 * @returns the product of the two input polynomials
 */
std::vector<int> multiply_polynomials(std::vector<int> first,
                                      std::vector<int> second) {
    std::vector<int> res;  // to store the result of the product

    std::vector<std::complex<double>> f1(first.begin(), first.end());
    std::vector<std::complex<double>> f2(second.begin(), second.end());

    // make n to the smallest power of 2 which is greater than sum of both
    // polynomial's degrees
    int n = 1;
    while (n < first.size() + second.size()) {
        n <<= 1;
    }

    f1.resize(n);
    f2.resize(n);

    // compute FFT of the polynomials
    FFT(f1, false);
    FFT(f2, false);

    // multiply the transforms together
    for (int i = 0; i < n; i++) {
        f1[i] *= f2[i];
    }

    // invert the transform to get the result
    FFT(f1, true);

    for (int i = 0; i < n; i++) {
        res.push_back(round(f1[i].real()));
    }
    return res;
}

}  // namespace fast_fourier_transform
}  // namespace divide_and_conquer

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    // 1st test
    std::vector<int> a11 = {2, 2};      // 2x + 2
    std::vector<int> a12 = {-6, 5, 1};  // x^2 + 5x - 6
    std::vector<int> res1 = {-12, -2, 12, 2, 0, 0, 0, 0};
    std::cout << "1st test... ";
    assert(divide_and_conquer::fast_fourier_transform::multiply_polynomials(
               a11, a12) == res1);
    std::cout << "passed" << std::endl;

    // 2nd test
    std::vector<int> a21 = {-9, 0, 1};  // x^2 - 9
    std::vector<int> a22 = {-2, 7, 6};  // 6x^2 + 7x - 2
    std::vector<int> res2 = {18, -63, -56, 7, 6, 0, 0, 0};
    std::cout << "2nd test... ";
    assert(divide_and_conquer::fast_fourier_transform::multiply_polynomials(
               a21, a22) == res2);
    std::cout << "passed" << std::endl;

    // 3rd test
    std::vector<int> a31 = {1, 1};         // x + 1
    std::vector<int> a32 = {1, 1};         // x + 1
    std::vector<int> res3 = {1, 2, 1, 0};  // x^2 + 2x + 1
    std::cout << "3rd test... ";
    assert(divide_and_conquer::fast_fourier_transform::multiply_polynomials(
               a31, a32) == res3);
    std::cout << "passed" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
