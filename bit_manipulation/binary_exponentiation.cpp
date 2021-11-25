#include <iostream>
using namespace std;

long binaryExponention(int x, int n) {
    // @param x : base number
    // @param n : exponent
    // T(N) = O(log(n))
    // S(n) = O(1)
    long res = 1;
    while (n != 0) {
        if (n % 2 == 1) {
            // last bit is 1
            res *= x;
        }
        x *= x;
        n /= 2;
    }
    return res;
}

int main(int argc, char *argv[]) {
    int x, n;
    cout << "Enter x(base) and n(exponent):";
    cin >> x >> n;
    cout << "Power(" << x << "," << n << ") : " << binaryExponention(x, n);
    return 0;
}