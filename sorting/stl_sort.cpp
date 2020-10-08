/**
 * @file
 * @brief stl sort algorithm
 *
 * The working principle of the Bubble sort algorithm:
        std::sort() is a generic function in C++ Standard Library, for doing comparison sorting.
* Syntax:
        sort(startaddress, endaddress, comparator)
        where:
        startaddress: the address of the first element of the array
        endaddress: the address of the last element of the array
        comparator: the comparison to be done with the array. 
                    This argument is optional.
*Algorithm used by sort():
     The algorithm used by sort() is IntroSort. Introsort being a hybrid sorting algorithm uses three sorting algorithm to minimise the running time, Quicksort, Heapsort and Insertion Sort. Simply putting, it is the best sorting algorithm around. It is a hybrid sorting algorithm, which means that it uses more than one sorting algorithms as a routine.

*Time Complexity:
        Best Case – O(N log N)
        Average Case- O(N log N)
        Worse Case- O(N log N)
        where, N = number of elements to be sorted.

* Knowing all sorting techniques are important.And knowing inbulit sort is important too for solving complex programs.
* Though inbulit sort which is included in  ALGORITHMS  header file sort in  increasing order.You can change the order by just
* passing compare function as a parameter in sort function.
* Inbulit sort function take 2 parameters:sort[a,a+n) =>where,a i.e first value is included and end point a+n is not included.
*Inside comparator function it's written as:if(a[j]<a[j+1]){Swap} and we are just overwriting this function saying =
* if(comp(a[j],a[j+1])) to compare it.
 **/

#include<iostream>
#include<algorithm>
#include<vector>


bool myCompare(int a,int b){
    //for changing  order in decreasing order.
    //if you want it to follow increasing order change it to a<b;
    return a>b;
}
//Main Function
int main(){

       /// For user insteraction
    size_t n;
    std::cout << "Enter the length of your array (0 to exit): ";
    std::cin >> n;
    if (n == 0) {
        return 0;
    }

    int *arr = new int[n];
    std::cout << "Enter any " << n << " Numbers for Unsorted Array : ";
       for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    // sort function
    sort(a,a+n,myCompare);
    //final sorted array
    for(int i=0;i<n;i++){
     std::cout<<a[i]<<" ";
    }
    std::cout << std::endl;
    delete[] arr;
    return 0;
}