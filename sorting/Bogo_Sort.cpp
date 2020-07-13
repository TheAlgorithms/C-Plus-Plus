// In computer science, bogosort (also known as permutation sort, stupid sort, slowsort, shotgun sort, random sort,
//monkey sort, bobosort or shuffle sort) is a highly inefficient sorting algorithm based on the generate and test paradigm. The function
//successively generates permutations of its input until it finds one that is sorted. It is not useful for sorting, but may be used for
//educational purposes, to contrast it with more efficient algorithms.
//  Two versions of this algorithm exist: a deterministic version that enumerates all permutations until it hits a sorted one,
// and a randomized version that randomly permutes its input. 
//Randomized version is implemented below.
#include <iostream>
#include <cassert>
//This function checks if array is sorted
bool is_sorted(int *arr, int n)
{
    for(int i = 0; i < n - 1; i ++)
    {
        //If any element is greater than element after it than it is not sorted
        if(arr[i] > arr[i + 1])
        {
            return false;
        }
    }
    return true;
}
//This function prints the array
void show_array(int *arr, int n)
{
    for(int i = 0; i < n; i ++)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}
//This function shuffles the array randomly
void shuffle(int *arr, int n)
{
    for(int i = 0; i < n; i ++)
    {
        //Swaps i'th  index with random index (less than array size)
        std::swap(arr[i], arr[rand() % n]);
    }
}
//Randomized bogo sort
void randomized_bogosort(int *arr, int n)
{
    //Untill array is not sorted
    while(!is_sorted(arr, n))
    {
        shuffle(arr, n);//Shuffle the array
    }
}
//Driver Code
int main()
{
    int n = 5; //Size of an array
    int arr[5] = {3, 7, 10, 4, 1}; // Defining array which we want to sort
    randomized_bogosort(arr, n); //Callling bogo sort on it
    std::cout << "Sorted Array (Randomized Bogosort) : " ;
    show_array(arr, n); //Printing sorted array
    assert(is_sorted(arr, n));//For testing purpose
    return 0;
}