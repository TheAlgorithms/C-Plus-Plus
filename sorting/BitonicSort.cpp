// Source : https://www.geeksforgeeks.org/bitonic-sort/

/* C++ Program for Bitonic Sort. Note that this program 
   works only when size of input is a power of 2. */

#include <stdio.h>
#include <algorithm.h>
using namespace std;

/*The parameter dir indicates the sorting direction, ASCENDING 
   or DESCENDING; if (a[i] > a[j]) agrees with the direction, 
   then a[i] and a[j] are interchanged.*/
void compAndSwap(int a[], int i, int j, int dir)
{
    if (dir == (a[i] > a[j]))
        swap(a[i], a[j]);
}

/*It recursively sorts a bitonic sequence in ascending order, 
  if dir = 1, and in descending order otherwise (means dir=0). 
  The sequence to be sorted starts at index position low, 
  the parameter cnt is the number of elements to be sorted.*/
void bitonicMerge(int a[], int low, int cnt, int dir)
{
    if (cnt > 1)
    {
        int k = cnt / 2;
        for (int i = low; i < low + k; i++)
            compAndSwap(a, i, i + k, dir);
        bitonicMerge(a, low, k, dir);
        bitonicMerge(a, low + k, k, dir);
    }
}

/* This function first produces a bitonic sequence by recursively 
    sorting its two halves in opposite sorting orders, and then 
    calls bitonicMerge to make them in the same order */
void bitonicSort(int a[], int low, int cnt, int dir)
{
    if (cnt > 1)
    {
        int k = cnt / 2;

        // sort in ascending order since dir here is 1
        bitonicSort(a, low, k, 1);

        // sort in descending order since dir here is 0
        bitonicSort(a, low + k, k, 0);

        // Will merge wole sequence in ascending order
        // since dir=1.
        bitonicMerge(a, low, cnt, dir);
    }
}

/* Caller of bitonicSort for sorting the entire array of 
   length N in ASCENDING order */
void sort(int a[], int N, int up)
{
    bitonicSort(a, 0, N, up);
}

// Driver code
int main()
{
    int a[] = {3, 7, 4, 8, 6, 2, 1, 5};
    int N = sizeof(a) / sizeof(a[0]);

    int up = 1; // means sort in ascending order
    sort(a, N, up);

    printf("Sorted array: \n");
    for (int i = 0; i < N; i++)
        printf("%d ", a[i]);
    return 0;
}
