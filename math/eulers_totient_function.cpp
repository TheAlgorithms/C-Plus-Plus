#include<bits/stdc++.h>

using namespace std;

/**

Euler Totient Function also know as phi function.

phi(n) = phi(p1^a1).phi(p2^a2)...
where p1, p2,... are prime factor of n.

3 Euler's Property:
1. phi(prime_no) = prime_no-1
2. phi(prime_no^k) = (prime_no^k - prime_no^(k-1))
3. phi(a,b) = phi(a). phi(b) where a and b are relative primes.

Applying this 3 property on the first equation.
phi(n) = n. (1-1/p1). (1-1/p2). ...
where p1,p2... are prime factors.

Hence Implementation in O(sqrt(n)).

*/

int phiFunction (int n ) {
    int result = n ;
    for ( ll i=2 ; i*i <= n ; i++ ) {
        if ( n%i == 0 ) {
            while ( n%i == 0 ) {
                n /= i ;
            }
            result -= result/i ;
        }
    }
    if ( n > 1 ) result -= result/n ;
    return result ;
}

int main() {
    int n ;
    cin >> n ;
    cout << phiFunction ( n ) << endl ;
}
