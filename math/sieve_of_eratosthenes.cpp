/*
 * Sieve of Eratosthenes is an algorithm to find the primes 
 * that is between 2 to N (as defined in main).
 *
 * Time Complexity  : O(N * log N)
 * Space Complexity : O(N)
 */

#include <iostream>
using namespace std;

#define MAX 10000000

bool isprime[MAX];

/*
 * This is the function that finds the primes and eliminates 
 * the multiples.
 */
void sieve(int N)
{
    isprime[0] = true;
    isprime[1] = true;
    for (int i = 2; i * i <= N; i++)
    {
        if (!isprime[i])
        {
            for (int j = i * i; j <= N; j += i)
            {
                isprime[j] = true;
            }
        }
    }
}

/*
 * This function prints out the primes to STDOUT
 */
void print(int N)
{
    for (int i = 1; i <= N; i++)
    {
        if (!isprime[i])
        {
            cout << i << ' ';
        }
    }
    cout << '\n';
}

int main()
{
    int N = 100;
    sieve(N);
    print(N);
}
