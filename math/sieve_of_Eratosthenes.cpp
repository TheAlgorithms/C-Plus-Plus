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

int isprime[MAX];

/*
 * This is the function that finds the primes and eliminates 
 * the multiples.
 */
void sieve(int N)
{
    isprime[0] = 0;
    isprime[1] = 0;
    for (int i = 2; i <= N; i++)
    {
        if (isprime[i])
        {
            for (int j = i * 2; j <= N; j += i)
            {
                isprime[j] = 0;
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
        if (isprime[i] == 1)
        {
            cout << i << ' ';
        }
    }
    cout << '\n';
}

/*
 * NOTE: This function is important for the 
 * initialization of the array.
 */
void init()
{
    for (int i = 1; i < MAX; i++)
    {
        isprime[i] = 1;
    }
}

int main()
{
    int N = 100;
    init();
    sieve(N);
    print(N);
}
