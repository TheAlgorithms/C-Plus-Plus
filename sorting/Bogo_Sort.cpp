/**
 * @file
 * @brief Bogo sort algorithm
 *
 * Implementation Details -
 *      In computer science, bogosort (also known as permutation sort, stupid sort, slowsort, 
 *      shotgun sort, random sort, monkey sort, bobosort or shuffle sort) is a highly inefficient 
 *      sorting algorithm based on the generate and test paradigm.Two versions of this algorithm 
 *      exist: a deterministic version that enumerates all permutations until it hits a sorted one,
 *      and a randomized version that randomly permutes its input.Randomized version is implemented here. 
 *
 * Algorithm -      
 *      
 *      Shuffle the array untill array is sorted.
 *
 */
#include <iostream>
#include <array>
#include <cassert>
//This function checks if array is sorted
template<typename T, size_t N>
bool is_sorted(const std::array <T, N> &arr)
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
template<typename T, size_t N>
void show_array(const std::array <T, N> &arr)
{
    for(int x : arr)
    {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}
//This function shuffles the array randomly
template<typename T, size_t N>
std::array <T, N> shuffle(std::array <T, N> arr)
{
    for(int i = 0; i < arr.size(); i ++)
    {
        //Swaps i'th  index with random index (less than array size)
        std::swap(arr[i], arr[rand() % arr.size()]);
    }
    return arr;
}
//Randomized bogo sort
template<typename T, size_t N>
std::array <T, N> randomized_bogosort(std::array <T, N> arr)
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
    std::array <int, 5> arr = {3, 7, 10, 4, 1}; // Defining array which we want to sort
    arr = randomized_bogosort(arr); //Callling bogo sort on it
    std::cout << "Sorted Array (Randomized Bogosort) : " ;
    show_array(arr); //Printing sorted array
    assert(is_sorted(arr));//For testing purpose
    return 0;
}