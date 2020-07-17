/**
 * @author sprintyaf
 * @file fibonacci_search.cpp
 * @brief [Fibonacci search
 * algorithm](https://en.wikipedia.org/wiki/Fibonacci_search_technique)
 */

#include <iostream>
#include <vector> // for std::vector class
#include <cassert> // for assert
#include <cstdlib> // for random numbers
#include <algorithm> // for sorting



/**
 * @brief using fibonacci search algorithm finds an index of a given element in a sorted array
 * 
 * @param arr sorted array
 * @param value value that we're looking for
 * @returns if the array contains the value, returns an index of the element. otherwise -1.
 */
int fibonacci_search(const std::vector<int> &arr, int value){
    // initialize last and current members of Fibonacci sequence 
    int last = 0, current = 1;
    int length = arr.size(); // array size
    // next member of Fibonacci sequence which is "last" + "current"
    int next = last + current; 

    // "next" will store the smallest Fibonacci number greater or equal to "length"
    while(next < length){
        last = current;
        current = next;
        next = last + current;
    }

    // "offset" is the end of eliminated range from front
    int offset = -1, index;
    // while loop until there are elements left to consider.
    // when "next" becomes 1, last is equal to 0, so search is done,
    // because arr[offset] will already be eliminated
    while(next > 1){
        // check if "last" is valid location
        index = std::min(offset + last, length-1);
        // if value is greater than the value at "index", eliminate the subarray from offset to index
        if(arr[index] < value){
            next = current;
            current = last;
            last = next - current;
            offset = index;
        // if value is less than the value at "index", eliminate the subarray after index+1
        } else if(arr[index] > value){
            next = last;
            current = current - last;
            last = next - current;
        // element is found
        } else {
            return index;
        }
    }
    // comparing the last element
    if(current && !arr.empty() && arr[offset+1] == value){
        return offset+1;
    }
    // value was not found, return -1
    return -1;
}

/**
 * @brief random tests for checking performance when an array doesn't contain an element
*/
bool no_occurence_tests(){
    bool passed = true;
    int rand_num, rand_value, index, num_tests = 1000;
    std::vector<int> arr;
    while(num_tests--){
        arr.clear();
        for(int i = 0; i < 100; i++){
            rand_num = std::rand() % 1000;
            arr.push_back(rand_num);
        }
        rand_value = std::rand() % 1000;
        while(std::find(arr.begin(), arr.end(), rand_value) != arr.end()){
            std::remove(arr.begin(), arr.end(), rand_value);
        }
        sort(arr.begin(), arr.end());
        index = fibonacci_search(arr, rand_value);
        passed = passed && (index == -1);
    }
    return passed;
}

/**
 * @brief random tests which cover cases when we have one, multiple or zero occurences of the value we're looking for
*/
bool random_tests(){
    bool passed = true;
    int rand_num, rand_value, index, real_value, num_tests = 10000;
    std::vector<int> arr;
    while(num_tests--){
        arr.clear();
        for(int i = 0; i < 100; i++){
            rand_num = std::rand() % 1000;
            arr.push_back(rand_num);
        }
        rand_value = std::rand() % 1000;
        std::sort(arr.begin(), arr.end());
        index = fibonacci_search(arr, rand_value);
        if(index != -1){
            real_value = arr[index];
            passed = passed && (real_value == rand_value);
        } else {
            passed = passed && (std::find(arr.begin(), arr.end(), rand_value) == arr.end());
        }
    }
    return passed;
}

/**
 * Main Function
 * testing the algorithm
 */
int main() {
    assert(no_occurence_tests());
    assert(random_tests());
    return 0;
}
