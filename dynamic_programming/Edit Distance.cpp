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
using namespace std;

int min(int x, int y, int z)
{
    return min(min(x, y), z);
}

/* A Naive recursive C++ program to find
 * minimum number of operations to convert
 * str1 to str2.
 * O(3^m)
 */
int editDist(string str1, string str2, int m, int n)
{
    if (m == 0)
        return n;
    if (n == 0)
        return m;

    //If last characters are same then continue
    //for the rest of them.
    if (str1[m - 1] == str2[n - 1])
        return editDist(str1, str2, m - 1, n - 1);

    //If last not same, then 3 possibilities
    //a.Insert b.Remove c. Replace
    //Get min of three and continue for rest.
    return 1 + min(editDist(str1, str2, m, n - 1),
                   editDist(str1, str2, m - 1, n),
                   editDist(str1, str2, m - 1, n - 1));
}

/* A DP based program
 * O(m x n)
 */
int editDistDP(string str1, string str2, int m, int n)
{

    //Create Table for SubProblems
    int dp[m + 1][n + 1];

    //Fill d[][] in bottom up manner
    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            //If str1 empty. Then add all of str2
            if (i == 0)
                dp[i][j] = j;

            //If str2 empty. Then add all of str1
            else if (j == 0)
                dp[i][j] = i;

            //If character same. Recur for remaining
            else if (str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];

            else
                dp[i][j] = 1 + min(dp[i][j - 1],    //Insert
                                   dp[i - 1][j],    //Remove
                                   dp[i - 1][j - 1] //Replace
                               );
        }
    }

    return dp[m][n];
}

int main()
{
    string str1 = "sunday";
    string str2 = "saturday";

    cout << editDist(str1, str2, str1.length(), str2.length()) << endl;
    cout << editDistDP(str1, str2, str1.length(), str2.length()) << endl;

    return 0;
}
