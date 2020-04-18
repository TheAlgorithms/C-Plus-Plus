//#include <bits/stdc++.h>
#incldue <iostream>
#define MAX 4000000
using namespace std;
typedef long long ll;
void ConsTree(ll arr[], ll segtree[], ll low, ll high, ll pos)
{
	if (low == high)
	{
		segtree[pos] = arr[low];
		return;
	}
	ll mid = (low + high) / 2;
	ConsTree(arr, segtree, low, mid, 2 * pos + 1);
	ConsTree(arr, segtree, mid + 1, high, 2 * pos + 2);
	segtree[pos] = segtree[2 * pos + 1] + segtree[2 * pos + 2];
}
ll query(ll segtree[], ll lazy[], ll qlow, ll qhigh, ll low, ll high, ll pos)
{
	if (low > high)
		return 0;
	if (qlow > high || qhigh < low)
		return 0;
	if (lazy[pos] != 0)
	{
		segtree[pos] += lazy[pos] * (high - low + 1);
		if (low != high)
		{
			lazy[2 * pos + 1] += lazy[pos];
			lazy[2 * pos + 2] += lazy[pos];
		}
		lazy[pos] = 0;
	}
	if (qlow <= low && qhigh >= high)
		return segtree[pos];
	ll mid = (low + high) / 2;
	return query(segtree, lazy, qlow, qhigh, low, mid, 2 * pos + 1) + query(segtree, lazy, qlow, qhigh, mid + 1, high, 2 * pos + 2);
}
void update(ll segtree[], ll lazy[], ll start, ll end, ll delta, ll low, ll high, ll pos)
{
	if (low > high)
		return;
	if (lazy[pos] != 0)
	{
		segtree[pos] += lazy[pos] * (high - low + 1);
		if (low != high)
		{
			lazy[2 * pos + 1] += lazy[pos];
			lazy[2 * pos + 2] += lazy[pos];
		}
		lazy[pos] = 0;
	}
	if (start > high || end < low)
		return;
	if (start <= low && end >= high)
	{
		segtree[pos] += delta * (high - low + 1);
		if (low != high)
		{
			lazy[2 * pos + 1] += delta;
			lazy[2 * pos + 2] += delta;
		}
		return;
	}
	ll mid = (low + high) / 2;
	update(segtree, lazy, start, end, delta, low, mid, 2 * pos + 1);
	update(segtree, lazy, start, end, delta, mid + 1, high, 2 * pos + 2);
	segtree[pos] = segtree[2 * pos + 1] + segtree[2 * pos + 2];
}
int main()
{
	ll n, c;
	scanf("%lld %lld", &n, &c);
	ll arr[n] = {0}, p, q, v, choice;
	ll segtree[MAX], lazy[MAX] = {0};
	ConsTree(arr, segtree, 0, n - 1, 0);
	while (c--)
	{
		scanf("%lld", &choice);
		if (choice == 0)
		{
			scanf("%lld %lld %lld", &p, &q, &v);
			update(segtree, lazy, p - 1, q - 1, v, 0, n - 1, 0);
		}
		else
		{
			scanf("%lld %lld", &p, &q);
			printf("%lld\n", query(segtree, lazy, p - 1, q - 1, 0, n - 1, 0));
		}
	}
	return 0;
}
