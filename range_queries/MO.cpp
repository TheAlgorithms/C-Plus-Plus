#include <iostream>
using namespace std;
const int N = 1e6 + 5;
int a[N], bucket[N], cnt[N];
int bucket_size;
struct query
{
	int l, r, i;
} q[N];
int ans = 0;

void add(int index)
{
	cnt[a[index]]++;
	if (cnt[a[index]] == 1)
		ans++;
}
void remove(int index)
{
	cnt[a[index]]--;
	if (cnt[a[index]] == 0)
		ans--;
}

bool mycmp(query x, query y)
{
	if (x.l / bucket_size != y.l / bucket_size)
		return x.l / bucket_size < y.l / bucket_size;
	return x.r < y.r;
}

int main()
{
	int n, t, i, j, k = 0;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d", &a[i]);
	bucket_size = ceil(sqrt(n));
	scanf("%d", &t);
	for (i = 0; i < t; i++)
	{
		scanf("%d %d", &q[i].l, &q[i].r);
		q[i].l--;
		q[i].r--;
		q[i].i = i;
	}
	sort(q, q + t, mycmp);
	int left = 0, right = 0;
	for (i = 0; i < t; i++)
	{
		int L = q[i].l, R = q[i].r;
		while (left < L)
		{
			remove(left);
			left++;
		}
		while (left > L)
		{
			add(left - 1);
			left--;
		}
		while (right <= R)
		{
			add(right);
			right++;
		}
		while (right > R + 1)
		{
			remove(right - 1);
			right--;
		}
		bucket[q[i].i] = ans;
	}
	for (i = 0; i < t; i++)
		printf("%d\n", bucket[i]);
	return 0;
}
