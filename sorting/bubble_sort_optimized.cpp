#include <iostream>  /// for IO operations
#include <vector>    /// for std::vector
#include <cassert>   /// for assert

namespace sorting {

    /**
     * @brief Sorts the given vector using the bubble sort algorithm.
     * Optimized by reducing the number of passes in average cases.
     * @param nums the vector of integers to be sorted
     * @return reference to the sorted vector
     */
    std::vector<int>& bubble_sort(std::vector<int>& nums) {
        int flag=0;
        int temp;
        for(int i=0; i<nums.size()-1;i++){
            flag=0;
            for(int j=0; j<nums.size()-1-i;j++){
                if(nums[j]>nums[j+1]){
                    temp=nums[j];
                    nums[j]=nums[j+1];
                    nums[j+1]=temp;
                    flag=1;
                }
            }
            if(flag==0){
                break;
            }
        }
        return nums;
    }

    /**
     * @brief Self-test implementations
     * @returns void
     */
    static void tests() {
        std::vector<int> v1 = {2,8,1,6,2,0,3,6};
        std::vector<int> expected1 = {0,1,2,2,3,6,6,8};
        assert(bubble_sort(v1) == expected1);

        std::vector<int> v2 = {5,4,3,2,1};
        std::vector<int> expected2 = {1,2,3,4,5};
        assert(bubble_sort(v2) == expected2);

        std::vector<int> v3 = {1,2,3,4,5};
        std::vector<int> expected3 = {1,2,3,4,5};
        assert(bubble_sort(v3) == expected3);

        std::cout << "All tests have successfully passed!\n";
    }
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    sorting::tests(); // run self-test implementations
    return 0;
}
   
