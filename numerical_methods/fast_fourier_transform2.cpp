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

unsigned int bitReverse(unsigned int x, const unsigned int log2n) {
    unsigned int n = 0;
    for (int i=0; i < log2n; i++) {
        n <<= 1;
        n |= (x & 1);
        x >>= 1;
    }
    return n;
}

const double PI = 3.1415926536;

template<typename Container>
Container fft(const Container& a, const unsigned int log2n)
{
    using Complex = typename Container::value_type;

    const Complex J(0, 1);
    int n = 1 << log2n;
    Container b(n);

    for (unsigned int i=0; i < n; ++i) {
        b[bitReverse(i, log2n)] = a[i];
    }

    for (int s = 1; s <= log2n; ++s) {
        int m = 1 << s;
        int m2 = m >> 1;
        Complex w(1, 0);
        Complex wm = exp(-J * (PI / m2));
        for (int j=0; j < m2; ++j) {
            for (int k=j; k < n; k += m) {
                Complex t = w * b[k + m2];
                Complex u = b[k];
                b[k] = u + t;
                b[k + m2] = u - t;
            }
            w *= wm;
        }
    }

    return b;
}

static void test() {
    using ComplVec = std::vector<std::complex<double>>;

    /* descriptions of the following test */

    //    auto *t1 = new std::complex<double>[2];  /// Test case 1
    //    auto *t2 = new std::complex<double>[4];  /// Test case 2

    auto t1 = std::vector<std::complex<double>> {{1, 0}, {2, 0}};
    auto t2 = std::vector<std::complex<double>> {
        {1, 0},
        {2, 0},
        {3, 0},
        {4, 0}};

    uint8_t n1 = 2;
    uint8_t n2 = 4;
    // The result was verified using the following
    // online tool: https://scistatcalc.blogspot.com/2013/12/fft-calculator.html
    std::vector<std::complex<double>> r1 = {
        {3, 0}, {-1, 0}};  /// True Answer for test case 1

    std::vector<std::complex<double>> r2 = {
        {10, 0}, {-2, 2}, {-2, 0}, {-2, -2}};  /// True Answer for test case 2

    ComplVec o1 = fft(t1, 1);
    ComplVec o2 = fft(t2, 2);
    for (short i = 0; i < n1; i++) {
        // Comparing for both real and imaginary values for test case 1
        assert((r1[i].real() - o1[i].real() < 0.00000001) &&
               (r1[i].imag() - o1[i].imag() < 0.00000001));
    }

    std::cout << std::endl;

    for (short i = 0; i < n2; i++) {
        // Comparing for both real and imaginary values for test case 2
        assert((r2[i].real() - o2[i].real() < 0.00000001) &&
               (r2[i].imag() - o2[i].imag() < 0.00000001));
    }
    std::cout << "All tests have successfully passed!\n";
}

int main() {
    test();  //  run self-test implementations
             //  with 2 defined test cases
}