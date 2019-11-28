#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Declaring variables for maintaing prime numbers and to check whether a number is prime or not
bool isprime[1000006];
vector<int> prime_numbers;
vector<pair<int, int>> factors;

// Calculating prime number upto a given range
void SieveOfEratosthenes(int N)
{
    // initializes the array isprime
    memset(isprime, true, sizeof isprime);

    for (int i = 2; i <= N; i++)
    {
        if (isprime[i])
        {
            for (int j = 2 * i; j <= N; j += i)
                isprime[j] = false;
        }
    }

    for (int i = 2; i <= N; i++)
    {
        if (isprime[i])
            prime_numbers.push_back(i);
    }
}

// Prime factorization of a number
void prime_factorization(int num)
{

    int number = num;

    for (int i = 0; prime_numbers[i] <= num; i++)
    {
        int count = 0;

        // termination condition
        if (number == 1)
        {
            break;
        }

        while (number % prime_numbers[i] == 0)
        {
            count++;
            number = number / prime_numbers[i];
        }

        if (count)
            factors.push_back(make_pair(prime_numbers[i], count));
    }
}

/*
    I added a simple UI.
*/
int main()
{
    int num;
    cout << "\t\tComputes the prime factorization\n\n";
    cout << "Type in a number: ";
    cin >> num;

    SieveOfEratosthenes(num);

    prime_factorization(num);

    // Prime factors with their powers in the given number in new line
    for (auto it : factors)
    {
        cout << it.first << " " << it.second << endl;
    }

    return 0;
}
