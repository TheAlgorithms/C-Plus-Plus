#include <iostream>
using namespace std;
// time complexity O(n)
// space complexity O(n)
int trapped(int arr[], int n)
{
    int trapwater = 0;
    int lmax[n], rmax[n];
    lmax[0] = arr[0];
    for (int j = 1; j < n; j++)
    {
        lmax[j] = max(arr[j], lmax[j - 1]);
    } // for given input for loop be give {3,3,3,3,5}
    rmax[n - 1] = arr[n - 1];
    for (int k = n - 2; k >= 0; k--)
    {
        rmax[k] = max(rmax[k + 1], arr[k]);
    } // for given input for loop be give {5,5,5,5,5}
    for (int i = 1; i < n - 1; i++)
    {
        trapwater = trapwater + (min(lmax[i], rmax[i]) - arr[i]);
    }
    return trapwater;
}

int main()
{
    int arr[] = {3, 0, 1, 2, 5};
    cout << trapped(arr, 5);
    return 0;
}