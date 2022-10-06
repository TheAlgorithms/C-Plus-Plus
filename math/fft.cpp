#include <math.h>
#include <cassert>
#include <vector>

using namespace std;

typedef double dbl;

struct num {
    dbl x, y;
    num() { x = y = 0; }
    num(dbl x_, dbl y_) : x(x_), y(y_) {}
};

inline num operator+(num a, num b) { return num(a.x + b.x, a.y + b.y); }
inline num operator-(num a, num b) { return num(a.x - b.x, a.y - b.y); }
inline num operator*(num a, num b) {
    return num(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}
inline num conj(num a) { return num(a.x, -a.y); }

int base = 1;
vector<num> roots = {{0, 0}, {1, 0}};
vector<int> rev = {0, 1};

const dbl PI = static_cast<dbl>(acosl(-1.0));

void ensure_base(int nbase) {
    if (nbase <= base) {
        return;
    }
    rev.resize(1 << nbase);
    for (int i = 0; i < (1 << nbase); i++) {
        rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
    }
    roots.resize(1 << nbase);
    while (base < nbase) {
        dbl angle = 2 * PI / (1 << (base + 1));
        for (int i = 1 << (base - 1); i < (1 << base); i++) {
            roots[i << 1] = roots[i];
            dbl angle_i = angle * (2 * i + 1 - (1 << base));
            roots[(i << 1) + 1] = num(cos(angle_i), sin(angle_i));
        }
        base++;
    }
}

void fft(vector<num>& a, int n = -1) {
    if (n == -1) {
        n = (int)a.size();
    }
    assert((n & (n - 1)) == 0);
    int zeros = __builtin_ctz(n);
    ensure_base(zeros);
    int shift = base - zeros;
    for (int i = 0; i < n; i++) {
        if (i < (rev[i] >> shift)) {
            swap(a[i], a[rev[i] >> shift]);
        }
    }
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                num z = a[i + j + k] * roots[j + k];
                a[i + j + k] = a[i + j] - z;
                a[i + j] = a[i + j] + z;
            }
        }
    }
}