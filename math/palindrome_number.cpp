#include <iostream>
using namespace std;


bool isPalindrome(int number) {
   
    if (number < 0) return false;

    int originalNumber = number;
    int reversedNumber = 0;

 
    while (number > 0) {
        int lastDigit = number % 10;
        reversedNumber = reversedNumber * 10 + lastDigit;
        number /= 10;
    }

    return originalNumber == reversedNumber;
}

int main() {
    int number;
    cout << "Enter a number: ";
    cin >> number;

    if (isPalindrome(number)) {
        cout << "The number is a palindrome." << endl;
    } else {
        cout << "The number is not a palindrome." << endl;
    }

    return 0;
}
