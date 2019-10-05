#include <bits/stdc++.h>

using namespace std;

int phi(int n)
{
    int result = n; // Initialize result as n

    // Consider all prime factors of n and subtract their
    // multiples from result
    for (int p = 2; p * p <= n; ++p) {

        // Check if p is a prime factor.
        if (n % p == 0) {

            // If yes, then update n and result
            while (n % p == 0)
                n /= p;
            result -= result / p;
        }
    }

    // If n has a prime factor greater than sqrt(n)
    // (There can be at-most one such prime factor)
    if (n > 1)
        result -= result / n;
    return result;
}

// Driver program to test above function
int main()
{
    int n;
    cin>>n;
    for (int i = 1; i <= n; i++)
    {
        cout<<"phi("<<i<<"):"<<phi(i)<<endl;
    }
    return 0;
}
