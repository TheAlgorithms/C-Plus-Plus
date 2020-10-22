/**
 * @file
 * @brief Implementation of [Merging k sorted arrays](https://leetcode.com/problems/merge-k-sorted-lists/) merging k sorted arrays
 *
 * @details
 * Merging k sorted arrays in a single array can be easily implemented by using heap
 * data structure or priority queue(minimum priority queue).
 * First push back all elements of all arrays in priority queue
 * Next check each element of array with other element position by position and
 * finally check if the current array has exhausted or not. 
 *
 * @author [Divyansh Kushwaha](https://github.com/webdesignbydivyansh)
 */

#include <algorithm> /// for std::is_sorted
#include <cassert>     /// for assert
#include <iostream> /// for io operations
#include <vector>    /// for std::vector 
#include<queue>     ///for priority queue
using namespace std;


/**
 * @namespace sorting
 * @brief Sorting algorithms
 */

namespace sorting {
/**
 * @namespace k_sorted
 * @brief Functions for [merge k sorted arrays](https://leetcode.com/problems/merge-k-sorted-lists/) algorithm
 */
namespace k_sorted { 
/**
 * @brief The main function implements mergeksorted
 * @tparam T type of array
 * @param v array to be sorted
 * @returns r
 */
template <typename T>
std::vector<T> mergeksorted(const std::vector<vector<T>> v) {
    std::vector<T> r;
    typedef pair <T,pair<T,T>>node;

    priority_queue<node,vector<node>,greater<node> > p;
	for(int i=0;i<v.size();i++)
	//Pushing all elements of array int priority queue
	p.push({v[i][0],{i,0}});
	while(!p.empty())   //check if queue is empty or not
	{
		node c=p.top();
		p.pop();
		int e=c.first;  
		int x=c.second.first;
		int y=c.second.second;
		r.push_back(e);
		//check if array end is reached or not
		if(y+1<v[x].size())
		p.push({v[x][y+1],{x,y+1}});
	}
	return r;
}
} // namespace k_sorted
} // namespace sorting

/**
 * @brief Test implementations
 * @returns void
 */
static void test() {
    // {{2,6,12,15},{1,3,14,20},{3,5,8,10}} returns {1 2 3 3 5 6 8 10 12 14 15 20}
    std::vector<vector<int>> array1 {{2,6,12,15},{1,3,14,20},{3,5,8,10}};
    std::cout << "Test 1... ";
    std::vector<int> arr1  = sorting::k_sorted::mergeksorted(array1);
    assert(std::is_sorted(std::begin(arr1), std::end(arr1)));
    std::cout << "passed" << std::endl;

    // {{-7.4, -6.5,-2.3, 0},{-8.5,-6.9,-2.4,-1.2,}} returns {-8.5 -7.4 -6.9 -6.5 -2.4 -2.3 -1.2 0}
    std::vector<vector<double>> array2 {{-7.4, -6.5,-2.3, 0},{-8.5,-6.9,-2.4,-1.2,}};
    std::cout << "Test 2... ";
    std::vector<double> arr2 = sorting::k_sorted::mergeksorted(array2);
    assert(std::is_sorted(std::begin(arr2), std::end(arr2)));
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
