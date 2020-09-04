/**
 * @file
 * \brief Implementation of an algorithm to solve the jumping game problem
 * \details
 * This algorithm is a greedy algorithm.
 * This solution takes in input as a vector and output as a boolean to check if you can reach the last position.
 * @author [Rakshaa Viswanathan](https://github.com/rakshaa2000)
*/
//Jump Game:
/*Given an array of non-negative integers, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length at that position.
Determine if you are able to reach the last index.*/

#include <vector>
#include<iostream>

//Implements the algorithm
/*We name the indices good and bad based on whether we can reach the destination if we start at that position.
 *We initialize the last index as lastPos.
 *Here, we start from the end of the array and check if we can ever reach the first index.
 *We check if the sum of the index and the maximum jump count given is greater than or equal to the lastPos.
 *If yes, then that is the last position you can reach starting from the back.
 *After the end of the loop, if we reach the lastPos as 0, then the destination can be reached from the start position.
*/
bool canJump(std::vector<int> nums) {
    auto lastPos = nums.size() - 1;
    for (auto i = nums.size() - 1; i >= 0; i--) {
        if (i + nums[i] >= lastPos) {
            lastPos = i;
        }
    }
    return lastPos == 0;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main(){
    //Sample test case
    std::vector<int> num={4,3,1,0,5};
    std::cout<<canJump(num);  //Should display true, as when you take one step from position 0, you reach position 1, from which 3 steps lead you to the destination
    return 0;
}
