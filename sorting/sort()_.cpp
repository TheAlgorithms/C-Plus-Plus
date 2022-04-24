/*Using sort() function in cpp
By default sort() sorts the array in ascending order. But this can be modified
by passing conditions through sort()

Syntax: sort(parameter1,parameter2,parameter3)

where parameter1 is the array to be sorted , parameter 2 is size of array and
parameter3 is desired sorting for eg:  interval range or descending parameter 3
options:
    1. sort(array, array + n);
    2. sort(array, array + n, greater<int>());
    3. sort(array, array + n, Interval);
*/
#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;
int main()
{
    int array[] = {1, 2, 4, 3, 6, 7, 3, 5, 8, 0, 9};
    int n = sizeof(array) / sizeof(array[0]);

    /*input is the starting of array and length to be sorted*/
    sort(array, array + n);

    cout << "\nSorted Array using "
            "default sort is : \n";
    for (int i = 0; i < n; ++i) cout << array[i] << " ";
    return 0;
}
