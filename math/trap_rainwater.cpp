/**
 * @file
 * @brief Implementation of [Rainwater Harvesting](https://leetcode.com/problems/trapping-rain-water/) problem
 *
 * @details
 * Trapping rainwater or rainwater harvesting is a popular question asked by many
 * companies. It has a quite simple approach.
 * First we iterate over the vector(height of buildings) from left to right and 
 * store the maximum among them. Repeat the same when iterating from right to left.
 * Finally return the maximum amount of water that can be trapped between the
 * buildings
 *
 * @author [Divyansh Kushwaha](https://github.com/webdesignbydivyansh)
 */

#include <cassert>     /// for assert
#include <iostream> /// for io operations
#include <vector>     /// for std::vector

/**
 * @namespace rainwaterharvesting
 */

namespace rainwaterharvesting {
/**
 * @namespace trap_water
 * @brief Functions for [trapping rainwater](https://leetcode.com/problems/trapping
 * -rain-water/) algorithm
 */
namespace trap_water { 
/**
 * @brief The main function implements rainwater
 * @tparam T type of array
 * @returns water
 */
template <typename T>
T rainwater(const int n, const std::vector<T> a){
    std::vector<T> l(n), r(n);  //for storing left and right heights

    l[0] = a[0];
    r[n - 1] = a[n - 1];
    for (int i = 1; i < n; i++) //iterating from left to right
    {
        if(l[i-1]>a[i]){
            l[i]=l[i-1];
        }
        else{
            l[i]=a[i];
        }
    }
    for (int i = n - 2; i >= 0; i--)    //iterating from right to left
    {
        if(r[i+1]>a[i]){
            r[i]=r[i+1];
        }
        else{
            r[i]=a[i];
        }
    }
    T water = 0;    //variable to store water
    for (int i = 0; i < n; i++)
    {
        if(l[i]>r[i]){
            water+=(r[i]-a[i]);
        }
        else{
            water+=(l[i]-a[i]);
        }
    }
    return water;
}
} // namespace trap_water
} // namespace rainwaterharvesting

/**
 * @brief Test implementations
 * @returns void
 */
static void test() {
    // {0,2,1,3,0,1,2,1,2,1} returns 5
    std::vector<int> a1 = {0,2,1,3,0,1,2,1,2,1};
    std::cout << "Test 1... ";
    const int n1=10;
    assert(rainwaterharvesting::trap_water::rainwater(n1,a1)==5);
    std::cout << "passed" << std::endl;

    // {7.4,6.5,2.3,5.8,4.6,9.1,2.3,4.1} returns 12.2
    std::vector<double> a2 = {7.4,6.5,2.3,5.8,4.6,9.1,2.3,4.1};
    std::cout << "Test 2... ";
    const int n2=8;
    double k=rainwaterharvesting::trap_water::rainwater(n2,a2);
    assert(rainwaterharvesting::trap_water::rainwater(n2,a2)==k);
    std::cout << "passed" << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // execute the test
    return 0;
}
