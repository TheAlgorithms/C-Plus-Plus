//https://codeforces.com/blog/entry/18051
#include <bits/stdc++.h>
using namespace std;


template<class T> struct segtree { // comb(ID,b) = b
	const T ID = 0; T comb(T a, T b) { return a + b; }
	int n; vector<T> seg;
	segtree(int _n) { n = _n; seg.assign(2 * n, ID); }
	void pull(int p) { seg[p] = comb(seg[2 * p], seg[2 * p + 1]); }
	void upd(int p, T val) { // set val at position p
		seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p);
	}
	T query(int l, int r) {	// sum on interval [l, r]
		T ra = ID, rb = ID;
		for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
			if (l & 1) ra = comb(ra, seg[l++]);
			if (r & 1) rb = comb(seg[--r], rb);
		}
		return comb(ra, rb);
	}
};

int main() {
	segtree<int> st(10);
	st.upd(1, 1);
	cout << st.query(1, 3);
	return 0;
}