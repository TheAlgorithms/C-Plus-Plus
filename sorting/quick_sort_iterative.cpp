/**
 * @file
 * @brief Quick Sort without recursion. This method uses the stack instead.
 * Both recursive and iterative implementations have O(n log n) best case
 * and O(n^2) worst case.
 * @details
 * https://stackoverflow.com/questions/12553238/quicksort-iterative-or-recursive
 * https://en.wikipedia.org/wiki/Quicksort
 * https://www.geeksforgeeks.org/iterative-quick-sort/
 * @author [Sebe324](https://github.com/sebe324)
 */

#include <iostream> /// for std::cout
#include <vector> /// for std::vector
#include <stack> /// for std::stack
#include <algorithm> /// for std::is_sorted
#include <cassert> /// for assert


/**
 * @namespace sorting
 * @brief Sorting algorithms
 */
namespace sorting {
/**
 * @brief The partition function sorts the array from
 * start to end and uses the last element as the pivot.
 * @param arr the array to be sorted
 * @param start starting index
 * @param end ending index
 * @return int next index of the pivot
 */
int partition(std::vector<int> &arr, int start, int end)
{
    int pivot = arr[end];
    int index = start - 1;

    for (int j = start; j < end; j++) {
        if (arr[j] <= pivot) {
            std::swap(arr[++index], arr[j]);
        }
    }

    std::swap(arr[index + 1], arr[end]);
    return index + 1;
}

/**
 * @brief The main sorting function
 * @details The iterative quick sort uses
 * the stack instead of recursion for saving
 * and restoring the environment between calls.
 * It does not need the end and start params, because
 * it is not recursive.
 * @param arr array to be sorted
 * @return void
 */
void iterativeQuickSort(std::vector<int> &arr)
{
    std::stack<int> stack;
    int start = 0;
    int end = arr.size()-1;
    stack.push(start);
    stack.push(end);

    while(!stack.empty())
    {
        end = stack.top();
        stack.pop();
        start = stack.top();
        stack.pop();

        int pivotIndex = partition(arr,start,end);

        if(pivotIndex -1 > start)
        {
            stack.push(start);
            stack.push(pivotIndex-1);
        }

        if(pivotIndex+1<end)
        {
            stack.push(pivotIndex+1);
            stack.push(end);
        }
    }
}

} // namespace sorting
/**
 * @brief Self-test implementations
 * @returns void
 */
void tests()
{
    //TEST 1 - Positive numbers
    std::vector<int> case1={100,534,1000000,553,10,61,2000,238,2756,9,12,56,30};
    std::cout<<"TEST 1\n";
    std::cout<<"Before: \n";
    for(auto x : case1) std::cout<<x<<",";
    std::cout<<"\n";
    sorting::iterativeQuickSort(case1);
    assert(std::is_sorted(std::begin(case1),std::end(case1)));
    std::cout<<"Test 1 succesful!\n";
    std::cout<<"After: \n";
    for(auto x : case1) std::cout<<x<<",";
    std::cout<<"\n";

    //TEST 2 - Negative numbers
    std::vector<int> case2={-10,-2,-5,-2,-3746,-785,-123, -452, -32456};
    std::cout<<"TEST 2\n";
    std::cout<<"Before: \n";
    for(auto x : case2) std::cout<<x<<",";
    std::cout<<"\n";
    sorting::iterativeQuickSort(case2);
    assert(std::is_sorted(std::begin(case2),std::end(case2)));
    std::cout<<"Test 2 succesful!\n";
    std::cout<<"After: \n";
    for(auto x : case2) std::cout<<x<<",";
    std::cout<<"\n";
}


/**
 * @brief Main function
 * @returns 0 on exit
 */
int main()
{
    tests(); // run self test implementation
    return 0;
}
