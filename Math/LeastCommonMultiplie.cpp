//Algorithm for finding lcm of two numbers a and b

#include <iostream>
#include <math.h>
using namespace std;

int HCF(int a, int b)
{
    if (b == 0)
        return a;

    return HCF(b, a % b);
}

int LCM(int a, int b)
{
    return (a * b) / HCF(a,b); //using Euclidean algorithm
}

int main()
{
    int a, b;
    cout << "Enter the first number" << endl;
    cin >> a;
    cout << "Enter the second number" << endl;
    cin >> b;
    cout << "LCM of " << a << " and " << b << " is = " << LCM(a,b) << endl;
}
