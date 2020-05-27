/**
 * @file
 * @brief This program aims at calculating the GCD of n numbers by division
 * method
 *
 * @see gcd_iterative_euclidean.cpp, gcd_recursive_euclidean.cpp
 */
#include <iostream>

/** Compute GCD using division algorithm
 *
 * @param[in] a array of integers to compute GCD for
 * @param[in] n number of integers in array `a`
 */
int gcd(int *a, int n) {
    int j = 1;  // to access all elements of the array starting from 1
    int gcd = a[0];
    while (j < n) {
        if (a[j] % gcd == 0)  // value of gcd is as needed so far
            j++;              // so we check for next element
        else
            gcd = a[j] % gcd;  // calculating GCD by division method
    }
    return gcd;
}

/** Main function */
int main() {
    int n;
    std::cout << "Enter value of n:" << std::endl;
    std::cin >> n;
    int *a = new int[n];
    int i;
    std::cout << "Enter the n numbers:" << std::endl;
    for (i = 0; i < n; i++) std::cin >> a[i];

    std::cout << "GCD of entered n numbers:" << gcd(a, n) << std::endl;

    delete[] a;
    return 0;
}
