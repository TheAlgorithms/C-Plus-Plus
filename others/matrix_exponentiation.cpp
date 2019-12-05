/*
Matrix Exponentiation. If the problem can be solved with DP but constaints are
high.
ai = bi (for i <= k)
ai = c1*ai-1 + c2*ai-2 + ... + ck*ai-k (for i > k)
Taking the example of Fibonacci series, K=2
b1 = 1, b2=1
c1 = 1, c2=1
a = 0 1 1 2 ....
This way you can find the 10^18 fibonacci number%MOD.
I have given a general way to use it. The program takes the input of B and C
matrix.

Steps for Matrix Expo
1. Create vector F1 : which is the copy of B.
2. Create transpose matrix (Learn more abput it on the internet)
3. Perform T^(n-1) [transpose matrix to the power n-1]
4. Multiply with F to get the last matrix of size (1xk).
The first element of this matrix is the required result.
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define endl '\n'
#define pb push_back
#define mp make_pair
#define trace1(x) cout << #x << ": " << x << endl
#define trace2(x, y) cout << #x << ": " << x << " | " << #y << ": " << y << endl
#define trace3(x, y, z)                                                        \
    cout << #x << ":" << x << " | " << #y << ": " << y << " | " << #z << ": "  \
         << z << endl
#define trace4(a, b, c, d)                                                     \
    cout << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " \
         << c << " | " << #d << ": " << d << endl
#define trace5(a, b, c, d, e)                                                  \
    cout << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " \
         << c << " | " << #d << ": " << d << " | " << #e << ": " << e << endl
#define trace6(a, b, c, d, e, f)                                               \
    cout << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " \
         << c << " | " << #d << ": " << d << " | " << #e << ": " << e << " | " \
         << #f << ": " << f << endl
#define traceloop(x, a)                                                        \
    {                                                                          \
        for (ll i = 0; i < x; i++)                                             \
            cout << a[i] << " ";                                               \
        cout << endl;                                                          \
    }
#define MOD 1000000000
ll ab(ll x) { return x > 0LL ? x : -x; }
ll k;
vector<ll> a, b, c;

// To multiply 2 matrix
vector<vector<ll>> multiply(vector<vector<ll>> A, vector<vector<ll>> B) {
    vector<vector<ll>> C(k + 1, vector<ll>(k + 1));
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= k; j++) {
            for (int z = 1; z <= k; z++) {
                C[i][j] = (C[i][j] + (A[i][z] * B[z][j]) % MOD) % MOD;
            }
        }
    }
    return C;
}

// computing power of a matrix
vector<vector<ll>> power(vector<vector<ll>> A, ll p) {
    if (p == 1)
        return A;
    if (p % 2 == 1) {
        return multiply(A, power(A, p - 1));
    } else {
        vector<vector<ll>> X = power(A, p / 2);
        return multiply(X, X);
    }
}

// main function
ll ans(ll n) {
    if (n == 0)
        return 0;
    if (n <= k)
        return b[n - 1];
    // F1
    vector<ll> F1(k + 1);
    for (int i = 1; i <= k; i++)
        F1[i] = b[i - 1];

    // Transpose matrix
    vector<vector<ll>> T(k + 1, vector<ll>(k + 1));
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= k; j++) {
            if (i < k) {
                if (j == i + 1)
                    T[i][j] = 1;
                else
                    T[i][j] = 0;
                continue;
            }
            T[i][j] = c[k - j];
        }
    }
    // T^n-1
    T = power(T, n - 1);

    // T*F1
    ll res = 0;
    for (int i = 1; i <= k; i++) {
        res = (res + (T[1][i] * F1[i]) % MOD) % MOD;
    }
    return res;
}

// 1 1 2 3 5

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    ll i, j, x;
    while (t--) {
        cin >> k;
        for (i = 0; i < k; i++) {
            cin >> x;
            b.pb(x);
        }
        for (i = 0; i < k; i++) {
            cin >> x;
            c.pb(x);
        }
        cin >> x;
        cout << ans(x) << endl;
        b.clear();
        c.clear();
    }
    return 0;
}
