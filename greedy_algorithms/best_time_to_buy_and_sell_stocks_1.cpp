/*
Best Time to Buy and Sell Stock - Greedy
Problem Statement: 
Given an array for which the ith element is the price of a given stock on day i.
If you were only permitted to complete at most one transaction 
(i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.

Note that you cannot sell a stock before you buy one.
*/


#include <iostream>
#include <vector> 

int maxProfit(std::vector<int> prices, int n) 
{
    int i = 0, ans = 0;
    
	// no profit if the number of days is zero
    if(n == 0)
	  {
       return 0;
	  }
        
    std::vector<int>b(n);
    
	// ith value of vector b will have the highest value of stock price till that day
    b[n - 1] = prices[n - 1];
    for(i = n - 2; i >= 0; i--)
	  {
       b[i] = std::max(b[i + 1], prices[i]);
	  }
    
	// maximum profit will maximum of all the profits by buying stock at prices[i] price and selling it with b[i] price
    for(i = 0; i < n; i++)
	  {
       ans = std::max(ans, b[i] - prices[i]);
	  }
        
    return ans;
}
	
int main() 
{
	int n = 0, val = 0;
	
    std::cout <<"Enter number of days ";
    std::cin >> n;

    std::vector<int>prices(n, 0);
	
    std::cout <<"Enter price of stock in each day: ";
    for (int i = 0; i < n; ++i) 
	  {
        std::cin >> prices[i];
	  }
 
    std::cout << maxProfit(prices, n);
    return 0;
}
