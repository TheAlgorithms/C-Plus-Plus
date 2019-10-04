#include <iostream>
using namespace std;
long long int solve(long long int b, long long int p, long long int m) {
    long long int ans = 1;
    while (p) {
        if (p&1)  // check the last bit of p
            ans = ans * b % m;
        p >>= 1; // right shift p 1 bit
        b = b * b % m;
    }
    return ans;
}
int main(int argc, char const *argv[]) {
    // Compute the result of (b^p) % m
    // b and p are the maximum value of long long int
    // m is sqrt(2^63 - 1)
    long long int b = (1ll<<63) - 1, p = b, m = 3037000499;
    cout << solve(b, p, m) << endl;
	return 0;
}
