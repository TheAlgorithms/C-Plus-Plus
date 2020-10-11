/*House Robber - Dynamic Programming

Problem Statement: 
A robber is planning to rob houses along a street. Each house has a 
certain  amount  of money stashed, the only constraint stopping you 
from  robbing  each of them  is that  adjacent houses have security 
system connected and it will automatically contact the police if two
adjacent houses were broken into on the same night.

Task: 
Determine the maximum amount of money you can rob tonight without alerting the police

Solution: 
For every house we have two options either to rob it, if we do so we have to
move to next to next huse as we cannot rob two adjacent houses. If we don't rob this
house then we can move to the next one. The maximum of above two cases will be the maximum profit.
We store our preiously calculated results in a table (dpTable) if we found that we have already
calculated the ans then we simply return it.
*/


#include <iostream>
#include <vector> 
#include <cassert>

/**
 * @brief This function implements the above algorithm
 * @money array of numbers containing the money in the ith house
 * @dpTable is the memoization table, having the previously calculated result
 * @returns integer denoting the maximum money theif can rob
 */  
 
 
int houseRobber(std::vector<int> &dpTable, const std::vector<int> &money, int pos=0)
{
    int n = money.size();
    if(pos >= n)
    {
        return 0;  
    }		

    if(dpTable[pos] != -1)
    {
        return dpTable[pos];   // if the result for this position has been already calculated
    }

    // rob the current house & move to next to next one or didn't rob the current house move to next one
    return dpTable[pos] = std::max(money[pos] + houseRobber(dpTable, money, pos + 2), houseRobber(dpTable, money, pos + 1));              				 

}

/**
 * @brief Function to test above algorithm
 * @returns void
 */

static void test()
{
  // Test 1
  {
   std::vector<int> num1 = {1, 2, 3, 1};
   int n = num1.size();
   std::vector<int>dpTable(n, -1);

   int output = houseRobber(dpTable, num1);
   assert(output == 4);
   std::cout << "Input: ";
   for(auto i: num1)
   {
     std::cout << i << " ";
   }
   std::cout << "Output: 4" << std::endl;
  }

  // Test 2
  {
   std::vector<int> num1 = {2, 7, 9, 3, 1};
   int n = num1.size();
   std::vector<int>dpTable(n, -1);

   int output = houseRobber(dpTable, num1);
   assert(output == 12);
   std::cout << "Input: ";
   for(auto i: num1)
   {
    std::cout << i << " ";
   }
   std::cout << "Output: 12" << std::endl;
  }
}

/**
 * @brief Main function
 * @returns 0 on exit
 */

int main() 
{
	test();
    return 0;
}
