/*  
* Calculation of the first n fibonacci numbers.
*/
#include<iostream>
#include<vector>

using namespace std;

// n fibonacci numbers to be calculated
vector<long long> fib(unsigned int n)
{
    long long fn = 0;
    vector<long long> fibNumbers;
    fibNumbers.push_back(0L);
    fibNumbers.push_back(1L);

    if (n > 2)
    {
        for(int i = 0; i <= n - 2 ;i++)
        {
            fn = fibNumbers[fibNumbers.size() -1] + fibNumbers[fibNumbers.size() - 2];
            fibNumbers.push_back(fn);
        }
    }
    return fibNumbers;
}


int main()
{
    unsigned int n = 20;
    vector<long long> fibo = fib(n);

    cout << "Fibonacci number for: " << n << endl;

    for (vector<long long>::iterator it = fibo.begin(); it != fibo.end();it++)
        cout << *it << endl;
}