const int N = 1e6 + 3;
const int mod = 1e9 + 7;
int fact[N];

void precompute() {
	fact[0] = 1;
	for (int i = 1; i < N; i++)
		fact[i] = (fact[i - 1] * i) % mod;
}

int power(int x, int y) {
	int res = 1;
	x = x % mod;
	while (y)
	{
		if (y & 1) res = (res * x) % mod;
		x = (x * x) % mod;
		y >>= 1;
	}
	return res;
}

int modInverse(int n, int p) {
	return power(n, p - 2);
}

int comb(int n, int r)
{
	if (r == 0)
		return 1;

	return (fact[n] * modInverse(fact[r], mod) % mod * modInverse(fact[n - r], mod) % mod) % mod;
}
