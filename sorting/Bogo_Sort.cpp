//In computer science, bogosort (also known as permutation sort, stupid sort, slowsort, shotgun sort, random sort,
//monkey sort, bobosort or shuffle sort) is a highly inefficient sorting algorithm based on the generate and test paradigm. The function
//successively generates permutations of its input until it finds one that is sorted. It is not useful for sorting, but may be used for
//educational purposes, to contrast it with more efficient algorithms.

//Two versions of this algorithm exist: a deterministic version that enumerates all permutations until it hits a sorted one,
// and a randomized version that randomly permutes its input. 
//Randomized version is implemented below.

#include <iostream>
#include <vector>
using namespace std;

bool isSorted(vector <int> arr)
{
    for(int i = 0; i < arr.size() - 1; i ++)
    {
        if(arr[i] > arr[i + 1])
        {
            return false;
        }
    }
    return true;
}
void ShowArray(vector <int> arr)
{
    for(int i = 0; i < arr.size(); i ++)
    {
        cout << arr[i] << ' ';
    }
    cout << endl;
}
void shuffle(vector <int> &arr)
{
    for(int i = 0; i < arr.size(); i ++)
    {
        swap(arr[i], arr[rand() % arr.size()]);
    }
}
void randomized_BogoSort(vector <int> arr)
{
    while(!isSorted(arr))
    {
        shuffle(arr);
    }
    cout << "Sorted Array (Randomized Bogosort) : " ;
    ShowArray(arr);
}

int main()
{
    int size = 0;
    cout << "Enter Array Size : ";
    cin >> size;

    vector <int> arr(size);
    cout << "Enter Elements one by one : ";
    for(int &x : arr)
    {
        cin >> x;
    }

    randomized_BogoSort(arr);

    return 0;
}