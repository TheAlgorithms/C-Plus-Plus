
#include <iostream>
#include <cstdio>
using namespace std;
const long long MAX = 93;

long long f[MAX] = {0};

long long fib(long long n)
{

    if (n == 0)
        return 0;
    if (n == 1 || n == 2)
        return (f[n] = 1);

    if (f[n])
        return f[n];

    long long k = (n % 2 != 0) ? (n + 1) / 2 : n / 2;

    f[n] = (n % 2 != 0) ? (fib(k) * fib(k) + fib(k - 1) * fib(k - 1))
                        : (2 * fib(k - 1) + fib(k)) * fib(k);
    return f[n];
}

void main()
{
    //Main Function
    for (long long i = 1; i < 93; i++)
    {
        cout << i << " th Fibonacci series are " << fib(i) << "\n";
    }
    
}
