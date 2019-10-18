#include <vector>
#include <map>
using namespace std;

long long mulMod(long long x, long long y, long long mod) {
    if (y == 0) return 0;
    if (x < LLONG_MAX / y) return (x * y) % mod;
    if (y % 2) return (x + mulMod(x, y-1, mod)) % mod;
    return mulMod((x + x) % mod, y / 2, mod);
}

long long powerMod(long long x, long long y, long long mod) {
    if (y == 0) return 1LL;
    if (y % 2) return mulMod(x, powerMod(x, y - 1, mod), mod);
    return powerMod(mulMod(x, x, mod), y / 2, mod);
}

long long gcd(long long a, long long b) {
    return (b == 0 ? a : gcd(b, a % b));
}

// Use power in this file only
// Rabin-Miller primality testing algorithm
// deterministic for upto 2^64
bool MillerRabin(long long n) {
    if (n == 2) return true;
    if (n < 2 || n % 2 == 0) return false;
    long long d = n - 1, r = 0;
    while (d % 2 == 0) {
        d /= 2; r++;
    }
    vector<long long> bases({2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37});
    for (long long a : bases) {
        if (n-1 <= a) break;
        bool isComposite = true;
        long long x = powerMod(a, d, n);
        if (x == 1 || x == n-1) continue;
        for (int i = 0; i < r; i++) {
            x = mulMod(x, x, n);
            if (x == n-1) {
                isComposite = false;
                break;
            }
        }
        if (isComposite) return false;
    }
    return true;
}

long long pollardRho(long long n) {
    if (n == 1) return 1;
    if (n % 2 == 0) return 2;
    long long x = rand() % (n-2) + 2, c = rand() % (n-1) + 1;
    long long y = x, d = 1;
    while (d == 1) {
        x = (mulMod(x, x, n) + c) % n;
        y = (mulMod(y, y, n) + c) % n;
        y = (mulMod(y, y, n) + c) % n;
        d = gcd((x > y ? x-y : y-x), n);
        if (d == n) return pollardRho(n);
    }
    return d;
}

map<long long, int> factors;

// Precondition:  factors is an empty map,
//                n is a positive integer
// Postcondition: factors[p] is the exponent of p
//                in prime factorization of n
void factorize(long long n) {
    if (n == 1) return;
    if (!MillerRabin(n)) {
        long long fact = pollardRho(n);
        factorise(fact); factorise(n / fact);
    } else {
        factors[n]++;
    }
}
