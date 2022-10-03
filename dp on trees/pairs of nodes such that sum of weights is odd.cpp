#include <bits/stdc++.h>
#define int long long
using namespace std;
#define full(v1)      v1.begin(), v1.end()
#define pb            push_back
#define loop(i, a, b) for (int i = (a); i < (b); i++)
#define endl          "\n"
#define is(x)         cerr << #x << " is " << x << "\n";
vector<pair<int, int>> v[100009];
vector<pair<int, int>> dp(100001);
void dfs(int s, int p, int ct) {
    dp[s] = {0, 0};
    for (auto i : v[s]) {
        if (i.first != p) {
            if (i.second)
                dp[s].second++;
            else
                dp[s].first++;
            dfs(i.first, s, i.second);
            if (i.second) {
                dp[s].first += dp[i.first].second;
                dp[s].second += dp[i.first].first;
            } else {
                dp[s].second += dp[i.first].second;
                dp[s].first += dp[i.first].first;
            }
        }
    }
}
void actualdfs(int s, int p) {
    for (auto i : v[s]) {
        if (i.first != p) {
            int a = dp[i.first].first;   // even
            int b = dp[i.first].second;  // odd
            if (!i.second) {
                dp[i.first] = dp[s];
            } else {
                dp[i.first].first = (dp[s].second - 1);
                dp[i.first].second = (dp[s].first + 1);
            }
            actualdfs(i.first, s);
        }
    }
}

void solve() {
    int i, j, n, t, q, a, b, m, k, ct = 0, sum = 0, flag = 0;
    cin >> n;
    m = n - 1;
    while (m--) {
        cin >> a >> b >> k;
        k %= 2;
        v[a].pb({b, k});
        v[b].pb({a, k});
    }
    dfs(1, 0, 0);
    actualdfs(1, 0);
    for (int i = 1; i <= n; i++) sum += dp[i].second;
    cout << sum / 2;
}
signed main() {
    // freopen("lineup.in","r",stdin);
    // freopen("lineup.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    // cin>>t;
    while (t--) {
        solve();
        cout << "\n";
    }

    cerr << clock() * 1000.0 / CLOCKS_PER_SEC << 'm' << 's';
    return 0;
}
