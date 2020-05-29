//Program to calculate length of longest increasing subsequence in an array
// in O(n log n)
// tested on : https://cses.fi/problemset/task/1145/

#include <iostream>

using namespace std;
int LIS(int arr[], int n)
{
    set < int > active; // The current built LIS.
    active.insert(arr[0]);
    // Loop through every element.
    for (int i = 1; i < n; ++i)
    {
        auto get = active.lower_bound(arr[i]);
        if (get == active.end())
	{
            active.insert(arr[i]);
        } // current element is the greatest so LIS increases by 1.
        else
	{
            int val = * get; // we find the position where arr[i] will be in the LIS. If it is in the LIS already we do nothing
            if (val > arr[i])
	    {
                // else we remove the bigger element and add a smaller element (which is arr[i]) and continue;
                active.erase(get);
                active.insert(arr[i]);
            }
        }
    }
    return active.size(); // size of the LIS.
}
int main(int argc, char const * argv[])
{
    int n;
    cout << "Enter size of array: ";
    cin >> n;
    int a[n];
    cout << "Enter array elements: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }
    cout << LIS(a, n) << endl;
    return 0;
}
