/**
 * @file
 * @brief [A fast Fourier transform
* (FFT)](https://www.oreilly.com/library/view/c-cookbook/0596007612/ch11s18.html)
 */

#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

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

template<typename Container,
    std::enable_if<>>
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

int main() {
    using cx = complex<double>;
    vector<cx> a = { cx(0,0), cx(1,1), cx(3,3), cx(4,4),
              cx(4, 4), cx(3, 3), cx(1,1), cx(0,0) };

    auto b = fft(a, 3);
    for (auto i : b)
        cout << i << "\n";
}