/**
 * @file
 * @brief A buzz number is a number that is either divisible by 7 or has last
 * digit as 7.
 */
#include <iostream>
using namespace std;

/** main function */
int main() {
    int n, t;
    /*enter the number of test case*/
    cin >> t;
    while (t--) {
        /*enter the number n*/
        cin >> n;
        if ((n % 7 == 0) || (n % 10 == 7))
            cout << n << " is a buzz number" <<endl;
        else
            cout << n << " is not a buzz number" <<endl;
    }
    return 0;
}
