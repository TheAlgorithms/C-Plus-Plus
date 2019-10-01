//This code is used to calculate (a^n)%m
#include <iostream>
using namespace std;

int ModularExponentiation(int a, int n, int M)
{
    if (n == 0)
        return 1;
    else if (n % 2 == 0) //n is even
        return ModularExponentiation((a * a) % M, n / 2, M);
    else //n is odd
        return (a * ModularExponentiation((a * a) % M, (n - 1) / 2, M)) % M;
}

//Driver Code
int main()
{
    int a, n, M;
    cout << "Enter the number" << endl;
    cin >> a;
    cout << "Enter the power" << endl;
    cin >> n;
    cout << "Enter the mod value" << endl;
    cin>>M;
    cout << "Modular Exponentiation value is " << ModularExponentiation(a, n, M) << endl;
}
