// This program aims at calculating the GCD of n numbers by division method
#include <iostream>

int main() {
    int n;
    std::cout << "Enter value of n:" << std::endl;
    std::cin >> n;
    int *a = new int[n];
    int i, j, gcd;
    std::cout << "Enter the n numbers:" << std::endl;
    for (i = 0; i < n; i++) std::cin >> a[i];
    j = 1;  // to access all elements of the array starting from 1
    gcd = a[0];
    while (j < n) {
        if (a[j] % gcd == 0)  // value of gcd is as needed so far
            j++;              // so we check for next element
        else
            gcd = a[j] % gcd;  // calculating GCD by division method
    }
    std::cout << "GCD of entered n numbers:" << gcd;
    delete[] a;
    return 0;
}
