/**
 * Copyright 2020 @author Albirair
 * @file
 *
 * A generic implementation of binary_search.
 */
#ifndef SEARCH_BINARY_SEARCH_H_
#define SEARCH_BINARY_SEARCH_H_
#include <utility>  // for pair
#include <cstddef>  // for size_t
/// searching a value in a sorted container in logarithmic time
/**
 * A decrease and conquer algorithm by a constant factor of 2. It compares the
 * value searched for with the element in the middle, if they are equal it
 * terminates successfully. If the value is greater than the middle element
 * we repeat searching in the right half, otherwise we do the same in the left
 * half.
 * @param first points to the first element
 * @param n the number of elements
 * @param value the target for searching
 * @return On success, it returns an std::pair whose values are @c true and an
 * iterator to the element of @c value . On Failure, it returns @ false and
 * an iterator to the closest value.
*/
template<class Iterator>
std::pair<bool, Iterator> binary_search(Iterator first, std::size_t n,
                                        const decltype(*first) value) {
    // while the container has elements
    while (n) {
        // check the middle element
        std::size_t mi = n >> 1;
        Iterator m = first + mi;
        // if the value is found return
        if (value == *m)
            return std::pair<bool, Iterator>(true, m);
        // if value is in the right half, focus on the right half
        if (value > *m) {
            first = m + 1;
            n -= mi + 1;
        } else {
            n = mi;
        }
    }
    return std::pair<bool, Iterator>(false, first);
}
/// searching a value in a sorted container in logarithmic time
/**
 * A decrease and conquer algorithm by a constant factor of 2. It compares the
 * value searched for with the element in the middle, if they are equal it
 * terminates successfully. If the value is greater than the middle element
 * we repeat searching in the right half, otherwise we do the same in the left
 * half.
 * @param first points to the first element
 * @param last points to 1-step past the last element
 * @param value the target for searching
 * @return On success, it returns an std::pair whose values are @c true and an
 * iterator to the element of @c value . On Failure, it returns @ false and
 * an iterator to the closest value.
*/
template<class Iterator>
std::pair<bool, Iterator> binary_search(Iterator first, Iterator last,
                                        const decltype(*first) value) {
    return binary_search(first, last - first, value);
}
#endif  // SEARCH_BINARY_SEARCH_H_
