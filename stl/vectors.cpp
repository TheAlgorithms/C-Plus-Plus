#include <iostream>
#include <vector>
using namespace std;

/**
 * This code is a basic implementation for use of vector STL in C++.
 * The below code includes:
 * (a) Creation of vectors
 * (b) Traversing vectors
 * (c) Sorting in vecotrs
 */
int main() 
{
    vector<int> arr;

    //insert in a vector
    arr.push_back(1);
    arr.push_back(2);

    //access vector elements
    cout<<arr[0]<<" "<<arr[1]<<endl;

    //check size of vector
    cout<<arr.size()<<endl;

    //sort a vector
    sort(arr.begin(),arr.end());

    //iterating over vector, way #1:
    for(int i=0;i<arr.size();i++) {
        cout<<arr[i]<<" ";
    }
    cout<<endl;

    //iterating over vector, way #2:
    for(auto it=arr.begin();it!=arr.end();it++) {
        cout<<*it<<" ";
    }
    cout<<endl;
}
