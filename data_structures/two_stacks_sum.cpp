
/**
 * @author      : abhj
 * @created     : Friday Oct 01, 2021 17:31:47 IST
 * @filename    : c.cpp
 */

#include "bits/stdc++.h"
#define int          long long int
#define mp           make_pair
#define pb           emplace_back
#define F            first
#define S            second
using vi       =     std::vector<int>;
using vvi      =     std::vector<vi>;
using pii      =     std::pair<int, int>;
using vpii     =     std::vector<pii>;
using vvpii    =     std::vector<vpii>;
using namespace std;
const int inf  =     1e18 + 10;
const int N    =     2e6 + 10;
int n, m, x;
void solve() {
	cin >> n >> m >> x;
	vi a (n), b (m);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < m; i++)
		cin >> b[i];
	int sum = 0, cnt = 0, temp = 0, i = 0, j = 0;
	while (i < n and sum + a[i] <= x) {
		sum += a[i];
		i++;
	}
	cnt = i;
	while (j < m and i >= 0) {
		sum += b[j];
		j++;
		while (sum > x and i > 0) {
			i--;
			sum -= a[i];
		}
		if (sum <= x and i + j > cnt)
			cnt = i + j;
	}
	cout << cnt;
}

int32_t main() {
	ios_base::sync_with_stdio (false);
	cin.tie (0);
	solve();
	return 0;
}
