/**
 * @file
 * @minimum coins change problem is a problem used to find the minimum number of 
 * coins required to completely reach a target amount.
 *
 * @details
 * This problem can be solved using 2 methods:
 * 1. Top down approach
 * 2. Bottom up appraoch
 * Top down approach involves a vector with all elements initialised to 0.
 * It is based on optimal substructure and overlapping subproblems.
 * Overall time complexity of coin change problem is O(n*t)
 * For example: example 1:-
 * Coins: {1,7,10}
 * Target:15
 * Therfore minimum number of coins required = 3 of denomination 1,7 and 7.
 * @author [Divyansh Kushwaha](https://github.com/webdesignbydivyansh)
 * @see related problem at [Leetcode](https://leetcode.com/problems/coin-change/)
*/

#include <iostream>   // for io operations
#include <vector>     // for std::vector
#include <cassert>    // for std::assert
#include <climits>    // for INT_MAX

/**
 * @namespace min_coin_change
 * @brief minimum number of coins
 */
namespace min_coin_change {
/**
 * @namespace mincoins_topdown
 * @brief Functions for [minimum coin exchange](https://leetcode.com/problems/coin-change/) problem
 */
namespace mincoins_topdown {
    /**
    * @brief This implementation is for finding minimum number of coins .
    * @param n, coins, t, dp
    * @param n amount to be reached
    * @param coins vector of coins
    * @param t number of coins available
    * @param dp initilised to 0
    * @returns minimum number of coins
    */
    template<typename T>
    int mincoins(T n, std::vector<T> coins, const int t, std::vector<T> dp){
        if(n==0){
            return 0;
        }
        if(dp[n]!=0){
            return dp[n];
        }
        int ans=INT_MAX;    //variable to store min coins
        for(int i=0;i<t;i++){
            if(n-coins[i]>=0){  //if after subtracting the current denomination is it                     greater than 0 or not
                int sub=mincoins(n-coins[i],coins,t,dp);
                ans=std::min(ans,sub+1);
            }
        }
        dp[n]=ans;
        return dp[n];   //returns minimum number of coins
    }

}  // namespace mincoins_topdown
}  // namespace min_coin_change

/**
 * @brief Test implementations
 * @returns void
 */
static void test() {
    // example 1: number of coins=3 and minimum coins required=3(7,7,1)
    const int n1 = 15, t1=3, a1=0;
    std::cout << "\nTest 1...";
    std::vector<int> arr1 {1,7,10};
    std::vector<int> dp1 (n1+1);
    fill(dp1.begin(),dp1.end(),a1);
    assert(min_coin_change::mincoins_topdown::mincoins(n1, arr1, t1, dp1)==3);
    std::cout << "Passed\n";

}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();
    return 0;
}
