/*
House Robber - Dynamic Programming

Problem Statement: 
A robber is planning to rob houses along a street. Each house has a 
certain  amount  of money stashed, the only constraint stopping you 
from  robbing  each of them  is that  adjacent houses have security 
system connected and it will automatically contact the police if two
adjacent houses were broken into on the same night.

Task: 
Determine the maximum amount of money you can rob tonight without alerting the police
*/


#include <iostream>
#include <vector>
#include <cstring> 

int houseRobber(int dpTable[],vector<int>& money,int n,int pos=0)
{
    if(pos >= n)
        return 0;              // if all houses are done, return 0
        
    if(dpTable[pos] != -1)
        return dpTable[pos];   // if the result for this position has been already calculated, return it
        
    return dpTable[pos] = max( 
	                      money[pos]+houseRobber(dpTable, money, n, pos+2)     // rob the current house & move to next to next one
						           ,houseRobber(dpTable, money, n, pos+1));             // didn't rob the current house move to next one
}
	
int main() 
{
	int n;
	
    cout <<"Enter number of houses ";
    cin >> n;
	
	vector<int> money(n);
	
	// memoization table
	int dpTable[n]; 

	memset(dpTable,-1,sizeof(dpTable));
	
    cout <<"Enter amount of money in each house: ";
    for (int i = 0; i < n; ++i) 
        cin >> money[i];
 
    cout << houseRobber(dpTable,money,n);
    return 0;
}
