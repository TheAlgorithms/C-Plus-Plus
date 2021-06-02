// finding nCk % m given m is prime
// nCk % m = (n!/(k)!(n-k)!) % m
//         = (n!) * inverse(k!) * inverse(n-k)! % m 
// Since m is prime inverse(x) = x^(m-2) % m ( by Fermat's theorem )
// So nCk % m = factorial[k] * inverse[k] * inverse[n-k] % m
//
// Tested on: https://cses.fi/problemset/task/1079/
                                            
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6+6;
const ll mod = 1e9+7;    // mod is prime
vector<ll> factorial(N); // pre calculating factorials and inverses
vector<ll> inverse(N);
 
// binary exponentiation O(log(n))
ll binpow(ll a, ll b, ll x) {
	a %= x;
	ll res = 1;
	while (b > 0) {
		if (b & 1) { res = res * a % x; }
		a = a * a % x;
		b >>= 1;
  }
  return res;
}
// pre calculating inverse and factorial O(n * log(n)) 
void pre(){
  factorial[0] = 1;
  inverse[0] = binpow(1,mod-2,mod);
  for(int i=1; i<N; ++i){
    factorial[i] = i * factorial[i-1] % mod;
    inverse[i] = binpow(factorial[i],mod-2,mod);
  }
}
// nCk % mod  
ll nck(int n, int k){
  ll ans = factorial[n];
  ans = ans * inverse[k] % mod;
  ans = ans * inverse[n-k] % mod;
  return ans;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int t;
	cin>>t;
	pre();
	while(t--){
		ll a, b;
		cin>>a>>b;
		cout<<nck(a,b)<<'\n';
	}
	return 0;
 
}
