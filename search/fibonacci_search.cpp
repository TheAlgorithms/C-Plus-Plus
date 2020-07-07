/**
 * Copyright 2020 @author sprintyaf
 * @file
 * @brief [Fibonacci search
 * algorithm](https://en.wikipedia.org/wiki/Fibonacci_search_technique)
 */

#include <iostream>
#include <vector> // for std::vector class
#include <cassert> // for assert



/**
 * Returns minimum of the two numbers
 */
int min(int first, int second){
    if(first < second){
        return first;
    } else {
        return second;
    }
}

/**
 * Input: a sorted array, a value we're looking for and size of the array
 * Output: if the array contains the value, returns its index
 *         else returns -1
 */
int fibonacci_search(int *arr, int value, int length){
    int last = 0, current = 1, offset = -1, index;
    int next = last + current;

    while(next < length){
        last = current;
        current = next;
        next = last + current;
    }

    while(next > 1){
        index = min(offset + last, length-1);
        if(arr[index] < value){
            next = current;
            current = last;
            last = next - current;
            offset = index;
        } else if(arr[index] > value){
            next = last;
            current = current - last;
            last = next - current;
        } else {
            return index;
        }
    }
    if(current && (length > 0) && arr[offset+1] == value){
        return offset+1;
    }
    return -1;
}

/**
 * Tests where given value occurs only once
 */
bool one_occurence_test(){
    // declarations
    int value, index, length;
    bool passed = true;
    // last element
    length = 3;
    int arr1[length] = {1, 2, 3};
    value = 3;
    index = fibonacci_search(arr1, value, length);
    passed = passed && (index == 2);
    // first element
    value = 1;
    index = fibonacci_search(arr1, value, length);
    passed = passed && (index == 0);
    // somewhere in the middle element
    length = 4;
    int arr2[length] = {1, 3, 5, 7};
    value = 3;
    index = fibonacci_search(arr2, value, length);
    passed = passed && (index == 1);
    // arr size is 1
    length = 1;
    int arr3[length] = {10};
    value = 10;
    index = fibonacci_search(arr3, value, length);
    passed = passed && (index == 0);

    return passed;
}

/**
 * Tests where given value occurs more than once
 */
bool many_occurence_test(){
    // declarations
    int value, index, length;
    bool passed = true;
    // last element
    length = 4;
    int arr1[length] = {1, 1, 10, 10};
    value = 10;
    index = fibonacci_search(arr1, value, length);
    passed = passed && (index == 2 || index == 3);
    // first element
    value = 1;
    index = fibonacci_search(arr1, value, length);
    passed = passed && (index == 0 || index == 1);
    // somewhere in the middle element
    length = 4;
    int arr2[length] = {1, 3, 3, 7};
    value = 3;
    index = fibonacci_search(arr2, value, length);
    passed = passed && (index == 1 || index == 2);
    // all elements are the same
    length = 3;
    int arr3[length] = {10, 10, 10};
    value = 10;
    index = fibonacci_search(arr3, value, length);
    passed = passed && (index >= 0 && index <= 2);

    return passed;
}

/**
 * Tests where the array doesn't contain given value
 */
bool no_occurence_test(){
    // declarations
    int value, index, length;
    bool passed = true;
    // many elements
    length = 4;
    int arr1[length] = {1, 2, 4, 5};
    value = 3;
    index = fibonacci_search(arr1, value, length);
    passed = passed && (index == -1);
    // one element
    length = 1;
    int arr2[length] = {1};
    value = 2;
    index = fibonacci_search(arr2, value, length);
    passed = passed && (index == -1);
    // empty array
    length = 0;
    int arr3[length];
    value = 10;
    index = fibonacci_search(arr3, value, length);
    passed = passed && (index == -1);

    return passed;
}


/**
 * Main Function
 * testing the algorithm
 */
int main() {
    assert(one_occurence_test());
    assert(many_occurence_test());
    assert(no_occurence_test());
    return 0;
}
