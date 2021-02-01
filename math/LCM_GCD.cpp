#include <iostream>
using namespace std;

int gcd(int a, int b) {
    if (a == 0) {
        return b;
    }
    return gcd(b % a, a);
}

int lcm(int a, int b) { return (a * b) / gcd(a, b); }

int main() {
    int a, b = 0;
    cout << "Enter First Number: ";
    cin >> a;
    cout << "Enter Second Number: ";
    cin >> b;
    cout << "GCD is " << gcd(a, b) << endl;
    // cout << endl;
    cout << "LCM is " << lcm(a, b) << endl;
    // cout << endl;
    return 0;
}
