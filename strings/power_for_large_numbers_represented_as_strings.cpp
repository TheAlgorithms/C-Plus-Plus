/**
 * \file
 * \brief The gfg
 *modulo-power-for-large-numbers-represented-as-strings
 */
#include <iostream> 
using namespace std; 
#define ll long long int 
const ll MOD = 1e9 + 7; 
// Returns modulo exponentiation for two numbers 
// represented as long long int. It is used by 
// powerStrings(). Its complexity is log(n) 
ll powerLL(ll x, ll n) { 
	ll result = 1; 
	while (n) {
		if (n & 1) {
			result = result * x % MOD;
		}

		n = n / 2; 
		x = x * x % MOD; 
	} 
	return result; 
} 
// Returns modulo exponentiation for two numbers 
// represented as strings. It is used by 
// powerStrings() 
ll powerStrings(string sa, string sb) { 
	// We convert strings to number 
	ll a = 0, b = 0; 
	// calculating a % MOD 
	for (int i = 0; i < sa.length(); i++) 
		a = (a * 10 + (sa[i] - '0')) % MOD; 
	// calculating b % (MOD - 1) 
	for (int i = 0; i < sb.length(); i++) 
		b = (b * 10 + (sb[i] - '0')) % (MOD - 1); 
	// Now a and b are long long int. We 
	// calculate a^b using modulo exponentiation 
	return powerLL(a, b); 
} 
int main() { 
     string sa,sb; 
	 cin>>sa>>sb;
	 cout << powerStrings(sa, sb) << endl; 
	return 0; 
} 
