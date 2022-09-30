#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <complex>
#include <queue>
#include <set>
#include <unordered_set>
#include <list>
#include <chrono>
#include <random>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <stack>
#include <iomanip>
#include <fstream>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> p32;
typedef pair<ll, ll> p64;
typedef pair<double, double> pdd;
typedef vector<ll> v64;
typedef vector<int> v32;
typedef vector<vector<int>> vv32;
typedef vector<vector<ll>> vv64;
typedef vector<vector<p64>> vvp64;
typedef vector<p64> vp64;
typedef vector<p32> vp32;
ll MOD = 998244353;
double eps = 1e-12;
#define forn(i, e) for (ll i = 0; i < e; i++)
#define forsn(i, s, e) for (ll i = s; i < e; i++)
#define rforn(i, s) for (ll i = s; i >= 0; i--)
#define rforsn(i, s, e) for (ll i = s; i >= e; i--)
#define ln "\n"
#define dbg(x) cout << #x << " = " << x << ln
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define INF 2e18
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define sz(x) ((ll)(x).size())

int divide(int a, int b)
{
    //  Lets take a=15 b=2
    // 15/2 =  1 + 13/2= 1 + 1 +11/2 = 1 + 1 + 1 + 9/2 ......7.5=ans
    // same aproach is followed here using recursion

    static int ans = 1; // minimum quotient is one if a>b
    try
    {
        if (b == 0)
            throw b;
    }

    catch (int b)
    {
        cout << "Division by zero is not possible" << endl;
        exit(0);
    }


    if (a - b < 0)    // if b is greater than a than ans is 0.		
        return 0;

    if (a - b < b) // if we dont have enough left to get one more than b
        return ans;

    ans++; // quotient is increased
    return divide(a - b, b);
}

void solve()
{
    int a, b;
    cin >> a >> b;
    cout << divide(a, b);
}
int main()
{
    fast_cin();
    ll t = 1;
    cin >> t;
    for (int it = 1; it <= t; it++)
    {
        solve();
    }
    return 0;
}