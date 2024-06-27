/**
 * @file
 * @brief [A fast Fourier transform
* (FFT)](https://www.oreilly.com/library/view/c-cookbook/0596007612/ch11s18.html)
 */

#include <cmath>
#include <complex>
#include <iostream>
#include <vector>
#include <cstdint>   /// for uint8_t and other
#include <cassert>   /// for assert

using namespace std;

namespace numerical_methods {
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

template <typename Container>
Container fft(const Container& in_data, const unsigned int log2n) {
    using Complex = typename Container::value_type;

    const Complex J(0, 1);
    int n = 1 << log2n;
    Container out_data(n);

    for (unsigned int i = 0; i < n; ++i) {
        out_data[bit_reverse(i, log2n)] = in_data[i];
    }

    for (int s = 1; s <= log2n; ++s) {
        int m = 1 << s;
        int m2 = m >> 1;
        Complex w(1, 0);
        Complex wm = exp(-J * (PI / m2));
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

    return out_data;
}
} // namespace numerical_methods

static void test() {
    using ComplVec = std::vector<std::complex<double>>;

    auto t1 = ComplVec {{1, 0}, {2, 0}};
    auto t2 = ComplVec {
        {1, 0},
        {2, 0},
        {3, 0},
        {4, 0}};
    auto t3 = ComplVec {
        {0, 0},
        {1, 1},
        {3, 3},
        {4, 4},
        {4, 4},
        {3, 3},
        {1, 1},
        {0, 0}};

    uint8_t logN1 = 1;
    uint8_t logN2 = 2;
    uint8_t logN3 = 3;

    uint8_t n1 = 1 << logN1;
    uint8_t n2 = 1 << logN2;
    uint8_t n3 = 1 << logN3;

    // The result was verified using the following
    // online tool: https://scistatcalc.blogspot.com/2013/12/fft-calculator.html
    // True Answer for test case 1
    ComplVec r1 = {{3, 0}, {-1, 0}};

    // True Answer for test case 2
    ComplVec r2 = {{10, 0}, {-2, 2}, {-2, 0}, {-2, -2}};

    // True Answer for test case 3
    ComplVec r3 = {
        {16, 16},
        {-4.82843, -11.6569},
        {0, 0},
        {-0.343146, 0.828427},
        {0, 0},
        {0.828427, -0.343146},
        {0, 0},
        {-11.6569, -4.82843}};

    ComplVec o1 = numerical_methods::fft(t1, logN1);
    for (short i = 0; i < n1; i++) {
        // Comparing for both real and imaginary values for test case 1
        assert((r1[i].real() - o1[i].real() < 0.00000001) &&
               (r1[i].imag() - o1[i].imag() < 0.00000001));
    }

    ComplVec o2 = numerical_methods::fft(t2, logN2);
    for (short i = 0; i < n2; i++) {
        // Comparing for both real and imaginary values for test case 2
        assert((r2[i].real() - o2[i].real() < 0.00000001) &&
               (r2[i].imag() - o2[i].imag() < 0.00000001));
    }

    ComplVec o3 = numerical_methods::fft(t3, logN3);
    for (short i = 0; i < n3; i++) {
        // Comparing for both real and imaginary values for test case 3
        assert((r3[i].real() - o3[i].real() < 0.00000001) &&
               (r3[i].imag() - o3[i].imag() < 0.00000001));
    }

    std::cout << "All tests have successfully passed!\n";
}

int main() {
    test();  //  run self-test implementations
             //  with 2 defined test cases
}