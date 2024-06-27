/**
 * @file
 * @brief [A fast Fourier transform
 * (FFT)](https://www.oreilly.com/library/view/c-cookbook/0596007612/ch11s18.html)
 * is an algorithm that computes the discrete Inverse Fast Fourier transform (FFT)
 * @details
 * The difference between an inverse transformation and a direct one
 * is the presence of normalization and a change in the sign under the exponent.
 * Function in this example, was written to be as simple as possible rather
 * than focusing on efficiency. Time complexity this algorithm computes
 * the DFT in O(nlogn) time in comparison to traditional O(n^2).
 * @author [Alexey Elfimov](https://github.com/ikocs)
*/

#include <complex>   /// for storing points and coefficients
#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector
#include <cstdint>   /// for uint8_t and other
#include <cassert>   /// for assert

using namespace std;

/**
 * @namespace numerical_methods
 * @brief Numerical algorithms/methods
 */
namespace numerical_methods {
/**
 * @brief Performs bit inversion in a number
 * @param x input number
 * @param log2n number size
 * @return result revert number
 */
unsigned int bit_reverse(unsigned int x, const unsigned int log2n) {
    unsigned int n = 0;
    for (int i = 0; i < log2n; i++) {
        n <<= 1;
        n |= (x & 1);
        x >>= 1;
    }
    return n;
}

const double PI = 3.1415926536;

/**
 * @brief Inverse Fast Fourier Transform is a recursive function which
 * returns Container of complex numbers
 * @tparam Container container for storing data. For example std::vector
 * @param in_data input data
 * @param log2n size ifft in power of two format
 * @return calculation result
 */
template <typename Container>
Container ifft(const Container& in_data, const unsigned int log2n) {
    using Complex = typename Container::value_type;

    const Complex J(0, 1);
    int n = 1 << log2n;
    Container out_data(n);

    for (unsigned int i = 0; i < n; ++i) {
        out_data[bit_reverse(i, log2n)] = in_data[i];
    }

    // Corrections for the reverse conversion
    // are made according to: https://help.scilab.org/docs/6.1.1/en_US/fft.html
    for (int s = 1; s <= log2n; ++s) {
        int m = 1 << s;
        int m2 = m >> 1;
        Complex w(1, 0);
        Complex wm = exp(J * (PI / m2));
        for (int j = 0; j < m2; ++j) {
            for (int k = j; k < n; k += m) {
                Complex t = w * out_data[k + m2];
                Complex u = out_data[k];
                out_data[k] = u + t;
                out_data[k + m2] = u - t;
            }
            w *= wm;
        }
    }

    // normalization
    for (auto& o : out_data) o /= n;

    return out_data;
}
}// namespace numerical_methods

/**
 * @brief Self-test implementations
 * @details
 * Declaring three test cases and checking for the error
 * in predicted and true value is less than 1e-6.
 * @returns void
 */
static void test() {
    using ComplVec = std::vector<std::complex<double>>;

    ComplVec t1 {{3, 0}, {-1, 0}};
    ComplVec t2 {{10, 0}, {-2, 2}, {-2, 0}, {-2, -2}};
    ComplVec t3 {
        {16, 16},
        {-4.82843, -11.6569},
        {0, 0},
        {-0.343146, 0.828427},
        {0, 0},
        {0.828427, -0.343146},
        {0, 0},
        {-11.6569, -4.82843}};


    uint8_t logN1 = 1;
    uint8_t logN2 = 2;
    uint8_t logN3 = 3;

    uint8_t n1 = 1 << logN1;
    uint8_t n2 = 1 << logN2;
    uint8_t n3 = 1 << logN3;

    // The result was verified using the following
    // online tool: https://scistatcalc.blogspot.com/2013/12/fft-calculator.html
    // True Answer for test case 1
    ComplVec r1 {{1, 0}, {2, 0}};

    // True Answer for test case 2
    ComplVec r2 {{1, 0}, {2, 0}, {3, 0}, {4, 0}};

    // True Answer for test case 3
    ComplVec r3 {
        {0, 0},
        {1, 1},
        {3, 3},
        {4, 4},
        {4, 4},
        {3, 3},
        {1, 1},
        {0, 0}};

    ComplVec o1 = numerical_methods::ifft(t1, logN1);
    for (short i = 0; i < n1; i++) {
        // Comparing for both real and imaginary values for test case 1
        assert((r1[i].real() - o1[i].real() < 1e-6) &&
               (r1[i].imag() - o1[i].imag() < 1e-6));
    }

    ComplVec o2 = numerical_methods::ifft(t2, logN2);
    for (short i = 0; i < n2; i++) {
        // Comparing for both real and imaginary values for test case 2
        assert((r2[i].real() - o2[i].real() < 1e-6) &&
               (r2[i].imag() - o2[i].imag() < 1e-6));
    }

    ComplVec o3 = numerical_methods::ifft(t3, logN3);
    for (short i = 0; i < n3; i++) {
        // Comparing for both real and imaginary values for test case 3
        assert((r3[i].real() - o3[i].real() < 1e-4) &&
               (r3[i].imag() - o3[i].imag() < 1e-4));
    }

    std::cout << "All tests have successfully passed!\n";
}

int main() {
    test();  //  run self-test implementations
             //  with 2 defined test cases
}