
/* Given two strings str1 & str2
 * and below operations that can
 * be performed on str1. Find
 * minimum number of edits
 * (operations) required to convert
 * 'str1' into 'str2'/
 * a. Insert
 * b. Remove
 * c. Replace
 * All of the above operations are
 * of equal cost
 */

#include <iostream>
#include <string>
#include <vector>


int min(int x, int y, int z) { return std::min(std::min(x, y), z); }

/* A Naive recursive C++ program to find
 * minimum number of operations to convert
 * str1 to str2.
 * O(3^m)
 */
int editDist(const std::string &str1,const std::string &str2, int m, int n) {
    if (m == 0)
        return n;
    if (n == 0)
        return m;

    // If last characters are same then continue
    // for the rest of them.
    if (str1[m - 1] == str2[n - 1])
        return editDist(str1, str2, m - 1, n - 1);

    // If last not same, then 3 possibilities
    // a.Insert b.Remove c. Replace
    // Get min of three and continue for rest.
    return 1 + min(editDist(str1, str2, m, n - 1),
                   editDist(str1, str2, m - 1, n),
                   editDist(str1, str2, m - 1, n - 1));
}

/* A DP based program
 * Time Complexity:O(m x n)
 * Space Complexity: O(m x n)
 */
int editDistDP(const std::string &str1,const std::string &str2, int m, int n) {
    // Create Table for SubProblems
    std::vector<std::vector<int>>dp(m+1,std::vector<int>(n+1));

    // Fill d[][] in bottom up manner
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            // If str1 empty. Then add all of str2
            if (i == 0)
                dp[i][j] = j;

            // If str2 empty. Then add all of str1
            else if (j == 0)
                dp[i][j] = i;

            // If character same. Recur for remaining
            else if (str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];

            else
                dp[i][j] = 1 + min(dp[i][j - 1],     // Insert
                                   dp[i - 1][j],     // Remove
                                   dp[i - 1][j - 1]  // Replace
                               );
        }
    }

    return dp[m][n];
}

/* A DP based program
 * Time Complexity: O(m x n)
 * Space Complexity: O(n) 
 */

/* In the above DP approach,
 * for particular index i we require
 * dp[i-1][j] and dp[i-1][j-1] values.
 * Thus dp values before i-1 i.e 
 * dp[i-2][j],dp[i-3][j]...
 * values are of no use to us.
 * Therefore instead of storing m*n table
 * we will only store values of 
 * dp[i-1][0],dp[i-1][1] ....dp[i-1[m] in 1D vector.
 * After traversing for particular index i
 * current dp values become previous dp values for index i+1
 * thus we will copy the cur vector to pre vector
 * and move to next index
 */ 

int editDistDP_in_O_n_space(const std::string &str1,const std::string &str2, int m, int n) {

    std::vector<int>pre(n + 1); //stores the dp value for previous index

    for (int i = 0; i <= m; i++) {
        std::vector<int>cur(n + 1); //stores the dp value for current index
        for (int j = 0; j <= n; j++) {
            // If str1 empty. Then add all of str2
            if (i == 0)
                cur[j] = j;

            // If str2 empty. Then add all of str1
            else if (j == 0)
                cur[j] = i;

            // If character same. Recur for remaining
            else if (str1[i - 1] == str2[j - 1])
                cur[j] = pre[j - 1];

            else
                cur[j] = 1 + min(cur[j - 1],     // Insert
                                   pre[j],     // Remove
                                   pre[j - 1]  // Replace
                               );
        }
        //now for next index i.e (i+1) we require dp values of ith index
        //so now cur becomes pre
        for(int j=0;j<=n;j++)
         {
            pre[j]=cur[j];   //copying cur values to pre
         }
    }

    return pre[n];
}

int main() {
    std::string str1 = "sunday";
    std::string str2 = "saturday";

    std::cout << editDist(str1, str2, str1.length(), str2.length()) << std::endl;
    std::cout << editDistDP(str1, str2, str1.length(), str2.length()) << std::endl;
    std::cout << editDistDP_in_O_n_space(str1, str2, str1.length(), str2.length()) <<std::endl;

    return 0;
}
