/**
 * Copyright 2020 @author Albirair
 * @file
 *
 * A generic implementation of non-recursive merge sort.
 */
#include <cstddef>  // for size_t
#include <utility>  // for std::move & std::remove_reference_t
template<class Iterator>
void merge(Iterator, Iterator, const Iterator, char[]);
/// bottom-up merge sort which sorts elements in a non-decreasing order
/**
 * sorts elements non-recursively by breaking them into small segments, merging
 * adjacent segments into larger sorted segments, then increasing the sizes of
 * segments by factors of 2 and repeating the same process.
 * best-case = worst-case = O(n log(n))
 * @param first points to the first element
 * @param last points to 1-step past the last element
 * @param n the number of elements
*/
template<class Iterator>
void non_recursive_merge_sort(const Iterator first, const Iterator last,
                              const size_t n) {
    // create a buffer large enough to store all elements
    // dynamically allocated to comply with cpplint
    char * buffer = new char[n * sizeof(*first)];
    // buffer size can be optimized to largest power of 2 less than n elements
    // divide the container into equally-sized segments whose length start at 1
    // and keeps increasing by factors of 2
    for (size_t length(1); length < n; length <<= 1) {
        // merge adjacent segments whose number is n / (length * 2)
        Iterator left(first);
        for (size_t counter(n / (length << 1)); counter; --counter) {
            Iterator right(left + length), end(right + length);
            merge(left, right, end, buffer);
            left = end;
        }
        // if the number of remaining elements (n * 2 % length) is longer
        // than a segment, merge the remaining elements
        if ((n & ((length << 1) - 1)) > length)
            merge(left, left + length, last, buffer);
    }
    delete[] buffer;
}
/// merges 2 sorted adjacent segments into a larger sorted segment
/**
 * best-case = worst-case = O(n)
 * @param l points to the left part
 * @param r points to the right part, end of left part
 * @param e points to end of right part
 * @param b points at the buffer
*/
template<class Iterator>
void merge(Iterator l, Iterator r, const Iterator e, char b[]) {
    // create 2 pointers to point at the buffer
    auto p(reinterpret_cast<std::remove_reference_t<decltype(*l)>*>(b)), c(p);
    // move the left part of the segment
    for (Iterator t(l); r != t; ++t)
        *p++ = std::move(*t);
    // while neither the buffer nor the right part has been exhausted
    // move the smallest element of the two back to the container
    while (e != r && c != p)
        *l++ = std::move(*r < *c ? *r++ : *c++);
    // notice only one of the two following loops will be executed
    // while the right part hasn't bee exhausted, move it back
    while (e != r)
        *l++ = std::move(*r++);
    // while the buffer hasn't bee exhausted, move it back
    while (c != p)
        *l++ = std::move(*c++);
}
/// bottom-up merge sort which sorts elements in a non-decreasing order
/**
 * @param first points to the first element
 * @param n the number of elements
*/
template<class Iterator>
void non_recursive_merge_sort(const Iterator first, const size_t n) {
    non_recursive_merge_sort(first, first + n, n);
}
/// bottom-up merge sort which sorts elements in a non-decreasing order
/**
 * @param first points to the first element
 * @param last points to 1-step past the last element
*/
template<class Iterator>
void non_recursive_merge_sort(const Iterator first, const Iterator last) {
    non_recursive_merge_sort(first, last, last - first);
}
/**
 * @mainpage A demonstration of auto-generated documentation using Doxygen.
 * Currently, it only creates output for non_recursive_merge_sort.cpp, but if
 * it has proven its efficacy it can be expanded to other files.
 * The configuration file is named doxy.txt and has been auto-generated too.
*/
// the remaining of this file is only for testing. It can erased to to convert
// it into a header file for later re-use.
#include <iostream>
int main(int argc, char ** argv) {
    int size;
    std::cout << "Enter the number of elements : ";
    std::cin >> size;
    int * arr = new int[size];
    for (int i = 0; i < size; ++i) {
        std::cout << "arr[" << i << "] = ";
        std::cin >> arr[i];
    }
    non_recursive_merge_sort(arr, size);
    std::cout << "Sorted array\n";
    for (int i = 0; i < size; ++i)
        std::cout << "arr[" << i << "] = " << arr[i] << '\n';
    delete[] arr;
    return 0;
}
