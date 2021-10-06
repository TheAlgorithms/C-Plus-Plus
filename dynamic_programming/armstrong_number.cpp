// Program to check whether a number is an armstrong number or not
#include <bits/stdc++.h>
include <iostream>
using std::cin;
using std::cout;
using namespace std;

int main() {
    int n, temp, rem, count = 0, sum=0;
    cout << "Enter a number: ";
    cin >> n;
    
    temp = n;
    while(temp != 0)
    {
        rem = temp%10;
        temp /= 10;
        count++;
    }

    temp = n;
    while(temp!=0)
    {
        rem = temp%10;
        sum += pow(rem,count);
        temp/=10;
    }
    

    if (sum == n)
        cout << n << " is an armstrong number";
    else
        cout << n << " is not an armstrong number";
    
    return 0;
}
