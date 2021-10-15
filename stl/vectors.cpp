#include <iostream>
#include <vector>

/**
 * This code is a basic implementation for use of vector STL in C++.
 * The below code includes:
 * (a) Creation of vectors
 * (b) Traversing vectors
 * (c) Sorting in vecotrs
 */
int main() 
{
    std::vector<int> arr;

    //insert in a vector
    arr.push_back(1);
    arr.push_back(2);

    //access vector elements
    assert(1==arr[0]);
    assert(2==arr[1]);

    //check size of vector
    assert(2==arr.size());

    //sort a vector
    sort(arr.begin(),arr.end());

    //iterating over vector
    for(int i : arr) {
        std::cout<<i<<" ";
    }
}
