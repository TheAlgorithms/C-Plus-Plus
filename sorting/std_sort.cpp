/**
 * \file
 * \brief [std::sort](https://en.cppreference.com/w/cpp/algorithm/sort)
 * implementation
 *
 * \author [Gopal Dahale](https://github.com/Gopal-Dahale)
 *
 * \details
 * Sorts the elements in the range [first, last) in non-descending order. The
 * order of equal elements is not guaranteed to be preserved.
 *
 * Time Complexity - \f$O(n \log(n))\f$  where N = std::distance(first, last)
 * comparisons.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

/**
 *
 * Overloading operator<<() to print the pairs 
 * @param os ostream object
 * @param p pair 
 */

template <typename T, typename U>
std::ostream &operator<<(std::ostream &os, std::pair<T, U> &p)
{
    std::cout << "{" << p.first << ", " << p.second << "}";
    return os;
}

/**
 *
 * Utility function to print the vector after
 * sorting.
 *
 * @param v vector to be printed
 *
 */

template <typename T>
void print_vector(std::vector<T> &v)
{
    std::for_each(v.begin(), v.end(), [&](T ele) { std::cout << ele << " "; });
    std::cout << "\n";
}

/**
 * Comparator function returns a boolean value describing which element should
 * be placed first in the sorted vector in ascending order
 * 
 * Compares with respect to second element of pair
 * 
 * @param x,y elements of vector
 *
 */
template <typename T, typename U>
bool compare_second(std::pair<T, U> &x, std::pair<T, U> &y)
{
    return x.second < y.second;
}
/**
 * 
 * Comparator function returns a boolean value describing which element should
 * be placed first in the sorted vector in ascending order
 * 
 * Compares with respect to first element of pair
 * 
 * @param x,y elements of vector
 *
 */
template <typename T, typename U>
bool compare_first(std::pair<T, U> &x, std::pair<T, U> &y)
{
    return x.first < y.first;
}

int main()
{
    std::vector<int> v1{-10, 78, -1, -6, 7, 4, 94, 5, 99, 0};

    std::sort(v1.begin(), v1.end()); // sorts in ascending order by default
    print_vector(v1);

    std::sort(v1.begin(), v1.end(), std::greater<int>()); // sorts in descending order
    print_vector(v1);

    /**
     * Sorting vector of pairs using std::sort and a comparator function
     */

    std::vector<std::pair<std::string, int>> v2{
        {"Cat", 3}, {"Dog", 2}, {"Mouse", 1}, {"Snake", 4}, {"Rabbit", 8}, {"Tiger", 5}, {"Monkey", 10}};

    std::sort(v2.begin(), v2.end(), compare_second<std::string, int>);
    print_vector(v2);

    std::sort(v2.begin(), v2.end(), compare_first<std::string, int>);
    print_vector(v2);

    return 0;
}
