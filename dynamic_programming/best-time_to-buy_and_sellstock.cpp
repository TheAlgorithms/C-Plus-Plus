/*
 *  
 *[Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)
 *
 * Explanation:
 *If buy stock at 7 & sell at any time in the future, we'll face loss. Because buying price is way higher then selling price available we have
 *Now, I have seen a dip & I buy at 1 & sell at 5 my overall profit will be 5 - 1 = 4
 *But what if, I had buy at 1 & sell at 6 my profit will be 6 - 1 = 5. Which is greater then my overall profit. So, i will update my overall profit with new value.
 *Now we have done as further we don't have any higher point to sell. We will return our answer.
 * 
 * 
 */
#include <iostream>

using namespace std;

class Solution {
 public:
    int maxProfit(vector<int>& prices) {
        int lsf = INT_MAX; // Least so far
        int op = 0; // Overall profit
        int pist = 0; // Profit if sold today

        for (int i = 0; i < prices.size(); i++) { // prices.size() is the number of elements in the vector
            if (prices[i] < lsf) {
                lsf = prices[i];
            }
            pist = prices[i] - lsf; // Profit if sold today
            if (op < pist) {
                op = pist;
            }
        }
        return op;
    }
};

// main function to run the program
int main(){
    vector<int> prices = {7, 6, 4, 3, 1}; // prices of the stock
    Solution s;
    cout << s.maxProfit(prices) << endl; // prints the maximum profit
   
    return 0; 
}

// Language: cpp
// Path: C-Plus-Plus\dynamic_programming\best-time_to-buy_and_sellstock.cpp

/* Testcases: 1
prices = [ 7, 1, 5, 3, 6, 4 ]
Expected Output: 5 

Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Not 7-1 = 6, as selling price needs to be larger than buying price.

*/


/* Testcases: 2

prices = [ 7, 6, 4, 3, 1 ]
Expected Output: 0 
Explanation: In this case, no transaction is done, i.e. max profit = 0.

*/

/* Testcases: 3

prices = [ 1, 2 ]
Expected Output: 1 
Explanation: Buy on day 0 (price = 1) and sell on day 1 (price = 2), profit = 2-1 = 1.

*/

/* Testcases: 4

prices = [ 2, 4, 1 ]
Expected Output: 2 
Explanation: Buy on day 0 (price = 2) and sell on day 1 (price = 4), profit = 4-2 = 2.

*/

/* Testcases: 5

prices = [ 2, 1, 2, 1, 0, 1, 2 ]
Expected Output: 2 
Explanation: Buy on day 5 (price = 0) and sell on day 6 (price = 2), profit = 2-0 = 2.

*/
