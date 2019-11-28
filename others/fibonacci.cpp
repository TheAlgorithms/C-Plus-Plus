//An efficient way to calculate nth fibonacci number faster and simpler than O(nlogn) method of matrix exponentiation
//This works by using both recursion and dynamic programming.
//as 93rd fibonacci exceeds 19 digits, which cannot be stored in a single long long variable, we can only use it till 92nd fibonacci
//we can use it for 10000th fibonacci etc, if we implement bigintegers.
//This algorithm works with the fact that nth fibonacci can easily found if we have already found n/2th or (n+1)/2th fibonacci
//It is a property of fibonacci similar to matrix exponentiation.

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

int main()
{
    //Main Function
    for (long long i = 1; i < 93; i++)
    {
        cout << i << " th fibonacci number is " << fib(i) << "\n";
    }
    return 0;
}
