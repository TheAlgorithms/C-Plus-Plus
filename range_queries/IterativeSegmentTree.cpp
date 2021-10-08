//Find the Maximum in given range with updates.
#include <bits/stdc++.h>
using namespace std;
//struct s(n,x);
struct SegTree
{
    typedef int T;
    static constexpr T unit = -1e9;
    T f(T a, T b) { return max(a, b); } // (any associative fn)
    vector<T> s;
    int n;
    SegTree(int _n = 0, T def = unit) : s(2 * _n, def), n(_n) {}
    //O(logn)
    void update(int pos, T val)
    {
        for (s[pos += n] = val; pos /= 2;)
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }
    //O(logn)
    T query(int b, int e)
    { // query [b, e)
        T ra = unit, rb = unit;
        for (b += n, e += n; b < e; b /= 2, e /= 2)
        {
            if (b % 2)
                ra = f(ra, s[b++]);
            if (e % 2)
                rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};
int main()
{
    int n;
    cin >> n;
    vector<int> v(n);

    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    SegTree s(n + 1);
    //Building of Segment Tree in O(n*(log(n)))
    for (int i = 0; i < n; i++)
    {
        s.update(i + 1, v[i]);
    }
    //queries

    int q;
    cin >> q;
    while (q--)
    {
        int t;
        //two types of queries
        //1) t = 1 change element at index i to u
        //2) t = 2 print the sum of elements in range [l,r]
        cin >> t;
        if (t == 1)
        {
            int id, u;
            cin >> id >> u;
            id--;                //changing to zero base
            s.update(id + 1, u); //updating the delta
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << s.query(l, r + 1) << endl;
        }
    }
}

// Time Complexity:
// O(nlogn)
// Space Complexity:
// O(n)

// Test Cases:
// Input:
// 5
// 1 3 4 7 -15
// 3
// 2 2 5
// 1 3 15
// 2 2 5
// Output:
// 7
// 15
