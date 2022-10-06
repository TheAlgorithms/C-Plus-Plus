#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << endl << endl << endl;
    cout << "------------C++ program for perfect number----------" << endl
         << endl;
    int num, i = 1, sum = 0;
    cout << "Enter a number : ";
    cin >> num;
    while (i < num) {
        if (num % i == 0)
            sum = sum + i;
        i++;
    }

    if (sum == num)
        cout << i << " is a perfect number\n";
    else
        cout << i << " is not a perfect number\n";
    system("pause");

    return 0;
}