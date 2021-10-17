/**
 * @file
 * @brief Implementation of an algorithm to solve the [jumping game]((https://leetcode.com/problems/jump-game/)) problem
 * @details
 * **Problem statement:** Given an array of non-negative integers, you are initially positioned at the first index of the array. Each element in the array represents your maximum jump length at that position. Determine if you are able to reach the last index.
 * This solution takes in input as a vector and output as a boolean to check if you can reach the last position.
 * We name the indices good and bad based on whether we can reach the destination if we start at that position.
 * We initialize the last index as lastPos.
 * Here, we start from the end of the array and check if we can ever reach the first index.
 * We check if the sum of the index and the maximum jump count given is greater than or equal to the lastPos.
 * If yes, then that is the last position you can reach starting from the back.
 * After the end of the loop, if we reach the lastPos as 0, then the destination can be reached from the start position.
 * @author [Rakshaa Viswanathan](https://github.com/rakshaa2000)
*/

#include <vector>
#include <iostream>
#include <cassert>


 /**
 * @brief This function implements the above algorithm
 * @param array of numbers containing the maximum jump (in steps) from that index
 * @returns bool value whether final index can be reached or not
 */  
bool canJump(const std::vector<int> &nums) {
    auto lastPos = nums.size() - 1;
    for (auto i = nums.size() - 1; i >= 0; i--) {
        if (i + nums[i] >= lastPos) {
            lastPos = i;
        }
    }
    return lastPos == 0;
}


/**
 * @brief Function to test above algorithm
 * @returns void
 */
static void test(){
  // Test 1
  std::vector<int> num1={4,3,1,0,5};
  assert(canJump(num1)==true);
  std::cout<<"Input: ";
  for(auto i: num1){
    std::cout<<i<<" ";
  }
  std::cout<<"Output: true"<<std::endl;
  // Test 2
  std::vector<int> num2={3,2,1,0,4};
  assert(canJump(num2)==false);
  std::cout<<"Input: ";
  for(auto i: num2){
    std::cout<<i<<" ";
  }
  std::cout<<"Output: false"<<std::endl;
}


/**
 * @brief Main function
 * @returns 0 on exit
 */
int main(){
    test();
    return 0;
}
