#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

void primefactors (int n)
{
    int count = 0;

    while (!(n % 2)) {
        n = n >> 1;
        count++;
    }

    if (count)
        cout << 2 << "  " << count << "\n";

    for (int i = 3; i <= sqrt(n); i += 2) {
        count = 0;
        while (n % i == 0) {
            count++;
            n = n / i;
        }
        if (count)
            cout << i << "  " << count << "\n";
    }

    if (n > 2)
        cout << n << "  " << 1 << "\n";
}

void printDivisors(int n)
{
    vector<int> v;
    for (int i=1; i<=sqrt(n); i++)
    {
        if (n%i==0)
        {
            if (n/i == i)
                cout << i << " ";
            else
            {
                cout << i << " ";

                v.push_back(n/i);
            }
        }
    }


    for (int i=v.size()-1; i>=0; i--)
        cout << v[i] << " " ;
}


int main()
{
    int number;
    cout << "\t\tComputes the prime factorization\n\n";
    cout << "Type in a number: ";
    cin >> number;


    primefactors(number);
    cout << "\n";
    printDivisors(number);
    return 0;
}
