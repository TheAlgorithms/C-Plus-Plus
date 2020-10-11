/*
Best Time to Buy and Sell Stock - Greedy
Problem Statement: 

Given an array for which the ith element is the price of a given stock on day i.
If you were only permitted to complete at most one transaction 
(i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.
Note that you cannot sell a stock before you buy one.

Solution:
we find the maximum price for which the stock can be sold after i-th day in vector b. The i-th element of b
is the maximum stock price from (n-1)th day to ith day. Then for each day find the profit by subtracing 
the cost of buying at ith day, final answer will be the maximum of these profits.
*/


#include <iostream>
#include <vector> 
#include <cassert>

/**
 * @brief This function implements the above algorithm
 * @prices array of numbers containing the price of stock on ith day
 * @returns integer denoting the maximum profit
 */  
 
 
int maxProfit(const std::vector<int> &prices) {
 
    int ans = 0, n = prices.size();

    // no profit if the number of days is zero
    if(n == 0) {
       return 0;
    }

    std::vector<int>b(n);

    // ith value of vector b will have the highest value of stock price till that day
    b[n - 1] = prices[n - 1];
    for(int i = n - 2; i >= 0; i--) {
       b[i] = std::max(b[i + 1], prices[i]);
    }

    // maximum profit will maximum of all the profits by buying stock at prices[i] price and selling it with b[i] price
    for(int i = 0; i < n; i++) {
       ans = std::max(ans, b[i] - prices[i]);
    }

    return ans;
}

/**
 * @brief Function to test above algorithm
 * @returns void
 */
 
static void test() {
 
  // Test 1
  {
   std::vector<int> num1 = {7, 1, 5, 3, 6, 4};

   int output = maxProfit(num1);
   assert(output == 5);
   std::cout << "Input: ";
   for(auto i: num1) {
     std::cout << i << " ";
   }
   std::cout << "Output: 5" << std::endl;
  }
  
  // Test 2
  {
   std::vector<int> num1 = {7,6,4,3,1};

   int output = maxProfit(num1);
   assert(output == 0);
   std::cout << "Input: ";
   for(auto i: num1) {
    std::cout << i << " ";
   }
   std::cout << "Output: 0" << std::endl;
  }
}

/**
 * @brief Main function
 * @returns 0 on exit
 */

int main() {
 
   test();
   return 0;
}
