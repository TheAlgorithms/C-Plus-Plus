// Problem statement - Consider a game where there are n children(numbered 1,
// 2,…, n) in a circle.During the game, every second child is removed from the
// circle, until there are no children left.In which order will the children be
// removed?

// problem link - https://cses.fi/problemset/task/2162/

#include <bits/stdc++.h>
#define ll long long
using namespace std;

void solve() {
    ll n;
    cin >> n;
    set<ll> s;
    for (int i = 1; i <= n; i++) s.insert(i);
    auto it = s.begin();
    ll c = 0;
    ll cnt = n;
    while (cnt != 1) {
        --cnt;
        if (c < 1) {
            ++c;
            ++it;
        }
        if (it == s.end())
            it = s.begin();
        if (c) {
            cout << *it << " ";

            s.erase(it++);
            if (it == s.end())
                it = s.begin();
            c = 0;
            if (it == s.end())
                it = s.begin();
        }
    }
    cout << *s.begin() << endl;
}
//----------------------Main----------------------------//

int main() {
    FIO;

    // test case - 7
    // output - 2 4 6 1 5 3 7

    solve();

    return 0;
}