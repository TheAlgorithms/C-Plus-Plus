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
    std::cout<<arr[0]<<" "<<arr[1]<<std::endl;

    //check size of vector
    std::cout<<arr.size()<<std::endl;

    //sort a vector
    sort(arr.begin(),arr.end());

    //iterating over vector, way #1:
    for(int i=0;i<arr.size();i++) {
        std::cout<<arr[i]<<" ";
    }
    std::cout<<std::endl;

    //iterating over vector, way #2:
    for(int item : arr) {
        std::cout<<item<<" ";
    }
    std::cout<<std::endl;
}
