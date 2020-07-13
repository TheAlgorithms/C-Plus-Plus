// In computer science, bogosort (also known as permutation sort, stupid sort, slowsort, shotgun sort, random sort,
//monkey sort, bobosort or shuffle sort) is a highly inefficient sorting algorithm based on the generate and test paradigm. The function
//successively generates permutations of its input until it finds one that is sorted. It is not useful for sorting, but may be used for
//educational purposes, to contrast it with more efficient algorithms.
//  Two versions of this algorithm exist: a deterministic version that enumerates all permutations until it hits a sorted one,
// and a randomized version that randomly permutes its input. 
//Randomized version is implemented below.
#include <iostream>
#include <vector>
#include <cassert>
//This function checks if array is sorted
bool is_sorted(const std::vector <int> &arr)
{
    for(int i = 0; i < arr.size() - 1; i ++)
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
void show_array(const std::vector <int> &arr)
{
    for(int x : arr)
    {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}
//This function shuffles the array randomly
std::vector <int> shuffle(std::vector <int> arr)
{
    for(int i = 0; i < arr.size(); i ++)
    {
        //Swaps i'th  index with random index (less than array size)
        std::swap(arr[i], arr[rand() % arr.size()]);
    }
    return arr;
}
//Randomized bogo sort
std::vector <int> randomized_bogosort(std::vector <int> arr)
{
    //Untill array is not sorted
    while(!is_sorted(arr))
    {
        arr = shuffle(arr);//Shuffle the array
    }
    return arr;
}
//Driver Code
int main()
{
    std::vector <int> arr = {3, 7, 10, 4, 1}; // Defining array which we want to sort
    arr = randomized_bogosort(arr); //Callling bogo sort on it
    std::cout << "Sorted Array (Randomized Bogosort) : " ;
    show_array(arr); //Printing sorted array
    assert(is_sorted(arr));//For testing purpose
    return 0;
}