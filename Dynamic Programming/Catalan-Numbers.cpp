/** Print all the Catalan numbers from 0 to n, n being the user input.

 * A Catalan number satifies the following two properties:
 * C(0) = C(1) = 1; C(n) = sum(C(i).C(n-i-1)), from i = 0 to n-1
 * Read more about Catalan numbers here:
    https://en.wikipedia.org/wiki/Catalan_number
 */

#include <iostream>
using namespace std;

int *cat; // global array to hold catalan numbers

unsigned long int catalan_dp(int n)
{
    /** Using the tabulation technique in dynamic programming,
        this function computes the first `n+1` Catalan numbers

        Parameter
        ---------
        n: The number of catalan numbers to be computed.

        Returns
        -------
        cat[n]: An array containing the first `n+1` Catalan numbers
    */

    // By definition, the first two Catalan numbers are 1
    cat[0] = cat[1] = 1;

    // Compute the remaining numbers from index 2 to index n, using tabulation
    for (int i = 2; i <= n; i++)
    {
        cat[i] = 0;
        for (int j = 0; j < i; j++)
            cat[i] += cat[j] * cat[i - j - 1]; // applying the definition here
    }

    // Return the result
    return cat[n];
}

int main(int argc, char *argv[])
{
    int n;
    cout << "Enter n: ";
    cin >> n;

    cat = new int[n + 1];

    cout << "Catalan numbers from 0 to " << n << " are:\n";
    for (int i = 0; i <= n; i++)
    {
        cout << "catalan (" << i << ") = " << catalan_dp(i) << endl;
        // NOTE: Since `cat` is a global array, calling `catalan_dp`
        // repeatedly will not recompute the the values already computed
        // as in case of pre-computed values, the array will simply return them,
        // instead of recomputing them.
    }

    return 0;
}

/** Sample Test Case:

$ cd "Dynamic Programming"
$ g++ Catalan-Numbers.cpp
$ ./a.exe

Enter n: 5
Catalan numbers from 0 to 5 are:
catalan (0) = 1
catalan (1) = 1
catalan (2) = 2
catalan (3) = 5
catalan (4) = 14
catalan (5) = 42

*/
