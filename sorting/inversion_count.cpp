/*
 *this program is use to count the number in inversions in an array
 *In an array two elements .i.e. a[i], a[j] are said to be in inverison if a[i] > a[j] and i < j. 
 *The count of inversion indicates how close the array is from being sorted
 *For example for integer array named arr
 *int arr[] = {2,1,3,4}
 *In the array arr (2,1) form an inversion pair because 2 > 1 and 2 comes before 1 in the array.
 *The sort this array we need to swap 1,2, so the count of inversions here is 1.
 *The efficient way to solve is to take some inspiration from the merge sort algorithm
 *This algorithm takes O(NlogN) time.Idea behind the algorithm :
 *Suppose we have an array of integers of size n.
 *Suppose the indices, low = 0, high = n-1, mid = (low + high)/2.
 *The array indices can be visualized as low .............. mid mid+1 .............. high
 *The array is divided into 2 halves, these two halves are sorted recursively, the difference from 
 *the merge sort here is that, while sorting the array recursively, inversion pairs are also counted.
 *We are counting the numbers of inverison while we are sorting left half recursively
 *We are counting the number of inversion while we are sorting right half recursively
 *Then we count number of inverisons while merging both halves together
 *Main code snippet of this alogorithm is 
 *if(start >= end) {
        return 0;
    }
    int inv_count = 0; // initialize the inverision count.
    int int mid = start + (end- start) /2;
    inv_count += inversion_count(arr ,start, mid); // count number of inverisons while sorting left half recursively
    inv_count += inversion_count(arr , mid+1, end); // count number of inverisons while sorting right half recursively
    inv_count += merge(arr,start,end); // merge both halves together and add inversion count
    return inv_count;
*/
#include <cstdlib>
#include <iostream>
#include <vector>


int merge(std ::vector<int> *arr, int start, int end)
{
    int mid = start + (end - start) / 2;
    int i = start;
    int j = mid + 1;
    int k = start;
    std ::vector<int> temp(1000000);
    int cnt = 0;

    while (i <= mid and j <= end)
    {
        if (arr->at(i) <= arr->at(j))
        {
            temp[k] = arr->at(i);
            k++;
            i++;
        }
        else
        { // inversion
            temp[k++] = arr->at(j++);
            cnt += mid - i + 1;
        }
    }
    while (i <= mid)
    {
        temp[k++] = arr->at(i++);
    }

    while (j <= end)
    {
        temp[k++] = arr->at(j++);
    }
    for (int i = start; i <= end; i++)
    {
        arr->at(i) = temp[i];
    }
    return cnt;
}

int inversion_count(std ::vector<int> *arr, int start, int end)
{

    if (start >= end)
    {
        return 0;
    }
    int inv_count = 0; // initialize the inverision count.
    int mid = start + (end - start) / 2;
    inv_count += inversion_count(arr, start, mid);   // count number of inverisons while sorting left half recursively
    inv_count += inversion_count(arr, mid + 1, end); // count number of inverisons while sorting right half recursively
    inv_count += merge(arr, start, end);             // merge both halves together and add inversion count
    return inv_count;
}

int main()
{

    int n = 0;
    std::cin >> n;
    int e = 0;
    std::vector<int> arr;
    for (int i = 0; i < n; i++)
    {
        std::cin >> e;
        arr.push_back(e);
    }
    std ::cout << inversion_count(&arr, 0, n - 1) << std::endl;
    return 0;
}
