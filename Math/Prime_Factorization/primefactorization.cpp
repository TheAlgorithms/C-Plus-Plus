#include <iostream>
#include <cmath>
using namespace std;

void primefactors (int n)
{
    int count = 0;

    while (!(n % 2)) {
        n = n >> 1;
        count++;
    }

    if (count)
        cout << 2 << "  " << count << endl;

    for (int i = 3; i <= sqrt(n); i += 2) {
        count = 0;
        while (n % i == 0) {
            count++;
            n = n / i;
        }
        if (count)
            cout << i << "  " << count << endl;
    }

    if (n > 2)
        cout << n << "  " << 1 << endl;
}

int main()
{
    int number;
    cout << "\t\tComputes the prime factorization\n\n";
    cout << "Type in a number: ";
    cin >> number;


    primefactors(number);
    return 0;
}
