#include <bits/stdc++.h>
using namespace std;

// Binary Indexed Tree / Fenwick Tree
// 1-indexed BIT and input array

int MAXN = 100000;
int BIT[100005], arr[100005];

inline void update (int x, int val)
{
	for (;x<=MAXN;x+=(x&(-x)))
		BIT[x]+=val;
}


inline int query(int x)
{
	int sum=0;
	for (;x>0;x-=(x&(-x)))
		sum+=BIT[x];
	return sum;
}

int main() {
	
	int a, b, n, val, ans;
	memset(BIT, 0, sizeof(BIT));
	// Take Input
	
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> arr[i];
		update(i, arr[i]);
	}
	
	// Point Update, Point Query
	// Add val to element at index a
	cin >> val >> a;
	update(a, val);
	// Query element at index a
	cin >> a;
	ans = query(a)-query(a-1);
	cout << ans << endl;

	// Point Update, Range Query
	// Add val to element at index a
	cin >> val >> a;
	update(a, val);
	// Query sum of elements from index a to b inclusive
	cin >> a >> b;
	ans = query(b)-query(a-1);
	cout << ans << endl;
	
	// 5
	// 1 2 3 4 5
	// 1 1 -> 2 2 3 4 5
	// 1 -> ans = 2
	// 2 2 -> 2 4 3 4 5
	// 2 5 -> ans = 16

	return 0;
}