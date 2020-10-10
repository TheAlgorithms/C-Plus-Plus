/*House Robber - Dynamic Programming
Problem Statement: 
A robber is planning to rob houses along a street. Each house has a 
certain  amount  of money stashed, the only constraint stopping you 
from  robbing  each of them  is that  adjacent houses have security 
system connected and it will automatically contact the police if two
adjacent houses were broken into on the same night.
Task: 
Determine the maximum amount of money you can rob tonight without alerting the police*/


#include <iostream>
#include <vector> 

std::vector<int> money;
int houseRobber(std::vector<int>dpTable, int n, int pos=0)
{
    if(pos >= n)
	{
        return 0;  
	}		
        
    if(dpTable[pos] != -1)
	{
        return dpTable[pos];   // if the result for this position has been already calculated
	}
        
	// rob the current house & move to next to next one or didn't rob the current house move to next one
    return dpTable[pos] = std::max(money[pos] + houseRobber(dpTable, n, pos + 2), houseRobber(dpTable, n, pos + 1));              				 

}
	
int main() 
{
	int n = 0, val = 0;
	
    std::cout <<"Enter number of houses ";
    std::cin >> n;
	
	// memoization table
	std::vector<int>dpTable(n,-1);

    std::cout <<"Enter amount of money in each house: ";
    for (int i = 0; i < n; ++i) 
	{
        std::cin >> val;
		money.push_back(val);
	}
 
    std::cout << houseRobber(dpTable, n);
    return 0;
}
