// Program to check whether a number is an armstrong number or not
#include <cmath>
#include <iostream>
using std::cin;
using std::cout;

int main() {
    int n = 0, temp = 0, rem = 0, count = 0, sum = 0;
    cout << "Enter a number: ";
    cin >> n;

    temp = n;

    /* First Count the number of digits
       in the given number */
    while (temp != 0) {
        temp /= 10;
        count++;
    }

    /* Calculation for checking of armstrongs number i.e.
       in an n-digit number sum of the digits is raised to a power of n
       is equal to the original number */

    temp = n;
    while (temp != 0) {
        rem = temp % 10;
        sum += static_cast<int>(pow(rem, count));
        temp /= 10;
    }

    if (sum == n) {
        cout << n << " is an armstrong number";
    } else {
        cout << n << " is not an armstrong number";
    }

    return 0;
}
