/**
@file
@brief Matrix Exponentiation.

The problem can be solved with DP but constraints are high.
<br/>\f$a_i = b_i\f$ (for \f$i <= k\f$)
<br/>\f$a_i = c_1 a_{i-1} + c_2 a_{i-2} + ... + c_k a_{i-k}\f$ (for \f$i > k\f$)
<br/>Taking the example of Fibonacci series, \f$k=2\f$
<br/>\f$b_1 = 1,\; b_2=1\f$
<br/>\f$c_1 = 1,\; c_2=1\f$
<br/>\f$a = \begin{bmatrix}0& 1& 1& 2& \ldots\end{bmatrix}\f$
<br/>This way you can find the \f$10^{18}\f$ fibonacci number%MOD.
I have given a general way to use it. The program takes the input of B and C
matrix.

Steps for Matrix Expo
1. Create vector F1 : which is the copy of B.
2. Create transpose matrix (Learn more about it on the internet)
3. Perform \f$T^{n-1}\f$ [transpose matrix to the power n-1]
4. Multiply with F to get the last matrix of size (1\f$\times\f$k).

The first element of this matrix is the required result.
*/

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

/*! shorthand definition for `int64_t` */
#define ll int64_t

/*! shorthand definition for `std::endl` */
#define endl std::endl

/*! shorthand definition for `int64_t` */
#define pb push_back
#define MOD 1000000007

/** returns absolute value */
inline ll ab(ll x) { return x > 0LL ? x : -x; }

/** global variable k
 * @todo @stepfencurryxiao add documetnation
 */
ll k;

/** global vector variables
 * @todo @stepfencurryxiao add documetnation
 */
vector<ll> a, b, c;

/** To multiply 2 matrices
 * \param [in] A matrix 1 of size (m\f$\times\f$n)
 * \param [in] B \p matrix 2 of size (p\f$\times\f$q)\n\note \f$p=n\f$
 * \result matrix of dimension (m\f$\times\f$q)
 */
vector<vector<ll>> multiply(const vector<vector<ll>> &A,
                            const vector<vector<ll>> &B) {
    vector<vector<ll>> C(k + 1, vector<ll>(k + 1));
    for (ll i = 1; i <= k; i++) {
        for (ll j = 1; j <= k; j++) {
            for (ll z = 1; z <= k; z++) {
                C[i][j] = (C[i][j] + (A[i][z] * B[z][j]) % MOD) % MOD;
            }
        }
    }
    return C;
}

/** computing integer power of a matrix using recursive multiplication.
 * @note A must be a square matrix for this algorithm.
 * \param [in] A base matrix
 * \param [in] p exponent
 * \return matrix of same dimension as A
 */
vector<vector<ll>> power(const vector<vector<ll>> &A, ll p) {
    if (p == 1)
        return A;
    if (p % 2 == 1) {
        return multiply(A, power(A, p - 1));
    } else {
        vector<vector<ll>> X = power(A, p / 2);
        return multiply(X, X);
    }
}

/*! Wrapper for Fibonacci
 * \param[in] n \f$n^\text{th}\f$ Fibonacci number
 * \return \f$n^\text{th}\f$ Fibonacci number
 */
ll ans(ll n) {
    if (n == 0)
        return 0;
    if (n <= k)
        return b[n - 1];
    // F1
    vector<ll> F1(k + 1);
    for (ll i = 1; i <= k; i++) F1[i] = b[i - 1];

    // Transpose matrix
    vector<vector<ll>> T(k + 1, vector<ll>(k + 1));
    for (ll i = 1; i <= k; i++) {
        for (ll j = 1; j <= k; j++) {
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
    for (ll i = 1; i <= k; i++) {
        res = (res + (T[1][i] * F1[i]) % MOD) % MOD;
    }
    return res;
}

/** Main function */
int main() {
    cin.tie(0);
    cout.tie(0);
    ll t;
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
