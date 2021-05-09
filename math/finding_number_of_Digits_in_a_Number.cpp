/**
 * @author amino19
 * @file
 *
 * \brief Finding number of Digits in a Number
 * \details Basically, its a very basic math of
 *  finding number of digits in a number (input),
 *  For more details, refer Algorithms-Explanation
 */

#include<bits/stdc++.h>
using namespace std;

// Main function
int main()
{
    int N;
    cout << "Enter the number: ";
    /* given number as input  */
    cin >> N;

    /* algorithmic formula */
    int k = floor(log10(N) + 1);

    /* print number of digits */
    cout << "Number of digits: " << k;
}