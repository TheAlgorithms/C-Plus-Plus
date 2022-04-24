/**
 * \file
 * \brief [ Default Sort Function]
 * Using sort() function in cpp
By default sort() sorts the array in ascending order. But this can be modified further
by passing conditions through sort()

\details
Syntax: sort(parameter1,parameter2,parameter3)

where parameter1 is the array to be sorted , parameter 2 is size of array and
parameter3 is desired sorting for eg:  interval range or descending parameter 3
options:
    1. sort(array, array + n);
    2. sort(array, array + n, greater<int>());
    3. sort(array, array + n, Interval);


 *  1. Easiest way of sorting
 *  2.For small set of data it is quite efficient
 *  3.It does not change the relative order of elements with equal keys.

*/

#include <algorithm>  // for algorithm functions
#include <iostream>   // for IO operations

using namespace std;
int main() {
    int array[] = {1, 2, 4, 3, 6, 7, 3, 5, 8, 0, 9};
    int n = sizeof(array) / sizeof(array[0]);

    /*input is the starting of array and length to be sorted*/
    sort(array, array + n);

    cout << "\nSorted Array using "
            "default sort is : \n";
    for (int i = 0; i < n; ++i) cout << array[i] << " ";
    return 0;
}
