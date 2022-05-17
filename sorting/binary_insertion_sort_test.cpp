#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include "binary_insertion_sort.h"
static void test() {
    /* 1st test:
       [5] returns [5] */
    std::vector<int64_t> arr1({5});
    sorting::insertionSort_binsrch(arr1);
    assert(std::is_sorted(std::begin(arr1), std::end(arr1)));
    std::cout << "True" << std::endl;

    /* 2nd test:
       [1,2] returns [1,2] */
    std::vector<int64_t> arr2({1,2});
    sorting::insertionSort_binsrch(arr2);
    assert(std::is_sorted(std::begin(arr2), std::end(arr2)));
    std::cout << "True" << std::endl;

    /* 3rd test:
       [1,3,2,4] returns [1,2,3,4] */
    std::vector<float> arr3({1,3,2,4});
    sorting::insertionSort_binsrch(arr3);
    assert(std::is_sorted(std::begin(arr3), std::end(arr3)));
    std::cout << "True" << std::endl;

    /* 4th test:
       [5,4,3,2,1] returns [1,2,3,4,5] */
    std::vector<float> arr4({5,4,3,2,1});
    sorting::insertionSort_binsrch(arr4);
    assert(std::is_sorted(std::begin(arr4), std::end(arr4)));
    std::cout << "True" << std::endl;

    /* 5th test:
       [-1,-2,1,2] returns [-2,-1,1,2] */
    std::vector<float> arr5({12.8, -3.7, -20.7, -7.1, 2.2});
    sorting::insertionSort_binsrch(arr5);
    assert(std::is_sorted(std::begin(arr5), std::end(arr5)));
    std::cout << "True" << std::endl;

    /* 6th test:
       [0.2,0.1,0.3] returns [0.1,0.2,0.3] */
    std::vector<float> arr6({0.2,0.1,0.3});
    sorting::insertionSort_binsrch(arr6);
    assert(std::is_sorted(std::begin(arr6), std::end(arr6)));
    std::cout << "True" << std::endl;

    /* 7th test:
       [z,x,c,v] returns 0 */
    std::vector<float> arr7({z,x,c,v});
    sorting::insertionSort_binsrch(arr7);
    assert(std::is_sorted(std::begin(arr7), std::end(arr7)));
    std::cout << "True" << std::endl;
}
